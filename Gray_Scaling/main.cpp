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

int main(int argc, char** argv) {

	//テスト画像ファイル一覧メモ帳読み込み
	char test_name[1024],test_name2[1024];
	FILE *test_data,*test_data2;
	fopen_s(&test_data, "C:/photo/train_data_from_demo/pre_experiment_data/Only_One_Pose/CD_pos/list_Lie_Only.txt", "r");

	if (test_data == NULL) {
		cout << "error" << endl;
		return 0;
	}

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
		img= img(cv::Rect( 0, img.rows/4, img.cols, img.rows/2));
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
	return 0;
}
