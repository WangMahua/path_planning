#include "ros/ros.h"
#include <iostream>
#include <sstream>
#include <cstdlib>
#include "std_msgs/String.h"
#include "std_msgs/Header.h"
#include "test_2_service/string.h"
#include "test_2_service/path_planning.h"

#include <message_filters/time_synchronizer.h>
#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>

using namespace message_filters ;

int count = 0 ;

typedef message_filters::Subscriber<test_2_service::string> string_sub_type; 
typedef message_filters::sync_policies::ApproximateTime<test_2_service::string, test_2_service::string> NoCloudSyncPolicy;    

class MyClass{
    public:
        ros::NodeHandle nh;
        message_filters::Subscriber<test_2_service::string> chatter_1_sub(nh,"chatter_1",1);
        message_filters::Subscriber<test_2_service::string> chatter_2_sub(nh,"chatter_2",1);


        typedef sync_policies::ApproximateTime<test_2_service::string, test_2_service::string> MySyncPolicy;

        Synchronizer<MySyncPolicy> sync(MySyncPolicy(10), chatter_1, chatter_2);
        sync.registerCallback(boost::bind(&MyClass::callback, _1, _2));
        void callback( const test_2_service::string::ConstPtr& chatter_1 , const test_2_service::string::ConstPtr& chatter_2 );
// method definitions needed here
};

void MyClass::callback( const test_2_service::string::ConstPtr& chatter_1 , const test_2_service::string::ConstPtr& chatter_2 ){

    ROS_INFO ("I heard: [%s]", chatter_1->data.c_str()); 
    ROS_INFO ("I heard: [%s]", chatter_2->data.c_str());   

}


int main(int argc, char **argv)
{
    
    ros::init(argc, argv, "agent");

    


    double begin_time =ros::Time::now().toSec();


    while (ros::ok())
    {
        double clustering_time = ros::Time::now().toSec () - begin_time;
        if(clustering_time > count ){
            ROS_INFO ("%f secs for path plan .", clustering_time);
            count ++ ;
        } 
        
        test_2_service::path_planning pos;
        pos.my_pos_x = 1 ;
        pos.my_pos_y = 1 ;
        pos.enemy1_x = 20 ;
        pos.enemy1_y = 10 ;
        pos.enemy2_x = 10 ;
        pos.enemy2_y = 35 ;
        pos.ally_x = 50 ;
        pos.ally_y = 28 ;        

        ros::spinOnce();

    }


    return 0;
}