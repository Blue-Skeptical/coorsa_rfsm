#include "includes.h"


//Variabili globali
int NucleoResult;
//-----------------


typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

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
class Move_to_detect : public rfsm::StateCallback{

  virtual void entry(){
    pallet_database_pkg::pallet_info srv;
    srv.request.box_type = 3;
    if(ros::service::call("/pallet_database/get_pallet_info",srv)){
      goal.target_pose.header.frame_id = "map";
      goal.target_pose.header.stamp = ros::Time::now();
      goal.target_pose.pose = srv.response.approaching_pose_1;
    }

    ac->sendGoal(goal);

    while(ac->getState()!= actionlib::SimpleClientGoalState::SUCCEEDED){
      ros::spinOnce();
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

class Move_Pantografo_P : public rfsm::StateCallback {
public:
  //Comandi:
  //  0   -> FERMA i motori del pantografo (ovunque siano)
  //  1   -> Posizione DOWN (Primo comando che si aspetta)
  //  2   -> Posizione MID
  //  4   -> Posizione UP
  //  64 -> Griffe aperte
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


/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////
/////////////// SUBSCRIBER CALLBACK /////////////////////
/////////////////////////////////////////////////////////
void NucleoCallback(const std_msgs::Int16::ConstPtr& msg)
{
  NucleoResult = msg->data;
}
