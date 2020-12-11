#include "VocabularyGenerator.hpp"

using namespace std;


void buildSample( size_t nSamples,size_t nViews)
{
    MatrixXd samples;
    collectSamples(samples, nSamples, nViews);
    saveSamples(samples);

}

void buildVocabulary(Vocabulary &vocab, size_t nSamples, size_t vocabSize, size_t nViews)
{
    MatrixXd samples;
    collectSamples(samples, nSamples, nViews);
    saveSamples(samples);
    vocab.setSamples(samples, vocabSize);
    vocab.setNViews(nViews);
    saveVocabulary(vocab);
}


void collectSamples(MatrixXd &samples, size_t nSamples, size_t nViews)
{
    samples = MatrixXd(nSamples,64);
    default_random_engine generator;
    uniform_int_distribution<int> rndModel(0,1814);
    uniform_int_distribution<int> rndView(0,nViews-1);
    uniform_int_distribution<int> rndFeature(0,1023);
    #pragma omp parallel for schedule(dynamic, 16)
    for (size_t n = 0; n < nSamples; n++)
    {
        stringstream status;
        status << "Sampling " << 100.0 * n / nSamples << "% completed" << endl;
        cout << status.str();
        int i = rndModel(generator);
        while (i == 762)
        {
            i = rndModel(generator);
        }
        int j = rndView(generator);
        int k = rndFeature(generator);
        stringstream srcPath;
        srcPath << DATASET_PATH << "/" << to_string(i / 100) << "/m" << to_string(i) << "/render/m" << to_string(i) << "_" << to_string(j) << ".png";
        
        Mat input = imread(srcPath.str(), cv::IMREAD_GRAYSCALE); //grayscale
        BagOfFeatures BoF = BagOfFeatures(input);
        BoF.gabor_computing();

        samples.row(n) = BoF.features.row(k);
    }
    
}

void saveVocabulary(Vocabulary& vocab)
{
    MatrixXd centroids = vocab.getVocabulary();
    ofstream centroidsFile;
    centroidsFile.open("../data/centroids.xy");
    for (size_t i = 0; i < centroids.rows(); i++)
    {
        centroidsFile << centroids.row(i) << endl;
    }
    centroidsFile.close();

    VectorXd frequencies = vocab.getFrequecies();
    ofstream frequenciesFile;
    frequenciesFile.open("../data/frequencies.xy");
    for (size_t i = 0; i < frequencies.rows(); i++)
    {
        frequenciesFile << frequencies.row(i) << endl;
    }
    frequenciesFile.close();
}

void saveSamples(MatrixXd &samples)
{
    ofstream samplesFile;
    samplesFile.open("../data/samples_full.xy");
    for (size_t i = 0; i < samples.rows(); i++)
    {
        samplesFile << samples.row(i) << endl;
    }
    samplesFile.close();
}