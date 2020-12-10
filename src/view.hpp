//
// Created by tom on 09/12/2020.
//

#ifndef SHAPE_RETRIEVAL_SRC_VIEW_HPP_
#define SHAPE_RETRIEVAL_SRC_VIEW_HPP_

#include "BagOfFeatures.hpp"
#include "Histogram.hpp"
#define N_VIEWS 102

class view
{
 private :
	array<Mat,N_VIEWS> Image;

 public :
	Histogram Histo[N_VIEWS];
	BagOfFeatures set_of_bags[N_VIEWS];
	Vocabulary vocab;

	view();
	view(array<Mat,N_VIEWS>& _image, Vocabulary& _vocab) ;
	void CreateBoF();
	void CreateHisto();
};

#endif //SHAPE_RETRIEVAL_SRC_VIEW_HPP_
