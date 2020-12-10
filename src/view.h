//
// Created by tom on 09/12/2020.
//
#include "BagOfFeatures.h"
#include "Histogram.hpp"
#define N_VIEWS 102
#ifndef SHAPE_RETRIEVAL_SRC_VIEW_H_
#define SHAPE_RETRIEVAL_SRC_VIEW_H_

class view
{
 private :
	Mat Image[N_VIEWS];

 public :
	Histogram Histo[N_VIEWS];
	BagOfFeatures set_of_bags[N_VIEWS];
	Vocabulary vocab;

	view();
	view(Mat& _image, Vocabulary& _vocab) ;
	void CreateBoF();
	void CreateHisto();
};

#endif //SHAPE_RETRIEVAL_SRC_VIEW_H_
