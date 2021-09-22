--
-- Authors: j
-- Version: 1.0.0
-- Created using rFSMGui
--
return rfsm.state {
	caricate = 0,

    --States

    --Avvio_Deposito
    Avvio_Deposito = rfsm.state{entry= function() print("Stato: Avvio_Deposito... waiting for 'begin_d_E'") end},

    --Verso_Prelievo
    Verso_Prelievo = rfsm.state{entry= function() print("Stato: Verso_Prelievo... waiting for 'p_reached_E'") end},

    initial = rfsm.conn{},

    --Avvio_Prelievo
    Avvio_Prelievo = rfsm.state{
        entry = function() 	caricate = 0 
				print("Stato: Avvio_Prelievo... waiting for 'begin_p_E'") end,
    },

    --Verso_Deposito
    Verso_Deposito = rfsm.state{entry= function() print("Stato: Verso_Deposito... waiting for 'd_reached_E'") end},


    --Deposito
    Deposito = rfsm.state{

        --Termina_Deposito
        Termina_Deposito = rfsm.state{entry= function() print("Stato: Termina_Deposito... waiting for 'ending_d_E'") end},

        seconda_box = rfsm.conn{ },

        initial = rfsm.conn{ },

        --Rileva_Box
        Rileva_Box = rfsm.state{entry= function() print("Stato: Rileva_box... waiting for 'box_found_E'") end},

        --Trascina_Box
        Trascina_Box = rfsm.state{entry= function() print("Stato: Trascina_Box... waiting for 'box_loaded_E'") end},

        --Raggiungi_Box
        Raggiungi_Box = rfsm.state{entry= function() print("Stato: Raggiungi_Box... waiting for 'box_reached_E'") end},

    }, --end of Deposito


    --Prelievo
    Prelievo = rfsm.state{

        --Raggiungi_Box
        Raggiungi_Box = rfsm.state{entry= function() print("Stato: Raggiungi_Box... waiting for 'box_reached_E'") end},

        initial = rfsm.conn{ },

        --Rileva_Box
        Rileva_Box = rfsm.state{entry= function() print("Stato: Rileva_Box... waiting for 'box_found_E'") end},

        --Trascina_Box
        Trascina_Box = rfsm.state{entry= function() print("Stato: Trascina_Box... waiting for 'box_loaded_E'") end},

        --Termina_Prelievo
        Termina_Prelievo = rfsm.state{entry= function() print("Stato: Termina_Prelievo... waiting for 'ending_p_E'") end},


        seconda_box = rfsm.conn{ },
    }, --end of Prelievo



    --Transitions
    rfsm.trans{ src = 'initial', tgt = 'Avvio_Prelievo', pn = 0 },
    rfsm.trans{ src = 'Avvio_Prelievo', tgt = 'Prelievo.initial', pn = 0, events = {"begin_p_E"} },
    rfsm.trans{ src = 'Prelievo.initial', tgt = 'Prelievo.Rileva_Box', pn = 0 },
    rfsm.trans{ src = 'Prelievo.Rileva_Box', tgt = 'Prelievo.Raggiungi_Box', pn = 0, events = {"box_found_E"} },
    rfsm.trans{ src = 'Prelievo.Raggiungi_Box', tgt = 'Prelievo.Trascina_Box', pn = 0, events = {"box_reached_E"} },
    rfsm.trans{ src = 'Prelievo.Trascina_Box', tgt = 'Prelievo.seconda_box', pn = 0, events = {"box_loaded_E"}, effect = function() caricate = caricate +1 end },
    rfsm.trans{ src = 'Prelievo.seconda_box', tgt = 'Prelievo.Termina_Prelievo', pn = 0, guard = function() return (caricate%2)==1 end},
    rfsm.trans{ src = 'Prelievo.seconda_box', tgt = 'Prelievo.Raggiungi_Box', pn = 0, guard = function() return (caricate%2)==0 end},
    rfsm.trans{ src = 'Prelievo.Termina_Prelievo', tgt = 'Verso_Deposito', pn = 0, events = {"ending_p_E"} },
    rfsm.trans{ src = 'Verso_Deposito', tgt = 'Avvio_Deposito', pn = 0, events = {"d_reached_E"} },
    rfsm.trans{ src = 'Avvio_Deposito', tgt = 'Deposito.initial', pn = 0, events = {"begin_d_E"} },
    rfsm.trans{ src = 'Deposito.initial', tgt = 'Deposito.Rileva_Box', pn = 0 },
    rfsm.trans{ src = 'Deposito.Rileva_Box', tgt = 'Deposito.Raggiungi_Box', pn = 0, events = {"box_found_E"} },
    rfsm.trans{ src = 'Deposito.Raggiungi_Box', tgt = 'Deposito.Trascina_Box', pn = 0, events = {"box_reached_E"} },
    rfsm.trans{ src = 'Deposito.Trascina_Box', tgt = 'Deposito.seconda_box', pn = 0, events = {"box_loaded_E"}, effect = function() caricate = caricate -1 end },
    rfsm.trans{ src = 'Deposito.seconda_box', tgt = 'Deposito.Raggiungi_Box', pn = 0, guard = function() return (caricate%2) ==0 end},
    rfsm.trans{ src = 'Deposito.seconda_box', tgt = 'Deposito.Termina_Deposito', pn = 0, guard = function() return (caricate%2)==1 end},
    rfsm.trans{ src = 'Verso_Prelievo', tgt = 'Avvio_Prelievo', pn = 0, events = {"p_reached_E"} },
    rfsm.trans{ src = 'Deposito.Termina_Deposito', tgt = 'Verso_Prelievo', pn = 0, events = {"ending_d_E"} }
}
