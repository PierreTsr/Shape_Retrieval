#include "FeatureGenerator.hpp"

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


void computeFeatures(string srcPath)
{
    //build source and destination path
    vector<string> cutPath;
    boost::split(cutPath, srcPath, [](char c){return c == '/';});
    cutPath[cutPath.size()-2] = "features";
    stringstream dest;
    int ptIdx = cutPath[cutPath.size() -1].find_last_of('.');
    for (size_t i = 0; i < ptIdx; i++)
    {
        dest << cutPath[cutPath.size() - 1][i];
    }
    dest << ".ft";
    string destFile = dest.str();
    cutPath[cutPath.size() - 1] = destFile;
    string destPath = boost::join(cutPath, "/");
    cutPath.pop_back();
    string destDir = boost::join(cutPath, "/");
    
    //Compute Feature
    Mat input = imread("../example/test2.png", cv::IMREAD_GRAYSCALE); //grayscale
	BagOfFeatures BoF = BagOfFeatures(input, 4, 5, 4, 0.2);
    BoF.gabor_computing();

    //write data
    if (! directory_exists(destDir.c_str()))
    {
        mkdir(destDir.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    }
    ofstream destination;
    destination.open(destPath);
    for (size_t i = 0; i < BoF.features.rows(); i++)
    {
        destination << BoF.features.row(i) << endl;
    }
    destination.close();
}

void computeDataset(string datasetPath)
{
    array<string, 5> srcPath;
    srcPath[0] = datasetPath;
    double total = 1815;
    for (size_t i = 0; i < 19; i++)
    {   
        srcPath[1] = to_string(i);
        #pragma omp parallel for
        for (size_t j = 0; j < 100; j++)
        {
            if (100*1 + j == 762 || 10*i + j > total)
                continue;
            stringstream state;
            state << "Dataset " << 100 * (100*i + j) / total << "% complete" << endl;
            cout << state.str();
            stringstream dir;
            dir << "m" << to_string(100*i+j);
            srcPath[2] = dir.str();
            for (size_t k = 0; k < N_VIEWS; k++)
            {
                srcPath[3] = "render";
                stringstream imgName;
                imgName << "m" << to_string(100*i+j) << "_" << to_string(k) << ".png";
                srcPath[4] = imgName.str();
                string path = boost::join(srcPath, "/");
                computeFeatures(path);
            }
        }
    }
}