#include <opencv2/opencv.hpp>
#include <bits/stdc++.h>
#include <armadillo>
#include "../includes/splitter.h"

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
    Mat sumA(32, 32, CV_8UC1, 1);
    Mat sumP(32, 32, CV_8UC1, 1);
    Mat doubleA, doubleP, testA(TEST_ARRAY[2]), testP(TEST_ARRAY[3]);
    double maxA, maxP;
    for(int i=0; retA[i].rows != 1; i++)
        sumA += retA[i];
    for(int i=0; retP[i].rows != 1; i++)
        sumP += retP[i];
    sumA.convertTo(doubleA, CV_64F);
    sumP.convertTo(doubleP, CV_64F);
    maxA = sum(doubleA)[0];
    maxP = sum(doubleP)[0];
    doubleA /= 0.002*maxA;
    doubleP /= 0.002*maxP;
    testA.convertTo(testA, CV_64F);
    testP.convertTo(testP, CV_64F);
    doubleA = doubleA.mul(testP);
    doubleP = doubleP.mul(testP);
    SparseMat smA(doubleA), smP(doubleP);
    double prodA = 1, prodP = 1;
    SparseMatConstIterator_<double> itA = smA.begin<double>(), itA_end = smA.end<double>();
    SparseMatConstIterator_<double> itP = smP.begin<double>(), itP_end = smP.end<double>();
    for(; itA != itA_end; ++itA)
    {
        if(itA.value<double>())
            prodA *= itA.value<double>();
    }
    for(; itP != itP_end; ++itP)
    {
        if(itP.value<double>())
            prodP *= itP.value<double>();
    }
    cout << doubleA << endl << prodA << endl << endl;
    cout << doubleP << endl << prodP << endl << endl;
    return 0;
}
