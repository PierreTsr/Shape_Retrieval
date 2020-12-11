#include <iostream>
#include <chrono>
#include <set>
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
map<tuple<int,int>, View> dataset;

void setup()
{
	Histogram::vocabulary.setVocabFromFile("../backup", 2500);
	Histogram::vocabulary.setNViews(N_VIEWS * DATASET_SIZE);
	viewIndex = {};
	dataset = {};
}

void TestImageImport()
{
	Mat input = imread("../example/mimi.jpg", 0); //grayscale values between 0 adn 255

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

	fp = _Py_fopen(filename, "r");
	PyRun_SimpleFile(fp, filename);


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

tuple<int, int> findClosest(Histogram &hist)
{
	map<tuple<int, int>, double> bestScores;
	tuple<int, int> bests[10];
	int counter = 0, truc =0;
	double maxSim = -1;
	tuple<int,int> best;	
	for (auto i = dataset.begin(); i != dataset.end(); i++)
	{
		truc++;
		View v = i->second;
		double sim = hist.distance(v.Histo);
		if (sim>maxSim)
		{
			maxSim=sim;
			best = i->first;
		}
		if (counter < 10)
		{
			bests[counter] = i->first;
			bestScores.insert({i->first, sim});
			counter++;
		}
		else
		{
			double floor = bestScores.at(bests[9]);
			if (sim > floor)
			{
				bests[9] = i->first;
				bestScores.insert({i->first, sim});
			}
		}
		if(truc % 1000 == 0)
			cout << truc << endl;
		sort(bests, bests + counter, [=](tuple<int,int> a, tuple<int,int> b){
			return bestScores.at(a) > bestScores.at(b);
		});
	}
	cout << "Comparison done, processing results" << endl;
	map<int, int> modelScore;
	for (size_t i = 0; i < 10; i++)
	{
		if(modelScore.find(get<0>(bests[i])) == modelScore.end())
		{
			modelScore[get<0>(bests[i])] = 0;
		}
		modelScore[get<0>(bests[i])]++;
	}
	for (auto i = modelScore.begin(); i != modelScore.end(); i++)
	{
		cout << "le modèle " << i->first << " a un score de " << static_cast<double>(i->second)/10.0 <<endl;
	}

	for (size_t i = 0; i < 10; i++)
	{
		cout << "la vue " << get<0>(bests[i])<<"_"<< get<1>(bests[i])<< " a un score de " << bestScores.at(bests[i]) <<endl;
	}
	cout << get<0>(best) << " " << get<1>(best) << endl;
	return best;
}

int main()
{
	setup();
	computeAllHistogram();
  	loadAllHistograms(dataset);
	Py_Initialize();
	int inp = 1;
	while(inp)
 	{
		draw();
		Mat input = imread("../example/input.jpg", 0); //grayscale
		View init = View(input);		
		findClosest(init.Histo);
		//computeAllHistogram();
		cin >> inp;
	}
	Py_Finalize();
	return 0;
}
