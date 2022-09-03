#include <thread>
#include <mutex>
#include <condition_variable>
#include <camera_driver_with_opencv/camera_driver.h>

void publish_image(
    CameraDriver& camera,
    std::mutex& mt,
    std::condition_variable& cv,
    double duration)
{
    while(ros::ok())
    {
        std::unique_lock<std::mutex> lock(mt);
        if (cv.wait_for(
            lock,
            std::chrono::milliseconds(int(duration * 1000))) != std::cv_status::timeout)
        {
            break;
        }
        camera.capture();
    }
    return;
}

int main(int argc, char* argv[])
{
    ros::init(argc, argv, "camera_driver_with_opencv");
    ros::NodeHandle nh("~");
    int camera_index;
    nh.param<int>("camera_index", camera_index, 0);
    CameraDriver camera_driver(nh, camera_index);
    if (!ros::ok())
    {
        return 1;
    }
    if(argc > 1)
    {
        camera_driver.setFps(atoi(argv[1]));
        ROS_INFO("Set fps to %d", atoi(argv[1]));
    }
    ROS_INFO("The camera starts working.");

    std::mutex thread_mutex;
    std::condition_variable timer_cv;
    std::thread get_image_thread(
        &publish_image,
        std::ref(camera_driver),
        std::ref(thread_mutex),
        std::ref(timer_cv),
        1.0 / camera_driver.getFps());
    ros::spin();
    timer_cv.notify_all();
    get_image_thread.join();
    return 0;
}
