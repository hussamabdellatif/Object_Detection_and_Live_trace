#include <iostream> // for standard I/O
#include <string>   // for strings
#include <iomanip>  // for controlling float print precision
#include <sstream>  // string to number conversion
#include <opencv2/core.hpp>     // Basic OpenCV structures (cv::Mat, Scalar)
#include <opencv2/imgproc.hpp>  // Gaussian Blur
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>  // OpenCV window I/O
#include <vector>
using namespace std;
using namespace cv;

int main(int argc,  char* argv[]){
    Mat frame, ret, hsv, frame_threshold ,frame_threshold1,frame_threshold2;
    vector<vector<Point> > contour;
    vector<Vec4i> hierarchy;
    int centroid_x = 0;
    int centroid_y = 0;
    VideoCapture cap;
    int device_id = 0 , apiid = 0;
    cap.open(device_id + apiid);
    if(!cap.isOpened()) return -1;
    while(cap.isOpened()){
        cap.read(ret);
        flip(ret, frame, 1);
        if(frame.empty()) break;
        namedWindow("original", WINDOW_NORMAL);
        cvtColor(frame, hsv, COLOR_BGR2HSV);
        inRange(hsv, Scalar(30,150,50), Scalar(255,255,180), frame_threshold1);
        //inRange(hsv, Scalar(170, 70, 50), Scalar(180, 255, 255), frame_threshold2);
        //frame_threshold = frame_threshold1 | frame_threshold2;
        findContours(frame_threshold1,contour, hierarchy,1,2);
        double max_area = 0;
        int last_x = centroid_x;
        int last_y = centroid_y;
        size_t index = 0;
        Scalar color = Scalar( 250,0,0);
        Scalar color2 = Scalar( 0,0,250);
        if(!contour.empty()){
        for(size_t i=0; i<contour.size();i++){
            double area = contourArea(contour[i]);
            if(area>max_area){max_area = area;index = i;}
        }
        Rect bounding_rec = boundingRect(contour[index]);
        rectangle(frame, bounding_rec.tl(), bounding_rec.br(), color, 2);
        centroid_x = (bounding_rec.x + bounding_rec.x + bounding_rec.width) / 2;
        centroid_y = (bounding_rec.y + bounding_rec.y + bounding_rec.height) / 2;
        circle(frame, Point(centroid_x,centroid_y), 2, color, 4);
        }
        line(frame, Point(400,0),Point(400,700), color2, 7);
        line(frame, Point(900,0),Point(900,700), color2, 7);
        line(frame, Point(400,350),Point(900,350), color2, 7);
        imshow("Live", frame);
        if(centroid_x > last_x && ((centroid_x - last_x) > 1) && ((centroid_x - last_x) < 5) ) cout<<"Moving Left"<<endl;
        if(centroid_x < last_x && ((last_x-centroid_x)  > 1)   && ((last_x - centroid_x) < 5) ) cout<<"Moving Right"<<endl;
        if(centroid_y > last_y && ((centroid_y - last_y) > 1) && ((centroid_y -last_y) < 5) )cout<<"Moving down"<<endl;
        if(centroid_y < last_y && ((last_y-centroid_y)  > 1) && ((last_y-centroid_y) < 5) ) cout<<"Moving up"<<endl;

        if (waitKey(5) >= 0) break;
    }
    return 0;
}
