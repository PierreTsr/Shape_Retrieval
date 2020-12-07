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

	Mat line_rendering;

	const int kernel_size;
	const int k;

	MatrixXd gabor_computing();
 public :
	MatrixXd features;

	BagOfFeatures() = default;
	BagOfFeatures(Mat& _line_rendering, const int _k, const int _kernel_size);
	~BagOfFeatures();

	void fftshift(const Mat& input_img, Mat& output_img);
	void calculateDFT(Mat& scr, Mat& dst);
	void FourierTransform();
	Mat fourier_transform;
};