#include <opencv2/opencv.hpp>
#include <bits/stdc++.h>
#include "../includes/splitter.h"

using namespace std;
using namespace cv;

int main()
{
    Mat img;
    img = imread("images/a.png");
    Mat* ret;
    ret = split(img);
    for(int i=0; ret[i].rows != 1; i++)
    {
        imshow("a", ret[i]);
        waitKey(0);
    }
    return 0;
}
