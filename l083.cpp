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

void part3(int argc, char** argv){
    
    vector <Mat> VerticesC; //storing all 8 vertices in a Mat vector for cube
    VerticesC.push_back((Mat_ < double > (3, 1) << 1,1,1));
    VerticesC.push_back((Mat_ < double > (3, 1) << 1,1,-1));
    VerticesC.push_back((Mat_ < double > (3, 1) << 1,-1,1));
    VerticesC.push_back((Mat_ < double > (3, 1) <<  1,-1,-1));
    VerticesC.push_back((Mat_ < double > (3, 1) << -1,1,1));
    VerticesC.push_back((Mat_ < double > (3, 1) << -1,1,-1));
    VerticesC.push_back((Mat_ < double > (3, 1) << -1,-1,1));
    VerticesC.push_back((Mat_ < double > (3, 1) << -1,-1,-1));
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
    
    ofstream logs; //coordinates.txt
    logs.open ("log.txt");
    
    Mat_ <double>a = (Mat_ <double> (3, 1) << 0, 0, 7); 
    Mat_ <double>n = (Mat_ <double> (3, 1) << 0, 0, 1); 
    Mat_ <double>e = (Mat_ <double> (3, 1) << 0, 0, 2); 
    for (int i = 0; i < argc; i++)
        {
            if(strcmp(argv[i], "-a") == 0){
                double aa, b, c; 
                string s = argv[i+1];    
                stringstream ss(s);  
                string word;
                int count = 1; 
                while (getline(ss, word, ',')) { 
                    if(count == 1){
                        string noparen = word.substr(1);
                        aa = stod(noparen); 
                    }
                    if(count == 2){
                        b = stod(word);   
                    }
                    if(count == 3){
                        string noparen = word.substr(0, word.size()-1);
                        c = stod(noparen);   
                    }                    
                    count ++;
                }
                a = (Mat_ <double> (3, 1) << aa, b, c);
            }
            if(strcmp(argv[i], "-n") == 0){
                double aa, b, c;
                string s = argv[i+1]; 
                stringstream ss(s);  
                string word;
                int count = 1; 
                while (getline(ss, word, ',')) { 
                    if(count == 1){
                        string noparen = word.substr(1);
                        aa = stod(noparen); 
                    }
                    if(count == 2){
                        b = stod(word);   
                    }
                    if(count == 3){
                        string noparen = word.substr(0, word.size()-1);
                        c = stod(noparen);   
                    }                    
                    count ++;
                }
                n = (Mat_ <double> (3, 1) << aa, b, c);
            }
            if(strcmp(argv[i], "-e") == 0){
                double aa, b, c;
                string s = argv[i+1]; 
                stringstream ss(s);  
                string word;
                int count = 1; 
                while (getline(ss, word, ',')) { 
                    if(count == 1){
                        string noparen = word.substr(1);
                        aa = stod(noparen); 
                    }
                    if(count == 2){
                        b = stod(word);   
                    }
                    if(count == 3){
                        string noparen = word.substr(0, word.size()-1);
                        c = stod(noparen);   
                    }                    
                    count ++;
                }
                e = (Mat_ <double> (3, 1) << aa, b, c);
            }
    }
    logs << "The plane defined by (x-a)*n =0 is:" << "\n"; 
    
    logs << "a = " << "(" << a.at<double>(0, 0) << ","; 
    logs << a.at<double>(1, 0) << ","; 
    logs << a.at<double>(2, 0) << ") " << "\n"; 
    
    logs << "n = " << "(" << n.at<double>(0, 0) << ","; 
    logs << n.at<double>(1, 0) << ","; 
    logs << n.at<double>(2, 0) << ") " << "\n"; 
    
    logs << "e = " << "(" << e.at<double>(0, 0) << ","; 
    logs << e.at<double>(1, 0) << ","; 
    logs << e.at<double>(2, 0) << ") " << "\n"; 
    
    Mat_ <double>pv1 = (((a-e).dot(n))/((VerticesC[0]*50-e).dot(n)))*(VerticesC[0]*50-e) + e; 
    Mat_ <double>pv2 = (((a-e).dot(n))/((VerticesC[1]*50-e).dot(n)))*(VerticesC[1]*50-e) + e;
    Mat_ <double>pv3 = (((a-e).dot(n))/((VerticesC[2]*50-e).dot(n)))*(VerticesC[2]*50-e) + e;
    
    logs << "Vertices I used to create he 2d coordinate system and their projections are:" << "\n";
    
    logs << "v1 = " << "(" << VerticesC[0].at<double>(0, 0) * 50 << ","; 
    logs << VerticesC[0].at<double>(1, 0) * 50  << ","; 
    logs << VerticesC[0].at<double>(2, 0) * 50  << ") " << "\n"; 
    
    logs << "v2 = " << "(" << VerticesC[1].at<double>(0, 0) * 50 << ","; 
    logs << VerticesC[1].at<double>(1, 0) * 50 << ","; 
    logs << VerticesC[1].at<double>(2, 0) * 50 << ") " << "\n"; 
    
    logs << "v3 = " << "(" << VerticesC[2].at<double>(0, 0) * 50 << ","; 
    logs << VerticesC[2].at<double>(1, 0) * 50 << ","; 
    logs << VerticesC[2].at<double>(2, 0) * 50 << ") " << "\n"; 
    
    logs << "pv1 = " << "(" << pv1.at<double>(0, 0) * 50<< ","; 
    logs << pv1.at<double>(1, 0) * 50  << ","; 
    logs << pv1.at<double>(2, 0) * 50  << ") " << "\n"; 
    
    logs << "pv2 = " << "(" << pv2.at<double>(0, 0) << ","; 
    logs << pv2.at<double>(1, 0) << ","; 
    logs << pv2.at<double>(2, 0) << ") " << "\n"; 
    
    logs << "pv3 = " << "(" << pv3.at<double>(0, 0) << ","; 
    logs << pv3.at<double>(1, 0) << ","; 
    logs << pv3.at<double>(2, 0) << ") " << "\n"; 
    
    
    Mat_ <double>v1 = pv1 - pv2; 
    Mat_ <double>a2 = pv3 - pv1; 
    
    logs << "The 2 vectors a and b that are in plane are:" << "\n"; 
    
    logs << "a = pv1-pv2 = " << "(" << v1.at<double>(0, 0) << ","; 
    logs << v1.at<double>(1, 0) << ","; 
    logs << v1.at<double>(2, 0) << ") " << "\n"; 
    
    logs << "b = pv3-pv1 = " << "(" << a2.at<double>(0, 0) << ","; 
    logs << a2.at<double>(1, 0) << ","; 
    logs << a2.at<double>(2, 0) << ") " << "\n"; 
      
    Mat_ <double>v2 = a2 - ((a2.dot(v1))/(v1.dot(v1)))*v1; 
    
    double sum = (v1.at<double>(0, 0))*(v1.at<double>(0, 0)) +  (v1.at<double>(1, 0))*(v1.at<double>(1, 0)) + (v1.at<double>(2, 0))*(v1.at<double>(2, 0)); 
    
    double sum1 = (v2.at<double>(0, 0))*(v2.at<double>(0, 0)) +  (v2.at<double>(1, 0))*(v2.at<double>(1, 0)) + (v2.at<double>(2, 0))*(v2.at<double>(2, 0)); 
    
    Mat_ <double>w1 = (Mat_ <double> (3, 1) << (v1.at<double>(0, 0))/sqrt(sum),(v1.at<double>(1, 0))/sqrt(sum),(v1.at<double>(2, 0))/sqrt(sum));
    
    Mat_ <double>w2 = (Mat_ <double> (3, 1) << (v2.at<double>(0, 0))/sqrt(sum),(v2.at<double>(1, 0))/sqrt(sum),(v2.at<double>(2, 0))/sqrt(sum));
    
    logs << "The w1 and w2 obtained from a and b (these now are perpendicular and of magnitude 1) are: "<< "\n";
    
    logs << "w1 = " << "(" << w1.at<double>(0, 0) << ","; 
    logs << w1.at<double>(1, 0) << ","; 
    logs << w1.at<double>(2, 0) << ") " << "\n"; 
    
    logs << "w2 = " << "(" << w2.at<double>(0, 0) << ","; 
    logs << w2.at<double>(1, 0) << ","; 
    logs << w2.at<double>(2, 0) << ") " << "\n"; 
    
    
    Mat_ <double>pp = (Mat_ <double> (3, 1) << 0,0,0); 
    
    Mat_ <double>p0 = (((a-e).dot(n))/((pp-e).dot(n)))*(pp-e) + e;
    
    logs << "The center of the cube in first frame and its projection are: " << "\n"; 
    
    logs << "center = " << "(" << pp.at<double>(0, 0) << ","; 
    logs << pp.at<double>(1, 0) << ","; 
    logs << pp.at<double>(2, 0) << ") " << "\n"; 
    
    logs << "p0 = " << "(" << p0.at<double>(0, 0) << ","; 
    logs << p0.at<double>(1, 0) << ","; 
    logs << p0.at<double>(2, 0) << ") " << "\n"; 
    
    logs << "The coordinates in the 2d plane x = p0 + u*w1 + v*w2 are:(where p0 is the origin, preferraby the projection of the center of the cube in first frame, w1 and w2 are 2 perpendicular vertices in the plane)" << "\n";
    
    logs << "p0 = " << "(" << p0.at<double>(0, 0) << ","; 
    logs << p0.at<double>(1, 0) << ","; 
    logs << p0.at<double>(2, 0) << ") " << "\n"; 
    
    logs << "w1 = " << "(" << w1.at<double>(0, 0) << ","; 
    logs << w1.at<double>(1, 0) << ","; 
    logs << w1.at<double>(2, 0) << ") " << "\n"; 
    
    logs << "w2 = " << "(" << w2.at<double>(0, 0) << ","; 
    logs << w2.at<double>(1, 0) << ","; 
    logs << w2.at<double>(2, 0) << ") " << "\n"; 

    Mat_<double> projections = (Mat_ <double> (3, 3) << (p0.at<double>(0, 0)), (w1.at<double>(0, 0)), (w2.at<double>(0, 0)),
                               (p0.at<double>(1, 0)), (w1.at<double>(1, 0)), (w2.at<double>(1, 0)),
                               (p0.at<double>(2, 0)), (w1.at<double>(2, 0)), (w2.at<double>(2, 0))); 
    
    ofstream cube3d; //coordinates.txt
    cube3d.open ("coordinates.txt");
    ofstream cube2d; //coordinates2d.txt
    cube2d.open ("coordinates2d.txt");
    Mat image(600, 800, CV_8UC3, Scalar(0, 0, 0)); 
    int frames = 200; 
    VideoWriter cube("rotation.avi", VideoWriter::fourcc('M', 'J', 'P', 'G'), 20, cv::Size(800, 600));
    for(int j = 0; j < frames; j++){   
        if(j < 4){
              logs << "The frame" << j+1 << " in 3d has the following edges: (should be 12 edges, 12 pairs of 3d coordinates (x,y,z))" << "\n";
                for(int i = 0; i < VerticesC.size(); i++){
                    cube3d << "(" << VerticesC[i].at<double>(0, 0) * 50 << ","; 
                    cube3d << VerticesC[i].at<double>(1, 0) * 50 << ","; 
                    cube3d << VerticesC[i].at<double>(2, 0) * 50 << ") "; 
                    int v1 = EdgesC[i][0]; 
                    Mat result1; //rendering with perspective projection
                    solve(projections, VerticesC[i]*50, result1); 
                    cube2d << "(" << result1.at<double>(1,0) << "," << result1.at<double>(2,0) << ") ";       
            }
            cube3d << "\n"; 
            cube2d << "\n"; 
        }
        
        for(int i = 0; i < EdgesC.size(); i++){
            int v1 = EdgesC[i][0]; 
            int v2 = EdgesC[i][1]; 
            Mat result1; //rendering with perspective projection
            Mat result2;
            solve(projections, VerticesC[v1]*50, result1); 
            solve(projections, VerticesC[v2]*50, result2); 
            Point2d first(result1.at<double>(1,0), result1.at<double>(2,0));
            Point2d second(result2.at<double>(1,0), result2.at<double>(2,0));
            if(j < 4){
                logs << "(" << VerticesC[v1].at<double>(0, 0) * 50 << ","; 
                logs << VerticesC[v1].at<double>(1, 0) * 50 << ","; 
                logs << VerticesC[v1].at<double>(2, 0) * 50 << ") ";
                logs << ", " << "(" << VerticesC[v2].at<double>(0, 0) * 50 << ","; 
                logs << VerticesC[v2].at<double>(1, 0) * 50 << ","; 
                logs << VerticesC[v2].at<double>(2, 0) * 50 << ") ";
                logs << "\n"; 
            }
            line(image, first + Point2d(400, 300), second + Point2d(400, 300), Scalar(255, 255, 255), 1, LINE_8);
            circle(image, first + Point2d(400, 300),3, Scalar(255, 255, 255), 1);
            circle(image, second + Point2d(400, 300),3, Scalar(255, 255, 255), 1);
        }
        cube.write(image); 
        image = Mat::zeros(600, 800, CV_8UC3);
        Mat rotation; 
        Vec3d rot = {0.01 * CV_PI, 0.005, 0};
        Rodrigues(rot, rotation);
        if(j < 4){
            logs << "The frame" << j+1 <<" in 2d has the following edges: (should be 12 edges, 12 pairs of 2d coordinates (u,v), if the vertices do not cross the plane these are the projections of the 3d points on the plane)" << "\n"; 
            for(int i = 0; i < EdgesC.size(); i++){
                int v1 = EdgesC[i][0]; 
                int v2 = EdgesC[i][1]; 
                Mat result1; //rendering with perspective projection
                Mat result2;
                solve(projections, VerticesC[v1]*50, result1); 
                solve(projections, VerticesC[v2]*50, result2); 
                logs << "(" << result1.at<double>(1,0) << ","; 
                logs << result1.at<double>(2,0) << ") ";
                logs << ", (" << result2.at<double>(1,0) << ","; 
                logs << result2.at<double>(2,0) << ") ";
                logs << "\n"; 
        }
        }
        for(int i = 0; i < EdgesC.size(); i++){
            int v1 = EdgesC[i][0]; 
            int v2 = EdgesC[i][1]; 
            Mat change1 = rotation*VerticesC[v1]; //changing the coordinates based on the rotation
            Mat change2 = rotation*VerticesC[v2];
            VerticesC[v1] = change1; 
            VerticesC[v2] = change2; 
        }    
    }
    logs.close(); 
    cube2d.close();
    cube3d.close(); 
    
    //octahedron
    Mat_ <double>pv11 = (((a-e).dot(n))/((VerticesD[0]*50-e).dot(n)))*(VerticesD[0]*50-e) + e; 
    Mat_ <double>pv22 = (((a-e).dot(n))/((VerticesD[1]*50-e).dot(n)))*(VerticesD[1]*50-e) + e;
    Mat_ <double>pv33 = (((a-e).dot(n))/((VerticesD[2]*50-e).dot(n)))*(VerticesD[2]*50-e) + e;
    
    Mat_ <double>v11 = pv11 - pv22; 
    Mat_ <double>a22 = pv33 - pv11; 
      
    Mat_ <double>v22 = a22 - ((a22.dot(v11))/(v11.dot(v11)))*v11; 
    
    double summ = (v11.at<double>(0, 0))*(v11.at<double>(0, 0)) +  (v11.at<double>(1, 0))*(v11.at<double>(1, 0)) + (v11.at<double>(2, 0))*(v11.at<double>(2, 0)); 
    
    double sum11 = (v22.at<double>(0, 0))*(v22.at<double>(0, 0)) +  (v22.at<double>(1, 0))*(v22.at<double>(1, 0)) + (v22.at<double>(2, 0))*(v22.at<double>(2, 0)); 
    
    Mat_ <double>w11 = (Mat_ <double> (3, 1) << (v11.at<double>(0, 0))/sqrt(summ),(v11.at<double>(1, 0))/sqrt(summ),(v11.at<double>(2, 0))/sqrt(summ));
    
    Mat_ <double>w22 = (Mat_ <double> (3, 1) << (v2.at<double>(0, 0))/sqrt(sum11),(v22.at<double>(1, 0))/sqrt(sum11),(v22.at<double>(2, 0))/sqrt(sum11));
    
    Mat_ <double>ppp = (Mat_ <double> (3, 1) << 0,0,0); 
    
    Mat_ <double>p00 = (((a-e).dot(n))/((ppp-e).dot(n)))*(ppp-e) + e;
   
    Mat_<double> projections1 = (Mat_ <double> (3, 3) << (p00.at<double>(0, 0)), (w11.at<double>(0, 0)), (w22.at<double>(0, 0)),
                               (p00.at<double>(1, 0)), (w11.at<double>(1, 0)), (w22.at<double>(1, 0)),
                               (p00.at<double>(2, 0)), (w11.at<double>(2, 0)), (w22.at<double>(2, 0))); 
    
    for(int j = 0; j < frames; j++){   
        for(int i = 0; i < EdgesD.size(); i++){
            Mat result1; //rendering with perspective projection
            Mat result2;
            solve(projections, EdgesD[i][0]*50, result1); 
            solve(projections, EdgesD[i][1]*50, result2); 
            Point2d first(result1.at<double>(1,0), result1.at<double>(2,0));
            Point2d second(result2.at<double>(1,0), result2.at<double>(2,0));
            line(image, first + Point2d(400, 300), second + Point2d(400, 300), Scalar(255, 255, 255), 1, LINE_8);
            circle(image, first + Point2d(400, 300),3, Scalar(255, 255, 255), 1);
            circle(image, second + Point2d(400, 300),3, Scalar(255, 255, 255), 1);
        }
        cube.write(image); 
        image = Mat::zeros(600, 800, CV_8UC3);
        Mat rotation; 
        Vec3d rot = {0.01 * CV_PI, 0.005, 0};
        Rodrigues(rot, rotation);
        for(int i = 0; i < EdgesD.size(); i++){
            Mat change1 = rotation*EdgesD[i][0]; //changing the coordinates based on the rotation
            Mat change2 = rotation*EdgesD[i][1];
            EdgesD[i] = {change1, change2};
        }    
    }   
    
    waitKey(0);
    
}

int main(int argc, char** argv)
{
    part3(argc, argv); 
    return 0;
}
