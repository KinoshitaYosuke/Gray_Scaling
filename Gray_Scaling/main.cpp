#include <stdio.h>
#include <iostream>
#include <math.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <opencv2/opencv.hpp>
#include <math.h>

using namespace std;

void check() {
	char train_name[1024], origin_name[1024];
	FILE *train_data, *origin_data;
	
	srand((unsigned)time(NULL));

	fopen_s(&origin_data, "C:/photo/orilie.txt", "r");

	while (fgets(origin_name, 256, origin_data) != NULL) {
		int flag = 0;
		fopen_s(&train_data, "C:/photo/FD_lie.txt", "r");
		
		string name_ori = origin_name;
		char new_origin_name[1024];
		for (int i = 0; i < name_ori.length() - 1; i++) {
			new_origin_name[i] = origin_name[i];
			new_origin_name[i + 1] = '\0';
		}
		

		while (fgets(train_name, 256, train_data) != NULL) {
			string name_tra = train_name;
			
			if (name_tra == name_ori) { flag = 1; break; }

		}
		fclose(train_data);
		if (flag == 0 && rand() % 5 == 0) {
//		if(flag==0){
			cout << new_origin_name << endl; 
		}
	}
	
	fclose(origin_data);
}

void test_data() {
	char test_name[1024];
	FILE *test_data;

	fopen_s(&test_data, "C:/photo/test_data.txt", "r");

	while (fgets(test_name, 256, test_data) != NULL) {
		
		string name_tes = test_name;
		char new_test_name[1024];
		for (int i = 0; i < name_tes.length() - 1; i++) {
			new_test_name[i] = test_name[i];
			new_test_name[i + 1] = '\0';
		}
		cout << new_test_name << endl;
		cv::Mat img = cv::imread(new_test_name, 1);
		cv::imshow("", img);
		cvWaitKey(50);
	}
}

void copy_data() {
	char train_name[1024], origin_name[1024];
	FILE *train_data, *origin_data;

	fopen_s(&origin_data, "C:/photo/test_data.txt", "r");
	fopen_s(&train_data, "C:/photo/test_data2.txt", "r");

	while (fgets(origin_name, 256, origin_data) != NULL && fgets(train_name, 256, train_data) != NULL) {
		string name_ori = origin_name;
		char new_origin_name[1024];
		for (int i = 0; i < name_ori.length() - 1; i++) {
			new_origin_name[i] = origin_name[i];
			new_origin_name[i + 1] = '\0';
		}
		string name_tra = train_name;
		char new_train_name[1024];
		for (int i = 0; i < name_tra.length() - 1; i++) {
			new_train_name[i] = train_name[i];
			new_train_name[i + 1] = '\0';
		}
		cv::Mat img = cv::imread(new_origin_name, 1);
		cv::imwrite(new_train_name, img);

	}
	fclose(train_data);
	fclose(origin_data);
}

void RGB_to_Gray() {
	//テスト画像ファイル一覧メモ帳読み込み
	char test_name[1024], test_name2[1024];
	FILE *test_data, *test_data2;
	fopen_s(&test_data, "C:/photo/train_data_from_demo/pre_experiment_data/Arbitrary_Poses/list_lie.txt", "r");

	while (fgets(test_name, 256, test_data) != NULL) {

		cout << test_name << endl;

		string name_tes = test_name;
		char new_test_name[1024];
		for (int i = 0; i < name_tes.length() - 1; i++) {
			new_test_name[i] = test_name[i];
			new_test_name[i + 1] = '\0';
		}


		//画像の取り込み
		cv::Mat img = cv::imread(new_test_name, 1);	//検出する画像
//		img = img(cv::Rect(0, img.rows / 4, img.cols, img.rows / 2));
//		cv::imshow("", img);
//		cvWaitKey(10);
		if (img.channels() == 1) cv::imwrite(new_test_name, img);
		else {
			cv::Mat gray;
			cv::cvtColor(img, gray, CV_RGB2GRAY);
			cv::imwrite(new_test_name, gray);
		}

	}
	fclose(test_data);
}

void Normalize_One_Pose() {
	//テスト画像ファイル一覧メモ帳読み込み
	char test_name[1024], test_name2[1024];
	FILE *test_data, *test_data2;
	fopen_s(&test_data, "C:/photo/train_data_from_demo/pre_experiment_data/Only_One_Pose/list_Squat_Only.txt", "r");

	while (fgets(test_name, 256, test_data) != NULL) {

		cout << test_name << endl;

		string name_tes = test_name;
		char new_test_name[1024];
		for (int i = 0; i < name_tes.length() - 1; i++) {
			new_test_name[i] = test_name[i];
			new_test_name[i + 1] = '\0';
		}


		//画像の取り込み
		cv::Mat img = cv::imread(new_test_name, 1);	//検出する画像
//		img = img(cv::Rect(img.cols / 4, 0, img.cols / 2, img.rows));
		cv::imshow("", img);
		cvWaitKey(10);
		if (img.channels() == 1) cv::imwrite(new_test_name, img);
		else {
			cv::Mat gray;
			cv::cvtColor(img, gray, CV_RGB2GRAY);
			cv::imwrite(new_test_name, gray);
		}

	}
	fclose(test_data);
}

int main(int argc, char** argv) {
	
	
//	RGB_to_Gray();

	Normalize_One_Pose();

//	check();

//	test_data();

//	copy_data();

	return 0;
}
