#pragma once
#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <nav_msgs/Odometry.h>
#include <math.h>
#include <iostream>
#include <visualization_msgs/Marker.h>
#include <std_msgs/String.h>
#include <std_msgs/Int16.h>
#include <std_msgs/Float64MultiArray.h>
#include <rfsm.h>
#include "coorsa_rfsm/fsm_event.h"
#include "coorsa_rfsm/move_forward.h"
#include <ros/package.h>
#include <std_msgs/Int16.h>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2/LinearMath/Matrix3x3.h>
#include <tf2/utils.h>
#include <tf/transform_datatypes.h>

#include <dynamic_reconfigure/DoubleParameter.h>
#include <dynamic_reconfigure/Reconfigure.h>
#include <dynamic_reconfigure/Config.h>

#include <coorsa_interface/PerformBoxDetectionAction.h>
#include <coorsa_interface/PerformBoxDetectionActionGoal.h>
#include <coorsa_interface/PerformBoxDetectionActionResult.h>
#include <pallet_database_pkg/pallet_info.h>
#include <pallet_database_pkg/box_recovery.h>
#include <pallet_database_pkg/box_detected.h>

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;
typedef actionlib::SimpleActionClient<coorsa_interface::PerformBoxDetectionAction> BoxDetectionAction;

void UpdateGoalMarker(geometry_msgs::Pose newGoal);
void UpdateGoalMarker(float X, float Y, float theta);

visualization_msgs::Marker GoalMarker;
geometry_msgs::Pose MirPose;
geometry_msgs::Pose GetShiftedPose(geometry_msgs::Pose MyPose, float shift);
geometry_msgs::Pose GetMirShiftedPose(float shift);

float ShortenTheAngleDistance(float angle);
void MoveMir(float distance);
void RotateMir(float rad);
void SetMirVelocity(float vel);
void PerformPreciseApproach(geometry_msgs::Pose approaching_pose, MoveBaseClient* ac);
void NucleoCallback(const std_msgs::Int16::ConstPtr& msg);
void CheckMirPosition(geometry_msgs::Pose targetPose);
//class Verso_Deposito;
//class Verso_Prelievo;
class Move_Pantografo_P;
class Move_To_Detection_Pose;
class Request_Box;
class Begin_Detection;
class Move_To_Picking_Pose;

#include "callbacks.cpp"
