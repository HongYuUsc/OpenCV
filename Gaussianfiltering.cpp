#include"stdafx.h"
#include"opencv2/core.hpp"
#include"opencv2/highgui.hpp"
#include"opencv2/imgproc.hpp"
#include<iostream>
using namespace cv;
using namespace std;

int GaussianCoreValue1 = 3;
int GaussianCoreValue2 = 3;
Mat src, out;

static void GaussianFilter(int, void*);

int main(){
	src = imread("F:\\images\\yui.jpg");

	//start now
	namedWindow("Yui", WINDOW_NORMAL);
	namedWindow("Result", WINDOW_NORMAL);
	imshow("Yui", src);
	createTrackbar("ÄÚºË¿í", "Result", &GaussianCoreValue1, 50, GaussianFilter);
	createTrackbar("ÄÚºË³¤", "Result", &GaussianCoreValue2, 50, GaussianFilter);
	//
	waitKey(0);
}

static void GaussianFilter(int, void*) {
	GaussianBlur(src, out, Size(GaussianCoreValue1*2+1, GaussianCoreValue2 * 2 + 1), 0, 0);
	imshow("Result", out);
}