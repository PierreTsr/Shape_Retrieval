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

void BagOfFeatures::FourierTransform()
{
	line_rendering.convertTo(line_rendering, CV_32F);
	// expand input image to optimal size
	Mat padded;
	int m = getOptimalDFTSize(line_rendering.rows);
	int n = getOptimalDFTSize(line_rendering.cols);
	copyMakeBorder(line_rendering, padded, 0, m - line_rendering.rows, 0, n - line_rendering.cols, BORDER_CONSTANT, Scalar::all(0));

	// calculate DFT
	Mat DFT_image;
	calculateDFT(padded, DFT_image);

	Mat real, imaginary;
	Mat planes[] = { real, imaginary };

	split(DFT_image, planes);
	Mat mag_image;
	magnitude(planes[0], planes[1], mag_image);

	// switch to a logarithmic scale
	mag_image += Scalar::all(1);
	log(mag_image, mag_image);
	mag_image = mag_image(Rect(0, 0, mag_image.cols & -2, mag_image.rows & -2));

	fftshift(mag_image, fourier_transform);

	normalize(fourier_transform, fourier_transform, 0, 1, NORM_MINMAX);

}

void  BagOfFeatures::calculateDFT(Mat &scr, Mat &dst)
{
	// define mat consists of two mat, one for real values and the other for complex values
	Mat planes[] = { scr, Mat::zeros(scr.size(), CV_32F) };
	Mat complexImg;
	merge(planes, 2, complexImg);

	dft(complexImg, complexImg);
	dst = complexImg;
}

void  BagOfFeatures::fftshift(const Mat &input_img, Mat &output_img)
{
	output_img = input_img.clone();
	int cx = output_img.cols / 2;
	int cy = output_img.rows / 2;
	Mat q1(output_img, Rect(0, 0, cx, cy));
	Mat q2(output_img, Rect(cx, 0, cx, cy));
	Mat q3(output_img, Rect(0, cy, cx, cy));
	Mat q4(output_img, Rect(cx, cy, cx, cy));

	Mat temp;
	q1.copyTo(temp);
	q4.copyTo(q1);
	temp.copyTo(q4);
	q2.copyTo(temp);
	q3.copyTo(q2);
	temp.copyTo(q3);

}
MatrixXd BagOfFeatures::gabor_computing()
{

	for (int i = 0; i < k; i++)
	{
		Mat filteredFourierTransform;
		double sig = 1, th = 0, lm = 1.0, gm = 0.02, ps = 0;
		Mat kernel = cv::getGaborKernel(Size(kernel_size, kernel_size), sig, th, lm, gm, ps);
		filter2D(fourier_transform, filteredFourierTransform, CV_32F, kernel);
	}

	/*
	idft(complexI, invDFT, DFT_SCALE | DFT_REAL_OUTPUT ); // Applying IDFT
	invDFT.convertTo(invDFTcvt, CV_8U);
	imshow("Output", invDFTcvt);

	//show the image
	imshow("Original Image", img); */



}

