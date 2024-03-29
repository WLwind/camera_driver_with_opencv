#include <camera_driver_with_opencv/camera_driver.h>

CameraDriver::CameraDriver(ros::NodeHandle& nh, int camera_index)
: nh_(nh), camera_index(camera_index), camera(camera_index)
{
    nh_.param<int>("camera_index", camera_index, DEFAULT_CAMERA_INDEX);
    nh_.param<double>("fps", fps, DEFAULT_FPS);
    nh_.param<bool>("upside_down", upside_down, upside_down);

    if(!camera.isOpened())
    {
        ROS_ERROR("Failed to open camera device!");
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
    if (frame->image.empty())
    {
        ROS_ERROR("Failed to retrive new frame!");
        ros::shutdown();
    }

    ros::Time now = ros::Time::now();
    if (now - last >= period)
    {
        if(upside_down)
        {
            cv::flip(frame->image,frame->image,-1);//if your camera is upside down, then flip the images
        }
        frame->header.stamp = now;
        pub_image_raw.publish(frame->toImageMsg());//publish image topic
        last = now;//set current time mark
    }
}

void CameraDriver::setFps(double f)
{
    fps = f;
    period = ros::Duration(1.0 / fps);//calculate period
}

double CameraDriver::getFps() const
{
    return fps;
}
