#include <opencv2/opencv.hpp>
#include <bits/stdc++.h>

using namespace std;
using namespace cv;

bool isEmpty(int i, Mat A, int flag);
Mat trim(Mat);
Mat make_32_32(Mat);

Mat* split(Mat A)
{
    static Mat C[100];
    cvtColor(A, A, CV_BGR2GRAY);
    int i=0;
    while(i < A.rows && isEmpty(i, A, 0))
        i++;
    int top = i;
    while(i < A.rows && !isEmpty(i, A, 0))
        i++;
    int bottom = i;
    Mat roi(A, Rect(0, top, A.cols, bottom-top));
    A = roi.clone();

    int ctr = 0;
    for(int i=0; i<A.cols; i++)
    {
        while(i < A.cols-1 && isEmpty(i, A, 1))
            i++;
        int left = i;
        while(i < A.cols-1 && !isEmpty(i, A, 1))
            i++;    
        int right = i;
        if(right > left)
        {
            cout << left << " " << right << " " << A.rows << "Up" << "\n";
            Mat roi(A, Rect(left, 0, right-left, A.rows));
            roi = trim(roi);
            roi = make_32_32(roi);
            roi.copyTo(C[ctr++]);
        }
    }

    C[ctr] = Mat(1,1, CV_8UC1, Scalar(0,0,0));
    printf("%d\n", ctr);


    return C;
}

Mat make_32_32(Mat A)
{
    if(A.rows > A.cols)
    {
        Size size(A.cols * 32 / A.rows, 32);
        resize(A, A, size);
        Mat fin(32, 32, CV_8UC1, 255);
        Mat roi(fin, Rect((32-A.cols)/2, 0, A.cols, A.rows));
        A.copyTo(roi);
        return fin;
    }
    else
    {
        Size size(32, A.rows * 32 / A.cols);
        resize(A, A, size);
        Mat fin(32, 32, CV_8UC1, 255);
        Mat roi(fin, Rect(0, (32-A.rows)/2, A.cols, A.rows));
        A.copyTo(roi);
        return fin;
    }
}

Mat trim(Mat A)
{
    int i=0;
    while(i < A.rows && isEmpty(i, A, 0))
        i++;
    int top = i;
    i = A.rows-1;
    while(i > 0 && isEmpty(i, A, 0))
        i--;
    int bottom = i+1;
    Mat roi(A, Rect(0, top, A.cols, bottom-top));
    return roi;
    
}

bool isEmpty(int i, Mat A, int flag)
{
    if(flag)
    {
        cout << i << " " << A.rows << "\n";
        Mat roi(A, Rect(i, 0, 1, A.rows));
        return (A.rows == countNonZero(roi));
    }
    else
    {
        Mat roi(A, Rect(0, i, A.cols, 1));
        return (A.cols == countNonZero(roi));
    }
}
