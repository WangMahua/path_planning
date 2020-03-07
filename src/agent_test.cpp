#include "ros/ros.h"
#include <iostream>
#include <sstream>
#include <cstdlib>
#include "std_msgs/String.h"
#include "std_msgs/Header.h"
#include "test_2_service/string.h"
#include "test_2_service/path_planning.h"
#include "test_2_service/agent.h"
#include "lidar_2020/Ranging_alert.h"

#include <message_filters/time_synchronizer.h>
#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>
#include <boost/thread/thread.hpp>

#define BEAM_NUM 8 

using namespace message_filters ;

int count = 0 ;

void callback(const test_2_service::string::ConstPtr& chatter_1 , const test_2_service::string::ConstPtr& chatter_2 , const lidar_2020::Ranging_alert::ConstPtr& lidar_msg);


int main(int argc, char **argv)
{

    
    ros::init(argc, argv, "agent_test");
    ros::NodeHandle nh ; 

    //Publish to main 
    ros::Publisher main_pub = nh.advertise<test_2_service::agent>("agent", 1000);
    
    //message filters
    message_filters::Subscriber<test_2_service::string> sub_1(nh,"chatter_1",1,ros::TransportHints().tcpNoDelay());
    message_filters::Subscriber<test_2_service::string> sub_2(nh,"chatter_2",1,ros::TransportHints().tcpNoDelay());
    message_filters::Subscriber<lidar_2020::Ranging_alert> sub_3(nh,"ranging_alert",1,ros::TransportHints().tcpNoDelay()); //--->lidar
    typedef sync_policies::ApproximateTime<test_2_service::string,test_2_service::string,lidar_2020::Ranging_alert> MySyncPolicy;
    Synchronizer<MySyncPolicy> sync(MySyncPolicy(10),sub_1,sub_2,sub_3);
    sync.registerCallback(boost::bind(&callback,_1,_2,_3));

    //Time
    double begin_time =ros::Time::now().toSec();

    while(ros::ok){
        double clustering_time = ros::Time::now().toSec () - begin_time; 
     //   ROS_INFO ("%f secs for path plan .", clustering_time);
        ros::spinOnce();
    }
    return 0;
}

void callback(const test_2_service::string::ConstPtr& chatter_1 , const test_2_service::string::ConstPtr& chatter_2 , const lidar_2020::Ranging_alert::ConstPtr& lidar_msg){
    

    test_2_service::agent agent_pub;
    ROS_INFO ("I heard: [%s]", chatter_1->data.c_str()); 
    ROS_INFO ("I heard: [%s]", chatter_2->data.c_str()); 
    for(int i=0 ; i<BEAM_NUM ; i++){
        ROS_INFO("I heard alert[%d] = %d" , i ,lidar_msg->alert[i]);
    } 

    agent_pub.emergency = lidar_msg->alert;
    


}