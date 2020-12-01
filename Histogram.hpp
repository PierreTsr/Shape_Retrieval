#include <Eigen/Core>
#include <map>
#include <vector>

using namespace Eigen;

class Histogram
{
public:

    using vocabulary = MatrixXd;
    using index = std::map<int, std::vector<Histogram>>;

public:

    Histogram(MatrixXd const& bagOfFeatures);

    static double distance(Histogram const& hist1, Histogram const& hist2);
    void indexize();

private:

    static vocabulary &featuresVocabulary;
    static index &inverseIndex;
};