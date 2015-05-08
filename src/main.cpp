#include <opencv2/opencv.hpp>
#include <bits/stdc++.h>
#include "../includes/splitter.h"
#include "../includes/ml.h"

using namespace std;
using namespace cv;

int main()
{
    Mat a, retA[100], p, retP[100];
    a = imread("images/a.png");
    p = imread("images/p.png");
    Mat TEST_DATA, TEST_ARRAY[100];
    TEST_DATA = imread("images/mix.png");
    multi_split(TEST_DATA, TEST_ARRAY);
    multi_split(a, retA);
    multi_split(p, retP);

    Mat doubleA, doubleP, testA(TEST_ARRAY[2]), testP(TEST_ARRAY[3]);
    doubleA = learn(retA);
    doubleP = learn(retP);

    double prodA = mlProd(doubleA, testA);
    double prodP = mlProd(doubleP, testA);
    cout << prodA << endl << endl;
    cout << prodP << endl << endl;
    return 0;
}
