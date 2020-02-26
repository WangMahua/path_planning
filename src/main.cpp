#include "ros/ros.h"
#include <iostream>
#include "std_msgs/String.h"



#include "test_2_service/path.h"


#include "test_2_service/AddTwoInts.h"
#include <cstdlib>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "main");

  ros::NodeHandle n;
  

  ros::ServiceClient client = n.serviceClient<test_2_service::path>("add_two_ints_1");
  test_2_service::path srv;
  srv.request.my_pos_x = 3 ;
  srv.request.my_pos_y = 3 ;
  srv.request.enemy1_x = 20 ;
  srv.request.enemy1_y = 10 ;
  srv.request.enemy2_x = 10 ;
  srv.request.enemy2_y = 35 ;
  srv.request.ally_x = 50 ;
  srv.request.ally_y = 28 ;   
  srv.request.goal_pos_x = 45;
  srv.request.goal_pos_y = 30;

  /*ros::ServiceClient client2 = n.serviceClient<test_2_service::AddTwoInts>("add_two_ints_2");
  test_2_service::AddTwoInts srv2;
  srv2.request.a = 7;
  srv2.request.b = 3;*/

  while(ros::ok()){
    ROS_INFO("333 ");
    if (client.call(srv))
    {
    ROS_INFO("next_pos_x: %ld", (long int)srv.response.next_pos_x);
    ROS_INFO("next_pos_y: %ld", (long int)srv.response.next_pos_y);
    }
    else
    {
    ROS_ERROR("Failed to call service add_two_ints1");
    }
    /*
    if (client2.call(srv2))
    {
    ROS_INFO("Sum: %ld", (long int)srv2.response.sum);
    }
    else
    {
    ROS_ERROR("Failed to call service add_two_ints");
    return 1;
    }
    */
    ros::spinOnce();
  }
  return 0;
}