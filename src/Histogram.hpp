#include <Eigen/Core>
#include <map>
#include <vector>
#include <math.h>
#include "Vocabulary.hpp"

using namespace Eigen;

class Histogram
{
public:

    using index = std::map<int, std::vector<Histogram>>;

public:

    Histogram() = default;
    Histogram(MatrixXd const& bagOfFeatures);

    void setValue(MatrixXd const& bagOfFeatures);

    double distance(Histogram const& hist2);

private:

    static Vocabulary &vocabulary;
    std::map<int, double> weights;
    VectorXi computeCentroids(MatrixXd const& bagOfFeatures);
    void computeWeights(VectorXi const& bagOfWords);
};