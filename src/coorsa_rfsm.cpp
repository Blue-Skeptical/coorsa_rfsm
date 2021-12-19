#include "includes.h"

#define _USE_MATH_DEFINES

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;
typedef actionlib::SimpleActionClient<coorsa_interface::PerformBoxDetectionAction> BoxDetectionAction;

//Variabili globali
std::string event;
bool arrived=false;
ros::Publisher GoalMarkerPublisher;
ros::Publisher MirMarkerPublisher;
ros::Publisher InterMarkerPublisher;

// SERVICE CALLBACK, inserisce l'evento ricevuto nella variabile globale event
bool eventArrived(coorsa_rfsm::fsm_event::Request &req , coorsa_rfsm::fsm_event::Response &rep ){

	event=req.event;
	arrived=true;
	return true;
}
// CALLBACK che updata la posizione del MiR
void UpdateMirPose(geometry_msgs::PoseWithCovarianceStamped odom){
	MirPose = odom.pose.pose;
}
/*
void UpdateMirPose(nav_msgs::Odometry odom){
	MirPose = odom.pose.pose;
}*/

//Initialize Marker
void InitGoalMarker(){
GoalMarker.header.frame_id = "map";
GoalMarker.header.stamp = ros::Time();
GoalMarker.id = 0;
GoalMarker.type = visualization_msgs::Marker::CUBE;
GoalMarker.action = visualization_msgs::Marker::ADD;
GoalMarker.pose.position.x = 1;
GoalMarker.pose.position.y = 1;
GoalMarker.pose.position.z = 1;
GoalMarker.pose.orientation.x = 0.0;
GoalMarker.pose.orientation.y = 0.0;
GoalMarker.pose.orientation.z = 0.0;
GoalMarker.pose.orientation.w = 1.0;
GoalMarker.scale.x = 20;
GoalMarker.scale.y = 0.02;
GoalMarker.scale.z = 0.02;
GoalMarker.color.a = 1.0; // Don't forget to set the alpha!
GoalMarker.color.r = 0.0;
GoalMarker.color.g = 1.0;
GoalMarker.color.b = 0.0;
//only if using a MESH_RESOURCE marker type:
}

void InitMirMarker(){
MirMarker.header.frame_id = "map";
MirMarker.header.stamp = ros::Time();
MirMarker.id = 0;
MirMarker.type = visualization_msgs::Marker::CUBE;
MirMarker.action = visualization_msgs::Marker::ADD;
MirMarker.pose.position.x = 1;
MirMarker.pose.position.y = 1;
MirMarker.pose.position.z = 1;
MirMarker.pose.orientation.x = 0.0;
MirMarker.pose.orientation.y = 0.0;
MirMarker.pose.orientation.z = 0.0;
MirMarker.pose.orientation.w = 1.0;
MirMarker.scale.x = 20;
MirMarker.scale.y = 0.02;
MirMarker.scale.z = 0.02;
MirMarker.color.a = 1.0; // Don't forget to set the alpha!
MirMarker.color.r = 1.0;
MirMarker.color.g = 0.0;
MirMarker.color.b = 0.0;
//only if using a MESH_RESOURCE marker type:
}

void InitInterMarker(){
InterMarker.header.frame_id = "map";
InterMarker.header.stamp = ros::Time();
InterMarker.id = 0;
InterMarker.type = visualization_msgs::Marker::SPHERE;
InterMarker.action = visualization_msgs::Marker::ADD;
InterMarker.pose.position.x = 1;
InterMarker.pose.position.y = 1;
InterMarker.pose.position.z = 1;
InterMarker.pose.orientation.x = 0.0;
InterMarker.pose.orientation.y = 0.0;
InterMarker.pose.orientation.z = 0.0;
InterMarker.pose.orientation.w = 1.0;
InterMarker.scale.x = 0.03;
InterMarker.scale.y = 0.03;
InterMarker.scale.z = 0.03;
InterMarker.color.a = 1.0; // Don't forget to set the alpha!
InterMarker.color.r = 0.0;
InterMarker.color.g = 0.0;
InterMarker.color.b = 1.0;
//only if using a MESH_RESOURCE marker type:
}

void UpdateMarker(std::string Marker, geometry_msgs::Pose newGoal){
	if(Marker == "GOAL")
	{
		GoalMarker.pose = newGoal;
	}
	if(Marker == "MIR"){
		MirMarker.pose = newGoal;

	}
	if(Marker == "INTER"){
		InterMarker.pose = newGoal;
	}

	GoalMarkerPublisher.publish(GoalMarker);
	MirMarkerPublisher.publish(MirMarker);
	InterMarkerPublisher.publish(InterMarker);

}

void UpdateMarker(std::string Marker, float X, float Y, float theta){
	if(Marker == "GOAL"){
		GoalMarker.pose.position.x = X;
		GoalMarker.pose.position.y = Y;
		GoalMarker.pose.orientation.w = cos(theta/2);
		GoalMarker.pose.orientation.z = sin(theta/2);
	}
	if(Marker == "MIR"){
		MirMarker.pose.position.x = X;
		MirMarker.pose.position.y = Y;
		MirMarker.pose.orientation.w = cos(theta/2);
		MirMarker.pose.orientation.z = sin(theta/2);
	}
	if(Marker == "INTER"){
		InterMarker.pose.position.x = X;
		InterMarker.pose.position.y = Y;
		InterMarker.pose.orientation.w = cos(theta/2);
		InterMarker.pose.orientation.z = sin(theta/2);
	}

	GoalMarkerPublisher.publish(GoalMarker);
	MirMarkerPublisher.publish(MirMarker);
	InterMarkerPublisher.publish(InterMarker);
}

int main(int argc, char** argv) {

	if(argc < 2){
		ROS_ERROR(" *.lua needed as first argument. Could it be 'FSM3.lua' ?");
		return 1;
	}


	//______Avvio la macchina a stati______
	rfsm::StateMachine rfsm(true);

	std::string pk_name;
	if(argc > 2)	pk_name = argv[2];
	else 		pk_name = "coorsa_rfsm";

	std::string pk_path = ros::package::getPath(pk_name);	//Cerco il path del package (di default "coorsa_rfsm")
	pk_path = pk_path.append("/fsm/").append(argv[1]);		//Cerco nella sottocartella /fsm

	if(!rfsm.load(pk_path)){				//Carico la macchina a stati
		ROS_ERROR("FSM not found at: %s \nRemember that *.lua needs to be inside /fsm folder, inside your package folder.", pk_path.c_str());
		return 2;
	}
	rfsm.catchPrintOutput();
	rfsm.run();

	/*
	std_msgs::Int16 INT;
	INT.data = 2;
	INT.data |= (1u << 0);		//Setto a 1 il bit numero 0;
	std::cout << INT;
	*/

	//______Inizializzo il nodo______
	ros::init(argc, argv, "fsm_controller");
	ros::NodeHandle n;
	ros::Rate loop_rate(10);

	//______ACTION CLIENT per inviare i goal al MiR______
	MoveBaseClient moveBaseClient("move_base", true); //ac
	while(!moveBaseClient.waitForServer(ros::Duration(5.0))){
		ROS_INFO("Waiting for the move_base action server to come up");
	}
	BoxDetectionAction boxDetectionAction("",true);
//	while(!boxDetectionAction.waitForServer(ros::Duration(5.0))){
//		ROS_INFO("Waiting for the camera action server to come up");
//	}

	//SERVICE SERVER per far avanzare la macchina a stati.
	//I dispositivi dovranno effettuare delle call a questo ServiceServer per far avanzare la macchina a stati
	//inserendo come request la stringa contenente il nome dell'evento (es:"begin_p_E" per iniziare il prelievo)
	ros::ServiceServer service = n.advertiseService("fsm_event", eventArrived);

	GoalMarkerPublisher = n.advertise<visualization_msgs::Marker>("GoalMarkerPublisher",1000);
	MirMarkerPublisher = n.advertise<visualization_msgs::Marker>("MirMarkerPublisher",1000);
	InterMarkerPublisher = n.advertise<visualization_msgs::Marker>("InterMarkerPublisher",1000);

	ros::Publisher NucleoPublisher = n.advertise<std_msgs::Int16>("Pantograph_cmd",1000);
	ros::Subscriber NucleoSubscriber = n.subscribe("Pantograph_res",1000,NucleoCallback);
	ros::Subscriber MirOdomSubscriber = n.subscribe("amcl_pose",1000,UpdateMirPose); //amcl_pose
	ROS_WARN("MIR POSITION TAKEN FROM /amcl_pose !!!!");
	ROS_WARN("MIR POSITION TAKEN FROM /amcl_pose !!!!");
	ROS_WARN("MIR POSITION TAKEN FROM /amcl_pose !!!!");

	InitGoalMarker();
	InitMirMarker();
	InitInterMarker();

	//Inizializzo le callback con gli argomenti utilizzati
	//La funzione initCallback salva, nelle istanze delle classi, i puntatori:
	//	ActionServer ac:	Per permettere di inviare i goal del mir
	//	StateMachine rfsm:	Per poter gestire internamente la macchina a stati (inviando autonomamente degli eventi)

	MovePantografoP.initCallback(&NucleoPublisher,&rfsm);
	Move_To_Detection_Pose.initCallback(&moveBaseClient,&rfsm);
	Request_Box.initCallback(&rfsm);
	Begin_Detection.initCallback(&boxDetectionAction,&rfsm);
	Move_To_Picking_Pose.initCallback(&moveBaseClient,&rfsm);

	rfsm.setStateCallback("Request_Next_Pallet",Request_Next_Pallet);
	rfsm.setStateCallback("Request_Box", Request_Box);
	rfsm.setStateCallback("Detect_Box.Move_To_Detection_Pose", Move_To_Detection_Pose);
	rfsm.setStateCallback("Detect_Box.Begin_Detection", Begin_Detection);
	rfsm.setStateCallback("Detect_Box.Update_Database", Update_Database);
	rfsm.setStateCallback("Move_To_Picking_Pose",Move_To_Picking_Pose);


	std::cout<<"E' partita la macchina a stati:\n";
	while(ros::ok()){
		if(arrived){
			arrived=false;
			rfsm.sendEvent(event);
			rfsm.run();
		}
			GoalMarkerPublisher.publish(GoalMarker);
   		ros::spinOnce();
			loop_rate.sleep();
	}


	//...
	return 0;
}
