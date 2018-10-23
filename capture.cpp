#include "stdafx.h"
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/face.hpp"
#include "opencv2/imgproc.hpp"
#include<iostream>
#include<fstream>
#include<sstream>
using namespace std;
using namespace cv;

int main() {
	VideoCapture cap(0);
	Mat frame;
	int i = 1;
	if (!cap.isOpened()) {
		cerr << "ÎÒÇÃÄãÂð" << endl;
	}
	while (1) {
		cap >> frame;
		Mat original = frame.clone();
		imshow("video", original);
		char key = (char)waitKey(20);
		string path = format("G:/s42/%d.jpg", i);
		if (key == 13) {
			imwrite(path, frame);
			i++;
		}
		if (key == 32|| i==11) {
			destroyAllWindows;
			return 0;
		}

	}
	
}
