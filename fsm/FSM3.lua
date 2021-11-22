--
-- Authors: j
-- Version: 1.0.0
-- Created using rFSMGui
--
return rfsm.state {


    --States

    initial = rfsm.conn{ },

    --Request_Next_Pallet
    Request_Next_Pallet = rfsm.state{entry= function() print("Request next pallet") end}, --end of Request_Next_Pallet


    --Request_Box
    Request_Box = rfsm.state{entry= function() print("Request box") end}, --end of Request_Box


    --Move_To_Picking_Pose
    Move_To_Picking_Pose = rfsm.state{entry= function() print("Move to picking pose") end}, --end of Move_To_Picking_Pose


    --Detect_Box
    Detect_Box = rfsm.state{

        --Update_Database
        Update_Database = rfsm.state{entry= function() print("Update database") end}, --end of Update_Database


        --Move_To_Detection_Pose
        Move_To_Detection_Pose = rfsm.state{entry= function() print("Move to detection pose") end}, --end of Move_To_Detection_Pose


        initial = rfsm.conn{ },

        --Begin_Detection
        Begin_Detection = rfsm.state{entry= function() print("Begin detection") end}, --end of Begin_Detection

    }, --end of Detect_Box



    --Transitions
    rfsm.trans{ src = 'initial', tgt = 'Request_Next_Pallet', pn = 0 },
    rfsm.trans{ src = 'Request_Next_Pallet', tgt = 'Request_Box', pn = 0, events = {"Success_E"} },
    rfsm.trans{ src = 'Detect_Box.Move_To_Detection_Pose', tgt = 'Detect_Box.Begin_Detection', pn = 0, events = {"Success_E"} },
    rfsm.trans{ src = 'Request_Box', tgt = 'Detect_Box.Move_To_Detection_Pose', pn = 0, events = {"Fail_E"} },
    rfsm.trans{ src = 'Detect_Box.Begin_Detection', tgt = 'Detect_Box.Update_Database', pn = 0, events = {"Success_E"} },
    rfsm.trans{ src = 'Detect_Box.Update_Database', tgt = 'Request_Box', pn = 0, events = {"Success_E"} },
    rfsm.trans{ src = 'Request_Box', tgt = 'Move_To_Picking_Pose', pn = 0, events = {"Success_E"} },
}
