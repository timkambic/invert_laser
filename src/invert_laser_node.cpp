//Copyright (c) 2018, Tim Kambic
//All rights reserved.
//
//Redistribution and use in source and binary forms, with or without
//modification, are permitted provided that the following conditions are met:
//* Redistributions of source code must retain the above copyright
//	notice, this list of conditions and the following disclaimer.
//* Redistributions in binary form must reproduce the above copyright
//	notice, this list of conditions and the following disclaimer in the
//	documentation and/or other materials provided with the distribution.
//* Neither the name of the <organization> nor the
//	names of its contributors may be used to endorse or promote products
//	derived from this software without specific prior written permission.
//
//THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
//ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
//WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
//DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
//DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
//(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
//LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
//ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
//(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
//SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"


ros::Publisher laser_pub;
std::string out_frame;

void scanCB(const sensor_msgs::LaserScan::ConstPtr &msg){
	sensor_msgs::LaserScan msg_out;
	msg_out.header = msg->header;
	if(!out_frame.empty()){ // change TF frame
		msg_out.header.frame_id = out_frame;
	}
	msg_out.angle_min = msg->angle_min;
	msg_out.angle_max = msg->angle_max;
	msg_out.angle_increment = msg->angle_increment;
	msg_out.time_increment = msg->time_increment;
	msg_out.scan_time = msg->scan_time;
	msg_out.range_max = msg->range_max;
	msg_out.range_min = msg->range_min;

	msg_out.ranges = msg->ranges;
	msg_out.intensities = msg->intensities;

	std::reverse(msg_out.ranges.begin(),msg_out.ranges.end()); // reverse readings
	std::reverse(msg_out.intensities.begin(),msg_out.intensities.end()); // reverse intensities

	laser_pub.publish(msg_out);
}

int main(int argc, char **argv){
	ros::init(argc, argv, "invert_laser");
	ros::NodeHandle n;
	ros::NodeHandle nh("~");
	out_frame = "";
	nh.getParam("out_frame",out_frame);

	laser_pub = n.advertise<sensor_msgs::LaserScan>("/scan", 5);
	ros::Subscriber sub = n.subscribe("/scan_inv", 5, scanCB);

	ros::spin();
}