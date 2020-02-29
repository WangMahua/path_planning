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
        message_filters::Subscriber<test_2_service::string> *chatter_1_sub;      
        message_filters::Subscriber<test_2_service::string> *chatter_2_sub;          
        message_filters::Synchronizer<NoCloudSyncPolicy>* no_cloud_sync_;

        void init();
        void callback( const test_2_service::string::ConstPtr& chatter_1 , const test_2_service::string::ConstPtr& chatter_2 );
        

// method definitions needed here
};

void MyClass::callback( const test_2_service::string::ConstPtr& chatter_1 , const test_2_service::string::ConstPtr& chatter_2 ){

    ROS_INFO ("123");
    ROS_INFO ("I heard: [%s]", chatter_1->data.c_str()); 
    ROS_INFO ("I heard: [%s]", chatter_2->data.c_str());   

}
void MyClass::init()
{
    std::string chatter_1_("chatter_1");
    std::string chatter_2_("chatter_2");

    int q = 5; //queue size
    ros::NodeHandle nh;

    chatter_1_sub = new string_sub_type(nh, chatter_1_, q);
    chatter_2_sub = new string_sub_type(nh, chatter_2_, q);    

    no_cloud_sync_ = new message_filters::Synchronizer<NoCloudSyncPolicy>(NoCloudSyncPolicy(q),  *chatter_1_sub, *chatter_2_sub);

    no_cloud_sync_->registerCallback(boost::bind(&MyClass::callback, this, _1, _2));
}

/*
class myScynchronizer{

    public:
        ros::NodeHandle nh ;
        message_filters::Subscriber<std_msgs::String> *chatter_1_sub;
        message_filters::Subscriber<std_msgs::String> *chatter_2_sub;
        typedef message_filters::sync_policies::ApproximateTime<std_msgs::String,std_msgs::String> NoCloudSyncPolicy;


        TimeSynchronizer<std_msgs::String,std_msgs::String> sync(chatter_1_sub, chatter_2_sub,10 );
        sync.registerCallback(boost::bind(&myScychornizer::callback,_1,_2));

        void callback(const std_msgs::String::Constptr& chatter_1 ,const std_msgs::String::Constptr& chatter_2);        
};

mySynchronizer::mySynchronizer(){
    ros::NodeHandle n;
    
    message_filters::Subscriber<std_msgs::String> chatter_1_sub(n, "chatter_1", 1);
    message_filters::Subscriber<std_msgs::String> chatter_2_sub(n, "chatter_2", 1);
    typedef  message_filters::sync_policies::ApproximateTime<std_msgs::String, std_msgs::String> MySyncPolicy;
    message_filters::Synchronizer<MySyncPolicy> sync(MySyncPolicy(10), chatter_1_sub,chatter_2_sub);
    
    sync.registerCallback(boost::bind(&mySynchronizer::callback, this,_1, _2));
}
*/

int main(int argc, char **argv)
{
    
    ros::init(argc, argv, "agent");

    


  //  double begin_time =ros::Time::now().toSec();


    while (ros::ok())
    {
       /* 
        double clustering_time = ros::Time::now().toSec () - begin_time;
        if(clustering_time > count ){
             ("%f secs for path plan .", clustering_time);
            count ++ ;
        } 
     */  
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