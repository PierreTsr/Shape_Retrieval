//
// Created by tom on 09/12/2020.
//

#include "View.hpp"

View::View(Mat& _Image)
{
    Image = _Image;
    BagOfFeatures BoF(Image);
    BoF.gabor_computing();
    Histo = Histogram(BoF.features);
}

View::View(int _model, int _view)
{
    model = _model;
    view = _view;
    stringstream path;
    path << DATASET_PATH << "/" << to_string(model / 100) << "/m" << to_string(model) << "/render/m" << to_string(model) << "_" << to_string(view) << ".png";
    Image = imread(path.str(), 0);
    BagOfFeatures BoF(Image);
    BoF.gabor_computing();
    Histo = Histogram(BoF.features);
}


//https://www.worldbestlearningcenter.com/tips/Cplusplus-directory-exists.htm
bool directory_exists(const char *dname){
    DIR *di=opendir(dname); //open the directory
    if(di)
    {
        closedir(di);
        return true;
    }  //can open=>return true
    else
    {
        closedir(di);
        return false;
    } //otherwise return false
}

void View::writeHistogram()
{
    stringstream dirPath;
    dirPath << DATASET_PATH << "/" << to_string(model / 100) << "/m" << to_string(model) << "/histogram";
    if (! directory_exists(dirPath.str().c_str()))
    {
        mkdir(dirPath.str().c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    }

    stringstream path;
    path << DATASET_PATH << "/" << to_string(model / 100) << "/m" << to_string(model) << "/histogram/m" << to_string(model) << "_" << to_string(view) << ".xy";
    Histo.writeToFile(path.str());
}

void View::indexize(InverseIndex &index)
{
    for (auto i = Histo.getWeigths().cbegin(); i != Histo.getWeigths().cend(); i++)
    {
        if(index.find(i->first) == index.cend())
        {
            index[i->first] = {};
        }
        index[i->first].push_back({model, view});
    }
}

void View::setID(int _model, int _view)
{
    model = _model;
    view = _view;
    stringstream path;
    path << DATASET_PATH << "/" << to_string(model / 100) << "/m" << to_string(model) << "/histogram/m" << to_string(model) << "_" << to_string(view) << ".xy";
    Histo = Histogram();
    Histo.setFromFile(path.str());
}
