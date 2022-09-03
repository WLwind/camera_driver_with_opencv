#pragma once

#include <stdlib.h>
#include <memory>
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
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>

class CameraDriver
{
public:
  enum Default
  {
    DEFAULT_CAMERA_INDEX = 0,//default camera index
    DEFAULT_FPS = 30//default fps
  };

  CameraDriver(ros::NodeHandle& nh, int camera_index = DEFAULT_CAMERA_INDEX);
  ~CameraDriver();
  void capture();//capture the image by polling
  void setFps(double fps);//set fps
  double getFps() const;

private:
  ros::NodeHandle& nh_;
  image_transport::ImageTransport it {nh_};
  image_transport::Publisher pub_image_raw {it.advertise("image", 1)};

  int camera_index {0};
  double fps {30.0};
  bool upside_down {false};//whether your camera is set upside down

  cv::VideoCapture camera;
  cv::Mat image;
  cv_bridge::CvImagePtr frame {boost::make_shared<cv_bridge::CvImage>()};

  ros::Time last{0};
  ros::Duration period{ros::Duration(1.0/fps)};
};
