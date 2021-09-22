#pragma once
#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
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
#include <pallets_manager/GetPallet.h>
#include <pallets_manager/PALLET.h>
#include <pallet_database_pkg/pallet_info.h>

#include "callbacks.cpp"

class Verso_Deposito;
class Verso_Prelievo;
class Move_Pantografo;
