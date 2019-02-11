#include "ros/ros.h"
#include "beginner_tutorials/Song.h"
#include <iostream>
#include <string>

void callback(const beginner_tutorials::SongConstPtr& msg)
{
	std::cout << "name:" << msg->name << std::endl
		      << "singger:" << msg->singger << std::endl
    		  << msg->lyrics << std::endl;
}

int main(int argc, char *argv[])
{
	ros::init(argc, argv, "listener");
	ros::NodeHandle n;
	ros::Subscriber sub = n.subscribe("chatter", 10, callback);
	ros::spin();

	return 0;
}