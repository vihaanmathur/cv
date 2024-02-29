#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <vector> 
#include <algorithm>

using namespace std;

using namespace cv;

void part1(){
    vector <Mat> VerticesC; //storing all 8 vertices in a Mat vector for cube
    VerticesC.push_back((Mat_ < double > (4, 1) << 1,1,1, 1));
    VerticesC.push_back((Mat_ < double > (4, 1) << 1,1,-1, 1));
    VerticesC.push_back((Mat_ < double > (4, 1) << 1,-1,1, 1));
    VerticesC.push_back((Mat_ < double > (4, 1) <<  1,-1,-1, 1));
    VerticesC.push_back((Mat_ < double > (4, 1) << -1,1,1, 1));
    VerticesC.push_back((Mat_ < double > (4, 1) << -1,1,-1, 1));
    VerticesC.push_back((Mat_ < double > (4, 1) << -1,-1,1, 1));
    VerticesC.push_back((Mat_ < double > (4, 1) << -1,-1,-1, 1));
    vector <vector<int>> EdgesC; //storing all the edges (connections between the vertices) for cube
    EdgesC.push_back({0,2});
    EdgesC.push_back({5,7});
    EdgesC.push_back({2,3});
    EdgesC.push_back({0,1});
    EdgesC.push_back({1,5});
    EdgesC.push_back({4,6});
    EdgesC.push_back({6,7});
    EdgesC.push_back({0,4});
    EdgesC.push_back({4,5});
    EdgesC.push_back({3,7});
    EdgesC.push_back({1,3});
    EdgesC.push_back({2,6});
    //Now octahedron
    vector <Mat> VerticesD;
    VerticesD.push_back((Mat_ < double > (4, 1) << 1, 0, 0, 1));
    VerticesD.push_back((Mat_ < double > (4, 1) << -1, 0, 0, 1));
    VerticesD.push_back((Mat_ < double > (4, 1) << 0, 1, 0, 1));
    VerticesD.push_back((Mat_ < double > (4, 1) << 0, -1, 0, 1));
    VerticesD.push_back((Mat_ < double > (4, 1) << 0, 0, 1, 1));
    VerticesD.push_back((Mat_ < double > (4, 1) << 0, 0, -1, 1));
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
    int frames = 200; 
    double near = 0.1;
    double far = 400;
   // double d = 700; 
    double fov = 90; 
    double s = 1 / (tan((fov/2) * (CV_PI / 360)));
    
    Mat projection = (Mat_<double>(4, 4) <<
       s, 0, 0, 0,
       0, s, 0, 0,
       0, 0, (-far) / (far-near), -1,
       0, 0, (-far * near) / (far - near), 0);
    Mat translation = Mat::eye(4, 4, CV_64FC1); 
    translation.at<double>(0, 3) = 0; 
    translation.at<double>(1, 3) = 0; 
    translation.at<double>(2, 3) = 4; 
    ofstream cube3d; //coordinates.txt
    cube3d.open ("coordinates.txt");
    vector<Mat> coords3d; 
    ofstream cube2d; //coordinates2d.txt
    cube2d.open ("coordinates2d.txt");
    VideoWriter cube("rotation.avi", VideoWriter::fourcc('M', 'J', 'P', 'G'), 20, cv::Size(800, 600));
    for(int j = 0; j < frames; j++){
        if(j < 4){
            for(int i = 0; i < VerticesC.size(); i++){
                cube3d << "(" << VerticesC[i].at<double>(0, 0) << ","; 
                cube3d << VerticesC[i].at<double>(1, 0) << ","; 
                cube3d << VerticesC[i].at<double>(2, 0) << ") "; 
                Mat po = projection * translation * VerticesC[i]; //perspective projection 2d coordinates
                Point2d p(po.at<double>(0,0), po.at<double>(1,0));
                p = p/(po.at<double>(3,0)); 
                cube2d << "(" << p.x << "," << p.y << ") ";       
            }
            cube3d << "\n"; 
            cube2d << "\n"; 
        }
                
        for(int i = 0; i < EdgesC.size(); i++){
            int v1 = EdgesC[i][0]; 
            int v2 = EdgesC[i][1]; 
            Mat result1 = projection * translation * VerticesC[v1]; //rendering with perspective projection
            Mat result2 = projection * translation * VerticesC[v2];
            Point2d first(result1.at<double>(0,0), result1.at<double>(1,0));
            Point2d second(result2.at<double>(0,0), result2.at<double>(1,0));
            first = first/(result1.at<double>(3,0)); 
            second = second/(result2.at<double>(3,0)); 
            line(image, first*10 + Point2d(400, 300), second*10 + Point2d(400, 300), Scalar(255, 255, 255), 1, LINE_8);
        }
        cube.write(image); 
        image = Mat::zeros(600, 800, CV_8UC3);
        Mat rotation; 
        Vec3d rot = {0.01 * CV_PI, 0.005, 0};
        Rodrigues(rot, rotation);
        Mat rotation4 = Mat::zeros(4, 4, rotation.type());
        rotation.copyTo(rotation4(Rect(0, 0, 3, 3)));
        rotation4.at<double>(3, 3) = 1;
        for(int i = 0; i < EdgesC.size(); i++){
            int v1 = EdgesC[i][0]; 
            int v2 = EdgesC[i][1]; 
            Mat change1 = rotation4*VerticesC[v1]; //changing the coordinates based on the rotation
            Mat change2 = rotation4*VerticesC[v2];
            VerticesC[v1] = change1; 
            VerticesC[v2] = change2; 
        }    
    }
    cube3d.close();
    cube2d.close();
    //octahedron  
    for(int j = 0; j < frames; j++){
        for(int i = 0; i < EdgesD.size(); i++){
            Mat result1 = projection * translation * EdgesD[i][0];
            Mat result2 = projection * translation * EdgesD[i][1];
            Point2d first(result1.at<double>(0,0), result1.at<double>(1,0));
            Point2d second(result2.at<double>(0,0), result2.at<double>(1,0));
            first = first/(result1.at<double>(3,0)); 
            second = second/(result2.at<double>(3,0)); 
            line(image, first*10 + Point2d(400, 300), second*10 + Point2d(400, 300), Scalar(255, 255, 255), 1, LINE_8);
        }
        cube.write(image); 
        image = Mat::zeros(600, 800, CV_8UC3);
        Mat rotation; 
        Vec3d rot = {0.01 * CV_PI, 0.05, 0};
        Rodrigues(rot, rotation);
        Mat rotation4 = Mat::zeros(4, 4, rotation.type());
        rotation.copyTo(rotation4(Rect(0, 0, 3, 3)));
        rotation4.at<double>(3, 3) = 1;
        for(int i = 0; i < EdgesD.size(); i++)
        {
            Mat change1 = rotation4*EdgesD[i][0];
            Mat change2 = rotation4*EdgesD[i][1];
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
