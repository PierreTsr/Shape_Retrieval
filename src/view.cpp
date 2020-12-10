//
// Created by tom on 09/12/2020.
//

#include "view.hpp"

view::view(Mat& _Image, Vocabulary& _vocab) : vocab(_vocab), Image(_Image), BoF(Image), Histo(BoF.features)
{
}
