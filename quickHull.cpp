/*
 * This program uses a Graham Scan to implement the QuickHull Algorithm and draw a Convex Hull on a ppm image. 
 *
 *  Created on: Nov 30, 2022
 *      Author: Vihaan Mathur
 */

#include <iostream>
#include <cmath>
#include <tgmath.h>
#include <math.h>
#include <fstream>
#include <iomanip>
#include <string>
#include <iterator>
#include <algorithm>
#include <unordered_map>
#include <utility>
#include <list>
#include <time.h>
#include <vector>
#include <stack>

using namespace std;

class Point {
	private:
		double x;
		double y;
		static bool sortFunct(Point i, Point j) {
			return (j.getx() > i.getx());
		}
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
		double getx() const{
			return x;
			}
		double gety() const{
			return y;
		}

		void display() const{
			cout << "(" << std::setprecision(23) << x << "," << std::setprecision(23) << y << ")";
		}

		bool operator==(const Point& p) const
		    {
		        return x == p.x && y == p.y;
		    }

		static list<Point> getSorted(list<Point> listOfPoints)
		{
		listOfPoints.sort(sortFunct); // invoke system sort with sortFunct comparator
		return listOfPoints;
		}

};

double distance(Point p1, Point p2){
	return sqrt((pow((p2.getx()-p1.getx()), 2) + pow((p2.gety()-p1.gety()), 2)));
}


class Line {
	private:
		Point p1;
		Point p2;
		double m;
		double b;
		//bool und;
	public:
		Line()
		{
			p1 = Point();
			p2 = Point();
			m = 9999;
			b = 9999;
		}
		Line(Point p11, Point p22){
			p1 = p11;
			p2 = p22;
			m = (p22.gety()-p11.gety())/(p22.getx()-p11.getx());
			b = p11.gety() - ((p22.gety()-p11.gety())/(p22.getx()-p11.getx()))*p11.getx();
		}
		Line(double mm, double bb){
			m = mm;
			b = bb;
			p1 = Point();
			p2 = Point();
		}
		Line(Point p11, Point p22,  double m1, double b1){
			p1 = p11;
			p2 = p22;
			m = m1;
			b = b1;
			//und = false;
		}
		Line(const Line& l1)
		    {
			p1 = l1.p1;
			p2 = l1.p2;
			m = l1.m;
			b = l1.b;
			//if(l1.m == NULL){
			//	und = l1.und;
			// }
		    }
		~Line()
		    {
		        //cout<<"\n Destructor executed";
		    }

		double getyint(){
			return b;
		}

		double getB()
		{
			return b;
		}

		double getM(){
			return m;
		}

		double getx1(){
			return p1.getx();
		}

		double gety1(){
			return p1.gety();
		}

		double getx2(){
			return p2.getx();
		}

		double gety2(){
			return p2.gety();
		}

		double getperp(){
			return (-1)/m;
		}

		void toString(){
			cout << "y = " << m << "x + " << b;
		}


};

Point findinter(Line l1, Line l2){
	double x = (l1.getB()-l2.getB())/(l2.getM()-l1.getM());
	double y = l1.getM()*x + l1.getB();
	Point p = Point(x, y);
	return p;

}

void illuminate(int **grid, int x, int y){
	if(x <400 and x >0 and y < 400 and y >0){
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

void bresenham(int **grid, Point p1, Point p2){
	int x1 = round(p1.getx() * 400);
	int x2 = round(p2.getx() * 400);
	int y1 = round(p1.gety() * 400);
	int y2 = round(p2.gety() * 400);
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

void makecircle(int **grid, Point p1, double radius){
	int xc = round(p1.getx() * 400);
	int yc = round(p1.gety() * 400);
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
}

bool comparePx(Point i1, Point i2)
		{
		    return (i1.getx() < i2.getx());
		}

bool comparePy(Point i1, Point i2)
		{
		    return (i1.gety() < i2.gety());
		}

int num = 60;

void findhull(vector<Point> &convexh, vector<Point> &s, Point a, Point b){
	if(s.empty()){
		return;
	}
	Line ab = Line(a, b);
	double maxD = 0;
	Point c;
	double newSlope = (-1)/ab.getB();
	for(Point x: s){
		double yint = x.gety() - newSlope*x.getx();
		Line new1 = Line(newSlope, yint);
		Point di = findinter(new1, ab);
		if(distance(di, x) > maxD){
			maxD = distance(di, x);
			c = x;
		}
	}

	int index = 99999999;

    for(int i = 1; i < convexh.size(); i++){
    	if((convexh[i] == b and convexh[i-1] == a))
    	{
    		index = i;
    		break;
    	}
    }

    convexh.insert(convexh.begin() + index, c);

	//convexh.push_back(c);

	//cout << " c " << c.getx() << " " << c.gety() << endl;

	Line ac = Line(a, c);

	Line cb = Line(c, b);

	vector<Point> s1;

	vector<Point> s2;

	for(int i = 0; i < s.size(); i++){
		Point p = s[i];
		if(p == c){
			continue;
		}
		//right side from a to c
		double value1 = ((c.getx()-a.getx())*(p.gety() - a.gety()))  - ((c.gety() - a.gety())*(p.getx() - a.getx()));
		//right side from c to b
		double value2 = ((b.getx()-c.getx())*(p.gety() - c.gety()))  - ((b.gety() - c.gety())*(p.getx() - c.getx()));
		if(value1 < 0){
			s1.push_back(p);
		}
		else if(value2 < 0){
			s2.push_back(p);
		}
	}

	vector<Point> &s111 = s1;
	vector<Point> &s222 = s2;


	findhull(convexh, s111, a, c);
	findhull(convexh, s222, c, b);

}


vector<Point> quickhull(int **grid, vector<Point> points){
	vector<Point> convexh;
	sort(points.begin(), points.end(), comparePx);
	Point a = points[0];
	Point b = points[num-1];

	int count = 1;
	while(points[count].getx() == a.getx()){
		if(points[count].gety() < a.gety()){
			a = points[count];
		}
		count += 1;
	}

	count = num-2;
	while(points[count].getx() == b.getx()){
			if(points[count].gety() > b.gety()){
				b = points[count];
			}
			count -= 1;
		}

	convexh.push_back(a);
	convexh.push_back(b);
	convexh.push_back(a);

	vector<Point > s1;

	vector<Point> s2;

	for(int i = 0; i < points.size(); i++){
		Point p = points[i];
		//for right turn from a to b
		double value1 = ((b.getx()-a.getx())*(p.gety() - a.gety()))  - ((b.gety() - a.gety())*(p.getx() - a.getx()));
		//for right turn from b to a
		double value2 = ((a.getx()-b.getx())*(p.gety() - b.gety()))  - ((a.gety() - b.gety())*(p.getx() - b.getx()));
		if((p == a) or (p == b)){
			continue;
		}
		else if(value2 < 0){
			s2.push_back(p);
		}
		else if(value1 < 0){
			s1.push_back(p);
		}
		else{

		}
	}

	//bresenham(grid, a, b);

	vector<Point> &convexhull = convexh;

	vector<Point> &s11 = s1;

	vector<Point> &s22 = s2;

	findhull(convexhull, s11, a, b);

	findhull(convexhull, s22, b, a);

	return convexh;
}

void part1(){
	int x = 400;
	int y = 400;

	int**grid;

	grid = new int*[400];

	for(int i = 0; i < 400; i++){
		grid[i] = new int[400];
	}

	int**ppm;

	ppm = new int*[400];

	for(int i = 0; i < 400; i++){
			ppm[i] = new int[1200];
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

	ofstream out;
	srand(time(NULL));
	vector<Point> points;
	out.open ("points.txt");
	for(int i = 0; i < num; i++){
		double pointx = ((double) rand() / (RAND_MAX));
		double pointy = ((double) rand() / (RAND_MAX));
		points.push_back(Point(pointx, pointy));
		out << std::setprecision(23) << pointx << "  " << std::setprecision(23) << pointy << "\n";
	}
	out.close();


	for(int i = 0; i < num; i++){
		Point p = points[i];
		makecircle(grid, p, 3);
	}

	vector<Point> convexh = quickhull(grid, points);

	//sort(convexh.begin(), convexh.end(), comparePy);

	for(int i = 0; i < convexh.size(); i++){
		makecircle(grid, convexh[i], 2);
		makecircle(grid, convexh[i], 3);
	}

	for(int i = 0; i < convexh.size()-1; i++){
		bresenham(grid, convexh[i], convexh[i+1]);
	}

	//make ppm
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
	myfile.open ("quickhull.ppm");
	myfile << "P3  400  400  1\n";
	for (int i = 0; i < x; i++){
		  for (int j = 0; j < y*3; j++){
			myfile << ppm[i][j] << " ";
		  }
		myfile << "\n";
	}
	myfile.close();


}

Point p0;

bool compareCross(Point p1, Point p2){
	double cross = (((p1.getx() - p0.getx())*(p2.gety() - p0.gety()))  - ((p1.gety() - p0.gety())*(p2.getx()-p0.getx())));
	return (cross > 0);
}

bool notleft(Point a, Point b, Point p){
	double value1 = ((b.getx()-a.getx())*(p.gety() - a.gety()))  - ((b.gety() - a.gety())*(p.getx() - a.getx()));
	return (value1 < 0);
}

void part2(){
	int x = 400;
	int y = 400;

	int**grid;

	grid = new int*[400];

	for(int i = 0; i < 400; i++){
		grid[i] = new int[400];
	}

	int**ppm;

	ppm = new int*[400];

	for(int i = 0; i < 400; i++){
			ppm[i] = new int[1200];
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
	ifstream poin;
	poin.open("points.txt");
	vector<Point> points;
	if(poin.is_open()){
		string line;
		while (getline(poin,line))
			{
			  double xval = stod(line.substr(0, line.find(' ')));
			  double yval = stod(line.substr(line.find(' ') + 1, line.length()));
			  points.push_back(Point(xval, yval));
			}
			poin.close();
		  }

	for(int i = 0; i < points.size(); i++){
			Point p = points[i];
			makecircle(grid, p, 3);
		}
	sort(points.begin(), points.end(), comparePy);
	p0 = points[0];

	int count1 = 1;
	while(points[count1].gety() == p0.gety()){
		if(points[count1].getx() < p0.getx()){
			p0 = points[count1];
		}
		count1 += 1;
	}

	vector<Point>::iterator r;
	r = remove(points.begin(), points.end(), p0);

	sort(points.begin(), points.end(), compareCross);
	stack<Point> stack;
	stack.push(p0);
	stack.push(points[0]);
	for(int i = 1; i < points.size(); i++){
		Point p = points[i];
		Point b = stack.top();
		stack.pop();
		Point a = stack.top();
		while((stack.size() > 1) and (notleft(a, b, p))){
			b = stack.top();
			stack.pop();
			a = stack.top();
		}
		stack.push(b);
		stack.push(p);


	}

	stack.push(p0);

	while(stack.size() > 1){
		Point p =  stack.top();
		makecircle(grid, p, 2);
		stack.pop();
		Point p1 = stack.top();
		bresenham(grid, p, p1);
	}

	//make ppm
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
	myfile.open ("grahamscan.ppm");
	myfile << "P3  400  400  1\n";
	for (int i = 0; i < x; i++){
		  for (int j = 0; j < y*3; j++){
			myfile << ppm[i][j] << " ";
		  }
		myfile << "\n";
	}
	myfile.close();


}


int main(){
	//part1();
	part2();

}




