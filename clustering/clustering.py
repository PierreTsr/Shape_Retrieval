from sklearn.cluster import MiniBatchKMeans
import numpy as np

vocabSize = 2500

print("Loading samples...")
file = open("../data/samples_full.xy", "r")
samples = []
for l in file:
    line = l[:-1].split(" ")
    for i in range(len(line)-1, -1, -1):
        if line[i] == '':
            del(line[i])
    samples.append([float(s) for s in line])
samples = np.array(samples)
file.close()
print("Done")

print("Clustering...")
kmeans = MiniBatchKMeans(vocabSize, max_iter = 256, batch_size = 256, compute_labels = False, n_init = 16).fit(samples)
print("Done")

print("Writing data...")
centroids = kmeans.cluster_centers_
centroidFile = open("../data/centroids_full.xy", "w")
for i in range(0, centroids.shape[0]):
    for j in range(0, centroids.shape[1]):
        centroidFile.write(str(centroids[i, j]) + " ")
    centroidFile.write("\n")
centroidFile.close()

labels = kmeans.predict(samples)
frequencies = np.zeros((vocabSize,))
frequenciesFile = open("../data/frequencies_full.xy", "w")
for i in range(0, labels.shape[0]):
    frequencies[labels[i]]+=1
for i in range(0, vocabSize):
    frequenciesFile.write(str(frequencies[i]) + "\n")
frequenciesFile.close()
print("Done")
