#include <iostream>
#include "Histogram.hpp"
#include "BagOfFeatures.h"

using namespace std;
using namespace cv;

Vocabulary Histogram::vocabulary = Vocabulary();

void TestImageImport()
{
	Mat input = imread("../example/mimi.jpg", 0); //grayscale
	assert(input.rows != 0);
	cout << "unit  test : import image OK" << endl;

}

void TestFourierTransform()
{
	Mat input = imread("../example/mimi.jpg", 0); //grayscale
	BagOfFeatures BoF =BagOfFeatures(input,4,4);
	BoF.FourierTransform();
	assert(BoF.fourier_transform.rows != 0);
	cout << "unit  test : fourier_transform OK" << endl;

}

int main()
{
	TestImageImport();
	TestFourierTransform();
	return 0;
}