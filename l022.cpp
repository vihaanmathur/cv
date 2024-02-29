/*
 * l021.cpp
 *
 *  Created on: Sep 16, 2022
 *      Author: viditmathur
 */

#include <cmath>
#include <tgmath.h>
#include<iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include<algorithm>

using namespace std;

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
			  cout<<"\n Destructor executed";
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
		        cout<<"\n Destructor executed";
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

double distance(Point p1, Point p2){
	return sqrt((pow((p2.getx()-p1.getx()), 2) + pow((p2.gety()-p1.gety()), 2)));
}

class Square {
	private:
		Point v1;
		Point v2;
		Point v3;
		Point v4;
		double sidel;
		double area;
		Line l1;
		Line l2;
		Line l3;
		Line l4;
	public:
		Square(){
			v1 = Point();
			v2 = Point();
			v3 = Point();
			v4 = Point();
			sidel = 9999999;
			area = 99999;
			l1 = Line();
			l2 = Line();
			l3 = Line();
			l4 = Line();

		}
		Square(Point v11, Point v22,  Point v33, Point v44, Line l11, Line l22, Line l33, Line l44){
			v1 = v11;
			v2 = v22;
			v3 = v33;
			v4 = v44;
			sidel = distance(v1, v2);
			area = sidel*sidel;
			l1 = l11;
			l2 = l22;
			l3 = l33;
			l4 = l44;
		}
		Square(const Square& s1)
		    {
			v1 = s1.v1;
			v2 = s1.v2;
			v3 = s1.v3;
			v4 = s1.v4;
			sidel = s1.sidel;
			area = s1.area;
			l1 = s1.l1;
			l2 = s1.l2;
			l3 = s1.l3;
			l4 = s1.l4;
		    }
		~Square()
		    {
		        cout<<"\n Destructor executed";
		    }

		Point getv1(){
			return v1;
		}
		Point getv2(){
			return v2;
				}
		Point getv3(){
			return v3;
				}
		Point getv4(){
			return v4;
				}

		double getarea(){
					return area;
				}
		double getsidel(){
					return sidel;
				}
		Line getl1(){
					return l1;
						}
		Line getl2(){
					return l2;
						}
		Line getl3(){
					return l3;
						}
		Line getl4(){
					return l4;
						}

		void toString(){
			cout << "Square with side length: " << sidel;
		}


};


double calcarea(double x1, double y1,double x2,double y2,double x3,double y3)
{
	double a = sqrt((pow((x2-x1), 2) + pow(y2-y1, 2)));
	double b = sqrt((pow((x3-x1), 2) + pow(y3-y1, 2)));
	double c = sqrt((pow((x3-x2), 2) + pow(y3-y2, 2)));
	double s = .5*(a+b+c);
	double area = sqrt(s*(s-a)*(s-b)*(s-c));
	return area;
}

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

void bresenham(int **grid, Line l1){
	int x1 = round(l1.getx1() * 800);
	int x2 = round(l1.getx2() * 800);
	int y1 = round(l1.gety1() * 800);
	int y2 = round(l1.gety2() * 800);
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

void makecircle(int **grid, Point p1){
	double radius = 4;
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

void part1(){
	ofstream myfile;
	ofstream file1;

	srand(time(NULL));
	double x1 = ((double) rand() / (RAND_MAX));
	double y1 = ((double) rand() / (RAND_MAX));
	double x2 = ((double) rand() / (RAND_MAX));
	double y2 = ((double) rand() / (RAND_MAX));
	double x3 = ((double) rand() / (RAND_MAX));
	double y3 = ((double) rand() / (RAND_MAX));
	myfile.open ("log.txt");
	file1.open("points.txt");
	myfile << "(" << std::setprecision(19) << x1 << "," << std::setprecision(19) << y1 << ")" << " ";
	myfile << "(" << std::setprecision(19) << x2 << "," << std::setprecision(19) << y2 << ")" << " ";
	myfile << "(" << std::setprecision(19) << x3 << "," << std::setprecision(19) << y3 << ")" << " ";
	file1 << "(" << std::setprecision(19) << x1 << "," << std::setprecision(19) << y1 << ")" << ", " << "\n";
	file1 << "(" << std::setprecision(19) << x2 << "," << std::setprecision(19) << y2 << ")" << ", " << "\n";
	file1 << "(" << std::setprecision(19) << x3 << "," << std::setprecision(19) << y3 << ")" << ", " << "\n";
	cout << "(" << std::setprecision(19) << x1 << "," << std::setprecision(19) << y1 << ")" << " ";
	cout << "(" << std::setprecision(19) << x2 << "," << std::setprecision(19) << y2 << ")" << " ";
	cout << "("<< std::setprecision(19) << x3 << "," << std::setprecision(19) << y3 << ")" << " ";
	int num = 0;
	while (num == 0){
		double x4 = ((double) rand() / (RAND_MAX));
		double y4 = ((double) rand() / (RAND_MAX));
		cout << "\n";
		cout << "testing... " << "(" << x4 << "," << y4 << ")" << " ";
		myfile << "\n";
		myfile << "testing... " << "(" << x4 << "," << y4 << ")" << " ";
		//triangle excluding x4
		double a1 = calcarea(x1, y1, x2, y2, x4, y4);
		double a2 = calcarea(x2, y2, x3, y3, x4, y4);
		double a3 = calcarea(x1, y1, x3, y3, x4, y4);
		double fulla = calcarea(x1, y1, x2, y2, x3, y3);
		double sumarea = a1+a2+a3;
		//triangle excluding x2
		double a4 = calcarea(x1, y1, x3, y3, x2, y2);
		double a5 = calcarea(x1, y1, x4, y4, x2, y2);
		double a6 = calcarea(x3, y3, x4, y4, x2, y2);
		double fulla1 = calcarea(x1, y1, x4, y4, x3, y3);
		double sumarea1 = a4+a5+a6;
//		//triangle excluding x1
		double a7 = calcarea(x2, y2, x3, y3, x1, y1);
		double a8 = calcarea(x4, y4, x3, y3, x1, y1);
		double a9 = calcarea(x2, y2, x4, y4, x1, y1);
		double fulla2 = calcarea(x2, y2, x3, y3, x4, y4);
		double sumarea2 = a7+a8+a9;
//		//triangle excluding x3
		double a10 = calcarea(x1, y1, x2, y2, x3, y3);
		double a11 = calcarea(x1, y1, x4, y4, x3, y3);
		double a12 = calcarea(x2, y2, x4, y4,x3, y3);
		double fulla3 = calcarea(x1, y1, x2, y2, x4, y4);
		double sumarea3 = a10+a11+a12;
		if((abs(sumarea - fulla) >= 0.01) and (abs(sumarea1 - fulla1) >= 0.01) and (abs(sumarea2 - fulla2) >= 0.01) and (abs(sumarea3 - fulla3) >= 0.01))
		{
			num = 1;
			file1 << "(" << std::setprecision(19) << x4 << "," << std::setprecision(19) << y4 << ")" << " ";
		}
	}
	myfile.close();
	file1.close();

}

Point findinter(Line l1, Line l2){
	double x = (l1.getB()-l2.getB())/(l2.getM()-l1.getM());
	double y = l1.getM()*x + l1.getB();
	Point p = Point(x, y);
	return p;

}

Square makeSquare(int **grid, Point a, Point b, Point c, Point d, int whiche){
		double slope = (c.gety()-a.gety())/(c.getx()-a.getx());
		double aint = a.gety() - slope*a.getx();
		Line l1 = Line(Point(0, aint), Point(799, slope*799 + aint), slope, aint); //ac
		double perpsl = l1.getperp();
		double blint = b.gety() - perpsl*b.getx();
		Line l2 = Line(Point(0, blint), Point(799, perpsl*799 + blint), perpsl, blint); //be
		//step 3 - BE = AC --> two ways
		double dx = a.getx() - c.getx();
		double dy = a.gety() - c.gety();
		Point e;
		if(whiche == 1)
		{
			e = Point(b.getx() - dy, b.gety()+dx);
		}
		else
		{
			e = Point(b.getx() + dy, b.gety()-dx);
		}
		//step 4
		double desl = (e.gety()-d.gety())/(e.getx()-d.getx());
		double deint = e.gety() - desl*e.getx();
		Line l3 = Line(Point(0, deint), Point(799, desl*799 + deint), desl, deint); //de
		//step 5
		double step5 = l3.getperp();
		double p51int = a.gety() - step5*a.getx();
		double p52int = c.gety() - step5*c.getx();
		Line l4 = Line(Point(0, p51int), Point(799, step5*799 + p51int), step5, p51int); //perpin a to de
		Line l5 = Line(Point(0, p52int), Point(799, step5*799 + p52int), step5, p52int); //perpin c to de
		//step 6
		double step6 = l4.getperp();
		double step6i = b.gety() - step6*b.getx();
		Line l6 = Line(Point(0, step6i), Point(799, step6*799 + step6i), step6, step6i);
		//4 vertices of square
		Point v1 = findinter(l3,l4);
		Point v2 = findinter(l3,l5);
		Point v3 = findinter(l4, l6);
		Point v4 = findinter(l5, l6);
		Square s = Square(v1, v2, v3, v4, l3, l4, l5 ,l6);

		return s;
}

void part2(){

	//generating 2d array
	int x = 800;
	int y = 800;

	int**grid;

	grid = new int*[800];

	for(int i = 0; i < 800; i++){
		grid[i] = new int[800];
	}

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

	ifstream points;
	points.open("points.txt");
	string arril[4];
	int countt = 0;
	if(points.is_open()){
		string line;
		while (getline(points,line))
		    {
			  line.erase(remove(line.begin(), line.end(), '('), line.end());
			  line.erase(remove(line.begin(), line.end(), ')'), line.end());
			  line.erase(remove(line.begin(), line.end(), ' '), line.end());
			  if(countt != 3){
					  line.erase(line.end()-1, line.end());}
		      //cout << line << '\n';
		      arril[countt] = line;
		      countt = countt+ 1;
		    }
		    points.close();
		  }
	//cout << arril[0] << arril[0].find(',');
	double pointsx[4];
	double pointsy[4];
	for(int i = 0; i < 4; i++){
		string l = arril[i];
		string xval = l.substr(0, l.find(','));
		//cout << xval;
		string yval = l.substr(l.find(',') + 1, l.length() - 1 - l.find(','));
		//cout << " " << yval;
		pointsx[i] = stod(xval);
		pointsy[i] = stod(yval);

	}
	//cout << pointsx[0] << " " << pointsx[1] << " " << pointsx[2] << " " << pointsx[3] << "\n";
	//cout << pointsy[0] << " " << pointsy[1] << " " << pointsy[2] << " " << pointsy[3] << "\n";



	//starting by reading file and putting coordinates into point objects
	Point a = Point(pointsx[0], pointsy[0]);
	Point b = Point(pointsx[1], pointsy[1]);
	Point c = Point(pointsx[2], pointsy[2]);
	Point d = Point(pointsx[3], pointsy[3]);
	Point arr[4] = {a, b, c, d};
	//generating the six squares
	Square s1 = makeSquare(grid, a, b, c, d, 1);
	Square s2 = makeSquare(grid, a, b, c, d, 2);
	Square s3 = makeSquare(grid, a, c, d, b, 1);
	Square s4 = makeSquare(grid, a, c, d, b, 2);
	Square s5 = makeSquare(grid, a, c, b, d, 1);
	Square s6 = makeSquare(grid, a, c, b, d, 2);

	Square s[6] = {s1, s2, s3, s4, s5, s6};

	ofstream out;
	out.open ("output.txt");
	out << "(" << std::setprecision(19) << a.getx() << "," << std::setprecision(19) << a.gety() << ")" << " , ";
	out << "(" << std::setprecision(19) << b.getx() << "," << std::setprecision(19) << b.gety() << ")" << " , ";
	out << "(" << std::setprecision(19) << c.getx() << "," << std::setprecision(19) << c.gety() << ")" << " , ";
	out << "(" << std::setprecision(19) << d.getx() << "," << std::setprecision(19) << d.gety() << ")" << "\n";

	for(int i = 0; i < 6; i++){
			Square sq = s[i];
			out << "(" << sq.getv1().getx() << "," << sq.getv1().gety() << ") " << "," << " (" << sq.getv2().getx() << "," << sq.getv2().gety() << ") " << "," << " (" << sq.getv3().getx() << "," << sq.getv3().gety() << ") " << "," << " (" << sq.getv4().getx() << "," << sq.getv4().gety() << ") " << "Area=" << sq.getarea() << "\n";
		}

	out.close();


	Square minS;

	if(s1.getarea() < minS.getarea()){
		minS = s1;
	}
	if(s2.getarea() < minS.getarea()){
			minS = s2;
		}
	if(s3.getarea() < minS.getarea()){
			minS = s3;
		}
	if(s4.getarea() < minS.getarea()){
			minS = s4;
		}
	if(s5.getarea() < minS.getarea()){
				minS = s5;
			}
	if(s6.getarea() < minS.getarea()){
				minS = s6;
			}

	//Rendering
	makecircle(grid, a);
	makecircle(grid, b);
	makecircle(grid, c);
	makecircle(grid, d);
	makecircle(grid, minS.getv1());
	makecircle(grid, minS.getv2());
	makecircle(grid, minS.getv3());
	makecircle(grid, minS.getv4());
	bresenham(grid, minS.getl1());
	bresenham(grid, minS.getl2());
	bresenham(grid, minS.getl3());
	bresenham(grid, minS.getl4());

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
	myfile.open ("output.ppm");
	myfile << "P3  800  800  1\n";
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
	return 0;
}


