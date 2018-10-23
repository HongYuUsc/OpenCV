#include "stdafx.h"
#include<opencv2\opencv.hpp>
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

int main() {
	CascadeClassifier face_cascade;
	String text_face = string("G:\\haarcascade_frontalface_alt.xml");
	if (!face_cascade.load(text_face)) {
		cout << "ÎÒÇÃÄãÂð" << endl;
	}
	Mat frame;
	frame = imread("G:/s42/5.jpg");

	Mat gray_color;
	cvtColor(frame, gray_color, COLOR_BGR2GRAY);

	vector<Rect> faces;
	face_cascade.detectMultiScale(gray_color, faces);

	for (int j = 0; j < faces.size(); j++) {
		Rect face_j = faces[j];
		rectangle(frame, face_j, CV_RGB(255, 0, 0));
		Mat faceROI = frame(face_j);
		Mat myface;
		if (faceROI.cols > 100) {
			resize(faceROI, myface, Size(92, 112));
			cvtColor(myface, myface, COLOR_BGR2GRAY);
			String myphoto = format("F:\\orl_faces\\test.jpg");
			imwrite(myphoto, myface);
			imshow("ii", myface);
		}
	}
	waitKey(0);
}



