#ifndef SHAPE_RETRIEVAL__HISTOGRAM_H_
#define SHAPE_RETRIEVAL__HISTOGRAM_H_

#include <Eigen/Core>
#include <map>
#include <vector>
#include <math.h>
#include "Vocabulary.hpp"

using namespace Eigen;

class Histogram
{
public:

	static Vocabulary vocabulary;

	Histogram() = default;
    Histogram(MatrixXd const& bagOfFeatures);

    void setValue(MatrixXd const& bagOfFeatures);
    std::map<int, double> getWeigths(){return weights;};
    void writeToFile(string path);
    void setFromFile(string path);

    double distance(Histogram const& hist2);

private:

    std::map<int, double> weights;
    VectorXi computeCentroids(MatrixXd const& bagOfFeatures);
    void computeWeights(VectorXi const& bagOfWords);
};

#endif //SHAPE_RETRIEVAL__HISTOGRAM_H_