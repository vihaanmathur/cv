/*
 * The program uses the Bresenham Line Drawing Algorithm and Circle Drawing Algorithm 
 to draw circles, lines, and Euler lines across a white screen. 
 *
 *  Created on: Aug 29, 2022
 *      Author: Vihaan Mathur
 */

#include<iostream>
#include <fstream>
#include <cmath>
#include <tgmath.h>

using namespace std;

void illuminate(int **grid, int x, int y){
	if(x <800 and x >0 and y < 800 and y >0){
		grid[x][y] = 0;
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




int main()
{
	int x = 800;
	int y = 800;

	int**grid;

	grid = new int*[800];

	for(int i = 0; i < 800; i++){
		grid[i] = new int[800];
	}

	//int grid[200][200];
	int**ppm;

	ppm = new int*[800];

	for(int i = 0; i < 800; i++){
			ppm[i] = new int[2400];
		}

	for (int i = 0; i < x; i++)
	{
		  for (int j = 0; j < y; j++)
		  {
		    grid[i][j] = 1;
		  }
	}
	for (int i = 0; i < x; i++)
		{
			  for (int j = 0; j < y*3; j++)
			  {
			    ppm[i][j] = 1;
			  }
		}

	//random points triangle as well as calculating other stuff

	int r2 = ((double) rand() / (RAND_MAX));
	srand(time(NULL));
	double x1o = ((double) rand() / (RAND_MAX));
	double x2o = ((double) rand() / (RAND_MAX));
	double y1o = ((double) rand() / (RAND_MAX));
	double y2o = ((double) rand() / (RAND_MAX));
	double x3o = ((double) rand() / (RAND_MAX));
	double y3o = ((double) rand() / (RAND_MAX));

	double a = sqrt((pow((x2o-x1o), 2) + pow(y2o-y1o, 2)));
	double b = sqrt((pow((x3o-x1o), 2) + pow(y3o-y1o, 2)));
	double c = sqrt((pow((x3o-x2o), 2) + pow(y3o-y2o, 2)));
	double s = .5*(a+b+c);

	//incircle
	double r = sqrt(((s-a)*(s-b)*(s-c))/(s));
	double incx  = (a*x3o+b*x2o+c*x1o)/(a+b+c);
	double incy = (a*y3o+b*y2o+c*y1o)/(a+b+c);

	//circumcircle
	double bigr = (a*b*c)/(4.0*r*s);
	double midx1 = (x1o+x2o)/2;
	double midy1 = (y1o+y2o)/2;
	double slop1 = (-1)/((y2o-y1o)/(x2o-x1o));
	double yint1 = midy1 - slop1*midx1;
	double midx2 = (x1o+x3o)/2;
	double midy2 = (y1o+y3o)/2;
	double slop2 = (-1)/((y3o-y1o)/(x3o-x1o));
	double yint2 = midy2 - slop2*midx2;

	double circx = (yint2-yint1)/(slop1-slop2);
	double circy = slop1*circx + yint1;


	//orthocenter, 9 point circle

	//slopes are still perpindicular of two sides but intersect with opposite vertices, not midpoints
	double yint3 = y3o - slop1*x3o;
	double yint4 = y2o - slop2*x2o;

	double orthx = (yint4-yint3)/(slop1-slop2);
	double orthy = slop1*orthx + yint3;

	double niner = bigr/2;
	double ninx = (orthx+circx)/2;
	double niny = (orthy+circy)/2;

	//euler line calculations
	double eulslop = (orthy-circy)/(orthx-circx);
	double eulint = orthy - eulslop*orthx;
	double eulx1 = 0;
	double euly1 = eulslop*eulx1 + eulint;
	double eulx2 = 799;
	double euly2 = eulslop*eulx2 + eulint;


	//scaling up centers
	int x1 = round(x1o * 800);
	int x2 = round(x2o * 800);
	int y1 = round(y1o * 800);
	int y2 = round(y2o * 800);
	int x3 = round(x3o * 800);
	int y3 = round(y3o * 800);

	int arrX [4] = {x1, x2, x3, x1};

	int arrY [4] = {y1, y2, y3, y1};

	//int arrX [4] = {0, 500, 400, 0};

	//int arrY [4] = {0, 300, 200, 0};

	//bresenham_12(grid,0,0,500,300);

	//bresenham_12(grid, 500, 300, 400, 200);

	//bresenham_12(grid, 400, 200, 0, 0);

	for (int i = 0; i < 3; i++){
		int x1 = arrX[i];
		int y1 = arrY[i];
		int x2 = arrX[i+1];
		int y2 = arrY[i+1];
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

	//making incircle and circumcircle and nine point circle

	int arrcirc [9] = {(int) round(r * 800), (int) round(incx * 800),(int) round(incy * 800), (int) round(bigr * 800), (int) round(circx * 800), (int) round(circy * 800), (int) round(niner * 800), (int) round(ninx * 800), (int) round(niny * 800)};
	int count1 = 0;


	for(int i = 0; i < 3; i++){

		int radius = arrcirc[count1];
		int xc = arrcirc[count1+1];
		int yc = arrcirc[count1+2];
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
			illuminate(grid, xc+x, yc+yy);
			illuminate(grid, xc+x, yc-yy);
			illuminate(grid, xc-x, yc+yy);
			illuminate(grid, xc-x, yc-yy);
			illuminate(grid, xc+yy, yc+x);
			illuminate(grid, xc+yy, yc-x);
			illuminate(grid, xc-yy, yc+x);
			illuminate(grid, xc-yy, yc-x);

			y2_new -= (2 * x) + 3;
		}
		count1 += 3;

	}

	//making euler line
	int xx1 = round(eulx1 * 800);
	int yy1 =round(euly1 * 800);
	int xx2 = round(eulx2 * 800);
	int yy2 = round(euly2 * 800);
	int dx1 = abs(xx2 - xx1);
	int dy1 = abs(yy2 - yy1);
	if(dx1 == 0){
		bresenham_1112(grid, xx1, yy1, xx2, yy2);
	}
	if(dy1 == 0){
		bresenham_56(grid, xx1, yy1, xx2, yy2);
			}
	if(dx1 >= dy1) //driving axis x
	{
		if((xx2 > xx1 and yy2 > yy1) or (xx2 < xx1 and yy2 < yy1)){
			bresenham_12(grid, xx1, yy1, xx2, yy2);
		}
		else{
			bresenham_34(grid, xx1, yy1, xx2, yy2);
		}
	}
	else if(dy1 > dx1)//driving axis y
	{
		if((xx2 > xx1 and yy2 > yy1) or (xx2 < xx1 and yy2 < yy1)){
			bresenham_78(grid, xx1, yy1, xx2, yy2);

		}
		else{
			bresenham_910(grid, xx1, yy1, xx2, yy2);
			}

		}



	//creating ppm file
	int count = 0;
	for (int i = 0; i < x; i++)
		{
			  count = 0;
			  for (int j = 0; j < y*3; j+=3)
			  {
				  int val = grid[i][count];
				  ppm[i][j] = val;
				  ppm[i][j+1] = val;
				  ppm[i][j+2] = val;
				  count += 1;
			  }
	}

	ofstream myfile;
	myfile.open ("lines.ppm");
	myfile << "P3  800  800  1\n";
	for (int i = 0; i < x; i++){
		  for (int j = 0; j < y*3; j++){
		    myfile << ppm[i][j] << " ";
		  }
		myfile << "\n";
	}
	myfile.close();
	return 0;
}



