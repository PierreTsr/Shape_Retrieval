# Shape_Retrieval
sketch-based shape retrieval project

## Prerequisites

The external C++ libraries needed are:
 1. OpenCV
 2. Boost
 3. OpenGL
 4. PythonLibs

You also need to download the igl libray.
Finally your active Python environment needs VTK, numpy, sklearn, and opencv.

## Usage

clone the repository using git, and build it with CMake
```
git clone https://github.com/PierreTsr/Shape_Retrieval.git
cd Shape_Retrieval/
mkdir build
cd build/
cmake ../
make
```
The project needs to be cloned next to the igl library to work. The Princeton Shapes dataset must be pasted next to the project too. 

The first step is to compute the 2D renders of the model using 
```
python ../OccludingContours/generateDataset.py
```
Then running `./ex_bin` will try to generate the histograms of a part of the dataset, load them, and display a window to draw in. The closest views' ID will be returned in the console.

## Warning

Many path are hard-coded in pre-compilator variables and need to be respected for the program to work.