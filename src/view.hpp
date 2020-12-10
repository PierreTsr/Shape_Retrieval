//
// Created by tom on 09/12/2020.
//

#ifndef SHAPE_RETRIEVAL_SRC_VIEW_HPP_
#define SHAPE_RETRIEVAL_SRC_VIEW_HPP_

#include "BagOfFeatures.hpp"
#include "Histogram.hpp"

class view
{
 private :
	Mat Image;

 public :
	BagOfFeatures BoF;
	Histogram	Histo;
	Vocabulary vocab;

	view();
	view(Mat& _Image, Vocabulary& _vocab) ;

};

#endif //SHAPE_RETRIEVAL_SRC_VIEW_HPP_
