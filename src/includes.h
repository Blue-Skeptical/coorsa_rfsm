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
#include <rfsm.h>
#include "coorsa_rfsm/fsm_event.h"
#include "coorsa_rfsm/move_forward.h"
#include <ros/package.h>
#include <std_msgs/Int16.h>
//#include <pallets_manager/GetPallet.h>
//#include <pallets_manager/PALLET.h>
#include <pallet_database_pkg/pallet_info.h>


geometry_msgs::Pose MirPose;
geometry_msgs::Pose GetShiftedPose(geometry_msgs::Pose MyPose, float shift);
void NucleoCallback(const std_msgs::Int16::ConstPtr& msg);
//class Verso_Deposito;
//class Verso_Prelievo;
class Move_Pantografo_P;
class Move_to_detect;

#include "callbacks.cpp"
