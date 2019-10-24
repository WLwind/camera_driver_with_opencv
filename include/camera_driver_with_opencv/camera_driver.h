#pragma once

#include <stdlib.h>
#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
/*
#include <opencv2/core/core.hpp>//for OpenCV2
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
*/
//for OpenCV3
#include <opencv2/core.hpp>
#include <opencv/highgui.h>
#include <opencv2/opencv.hpp>

class CameraDriver
{
public:
  enum Default
  {
    DEFAULT_CAMERA_INDEX = 0,//default camera index
    DEFAULT_FPS = 30//default fps
  };

  CameraDriver(int camera_index = DEFAULT_CAMERA_INDEX);
  ~CameraDriver();
  void capture();//capture the image by polling
  void setFps(int);//set fps

private:
  ros::NodeHandle nh{"~"};
  image_transport::ImageTransport it{nh};
  image_transport::Publisher pub_image_raw{it.advertise("image_raw", 1)};

  int camera_index{0};
  int fps{30};

  cv::VideoCapture camera;
  cv::Mat image;
  cv_bridge::CvImagePtr frame{boost::make_shared<cv_bridge::CvImage>()};

  ros::Time last{0};
  ros::Duration period{ros::Duration(1.0/fps)};
};
