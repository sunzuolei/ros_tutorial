#include "timer_demo/timer.h"

int main(int argc, char **argv)
{
    // Set up ROS.
    ros::init(argc, argv, "timer_node");
    ros::NodeHandle nh;

    // Create a new object.
    timer_demo::TimerTrigger my_node(nh);

    // Let ROS handle all callbacks.
    ros::spin();
    return 0;
}
