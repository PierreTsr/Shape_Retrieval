#ifndef SHAPE_RETRIEVAL__VOCABULARY_H_
#define SHAPE_RETRIEVAL__VOCABULARY_H_

#include <Eigen/Core>
#include <fstream>
#include <cstdlib>
#include <iostream>
#include "opencv2/core.hpp"
#include "opencv2/core/eigen.hpp"
#include "../external/dkm/include/dkm.hpp"

using namespace Eigen;
using namespace std;

#define FEATURE_DIM 64

void eigen2std(const MatrixXd &mat, vector<array<double, FEATURE_DIM>> &vec);
void std2eigen(const vector<array<double, FEATURE_DIM>> &vec, MatrixXd &mat);


class Vocabulary
{
public:
    Vocabulary() = default;
    Vocabulary(MatrixXd const& featureSamples, int vocabSize, int numberOfViews) {
        this->numberOfViews = numberOfViews;
        setSamples(featureSamples, vocabSize);
    };

    void setSamples(MatrixXd const& featureSamples, int vocabSize);
    void setNViews(int numberOfViews) {this->numberOfViews = numberOfViews; };
    void setCentroids(MatrixXd const& centroids){this->centroids = centroids; };
    void setFrequecies(VectorXd const& frequencies){this->frequencies = frequencies; };
    void setVocabFromFile(string vocabPath, size_t vocabSize);
    
    int getNumberOfViews() {return this->numberOfViews; };
    VectorXd getFrequecies() {return this->frequencies; }
    MatrixXd getVocabulary() {return this->centroids; };

private:
    int numberOfViews;
    VectorXd frequencies;
    MatrixXd centroids;
};

#endif //SHAPE_RETRIEVAL__VOCABULARY_H_