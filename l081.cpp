#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <vector> 

using namespace std;

using namespace cv;

//take in the vertices and then remove the z and 
//draw the lines function line
//make a list of connections 
//rotation stuff 
//VideoWriter 


void part1(){
    vector <Mat> VerticesC; //storing all 8 vertices in a Mat vector for cube
    VerticesC.push_back((Mat_ < double > (3, 1) << 1,1,1));
    VerticesC.push_back((Mat_ < double > (3, 1) << 1,1,-1));
    VerticesC.push_back((Mat_ < double > (3, 1) << 1,-1,1));
    VerticesC.push_back((Mat_ < double > (3, 1) <<  1,-1,-1));
    VerticesC.push_back((Mat_ < double > (3, 1) << -1,1,1));
    VerticesC.push_back((Mat_ < double > (3, 1) << -1,1,-1));
    VerticesC.push_back((Mat_ < double > (3, 1) << -1,-1,1));
    VerticesC.push_back((Mat_ < double > (3, 1) << -1,-1,-1));
    vector <vector<Mat>> EdgesC; //storing all the edges (connections between the vertices) for cube
    EdgesC.push_back({VerticesC[0],VerticesC[2]});
    EdgesC.push_back({VerticesC[5],VerticesC[7]});
    EdgesC.push_back({VerticesC[2],VerticesC[3]});
    EdgesC.push_back({VerticesC[0],VerticesC[1]});
    EdgesC.push_back({VerticesC[1],VerticesC[5]});
    EdgesC.push_back({VerticesC[4],VerticesC[6]});
    EdgesC.push_back({VerticesC[6],VerticesC[7]});
    EdgesC.push_back({VerticesC[0],VerticesC[4]});
    EdgesC.push_back({VerticesC[4],VerticesC[5]});
    EdgesC.push_back({VerticesC[3],VerticesC[7]});
    EdgesC.push_back({VerticesC[1],VerticesC[3]});
    EdgesC.push_back({VerticesC[2],VerticesC[6]});
    //Now octahedron
    vector <Mat> VerticesD;
    VerticesD.push_back((Mat_ < double > (3, 1) << 1, 0, 0));
    VerticesD.push_back((Mat_ < double > (3, 1) << -1, 0, 0));
    VerticesD.push_back((Mat_ < double > (3, 1) << 0, 1, 0));
    VerticesD.push_back((Mat_ < double > (3, 1) << 0, -1, 0));
    VerticesD.push_back((Mat_ < double > (3, 1) << 0, 0, 1));
    VerticesD.push_back((Mat_ < double > (3, 1) << 0, 0, -1));
    vector <vector<Mat>> EdgesD; 
    EdgesD.push_back({ VerticesD[0],VerticesD[4] });
    EdgesD.push_back({ VerticesD[1],VerticesD[5] });
    EdgesD.push_back({ VerticesD[2],VerticesD[4] });
    EdgesD.push_back({ VerticesD[1],VerticesD[2] });
    EdgesD.push_back({ VerticesD[0],VerticesD[3] });
    EdgesD.push_back({ VerticesD[3],VerticesD[5] });
    EdgesD.push_back({ VerticesD[1],VerticesD[4] });
    EdgesD.push_back({ VerticesD[1],VerticesD[3] });
    EdgesD.push_back({ VerticesD[0],VerticesD[5] });
    EdgesD.push_back({ VerticesD[3],VerticesD[4] });
    EdgesD.push_back({ VerticesD[2],VerticesD[5] });
    EdgesD.push_back({ VerticesD[0],VerticesD[2] });
    
    Mat image(600, 800, CV_8UC3, Scalar(0, 0, 0)); 
    int frames = 600; 
    VideoWriter cube("rotation.avi", VideoWriter::fourcc('X', 'V', 'I', 'D'), 20, cv::Size(800, 600));
    for(int j = 0; j < frames; j++){
        for(int i = 0; i < EdgesC.size(); i++){
            Point2d first(EdgesC[i][0].at<double>(0,0), EdgesC[i][0].at<double>(1,0));
            Point2d second(EdgesC[i][1].at<double>(0,0), EdgesC[i][1].at<double>(1,0));
            line(image, first*100 + Point2d(400, 300), second*100 + Point2d(400, 300), Scalar(255, 255, 255), 1, LINE_8);
        }
        cube.write(image); 
        image = Mat::zeros(600, 800, CV_8UC3);
        Mat rotation; 
        Vec3d rot = {0.01 * CV_PI, 0.005, 0.09};
        Rodrigues(rot, rotation);
        for(int i = 0; i < EdgesC.size(); i++){
            Mat change1 = rotation*EdgesC[i][0];
            Mat change2 = rotation*EdgesC[i][1];
            EdgesC[i] = {change1, change2};
        }    
    }
    
    //dodecahedron rendering 
    for(int j = 0; j < frames; j++){
    for(int i = 0; i < EdgesD.size(); i++){
        Point2d first(EdgesD[i][0].at<double>(0,0), EdgesD[i][0].at<double>(1,0));
        Point2d second(EdgesD[i][1].at<double>(0,0), EdgesD[i][1].at<double>(1,0));
        line(image, first*100 + Point2d(400, 300), second*100 + Point2d(400, 300), Scalar(255, 255, 255), 1, LINE_8);
    }
    cube.write(image); 
    image = Mat::zeros(600, 800, CV_8UC3);
    Mat rotation; 
    Vec3d rot = {0.01 * CV_PI, 0.005, 0.09};
    Rodrigues(rot, rotation);
    for(int i = 0; i < EdgesD.size(); i++){
        Mat change1 = rotation*EdgesD[i][0];
        Mat change2 = rotation*EdgesD[i][1];
        EdgesD[i] = {change1, change2};
    }    
}
    
    waitKey(0);
    
}

int main()
{
    
    part1(); 

    return 0;
}