#include "ros/ros.h"
#include <iostream>
#include "std_msgs/String.h"

#include "std_msgs/String.h"
#include "test_2_service/path_planning.h"
#include <cstdlib>


/**
 * This tutorial demonstrates simple sending of messages over the ROS system.
 */

int main(int argc, char **argv)
{
 
    ros::init(argc, argv, "agent");
    ros::NodeHandle n;

    ros::Publisher path_pub = n.advertise<test_2_service::path_planning>("path_planning", 1);


    ros::Rate loop_rate(1);


    while (ros::ok())
    {
        test_2_service::path_planning pos;
        pos.my_pos_x = 1 ;
        pos.my_pos_y = 1 ;
        pos.enemy1_x = 20 ;
        pos.enemy1_y = 10 ;
        pos.enemy2_x = 10 ;
        pos.enemy2_y = 35 ;
        pos.ally_x = 50 ;
        pos.ally_y = 28 ;        

        path_pub.publish(pos);

        ros::spinOnce();

        loop_rate.sleep();

    }


    return 0;
}