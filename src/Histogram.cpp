#include "Histogram.hpp"


Histogram::Histogram(MatrixXd const& bagOfFeatures)
{
    VectorXi words = this->computeCentroids(bagOfFeatures);
    this->computeWeights(words);
};

void Histogram::setValue(MatrixXd const& bagOfFeatures)
{
    VectorXi words = this->computeCentroids(bagOfFeatures);
    this->computeWeights(words);
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
        if(wordIndex == 1)
            continue;
        if(rawHistogram.find(wordIndex) == rawHistogram.end())
        {
            rawHistogram[wordIndex] = 1;
        }
        else
        {
            rawHistogram[wordIndex]++;
        }
    }

/*     for (auto i = rawHistogram.cbegin(); i != rawHistogram.cend(); i++)
    {
        cout << "la feature " << i->first << " apparaît " << i->second << " fois" << endl;
    } */

    int numberOfViews = this->vocabulary.getNumberOfViews();
    VectorXd vocabFrequencies = this->vocabulary.getFrequecies();
    this->weights = {};
    for (auto& item: rawHistogram)
    {
        weights[item.first] =  log(numberOfViews / vocabFrequencies(item.first)) * static_cast<double>(item.second) / static_cast<double>(bagOfWords.rows());
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

void Histogram::writeToFile(string path)
{
    ofstream file;
    file.open(path);
    for (auto i = weights.cbegin(); i != weights.cend(); i++)
    {
        file << i->first << " " << i->second << endl;
    }
    file.close();    
}

void Histogram::writeToFile(ofstream &file)
{
    for (auto i = weights.cbegin(); i != weights.cend(); i++)
    {
        file << i->first << " " << i->second << endl;
    }
}

void Histogram::setFromFile(string path)
{
    this->weights = {};
    ifstream file;
    file.open(path);
    int idx;
    double weight;
    while (file >> idx && file >> weight)
    {
        this->weights[idx] = weight;
    }
    file.close();   
}

void Histogram::setFromStream(ifstream &file)
{
    string line;
    getline(file, line);
    while (line.compare("===END===") != 0)
    {
        vector<string> tmp;
        boost::split(tmp, line, boost::is_any_of(" "));
        assert(tmp.size() == 2);
        weights[atoi(tmp[0].c_str())] = stod(tmp[1]);
        getline(file, line);
    }
}