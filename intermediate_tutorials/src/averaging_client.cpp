#include <boost/thread.hpp>

#include "ros/ros.h"
#include "intermediate_tutorials/AveragingAction.h"
#include "actionlib/client/simple_action_client.h"
#include "actionlib/client/terminal_state.h"
//目标可能出现的状态


void spinThread()
{
  ros::spin();
}


int main(int argc, char *argv[])
{
    ros::init(argc, argv, "test_averaging");
    
    actionlib::SimpleActionClient<intermediate_tutorials::AveragingAction> ac("averaging");
    //客户端是使用 名为"averaging"的实例。

    boost::thread spin_thread(&spinThread);
    //这里创建了线程，ros节点在后台开始运转。如果需要，可以使用此方法为操作客户机创建多个线程。

    ROS_INFO("Waiting for action server to start.");

    ac.waitForServer();
    //就绪态，等待动作服务器的响应，此处阻塞。

    ROS_INFO("Action server started, sending goal.");

    intermediate_tutorials::AveragingGoal goal;

    goal.samples = 100;

    ac.sendGoal(goal);

    bool finished_before_timeout = ac.waitForResult(ros::Duration(30.0));
    //等待动作结束，最后反馈结果。如果最后结果在设定的时间内反馈回来，就返回true，否则就是false。

    if (finished_before_timeout)
    {
        actionlib::SimpleClientGoalState state = ac.getState();
        //获取状态。

        ROS_INFO("Action finished: %s",state.toString().c_str());
        
    }
    else
    {
        ROS_INFO("Action did not finish before the time out.");
    }

    ros::shutdown();

    spin_thread.join();

    return 0;
}

