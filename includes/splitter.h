#ifndef __SPLITTER_H__
#define __SPLITTER_H__

#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
bool isEmpty(int, Mat, int);
void multi_split(Mat A, Mat C[100]);


#endif
