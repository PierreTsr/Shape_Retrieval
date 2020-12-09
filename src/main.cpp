#include <iostream>
#include "Histogram.hpp"
#include "BagOfFeatures.h"

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
	Mat input = imread("../example/mimi.jpg", 0); //grayscale
	BagOfFeatures BoF = BagOfFeatures(input, 4, 5,4,0.5);
	BoF.gabor_computing();
}

int main()
{
	TestGaborfilteringTransform();
	return 0;
}