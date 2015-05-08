#include <opencv2/opencv.hpp>
#include <bits/stdc++.h>
using namespace std;
using namespace cv;

Mat learn(Mat *Arr)
{
    Mat sum_mat(32, 32, CV_8UC1, 1), decimal;
    for(int i=0; Arr[i].rows != 1; i++)
        sum_mat += Arr[i];
    sum_mat.convertTo(decimal, CV_64F);
    decimal /= 0.001*sum(decimal)[0];
    return decimal;
}


double mlProd(Mat decimal, Mat mask)
{
    mask.convertTo(mask, CV_64F);
    decimal = decimal.mul(mask);
    SparseMat sm(decimal);
    double prod = 1;
    SparseMatConstIterator_<double> it = sm.begin<double>(), it_end = sm.end<double>();
    for(; it != it_end; ++it)
        if(it.value<double>())
            prod *= it.value<double>();
    return prod;
}
