/*
 * This program implements the Canny Edge Detection on any image. 
 It uses hysteresis, double threshold (image1.ppm), and non-maximum suppression to generate three images. 
 *
 *  Created on: Dec 14, 2022
 *      Author: Vihaan Mathur
 */

#include <iostream>
#include <cmath>
#include <tgmath.h>
#include <math.h>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <utility>
#include <list>
#include <vector>
using namespace std;

int sizex = 0;
int sizey = 0;
int max_val = 0;
char *temp = new char[2];


int** BWconver(int **image){
	int** array;
	array = new int*[sizey];

	for(int i = 0; i < sizey; i++){
		array[i] = new int[sizex];
	}
	for (int i = 0; i < sizey; i++)
	{
		  for (int j = 0; j < sizex; j++)
		  {
			array[i][j] = 1;
		  }
	}
	int c = 0;
	for (int i = 0; i < sizey; i++)
		{
		  c = 0;
		  for (int j = 0; j < sizex*3; j+=3)
		  {
			  int intens = (image[i][j] + image[i][j+1] + image[i][j+2]) / 3;
			  array[i][c] = intens;
			  c++;
		  }
	}
//		for(int i = 0; i < sizex; i++){
//			for(int j = 0; j < sizey*3; j++){
//				cout << array[i][j] << " ";
//
//			}
//		}

	ofstream myfile;
	myfile.open ("imageg.ppm");
	myfile <<"P3  " << sizex << "  " << sizey << "  " << max_val << "\n";
	for (int i = 0; i < sizey; i++){
		  for (int j = 0; j < sizex; j++){
			myfile << array[i][j] << " " << array[i][j] << " " << array[i][j] << " ";
		  }
		myfile << "\n";
	}
	myfile.close();
	return array;

}


//void Sobelconver(int **image, int threshold){
//	int** gx;
//	gx = new int*[sizey];
//
//	for(int i = 0; i < sizey; i++){
//		gx[i] = new int[sizex];
//	}
//	for (int i = 0; i < sizey; i++)
//	{
//		  for (int j = 0; j < sizex; j++)
//		  {
//			gx[i][j] = 1;
//		  }
//	}
//	int** gy;
//	gy = new int*[sizey];
//
//	for(int i = 0; i < sizey; i++){
//		gy[i] = new int[sizex];
//	}
//	for (int i = 0; i < sizey; i++)
//	{
//		  for (int j = 0; j < sizex; j++)
//		  {
//			gy[i][j] = 1;
//		  }
//	}
//	for(int i = 0; i < sizey; i++){
//		for(int j = 0; j < sizex; j++){
//			if((i == 0) or (j == 0) or (i == sizey-1) or (j == sizex-1)){
//				continue;
//			}
//			else{
//				gx[i][j] = 1*image[i-1][j-1] + -1*image[i-1][j+1] + 2*image[i][j-1] + -2*image[i][j+1] + 1*image[i+1][j-1] + -1*image[i+1][j+1];
//				gy[i][j] = 1*image[i-1][j-1] + 1*image[i-1][j+1] + 2*image[i-1][j] + -2*image[i+1][j] + -1*image[i+1][j-1] + -1*image[i+1][j+1];
//			}
//		}
//	}
//
//	for(int i = 0; i < sizey; i++){
//		for(int j = 0; j < sizex; j++){
//			if((i == 0) or (j == 0) or (i == sizey-1) or (j == sizex-1)){
//				image[i][j] = 0;
//			}
//			else{
//				int sqrtv = sqrt(gx[i][j]*gx[i][j] + gy[i][j]*gy[i][j]);
//				//cout << sqrtv << endl;
//				if(sqrtv > threshold){
//					image[i][j] = 1;
//				}
//				else{
//					image[i][j] = 0;
//			}
//			}
//		}
//	}
//
//	ofstream myfile;
//	myfile.open ("imagem.ppm");
//	myfile <<"P3  " << sizex << "  " << sizey << " 1\n";
//	for (int i = 0; i < sizey; i++){
//		  for (int j = 0; j < sizex; j++){
//			myfile << image[i][j] << " " << image[i][j] << " " << image[i][j] << " ";
//		  }
//		myfile << "\n";
//	}
//	myfile.close();
//
//
//}

//void part1(){
//	ifstream poin;
//	poin.open("image.ppm");
//	int**image;
//	poin.read(temp, 2);
//	poin >> sizex >> sizey >> max_val;
//
//    image = new int*[sizey];
//
//	for(int i = 0; i < sizey; i++){
//			image[i] = new int[sizex*3];
//		}
//
//	for (int i = 0; i < sizey; i++)
//		{
//			  for (int j = 0; j < sizex*3; j++)
//			  {
//				image[i][j] = 1;
//			  }
//		}
//
//	for(int i = 0; i < sizey; i++){
//		for(int j = 0; j < sizex*3; j++){
//			poin >> image[i][j];
//
//		}
//	}
////	for(int i = 0; i < sizex; i++){
////		for(int j = 0; j < sizey*3; j++){
////			cout << image[i][j];
////
////		}
////	}
//
//		int** grayed;
//		grayed = new int*[sizey];
//		for(int i = 0; i < sizey; i++){
//				grayed[i] = new int[sizex];
//			}
//		for (int i = 0; i < sizey; i++)
//		{
//			  for (int j = 0; j < sizex; j++)
//			  {
//				grayed[i][j] = 1;
//			  }
//		}
//		grayed = BWconver(image);
//		Sobelconver(grayed, 200);
//}

int neighbors[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};


//in bounds function and an array with all 8 neighbors that you can go through

void hysteresis(int** image, int i, int j){
	if(image[i][j] == 0 or image[i][j] == 1 or image[i][j] == 3){
		return;
	}
	else{
		image[i][j] = 3;
		for(int x = 0; x < 8; x++){
			int n1 = neighbors[x][0];
			int n2 = neighbors[x][1];
			if(image[i+n1][j+n2] == 1){
				image[i+n1][j+n2] = 2;
			}
			hysteresis(image, i+n1, j+n2);

		}
	}


}

//void Sobeldouble(int **image, int threshold1,  int threshold2){
//	int** gx;
//	gx = new int*[sizey];
//
//	for(int i = 0; i < sizey; i++){
//		gx[i] = new int[sizex];
//	}
//	for (int i = 0; i < sizey; i++)
//	{
//		  for (int j = 0; j < sizex; j++)
//		  {
//			gx[i][j] = 1;
//		  }
//	}
//	int** gy;
//	gy = new int*[sizey];
//
//	for(int i = 0; i < sizey; i++){
//		gy[i] = new int[sizex];
//	}
//	for (int i = 0; i < sizey; i++)
//	{
//		  for (int j = 0; j < sizex; j++)
//		  {
//			gy[i][j] = 1;
//		  }
//	}
//	for(int i = 0; i < sizey; i++){
//		for(int j = 0; j < sizex; j++){
//			if((i == 0) or (j == 0) or (i == sizey-1) or (j == sizex-1)){
//				continue;
//			}
//			else{
//				gx[i][j] = 1*image[i-1][j-1] + -1*image[i-1][j+1] + 2*image[i][j-1] + -2*image[i][j+1] + 1*image[i+1][j-1] + -1*image[i+1][j+1];
//				gy[i][j] = 1*image[i-1][j-1] + 1*image[i-1][j+1] + 2*image[i-1][j] + -2*image[i+1][j] + -1*image[i+1][j-1] + -1*image[i+1][j+1];
//			}
//		}
//	}
//
//	for(int i = 0; i < sizey; i++){
//		for(int j = 0; j < sizex; j++){
//			if((i == 0) or (j == 0) or (i == sizey-1) or (j == sizex-1)){
//				image[i][j] = 0;
//			}
//			else{
//				int sqrtv = sqrt(gx[i][j]*gx[i][j] + gy[i][j]*gy[i][j]);
//				//cout << sqrtv << endl;
//				if(sqrtv >= threshold2){
//					image[i][j] = 2;
//				}
//				else if(sqrtv >= threshold1){
//					image[i][j] = 1;
//				}
//				else{
//					image[i][j] = 0;
//			}
//			}
//		}
//	}
//
//	for(int i = 0; i < sizey; i++){
//		for(int j = 0; j < sizex; j++){
//			if((i == 0) or (j == 0) or (i == sizey-1) or (j == sizex-1)){
//				image[i][j] = 0;
//			}
//			else{
//				hysteresis(image, i, j);
//			}
//		}
//	}
//
//	for(int i = 0; i < sizey; i++){
//		for(int j = 0; j < sizex; j++){
//			if((i == 0) or (j == 0) or (i == sizey-1) or (j == sizex-1)){
//				continue;
//			}
//			else if(image[i][j] == 3 or image[i][j] == 2){
//				image[i][j] = 1;
//			}
//			else if(image[i][j] == 1){
//				image[i][j] = 0;
//
//			}
//		}
//	}
//
//	ofstream myfile;
//	myfile.open ("image1.ppm");
//	myfile <<"P3  " << sizex << "  " << sizey << " 1\n";
//	for (int i = 0; i < sizey; i++){
//		  for (int j = 0; j < sizex; j++){
//			myfile << image[i][j] << " " << image[i][j] << " " << image[i][j] << " ";
//		  }
//		myfile << "\n";
//	}
//	myfile.close();
//}

//void part2(){
//	ifstream poin;
//	poin.open("image.ppm");
//	int**image;
//	poin.read(temp, 2);
//	poin >> sizex >> sizey >> max_val;
//
//    image = new int*[sizey];
//
//	for(int i = 0; i < sizey; i++){
//			image[i] = new int[sizex*3];
//		}
//
//	for (int i = 0; i < sizey; i++)
//		{
//			  for (int j = 0; j < sizex*3; j++)
//			  {
//				image[i][j] = 1;
//			  }
//		}
//
//	for(int i = 0; i < sizey; i++){
//		for(int j = 0; j < sizex*3; j++){
//			poin >> image[i][j];
//
//		}
//	}
////	for(int i = 0; i < sizex; i++){
////		for(int j = 0; j < sizey*3; j++){
////			cout << image[i][j];
////
////		}
////	}
//
//		int** grayed;
//		grayed = new int*[sizey];
//		for(int i = 0; i < sizey; i++){
//				grayed[i] = new int[sizex];
//			}
//		for (int i = 0; i < sizey; i++)
//		{
//			  for (int j = 0; j < sizex; j++)
//			  {
//				grayed[i][j] = 1;
//			  }
//		}
//		grayed = BWconver(image);
//		Sobeldouble(grayed, 100, 280);
//}

void MaximumSupp(int **image, int threshold1,  int threshold2){
	int** gx;
	gx = new int*[sizey];

	for(int i = 0; i < sizey; i++){
		gx[i] = new int[sizex];
	}
	for (int i = 0; i < sizey; i++)
	{
		  for (int j = 0; j < sizex; j++)
		  {
			gx[i][j] = 1;
		  }
	}
	int** gy;
	gy = new int*[sizey];

	for(int i = 0; i < sizey; i++){
		gy[i] = new int[sizex];
	}
	for (int i = 0; i < sizey; i++)
	{
		  for (int j = 0; j < sizex; j++)
		  {
			gy[i][j] = 1;
		  }
	}

	int** g;
	g = new int*[sizey];

	for(int i = 0; i < sizey; i++){
		g[i] = new int[sizex];
	}
	for (int i = 0; i < sizey; i++)
	{
		  for (int j = 0; j < sizex; j++)
		  {
			g[i][j] = 1;
		  }
	}
	for(int i = 0; i < sizey; i++){
		for(int j = 0; j < sizex; j++){
			if((i == 0) or (j == 0) or (i == sizey-1) or (j == sizex-1)){
				g[i][j] = 0;
				continue;
			}
			else{
				gx[i][j] = 1*image[i-1][j-1] + -1*image[i-1][j+1] + 2*image[i][j-1] + -2*image[i][j+1] + 1*image[i+1][j-1] + -1*image[i+1][j+1];
				gy[i][j] = 1*image[i-1][j-1] + 1*image[i-1][j+1] + 2*image[i-1][j] + -2*image[i+1][j] + -1*image[i+1][j-1] + -1*image[i+1][j+1];
				int sqrtv = sqrt(gx[i][j]*gx[i][j] + gy[i][j]*gy[i][j]);
				g[i][j] = sqrtv;

			}
		}
	}

	double** theta;
	theta = new double*[sizey];

	for(int i = 0; i < sizey; i++){
		theta[i] = new double[sizex];
	}
	for (int i = 0; i < sizey; i++)
	{
		  for (int j = 0; j < sizex; j++)
		  {
			theta[i][j] = 1;
		  }
	}

	double pixels[9] = {-180, -135, -90, -45, 0, 45, 90, 135, 180};

	for(int i = 0; i < sizey; i++){
		for(int j = 0; j < sizex; j++){
			if((i == 0) or (j == 0) or (i == sizey-1) or (j == sizex-1)){
				theta[i][j] = 0;
			}
			else{
				theta[i][j] = atan2(gy[i][j], gx[i][j]) * 180.0 / 3.14159265;
			}
		}
	}


	double min = 999999999999;

	double picked = 9090909;

	for(int i = 0; i < sizey; i++){
		for(int j = 0; j < sizex; j++){
			if((i == 0) or (j == 0) or (i == sizey-1) or (j == sizex-1)){
				continue;
			}
			for(int x = 0; x < 9; x++){
				if(abs(theta[i][j] - pixels[x]) < min){
					min = abs(theta[i][j] - pixels[x]);
					picked = pixels[x];
				}

			}
			theta[i][j] = picked;
			min = 99999999;
			picked = 9090909;
		}
	}

	double** nms;
	nms = new double*[sizey];

	for(int i = 0; i < sizey; i++){
		nms[i] = new double[sizex];
	}
	for (int i = 0; i < sizey; i++)
	{
		  for (int j = 0; j < sizex; j++)
		  {
			nms[i][j] = 1;
		  }
	}


	int anglesn[9][5] = {{0, 0, 1, 0, -1}, {180, 0, 1, 0, -1}, {-180, 0, 1, 0, -1}, {-45, -1, 1, 1, -1}, {90, 1, 0, -1, 0},  {-135, -1, -1, 1, 1},  {135, -1, 1, 1, -1},  {-90, 1, 0, -1, 0},  {45, -1, -1, 1, 1}};

	for(int i = 0; i < sizey; i++){
		for(int j = 0; j < sizex; j++){
			if((i == 0) or (j == 0) or (i == sizey-1) or (j == sizex-1)){
				nms[i][j] = 0;
				continue;
			}
			int angle = int(theta[i][j]);
			int temp = g[i][j];
			for(int x = 0; x < 9; x++){
				if(anglesn[x][0] == angle){
					if((temp >= g[i+anglesn[x][1]][j+anglesn[x][2]]) and (temp >= g[i+anglesn[x][3]][j+anglesn[x][4]])){
						nms[i][j] = 1;
					}
					else{
						nms[i][j] = 0;
					}

				}
				else{
					continue;
				}
			}
		}
	}



	ofstream my;
	my.open ("image2.ppm");
	my <<"P3  " << sizex << "  " << sizey << " 1\n";
	for (int i = 0; i < sizey; i++){
		  for (int j = 0; j < sizex; j++){
			my << nms[i][j] << " " << nms[i][j] << " " << nms[i][j] << " ";
		  }
		my << "\n";
	}
	my.close();


	for(int i = 0; i < sizey; i++){
		for(int j = 0; j < sizex; j++){
			if((i == 0) or (j == 0) or (i == sizey-1) or (j == sizex-1)){
				image[i][j] = 0;
			}
			else{
				//cout << sqrtv << endl;
				if(g[i][j] >= threshold2){
					image[i][j] = 2;
				}
				else if(g[i][j] >= threshold1){
					image[i][j] = 1;
				}
				else{
					image[i][j] = 0;
			}
			}
		}
	}

	for(int i = 0; i < sizey; i++){
		for(int j = 0; j < sizex; j++){
			if((i == 0) or (j == 0) or (i == sizey-1) or (j == sizex-1)){
				image[i][j] = 0;
			}
			else{
				hysteresis(image, i, j);
			}
		}
	}

	for(int i = 0; i < sizey; i++){
		for(int j = 0; j < sizex; j++){
			if((i == 0) or (j == 0) or (i == sizey-1) or (j == sizex-1)){
				continue;
			}
			else if(image[i][j] == 3 or image[i][j] == 2){
				image[i][j] = 1;
			}
			else if(image[i][j] == 1){
				image[i][j] = 0;

			}
		}
	}

	ofstream myfile;
	myfile.open ("image1.ppm");
	myfile <<"P3  " << sizex << "  " << sizey << " 1\n";
	for (int i = 0; i < sizey; i++){
		  for (int j = 0; j < sizex; j++){
			myfile << image[i][j] << " " << image[i][j] << " " << image[i][j] << " ";
		  }
		myfile << "\n";
	}
	myfile.close();


	for(int i = 0; i < sizey; i++){
		for(int j = 0; j < sizex; j++){
			if((i == 0) or (j == 0) or (i == sizey-1) or (j == sizex-1)){
				image[i][j] = 0;
			}
			else if(image[i][j] == 1 and nms[i][j] == 1){
				image[i][j] = 1;
			}
			else{
				image[i][j] = 0;

			}
		}
	}



	ofstream fifi;
	fifi.open ("imagef.ppm");
	fifi <<"P3  " << sizex << "  " << sizey << " 1\n";
	for (int i = 0; i < sizey; i++){
		  for (int j = 0; j < sizex; j++){
			fifi << image[i][j] << " " << image[i][j] << " " << image[i][j] << " ";
		  }
		fifi << "\n";
	}
	fifi.close();


}

void part3(){
	ifstream poin;
	poin.open("image.ppm");
	int**image;
	poin.read(temp, 2);
	poin >> sizex >> sizey >> max_val;

    image = new int*[sizey];

	for(int i = 0; i < sizey; i++){
			image[i] = new int[sizex*3];
		}

	for (int i = 0; i < sizey; i++)
		{
			  for (int j = 0; j < sizex*3; j++)
			  {
				image[i][j] = 1;
			  }
		}

	for(int i = 0; i < sizey; i++){
		for(int j = 0; j < sizex*3; j++){
			poin >> image[i][j];

		}
	}
//	for(int i = 0; i < sizex; i++){
//		for(int j = 0; j < sizey*3; j++){
//			cout << image[i][j];
//
//		}
//	}

		int** grayed;
		grayed = new int*[sizey];
		for(int i = 0; i < sizey; i++){
				grayed[i] = new int[sizex];
			}
		for (int i = 0; i < sizey; i++)
		{
			  for (int j = 0; j < sizex; j++)
			  {
				grayed[i][j] = 1;
			  }
		}
		grayed = BWconver(image);
		MaximumSupp(grayed, 100, 175);

}

int main() {
	//part1();
	part3();
	return 0;
}


