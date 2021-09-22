--
-- Authors: j
-- Version: 1.0.0
-- Created using rFSMGui
--
return rfsm.state {
	caricate = 0,

    --States

    initial = rfsm.conn{},
		Begin = rfsm.state{entry = function() print("Waiting to begin COORSA task.. (Begin_T_E)") end},

	MIR = rfsm.state{
		initial =rfsm.conn{},

	   	--Prelievo----------------------------------
		Prelievo = rfsm.state{

			--Muoviti per vedere tutti i pacchi
			Move_to_detect = rfsm.state{entry= function() print("Stato: Move to detect pallet layer") end},

				-- Detect, choose and extract boxes
				DCE = rfsm.state{
				--Esegui la detection del piano superiore del palleto e della posizione di ogni pacco
				Detect_boxes = rfsm.state{entry= function() print("Stato: Detect boxes on pallet") end},

				--Algoritmo di pianificazione per la scelta dei pacchi da prendere
				Choose_boxes = rfsm.state{entry= function() print("Stato: Choose boxes to be collected") end},

				--Muove base e braccio per l'estrazione, altrimenti termina il deposito se non ci sono più box
				Move_to_extraction = rfsm.state{entry= function() print("Stato: Move_to_extraction") end}


			},

			--Estrai la box
			Extract_box = rfsm.state{entry= function() print("Stato: Extract_box") end},

			--Effettua una local detection della box
			Local_detection = rfsm.state{entry= function() print("Stato: Local_detection") end},

	    	},

		Move_Pantografo_P = rfsm.state{entry = function() print("Stato: MovePantografo") end},

		Move_Pantografo_D = rfsm.state{entry = function() print("Stato: MovePantografo") end},

		--Deposito-----------------------------------
		Deposito = rfsm.state{

			--Muoviti per vedere tutti i pacchi
			Move_to_detect = rfsm.state{entry= function() print("Stato: Move to detect pallet layer") end},

				-- Detect, choose and extract boxes
				DCE = rfsm.state{
				--Esegui la detection del piano superiore del palleto e della posizione di ogni pacco
				Detect_boxes = rfsm.state{entry= function() print("Stato: Detect boxes on pallet") end},

				--Algoritmo di pianificazione per la scelta dei pacchi da prendere
				Choose_boxes = rfsm.state{entry= function() print("Stato: Choose boxes to be collected") end},

				--Muove base e braccio per l'estrazione, altrimenti termina il deposito se non ci sono più box
				Move_to_deposit = rfsm.state{entry= function() print("Stato: Move_to_Deposit") end}


			},

			--Estrai la box
			Deposit_box = rfsm.state{entry= function() print("Stato: Depisit_box") end},

			--Effettua una local detection della box
			Local_detection = rfsm.state{entry= function() print("Stato: Local_detection") end},

	    	},

	},

	--TASK FALLITO
	Task_failed = rfsm.state{entry= function() print("Task fallito") end},


    --Transitions
	rfsm.trans{ src = 'initial', tgt='Begin', pn = 0, events = {}},
	rfsm.trans{ src = 'Begin', tgt='MIR.Move_Pantografo_P', pn = 0, events = {'Begin_T_E'}},
		--rfsm.trans{ src = 'MIR.Avvio_Prelievo', tgt = 'MIR.Prelievo.Move_to_detect', pn = 0, events = {'begin_p_E'} },
	rfsm.trans{ src = 'MIR.Move_Pantografo_P' , tgt = 'MIR.Prelievo.Move_to_detect', pn = 0, events = {'HeightReached_E'} },
	rfsm.trans{ src = 'MIR.Prelievo.Move_to_detect', tgt = 'MIR.Prelievo.DCE.Detect_boxes', pn = 0, events = {'Success_E'} },

	rfsm.trans{ src = 'MIR.Prelievo.DCE.Detect_boxes', tgt = 'MIR.Prelievo.Move_to_detect', pn = 0, events = {'Failure_E'} },
	rfsm.trans{ src = 'MIR.Prelievo.DCE.Detect_boxes', tgt = 'MIR.Prelievo.DCE.Choose_boxes', pn = 0, events = {'Success_E'} },
	rfsm.trans{ src = 'MIR.Prelievo.DCE.Choose_boxes', tgt = 'MIR.Prelievo.DCE.Move_to_extraction', pn = 0, events = {'Success_E'} },
	rfsm.trans{ src = 'MIR.Prelievo.DCE.Move_to_extraction', tgt = 'MIR.Prelievo.DCE.Choose_boxes', pn = 0, events = {'Failure_E'} },
	rfsm.trans{ src = 'MIR.Prelievo.DCE.Move_to_extraction', tgt = 'MIR.Prelievo.Extract_box', pn = 0, events = {'Success_E'} },
	rfsm.trans{ src = 'MIR.Prelievo.DCE.Move_to_extraction', tgt = 'MIR.Move_Pantografo_D', pn = 0, events = {'Done_E'} },
	rfsm.trans{ src = 'MIR.Prelievo.DCE', tgt = 'Task_failed', pn = 1, events = {'Complete_Failure_E'} },

	rfsm.trans{ src = 'MIR.Prelievo.Extract_box', tgt = 'MIR.Prelievo.DCE.Move_to_extraction', pn = 0, events = {'Success_E'} },
	rfsm.trans{ src = 'MIR.Prelievo.Extract_box', tgt = 'MIR.Prelievo.Local_detection', pn = 0, events = {'Failure_E'} },
	rfsm.trans{ src = 'MIR.Move_Pantografo_D', tgt = 'MIR.Deposito.Move_to_detect', pn=0, events = {'HeightReached_E'}},
	rfsm.trans{ src = 'MIR.Prelievo.Local_detection', tgt = 'MIR.Prelievo.Extract_box', pn = 0, events = {'Success_E'} },
	rfsm.trans{ src = 'MIR.Prelievo.Local_detection', tgt = 'MIR.Prelievo.Extract_box', pn = 0, events = {'Failure_E'} },

	rfsm.trans{ src = 'MIR.Deposito.Move_to_detect', tgt = 'MIR.Deposito.DCE.Detect_boxes', pn = 0, events = {'Success_E'} },

	rfsm.trans{ src = 'MIR.Deposito.DCE.Detect_boxes', tgt = 'MIR.Deposito.Move_to_detect', pn = 0, events = {'Failure_E'} },
	rfsm.trans{ src = 'MIR.Deposito.DCE.Detect_boxes', tgt = 'MIR.Deposito.DCE.Choose_boxes', pn = 0, events = {'Success_E'} },
	rfsm.trans{ src = 'MIR.Deposito.DCE.Choose_boxes', tgt = 'MIR.Deposito.DCE.Move_to_deposit', pn = 0, events = {'Success_E'} },
	rfsm.trans{ src = 'MIR.Deposito.DCE.Move_to_deposit', tgt = 'MIR.Deposito.DCE.Choose_boxes', pn = 0, events = {'Failure_E'} },
	rfsm.trans{ src = 'MIR.Deposito.DCE.Move_to_deposit', tgt = 'MIR.Deposito.Deposit_box', pn = 0, events = {'Success_E'} },
	rfsm.trans{ src = 'MIR.Deposito.DCE.Move_to_deposit', tgt = 'MIR.Move_Pantografo_P', pn = 0, events = {'Done_E'} },
	rfsm.trans{ src = 'MIR.Deposito.DCE', tgt = 'Task_failed', pn = 1, events = {'Complete_Failure_E'} },

	rfsm.trans{ src = 'MIR.Deposito.Deposit_box', tgt = 'MIR.Deposito.DCE.Move_to_deposit', pn = 0, events = {'Success_E'} },
	rfsm.trans{ src = 'MIR.Deposito.Deposit_box', tgt = 'MIR.Deposito.Local_detection', pn = 0, events = {'Failure_E'} },

	rfsm.trans{ src = 'MIR.Deposito.Local_detection', tgt = 'MIR.Deposito.Deposit_box', pn = 0, events = {'Success_E'} },
	rfsm.trans{ src = 'MIR.Deposito.Local_detection', tgt = 'MIR.Deposito.Deposit_box', pn = 0, events = {'Failure_E'} }
--	rfsm.trans{ src = 'MIR.Deposito.initial', tgt = 'MIR.Deposito.Rileva_Box', pn = 0 },
--	rfsm.trans{ src = 'MIR.Deposito.Rileva_Box', tgt = 'MIR.Deposito.Raggiungi_Box', pn = 0, events = {"box_found_E"} },
--	rfsm.trans{ src = 'MIR.Deposito.Raggiungi_Box', tgt = 'MIR.Deposito.Trascina_Box', pn = 0, events = {"box_reached_E"} },
--	rfsm.trans{ src = 'MIR.Deposito.Trascina_Box', tgt = 'MIR.Deposito.seconda_box', pn = 0, events = {"box_loaded_E"}, effect = function() caricate = caricate -1 end },
--	rfsm.trans{ src = 'MIR.Deposito.seconda_box', tgt = 'MIR.Deposito.Raggiungi_Box', pn = 0, guard = function() return (caricate%2) ==0 end},
--	rfsm.trans{ src = 'MIR.Deposito.seconda_box', tgt = 'MIR.Deposito.Termina_Deposito', pn = 0, guard = function() return (caricate%2)==1 end},
--	rfsm.trans{ src = 'MIR.Verso_Prelievo', tgt = 'MIR.Avvio_Prelievo', pn = 0, events = {"p_reached_E"} },
--	rfsm.trans{ src = 'MIR.Deposito.Termina_Deposito', tgt = 'MIR.Verso_Prelievo', pn = 0, events = {"ending_d_E"} },
--	rfsm.trans{ src = 'MIR', tgt='Task_failed', pn=1, events = {"errore_E"}}
}
