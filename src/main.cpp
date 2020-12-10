#include <iostream>
#include <chrono>
#include <stdio.h>
#include <Python.h>
#include "Histogram.hpp"
#include "BagOfFeatures.hpp"
#include "FeatureGenerator.hpp"
#include "VocabularyGenerator.hpp"
#include <chrono>
using namespace chrono;
using namespace std;
using namespace cv;

Vocabulary Histogram::vocabulary = Vocabulary();

void TestImageImport()
{
	Mat input = imread("../example/mimi.jpg", 0); //grayscale values between 0 adn 255
	assert(input.rows != 0);

	cout << "unit  test : import image OK" << endl;

}

void TestGaborfilteringTransform()
{
	Mat input = imread("../example/m3_15.png", 0); //grayscale
	BagOfFeatures BoF = BagOfFeatures(input);
	BoF.gabor_computing();
	imshow("input", input);
	waitKey(0);
}
void draw()
{
	char filename[] = "../src/test_draw.py";
	FILE* fp;

	Py_Initialize();

	fp = _Py_fopen(filename, "r");
	PyRun_SimpleFile(fp, filename);

	Py_Finalize();
}

int main()
{
	//TestGaborfilteringTransform();
	//draw();
	Mat input = imread("../example/input.jpg", 0); //grayscale
	BagOfFeatures BoF = BagOfFeatures(input);
	//BoF.gabor_computing();

	TestGaborfilteringTransform();

	//TODO
}
