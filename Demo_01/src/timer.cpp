#include "timer_demo/timer.h"

namespace timer_demo
{

TimerTrigger::TimerTrigger(ros::NodeHandle nh)
{
    // Initialize node parameters from launch file or command line. Use a private node handle so that multiple instances
    // of the node can be run simultaneously while using different parameters.
    ros::NodeHandle pnh("~");
    pnh.param("timer_a_duration", duration_a_, 1.1);
    pnh.param("timer_b_duration", duration_b_, 2.2);

    ros::Timer timer_a = nh.createTimer(ros::Duration(duration_a_),
            &TimerTrigger::timerCallbackA, this, false);
    ros::Timer timer_b = nh.createTimer(ros::Duration(duration_b_),
            &TimerTrigger::timerCallbackB, this, false);
    ros::spin();
}

TimerTrigger::~TimerTrigger()
{

}

void TimerTrigger::timerCallbackA(const ros::TimerEvent&)
{
    ROS_INFO("Timer A triggered, duration = %.2f", duration_a_);
}

void TimerTrigger::timerCallbackB(const ros::TimerEvent&)
{
    ROS_INFO("Timer B triggered, duration = %.2f", duration_b_);
}

}
