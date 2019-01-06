//g++ main.cpp Screen.cpp Swarm.cpp Particle.cpp -o testing -I/Library/Frameworks/SDL2.framework/Headers -F/Library/Frameworks -framework SDL2
#include "Screen.h"
#include <iostream>
#include <stdlib.h>
#include <SDL.h>
#include <chrono>
#include <random>
#include <iostream>
#include <iomanip>
#include <math.h>
#include <time.h>
#include "Swarm.h"
#include <iomanip>  // for controlling float print precision
#include <sstream>  // string to number conversion
#include <opencv2/core.hpp>     // Basic OpenCV structures (cv::Mat, Scalar)
#include <opencv2/imgproc.hpp>  // Gaussian Blur
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>  // OpenCV window I/O
#include <vector>

using namespace std;
using namespace cv;

int main(){
    srand(time(NULL));
    string text1,text2;
    Screen screen;
    long long delay = 0; //Delays the start of the software for calibration
    if(!screen.init()) cout<<"Error"<<endl;
    Swarm swarm;
    int velocity_x =0,velocity_y =0;
    Mat frame, ret, hsv, frame_threshold ,frame_threshold1,frame_threshold2; //Mat objects for image detection
    vector<vector<Point> > contour;
    vector<Vec4i> hierarchy;
    int centroid_x = 0,centroid_y = 0;
    VideoCapture cap;
    int device_id = 0 , apiid = 0;
    cap.open(device_id + apiid);
    if(!cap.isOpened()) return -1;
    while(true){ //infinite loop
        cap.read(ret);
        flip(ret, frame, 1);
        if(frame.empty()) break;
        namedWindow("original", WINDOW_NORMAL);
        cvtColor(frame, hsv, COLOR_BGR2HSV);
        inRange(hsv, Scalar(30,150,50), Scalar(255,255,180), frame_threshold1); //find blue object
        //inRange(hsv, Scalar(170, 70, 50), Scalar(180, 255, 255), frame_threshold2);
        //frame_threshold = frame_threshold1 | frame_threshold2;
        findContours(frame_threshold1,contour, hierarchy,1,2);
        double max_area = 0;
        int last_x = centroid_x;
        int last_y = centroid_y;
        size_t index = 0;
        if(!contour.empty()){
        for(size_t i=0; i<contour.size();i++){
            double area = contourArea(contour[i]);
            if(area>max_area){max_area = area;index = i;}
        }
        Rect bounding_rec = boundingRect(contour[index]);
        rectangle(frame, bounding_rec.tl(), bounding_rec.br(), Scalar( 250,0,0), 2);
        centroid_x = (bounding_rec.x + bounding_rec.x + bounding_rec.width) / 2;
        centroid_y = (bounding_rec.y + bounding_rec.y + bounding_rec.height) / 2;
        circle(frame, Point(centroid_x,centroid_y), 2, Scalar( 250,0,0), 4);
        }
        if(!text1.empty() || !text2.empty())
            cv::putText(frame, (("Moving: ")+text1+text2), Point(30,30), 1, 2, Scalar(0,250,0), 3, LINE_8);

        imshow("Live", frame);
        /*left and right motion*/
        double cons = 0.01;
        if( abs(centroid_x - last_x) > cons  ){
            if(centroid_x - last_x < 0){ // move left
                if( (((last_x-centroid_x)  > cons)) && ((last_x - centroid_x) < 20)){
                    velocity_x = -2;
                    text1 = "Left";
                }else{
                    velocity_x = 0;
                    text1 = " ";
                }
            }else{ //move right
                if( (((centroid_x-last_x)  > cons)) && ((centroid_x-last_x  ) < 20)){
                    velocity_x = 2;
                    text1 = "Right";
                }else{
                    velocity_x = 0;
                    text1 = " ";
                }
            }
        }else{
            velocity_x = 0;
            text1 = " ";
        }

        /*UP and DOWN Motion*/
        if( abs(centroid_y - last_y) > cons  ){
            if(centroid_y - last_y < 0){ // move up
                if( (((last_y-centroid_y)  > cons)) && ((last_y - centroid_y) < 40)){
                    velocity_y = -2;
                    text2  = " Up";
                }
                else{
                    velocity_y = 0;
                    text2 = " ";
                }
            }else{ //move down
                if( (((centroid_y-last_y)  > cons)) && ((centroid_y-last_y  ) < 40)) {
                    velocity_y = 2;
                    text2 = " Down";
                }else {
                    velocity_y = 0;
                    text2 =" ";
                }
            }
        }else{
            velocity_y = 0;
            text2 = " ";
        }

        if (waitKey(5) >= 0) break;
        Particle *pP = swarm.getParticles();
        int v1 = (rand() % 255 ) ;
        int v2 = (rand() % 255 ) ;
        int v3 = (rand() % 255 ) ;
        swarm.update(velocity_x,velocity_y);
         for(int i=0;i<Swarm::NPARTICLES;i++){
            Particle particle = pP[i];
            int x = (particle.m_x  ); //+ 1) *  Screen::SCREEN_WIDTH/2;
            int y = (particle.m_y );// + 1) *  Screen::SCREEN_HEIGHT/2;
            screen.setPixel(x,y,v1,v2,v3);
         }

        if(screen.processEvents()) break;
        screen.update();
        while(delay < 10000000) delay++;
    }
    screen.close();
    return 0;
}
