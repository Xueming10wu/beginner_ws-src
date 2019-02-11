#include "ros/ros.h"
#include "beginner_tutorials/addTwoInt.h"
#include <iostream>


void usage()
{
    std::cout << "client [x y]" << std::endl;
}

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "add_two_ints_client");
    

    if (argc == 3)
    {

    }
    else
    {
        usage();
        return 1;
    }
    
    ros::NodeHandle nh;
    ros::ServiceClient client = nh.serviceClient<beginner_tutorials::addTwoInt>("add_two_ints");
    beginner_tutorials::addTwoInt srv;
    srv.request.a = atoll(argv[1]);
    srv.request.b = atoll(argv[2]);
    
    //此处使用的是请求服务
    if(client.call(srv))
    {
        std::cout << "Requesting" << srv.request.a << " " << srv.request.b << std::endl;
        std::cout << "sum:" << srv.response.sum << std::endl 
                << "mul:" << srv.response.mul << std::endl;
    }
    else
    {
        std::cout << "Service call failed\n";
    }

    return 0;
}