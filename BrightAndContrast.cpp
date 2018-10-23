#include "stdafx.h"
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include<iostream>
using namespace cv;
using namespace std;

static void ContrastAndBright(int, void*);

int ContrastValue;
int BrightValue;
Mat srcimg,dstimg;

int main() {

	double alpha = 0.5;
	srcimg = imread("F:\\images\\111.jpg");
	dstimg = Mat::zeros(srcimg.size(), srcimg.type());
	if (!(srcimg.data)) { cout << "我敲你吗" << endl; }

	ContrastValue = 80;
	BrightValue = 80;

	namedWindow("Result");
	namedWindow("Original");
	createTrackbar("Contrast", "Result", & ContrastValue, 300, ContrastAndBright);
	createTrackbar("Bright", "Result", &BrightValue, 300, ContrastAndBright);
	ContrastAndBright(ContrastValue, 0);
	ContrastAndBright(BrightValue, 0);

	waitKey(0);

}

static void ContrastAndBright(int, void *)
{

	//创建窗口
	namedWindow("Original", 1);

	//三个for循环，执行运算 g_dstImage(i,j) =a*g_srcImage(i,j) + b
	for (int y = 0; y < srcimg.rows; y++)
	{
		for (int x = 0; x < srcimg.cols; x++)
		{
			for (int c = 0; c < 3; c++)
			{
				dstimg.at<Vec3b>(y, x)[c] = saturate_cast<uchar>((ContrastValue*0.01)*srcimg.at<Vec3b>(y, x)[c]+BrightValue);
			}
		}
	}

	//显示图像
	imshow("Original", srcimg);
	imshow("Result", dstimg);
}
