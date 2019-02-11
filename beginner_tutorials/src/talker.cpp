#include "ros/ros.h"
#include "beginner_tutorials/Song.h"
#include <iostream>
#include <string>

int main(int argc, char *argv[])
{

	ros::init(argc, argv, "talker");
	ros::NodeHandle nh;
	ros::Publisher pub = nh.advertise<beginner_tutorials::Song>("chatter", 10);

	std::string lyrics[3] = {"A","AB","ABC"};
	int count = 0;

	beginner_tutorials::Song msg;
	msg.name = "HJ";
    msg.singger = "JL";

	ros::Rate loop_rate(1);
	while (ros::ok())
	{
		msg.lyrics = lyrics[count % 3];
        count += 1;
        pub.publish(msg);
		ros::spinOnce();
		loop_rate.sleep();
	}

	return 0;
}