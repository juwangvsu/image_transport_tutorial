cmake_minimum_required(VERSION 2.8.3)
project(image_transport_tutorial)
add_definitions(-std=c++11)
find_package(catkin REQUIRED COMPONENTS
  image_transport
  roscpp
  sensor_msgs
  cv_bridge
  message_generation
  nodelet
  std_msgs
)
find_package(cmake_modules REQUIRED)
find_package(Eigen REQUIRED)

# add the resized image message
add_message_files(
   FILES ResizedImage.msg
)
generate_messages(DEPENDENCIES sensor_msgs)
catkin_package(
  INCLUDE_DIRS include
  CATKIN_DEPENDS image_transport roscpp sensor_msgs geometry_msgs cv_bridge message_runtime std_msgs 
  DEPENDS Eigen
)


#find_package(OpenCV 3 REQUIRED)
find_package(OpenCV 3 REQUIRED
  COMPONENTS
    opencv_core
    opencv_imgproc
    opencv_imgcodecs
    opencv_highgui
  CONFIG
)
include_directories(include ${OpenCV_INCLUDE_DIRS})
include_directories(
  ${Eigen_INCLUDE_DIRS}
  ${catkin_INCLUDE_DIRS}
)
add_library(resized_publisher src/manifest.cpp src/resized_publisher.cpp src/resized_subscriber.cpp)
target_link_libraries(resized_publisher ${catkin_LIBRARIES} ${OpenCV_LIBRARIES} ${OpenCV_LIBS} )

add_dependencies(resized_publisher image_transport_tutorial_generate_messages_cpp)

# add the publisher example
add_executable(my_publisher src/my_publisher.cpp)
target_link_libraries(my_publisher ${catkin_LIBRARIES} ${OpenCV_LIBRARIES} ${OpenCV_LIBS})

#add_dependencies(my_subscriber image_transport_tutorial_generate_messages_cpp)
# add the subscriber example
add_executable(my_subscriber src/my_subscriber.cpp)
target_link_libraries(my_subscriber ${catkin_LIBRARIES} ${OpenCV_LIBRARIES} ${OpenCV_LIBS} -lopencv_highgui)

# add the plugin examples
#install(DIRECTORY include/apriltags_ros
#  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
#)

