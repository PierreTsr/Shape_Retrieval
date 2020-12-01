#include "Histogram.hpp"

Histogram::Histogram(MatrixXd const& bagOfFeatures)
{
    MatrixXi words = this->computeCentroids(bagOfFeatures);
    this->computeWeights(words);
    this->indexize();
};

void Histogram::setValue(MatrixXd const& bagOfFeatures)
{
    this->computeWeights(bagOfFeatures);
};

void Histogram::updateIndex()
{
    //Remove from index if necessary
    //TODO
    this->indexize();
};

VectorXi Histogram::computeCentroids(MatrixXd const& bagOfFeatures)
{
    VectorXd sqNormVoc, sqNormFeatures;
    MatrixXd allDotProducts, distanceToVoc;

    sqNormVoc = this->featuresVocabulary.rowwise().squaredNorm();
    sqNormFeatures = bagOfFeatures.rowwise().squaredNorm();
    allDotProducts = this->featuresVocabulary * bagOfFeatures.transpose();

    distanceToVoc = -2*allDotProducts;
    distanceToVoc.colwise() += sqNormVoc;
    distanceToVoc.rowwise() += sqNormFeatures.transpose();

    VectorXi words(distanceToVoc.cols());
    for (size_t i = 0; i < distanceToVoc.cols(); i++ )
    {
        MatrixXd::Index minIndex;
        distanceToVoc.col(i).minCoeff(&minIndex);
        words(i) = minIndex;
    }
    return words;
};

void Histogram::computeWeights(VectorXi const& bagOfWords)
{
    std::map<int, int> rawHistogram = {};
    for (size_t i = 0; i < bagOfWords.rows(); i++)
    {
        int wordIndex = bagOfWords(i);
        if(rawHistogram.find(wordIndex) == rawHistogram.end())
        {
            rawHistogram[wordIndex] = 1;
        }
        else
        {
            rawHistogram[wordIndex]++;
        }
    }

    int numberOfViews;
    VectorXd vocabFrequencies;
    this->weights = {};
    for (auto& item: rawHistogram)
    {
        weights[item.first] = item.second / bagOfWords.rows() * log(numberOfViews / vocabFrequencies(item.first));
    }
};