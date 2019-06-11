#include <ros/ros.h>
#include "std_msgs/String.h"
#include <image_transport/image_transport.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
static const std::string OPENCV_WINDOW = "Image window";
sensor_msgs::ImagePtr msg;
void chatterCallback(const std_msgs::String::ConstPtr& strmsg)
{
  cv::Mat image = cv::imread(strmsg->data, CV_LOAD_IMAGE_COLOR);
  cv::circle(image, cv::Point(50, 50), 10, CV_RGB(255,0,0));

 cv::Mat gray_image;
 cv::cvtColor( image, gray_image, CV_BGR2GRAY );
  msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", image).toImageMsg();
  ROS_INFO("I heard: [%s]", strmsg->data.c_str());
}
int main(int argc, char** argv)
{
  ros::init(argc, argv, "image_publisher");
  ros::NodeHandle nh;
  int consolemode;
nh.param("consolemode", consolemode, 0);
std::cout<<"consolemode is "<<consolemode<<std::endl;
ros::Subscriber sub = nh.subscribe("imagefname", 1000, chatterCallback);
  image_transport::ImageTransport it(nh);
  image_transport::Publisher pub = it.advertise("camera/image", 1);
 if (consolemode==0){
	cv::namedWindow(OPENCV_WINDOW,CV_WINDOW_AUTOSIZE);
	}
  cv::Mat image = cv::imread(argv[1], CV_LOAD_IMAGE_COLOR);
cv::circle(image, cv::Point(50, 50), 10, CV_RGB(255,0,0));

 cv::Mat gray_image;
 cv::cvtColor( image, gray_image, CV_BGR2GRAY );

/* if (consolemode==0){
 	cv::namedWindow( argv[1], CV_WINDOW_AUTOSIZE );
	}
*/
 //cv::imshow( argv[1], image );
 //cv::imshow(OPENCV_WINDOW, image);
 //cv::waitKey(0);

  msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", image).toImageMsg();

  ros::Rate loop_rate(5);
  while (nh.ok()) {
   cv::imshow(OPENCV_WINDOW, gray_image);
   cv::waitKey(1);// 0 mean block wait for any key in image window. this seems required for 
		//opencv to update image window. however this mean msg can't be 
		//published below, use a non-zero number in this call to refresh open cv 
		// window should be used.

    pub.publish(msg);
    ros::spinOnce();
    loop_rate.sleep();
  }
}

