# camera_driver_with_opencv
A ROS package for publishing image topics from a rgb camera.  
This package uses a simple polling way with OpenCV tools to capture images from /dev/videoX device and publish them to ROS. We have tested this with Raspbery Pi camera and Orbbec Astra pro.
## Launch files
* camera_polling.launch
Launch the polling node to capture images.
### Parameters
* fps  
Frame rate (f/s).
* camera_index  
The device number of /dev/videoX. If you plug in Astra pro, there will be 2 video devices displayed, and the 2nd(/dev/video1) one is rgb device.
* view  
Whether you want to view the image stream using image_view tool.
* save  
Whether you want to save the image stream using rosbag tool.
* upside_down  
If your camera is set upside down, setting this to true will flip the images vertically.
## Examples
`roslaunch camera_driver_with_opencv camera_polling.launch camera_index:=1 fps:=30 view:=false save:=true upside_down:=true`