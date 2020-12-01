#include "Histogram.hpp"

Histogram::Histogram(MatrixXd const& bagOfFeatures)
{
    VectorXi words = this->computeCentroids(bagOfFeatures);
    this->computeWeights(words);
    this->indexize();
};

void Histogram::setValue(MatrixXd const& bagOfFeatures)
{
    VectorXi words = this->computeCentroids(bagOfFeatures);
    this->computeWeights(words);
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
    MatrixXd featuresVocabulary = this->vocabulary.getVocabulary();

    sqNormVoc = featuresVocabulary.rowwise().squaredNorm();
    sqNormFeatures = bagOfFeatures.rowwise().squaredNorm();
    allDotProducts = featuresVocabulary * bagOfFeatures.transpose();

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

    int numberOfViews = this->vocabulary.getNumberOfViews();
    VectorXd vocabFrequencies = this->vocabulary.getFrequecies();
    this->weights = {};
    for (auto& item: rawHistogram)
    {
        weights[item.first] = item.second / bagOfWords.rows() * log(numberOfViews / vocabFrequencies(item.first));
    }
};

double Histogram::distance(Histogram const& hist2)
{
    double dotProduct = 0;
    double normHist1 = 0;
    double normHist2 = 0;

    for (auto& item:this->weights)
    {
        normHist1 += pow(item.second, 2);
        if (hist2.weights.find(item.first) != hist2.weights.end())
            dotProduct += item.second * hist2.weights.at(item.first);
    }
    for (auto& item: hist2.weights)
        normHist2 += pow(item.second, 2);
    
    normHist1 = sqrt(normHist1);
    normHist2 = sqrt(normHist2);
    return dotProduct / (normHist1 * normHist2);
}