//
// Created by tom on 01/12/2020.
//

#ifndef SHAPE_RETRIEVAL__BAG_OF_FEATURES_H_
#define SHAPE_RETRIEVAL__BAG_OF_FEATURES_H_

#include <Eigen/Core>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <cmath>
#include <omp.h>

using namespace std;
using namespace Eigen;
using namespace cv;


class BagOfFeatures
{
 private :

	Mat line_rendering;

	const int gabor_kernel_size;
	const double tile_size;
	const double kernel_width;	//fraction of the total image.
	const int k;

 public :
	MatrixXd features;

	BagOfFeatures() = default;
	BagOfFeatures(Mat& _line_rendering, const int _k, const int _gabor_kernel_size,const int _tile_size,const double _kernel_width);
	~BagOfFeatures();

	void gabor_computing();

	Mat ApplyFiter(double theta, double sigma_x, double sigma_y, double omega);
};

#endif //SHAPE_RETRIEVAL__BAG_OF_FEATURES_H_