#include "Vocabulary.hpp"

void Vocabulary::setSamples(MatrixXd const& featureSamples, int vocabSize)
{
    //clustering sur l'échantillon de features
    //placer les centroides dans this->centroids
    //calculer la fréquence de chaque mot et update this->frequencies
    
    int nPoints = featureSamples.rows(), dim = featureSamples.cols();
    cv::Mat cvData(nPoints, dim, CV_64F);
    cv::Mat labels(nPoints, 1, CV_16U);
    cv::Mat centroids(vocabSize, dim, CV_64F);
    cv::eigen2cv(featureSamples, cvData);
    
    cv::kmeans(cvData, vocabSize, labels, cvTermCriteria(CV_TERMCRIT_EPS, 10, .1), 10, 0, centroids);

    MatrixXd eigenCentroids(vocabSize, dim);
    cv::cv2eigen(centroids, eigenCentroids);
    this->centroids = eigenCentroids;

    this->frequencies = VectorXd::Zero(vocabSize);
    for (int i = 0; i < nPoints; i++)
    {
        this->frequencies(labels.at<int>(i, 0))++;
    }
    this->frequencies = frequencies / nPoints;
}