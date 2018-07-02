cmake_minimum_required(VERSION 2.8.3)
project(invert_laser)
add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
        roscpp
        sensor_msgs
        )

catkin_package(
        #  INCLUDE_DIRS include
        #  LIBRARIES invert_laser
        #  CATKIN_DEPENDS roscpp sensor_msgs
        #  DEPENDS system_lib
)

include_directories(
        # include
        ${catkin_INCLUDE_DIRS}
)
add_executable(${PROJECT_NAME}_node src/invert_laser_node.cpp)
add_dependencies(${PROJECT_NAME}_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(${PROJECT_NAME}_node
        ${catkin_LIBRARIES}
        )

