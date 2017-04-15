#ifndef TIMER_H
#define TIMER_H

#include "ros/ros.h"
namespace timer_demo
{

class TimerTrigger
{
public:
    TimerTrigger(ros::NodeHandle nh);
    ~TimerTrigger();
private:
    void timerCallbackA(const ros::TimerEvent&);
    void timerCallbackB(const ros::TimerEvent&);

    double duration_a_;
    double duration_b_;
};

}

#endif // TIMER_H
