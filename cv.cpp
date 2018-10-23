#include "stdafx.h"
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/face.hpp"
#include "opencv2/imgproc.hpp"
#include<iostream>
#include<fstream>
#include<sstream>

using namespace cv;
using namespace std;
using namespace cv::face;

static Mat norm_0_255(InputArray _src) {
	Mat src = _src.getMat();
	// Create and return normalized image:
	Mat dst;
	switch (src.channels()) {
	case 1:
		cv::normalize(_src, dst, 0, 255, NORM_MINMAX, CV_8UC1);
		break;
	case 3:
		cv::normalize(_src, dst, 0, 255, NORM_MINMAX, CV_8UC3);
		break;
	default:
		src.copyTo(dst);
		break;
	}
	return dst;
}
static void read_csv(const string& filename, vector<Mat>& images, vector<int>& labels, char separator = ';') {
	std::ifstream file(filename.c_str(), ifstream::in);
	if (!file) {
		string error_message = "No valid input file was given, please check the given filename.";
		CV_Error(Error::StsBadArg, error_message);
	}
	string line, path, classlabel;
	while (getline(file, line)) {
		stringstream liness(line);
		getline(liness, path, separator);
		getline(liness, classlabel);
		if (!path.empty() && !classlabel.empty()) {
			images.push_back(imread(path, 0));
			labels.push_back(atoi(classlabel.c_str()));
		}
	}
}

int main(int argc, const char *argv[]) {

	string output_folder = string("F:\\vc++ file\\eigenface");
	string fn_csv = string("F:\\orl_faces\\at.txt");
	string fn_haar = string("G:\\haarcascade_frontalface_alt_tree.xml");
	vector<Mat> images;
	vector<int> labels;

	try {
		read_csv(fn_csv, images, labels);
	}
	catch(cv::Exception& e){
		cerr << "Error opening file \"" << fn_csv << "\". Reason: " << e.msg << endl;
		exit(1);
	}
	if (images.size() <= 1) {
		string error_message = "This demo needs at least 2 images to work. Please add more images to your data set!";
		CV_Error(Error::StsError, error_message);
	}

	int img_height = images[0].cols;
	int img_width = images[0].rows;
	//Mat testsample = images[156];
	//int testlabel = labels[156];
	//images.pop_back();
	//labels.pop_back();
	//images.erase(images.begin() + 156);
	//labels.erase(labels.begin() + 156);

	Ptr<EigenFaceRecognizer> model = EigenFaceRecognizer::create();
	model->train(images, labels);

	CascadeClassifier cascade;
	cascade.load(fn_haar);
	VideoCapture cap(0);

	if (!cap.isOpened()) {
		cerr << "Capture Device can not be opened" << endl;
		return -1;
	}

	if (!cascade.load("G:\\haarcascade_frontalface_alt.xml"))  //需要将xml文档放在自己指定的路径下
	{
		cout << "Load haarcascade_alt.xml failed!" << endl;
		return 0;
	}

	Mat testsample,testgray;
	testsample = imread("F:\\orl_faces\\test.jpg");
	cvtColor(testsample, testgray, CV_BGR2GRAY);
	int predictlabel = model->predict(testgray);
	string result_message = format("Predict_label:%d", predictlabel);
	cout << result_message << endl;

	string textmessage;
	vector<Rect> faces;
	Mat frame;
	while (1) {
		cap >> frame;
		Mat original = frame.clone();
		Mat gray;
		cvtColor(original, gray, CV_BGR2GRAY);
		cascade.detectMultiScale(gray, faces);//识别图片中的人脸
		for (int i = 0; i < faces.size(); i++) {
			Rect face_i = faces[i];
			Mat face = gray(face_i);//选取指定区域Rect的face
			Mat face_resize;
			cv::resize(face, face_resize, Size(img_width, img_height), 1.0, 1.0, INTER_CUBIC);
			int predictionlabel = model->predict(face_resize);
			rectangle(original, face_i, Scalar(0, 0, 255));
			textmessage = format("ID = %d", predictionlabel);
			int pos_x = max(face_i.tl().x - 10, 0);
			int pos_y = max(face_i.tl().y - 10, 0);
			putText(original, textmessage, Point(pos_x, pos_y), FONT_HERSHEY_PLAIN, 1.0, CV_RGB(0, 255, 0), 2.0);
        }
		imshow("facial_recognition", original);
		char key = (char)waitKey(20);
		if (key == 97) {
			destroyAllWindows;
			break;
		}	
	}
	//int predictlabel = model->predict(testsample);
	//string result_message = format("Predict_label:%d/Actual_label:%d", predictlabel, testlabel);
	//cout << result_message << endl;
	//waitKey(0);
	//return 0;
}