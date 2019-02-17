#include "ros/ros.h"
#include "std_msgs/Float32.h"
#include "actionlib/server/simple_action_server.h"
#include "intermediate_tutorials/AveragingAction.h"
#include <iostream>
#include <string.h>


class AveragingAction
{
public:
    AveragingAction(std::string name)
    :as_(nh_, name, false),
    action_name_(name)
    {   
        //注册目标回调函数
        as_.registerGoalCallback( boost::bind(&AveragingAction::goalCB, this) );

        //注册抢占回调函数
        as_.registerPreemptCallback( boost::bind(&AveragingAction::preemptCB, this) );
        
        //接收类型为std_msgs::Float32 名为"/random_number"的话题，接收回调函数名为AveragingAction::analysisCB
        sub_ = nh_.subscribe<std_msgs::Float32>("/random_number", 1, &AveragingAction::analysisCB, this );

        //服务挂起
        as_.start();
    };

    ~AveragingAction(void)
    {
    };

    void goalCB()
    {
        std::cout << "New goal" << std::endl;
        data_count_ = 0;
        sum_ = 0;
        sum_sq_ = 0;
        goal_ = as_.acceptNewGoal()->samples;
    };

    void preemptCB()
    {   
        //此操作是事件驱动的，操作代码只在回调发生时才运行，因此创建了preempt回调，以确保操作能够快速响应取消请求。
        //回调函数不接受参数，并在操作服务器上设置抢占。
        ROS_INFO("%s: Preempted", action_name_.c_str());

        //服务器设置为被抢占态，状态号(2)
        as_.setPreempted();
    };

    void analysisCB(const std_msgs::Float32::ConstPtr& msg)
    {
        //这是个处理单独话题的一个回调函数，用来配合action，提供数据源
        if (!as_.isActive())
        {
            //检测服务器状态
            //如果服务器不是进行态(1)的话，就退出回调函数
            return;
        }
        data_count_++;
        feedback_.sample = data_count_;
        feedback_.data = msg->data;

        sum_ += msg->data;
        feedback_.mean = sum_ / data_count_;

        sum_sq_ += pow(msg->data, 2);
        feedback_.std_dev = sqrt(fabs((sum_sq_/data_count_) - pow(feedback_.mean, 2)));

        //发布反馈数据
        as_.publishFeedback(feedback_);
        

        if (data_count_ > goal_)
        {
            result_.mean = feedback_.mean;
            result_.std_dev = feedback_.std_dev;

            /*
            *一旦收集了足够的数据，操作服务器就设置为成功或失败。
            *这将中断操作服务器，analysisCB函数将立即返回，if的描述。
            */
            if(result_.mean < 5.0)
            {
                ROS_INFO("%s: Aborted", action_name_.c_str());
                //set the action state to aborted(状态码:4)
                as_.setAborted(result_);
            }
            else 
            {
                ROS_INFO("%s: Succeeded", action_name_.c_str());
                // set the action state to succeeded(状态码:3)
                as_.setSucceeded(result_);
            }
        }
    };

protected:
    ros::NodeHandle nh_;

    actionlib::SimpleActionServer<intermediate_tutorials::AveragingAction> as_;

    intermediate_tutorials::AveragingFeedback feedback_;

    intermediate_tutorials::AveragingResult result_;

private:
    std::string action_name_;

    int data_count_, goal_;

    //总和 & 2次方的和
    float sum_, sum_sq_;

    ros::Subscriber sub_;
};


int main(int argc, char *argv[])
{
    ros::init(argc, argv, "averaging_sever");

    AveragingAction averaging("averaging");

    ros::spin();

    return 0;
}
