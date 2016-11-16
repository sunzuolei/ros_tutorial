#include "ros/ros.h"

int main(int argc, char **argv)
{
    // Set up ROS.
    ros::init(argc, argv, "hello_node");

    int count = 0;
    double rate;
    ros::NodeHandle nh;
    ros::NodeHandle pnh("~");
    pnh.param("rate", rate, 5.1);

    ros::Rate loop_rate(rate);

    while(ros::ok())
    {
        ROS_INFO("Hello ROS world! rate=%.2f, count=%d",
                 rate, count);

        // Let ROS handle all callbacks.
        ros::spinOnce();
        loop_rate.sleep();
        count++;
    }
    return 0;
}
