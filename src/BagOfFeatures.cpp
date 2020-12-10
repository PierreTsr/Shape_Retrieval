//
// Created by tom on 01/12/2020.
//
#include "BagOfFeatures.hpp"
#include <opencv2/opencv.hpp>

using namespace std;
using namespace Eigen;
using namespace cv;

BagOfFeatures::BagOfFeatures(Mat& _line_rendering)
{
	this->line_rendering = _line_rendering;  //line_rendering needs to be in grayscale
	this->features = MatrixXd::Zero(TILE_SIZE * TILE_SIZE * NB_ORIENTATION, 1024);

}
BagOfFeatures::~BagOfFeatures()
{
}

Mat BagOfFeatures::ApplyFiter(double theta, double sigma_x, double sigma_y, double omega)
{
	Mat filtered_line_rendering = Mat(line_rendering.size(), line_rendering.type());
	double sig = sigma_x;
	double lm = 2 * M_PI / omega;
	double gm = sig / sigma_y;
	double ps = M_PI / 2.0;
	Mat kernel1 = cv::getGaborKernel(cv::Size(GABOR_KERNEL_SIZE, GABOR_KERNEL_SIZE), sig, theta, lm, gm, ps, CV_64F);
	filter2D(line_rendering, filtered_line_rendering, CV_64F, kernel1);
	normalize(filtered_line_rendering, filtered_line_rendering, 255, 0);
	return (filtered_line_rendering);
}

void BagOfFeatures::gabor_computing()
{

	double sigma_x = 0.01 * line_rendering.cols;
	double sigma_y = sigma_x / 0.3;
	double omega = 0.13;
	features.resize(1024, NB_ORIENTATION * TILE_SIZE * TILE_SIZE);
#pragma omp parallel for
	for (int K = 0; K < NB_ORIENTATION; K++)
	{

		double theta = K * M_PI / NB_ORIENTATION; //in degrees
		Mat filtered_image = ApplyFiter(theta, sigma_x, sigma_y, omega);
		/*cv::Mat fg;
		filtered_image.convertTo(fg,CV_32F);
		fg = fg + 1;
		cv::log(fg,fg);
		cv::normalize(fg,fg,0,255,cv::NORM_MINMAX);
		cv::convertScaleAbs(fg,fg);
		cv::imshow("a",fg);
		waitKey(0);*/
		for (int i = 0; i < 32; i++)
		{
			for (int j = 0; j < 32; j++)
			{
				Point2d KeyPoints((int)ceil((i + 1) * filtered_image.cols / (32 + 1)), (int)ceil((j + 1) * filtered_image.rows / (32 + 1)));

				int left_col = (int)max(0.0, floor(KeyPoints.x - KERNEL_WIDTH / 2.0 * filtered_image.cols));
				int right_col = (int)min((double)filtered_image.cols, ceil(KeyPoints.x + KERNEL_WIDTH / 2.0 * filtered_image.cols));
				int top_row = (int)max(0.0, floor(KeyPoints.y - KERNEL_WIDTH / 2.0 * filtered_image.rows));
				int bottom_row = (int)min((double)filtered_image.rows, ceil(KeyPoints.y + KERNEL_WIDTH / 2.0 * filtered_image.rows));
				cv::Range rows(top_row, bottom_row);
				cv::Range cols(left_col, right_col);
				Mat portion_image = filtered_image(rows, cols);
				for (int s = 0; s < TILE_SIZE; s++)
				{
					for (int t = 0; t < TILE_SIZE; t++)
					{
						int t_left_col = (int)floor(s * portion_image.cols / TILE_SIZE);
						int t_right_col = (int)ceil((s + 1) * portion_image.cols / TILE_SIZE);
						int t_top_row = (int)floor(s * portion_image.rows / TILE_SIZE);
						int t_bottom_row = (int)ceil((s + 1) * portion_image.rows / TILE_SIZE);
						cv::Range t_rows(t_top_row, t_bottom_row);
						cv::Range t_cols(t_left_col, t_right_col);
						features(i + 32 * j, t + 4 * s + K * TILE_SIZE * TILE_SIZE) = mean(portion_image(t_rows, t_cols))[0];

					}

				}

			}
		}
	}

}