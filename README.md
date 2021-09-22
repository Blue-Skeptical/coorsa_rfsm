# COORSA FSM Guide

## Sequenza di lancio
### Lancio del nodo del MiR:

**Se ho il mir fisico:**
- roslaunch mir_driver mir.launch
- Attendi una 20ina di secondi che si avvii il nodo

**Se lo voglio sulla simulazione Gazebo:**
- roslaunch mir_gazebo mir_maze_world.launch
- roslaunch mir_navigation amcl.launch initial_pose_x:=10.0 initial_pose_y:=10.0
- roslaunch mir_navigation start_planner.launch map_file:=$(rospack find mir_gazebo)/maps/maze.yaml
- Avvio la simulazione su Gazebo

### Avvio la comunicazione seriale:
- controlla la porta dove si trova la nucleo con dmesg | grep tty
- rosrun rosserial_server serial_node port:=/dev/*porta* _baud:=57600

### Lancio il Main:
- rosrun coorsa_rfsm coorsa_rfsm_node FSM2.lua (Qua cambia il file in base alla state machine da caricare,


## Comandi e segnali per il pantografo:
### Comandi:
  - 0   -> FERMA i motori del pantografo (ovunque siano)
  - 1   -> Posizione DOWN (Primo comando che si aspetta)
  - 2   -> Posizione MID
  - 4   -> Posizione UP
  - 64 -> Griffe aperte
  - 128  -> Griffe chiuse
### Segnali:
  - 8   -> Raggiunta posizione DOWN
  - 16   -> Raggiunta posizione MID
  - 32   -> Raggiunta posizione UP
  - 256  -> Griffe aperte arrivate
  - 512  -> Griffe chiuse arrivate
