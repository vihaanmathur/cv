/*
 * This program implements coin detection, but uses OpenCV. 
 *
 *  Created on: Feb 20, 2023
 *      Author: Vihaan Mathur
 */


#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;

using namespace cv;

int main(int argc, char** argv)
{
    int distance, centert, edget; 
    if ( argc != 8 )
    {
        printf("usage: DisplayImage.out <Image_Path>\n");
        return -1;
    }

    Mat image;
    image = imread( argv[1], 1 );

    if ( !image.data )
    {
        printf("No image data \n");
        return -1;
    }
    for (int i = 1; i < argc; i++)
        {
            if(strcmp(argv[i], "-d") == 0){
                distance = atoi(argv[i+1]);       
            }
            if(strcmp(argv[i], "-ct") == 0){
                centert = atoi(argv[i+1]);         
            }
            if(strcmp(argv[i], "-et") == 0){
                edget = atoi(argv[i+1]);         
            }
    }
    //grayscale
    //Coins Easy - 68 coins, $5.76
    //Coins Medium - 
    //Coins Hard - 
    Mat gray;
    gray = imread( argv[1], IMREAD_GRAYSCALE );
    //canny edge 
    Mat edges;
    Canny(gray, edges, 75, 120, 3, false);
    imwrite("./imagef.jpg", edges);
    imwrite("./imageg.jpg", gray); 
    Mat blurr;
    GaussianBlur(gray,blurr, Size(5,5),0);
    medianBlur(blurr, blurr, 5);
    vector<Vec3f> circles;
    HoughCircles(blurr, circles, HOUGH_GRADIENT, 1,
                 blurr.rows/distance,  
                 edget, centert, 50, 180 //blurr.rows/16, 120, 25 for easy image
                 //blurr.rows/30, 120, 58 for medium image 
                 //
    );
    for( size_t i = 0; i < circles.size(); i++ )
    {
        Vec3i c = circles[i];
        Point center = Point(c[0], c[1]);
        // circle center
        circle( image, center, 4, Scalar(0,0,255), 3, LINE_AA);
        // circle outline
        int radius = c[2];
        circle(image, center, radius, Scalar(0,0,255), 2, LINE_AA);
    }
    imwrite("./imageCircles.jpg", image);
    
    	//colors key below
		//black
		//red - penny
		//blue - dime
		//yellow - nickel
		//purple - quarter
		//green - half dollar
		//pink - dollar
		//only pennys, nickels, and quarters
		int pennyC = 0;
		int nickelC = 0;
		int quarterC = 0;
		int dimeC = 0;
		int halfC = 0;
		int dollarC = 0;
	    int max = 0;
	    double pennyrad = 0;
		for (size_t i = 0; i < circles.size(); i++) {
		  int mostc = 0;
          Vec3i c = circles[i];
          double radius = c[2];
		  for (int j = 0; j < circles.size(); j++) {
            Vec3i ins = circles[j];
            double radius1 = ins[2];
			if (radius == radius1) {
			  mostc++;
			}
		  }
		  if (mostc > max) {
			max = mostc;
			pennyrad = radius;
		  }
		} 
        double nickelr = 0.835/0.750;
        double pennyr = 1.0;
        double quarterr = 0.950/0.750;
        double dimer =  0.60/0.750;
        double halfr = 1.205/0.750;
        double dollarr = 1.1/0.750; 

		for (int i = 0; i < circles.size(); i++){
                  Vec3i c = circles[i];
                  double radius = c[2];
				  double num = radius/pennyrad;
				  string closest;
                  Point center = Point(c[0], c[1]);
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
                  circle(image, center, radius, Scalar(0,255,255), 2, LINE_AA);
				  nickelC++;
				  }
				  else if(closest == "quarter"){
                      circle(image, center, radius, Scalar(191,64,191), 2, LINE_AA);
					  quarterC++;

				  }
				  else if(closest == "dime"){
                      circle(image, center, radius, Scalar(255,0,0), 2, LINE_AA);
					  dimeC++;

				  }
				  else if(closest == "dollar"){
                      circle(image, center, radius, Scalar(180,105,255), 2, LINE_AA);
					  dollarC++;

				  }
				  else{ //half dollar
                      circle(image, center, radius, Scalar(127,255,0), 2, LINE_AA);
					  halfC++;

				  }
		}
        imwrite("./imageCoins.jpg", image);
        
    
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
		cout << "Total sum: $" << totalsum << "\n";
		res.close();


    waitKey(0);

    return 0;
}
