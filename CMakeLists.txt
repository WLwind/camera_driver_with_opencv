cmake_minimum_required(VERSION 2.8.3)
project(camera_driver_with_opencv)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++17)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  cv_bridge
  image_transport
  roscpp
  rospy
  sensor_msgs
  std_msgs
)

find_package(OpenCV REQUIRED)

###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if your package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES camera_driver_with_opencv
#  CATKIN_DEPENDS cv_bridge image_transport roscpp rospy sensor_msgs std_msgs
#  DEPENDS system_lib
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
)

add_executable(camera_polling_node
  src/camera_polling.cpp
  src/camera_driver.cpp
)
add_dependencies(camera_polling_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(camera_polling_node
  ${catkin_LIBRARIES}
  ${OpenCV_LIBRARIES}
)
add_executable(camera_node
  src/camera_node.cpp
  src/camera_driver.cpp
)
add_dependencies(camera_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(camera_node
  ${catkin_LIBRARIES}
  ${OpenCV_LIBRARIES}
)
