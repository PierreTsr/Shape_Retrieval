#include <iostream>
#include "Histogram.hpp"
#include "BagOfFeatures.hpp"
#include "FeatureGenerator.hpp"
#include <chrono>
using namespace chrono;
using namespace std;
using namespace cv;

Vocabulary Histogram::vocabulary = Vocabulary();

void TestImageImport()
{
	Mat input = imread("../example/mimi.jpg", 0); //grayscale				values between 0 adn 255
	assert(input.rows != 0);

	cout << "unit  test : import image OK" << endl;

}

void TestGaborfilteringTransform()
{
	Mat input = imread("../example/test2.png", 0); //grayscale
	BagOfFeatures BoF = BagOfFeatures(input, 4, 5, 4, 0.5);

	high_resolution_clock::time_point t1 = high_resolution_clock::now();

	for (int i = 0; i < 100; i++)
	{
		cout << i << endl;
		BoF.gabor_computing();
	}
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	duration<double, std::milli> time_span = t2 - t1;
	std::cout << "It took me " << time_span.count()/100 << " milliseconds." << std::endl;
}
int main()
{
	computeDataset("/home/pierre/Documents/INF574/psb_v1/benchmark/db");
}
