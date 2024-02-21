#include <ros/ros.h>
#include "get_det/GetDet.h"
#include "std_msgs/Float32.h"


// Объявляем сервер, издателя и подписчика
ros::ServiceServer server;
ros::Publisher publisher;
ros::Subscriber subscriber;


bool det(get_det::GetDet::Request &req,
         get_det::GetDet::Response &res) {

    res.det = req.first * req.fifth * req.ninth +
              req.second * req.sixth * req.seventh +
              req.fourth * req.third * req.eighth -
              req.third * req.fifth * req.seventh -
              req.second * req.fourth * req.ninth -
              req.first * req.eighth * req.sixth;

    ROS_INFO("request: %d, %d, %d, %d, %d, %d, %d, %d, %d",
             req.first, req.second, req.third,
             req.fourth, req.fifth, req.sixth,
             req.seventh, req.eighth, req.ninth);
    ROS_INFO("sending back response:[%f]", res.det);

    std_msgs::Float32 determinant;
    determinant.data = res.det;

    publisher.publish(determinant);
    ros::spinOnce();

    return true;

}


void recieve(const std_msgs::Float32 &input) {

    float tmp = input.data;
    if ((int) tmp % 2 == 0)
        ROS_INFO("even");
    else
        ROS_INFO("odd");

    return;
}


int main(int argc, char **argv) {

    ros::init(argc, argv, "get_det_situation");
    ros::NodeHandle n;

    server = n.advertiseService("get_det_3x3", det);
    publisher = n.advertise<std_msgs::Float32>("/name", 1000);
    subscriber = n.subscribe("/name", 1000, recieve);

    ROS_INFO("READY TO GET NINE INTEGERS TO GET DETERMINANT");
    ros::spin();
    return 0;

}