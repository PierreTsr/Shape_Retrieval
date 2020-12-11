#ifndef SHAPE_RETRIEVAL__HISTOGRAM_H_
#define SHAPE_RETRIEVAL__HISTOGRAM_H_

#include <Eigen/Core>
#include <map>
#include <vector>
#include <math.h>
#include <boost/algorithm/string.hpp>
#include "Vocabulary.hpp"

using namespace Eigen;

class Histogram
{
public:

	static Vocabulary vocabulary;

	Histogram() = default;
    Histogram(MatrixXd const& bagOfFeatures);

    void setValue(MatrixXd const& bagOfFeatures);
    void writeToFile(string path);
    void writeToFile(ofstream &file);
    void setFromFile(string path);
    void setFromStream(ifstream &file);

    double distance(Histogram const& hist2);

    std::map<int, double> weights;

private:

    
    VectorXi computeCentroids(MatrixXd const& bagOfFeatures);
    void computeWeights(VectorXi const& bagOfWords);
};

#endif //SHAPE_RETRIEVAL__HISTOGRAM_H_