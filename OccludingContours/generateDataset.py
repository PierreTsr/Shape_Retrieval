import occludingContours as oc
import os

def main(datasetPath, cameraFile):

    oc.setupPipeline()
    cameraDirections = oc.getPositionsFromFile(cameraFile)
    for i in range(0, 1):
        for j in range(0, 10):
            path = datasetPath + "/" + str(i) + "/m" + str(j)
            srcPath = path + "/m" + str(j) + ".obj"
            oc.setSourceFile(srcPath)
            if not os.path.exists(path + "/render/"):
                os.mkdir(path + "/render/")
            destPath = path + "/render/m" + str(j) + "_"
            oc.renderMutliplePositions(cameraDirections, destPath)

dbPath = "/home/pierre/Documents/INF574/psb_v1/benchmark/db"
cameraFile = "OccludingContours/camera_position.xy"

if __name__ == "__main__" :
    main(dbPath, cameraFile)