#include "Vocabulary.hpp"

void Vocabulary::setSamples(MatrixXd const& featureSamples, int vocabSize)
{
    //clustering sur l'échantillon de features
    //placer les centroides dans this->centroids
    //calculer la fréquence de chaque mot et update this->frequencies
    
    int nPoints = featureSamples.rows(), dim = featureSamples.cols();
    vector<array<double,FEATURE_DIM> > features;
    eigen2std(featureSamples, features);

    auto res = dkm::kmeans_lloyd(features, vocabSize);
    auto centroids = get<0>(res);
    auto labels = get<1>(res);

    MatrixXd eigenCentroids(vocabSize, dim);
    std2eigen(centroids, eigenCentroids);
    this->centroids = eigenCentroids;

    this->frequencies = VectorXd::Zero(vocabSize);
    for (int i = 0; i < nPoints; i++)
    {
        this->frequencies(labels[i])++;
    }
    this->frequencies = frequencies / nPoints;
}

void eigen2std(const MatrixXd &mat, vector<array<double, FEATURE_DIM>> &vec)
{
    for (size_t i = 0; i < mat.rows(); i++)
    {
        array<double, FEATURE_DIM> line;
        for (size_t j = 0; j < mat.cols(); j++)
        {
            line[j] = mat(i, j);
        }
        vec.push_back(line);
    }
}

void std2eigen(const vector<array<double, FEATURE_DIM>> &vec, MatrixXd &mat)
{
    for (size_t i = 0; i < vec.size(); i++)
    {
        for (size_t j = 0; j < FEATURE_DIM; j++)
        {
            mat(i, j) = vec[i][j];
        }
    }
}