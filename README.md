#COORSA FSM Guide

##Sequenza di lancio
###LANCIO IL NODO DEL MIR

	-Se ho il mir fisico:
		- roslaunch mir_driver mir.launch
		- Attendi una 20ina di secondi che si avvii il nodo
	-Se lo voglio sulla simulazione Gazebo:
		- roslaunch mir_gazebo mir_maze_world.launch
		- roslaunch mir_navigation amcl.launch initial_pose_x:=10.0 initial_pose_y:=10.0
		- roslaunch mir_navigation start_planner.launch map_file:=$(rospack find mir_gazebo)/maps/maze.yaml
		- Avvio la simulazione su Gazebo

###AVVIO LA COMUNICAZIONE SERIALE

	- controlla la porta dove si trova la nucleo con dmesg | grep tty
	- rosrun rosserial_server serial_node port:=/dev/*porta* _baud:=57600

###LANCIO IL MAIN

	-rosrun rfsmTest rfsmTest_node FSM2.lua (Qua cambia il file in base alla state machine da caricare,
