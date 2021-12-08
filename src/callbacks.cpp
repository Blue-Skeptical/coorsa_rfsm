#include "includes.h"

//Variabili globali
int NucleoResult;
int BoxNumber;
std::string PalletName;
std::vector<geometry_msgs::Pose>  BoxPoses;
std::vector<geometry_msgs::Pose>  BoxList;
std_msgs::Float64MultiArray PlaneDetected;

coorsa_interface::PerformBoxDetectionResultConstPtr BoxDetectionResult;
//-----------------

/////////////////////////////////////////////////////////
//////////////////// RFSM CALLBACK /////////////////////
///////////////////////////////////////////////////////
/*
class Verso_Deposito : public rfsm::StateCallback {
public:
    	virtual void entry() {
		//Genero il messaggio da inviare all'action goal del mir
    pallets_manager::GetPallet srv;
    srv.request.number_pallet = 1;
    if(ros::service::call("/GetPallet",srv)){
      deposito.target_pose.header.frame_id = "map";
      deposito.target_pose.header.stamp = ros::Time::now();
      deposito.target_pose.pose = srv.response.pallet.approaching_poses[0];
    }


//		deposito.target_pose.header.frame_id = "map";
//		deposito.target_pose.header.stamp = ros::Time::now();
//		deposito.target_pose.pose.position.x = 3.0;
//		deposito.target_pose.pose.position.y = 7.0;
//		deposito.target_pose.pose.orientation.w = cos(180*M_PI/(180*2));
//		deposito.target_pose.pose.orientation.z = sin(180*M_PI/(180*2));


		ac->sendGoal(deposito); // C'è -> perché abbiamo il riferimento all'action goal
	}

    	virtual void doo() {
		//Attendo che l'ActionClient sia in stato di successo (ho raggiunto la stazione di deposito)
		//per poi inviare l'evento del raggiungimento della stazione di deposito
		while(ac->getState()!= actionlib::SimpleClientGoalState::SUCCEEDED){
			ros::spinOnce();
		}
		rfsm->sendEvent("Reached_D_E");
	}
	virtual void exit() {}

	//Inizializzo dei puntatori per il client server e per la macchina a stati
	void initCallback(MoveBaseClient* act, rfsm::StateMachine* fsm){
		ac=act;
		rfsm=fsm;
	}

private:
	//variabili locali e puntatori
	move_base_msgs::MoveBaseGoal deposito;
	MoveBaseClient* ac;
	rfsm::StateMachine* rfsm;
} VersoDeposito;
*/
/*
class Verso_Prelievo : public rfsm::StateCallback {
public:
    	virtual void entry() {
		//Genero il messaggio da inviare all'action goal del mir
    			pallet_database_pkg::pallet_info srv;
    			srv.request.box_type = 1;
    			if(ros::service::call("/pallet_info",srv)){
            prelievo.target_pose.header.frame_id = "map";
            prelievo.target_pose.header.stamp = ros::Time::now();
            prelievo.target_pose.pose = srv.response.pallet.approaching_poses[0];
    			}
		//prelievo.target_pose.header.frame_id = "map";
		//prelievo.target_pose.header.stamp = ros::Time::now();
		//prelievo.target_pose.pose.position.x = 10.0;
		//prelievo.target_pose.pose.position.y = 10.0;
		//prelievo.target_pose.pose.orientation.w = cos(0/2);
		//prelievo.target_pose.pose.orientation.z = sin(0/2);

		ac->sendGoal(prelievo);// C'è -> perché abbiamo il riferimento all'action goal
	}


    	virtual void doo() {
		//Attendo che l'ActionClient sia in stato di successo (ho raggiunto la stazione di prelievo)
		//per poi inviare l'evento del raggiungimento della stazione di prelievo
		while(ac->getState()!= actionlib::SimpleClientGoalState::SUCCEEDED){
			ros::spinOnce();
		}
		rfsm->sendEvent("Reached_P_E");
	}

	virtual void exit() {}

	//Inizializzo dei puntatori per il client server e per la macchina a stati
	void initCallback(MoveBaseClient* act, rfsm::StateMachine* fsm){
		ac=act;
		rfsm = fsm;
	}

private:
	//variabili locali e puntatori
	move_base_msgs::MoveBaseGoal prelievo;
	MoveBaseClient* ac;
	rfsm::StateMachine* rfsm;
} VersoPrelievo;
*/
/*
class Move_to_detect : public rfsm::StateCallback{

  virtual void entry(){
    pallet_database_pkg::pallet_info srv;
    srv.request.box_type = 3;
    if(ros::service::call("/pallet_database/get_pallet_info",srv)){
      goal.target_pose.header.frame_id = "map";
      //goal.target_pose.header.stamp = ros::Time::now();
      goal.target_pose.pose = GetShiftedPose(srv.response.approaching_pose_1,-0.3);
      SendMirGoal(goal,0.05,0.05,1.0,false,ac);

      goal.target_pose.pose = srv.response.approaching_pose_1;
      SetMirVelocity(0.4);
      SendMirGoal(goal,0.05,0.05,1.0,false,ac);

      goal.target_pose.pose = GetShiftedPose(srv.response.approaching_pose_1,0.2);
      SendMirGoal(goal,0.05,0.05,1.0,false,ac);
    }


    while(NucleoResult != 8){
          ros::spinOnce();
    }
  }


  public: void initCallback(MoveBaseClient* act, rfsm::StateMachine* fsm){
    ac = act;
    rfsm = fsm;
  }

  private:
    move_base_msgs::MoveBaseGoal goal;
    MoveBaseClient* ac;
    rfsm::StateMachine* rfsm;

} MoveToDetect;
*/
class Move_Pantografo_P : public rfsm::StateCallback {
public:
  //Comandi:
  //  0   -> FERMA i motori del pantografo (ovunque siano)
  //  1   -> Posizione DOWN (Primo comando che si aspetta)
  //  2   -> Posizione MID
  //  4   -> Posizione UP
  //  64  -> Griffe aperte
  //  128  -> Griffe chiuse
  //Segnali:
  //  8   -> Raggiunta posizione DOWN
  // 16   -> Raggiunta posizione MID
  // 32   -> Raggiunta posizione UP
  // 256  -> Griffe aperte arrivate
  // 512  -> Griffe chiuse arrivate

  //Per inviare un comando:
  //    Mess.data = 0;
  //    Mess.data |= (1u << X)        dove 'X' è la posizione del bit
  //    NucleoPublisher->publish(Mess)
  //
  //Per leggere un segnale:
  //    while(NucleoResult != X){     dove 'X' è il numero decimale del segnale
  //      ros::spinOnce();
  //    }
  virtual void entry() {
          Mess.data = 0;
          Mess.data |= (1u << 0); //1 Posizione down
          NucleoPublisher->publish(Mess);
          rfsm->sendEvent("HeightReached_E");
      }

	virtual void exit() {}

	//Inizializzo dei puntatori per il client server e per la macchina a stati
	public: void initCallback(ros::Publisher* pub, rfsm::StateMachine* fsm){
		NucleoPublisher=pub;
		rfsm = fsm;
	}

private:
	//variabili locali e puntatori
  char c;
  std_msgs::Int16 Mess;
	ros::Publisher* NucleoPublisher;
	rfsm::StateMachine* rfsm;
} MovePantografoP;



class RequestNextPallet : public rfsm::StateCallback{

  virtual void entry(){
    //TODO
    //Chiamo il servizio che mi fornisce il prossimo pallet su cui lavorare
    BoxNumber = 3;
    PalletName = "Pallet_1";

    rfsm->sendEvent("Success_E");
  }

  public: void initCallback(rfsm::StateMachine* fsm){
    rfsm = fsm;
  }

  private:
    rfsm::StateMachine* rfsm;

} Request_Next_Pallet;

class RequestBox : public rfsm::StateCallback{

  virtual void entry(){
    //Chiamo il servizio di box recovery
    pallet_database_pkg::box_recovery srv;
    srv.request.box_number = BoxNumber;
    //srv.request.pallet_name = PalletName;

//    if(ros::service::call("/pallet_database/get_box_for_recovery",srv))
//    {
//      //Se le scatole erano già state detectate
//      if(srv.response.box_available)
//      {
//        BoxList = srv.response.box_list;
//         rfsm->sendEvent("Success_E");
//      }
//      //Altrimenti le devo detectare
//      rfsm->sendEvent("Fail_E");
//    }
    rfsm->sendEvent("Success_E");
  }

  public: void initCallback(rfsm::StateMachine* fsm){
    rfsm = fsm;
  }

  private:
    rfsm::StateMachine* rfsm;

} Request_Box;

class MoveToDetectionPose : public rfsm::StateCallback{
  virtual void entry(){
    //Muovo la base alla posizione di detect
    ////goal.target_pose.header.frame_id = "map";
    //TODO
    //Coordinate della posizione di detect
    ////while(ac->getState()!= actionlib::SimpleClientGoalState::SUCCEEDED){
		////	ros::spinOnce();
		////}
    //Chiamo l'action server dell'UR per iniziare la detect
    rfsm->sendEvent("Success_E");
  }

  public: void initCallback(MoveBaseClient* act, rfsm::StateMachine* fsm){
    ac = act;
    rfsm = fsm;
  }

  private:
    move_base_msgs::MoveBaseGoal goal;
    MoveBaseClient* ac;
    rfsm::StateMachine* rfsm;

} Move_To_Detection_Pose;

class BeginDetection : public rfsm::StateCallback{
  virtual void entry(){

    coorsa_interface::PerformBoxDetectionGoal goal;
    bda->sendGoal(goal);

    while(bda->getState()!= actionlib::SimpleClientGoalState::SUCCEEDED){
        ros::spinOnce();
    }

    BoxDetectionResult = bda->getResult();
    BoxPoses = BoxDetectionResult->box_poses;
    PlaneDetected = BoxDetectionResult->plane_detected;
    rfsm->sendEvent("Success_E");

  }

  public: void initCallback(BoxDetectionAction* _bda, rfsm::StateMachine* fsm){
        bda = _bda;
        rfsm = fsm;
  }

  private:
    BoxDetectionAction* bda;
    rfsm::StateMachine* rfsm;

}Begin_Detection;

class UpdateDatabase : public rfsm::StateCallback{
  virtual void entry(){

    pallet_database_pkg::box_detected srv;
    srv.request.pallet_name = PalletName;
    srv.request.box_detected = BoxList;
    srv.request.plane_detected = PlaneDetected;
    if(ros::service::call("pallet_database/save_box_detected",srv))
    {
        rfsm->sendEvent("Success_E");
    }
  }

  public: void initCallback(rfsm::StateMachine* fsm){
    rfsm = fsm;
  }

  private:
    rfsm::StateMachine* rfsm;


}Update_Database;

class MoveToPickingPose : public rfsm::StateCallback{
  virtual void entry(){
    pallet_database_pkg::pallet_info srv;
    srv.request.box_type = 4;
    if(ros::service::call("/pallet_database/get_pallet_info",srv)){
      PerformPreciseApproach(srv.response.approaching_pose_1,ac);
      PerformPreciseApproach(srv.response.approaching_pose_2,ac);
//      deposito.target_pose.header.frame_id = "map";
//      deposito.target_pose.header.stamp = ros::Time::now();
//      deposito.target_pose.pose = srv.response.pallet.approaching_poses[0];
    }

  }
  public: void initCallback(MoveBaseClient* act, rfsm::StateMachine* fsm){
    rfsm = fsm;
    ac = act;
  }
private:
  move_base_msgs::MoveBaseGoal goal;
  MoveBaseClient* ac;
  rfsm::StateMachine* rfsm;
}Move_To_Picking_Pose;


/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////

geometry_msgs::Pose GetShiftedPose(geometry_msgs::Pose MyPose, float shift){
  geometry_msgs::Pose shiftedPose;
  float x = MyPose.position.x;
  float y = MyPose.position.y;
  float w = MyPose.orientation.w;
  float z = MyPose.orientation.z;
  float alfa = acos(w)*2;

  shiftedPose.position.x = x + (shift * cos(alfa));
  shiftedPose.position.y = y + (shift * sin(alfa));
  shiftedPose.orientation.w = w;
  shiftedPose.orientation.z = z;

  return shiftedPose;
}

float ShortenTheAngleDistance(float angle){
  if(angle < -M_PI){
    if(angle < (-2*M_PI))
      return std::fmod(angle,-2*M_PI);
    else
      return 2*M_PI + angle;
  }
  else if(angle > M_PI){
    if(angle > (2*M_PI))
      return std::fmod(angle,2*M_PI);
    else
      return 2*M_PI - angle;
  }
  return angle;
}

void MoveMir(float distance){
  coorsa_rfsm::move_forward srv;
  srv.request.distance = distance;

  if(ros::service::call("/move_forward",srv)){
    ros::spinOnce();
  }
}
void RotateMir(float rad){
  coorsa_rfsm::move_forward srv;
  srv.request.distance = rad;
  if(ros::service::call("/rotate_forward",srv)){
    ros::spinOnce();
  }
}
void SetMirVelocity(float vel){
  dynamic_reconfigure::ReconfigureRequest srv_req;
  dynamic_reconfigure::ReconfigureResponse srv_resp;
  dynamic_reconfigure::DoubleParameter double_param;
  dynamic_reconfigure::Config conf;

  double_param.name = "max_speed_xy";
  double_param.value = 0.2;
  conf.doubles.push_back(double_param);

  srv_req.config = conf;

  ros::service::call("/move_base_node/DWBLocalPlanner/set_parameters", srv_req, srv_resp);
}

void CheckMirPosition(geometry_msgs::Pose targetPose){

  bool x=false;
  bool y=false;
  bool a=false;
  float x_Tollerance = 0.5f;
  float y_Tollerance = 0.5f;
  float a_Tollerance = 0.5f;
  float x_diff = 0;
  float y_diff = 0;
  float a_diff = 0;

  x_diff = std::abs(targetPose.position.x - MirPose.position.x);
  if(x_diff>x_Tollerance){
      ROS_WARN("Out of X tollerance: %f\t(tollerance: %f)\n",x_diff,x_Tollerance);
      x=false;
  }
  else{
    ROS_INFO("Good X: %f\n",x_diff);
    x=true;
  }

  y_diff = std::abs(targetPose.position.y - MirPose.position.y);
  if(y_diff>y_Tollerance){
      ROS_WARN("Out of Y tollerance: %f\t(tollerance: %f)\n",y_diff,y_Tollerance);
      y=false;
  }
  else{
    ROS_INFO("Good Y: %f\n",y_diff);
    y=true;
  }

  a_diff = std::abs(acos(targetPose.orientation.w)*2 - acos(MirPose.orientation.w)*2);
  if(a_diff>a_Tollerance){
      ROS_WARN("Out of angle tollerance: %f\t(tollerance: %f)\n",a_diff,a_Tollerance);
      RotateMir(cos(a_diff/2));
      a=false;
  }
  else{
    ROS_INFO("Good angle: %f\n",a_diff);
    a=true;
  }
}


void PerformPreciseApproach(geometry_msgs::Pose approaching_pose, MoveBaseClient* ac){
  //PORTA IL CENTRO SULLA RETTA PARALLELA AL LATO DEL Pallet
  ////Ruoto di 90° in senso orario il punto di approccio
  geometry_msgs::Pose ap = GetShiftedPose(approaching_pose,-0.8);
  float theta = acos(ap.orientation.w)*2;
  theta += M_PI/2;
  move_base_msgs::MoveBaseGoal goal;
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.pose.position = ap.position;
  goal.target_pose.pose.orientation.w = cos(theta/2);
  goal.target_pose.pose.orientation.z = sin(theta/2);
  ac->sendGoal(goal);
  while(ac->getState()!= actionlib::SimpleClientGoalState::SUCCEEDED){
    ros::spinOnce();
  }
  //CORREGGO LA POSIZIONE per mettere il centro del mir sulla retta PARALLELA
  // al lato del pallet
  float Xmir = MirPose.position.x;
  float Ymir = MirPose.position.y;
  float Xapp = approaching_pose.position.x;
  float Yapp = approaching_pose.position.y;
  float Amir = acos(MirPose.orientation.w)*2;
  float Aapp = acos(approaching_pose.orientation.w)*2;

  float Xt = (Ymir - Yapp + Xapp * tan(Aapp) - Xmir * tan(Amir))/(tan(Aapp)-tan(Amir));
  float Yt = (Xt - Xapp) * tan(Aapp) + Yapp;

  float distance = sqrt(pow(Xmir - Xt,2) + pow(Ymir - Yt,2));
  ros::spinOnce();
  ROS_INFO("Missing Distance: %f m",distance);
  MoveMir(distance);
  //GIRATI DI 90° VERSO IL PALLET
  ros::spinOnce();
  ros::Rate loop_rate(10);
  loop_rate.sleep();
  ros::spinOnce();
  loop_rate.sleep();
  ros::spinOnce();
  loop_rate.sleep();
  ros::spinOnce();
  loop_rate.sleep();
  ros::spinOnce();
  loop_rate.sleep();
  tf2::Quaternion mir_quat(0,0,MirPose.orientation.z,MirPose.orientation.w);
  float mir_angle = tf2::getYaw(MirPose.orientation);
  if(mir_angle < 0) mir_angle = 2*M_PI + mir_angle;

  ROS_INFO("\nApp: %f \nMe: %f",Aapp,mir_angle);
  RotateMir(Aapp - mir_angle);

  ros::spinOnce();
  loop_rate.sleep();
  ros::spinOnce();
  loop_rate.sleep();
  ros::spinOnce();
  loop_rate.sleep();
  ros::spinOnce();
  loop_rate.sleep();
  ros::spinOnce();
  loop_rate.sleep();
  mir_quat = tf2::Quaternion(0,0,MirPose.orientation.z,MirPose.orientation.w);
  mir_angle = tf2::getYaw(MirPose.orientation);
  if(mir_angle < 0) mir_angle = 2*M_PI + mir_angle;
  ROS_INFO("\n%f - %f = %f",Aapp,mir_angle, Aapp - mir_angle);
  ROS_INFO("\nNEW distance: %f\n", ShortenTheAngleDistance(Aapp - mir_angle));
  RotateMir(ShortenTheAngleDistance(Aapp - mir_angle));
//  else ROS_INFO("STO FERMO");
  MoveMir(2.5);


  //PROCEDI DRITTO FINO ALLA DISTANZA DESIDERATA
  //distance = sqrt(pow(MirPose.position.x - approaching_pose.position.x,2) - pow(MirPose.position.y - approaching_pose.position.y,2) );
  //MoveMir(distance);
//  CheckMirPosition(approaching_pose);
}

/////////////////////////////////////////////////////////
/////////////// SUBSCRIBER CALLBACK /////////////////////
/////////////////////////////////////////////////////////
void NucleoCallback(const std_msgs::Int16::ConstPtr& msg)
{
  NucleoResult = msg->data;
}
