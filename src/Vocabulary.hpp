#include <Eigen/Core>
#include "opencv2/core.hpp"
#include "opencv2/core/eigen.hpp"
using namespace Eigen;

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
    
    int getNumberOfViews() {return this->numberOfViews; };
    VectorXd getFrequecies() {return this->frequencies; }
    MatrixXd getVocabulary() {return this->centroids; };

private:
    int numberOfViews;
    VectorXd frequencies;
    MatrixXd centroids;
};