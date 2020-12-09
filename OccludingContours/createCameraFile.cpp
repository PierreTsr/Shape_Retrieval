#include <iostream>
#include <ostream>
#include <fstream>
#include <igl/readOFF.h>
#include <Eigen/Core>
#include <vector>
#include <array>
#include "../external/dkm/include/dkm.hpp"
using namespace std;
using namespace Eigen;

MatrixXd V;
MatrixXi F;

#define N_VIEWS 102

void eigen2std(const MatrixXd &mat, vector<array<double, 3>> &vec)
{
    for (size_t i = 0; i < mat.rows(); i++)
    {
        array<double, 3> line;
        for (size_t j = 0; j < mat.cols(); j++)
        {
            line[j] = mat(i, j);
        }
        vec.push_back(line);
    }
}

int main(int argc, char *argv[])
{
    igl::readOFF("../sphere.off", V, F);
    
    int nPoints = V.rows(), dim = V.cols();
    vector<array<double,3> > points;
    eigen2std(V, points);
    auto res = dkm::kmeans_lloyd(points, N_VIEWS);
    auto centroids = get<0>(res);

    ofstream cameraFile;
    cameraFile.open("../camera_position.xy");
    for (size_t i = 0; i < N_VIEWS; i++)
    {
        for (size_t j = 0; j < dim; j++)
        {
            cameraFile << centroids[i][j] << " ";
        }
        cameraFile << endl;
    }
    cameraFile.close();
    return 0;
}