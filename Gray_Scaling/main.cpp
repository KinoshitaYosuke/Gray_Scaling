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
#include "svm.h"

using namespace std;

class GT_Info {
public:
//	char name[1024];
	char *name;
	int x;
	int y;
	int width;
	int height;
	
	GT_Info() {
		x = y = -1;
		width = height = -1;
	}

};

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

	fopen_s(&origin_data, "C:/photo/predict-list-back.txt", "r");
	fopen_s(&train_data, "C:/photo/predict-list-back2.txt", "r");

	while (fgets(origin_name, 256, origin_data) != NULL) {
		string name_ori = origin_name;
		char new_origin_name[1024];
		for (int i = 0; i < name_ori.length() - 1; i++) {
			new_origin_name[i] = origin_name[i];
			new_origin_name[i + 1] = '\0';
		}
		for (int k = 0; k < 10; k++) {
			fgets(train_name, 256, train_data);
			string name_tra = train_name;
			char new_train_name[1024];
			for (int i = 0; i < name_tra.length() - 1; i++) {
				new_train_name[i] = train_name[i];
				new_train_name[i + 1] = '\0';
			}
			cv::Mat img = cv::imread(new_origin_name, 1);
			img = img(cv::Rect(rand() % (img.cols - 256), rand() % (img.rows - 256), 256, 256));
			cv::resize(img, img, cv::Size(), 128.0 / img.cols, 128.0 / img.rows);
			cv::imshow("", img);
			cvWaitKey(50);
			cv::imwrite(new_train_name, img);
		}
	}
	fclose(train_data);
	fclose(origin_data);
}

void RGB_to_Gray() {
	//テスト画像ファイル一覧メモ帳読み込み
	char test_name[1024], test_name2[1024];
	FILE *test_data, *test_data2;
	fopen_s(&test_data, "list_cd_2.txt", "r");

	while (fgets(test_name, 256, test_data) != NULL) {

		

		string name_tes = test_name;
		char new_test_name[1024];
		for (int i = 0; i < name_tes.length() - 1; i++) {
			new_test_name[i] = test_name[i];
			new_test_name[i + 1] = '\0';
		}

		char before_name[1024] = "CD_pos/";
		strcat_s(before_name, new_test_name);

	//	cout << before_name << endl;

		//画像の取り込み
		cv::Mat img = cv::imread(before_name, 1);	//検出する画像
		if (img.empty() == true) { 
			cout << before_name << endl;
			continue; 
		}
//		cv::imshow("", img);
//		cvWaitKey(10);

		char after_name[1024]="after/";
		strcat_s(after_name, new_test_name);
		if (img.channels() == 1) cv::imwrite(after_name, img);
		else {
			cv::Mat gray;
			cv::cvtColor(img, gray, CV_RGB2GRAY);
			cv::imwrite(after_name, gray);
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

void Normalize_INRIA() {
	//テスト画像ファイル一覧メモ帳読み込み
	char test_name[1024], test_name2[1024];
	FILE *test_data, *test_data2;
	fopen_s(&test_data, "INRIA-list.txt", "r");

	while (fgets(test_name, 256, test_data) != NULL) {

		cout << test_name << endl;

		string name_tes = test_name;
		char new_test_name[1024];
		for (int i = 0; i < name_tes.length() - 1; i++) {
			new_test_name[i] = test_name[i];
			new_test_name[i + 1] = '\0';
		}

		char after_name[1024];
		for (int i = 0; i < name_tes.length() - 1; i++) {
			after_name[i] = new_test_name[i];
			if (new_test_name[i] == '.') {
				after_name[i + 1] = 'b';
				after_name[i + 2] = 'm';
				after_name[i + 3] = 'p';
				after_name[i + 4] = '\0';
				break;
			}

		}

		//画像の取り込み
		cv::Mat img = cv::imread(new_test_name, 1);	//検出する画像
		img = img(cv::Rect(img.cols / 2 - 32 , img.rows / 2 - 64, 64, 128));
		cv::imshow("", img);
		cvWaitKey(10);
		if (img.channels() == 1) cv::imwrite(after_name, img);
		else {
			cv::Mat gray;
			cv::cvtColor(img, gray, CV_RGB2GRAY);
			cv::imwrite(after_name, gray);
		}

	}
	fclose(test_data);
}

void Gray_Test_INRIA() {
	//テスト画像ファイル一覧メモ帳読み込み
	char test_name[1024], test_name2[1024];
	FILE *test_data, *test_data2;
	fopen_s(&test_data, "INRIA-test-list.txt", "r");

	while (fgets(test_name, 256, test_data) != NULL) {

		cout << test_name << endl;

		string name_tes = test_name;
		char new_test_name[1024];
		for (int i = 0; i < name_tes.length() - 1; i++) {
			new_test_name[i] = test_name[i];
			new_test_name[i + 1] = '\0';
		}

		char after_name[1024];
		for (int i = 0; i < name_tes.length() - 1; i++) {
			after_name[i] = new_test_name[i];
			if (new_test_name[i] == '.') {
				after_name[i + 1] = 'b';
				after_name[i + 2] = 'm';
				after_name[i + 3] = 'p';
				after_name[i + 4] = '\0';
				break;
			}

		}

		//画像の取り込み
		cv::Mat img = cv::imread(new_test_name, 1);	//検出する画像
		
		cv::imshow("", img);
		cvWaitKey(10);
		if (img.cols == 640 && img.rows == 480) {
			if (img.channels() == 1) cv::imwrite(after_name, img);
			else {
				cv::Mat gray;
				cv::cvtColor(img, gray, CV_RGB2GRAY);
				cv::imwrite(after_name, gray);
			}
		}
	}
	fclose(test_data);
}

void check_aspect() {
	char train_name[1024], origin_name[1024];
	FILE *train_data, *origin_data;

	if (fopen_s(&origin_data, "C:/photo/train_data_from_demo/pre_experiment_data/Only_One_Pose/ex_experiment/Squat.txt", "r") != 0) {
		cout << 1 << endl;
		return;
	}
	if (fopen_s(&train_data, "C:/photo/train_data_from_demo/pre_experiment_data/Only_One_Pose/ex_experiment/Squat.txt", "r") != 0) {
		cout << 2 << endl;
		return;
	}

	int num = 1;
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
		char origin[1024] = "C:/photo/train_data_from_demo/pre_experiment_data/Only_One_Pose/ex_experiment/Squat_Only/";
		char train[1024] =  "C:/photo/train_data_from_demo/pre_experiment_data/Only_One_Pose/ex_experiment/Squat_Only/";
		strcat_s(origin, new_origin_name);
		strcat_s(train, new_train_name);

		cv::Mat img = cv::imread(origin, 1);
//		cout << (float) img.rows / img.cols << endl;
		cv::resize(img, img, cv::Size(), 128.0 / img.cols, 128.0 / img.rows);
		img = img(cv::Rect(28, 0, 72, 128));
		if (img.rows == 128 && img.cols == 72) {
			cout << num << ":" << new_origin_name << endl;
			num++;
			cv::imshow("", img);
			cvWaitKey(10);
			if (img.channels() != 1) { cv::cvtColor(img, img, CV_RGB2GRAY); }
			cv::imwrite(train, img);
		}
	}
	fclose(train_data);
	fclose(origin_data);
}

void Create_Binary_Image() {
	//テスト画像ファイル一覧メモ帳読み込み
	cout << 1234 << endl;
	char binary_name[1024] = "C:/photo/GT.txt";
	FILE *binary_data;
	if (fopen_s(&binary_data, binary_name, "r") != 0) {
		cout << "missing" << endl;
		return;
	}

	int num = 0;

	GT_Info GT;

	char str[1024];
	while (fgets(str, 256, binary_data)) {
		//	while ((fscanf_s(binary_data,"%[^,],%d,%d,%d,%d",str, &x,&y, &width, &height)) == 5) {
		char new_name[1024];
		string name = str;
		for (int i = 0; i < name.length() - 1; i++) {
			new_name[i] = str[i];
			new_name[i + 1] = '\0';
		}
		char *ctx;
		/* 1回目の呼出し */
		char *code = strtok_s(new_name, ", ", &ctx);
		char *xc = strtok_s(NULL, ",", &ctx);
		char *yc = strtok_s(NULL, ",", &ctx);
		char *widthc = strtok_s(NULL, ",", &ctx);
		char *heightc = strtok_s(NULL, ",", &ctx);
		GT.name = code;
		GT.x = atoi(xc);
		GT.y = atoi(yc);
		GT.width = atoi(widthc);
		GT.height = atoi(heightc);
		num++;

		cv::Mat res_bin = cv::Mat::zeros(480,640,CV_8UC3);
			for (int n = GT.y; n < GT.y + GT.height; n++) {
				for (int m = GT.x; m < GT.x + GT.width; m++) {
					res_bin.at<cv::Vec3b>(n, m) = cv::Vec3b(255, 255, 255);
				}
			}
			char save_name[1024] = "C:/photo/GT_binary/";
			strcat_s(save_name, GT.name);
			cv::imwrite(save_name, res_bin);
	}
	fclose(binary_data);
}

void Image_Binarization() {
	//テスト画像ファイル一覧メモ帳読み込み
	char test_name[1024];
	FILE *test_data;
	fopen_s(&test_data, "C:/photo/GT_binary_list.txt", "r");

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

		if (img.channels() != 1) cv::cvtColor(img,img,CV_RGB2GRAY);
		threshold(img, img, 20, 255, CV_THRESH_BINARY); 
		cv::imshow("", img);
		cvWaitKey(10);
		cv::imwrite(new_test_name, img);
	}
	fclose(test_data);
}

class Place {
public:
	int x;
	int y;
	int width;
	int height;
	float yudo;

	Place() {
		x = y = -1;
		width = height = -1;
		yudo = 0.0;
	}
};

cv::Mat draw_rectangle(cv::Mat ans_im, int x, int y, int width, int height, int r, int g, int b) {
	rectangle(ans_im, cvPoint(x, y), cvPoint(x + width, y + height), CV_RGB(r, g, b), 2);
	return ans_im;
}

void Result_MR_and_FPPI() {
	//変数宣言
	float miss_rate = 0;
	float fppi = 0;
	int num = 0;
	//テキストファイルのリスト読み込み
	char List_n[1024];
	FILE *List;
	if (fopen_s(&List, "c:/photo/text_list_4.txt", "r") != 0) {
		cout << "not found List file" << endl;
		return;
	}
	while (fgets(List_n, 256, List) != NULL) {
		string List_str = List_n;
		char List_name[1024];
		for (int i = 0; i < List_str.length() - 1; i++) {
			List_name[i] = List_n[i];
			List_name[i + 1] = '\0';
		}
		char GT_name[1024] = "c:/photo/GT_text/";
		strcat_s(GT_name, List_name);
		//GTファイル読み込み
		char GT_n[4][1024];
		FILE *GT;
		if (fopen_s(&GT, GT_name, "r") != 0) {
			cout << "not found GT file" << endl;
			return;
		}
		Place place_GT[10];
		int num_G = 0;
		while (fgets(GT_n[0], 256, GT) != NULL) {	//すべて読み込み，変数に格納
			fgets(GT_n[1], 256, GT);
			fgets(GT_n[2], 256, GT);
			fgets(GT_n[3], 256, GT);

			place_GT[num_G].x = atoi(GT_n[0]);
			place_GT[num_G].y = atoi(GT_n[1]);
			place_GT[num_G].width = atoi(GT_n[2]);
			place_GT[num_G].height = atoi(GT_n[3]);
			num_G++;
		}
		fclose(GT);
		char Result_name[1024] = "C:/photo/result_data_from_demo/2018_01_31_EP/result_data/";
		strcat_s(Result_name, List_name);
		//Resultファイル読み込み
		char Result_n[5][1024];
		FILE *Result;
		if (fopen_s(&Result, Result_name, "r") != 0) {
			cout << "not found Result file" << endl;
			return;
		}
		Place place_Result[1000];
		int num_R = 0;
		while (fgets(Result_n[0], 256, Result) != NULL) {	//すべて読み込み，変数に格納
			fgets(Result_n[1], 256, Result);
			fgets(Result_n[2], 256, Result);
			fgets(Result_n[3], 256, Result);
			fgets(Result_n[4], 256, Result);

			place_Result[num_R].yudo = atof(Result_n[0]);
			place_Result[num_R].x = atoi(Result_n[1]);
			place_Result[num_R].y = atoi(Result_n[2]);
			place_Result[num_R].width = atoi(Result_n[3]);
			place_Result[num_R].height = atoi(Result_n[4]);
			num_R++;
		}
		fclose(Result);
		char Img_n[1024];
		for (int i = 0; i < 256; i++) {
			if (List_name[i] == 't' && List_name[i+1]=='x') {
					Img_n[i] = 'b';
					Img_n[i + 1] = 'm';
					Img_n[i + 2] = 'p';
					Img_n[i + 3] = '\0';
					break;
			}
			Img_n[i] = List_name[i];
		}
		char Img_name[1024]="C:/photo/test_data_from_demo/test_data/";
		strcat_s(Img_name, Img_n);
		cout << Img_name << endl;
	//	cout << num_G << endl;
		cv::Mat img = cv::imread(Img_name, 1);

		for (int i = 0; i < num_G; i++) {
			img = draw_rectangle(img, place_GT[i].x, place_GT[i].y, place_GT[i].width, place_GT[i].height, 0, 0, 255);
		}
		for (int i = 0; i < num_R; i++) {
			if(place_Result[i].yudo>=0.921)
			img = draw_rectangle(img, place_Result[i].x, place_Result[i].y, place_Result[i].width, place_Result[i].height, 255, 0, 0);
		}
		cv::imshow("", img);
		cvWaitKey(0);
	}
	
	fclose(List);
}

void Result_MR_and_FPPI_2() {
	//変数宣言
	float miss_rate = 0;
	float fppi = 0;
	int num = 0;
	//テキストファイルのリスト読み込み
	char List_n[1024];
	FILE *List;
	if (fopen_s(&List, "c:/photo/text_list_4.txt", "r") != 0) {
		cout << "not found List file" << endl;
		return;
	}

	int file_num = 0;
	while (fgets(List_n, 256, List) != NULL) {
		file_num++;

		string List_str = List_n;
		char List_name[1024];
		for (int i = 0; i < List_str.length() - 1; i++) {
			List_name[i] = List_n[i];
			List_name[i + 1] = '\0';
		}
		char GT_name[1024] = "c:/photo/GT_text/";
		strcat_s(GT_name, List_name);
		//GTファイル読み込み
		char GT_n[4][1024];
		FILE *GT;
		if (fopen_s(&GT, GT_name, "r") != 0) {
			cout << "not found GT file" << endl;
			return;
		}
		Place place_GT[10];
		int num_G = 0;
		while (fgets(GT_n[0], 256, GT) != NULL) {	//すべて読み込み，変数に格納
			fgets(GT_n[1], 256, GT);
			fgets(GT_n[2], 256, GT);
			fgets(GT_n[3], 256, GT);

			place_GT[num_G].x = atoi(GT_n[0]);
			place_GT[num_G].y = atoi(GT_n[1]);
			place_GT[num_G].width = atoi(GT_n[2]);
			place_GT[num_G].height = atoi(GT_n[3]);
			num_G++;
		}
		fclose(GT);
		char Result_name[1024] = "C:/photo/result_data_from_demo/2018_01_15_AP/save_data/0.5_IoU0.3/";
		strcat_s(Result_name, List_name);
		//Resultファイル読み込み
		char Result_n[10][1024];
		FILE *Result;
		if (fopen_s(&Result, Result_name, "r") != 0) {
			cout << "not found Result file" << endl;
			return;
		}
		Place place_Result[2][1000];
		int num_R = 0;
		while (fgets(Result_n[0], 256, Result) != NULL) {	//すべて読み込み，変数に格納
			fgets(Result_n[1], 256, Result);
			fgets(Result_n[2], 256, Result);
			fgets(Result_n[3], 256, Result);
			fgets(Result_n[4], 256, Result);

			place_Result[0][num_R].yudo = atof(Result_n[0]);
			place_Result[0][num_R].x = atoi(Result_n[1]);
			place_Result[0][num_R].y = atoi(Result_n[2]);
			place_Result[0][num_R].width = atoi(Result_n[3]);
			place_Result[0][num_R].height = atoi(Result_n[4]);

			fgets(Result_n[5], 256, Result);
			fgets(Result_n[6], 256, Result);
			fgets(Result_n[7], 256, Result);
			fgets(Result_n[8], 256, Result);
			fgets(Result_n[9], 256, Result);

			place_Result[1][num_R].yudo = atof(Result_n[5]);
			place_Result[1][num_R].x = atoi(Result_n[6]);
			place_Result[1][num_R].y = atoi(Result_n[7]);
			place_Result[1][num_R].width = atoi(Result_n[8]);
			place_Result[1][num_R].height = atoi(Result_n[9]);

			num_R++;
		}
		fclose(Result);
		char Img_n[1024];
		for (int i = 0; i < 256; i++) {
			if (List_name[i] == 't' && List_name[i + 1] == 'x') {
				Img_n[i] = 'b';
				Img_n[i + 1] = 'm';
				Img_n[i + 2] = 'p';
				Img_n[i + 3] = '\0';
				break;
			}
			Img_n[i] = List_name[i];
		}
		char Img_name[1024] = "C:/photo/test_data_from_demo/test_data/";
		strcat_s(Img_name, Img_n);
		cout << Img_name << endl;
	//	cout << num_G << endl;
		cv::Mat img = cv::imread(Img_name, 1);

		for (int i = 0; i < num_G; i++) {
			img = draw_rectangle(img, place_GT[i].x, place_GT[i].y, place_GT[i].width, place_GT[i].height, 0, 0, 255);
		}
		for (int i = 0; i < num_R; i++) {
			if (place_Result[1][i].yudo >= 0.9)
				img = draw_rectangle(img, place_Result[0][i].x, place_Result[0][i].y, place_Result[0][i].width, place_Result[0][i].height, 255, 0, 0);
		}
		for (int i = 0; i < num_R; i++) {
			if (place_Result[1][i].yudo >= 0.9) {
				img = draw_rectangle(img, place_Result[1][i].x, place_Result[1][i].y, place_Result[1][i].width, place_Result[1][i].height, 0, 255, 0);
			}
		}
		cv::imshow("", img);
		cvWaitKey(0);
	}

	fclose(List);
}

int main(int argc, char** argv) {
//	Create_Binary_Image();

//	check_aspect();
	
//	RGB_to_Gray();

//	Normalize_One_Pose();

//	Normalize_INRIA();

//	Gray_Test_INRIA();

//	check();

//	test_data();

//	copy_data();
	
//	Image_Binarization();

	Result_MR_and_FPPI();

	return 0;
}
