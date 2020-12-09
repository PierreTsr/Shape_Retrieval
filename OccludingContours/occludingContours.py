import vtk
import numpy as np
from math import *

filename = "m0.obj"

def setupPipeline():
    #read file
    global reader
    reader = vtk.vtkOBJReader()
    reader.SetFileName(filename)

    #map 3d model
    global mapper
    mapper = vtk.vtkPolyDataMapper()
    mapper.SetInputConnection(reader.GetOutputPort())

    #set actor
    global actor
    actor = vtk.vtkActor()
    actor.SetMapper(mapper)

    # Create a rendering window and renderer
    global ren
    ren = vtk.vtkRenderer()
    ren.SetBackground(0, 0, 0)
    global intermediateWindow
    intermediateWindow = vtk.vtkRenderWindow()
    intermediateWindow.AddRenderer(ren)

    #render image
    global renImage
    renImage = vtk.vtkRenderLargeImage()
    renImage.SetInput(ren)
    renImage.SetMagnification(5)

    ren.AddActor(actor)

    #Canny edge detector inspired by
    #https://vtk.org/Wiki/VTK/Examples/Cxx/Images/CannyEdgeDetector

    #to grayscale
    global lumImage
    lumImage = vtk.vtkImageLuminance()
    lumImage.SetInputConnection(renImage.GetOutputPort())

    #to float
    global floatImage
    floatImage = vtk.vtkImageCast()
    floatImage.SetOutputScalarTypeToFloat()
    floatImage.SetInputConnection(lumImage.GetOutputPort())


    #gaussian convolution
    global smoothImage
    smoothImage = vtk.vtkImageGaussianSmooth()
    smoothImage.SetInputConnection(floatImage.GetOutputPort())
    smoothImage.SetDimensionality(2)
    smoothImage.SetRadiusFactors(1, 1, 0)


    #gradient
    global gradientImage
    gradientImage = vtk.vtkImageGradient()
    gradientImage.SetInputConnection(smoothImage.GetOutputPort())
    gradientImage.SetDimensionality(2)


    #gradient magnitude
    global magnitudeImage
    magnitudeImage = vtk.vtkImageMagnitude()
    magnitudeImage.SetInputConnection(gradientImage.GetOutputPort())

    #non max suppression
    global nonmaxSuppr
    nonmaxSuppr = vtk.vtkImageNonMaximumSuppression()
    nonmaxSuppr.SetDimensionality(2)


    #padding
    global padImage
    padImage = vtk.vtkImageConstantPad()
    padImage.SetInputConnection(gradientImage.GetOutputPort())
    padImage.SetOutputNumberOfScalarComponents(3)
    padImage.SetConstant(0)

    #to structured points
    global i2sp1
    i2sp1 = vtk.vtkImageToStructuredPoints()
    i2sp1.SetInputConnection(nonmaxSuppr.GetOutputPort())

    #link edges
    global linkImage
    linkImage = vtk.vtkLinkEdgels()
    linkImage.SetInputConnection(i2sp1.GetOutputPort())
    linkImage.SetGradientThreshold(2)

    #thresholds links
    global thresholdEdgels
    thresholdEdgels = vtk.vtkThreshold()
    thresholdEdgels.SetInputConnection(linkImage.GetOutputPort())
    thresholdEdgels.ThresholdByUpper(20)
    thresholdEdgels.AllScalarsOff()

    #filter
    global gf
    gf = vtk.vtkGeometryFilter()
    gf.SetInputConnection(thresholdEdgels.GetOutputPort())

    #to structured points
    global i2sp
    i2sp = vtk.vtkImageToStructuredPoints()
    i2sp.SetInputConnection(magnitudeImage.GetOutputPort())

    #subpixel
    global spe
    spe = vtk.vtkSubPixelPositionEdgels()
    spe.SetInputConnection(gf.GetOutputPort())

    #stripper
    global strip
    strip = vtk.vtkStripper()
    strip.SetInputConnection(spe.GetOutputPort())

    global dsm
    dsm = vtk.vtkPolyDataMapper()
    dsm.SetInputConnection(strip.GetOutputPort())
    dsm.ScalarVisibilityOff()

    global planeActor
    planeActor = vtk.vtkActor()
    planeActor.SetMapper(dsm)
    planeActor.GetProperty().SetAmbient(1.0)
    planeActor.GetProperty().SetDiffuse(0.0)

    global edgeRender
    edgeRender = vtk.vtkRenderer()
    edgeRender.AddActor(planeActor)
    global renderWindow
    renderWindow = vtk.vtkRenderWindow()
    renderWindow.AddRenderer(edgeRender)

    global finalImage
    finalImage = vtk.vtkRenderLargeImage()
    finalImage.SetMagnification(5)
    finalImage.SetInput(edgeRender)

    global revImage
    revImage = vtk.vtkImageThreshold()
    revImage.SetInputConnection(finalImage.GetOutputPort())
    revImage.ThresholdByUpper(127)
    revImage.ReplaceInOn()
    revImage.ReplaceOutOn()
    revImage.SetOutValue(255)
    revImage.SetInValue(0)

    #write image
    global imgWriter
    imgWriter = vtk.vtkPNGWriter()
    imgWriter.SetInputConnection(revImage.GetOutputPort())
    imgWriter.SetFileName("test.png")

def runPipeline():

    renImage = vtk.vtkRenderLargeImage()
    renImage.SetInput(ren)
    renImage.SetMagnification(5)
    lumImage.SetInputConnection(renImage.GetOutputPort())

    intermediateWindow.Render()
    
    magnitudeImage.Update()
    nonmaxSuppr.SetMagnitudeInputData(magnitudeImage.GetOutput())
    gradientImage.Update()
    nonmaxSuppr.SetVectorInputData(gradientImage.GetOutput())

    padImage.Update()
    i2sp1.SetVectorInputData(padImage.GetOutput())

    padImage.Update()
    i2sp.SetVectorInputData(padImage.GetOutput())

    i2sp.Update()
    spe.SetGradMapsData(i2sp.GetOutput())

    finalImage = vtk.vtkRenderLargeImage()
    finalImage.SetMagnification(5)
    finalImage.SetInput(edgeRender)
    revImage.SetInputConnection(finalImage.GetOutputPort())

    renderWindow.Render()
    imgWriter.Write()

    del(renImage)
    del(finalImage)


def setOrientation(direction):
    if direction[0] == 0 and direction[2]==0:
        direction[0]= .01
    direction = direction / np.linalg.norm(direction)
    print(direction)

    camera = vtk.vtkCamera()
    cameraPosition = mapper.GetCenter() + direction * 2 * mapper.GetLength()
    ren.GetActiveCamera().SetPosition(cameraPosition)
    ren.GetActiveCamera().SetFocalPoint(mapper.GetCenter())

def setSourceFile(filename):
    reader.SetFileName(filename)

def setDestFile(filename):
    imgWriter.SetFileName(filename)

def renderMutliplePositions(directions, prefix = "img"):
    for i in range(directions.shape[0]) :
        setOrientation(directions[i, :])
        setDestFile(prefix + str(i) + ".png")
        runPipeline()

def getPositionsFromFile(filename):
    directions = []
    with open(filename) as f:
        for line in f:
            l = line.split()
            point = [float(a) for a in l]
            directions.append(point)
    directions = np.array(directions)
    return directions
