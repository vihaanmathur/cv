/*
 * l031.cpp
 *
 *  Created on: Oct 11, 2022
 *      Author: viditmathur
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

class BoxPoint{
private:
	unsigned long long int x;
	unsigned long long int y;
	static bool sortFunct(BoxPoint i, BoxPoint j) {
		return (j.getx() > i.getx());
	}
public:
	BoxPoint(){
		x = 0;
		y = 0;
	}
	BoxPoint(unsigned long long int xv, unsigned long long int yv){
		x = xv;
		y = yv;
	}
	BoxPoint(const BoxPoint& p1)
	    {
	        x = p1.x;
	        y = p1.y;
	    }
	~BoxPoint()
	  {
		  //cout<<"\n Destructor executed";
	  }
	unsigned long long int getx() const{
		return x;
		}
	unsigned long long int gety() const{
		return y;
	}

	void display() const{
		cout << "(" << x << ","  << y << ")";
	}

	bool operator==(const BoxPoint& p) const
	    {
	        return x == p.x && y == p.y;
	    }

};

class MyHashFunction {
public:

    size_t operator()(const BoxPoint& p) const
    {
        BoxPoint z = p;
    	return (17*(z.getx() + z.gety()));
    }
};

bool compareP(Point i1, Point i2)
		{
		    return (i1.gety() < i2.gety());
		}

bool comparePx(Point i1, Point i2)
		{
		    return (i1.getx() < i2.getx());
		}


class minThing {
	private:
		Point p1;
		Point p2;
		double d;
	public:
		minThing(){
			p1 = Point();
			p2 = Point();
			d = 9999999;
		}
		minThing(Point p11, Point p22, double dist){
			p1 = p11;
			p2 = p22;
			d = dist;
		}
		minThing(const minThing& m)
			{
				p1 = m.p1;
				p2 = m.p2;
				d = m.d;
			}
		~minThing()
		  {
			  //cout<<"\n Destructor executed";
		  }
		Point getp1(){
			return p1;
			}
		Point getp2(){
			return p2;
		}

		double getdist(){
			return d;
		}
		void setp1(Point p) {
		      p1 = p;
		    }
		void setp2(Point p) {
				      p2 = p;
				    }
		void setdist(double di) {
				      d = di;
				    }
		minThing compareP(minThing i) {
			if(i.getdist() < d){
				return i;
			}
			else{
				return *this;
			}
		}

};

double distance(Point p1, Point p2){
	return sqrt((pow((p2.getx()-p1.getx()), 2) + pow((p2.gety()-p1.gety()), 2)));
}


void illuminate(int **grid, int x, int y, int color){
	//0 = black, 1 = red
	if(color == 0){
		if(x <800 and x >0 and y < 800 and y >0){
			grid[x][y] = 0;
		}
	}
	else{
		if(x <800 and x >0 and y < 800 and y >0){
			grid[x][y] = 2;
		}

	}

}
void makecircle(int **grid, Point p1, int radius){
	int xc = round(p1.getx() * 800);
	int yc = round(p1.gety() * 800);
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
		illuminate(grid, xc+x, yc+yy, 0);
		illuminate(grid, xc+x, yc-yy, 0);
		illuminate(grid, xc-x, yc+yy, 0);
		illuminate(grid, xc-x, yc-yy, 0);
		illuminate(grid, xc+yy, yc+x, 0);
		illuminate(grid, xc+yy, yc-x, 0);
		illuminate(grid, xc-yy, yc+x, 0);
		illuminate(grid, xc-yy, yc-x, 0);

		y2_new -= (2 * x) + 3;
	}
}

void makeredcircle(int **grid, Point p1, int radius){
	int xc = round(p1.getx() * 800);
	int yc = round(p1.gety() * 800);
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
		illuminate(grid, xc+x, yc+yy, 2);
		illuminate(grid, xc+x, yc-yy, 2);
		illuminate(grid, xc-x, yc+yy, 2);
		illuminate(grid, xc-x, yc-yy, 2);
		illuminate(grid, xc+yy, yc+x, 2);
		illuminate(grid, xc+yy, yc-x, 2);
		illuminate(grid, xc-yy, yc+x, 2);
		illuminate(grid, xc-yy, yc-x, 2);

		y2_new -= (2 * x) + 3;
	}
}

void part0(){
	string x;
	cout << "Do you want to generate points? Enter 'Y' for yes and 'N' for no ";
	cin >> x;

	srand(time(NULL));
	if (x == "Y"){
		int num;
		cout << "How many random points do you want to generate? ";
		cin >> num;
		ofstream out;
		out.open ("points.txt");
		for(int i = 0; i < num; i++){
			double pointx = ((double) rand() / (RAND_MAX));
			double pointy = ((double) rand() / (RAND_MAX));
			out << std::setprecision(23) << pointx << " " << std::setprecision(23) << pointy << "\n";
		}
		out.close();
	}
}

void makeppm(int** grid, int** ppm, Point p1, Point p2){
	int x = 800;
	int y = 800;

	//creating ppm file
	int count = 0;
	for (int i = 0; i < x; i++)
		{
			  count = 0;
			  for (int j = 0; j < y*3; j+=3)
			  {
				  int val = grid[i][count];
				  if(val == 2){
					  ppm[i][j] = 1;
					  ppm[i][j+1] = 0;
					  ppm[i][j+2] = 0;
				  }
				  else{
					  ppm[i][j] = val;
					  ppm[i][j+1] = val;
					  ppm[i][j+2] = val;
				  }
				  count += 1;
			  }
	}

	ofstream myfile;
	myfile.open ("points.ppm");
	myfile << "P3  800  800  1\n";
	for (int i = 0; i < x; i++){
		  for (int j = 0; j < y*3; j++){
			myfile << ppm[i][j] << " ";
		  }
		myfile << "\n";
	}
	myfile.close();

}

//clock_t part1(){
//
//	ifstream poin;
//	poin.open("points.txt");
//	list<Point> points;
//	if(poin.is_open()){
//		string line;
//		while (getline(poin,line))
//			{
//			  double xval = stod(line.substr(0, line.find(' ')));
//			  double yval = stod(line.substr(line.find(' ') + 1, line.length()));
//			  points.push_back(Point(xval, yval));
//			}
//			poin.close();
//		  }
//
//	Point p1;
//	Point p2;
//	double mindist = 999999999;
//	clock_t t;
//	t = clock();
//	for (int i = 0; i < int(points.size()); i++){
//		list<Point>::iterator it = points.begin();
//		advance(it, i);
//		for (int j = i+1; j < int(points.size()); j++){
//			list<Point>::iterator it1 = points.begin();
//			advance(it1, j);
//			double d = distance(*it, *it1);
//			if (d < mindist){
//				p1 = *it;
//				p2 = *it1;
//				mindist = d;
//			}
//		}
//	}
//
//	t = clock() - t;
//	cout << "time for iterative algorithm : " << t << " miliseconds" << endl;
//	//cout << "time for recursive algorithm: " << t*1.0/CLOCKS_PER_SEC << " seconds" << endl;
//
//	cout << "The two closest points are: ";
//	p1.display();
//	cout << " and ";
//	p2.display();
//	double printd = distance(p1, p2);
//	part1p1 = p1;
//	part1p2 = p2;
//	part1d = printd;
//	cout << "\n" << "The distance between them is: " << printd << endl;
//
//	return t;
//
//}

Point part3p1;

Point part3p2;

double part3d;

//Point part2p1;
//
//Point part2p2;
//
//double part2d;

Point part4p1;

Point part4p2;

double part4d;


//minThing merge(vector<Point> &sorted, int a, int b){
//	if((b - a) == 1){
//		minThing m = minThing(sorted[a], sorted[b], distance(sorted[a], sorted[b]));
//		return m;
//	}
//	else if((b-a) == 2){
//			double d1 = distance(sorted[a], sorted[a+1]);
//			double d2 = distance(sorted[a], sorted[b]);
//			double d3 = distance(sorted[a+1], sorted[b]);
//			if(d1 < d3 and d1 < d2){
//				return minThing(sorted[a], sorted[a+1], d1);
//			}
//			else if(d2 < d3 and d2 < d1){
//				return minThing(sorted[a], sorted[b], d2);
//			}
//			else{
//				return minThing(sorted[a+1], sorted[b], d3);
//			}
//		}
//	else{
//		int index = (a+b)/2;
//		minThing m1 = merge(sorted, a, index);
//		minThing m2 = merge(sorted, index+1, b);
//
//
//		Point mid = sorted[index];
//		minThing actual;
//		if(m1.getdist() < m2.getdist()){
//			actual = m1;
//		}
//		else{
//			actual = m2;
//
//		}
//
//		double minD = actual.getdist();
//		vector<Point> right;
//		vector<Point> left;
//
//		for(int i = index+1; i <= b; i++){
//			if((sorted[i].getx() - mid.getx()) <= minD){
//							right.push_back(sorted[i]);
//						}
//						else{
//							break;
//						}
//
//
//		}
//
//		for (int i = index; i >= a; i--) {
//			if((mid.getx() - sorted[i].getx()) <= minD){
//				left.push_back(sorted[i]);
//			}
//			else{
//				break;
//			}
//		}
//	    if(right.size() > 0 && left.size() > 0){
//			for(int i = 0; i < left.size(); i++){
//				for(int j = 0; j < right.size(); j++){
//					double current = distance(left[i], right[j]);
//					if(current < actual.getdist()){
//						actual.setdist(current);
//						actual.setp1(left[i]);
//						actual.setp2(right[j]);
//					}
//
//				}
//			}
//
//			return actual;
//	    }
//	    else{
//	    	return actual;
//	    }
//	}
//}

minThing merge3(vector<Point> &sorted, int a, int b){
	if((b - a) == 1){
		minThing m = minThing(sorted[a], sorted[b], distance(sorted[a], sorted[b]));
		return m;
	}
	else if((b-a) == 2){
			double d1 = distance(sorted[a], sorted[a+1]);
			double d2 = distance(sorted[a], sorted[b]);
			double d3 = distance(sorted[a+1], sorted[b]);
			if(d1 < d3 and d1 < d2){
				return minThing(sorted[a], sorted[a+1], d1);
			}
			else if(d2 < d3 and d2 < d1){
				return minThing(sorted[a], sorted[b], d2);
			}
			else{
				return minThing(sorted[a+1], sorted[b], d3);
			}
		}
	else{
		int index = (a+b)/2;
		minThing m1 = merge3(sorted, a, index);
		minThing m2 = merge3(sorted, index+1, b);


		Point mid = sorted[index];
		minThing actual;
		if(m1.getdist() < m2.getdist()){
			actual = m1;
		}
		else{
			actual = m2;

		}

		double minD = actual.getdist();
		vector<Point> vectorStrip;

		for(int i = index+1; i <= b; i++){
			if((sorted[i].getx() - mid.getx()) <= minD){
							vectorStrip.push_back(sorted[i]);
						}
						else{
							break;
						}

		}

		for (int i = index; i >= a; i--) {
			if((mid.getx() - sorted[i].getx()) <= minD){
				vectorStrip.push_back(sorted[i]);
			}
			else{
				break;
			}
		}

		sort(vectorStrip.begin(), vectorStrip.end(), compareP);


		for(int i = 0; i < vectorStrip.size(); i++){
			Point currP = vectorStrip[i];
			for(int j = 1; j < 16; j++){
				if(distance(currP, vectorStrip[i+j]) == 0){
					continue;
				}
				if(i+j < vectorStrip.size()){
				if(distance(currP, vectorStrip[i+j]) < actual.getdist()){
					actual.setdist(distance(currP, vectorStrip[i+j]));
					actual.setp1(currP);
					actual.setp2(vectorStrip[i+j]);
					}
				}
			}
		}
		return actual;
	}
}

//clock_t part2(){
//
//	ifstream poin;
//	poin.open("points10k.txt");
//	vector<Point> points;
//	if(poin.is_open()){
//		string line;
//		while (getline(poin,line))
//			{
//			  double xval = stod(line.substr(0, line.find(' ')));
//			  double yval = stod(line.substr(line.find(' ') + 1, line.length()));
//			  points.push_back(Point(xval, yval));
//			}
//			poin.close();
//		  }
//
//
//	clock_t t;
//	t = clock();
//
//	sort(points.begin(), points.end(), comparePx);
//
//	vector<Point> &sorted = points;
//
//	minThing q = merge(sorted, 0, sorted.size()-1);
//
//	t = clock() - t;
//	//cout << "time for intermediate recursive algorithm : " << t << " miliseconds" << endl;
//	cout << "time for intermediate recursive algorithm: " << t*1.0/CLOCKS_PER_SEC << " seconds" << endl;
//
//	cout << "The two closest points are: ";
//	q.getp1().display();
//	cout << " and ";
//	q.getp2().display();
//	cout << "\n" << "The distance between them is: " <<  std::setprecision(23) << q.getdist();
//
//	return t;
//}


clock_t part3(){
	ifstream poin;
	poin.open("points10k.txt");
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


	clock_t t;
	t = clock();

	sort(points.begin(), points.end(), comparePx);

	vector<Point> &sorted = points;

	minThing q = merge3(sorted, 0, sorted.size()-1);

	t = clock() - t;

	//cout << endl << "time for completely recursive algorithm : " << t << " miliseconds" << endl;
	cout << "time for completely recursive algorithm: " << t*1.0/CLOCKS_PER_SEC << " seconds" << endl;

	cout << "The two closest points are: ";
	q.getp1().display();
	part3p1 = q.getp1();
	part3p2 = q.getp2();
	part3d = q.getdist();
	cout << " and ";
	q.getp2().display();
	cout << "\n" << "The distance between them is: " <<  std::setprecision(23) << q.getdist();

	return t;

}

clock_t part4(){
	ifstream poin;
	poin.open("points10k.txt");
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

	clock_t t;
	t = clock();

	for (int i = points.size() - 1; i >= 0; i--)
	    {
	        int j = rand() % (i + 1);
	        swap(points[i], points[j]);
	    }

	double min = distance(points[0], points[1]);

	double copy = min;

	double side_l = min/2;

	unordered_map<BoxPoint, Point, MyHashFunction> poi;

	//putting in the first two points

	unsigned long long int first = floor(points[0].getx()/side_l);

	unsigned long long int second = floor(points[0].gety()/side_l);

	poi[BoxPoint(first, second)] = points[0];

	unsigned long long int first1 = floor(points[1].getx()/side_l);

	unsigned long long int second1 = floor(points[1].gety()/side_l);

	poi[BoxPoint(first1, second1)] = points[1];


//	cout << endl << side_l << " " << points[0].getx() << " " << floor(points[0].getx()/side_l) << endl;
//
//	  for (auto x : poi){
//	    cout << x.first.getx();
//	}

	for(int i = 2; i < points.size(); i++){

		unsigned long long int x = floor(points[i].getx()/side_l);

		unsigned long long int y = floor(points[i].gety()/side_l);

		for(unsigned long long int xx = x-2; xx <= x+2; xx++){
			for(unsigned long long int yy = y - 2; yy <= y+2; yy++){
				BoxPoint p = BoxPoint(xx, yy);
				if(poi.find(p) != poi.end()){
					Point check = poi[p];
					if(check == points[i]){
						continue;
					}
					if(distance(check, points[i]) < copy){
						part4p1 = check;
						part4p2 = points[i];
						copy = distance(check, points[i]);
					}
				}
			}
		}
		if(copy < min){
			poi.clear();
			min = copy;
			side_l = copy/2;
			for(int j = 0; j <= i; j++){
				unsigned long long int insertx = floor(points[j].getx()/side_l);

				unsigned long long int inserty = floor(points[j].gety()/side_l);

				poi[BoxPoint(insertx, inserty)] = points[j];

			}

		}
		else{
			poi[BoxPoint(x, y)] = points[i];
		}
	}

	t = clock() - t;

    part4d = min;

	cout << endl << "time for randomized algorithm : " << t*1.0/CLOCKS_PER_SEC << " seconds" << endl;
	cout << "The two closest points are: ";
	part4p1.display();
	cout << " and ";
	part4p2.display();
	cout << "\n" << "The distance between them is: " <<  std::setprecision(23) << part4d;

	return t;
}


int main()
{
	//part0();
	clock_t t0 = part3();
	clock_t t2 = part4();
	ofstream myfile;
	myfile.open ("results.txt");
	myfile << "Time for completing completely recursive algorithm: " << t0*1.0/CLOCKS_PER_SEC << " seconds" << endl;
	myfile << "The two closest points are: ";
	myfile << "(" << std::setprecision(23) << part3p1.getx() << "," << std::setprecision(23) << part3p1.gety() << ")";
	myfile << " and ";
	myfile << "(" << std::setprecision(23) << part3p2.getx() << "," << std::setprecision(23) << part3p2.gety() << ")";
	myfile << "\n" << "The distance between them is: " << part3d << endl;
	myfile << "Time for completing randomized algorithm: " << t2*1.0/CLOCKS_PER_SEC << " seconds" << endl;
	myfile << "The two closest points are: ";
	myfile << "(" << std::setprecision(23) << part4p1.getx() << "," << std::setprecision(23) << part4p1.gety() << ")";
	myfile << " and ";
	myfile << "(" << std::setprecision(23) << part4p2.getx() << "," << std::setprecision(23) << part4p2.gety() << ")";
	myfile << "\n" << "The distance between them is: " << part4d << endl;
	myfile.close();

	return 0;
}


