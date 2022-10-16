#include "parts.h"
#include <algorithm>
#include <iterator>
#include <string>
#include <nlohmann/json.hpp>
#include "ros/ros.h"
#include "std_msgs/String.h"

using namespace std;

wheel fourWheels;
leg flLeg;
leg frLeg;
leg rlLeg;
leg rrLeg;
// arm rightArm;
// arm leftArm;

void limbs(string topic, int inputAngle)
{
	switch(topic)
	{
		case "LegFL_Up":
			flLeg.inputUpperAngle(inputAngle);
			break;
			
		case "LegFL_Down":
			flLeg.inputLowerAngle(inputAngle);
			break;
			
		case "LegFR_Up":
			frLeg.inputUpperAngle(inputAngle);
			break;
			
		case "LegFR_Down":
			frLeg.inputLowerAngle(inputAngle);
			break;

		case "LegRL_Up":
			rlLeg.inputUpperAngle(inputAngle);
			break;
			
		case "LegRL_Down":
			rlLeg.inputLowerAngle(inputAngle);
			break;
			
		case "LegRR_Up":
			rrLeg.inputUpperAngle(inputAngle);
			break;
			
		case "LegRR_Down":
			rrLeg.inputLowerAngle(inputAngle);
			break;
/*			
		case "ArmLeft_Rotate":
			leftArm.inputRotateAngle(inputAngle);
			
		case "ArmLeft_Grab":
			leftArm.inputGrabAngle(inputAngle);

		case "ArmRight_Rotate":
			rightArm.inputRotateAngle(inputAngle);
			
		case "ArmRight_Grab":
			rightArm.inputGrabAngle(inputAngle);
*/			
		default:
			break;
	}
}
			
void callBack(const std_msgs::String::ConstPtr& msg)
{
	//parse JSON messages.
	json control;
	control = json::parse(msg->data.c_str());
	
	string topic;
	int angle;
	int speed;
	
	topic = control.value("topic", topic);
	angle = control.value("angle", angle);
	
	//Wheel Drive
	if(topic == "Drive")
	{
		speed = control.value("speed", speed);
		fourWheels.inputDriveSpeed(speed, angle);
		fourWheels.inputSteerAngle(angle);
	}
	
	//Limbs
	else
	{
		limbs(topic, angle);
	}
	 
}


int main(int argc, char **argv)
{
	ros::init(argc, argv, "robot_listen");
	
	ros::NodeHandle n;
	
	ros::Subscriber sub = n.subscribe("robot", 1000, callBack);
	
	ros::spin();
	
	return 0;
}
	

