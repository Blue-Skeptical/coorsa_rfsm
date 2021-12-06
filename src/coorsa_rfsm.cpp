#include "includes.h"

#define _USE_MATH_DEFINES

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;
typedef actionlib::SimpleActionClient<coorsa_interface::PerformBoxDetectionAction> BoxDetectionAction;

//Variabili globali
std::string event;
bool arrived=false;


// SERVICE CALLBACK, inserisce l'evento ricevuto nella variabile globale event
bool eventArrived(coorsa_rfsm::fsm_event::Request &req , coorsa_rfsm::fsm_event::Response &rep ){

	event=req.event;
	arrived=true;
	return true;
}
// CALLBACK che updata la posizione del MiR
void UpdateMirPose(geometry_msgs::PoseWithCovarianceStamped odom){
	//MirPose = odom.pose.pose;
	MirPose = odom.pose.pose;
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

	ros::Publisher NucleoPublisher = n.advertise<std_msgs::Int16>("Pantograph_cmd",1000);
	ros::Subscriber NucleoSubscriber = n.subscribe("Pantograph_res",1000,NucleoCallback);
	ros::Subscriber MirOdomSubscriber = n.subscribe("amcl_pose",1000,UpdateMirPose); //odom_comb

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
   		ros::spinOnce();
			loop_rate.sleep();
	}


	//...
	return 0;
}
