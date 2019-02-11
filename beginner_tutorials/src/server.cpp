#include "ros/ros.h"
#include "beginner_tutorials/addTwoInt.h"


bool serverFunction(beginner_tutorials::addTwoInt::Request &req, 
                    beginner_tutorials::addTwoInt::Response &res)
{
    res.sum = req.a + req.b;
    res.mul = req.a * req.b;
    return true;
}
    


int main(int argc, char *argv[])
{
    ros::init(argc, argv, "addTwoInt_server");
    ros::NodeHandle nh;
    ros::ServiceServer server = nh.advertiseService("add_two_ints",serverFunction );
    ros::spin();

    return 0;
}