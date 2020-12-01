#include <Eigen/Core>
#include <map>
#include <vector>
#include <math.h>

using namespace Eigen;

class Histogram
{
public:

    using vocabulary = MatrixXd;
    using index = std::map<int, std::vector<Histogram>>;

public:

    Histogram() = default;
    Histogram(MatrixXd const& bagOfFeatures);

    void updateIndex();
    void setValue(MatrixXd const& bagOfFeatures);

    double distance(Histogram const& hist2);

private:

    static vocabulary &featuresVocabulary;
    static index &inverseIndex;
    std::map<int, double> weights;
    VectorXi computeCentroids(MatrixXd const& bagOfFeatures);
    void computeWeights(VectorXi const& bagOfWords);
    void indexize();
};