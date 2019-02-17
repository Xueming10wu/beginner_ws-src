#include "ros/ros.h"
#include "actionlib/client/simple_action_client.h"
#include "beginner_tutorials/FibonacciAction.h"

using namespace beginner_tutorials;
typedef actionlib::SimpleActionClient<beginner_tutorials::FibonacciAction> Client;

class FibonacciClient
{
public:
    FibonacciClient(std::string name) : ac_( name, true )
    {
        ROS_INFO("Waiting for action server to start.");
        ac_.waitForServer();
        ROS_INFO("Action server started, sending goal.");
    };

    ~FibonacciClient()
    {
    };

    void start(int order)
    {
        FibonacciGoal goal;
        goal.order = order;

        // Need boost::bind to pass in the 'this' pointer
        ac_.sendGoal(goal,
        boost::bind(&FibonacciClient::doneCb, this, _1, _2),
        boost::bind(&FibonacciClient::activeCb, this),
        boost::bind(&FibonacciClient::feedbackCb, this, _1));
    }

    void doneCb(const actionlib::SimpleClientGoalState& state,
                const FibonacciResultConstPtr& result)
    {
        ROS_INFO("Action finished: [%s]", state.toString().c_str());
        ROS_INFO("Answer: %i", result->sequence.back());
        ros::shutdown();
        return;
    };

    void activeCb()
    {   
        actionlib::SimpleClientGoalState state = ac_.getState();

        ROS_INFO("Active : [%s]", state.toString().c_str());

        ROS_INFO("Goal just went active");
    };

    void feedbackCb(const FibonacciFeedbackConstPtr& feedback)
    {
        actionlib::SimpleClientGoalState state = ac_.getState();
        ROS_INFO("Feedback : [%s]", state.toString().c_str());
        ROS_INFO("Got Feedback of length %lu", feedback->sequence.size());
    };

protected:


private:
    std::string action_name_;
    Client ac_;
    
};

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "fibonacc_client");
    
    FibonacciClient my_client("fibonacci");

    my_client.start(20);

    ros::spin();

    return 0;
}


