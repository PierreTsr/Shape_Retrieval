//
// Created by tom on 09/12/2020.
//

#ifndef SHAPE_RETRIEVAL_SRC_VIEW_HPP_
#define SHAPE_RETRIEVAL_SRC_VIEW_HPP_

#include <dirent.h>
#include <sys/stat.h>
#include "BagOfFeatures.hpp"
#include "Histogram.hpp"
#include "InverseIndex.hpp"

class View
{
 private :
	Mat Image;


 public :
 	int model;
	int view;
	Histogram	Histo;

	View() = default;
	View(int _model, int _view);
	View(Mat& _Image);

	void writeHistogram();
	void writeHistogram(ofstream &file);
	void setID(int _model, int _view);
	void indexize(InverseIndex &index);

};

#endif //SHAPE_RETRIEVAL_SRC_VIEW_HPP_

#ifndef DATASET_PATH
#define DATASET_PATH "/home/pierre/Documents/INF574/psb_v1/benchmark/db"
#endif