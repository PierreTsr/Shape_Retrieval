//
// Created by tom on 01/12/2020.
//

#ifndef SHAPE_RETRIEVAL__BAG_OF_FEATURES_H_
#define SHAPE_RETRIEVAL__BAG_OF_FEATURES_H_

#endif //SHAPE_RETRIEVAL__BAG_OF_FEATURES_H_

#include <Eigen/Eigen>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace Eigen;
using namespace cv;

class BagOfFeatures
{
 private :
	BagOfFeatures(Mat& _line_rendering, const int _k, const int __kernel_size);
	MatrixXd gabor_computing();
	Mat line_rendering;
	const int kernel_size;
	const int k;
 public :
	MatrixXd features;

	BagOfFeatures(Mat _line_rendering, int _k, int _kernel_size);
	BagOfFeatures();
	~BagOfFeatures();
};