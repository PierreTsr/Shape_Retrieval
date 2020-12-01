//
// Created by tom on 01/12/2020.
//
#include "BagOfFeatures.h"
#include <opencv2/opencv.hpp>
#include <Eigen/src/Core/Matrix.h>

using namespace std;
using namespace Eigen;
using namespace cv;

BagOfFeatures::BagOfFeatures(Mat& _line_rendering, int const _k, int const _kernel_size) : kernel_size(_kernel_size), k(_k)
{
	this->line_rendering = _line_rendering;
	this->features = VectorXd::Zero(kernel_size * kernel_size * k);

}
BagOfFeatures::~BagOfFeatures()
{
}

MatrixXd BagOfFeatures::gabor_computing()
{
	int h = getOptimalDFTSize(line_rendering.rows);
	int w = getOptimalDFTSize(line_rendering.cols);

	cv::Mat dst;
	cv::Mat fourierTransform;

	//padding
	copyMakeBorder(line_rendering, dst, 0, h - line_rendering.rows, 0, w - line_rendering.cols, BORDER_CONSTANT, Scalar::all(0));
	//fourier transform
	Mat planes[] = {Mat_<float>(dst), Mat::zeros(dst.size(), CV_32F)};
	Mat complexI;
	merge(planes, 2, complexI);         // Add to the expanded another plane with zeros
	dft(complexI, complexI);            // this way the result may fit in the source matrix
	// compute the magnitude and switch to logarithmic scale
	// => log(1 + sqrt(Re(DFT(I))^2 + Im(DFT(I))^2))
	split(complexI, planes);                   // planes[0] = Re(DFT(I), planes[1] = Im(DFT(I))
	magnitude(planes[0], planes[1], planes[0]);// planes[0] = magnitude
	fourierTransform = planes[0];

	for (int i=0;i<k;i++){
		Mat filteredFourierTransform;
		double sig = 1, th = 0, lm = 1.0, gm = 0.02, ps = 0;
		Mat kernel = cv::getGaborKernel(Size(kernel_size, kernel_size), sig, th, lm, gm, ps);
		filter2D(fourierTransform, filteredFourierTransform, CV_32F, kernel);
	}

	/*
	idft(complexI, invDFT, DFT_SCALE | DFT_REAL_OUTPUT ); // Applying IDFT
	invDFT.convertTo(invDFTcvt, CV_8U);
	imshow("Output", invDFTcvt);

	//show the image
	imshow("Original Image", img); */



}

