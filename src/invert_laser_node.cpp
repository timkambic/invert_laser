
#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"


ros::Publisher laser_pub;

void scanCB(const sensor_msgs::LaserScan::ConstPtr &msg){

	sensor_msgs::LaserScan msg_out;
	msg_out.header = msg->header;
	msg_out.header.frame_id = "laser";
	msg_out.angle_min = msg->angle_min;
	msg_out.angle_max = msg->angle_max;
	msg_out.angle_increment = msg->angle_increment;
	msg_out.time_increment = msg->time_increment;
	msg_out.scan_time = msg->scan_time;
	msg_out.range_max = msg->range_max;
	msg_out.range_min = msg->range_min;

	msg_out.ranges = msg->ranges;
	msg_out.intensities = msg->intensities;

	std::reverse(msg_out.ranges.begin(),msg_out.ranges.end());
	std::reverse(msg_out.intensities.begin(),msg_out.intensities.end());

	laser_pub.publish(msg_out);
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "inver_laser");
	ros::NodeHandle n;
	laser_pub = n.advertise<sensor_msgs::LaserScan>("/scan", 1);
	ros::Subscriber sub = n.subscribe("/scan_inv", 1, scanCB);

	ros::spin();
}