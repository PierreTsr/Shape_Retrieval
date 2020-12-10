//
// Created by tom on 01/12/2020.
//

#ifndef SHAPE_RETRIEVAL__BAG_OF_FEATURES_H_
#define SHAPE_RETRIEVAL__BAG_OF_FEATURES_H_

#define GABOR_KERNEL_SIZE 11
#define TILE_SIZE 4
#define KERNEL_WIDTH 0.2
#define NB_ORIENTATION 4

#include <Eigen/Core>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <cmath>
#include <omp.h>
#include <iostream>

using namespace std;
using namespace Eigen;
using namespace cv;


class BagOfFeatures
{
 private :

	Mat line_rendering;

 public :
	MatrixXd features;

	BagOfFeatures();
	BagOfFeatures(Mat& _line_rendering);
	~BagOfFeatures();

	void gabor_computing();

	Mat ApplyFiter(double theta, double sigma_x, double sigma_y, double omega);
};

#endif //SHAPE_RETRIEVAL__BAG_OF_FEATURES_H_