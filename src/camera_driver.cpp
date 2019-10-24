#include <camera_driver_with_opencv/camera_driver.h>

CameraDriver::CameraDriver(int camera_index):camera_index(camera_index),camera(camera_index)
{
    nh.param<int>("camera_index", camera_index, DEFAULT_CAMERA_INDEX);
    nh.param<int>("fps", fps, DEFAULT_FPS);

    if(!camera.isOpened())
    {
        ROS_ERROR_STREAM( "Failed to open camera device!" );
        ros::shutdown();
    }

    period = ros::Duration(1.0/fps);//period
    frame->encoding = sensor_msgs::image_encodings::BGR8;//encode to format BGR8
}

CameraDriver::~CameraDriver()
{
    camera.release();
}

void CameraDriver::capture()
{
    camera >> frame->image;	// blocking, so it frees the CPU.
    if ( frame->image.empty() )
    {
        ROS_ERROR_STREAM( "Failed to retrive new frame! " );
        ros::shutdown();
    }

    ros::Time now = ros::Time::now();
    if ( ( now - last ) >= period )
    {
//        cv::flip(frame->image,frame->image,-1);//if your camera is upside down
        frame->header.stamp = now;
        pub_image_raw.publish( frame->toImageMsg() );//publish image topic
        last = now;
    }
}

void CameraDriver::setFps(int f)
{
    fps= f;
    period = ros::Duration(1.0/fps);//calculate period
}
