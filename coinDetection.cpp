/*
 * This program uses Canny Edge Detection and edge/gradient direction matrix to detect coins in an image. It then calculates the total
 money amount based on the radii of the respective detected coins. 
 *
 *  Created on: Feb 3, 2023
 *      Author: viditmathur
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

class Point {
	private:
		double x;
		double y;
	public:
		Point(){
			x = 0.99999;
			y = 0.99999;
		}
		Point(double xv, double yv){
			x = xv;
			y = yv;
		}
		Point(const Point& p1)
		    {
		        x = p1.x;
		        y = p1.y;
		    }
		~Point()
		  {
			  //cout<<"\n Destructor executed";
		  }
		double getx(){
			return x;
			}
		double gety(){
			return y;
		}


		void toString(){
			cout << "(" << std::setprecision(19) << x << "," << std::setprecision(19) << y << ")";
		}
};

class Circle {
private:
	Point center;
	double radius;
	double edges;
public:
	Circle(){
		center = Point();
		radius = 0.0;
		edges = 0.0;
	}
	Circle(Point c, double r, double e){
		center = c;
		radius = r;
		edges = e;
	}
	Circle(const Circle& p1)
	    {
			center = p1.center;
			radius = p1.radius;
			edges = p1.edges;
	    }
	~Circle()
	  {
		  //cout<<"\n Destructor executed";
	  }
	Point getcenter(){
		return center;
	}
	double getcenterx(){
		return center.getx();
	}

	double getcentery(){
		return center.gety();
	}

	double getradius(){
		return radius;
	}

	double getedges(){
		return edges;
	}

	void toString(){
		cout << "Circle with radius: " << radius << " and center: " << "(" << std::setprecision(19) << center.getx() << "," << std::setprecision(19) << center.gety() << ")";
	}

};

double distance(Point p1, Point p2){
	return sqrt((pow((p2.getx()-p1.getx()), 2) + pow((p2.gety()-p1.gety()), 2)));
}

void illuminate(int **grid, int x, int y){
	if(x < sizex and x > 0 and y < sizey and y > 0){
		grid[y][x] += 1;
	}

}

void bresenham_12(int **grid, int x1, int y1, int x2, int y2) {

	//if x2 < x1 --> switch

	if(x2 < x1){
		swap(x1, x2);
		swap(y1, y2);
	}

	int x = x2-x1; //delta x

	int y = y2-y1; //delta y

	int j = y1;

	int e = y - x;



	for (int i = x1; i<=x2-1; i++)
	{
		//cout << "(" << i << j << ")" << "\n";
		illuminate(grid, i, j);
		if (e >= 0){
			j++;
			e -= x;
		}
		e += y;
	}

}

void bresenham_34(int **grid, int x1, int y1, int x2, int y2) {

	//if x2 < x1 --> switch

	if(x2 < x1){
		swap(x1, x2);
		swap(y1, y2);
	}

	int x = x2-x1; //delta x

	int y = abs(y2-y1); //delta y

	int j = y1;

	int e = y - x;



	for (int i = x1; i<=x2-1; i++)
	{
		illuminate(grid, i, j);
		if (e >= 0){
			j--;
			e -= x;
		}
		e += y;
	}

}

void bresenham_56(int **grid, int x1, int y1, int x2, int y2) {

	//if x2 < x1 --> switch

	if(x2 < x1){
			swap(x1, x2);
			swap(y1, y2);
		}

	int j = y1;

	for (int i = x1; i<=x2-1; i++)
	{
		illuminate(grid, i, j);
		//grid[i][j] = 0;

	}

}

void bresenham_78(int **grid, int x1, int y1, int x2, int y2) {

	//if y2 < y1 --> switch
	if(y2 < y1){
					swap(x1, x2);
					swap(y1, y2);
				}


	int x = x2-x1; //delta x

	int y = y2-y1; //delta y

	int j = x1;

	int e = y - x;



	for (int i = y1; i<=y2-1; i++)
	{
		illuminate(grid, j, i);
		//grid[j][i] = 0;
		if (e >= 0){
			j++;
			e -= y;
		}
		e += x;
	}

}

void bresenham_910(int **grid, int x1, int y1, int x2, int y2) {

	//if y2 < y1 --> switch
	if(y2 < y1){
					swap(x1, x2);
					swap(y1, y2);
				}


	int x = abs(x2-x1); //delta x

	int y = y2-y1; //delta y

	int j = x1;

	int e = y - x;



	for (int i = y1; i<=y2-1; i++)
	{
		illuminate(grid, j, i);
		//grid[j][i] = 0;
		if (e >= 0){
			j--;
			e -= y;
		}
		e += x;
	}

}

void bresenham_1112(int **grid, int x1, int y1, int x2, int y2) {

	//if y2 < y1 --> switch
	if(y2 < y1){
				swap(x1, x2);
				swap(y1, y2);
			}

	int j = x1;

	for (int i = y1; i<=y2-1; i++)
	{
		illuminate(grid, j, i);
		//grid[j][i] = 0;

	}

}

void bresenham(int **grid, int xx,  int yy,int xxx, int yyy){
	int x1 = xx;
	int x2 = xxx;
	int y1 = yy;
	int y2 = yyy;
	int dx = abs(x2 - x1);
	int dy = abs(y2 - y1);
	if(dx == 0){
		bresenham_1112(grid, x1, y1, x2, y2);
	}
	if(dy == 0){
		bresenham_56(grid, x1, y1, x2, y2);
			}
	if(dx >= dy) //driving axis x
	{
		if((x2 > x1 and y2 > y1) or (x2 < x1 and y2 < y1)){
			bresenham_12(grid, x1, y1, x2, y2);
		}
		else{
			bresenham_34(grid, x1, y1, x2, y2);
		}
	}
	else if(dy > dx)//driving axis y
	{
		if((x2 > x1 and y2 > y1) or (x2 < x1 and y2 < y1)){
			bresenham_78(grid, x1, y1, x2, y2);

		}
		else{
			bresenham_910(grid, x1, y1, x2, y2);
			}

		}

}


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

int** precoin; //the image before voting
double** theta; //angle array
double** coinangles;

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

	coinangles = new double*[sizey];

	for(int i = 0; i < sizey; i++){
		coinangles[i] = new double[sizex];
	}
	for (int i = 0; i < sizey; i++)
	{
		  for (int j = 0; j < sizex; j++)
		  {
			coinangles[i][j] = theta[i][j];
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
				precoin[i][j] = 0;
			}
			else if(image[i][j] == 1 and nms[i][j] == 1){
				precoin[i][j] = 1;
			}
			else{
				precoin[i][j] = 0;

			}
		}
	}



	ofstream fifi;
	fifi.open ("imagef.ppm");
	fifi <<"P3  " << sizex << "  " << sizey << " 1\n";
	for (int i = 0; i < sizey; i++){
		  for (int j = 0; j < sizex; j++){
			fifi << precoin[i][j] << " " << precoin[i][j] << " " << precoin[i][j] << " ";
		  }
		fifi << "\n";
	}
	fifi.close();


}

void illuminatecolor(int **grid, int x, int y, int color){
	if(x < sizex and x > 0 and y < sizey and y > 0){
		grid[y][x] = color;
	}

}

void makecircle(int **grid, Point p1, double radius, int color){
	int xc = p1.getx();
	int yc = p1.gety();
	int xmax = (int) (radius * 0.70710678); // maximum x at radius/sqrt(2)
	int yy = radius;
	int yy2 = yy * yy;
	int ty = (2 * yy) - 1;
	int y2_new = yy2;
	for (int x = 0; x <= xmax; x++) {
		if ((yy2 - y2_new) >= ty)
		{
			yy2 -= ty;
			yy -= 1;
			ty -= 2;
		}
		if(color != 1){
			illuminatecolor(grid, xc+x, yc+yy, color);
			illuminatecolor(grid, xc+x, yc-yy, color);
			illuminatecolor(grid, xc-x, yc+yy, color);
			illuminatecolor(grid, xc-x, yc-yy, color);
			illuminatecolor(grid, xc+yy, yc+x, color);
			illuminatecolor(grid, xc+yy, yc-x, color);
			illuminatecolor(grid, xc-yy, yc+x, color);
			illuminatecolor(grid, xc-yy, yc-x, color);
		}
		else{
			illuminate(grid, xc+x, yc+yy);
			illuminate(grid, xc+x, yc-yy);
			illuminate(grid, xc-x, yc+yy);
			illuminate(grid, xc-x, yc-yy);
			illuminate(grid, xc+yy, yc+x);
			illuminate(grid, xc+yy, yc-x);
			illuminate(grid, xc-yy, yc+x);
			illuminate(grid, xc-yy, yc-x);
		}

		y2_new -= (2 * x) + 3;
	}
}

double checkcircle(int **grid, Point p1, double radius){

	int xc = p1.getx();
	int yc = p1.gety();
	int xmax = (int) (radius * 0.70710678); // maximum x at radius/sqrt(2)
	int yy = radius;
	int yy2 = yy * yy;
	int ty = (2 * yy) - 1;
	int y2_new = yy2;
	int total = 0;
	int edged = 0;
	for (int x = 0; x <= xmax; x++) {
		if ((yy2 - y2_new) >= ty)
		{
			yy2 -= ty;
			yy -= 1;
			ty -= 2;
		}

		int circles[8][2] = {{xc+x, yc+yy}, {xc+x, yc-yy}, {xc-x, yc+yy}, {xc-x, yc-yy}, {xc+yy, yc+x}, {xc+yy, yc-x}, {xc-yy, yc+x}, {xc-yy, yc-x}};
		for(int i = 0; i < 8; i++){
			int yval = circles[i][1];
			int xval = circles[i][0];
			if(xval < sizex and xval > 0 and yval < sizey and yval > 0 and grid[yval][xval] == 1){
				edged+=1;
			}
		}
		total+=8;
		y2_new -= (2 * x) + 3;
	}
	double fraction = ((double)edged/(double)total);
	return fraction;
}


void part3(){
	ifstream poin;
	poin.open("harder.ppm");
	int**image;
	poin.read(temp, 2);
	poin >> sizex >> sizey >> max_val;//sizex is column and size y is row

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
		int**finalone;

		finalone = new int*[sizey];

		for(int i = 0; i < sizey; i++){
				finalone[i] = new int[sizex*3];
			}

		for (int i = 0; i < sizey; i++)
			{
				  for (int j = 0; j < sizex*3; j++)
				  {
					finalone[i][j] = image[i][j];
				  }
			}

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

		precoin = new int*[sizey];

		for(int i = 0; i < sizey; i++){
			precoin[i] = new int[sizex];
		}
		for (int i = 0; i < sizey; i++)
		{
			  for (int j = 0; j < sizex; j++)
			  {
				precoin[i][j] = 1;
			  }
		}


		int** bresens;
		bresens = new int*[sizey];
		for(int i = 0; i < sizey; i++){
				bresens[i] = new int[sizex];
			}
		for (int i = 0; i < sizey; i++)
		{
			  for (int j = 0; j < sizex; j++)
			  {
				bresens[i][j] = 0;
			  }
		}
//
		int** gaus;
		gaus = new int*[sizey];
		for(int i = 0; i < sizey; i++){
				gaus[i] = new int[sizex];
			}
		for (int i = 0; i < sizey; i++)
		{
			  for (int j = 0; j < sizex; j++)
			  {
				gaus[i][j] = 0;
			  }
		}

		for (int i = 0; i < sizey; i++)
		{
			  for (int j = 0; j < sizex; j++)
			  {
					if((i == 0) or (j == 0) or (i == 1) or (j == 1)or (i == sizey-1) or (j == sizex-1) or (i == sizey-2) or (j == sizex-2)){
						gaus[i][j] = grayed[i][j];
					}
					else{
						gaus[i][j] = (36*grayed[i][j] + 24*grayed[i][j+1]+ 6*grayed[i][j+2] + 24*grayed[i][j-1] + 6*grayed[i][j-2]
						+ 24*grayed[i-1][j] + 16*grayed[i-1][j+1] + 16*grayed[i-1][j-1] + 4*grayed[i-1][j-2] + 4*grayed[i-1][j+2]
						+ 24*grayed[i+1][j] + 16*grayed[i+1][j+1] + 16*grayed[i+1][j-1] + 4*grayed[i+1][j-2] + 4*grayed[i+1][j+2]
						+ 6*grayed[i+2][j] + 4*grayed[i+2][j+1] + 4*grayed[i+2][j-1] + 1*grayed[i+2][j-2] + 1*grayed[i+2][j+2]
						+ 6*grayed[i-2][j] + 4*grayed[i-2][j+1] + 4*grayed[i-2][j-1] + 1*grayed[i-2][j-2] + 1*grayed[i-2][j+2])/256;
					}
			  }
		}


		//Do 5x5 gaussian blur to make image amazing
		MaximumSupp(gaus, 75, 130); //100 141
		for (int i = 0; i < sizey; i++){
			  for (int j = 0; j < sizex; j++){
				  if(precoin[i][j] == 1){
					  double angle = coinangles[i][j] * (3.14159265/180.0);
					  double slope = tan(angle);
					  double b = i - (slope * j);
					  int x1 = j+200;
					  int x2 = j-200;
					  int y1 = slope*x1 + b;
					  int y2 = slope*x2 + b;
					  bresenham(bresens, x1, y1, x2, y2);
				  }
			  }
		}
		int bresen_max = 0;
		for (int i = 0; i < sizey; i++)
				{
					  for (int j = 0; j < sizex; j++)
					  {
						if(bresens[i][j] > bresen_max){
							bresen_max = bresens[i][j];
						}
					  }
				}
		ofstream fi;
		fi.open ("imagev.ppm");
		fi <<"P3  " << sizex << "  " << sizey << " " << bresen_max << "\n";
		for (int i = 0; i < sizey; i++){
			  for (int j = 0; j < sizex; j++){
				fi << bresens[i][j] << " " << bresens[i][j] << " " << bresens[i][j] << " ";
			  }
			fi << "\n";
		}
		fi.close();

		for (int i = 0; i < sizey; i++){
			  for (int j = 0; j < sizex; j++){
				  if(bresens[i][j] > 69){ //29 for easy for harder, 69, for hardest: 88
					  makecircle(precoin, Point(j, i), 1, 2);
					  makecircle(precoin, Point(j, i), 2, 2);
					  makecircle(precoin, Point(j, i), 3, 2);
					  makecircle(precoin, Point(j, i), 4, 2);
				  }

			  }
		}
		ofstream filee;
		filee.open ("imageCC.ppm");
		filee <<"P3  " << sizex << "  " << sizey << " " << max_val << "\n";

		int c = 0;
		for (int i = 0; i < sizey; i++)
			{
			  c = 0;
			  for (int j = 0; j < sizex*3; j+=3)
			  {
				  if(precoin[i][c] == 2){
					  filee << 255 << " " << 0 << " " << 0 << " ";
					}
				  else{
					  filee << finalone[i][j] << " " << finalone[i][j+1] <<  " " << finalone[i][j+2] << " ";
				  }
				  c++;
			  }
			  filee << "\n";
		}
		filee.close();
//		//Below is part 2 stuff

		double minR = 75; // 75-130
		double maxR = 160;
		vector<Circle> possibleCircles;
		vector<Circle> actualCircles;

		for (int i = 0; i < sizey; i++)
		{
			  for (int j = 0; j < sizex; j++)
			  {
				 if(precoin[i][j] == 2){
					  for(int rr = minR; rr < maxR; rr++){
						  double ee = checkcircle(precoin, Point(j, i), rr);
						  if(ee > 0.2){ //0.2 for easy image
							  //cout << ee << "\n";
							  possibleCircles.push_back(Circle(Point(j, i), rr, ee));
						  }
					  }
			  }
		 }
		}


		for (int i = 0; i < possibleCircles.size(); i++){
			bool found = true;
			for(int j = 0; j < possibleCircles.size(); j++){
				if((distance(possibleCircles[i].getcenter(), possibleCircles[j].getcenter()) < 25) and (possibleCircles[j].getedges() > possibleCircles[i].getedges())){
					found = false;
				}
			}
			if(found == true){
				actualCircles.push_back(possibleCircles[i]);

			}

		}

		//cout << possibleCircles.size() << "\n";
		int** coinfi;
		coinfi = new int*[sizey];
		for(int i = 0; i < sizey; i++){
			coinfi[i] = new int[sizex];
			}
		for (int i = 0; i < sizey; i++)
		{
			  for (int j = 0; j < sizex; j++)
			  {
				  coinfi[i][j] = 0;
			  }
		}

		for (int i = 0; i < actualCircles.size(); i++){
		      makecircle(coinfi, actualCircles[i].getcenter(), 1, 2);
		      makecircle(coinfi, actualCircles[i].getcenter(), 2, 2);
		      makecircle(coinfi, actualCircles[i].getcenter(), 3, 2);
		      makecircle(coinfi, actualCircles[i].getcenter(), 4, 2);
		      makecircle(coinfi, actualCircles[i].getcenter(), 5, 2);
		      makecircle(coinfi, actualCircles[i].getcenter(), 6, 2);
		      makecircle(coinfi, actualCircles[i].getcenter(), 7, 2);
			  makecircle(coinfi, actualCircles[i].getcenter(), actualCircles[i].getradius(), 2);
			  makecircle(coinfi, actualCircles[i].getcenter(), actualCircles[i].getradius()+1.0, 2);
			  makecircle(coinfi, actualCircles[i].getcenter(), actualCircles[i].getradius()+2.0, 2);
			  makecircle(coinfi, actualCircles[i].getcenter(), actualCircles[i].getradius()+3.0, 2);
			  makecircle(coinfi, actualCircles[i].getcenter(), actualCircles[i].getradius()+4.0, 2);
		}

		ofstream ccs;
		ccs.open ("imageCircles.ppm");
		ccs <<"P3  " << sizex << "  " << sizey << " " << max_val << "\n";
		int count1 = 0;
		for (int i = 0; i < sizey; i++)
			{
			  count1 = 0;
			  for (int j = 0; j < sizex*3; j+=3)
			  {
				  if(coinfi[i][count1] == 2){
					  ccs << 255 << " " << 0 << " " << 0 << " ";
					}
				  else{
					  ccs << finalone[i][j] << " " << finalone[i][j+1] <<  " " << finalone[i][j+2] << " ";
				  }
				  count1++;
			  }
			  ccs << "\n";
		}
		ccs.close();

		//colors key below
		//1 = black
		//2 = red - penny
		//6 = blue - dime
		//4 = yellow - nickel
		//5 = purple - quarter
		//8 green - half dollar
		//7 pink - dollar
		//only pennys, nickels, and quarters
		int pennyC = 0;
		int nickelC = 0;
		int quarterC = 0;
		int dimeC = 0;
		int halfC = 0;
		int dollarC = 0;
	    int max = 0;
	    double pennyrad = 0;
		for (int i = 0; i < actualCircles.size(); i++) {
		  int mostc = 0;
		  for (int j = 0; j < actualCircles.size(); j++) {
			if (actualCircles[i].getradius() == actualCircles[j].getradius()) {
			  mostc++;
			}
		  }
		  if (mostc > max) {
			max = mostc;
			pennyrad = actualCircles[i].getradius();
		  }
		}

        double nickelr = 0.835/0.750;
        double pennyr = 1.0;
        double quarterr = 0.955/0.750;
        double dimer =  0.705/0.750;
        double halfr = 1.205/0.750;
        double dollarr = 1.043/0.750;


		for (int i = 0; i < actualCircles.size(); i++){
				  double num = actualCircles[i].getradius()/pennyrad;
				  string closest;
				  double mindist = 99999;
				  if(abs(num-pennyr) < mindist){
					  closest = "penny";
					  mindist = abs(num-pennyr);
				  }
				  if(abs(num-nickelr) < mindist){
					  closest = "nickel";
					  mindist = abs(num-nickelr);
				  }
				  if(abs(num-quarterr) < mindist){
					  closest = "quarter";
					  mindist = abs(num-quarterr);
				  }
				  if(abs(num-dimer) < mindist){
					  closest = "dime";
					  mindist = abs(num-dimer);
				  }
				  if(abs(num-halfr) < mindist){
					  closest = "half";
					  mindist = abs(num-halfr);
				  }
				  if(abs(num-dollarr) < mindist){
					  closest = "dollar";
					  mindist = abs(num-dollarr);
				  }

				  if(closest == "penny"){ //penny
					  pennyC++;
				  }
				  else if(closest == "nickel"){ //nickel
				  makecircle(coinfi, actualCircles[i].getcenter(), actualCircles[i].getradius(), 4);
				  makecircle(coinfi, actualCircles[i].getcenter(), actualCircles[i].getradius()+1.0, 4);
				  makecircle(coinfi, actualCircles[i].getcenter(), actualCircles[i].getradius()+2.0, 4);
				  makecircle(coinfi, actualCircles[i].getcenter(), actualCircles[i].getradius()+3.0, 4);
				  makecircle(coinfi, actualCircles[i].getcenter(), actualCircles[i].getradius()+4.0, 4);
				  nickelC++;
				  }
				  else if(closest == "quarter"){
					  makecircle(coinfi, actualCircles[i].getcenter(), actualCircles[i].getradius(), 5); //quarter
					  makecircle(coinfi, actualCircles[i].getcenter(), actualCircles[i].getradius()+1.0, 5);
					  makecircle(coinfi, actualCircles[i].getcenter(), actualCircles[i].getradius()+2.0, 5);
					  makecircle(coinfi, actualCircles[i].getcenter(), actualCircles[i].getradius()+3.0, 5);
					  makecircle(coinfi, actualCircles[i].getcenter(), actualCircles[i].getradius()+4.0, 5);
					  quarterC++;

				  }
				  else if(closest == "dime"){
					  makecircle(coinfi, actualCircles[i].getcenter(), actualCircles[i].getradius(), 6); //dime
					  makecircle(coinfi, actualCircles[i].getcenter(), actualCircles[i].getradius()+1.0, 6);
					  makecircle(coinfi, actualCircles[i].getcenter(), actualCircles[i].getradius()+2.0, 6);
					  makecircle(coinfi, actualCircles[i].getcenter(), actualCircles[i].getradius()+3.0, 6);
					  makecircle(coinfi, actualCircles[i].getcenter(), actualCircles[i].getradius()+4.0, 6);
					  dimeC++;

				  }
				  else if(closest == "dollar"){
					  makecircle(coinfi, actualCircles[i].getcenter(), actualCircles[i].getradius(), 7); //dollar
					  makecircle(coinfi, actualCircles[i].getcenter(), actualCircles[i].getradius()+1.0, 7);
					  makecircle(coinfi, actualCircles[i].getcenter(), actualCircles[i].getradius()+2.0, 7);
					  makecircle(coinfi, actualCircles[i].getcenter(), actualCircles[i].getradius()+3.0, 7);
					  makecircle(coinfi, actualCircles[i].getcenter(), actualCircles[i].getradius()+4.0, 7);
					  dollarC++;

				  }
				  else{
					  makecircle(coinfi, actualCircles[i].getcenter(), actualCircles[i].getradius(), 8); //half dollar
					  makecircle(coinfi, actualCircles[i].getcenter(), actualCircles[i].getradius()+1.0, 8);
					  makecircle(coinfi, actualCircles[i].getcenter(), actualCircles[i].getradius()+2.0, 8);
					  makecircle(coinfi, actualCircles[i].getcenter(), actualCircles[i].getradius()+3.0, 8);
					  makecircle(coinfi, actualCircles[i].getcenter(), actualCircles[i].getradius()+4.0, 8);
					  halfC++;

				  }
//			  if(actualCircles[i].getradius() > 75 and actualCircles[i].getradius() < 95){ //penny
//				  pennyC++;
//			  }
//			  else if(actualCircles[i].getradius() > 95 and actualCircles[i].getradius() < 105){ //nickel
//			  makecircle(coinfi, actualCircles[i].getcenter(), actualCircles[i].getradius(), 4);
//			  makecircle(coinfi, actualCircles[i].getcenter(), actualCircles[i].getradius()+1.0, 4);
//			  makecircle(coinfi, actualCircles[i].getcenter(), actualCircles[i].getradius()+2.0, 4);
//			  makecircle(coinfi, actualCircles[i].getcenter(), actualCircles[i].getradius()+3.0, 4);
//			  makecircle(coinfi, actualCircles[i].getcenter(), actualCircles[i].getradius()+4.0, 4);
//			  nickelC++;
//			  }
//			  else{
//				  makecircle(coinfi, actualCircles[i].getcenter(), actualCircles[i].getradius(), 5); //quarter
//				  makecircle(coinfi, actualCircles[i].getcenter(), actualCircles[i].getradius()+1.0, 5);
//				  makecircle(coinfi, actualCircles[i].getcenter(), actualCircles[i].getradius()+2.0, 5);
//				  makecircle(coinfi, actualCircles[i].getcenter(), actualCircles[i].getradius()+3.0, 5);
//				  makecircle(coinfi, actualCircles[i].getcenter(), actualCircles[i].getradius()+4.0, 5);
//				  quarterC++;
//          }
		}

		ofstream cc;
		cc.open ("imageCoins.ppm");
		cc <<"P3  " << sizex << "  " << sizey << " " << max_val << "\n";
		int count2 = 0;
		for (int i = 0; i < sizey; i++)
			{
			  count2 = 0;
			  for (int j = 0; j < sizex*3; j+=3)
			  {
				  if(coinfi[i][count2] == 2){
					  cc << 255 << " " << 0 << " " << 0 << " ";
					}
				  else if(coinfi[i][count2] == 4){
					  cc << 255 << " " << 255 << " " << 0 << " ";
					}
				  else if(coinfi[i][count2] == 5){
					  cc << 191 << " " << 64 << " " << 191 << " ";
					}
				  else if(coinfi[i][count2] == 6){ //dime
					  cc << 0 << " " << 0 << " " << 255 << " ";
					}
				  else if(coinfi[i][count2] == 7){ //dollar
					  cc << 255 << " " << 105 << " " << 180 << " ";
					}
				  else if(coinfi[i][count2] == 8){ //half dollar
					  cc << 0 << " " << 255 << " " << 127 << " ";
					}
				  else{
					  cc << finalone[i][j] << " " << finalone[i][j+1] <<  " " << finalone[i][j+2] << " ";
				  }
				  count2++;
			  }
			  cc << "\n";
		}
		cc.close();


		ofstream res;
		double totalsum = ((double)pennyC)*0.01 + ((double)nickelC)*0.05 + ((double)quarterC)*0.25 + ((double)dimeC)*0.1 + ((double)halfC)*0.5 + ((double)dollarC)*1;
		res.open ("results.txt");
		res <<"Summary of Coins:" <<  "\n";
		res << pennyC << " pennies" << "\n";
		res << nickelC << " nickels" << "\n";
		res << quarterC << " quarters" << "\n";
		res << dimeC << " dimes" << "\n";
		res << halfC << " half dollars" << "\n";
		res << dollarC << " dollar coins" << "\n";
		res << "Total sum: $" << totalsum;
		cout << "Summary of Coins:" <<  "\n";
		cout << pennyC << " pennies" << "\n";
		cout << nickelC << " nickels" << "\n";
		cout << quarterC << " quarters" << "\n";
		cout << dimeC << " dimes" << "\n";
		cout << halfC << " half dollars" << "\n";
		cout << dollarC << " dollar coins" << "\n";
		cout << "Total sum: $" << totalsum;
		res.close();




}

int main() {
	part3();
	return 0;
}


//OK so illuminate I do grid[y][x] and then in make circle I pass [x][y]
