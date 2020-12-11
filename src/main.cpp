#include <iostream>
#include <chrono>
#include <stdio.h>
#include <Python.h>
#include "Histogram.hpp"
#include "BagOfFeatures.hpp"
#include "FeatureGenerator.hpp"
#include "VocabularyGenerator.hpp"
#include "View.hpp"
#include "InverseIndex.hpp"
#include <chrono>

using namespace chrono;
using namespace std;
using namespace cv;

#define N_VIEWS 102
#define DATASET_SIZE 1813

Vocabulary Histogram::vocabulary = Vocabulary();
InverseIndex viewIndex;

void setup()
{
	Histogram::vocabulary.setVocabFromFile("../data", 2500);
	Histogram::vocabulary.setNViews(N_VIEWS * DATASET_SIZE);
	viewIndex = {};
}

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

void testAll()
{
	Mat input = imread("../example/m3_15.png", 0);
	Mat input2 = imread("../example/m201_74.png", 0);
	View first = View(input);
	View second = View(input2);
	double d = first.Histo.distance(second.Histo);
	std::map<int, double> weights = first.Histo.weights;	
	cout << "les 2 images sont à une distance de " << d << endl;
}

int main()
{
	setup();
	indexDataset(viewIndex);
	return 0;
}
