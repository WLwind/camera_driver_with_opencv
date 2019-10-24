#include <camera_driver_with_opencv/camera_driver.h>

int main(int argc, char* argv[])
{
    ros::init(argc, argv, "camera_driver_with_opencv");
    CameraDriver camera_driver;
    if(argc>1)
    {
        camera_driver.setFps(atoi(argv[1]));
        ROS_INFO("Set fps to %d",atoi(argv[1]));
    }
    ROS_INFO("The camera starts working.");

    while( ros::ok() )
    {
        camera_driver.capture();
        ros::spinOnce();
    }

    return EXIT_SUCCESS;
}
