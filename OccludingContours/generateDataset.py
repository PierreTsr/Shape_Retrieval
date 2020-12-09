import occludingContours as oc
import os
from tqdm import tqdm

def main(datasetPath, cameraFile):

    oc.setupPipeline()
    cameraDirections = oc.getPositionsFromFile(cameraFile)
    for i in tqdm(range(7, 19)):
        for j in tqdm(range(0, 100)):
            if 100*i + j == 762:
                continue
            path = datasetPath + "/" + str(i) + "/m" + str(100*i + j)
            srcPath = path + "/m" + str(100*i + j) + ".obj"
            oc.setSourceFile(srcPath)
            if not os.path.exists(path + "/render"):
                os.mkdir(path + "/render")
            destPath = path + "/render/m" + str(100*i + j) + "_"
            oc.renderMutliplePositions(cameraDirections, destPath)

dbPath = "/home/pierre/Documents/INF574/psb_v1/benchmark/db"
cameraFile = "camera_position.xy"

if __name__ == "__main__" :
    main(dbPath, cameraFile)