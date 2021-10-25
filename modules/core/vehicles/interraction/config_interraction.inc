/*--------- Interraction Panels System ---------*/

static enum _:E_INTERRACTION_DATA
{
    bool:inter_Trunk,
    bool:inter_Hood,
    bool:inter_lock,
    bool:inter_Engine,
    bool:inter_Lights,
    bool:inter_Windows_Above_Left,
    bool:inter_Windows_Above_Right,
    bool:inter_Windows_Below_Left,
    bool:inter_Windows_Below_Right,
    bool:inter_All_Windows,
    bool:inter_Doors_Above_Left,
    bool:inter_Doors_Above_Right,
    bool:inter_Doors_Below_Left,
    bool:inter_Doors_Below_Right,
    bool:inter_All_Doors
}

static enum _:E_PLAYER_INTERRACTION_DATA
{
    bool:pUsedInterractionPanels,
    bool:pUsedWindowsPanels,
    bool:pUsedDoorsPanels
}

static 
    Text:Interraction_GlobalTD[37],
    VehicleNearPlayer[MAX_PLAYERS] = INVALID_VEHICLE_ID,
    Interraction_Array[MAX_VEHICLES][E_INTERRACTION_DATA],
    pUseInterractionPanels[MAX_PLAYERS][E_PLAYER_INTERRACTION_DATA];
    
#define     Loop(%0,%1,%2)      for(new %0 = %1; %0 < %2; %0++)

// static enum _:MSG_PREFIX
// {
//     MSG_PREFIX_ERROR,
//     MSG_PREFIX_SUCCESS,
//     MSG_PREFIX_USAGE
// }

// stock Msg(playerid, type, const str[])
// {
//     switch(type)
//     {
//         case MSG_PREFIX_ERROR:
//         {
//             SendClientMessageStr(playerid, -1, str_format("[{FF1B1B}Error{FFFFFF}] %s", str));
//         }
//         case MSG_PREFIX_SUCCESS:
//         {
//             SendClientMessageStr(playerid, -1, str_format("[{0BFF19}Success{FFFFFF}] %s", str));
//         }
//     }

//     return 1;
// }


stock ResetInterractionVehicleArray(id)
{
    Interraction_Array[id][inter_Trunk] = false;
    Interraction_Array[id][inter_Hood] = false;
    Interraction_Array[id][inter_lock] = true;
    Interraction_Array[id][inter_Engine] = false;
    Interraction_Array[id][inter_Lights] = false;
    Interraction_Array[id][inter_Windows_Above_Left] = false;
    Interraction_Array[id][inter_Windows_Above_Right] = false;
    Interraction_Array[id][inter_Windows_Below_Left] = false;
    Interraction_Array[id][inter_Windows_Below_Right] = false;
    Interraction_Array[id][inter_All_Windows] = false;
    Interraction_Array[id][inter_Doors_Above_Left] = false;
    Interraction_Array[id][inter_Doors_Above_Right] = false;
    Interraction_Array[id][inter_Doors_Below_Left] = false;
    Interraction_Array[id][inter_Doors_Below_Right] = false;
    Interraction_Array[id][inter_All_Doors] = false;
    return 1;
}

stock ResetInterractionPlayerArray(id)
{
    VehicleNearPlayer[id] = INVALID_PLAYER_ID;
    pUseInterractionPanels[id][pUsedInterractionPanels] = false;
    pUseInterractionPanels[id][pUsedWindowsPanels] = false;
    pUseInterractionPanels[id][pUsedDoorsPanels] = false;
    return 1;
}

stock ResetInterractionArray()
{
    Loop(vehicleid, 0, MAX_VEHICLES)
    {
        ResetInterractionVehicleArray(vehicleid);
    }

    Loop(playerid, 0, MAX_PLAYERS)
    {
        ResetInterractionPlayerArray(playerid);
    }

    printf("Reset Interraction Array.");
    return 1;
}

stock CreateInterractionTextdraw()
{
    Interraction_GlobalTD[0] = TextDrawCreate(342.899902, 211.533447, "mdl-2001:Windows");
    TextDrawLetterSize(Interraction_GlobalTD[0], 0.000000, 0.000000);
    TextDrawTextSize(Interraction_GlobalTD[0], 260.000000, 195.000000);
    TextDrawAlignment(Interraction_GlobalTD[0], 1);
    TextDrawColor(Interraction_GlobalTD[0], -1);
    TextDrawSetShadow(Interraction_GlobalTD[0], 0);
    TextDrawSetOutline(Interraction_GlobalTD[0], 0);
    TextDrawBackgroundColor(Interraction_GlobalTD[0], 255);
    TextDrawFont(Interraction_GlobalTD[0], 4);
    TextDrawSetProportional(Interraction_GlobalTD[0], 0);
    TextDrawSetShadow(Interraction_GlobalTD[0], 0);

    Interraction_GlobalTD[1] = TextDrawCreate(351.700012, 229.866485, "mdl-2001:Trunk OFF");
    TextDrawLetterSize(Interraction_GlobalTD[1], 0.000000, 0.000000);
    TextDrawTextSize(Interraction_GlobalTD[1], 260.000000, 195.000000);
    TextDrawAlignment(Interraction_GlobalTD[1], 1);
    TextDrawColor(Interraction_GlobalTD[1], -1);
    TextDrawSetShadow(Interraction_GlobalTD[1], 0);
    TextDrawSetOutline(Interraction_GlobalTD[1], 0);
    TextDrawBackgroundColor(Interraction_GlobalTD[1], 255);
    TextDrawFont(Interraction_GlobalTD[1], 4);
    TextDrawSetProportional(Interraction_GlobalTD[1], 0);
    TextDrawSetShadow(Interraction_GlobalTD[1], 0);

    Interraction_GlobalTD[2] = TextDrawCreate(351.800109, 247.751098, "mdl-2001:Hood_OFF");
    TextDrawLetterSize(Interraction_GlobalTD[2], 0.000000, 0.000000);
    TextDrawTextSize(Interraction_GlobalTD[2], 260.000000, 195.000000);
    TextDrawAlignment(Interraction_GlobalTD[2], 1);
    TextDrawColor(Interraction_GlobalTD[2], -1);
    TextDrawSetShadow(Interraction_GlobalTD[2], 0);
    TextDrawSetOutline(Interraction_GlobalTD[2], 0);
    TextDrawBackgroundColor(Interraction_GlobalTD[2], 255);
    TextDrawFont(Interraction_GlobalTD[2], 4);
    TextDrawSetProportional(Interraction_GlobalTD[2], 0);
    TextDrawSetShadow(Interraction_GlobalTD[2], 0);

    Interraction_GlobalTD[3] = TextDrawCreate(351.800140, 265.118927, "mdl-2001:Lock OFF");
    TextDrawLetterSize(Interraction_GlobalTD[3], 0.000000, 0.000000);
    TextDrawTextSize(Interraction_GlobalTD[3], 260.000000, 195.000000);
    TextDrawAlignment(Interraction_GlobalTD[3], 1);
    TextDrawColor(Interraction_GlobalTD[3], -1);
    TextDrawSetShadow(Interraction_GlobalTD[3], 0);
    TextDrawSetOutline(Interraction_GlobalTD[3], 0);
    TextDrawBackgroundColor(Interraction_GlobalTD[3], 255);
    TextDrawFont(Interraction_GlobalTD[3], 4);
    TextDrawSetProportional(Interraction_GlobalTD[3], 0);
    TextDrawSetShadow(Interraction_GlobalTD[3], 0);

    Interraction_GlobalTD[4] = TextDrawCreate(340.999938, 318.218292, "mdl-2001:Doors");
    TextDrawLetterSize(Interraction_GlobalTD[4], 0.000000, 0.000000);
    TextDrawTextSize(Interraction_GlobalTD[4], 260.000000, 195.000000);
    TextDrawAlignment(Interraction_GlobalTD[4], 1);
    TextDrawColor(Interraction_GlobalTD[4], -1);
    TextDrawSetShadow(Interraction_GlobalTD[4], 0);
    TextDrawSetOutline(Interraction_GlobalTD[4], 0);
    TextDrawBackgroundColor(Interraction_GlobalTD[4], 255);
    TextDrawFont(Interraction_GlobalTD[4], 4);
    TextDrawSetProportional(Interraction_GlobalTD[4], 0);
    TextDrawSetShadow(Interraction_GlobalTD[4], 0);

    Interraction_GlobalTD[5] = TextDrawCreate(463.399841, 292.383300, "Windows_Click");
    TextDrawLetterSize(Interraction_GlobalTD[5], 0.000000, 1.049998);
    TextDrawTextSize(Interraction_GlobalTD[5], 10.000000, 83.000000);
    TextDrawAlignment(Interraction_GlobalTD[5], 2);
    TextDrawColor(Interraction_GlobalTD[5], -1);
    TextDrawUseBox(Interraction_GlobalTD[5], 1);
    TextDrawBoxColor(Interraction_GlobalTD[5], 0);
    TextDrawSetShadow(Interraction_GlobalTD[5], 0);
    TextDrawSetOutline(Interraction_GlobalTD[5], 0);
    TextDrawBackgroundColor(Interraction_GlobalTD[5], 255);
    TextDrawFont(Interraction_GlobalTD[5], 1);
    TextDrawSetProportional(Interraction_GlobalTD[5], 1);
    TextDrawSetShadow(Interraction_GlobalTD[5], 0);
    TextDrawSetSelectable(Interraction_GlobalTD[5], true);

    Interraction_GlobalTD[6] = TextDrawCreate(471.900054, 309.899963, "Trunk_Click");
    TextDrawLetterSize(Interraction_GlobalTD[6], 0.000000, 1.249999);
    TextDrawTextSize(Interraction_GlobalTD[6], 10.000000, 83.000000);
    TextDrawAlignment(Interraction_GlobalTD[6], 2);
    TextDrawColor(Interraction_GlobalTD[6], -1);
    TextDrawUseBox(Interraction_GlobalTD[6], 1);
    TextDrawBoxColor(Interraction_GlobalTD[6], 0);
    TextDrawSetShadow(Interraction_GlobalTD[6], 0);
    TextDrawSetOutline(Interraction_GlobalTD[6], 0);
    TextDrawBackgroundColor(Interraction_GlobalTD[6], 255);
    TextDrawFont(Interraction_GlobalTD[6], 1);
    TextDrawSetProportional(Interraction_GlobalTD[6], 1);
    TextDrawSetShadow(Interraction_GlobalTD[6], 0);
    TextDrawSetSelectable(Interraction_GlobalTD[6], true);

    Interraction_GlobalTD[7] = TextDrawCreate(472.599914, 329.400177, "Hood_Click");
    TextDrawLetterSize(Interraction_GlobalTD[7], 0.000000, 1.049998);
    TextDrawTextSize(Interraction_GlobalTD[7], 10.000000, 84.000000);
    TextDrawAlignment(Interraction_GlobalTD[7], 2);
    TextDrawColor(Interraction_GlobalTD[7], -1);
    TextDrawUseBox(Interraction_GlobalTD[7], 1);
    TextDrawBoxColor(Interraction_GlobalTD[7], 0);
    TextDrawSetShadow(Interraction_GlobalTD[7], 0);
    TextDrawSetOutline(Interraction_GlobalTD[7], 0);
    TextDrawBackgroundColor(Interraction_GlobalTD[7], 255);
    TextDrawFont(Interraction_GlobalTD[7], 1);
    TextDrawSetProportional(Interraction_GlobalTD[7], 1);
    TextDrawSetShadow(Interraction_GlobalTD[7], 0);
    TextDrawSetSelectable(Interraction_GlobalTD[7], true);

    Interraction_GlobalTD[8] = TextDrawCreate(474.299896, 347.334594, "Lock Click");
    TextDrawLetterSize(Interraction_GlobalTD[8], 0.000000, 1.049998);
    TextDrawTextSize(Interraction_GlobalTD[8], 10.000000, 84.000000);
    TextDrawAlignment(Interraction_GlobalTD[8], 2);
    TextDrawColor(Interraction_GlobalTD[8], -1);
    TextDrawUseBox(Interraction_GlobalTD[8], 1);
    TextDrawBoxColor(Interraction_GlobalTD[8], 0);
    TextDrawSetShadow(Interraction_GlobalTD[8], 0);
    TextDrawSetOutline(Interraction_GlobalTD[8], 0);
    TextDrawBackgroundColor(Interraction_GlobalTD[8], 255);
    TextDrawFont(Interraction_GlobalTD[8], 1);
    TextDrawSetProportional(Interraction_GlobalTD[8], 1);
    TextDrawSetShadow(Interraction_GlobalTD[8], 0);
    TextDrawSetSelectable(Interraction_GlobalTD[8], true);

    Interraction_GlobalTD[9] = TextDrawCreate(461.499969, 399.216583, "Doors_Click");
    TextDrawLetterSize(Interraction_GlobalTD[9], 0.000000, 1.149999);
    TextDrawTextSize(Interraction_GlobalTD[9], 10.000000, 82.000000);
    TextDrawAlignment(Interraction_GlobalTD[9], 2);
    TextDrawColor(Interraction_GlobalTD[9], -1);
    TextDrawUseBox(Interraction_GlobalTD[9], 1);
    TextDrawBoxColor(Interraction_GlobalTD[9], 0);
    TextDrawSetShadow(Interraction_GlobalTD[9], 0);
    TextDrawSetOutline(Interraction_GlobalTD[9], 0);
    TextDrawBackgroundColor(Interraction_GlobalTD[9], 255);
    TextDrawFont(Interraction_GlobalTD[9], 1);
    TextDrawSetProportional(Interraction_GlobalTD[9], 1);
    TextDrawSetShadow(Interraction_GlobalTD[9], 0);
    TextDrawSetSelectable(Interraction_GlobalTD[9], true);

    Interraction_GlobalTD[10] = TextDrawCreate(584.051818, 227.833160, "box");
    TextDrawLetterSize(Interraction_GlobalTD[10], 0.000000, 10.200003);
    TextDrawTextSize(Interraction_GlobalTD[10], 0.000000, 97.000000);
    TextDrawAlignment(Interraction_GlobalTD[10], 2);
    TextDrawColor(Interraction_GlobalTD[10], -1);
    TextDrawUseBox(Interraction_GlobalTD[10], 1);
    TextDrawBoxColor(Interraction_GlobalTD[10], 200);
    TextDrawSetShadow(Interraction_GlobalTD[10], 0);
    TextDrawSetOutline(Interraction_GlobalTD[10], 0);
    TextDrawBackgroundColor(Interraction_GlobalTD[10], 255);
    TextDrawFont(Interraction_GlobalTD[10], 1);
    TextDrawSetProportional(Interraction_GlobalTD[10], 1);
    TextDrawSetShadow(Interraction_GlobalTD[10], 0);

    Interraction_GlobalTD[11] = TextDrawCreate(466.599670, 148.083328, "mdl-2001:Above Left Window OFF");
    TextDrawLetterSize(Interraction_GlobalTD[11], 0.000000, 0.000000);
    TextDrawTextSize(Interraction_GlobalTD[11], 254.000000, 197.000000);
    TextDrawAlignment(Interraction_GlobalTD[11], 1);
    TextDrawColor(Interraction_GlobalTD[11], -1);
    TextDrawSetShadow(Interraction_GlobalTD[11], 0);
    TextDrawSetOutline(Interraction_GlobalTD[11], 0);
    TextDrawBackgroundColor(Interraction_GlobalTD[11], 255);
    TextDrawFont(Interraction_GlobalTD[11], 4);
    TextDrawSetProportional(Interraction_GlobalTD[11], 0);
    TextDrawSetShadow(Interraction_GlobalTD[11], 0);

    Interraction_GlobalTD[12] = TextDrawCreate(466.799865, 166.733184, "mdl-2001:Above Right Window OFF");
    TextDrawLetterSize(Interraction_GlobalTD[12], 0.000000, 0.000000);
    TextDrawTextSize(Interraction_GlobalTD[12], 254.000000, 197.000000);
    TextDrawAlignment(Interraction_GlobalTD[12], 1);
    TextDrawColor(Interraction_GlobalTD[12], -1);
    TextDrawSetShadow(Interraction_GlobalTD[12], 0);
    TextDrawSetOutline(Interraction_GlobalTD[12], 0);
    TextDrawBackgroundColor(Interraction_GlobalTD[12], 255);
    TextDrawFont(Interraction_GlobalTD[12], 4);
    TextDrawSetProportional(Interraction_GlobalTD[12], 0);
    TextDrawSetShadow(Interraction_GlobalTD[12], 0);

    Interraction_GlobalTD[13] = TextDrawCreate(466.299896, 184.732849, "mdl-2001:Below Left Window OFF");
    TextDrawLetterSize(Interraction_GlobalTD[13], 0.000000, 0.000000);
    TextDrawTextSize(Interraction_GlobalTD[13], 254.000000, 197.000000);
    TextDrawAlignment(Interraction_GlobalTD[13], 1);
    TextDrawColor(Interraction_GlobalTD[13], -1);
    TextDrawSetShadow(Interraction_GlobalTD[13], 0);
    TextDrawSetOutline(Interraction_GlobalTD[13], 0);
    TextDrawBackgroundColor(Interraction_GlobalTD[13], 255);
    TextDrawFont(Interraction_GlobalTD[13], 4);
    TextDrawSetProportional(Interraction_GlobalTD[13], 0);
    TextDrawSetShadow(Interraction_GlobalTD[13], 0);

    Interraction_GlobalTD[14] = TextDrawCreate(466.299804, 203.150329, "mdl-2001:Below Right Window OFF");
    TextDrawLetterSize(Interraction_GlobalTD[14], 0.000000, 0.000000);
    TextDrawTextSize(Interraction_GlobalTD[14], 254.000000, 197.000000);
    TextDrawAlignment(Interraction_GlobalTD[14], 1);
    TextDrawColor(Interraction_GlobalTD[14], -1);
    TextDrawSetShadow(Interraction_GlobalTD[14], 0);
    TextDrawSetOutline(Interraction_GlobalTD[14], 0);
    TextDrawBackgroundColor(Interraction_GlobalTD[14], 255);
    TextDrawFont(Interraction_GlobalTD[14], 4);
    TextDrawSetProportional(Interraction_GlobalTD[14], 0);
    TextDrawSetShadow(Interraction_GlobalTD[14], 0);

    Interraction_GlobalTD[15] = TextDrawCreate(466.299682, 222.184890, "mdl-2001:All Windows OFF");
    TextDrawLetterSize(Interraction_GlobalTD[15], 0.000000, 0.000000);
    TextDrawTextSize(Interraction_GlobalTD[15], 254.000000, 197.000000);
    TextDrawAlignment(Interraction_GlobalTD[15], 1);
    TextDrawColor(Interraction_GlobalTD[15], -1);
    TextDrawSetShadow(Interraction_GlobalTD[15], 0);
    TextDrawSetOutline(Interraction_GlobalTD[15], 0);
    TextDrawBackgroundColor(Interraction_GlobalTD[15], 255);
    TextDrawFont(Interraction_GlobalTD[15], 4);
    TextDrawSetProportional(Interraction_GlobalTD[15], 0);
    TextDrawSetShadow(Interraction_GlobalTD[15], 0);

    Interraction_GlobalTD[16] = TextDrawCreate(583.399658, 229.300018, "Above Left Windows");
    TextDrawLetterSize(Interraction_GlobalTD[16], 0.000000, 1.799998);
    TextDrawTextSize(Interraction_GlobalTD[16], 10.000000, 81.000000);
    TextDrawAlignment(Interraction_GlobalTD[16], 2);
    TextDrawColor(Interraction_GlobalTD[16], -1);
    TextDrawUseBox(Interraction_GlobalTD[16], 1);
    TextDrawBoxColor(Interraction_GlobalTD[16], 0);
    TextDrawSetShadow(Interraction_GlobalTD[16], 0);
    TextDrawSetOutline(Interraction_GlobalTD[16], 0);
    TextDrawBackgroundColor(Interraction_GlobalTD[16], 255);
    TextDrawFont(Interraction_GlobalTD[16], 1);
    TextDrawSetProportional(Interraction_GlobalTD[16], 1);
    TextDrawSetShadow(Interraction_GlobalTD[16], 0);
    TextDrawSetSelectable(Interraction_GlobalTD[16], true);

    Interraction_GlobalTD[17] = TextDrawCreate(584.399658, 248.250015, "Above Right Windows");
    TextDrawLetterSize(Interraction_GlobalTD[17], 0.000000, 1.149999);
    TextDrawTextSize(Interraction_GlobalTD[17], 10.000000, 80.000000);
    TextDrawAlignment(Interraction_GlobalTD[17], 2);
    TextDrawColor(Interraction_GlobalTD[17], -1);
    TextDrawUseBox(Interraction_GlobalTD[17], 1);
    TextDrawBoxColor(Interraction_GlobalTD[17], 0);
    TextDrawSetShadow(Interraction_GlobalTD[17], 0);
    TextDrawSetOutline(Interraction_GlobalTD[17], 0);
    TextDrawBackgroundColor(Interraction_GlobalTD[17], 255);
    TextDrawFont(Interraction_GlobalTD[17], 1);
    TextDrawSetProportional(Interraction_GlobalTD[17], 1);
    TextDrawSetShadow(Interraction_GlobalTD[17], 0);
    TextDrawSetSelectable(Interraction_GlobalTD[17], true);

    Interraction_GlobalTD[18] = TextDrawCreate(584.400146, 266.834503, "Below Left Windows");
    TextDrawLetterSize(Interraction_GlobalTD[18], 0.000000, 1.149999);
    TextDrawTextSize(Interraction_GlobalTD[18], 10.000000, 80.000000);
    TextDrawAlignment(Interraction_GlobalTD[18], 2);
    TextDrawColor(Interraction_GlobalTD[18], -1);
    TextDrawUseBox(Interraction_GlobalTD[18], 1);
    TextDrawBoxColor(Interraction_GlobalTD[18], 0);
    TextDrawSetShadow(Interraction_GlobalTD[18], 0);
    TextDrawSetOutline(Interraction_GlobalTD[18], 0);
    TextDrawBackgroundColor(Interraction_GlobalTD[18], 255);
    TextDrawFont(Interraction_GlobalTD[18], 1);
    TextDrawSetProportional(Interraction_GlobalTD[18], 1);
    TextDrawSetShadow(Interraction_GlobalTD[18], 0);
    TextDrawSetSelectable(Interraction_GlobalTD[18], true);

    Interraction_GlobalTD[19] = TextDrawCreate(584.400146, 284.719055, "Below Right Windows");
    TextDrawLetterSize(Interraction_GlobalTD[19], 0.000000, 1.149999);
    TextDrawTextSize(Interraction_GlobalTD[19], 10.000000, 80.000000);
    TextDrawAlignment(Interraction_GlobalTD[19], 2);
    TextDrawColor(Interraction_GlobalTD[19], -1);
    TextDrawUseBox(Interraction_GlobalTD[19], 1);
    TextDrawBoxColor(Interraction_GlobalTD[19], 0);
    TextDrawSetShadow(Interraction_GlobalTD[19], 0);
    TextDrawSetOutline(Interraction_GlobalTD[19], 0);
    TextDrawBackgroundColor(Interraction_GlobalTD[19], 255);
    TextDrawFont(Interraction_GlobalTD[19], 1);
    TextDrawSetProportional(Interraction_GlobalTD[19], 1);
    TextDrawSetShadow(Interraction_GlobalTD[19], 0);
    TextDrawSetSelectable(Interraction_GlobalTD[19], true);

    Interraction_GlobalTD[20] = TextDrawCreate(583.999877, 303.853485, "All Windows");
    TextDrawLetterSize(Interraction_GlobalTD[20], 0.000000, 1.149999);
    TextDrawTextSize(Interraction_GlobalTD[20], 10.000000, 80.000000);
    TextDrawAlignment(Interraction_GlobalTD[20], 2);
    TextDrawColor(Interraction_GlobalTD[20], -1);
    TextDrawUseBox(Interraction_GlobalTD[20], 1);
    TextDrawBoxColor(Interraction_GlobalTD[20], 0);
    TextDrawSetShadow(Interraction_GlobalTD[20], 0);
    TextDrawSetOutline(Interraction_GlobalTD[20], 0);
    TextDrawBackgroundColor(Interraction_GlobalTD[20], 255);
    TextDrawFont(Interraction_GlobalTD[20], 1);
    TextDrawSetProportional(Interraction_GlobalTD[20], 1);
    TextDrawSetShadow(Interraction_GlobalTD[20], 0);
    TextDrawSetSelectable(Interraction_GlobalTD[20], true);

    Interraction_GlobalTD[21] = TextDrawCreate(584.534545, 339.637695, "box");
    TextDrawLetterSize(Interraction_GlobalTD[21], 0.000000, 10.800007);
    TextDrawTextSize(Interraction_GlobalTD[21], 0.000000, 96.000000);
    TextDrawAlignment(Interraction_GlobalTD[21], 2);
    TextDrawColor(Interraction_GlobalTD[21], -1);
    TextDrawUseBox(Interraction_GlobalTD[21], 1);
    TextDrawBoxColor(Interraction_GlobalTD[21], 200);
    TextDrawSetShadow(Interraction_GlobalTD[21], 0);
    TextDrawSetOutline(Interraction_GlobalTD[21], 0);
    TextDrawBackgroundColor(Interraction_GlobalTD[21], 255);
    TextDrawFont(Interraction_GlobalTD[21], 1);
    TextDrawSetProportional(Interraction_GlobalTD[21], 1);
    TextDrawSetShadow(Interraction_GlobalTD[21], 0);

    Interraction_GlobalTD[22] = TextDrawCreate(466.894439, 262.416717, "mdl-2001:A-Left Door OFF");
    TextDrawLetterSize(Interraction_GlobalTD[22], 0.000000, 0.000000);
    TextDrawTextSize(Interraction_GlobalTD[22], 254.000000, 197.000000);
    TextDrawAlignment(Interraction_GlobalTD[22], 1);
    TextDrawColor(Interraction_GlobalTD[22], -1);
    TextDrawSetShadow(Interraction_GlobalTD[22], 0);
    TextDrawSetOutline(Interraction_GlobalTD[22], 0);
    TextDrawBackgroundColor(Interraction_GlobalTD[22], 255);
    TextDrawFont(Interraction_GlobalTD[22], 4);
    TextDrawSetProportional(Interraction_GlobalTD[22], 0);
    TextDrawSetShadow(Interraction_GlobalTD[22], 0);

    Interraction_GlobalTD[23] = TextDrawCreate(466.768280, 281.851135, "mdl-2001:A-Right Door OFF");
    TextDrawLetterSize(Interraction_GlobalTD[23], 0.000000, 0.000000);
    TextDrawTextSize(Interraction_GlobalTD[23], 254.000000, 197.000000);
    TextDrawAlignment(Interraction_GlobalTD[23], 1);
    TextDrawColor(Interraction_GlobalTD[23], -1);
    TextDrawSetShadow(Interraction_GlobalTD[23], 0);
    TextDrawSetOutline(Interraction_GlobalTD[23], 0);
    TextDrawBackgroundColor(Interraction_GlobalTD[23], 255);
    TextDrawFont(Interraction_GlobalTD[23], 4);
    TextDrawSetProportional(Interraction_GlobalTD[23], 0);
    TextDrawSetShadow(Interraction_GlobalTD[23], 0);

    Interraction_GlobalTD[24] = TextDrawCreate(466.799774, 300.385833, "mdl-2001:B-Left Door OFF");
    TextDrawLetterSize(Interraction_GlobalTD[24], 0.000000, 0.000000);
    TextDrawTextSize(Interraction_GlobalTD[24], 254.000000, 197.000000);
    TextDrawAlignment(Interraction_GlobalTD[24], 1);
    TextDrawColor(Interraction_GlobalTD[24], -1);
    TextDrawSetShadow(Interraction_GlobalTD[24], 0);
    TextDrawSetOutline(Interraction_GlobalTD[24], 0);
    TextDrawBackgroundColor(Interraction_GlobalTD[24], 255);
    TextDrawFont(Interraction_GlobalTD[24], 4);
    TextDrawSetProportional(Interraction_GlobalTD[24], 0);
    TextDrawSetShadow(Interraction_GlobalTD[24], 0);

    Interraction_GlobalTD[25] = TextDrawCreate(466.799774, 319.620422, "mdl-2001:B-Right Door OFF");
    TextDrawLetterSize(Interraction_GlobalTD[25], 0.000000, 0.000000);
    TextDrawTextSize(Interraction_GlobalTD[25], 254.000000, 197.000000);
    TextDrawAlignment(Interraction_GlobalTD[25], 1);
    TextDrawColor(Interraction_GlobalTD[25], -1);
    TextDrawSetShadow(Interraction_GlobalTD[25], 0);
    TextDrawSetOutline(Interraction_GlobalTD[25], 0);
    TextDrawBackgroundColor(Interraction_GlobalTD[25], 255);
    TextDrawFont(Interraction_GlobalTD[25], 4);
    TextDrawSetProportional(Interraction_GlobalTD[25], 0);
    TextDrawSetShadow(Interraction_GlobalTD[25], 0);

    Interraction_GlobalTD[26] = TextDrawCreate(466.899810, 339.071685, "mdl-2001:All Doors OFF");
    TextDrawLetterSize(Interraction_GlobalTD[26], 0.000000, 0.000000);
    TextDrawTextSize(Interraction_GlobalTD[26], 254.000000, 197.000000);
    TextDrawAlignment(Interraction_GlobalTD[26], 1);
    TextDrawColor(Interraction_GlobalTD[26], -1);
    TextDrawSetShadow(Interraction_GlobalTD[26], 0);
    TextDrawSetOutline(Interraction_GlobalTD[26], 0);
    TextDrawBackgroundColor(Interraction_GlobalTD[26], 255);
    TextDrawFont(Interraction_GlobalTD[26], 4);
    TextDrawSetProportional(Interraction_GlobalTD[26], 0);
    TextDrawSetShadow(Interraction_GlobalTD[26], 0);

    Interraction_GlobalTD[27] = TextDrawCreate(584.300415, 345.750122, "A-Left Doors");
    TextDrawLetterSize(Interraction_GlobalTD[27], 0.000000, 0.950001);
    TextDrawTextSize(Interraction_GlobalTD[27], 10.000000, 81.000000);
    TextDrawAlignment(Interraction_GlobalTD[27], 2);
    TextDrawColor(Interraction_GlobalTD[27], -1);
    TextDrawUseBox(Interraction_GlobalTD[27], 1);
    TextDrawBoxColor(Interraction_GlobalTD[27], 0);
    TextDrawSetShadow(Interraction_GlobalTD[27], 0);
    TextDrawSetOutline(Interraction_GlobalTD[27], 0);
    TextDrawBackgroundColor(Interraction_GlobalTD[27], 0);
    TextDrawFont(Interraction_GlobalTD[27], 1);
    TextDrawSetProportional(Interraction_GlobalTD[27], 1);
    TextDrawSetShadow(Interraction_GlobalTD[27], 0);
    TextDrawSetSelectable(Interraction_GlobalTD[27], true);

    Interraction_GlobalTD[28] = TextDrawCreate(584.232055, 364.849731, "A-Right Doors");
    TextDrawLetterSize(Interraction_GlobalTD[28], 0.000000, 0.950001);
    TextDrawTextSize(Interraction_GlobalTD[28], 10.000000, 81.000000);
    TextDrawAlignment(Interraction_GlobalTD[28], 2);
    TextDrawColor(Interraction_GlobalTD[28], -1);
    TextDrawUseBox(Interraction_GlobalTD[28], 1);
    TextDrawBoxColor(Interraction_GlobalTD[28], 0);
    TextDrawSetShadow(Interraction_GlobalTD[28], 0);
    TextDrawSetOutline(Interraction_GlobalTD[28], 0);
    TextDrawBackgroundColor(Interraction_GlobalTD[28], 255);
    TextDrawFont(Interraction_GlobalTD[28], 1);
    TextDrawSetProportional(Interraction_GlobalTD[28], 1);
    TextDrawSetShadow(Interraction_GlobalTD[28], 0);
    TextDrawSetSelectable(Interraction_GlobalTD[28], true);

    Interraction_GlobalTD[29] = TextDrawCreate(584.500488, 383.366668, "B-Left Doors");
    TextDrawLetterSize(Interraction_GlobalTD[29], 0.000000, 0.950001);
    TextDrawTextSize(Interraction_GlobalTD[29], 10.000000, 81.000000);
    TextDrawAlignment(Interraction_GlobalTD[29], 2);
    TextDrawColor(Interraction_GlobalTD[29], -1);
    TextDrawUseBox(Interraction_GlobalTD[29], 1);
    TextDrawBoxColor(Interraction_GlobalTD[29], 0);
    TextDrawSetShadow(Interraction_GlobalTD[29], 0);
    TextDrawSetOutline(Interraction_GlobalTD[29], 0);
    TextDrawBackgroundColor(Interraction_GlobalTD[29], 255);
    TextDrawFont(Interraction_GlobalTD[29], 1);
    TextDrawSetProportional(Interraction_GlobalTD[29], 1);
    TextDrawSetShadow(Interraction_GlobalTD[29], 0);
    TextDrawSetSelectable(Interraction_GlobalTD[29], true);

    Interraction_GlobalTD[30] = TextDrawCreate(584.800415, 402.616760, "B-Right Doors");
    TextDrawLetterSize(Interraction_GlobalTD[30], 0.000000, 0.950001);
    TextDrawTextSize(Interraction_GlobalTD[30], 10.000000, 81.000000);
    TextDrawAlignment(Interraction_GlobalTD[30], 2);
    TextDrawColor(Interraction_GlobalTD[30], -1);
    TextDrawUseBox(Interraction_GlobalTD[30], 1);
    TextDrawBoxColor(Interraction_GlobalTD[30], 0);
    TextDrawSetShadow(Interraction_GlobalTD[30], 0);
    TextDrawSetOutline(Interraction_GlobalTD[30], 0);
    TextDrawBackgroundColor(Interraction_GlobalTD[30], 255);
    TextDrawFont(Interraction_GlobalTD[30], 1);
    TextDrawSetProportional(Interraction_GlobalTD[30], 1);
    TextDrawSetShadow(Interraction_GlobalTD[30], 0);
    TextDrawSetSelectable(Interraction_GlobalTD[30], true);

    Interraction_GlobalTD[31] = TextDrawCreate(584.400390, 422.449951, "All Doors");
    TextDrawLetterSize(Interraction_GlobalTD[31], 0.000000, 0.950001);
    TextDrawTextSize(Interraction_GlobalTD[31], 10.000000, 81.000000);
    TextDrawAlignment(Interraction_GlobalTD[31], 2);
    TextDrawColor(Interraction_GlobalTD[31], -1);
    TextDrawUseBox(Interraction_GlobalTD[31], 1);
    TextDrawBoxColor(Interraction_GlobalTD[31], 0);
    TextDrawSetShadow(Interraction_GlobalTD[31], 0);
    TextDrawSetOutline(Interraction_GlobalTD[31], 0);
    TextDrawBackgroundColor(Interraction_GlobalTD[31], 255);
    TextDrawFont(Interraction_GlobalTD[31], 1);
    TextDrawSetProportional(Interraction_GlobalTD[31], 1);
    TextDrawSetShadow(Interraction_GlobalTD[31], 0);
    TextDrawSetSelectable(Interraction_GlobalTD[31], true);

    Interraction_GlobalTD[32] = TextDrawCreate(352.099975, 282.386627, "mdl-2001:Engine OFF");
    TextDrawLetterSize(Interraction_GlobalTD[32], 0.000000, 0.000000);
    TextDrawTextSize(Interraction_GlobalTD[32], 260.000000, 195.000000);
    TextDrawAlignment(Interraction_GlobalTD[32], 1);
    TextDrawColor(Interraction_GlobalTD[32], -1);
    TextDrawSetShadow(Interraction_GlobalTD[32], 0);
    TextDrawSetOutline(Interraction_GlobalTD[32], 0);
    TextDrawBackgroundColor(Interraction_GlobalTD[32], 255);
    TextDrawFont(Interraction_GlobalTD[32], 4);
    TextDrawSetProportional(Interraction_GlobalTD[32], 0);
    TextDrawSetShadow(Interraction_GlobalTD[32], 0);

    Interraction_GlobalTD[33] = TextDrawCreate(351.900024, 300.120239, "mdl-2001:Lights OFF");
    TextDrawLetterSize(Interraction_GlobalTD[33], 0.000000, 0.000000);
    TextDrawTextSize(Interraction_GlobalTD[33], 260.000000, 195.000000);
    TextDrawAlignment(Interraction_GlobalTD[33], 1);
    TextDrawColor(Interraction_GlobalTD[33], -1);
    TextDrawSetShadow(Interraction_GlobalTD[33], 0);
    TextDrawSetOutline(Interraction_GlobalTD[33], 0);
    TextDrawBackgroundColor(Interraction_GlobalTD[33], 255);
    TextDrawFont(Interraction_GlobalTD[33], 4);
    TextDrawSetProportional(Interraction_GlobalTD[33], 0);
    TextDrawSetShadow(Interraction_GlobalTD[33], 0);

    Interraction_GlobalTD[34] = TextDrawCreate(472.800415, 364.116668, "Engine Lock");
    TextDrawLetterSize(Interraction_GlobalTD[34], 0.000000, 0.950001);
    TextDrawTextSize(Interraction_GlobalTD[34], 10.000000, 81.000000);
    TextDrawAlignment(Interraction_GlobalTD[34], 2);
    TextDrawColor(Interraction_GlobalTD[34], -1);
    TextDrawUseBox(Interraction_GlobalTD[34], 1);
    TextDrawBoxColor(Interraction_GlobalTD[34], 0);
    TextDrawSetShadow(Interraction_GlobalTD[34], 0);
    TextDrawSetOutline(Interraction_GlobalTD[34], 0);
    TextDrawBackgroundColor(Interraction_GlobalTD[34], 255);
    TextDrawFont(Interraction_GlobalTD[34], 2);
    TextDrawSetProportional(Interraction_GlobalTD[34], 1);
    TextDrawSetShadow(Interraction_GlobalTD[34], 0);
    TextDrawSetSelectable(Interraction_GlobalTD[34], true);

    Interraction_GlobalTD[35] = TextDrawCreate(472.400421, 381.933410, "Lights Click");
    TextDrawLetterSize(Interraction_GlobalTD[35], 0.000000, 0.950001);
    TextDrawTextSize(Interraction_GlobalTD[35], 10.000000, 81.000000);
    TextDrawAlignment(Interraction_GlobalTD[35], 2);
    TextDrawColor(Interraction_GlobalTD[35], -1);
    TextDrawUseBox(Interraction_GlobalTD[35], 1);
    TextDrawBoxColor(Interraction_GlobalTD[35], 0);
    TextDrawSetShadow(Interraction_GlobalTD[35], 0);
    TextDrawSetOutline(Interraction_GlobalTD[35], 0);
    TextDrawBackgroundColor(Interraction_GlobalTD[35], 255);
    TextDrawFont(Interraction_GlobalTD[35], 1);
    TextDrawSetProportional(Interraction_GlobalTD[35], 1);
    TextDrawSetShadow(Interraction_GlobalTD[35], 0);
    TextDrawSetSelectable(Interraction_GlobalTD[35], true);

    return 1;
}

stock bool:DebugInterractionPlayer(playerid)
{
    new vehicleid = VehicleNearPlayer[playerid];
    if(vehicleid != INVALID_VEHICLE_ID)
    {
        new engine = 0, lights = 0, alarm = 0, doors = 0, bonnet = 0, boot = 0, objective = 0;

        // Set String
        TextDrawSetString(Interraction_GlobalTD[1], "mdl-2001:Trunk OFF");
        if(Interraction_Array[vehicleid][inter_Trunk] == true)
        {
            TextDrawSetString(Interraction_GlobalTD[1], "mdl-2001:Trunk ON");
            boot = VEHICLE_PARAMS_ON;
        }

        TextDrawSetString(Interraction_GlobalTD[2], "mdl-2001:Hood_OFF");
        if(Interraction_Array[vehicleid][inter_Hood] == true)
        {
            TextDrawSetString(Interraction_GlobalTD[2], "mdl-2001:Hood_ON");
            bonnet = VEHICLE_PARAMS_ON;
        }

        TextDrawSetString(Interraction_GlobalTD[3], "mdl-2001:Lock OFF");
        if(Interraction_Array[vehicleid][inter_lock] == true)
        {
            TextDrawSetString(Interraction_GlobalTD[3], "mdl-2001:Lock ON");
            doors = VEHICLE_PARAMS_ON;
        }

        TextDrawSetString(Interraction_GlobalTD[32], "mdl-2001:Engine OFF");
        if(Interraction_Array[vehicleid][inter_Engine] == true)
        {
            TextDrawSetString(Interraction_GlobalTD[32], "mdl-2001:Engine ON");
            engine = VEHICLE_PARAMS_ON;
        }

        TextDrawSetString(Interraction_GlobalTD[33], "mdl-2001:Lights OFF");
        if(Interraction_Array[vehicleid][inter_Lights] == true)
        {
            TextDrawSetString(Interraction_GlobalTD[33], "mdl-2001:Lights ON");
            lights = VEHICLE_PARAMS_ON;
        }

        SetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
        return true;
    }

    return false;
}

stock bool:DebugPanelsInterraction(playerid)
{
    new vehicleid = VehicleNearPlayer[playerid];
    if(vehicleid != INVALID_PLAYER_ID)
    {
        new driver = 0, passenger = 0, backleft = 0, backright = 0;

        TextDrawSetString(Interraction_GlobalTD[11], "mdl-2001:Above Left Window OFF");
        if(Interraction_Array[vehicleid][inter_Windows_Above_Left] == true)
        {
            TextDrawSetString(Interraction_GlobalTD[11], "mdl-2001:Above Left Window ON");
            driver = 1;
        }

        TextDrawSetString(Interraction_GlobalTD[12], "mdl-2001:Above Right Window OFF");
        if(Interraction_Array[vehicleid][inter_Windows_Above_Right] == true)
        {
            TextDrawSetString(Interraction_GlobalTD[12], "mdl-2001:Above Right Window ON");
            passenger = 1;
        }

        TextDrawSetString(Interraction_GlobalTD[13], "mdl-2001:Below Left Window OFF");
        if(Interraction_Array[vehicleid][inter_Windows_Below_Left] == true)
        {
            TextDrawSetString(Interraction_GlobalTD[13], "mdl-2001:Below Left Window ON");
            backleft = 1;
        }

        TextDrawSetString(Interraction_GlobalTD[14], "mdl-2001:Below Right Window OFF");
        if(Interraction_Array[vehicleid][inter_Windows_Below_Right] == true)
        {
            TextDrawSetString(Interraction_GlobalTD[14], "mdl-2001:Below Right Window ON");
            backright = 1;
        }

        SetVehicleParamsCarWindows(vehicleid, driver, passenger, backleft, backright);
        return true;
    }

    return false;
}

stock bool:DebugDoorsPanelsInterraction(playerid)
{
    new vehicleid = VehicleNearPlayer[playerid];
    if(vehicleid != INVALID_VEHICLE_ID)
    {
        new driver = 0, passenger = 0, backleft = 0, backright = 0;

        TextDrawSetString(Interraction_GlobalTD[22], "mdl-2001:A-Left Door OFF");
        if(Interraction_Array[vehicleid][inter_Doors_Above_Left] == true)
        {
            TextDrawSetString(Interraction_GlobalTD[22], "mdl-2001:A-Right Door ON");
            driver = 1;
        }

        TextDrawSetString(Interraction_GlobalTD[23], "mdl-2001:A-Right Door OFF");
        if(Interraction_Array[vehicleid][inter_Doors_Above_Right] == true)
        {
            TextDrawSetString(Interraction_GlobalTD[23], "mdl-2001:A-Right Door ON");
            passenger = 1;
        }

        TextDrawSetString(Interraction_GlobalTD[24], "mdl-2001:B-Left Door OFF");
        if(Interraction_Array[vehicleid][inter_Doors_Below_Left] == true)
        {
            TextDrawSetString(Interraction_GlobalTD[24], "mdl-2001:B-Left Door ON");
            backleft = 1;
        }

        TextDrawSetString(Interraction_GlobalTD[25], "mdl-2001:B-Right Door OFF");
        if(Interraction_Array[vehicleid][inter_Doors_Below_Right] == true)
        {
            TextDrawSetString(Interraction_GlobalTD[25], "mdl-2001:B-Right Door ON");
            backright = 1;
        }

        SetVehicleParamsCarDoors(vehicleid, driver, passenger, backleft, backright);
        return true;
    }

    return false;
}

stock ShowInterracationOnGround(playerid)
{
    DebugInterractionPlayer(playerid);
    HideInterractionForPlayer(playerid);

    pUseInterractionPanels[playerid][pUsedInterractionPanels] = true;
    
    // Trunk
    TextDrawShowForPlayer(playerid, Interraction_GlobalTD[1]);
    TextDrawShowForPlayer(playerid, Interraction_GlobalTD[6]);

    // Hood
    TextDrawShowForPlayer(playerid, Interraction_GlobalTD[2]);
    TextDrawShowForPlayer(playerid, Interraction_GlobalTD[7]);

    // Lock
    TextDrawShowForPlayer(playerid, Interraction_GlobalTD[3]);
    TextDrawShowForPlayer(playerid, Interraction_GlobalTD[8]);
    return 1;
}

stock ShowInterractionForPlayer(playerid)
{
    DebugInterractionPlayer(playerid);
    HideInterractionForPlayer(playerid);

    pUseInterractionPanels[playerid][pUsedInterractionPanels] = true;
    for(new i = 0; i < 10; i++)
    {
        TextDrawShowForPlayer(playerid, Interraction_GlobalTD[i]);
    }
    
    for(new i = 32; i < 36; i++)
    {
        TextDrawShowForPlayer(playerid, Interraction_GlobalTD[i]);
    }

    return 1;
}

stock HideInterractionForPlayer(playerid)
{
    pUseInterractionPanels[playerid][pUsedInterractionPanels] = false;
    for(new i = 0; i < 10; i++)
    {
        TextDrawHideForPlayer(playerid, Interraction_GlobalTD[i]);
    }

    for(new i = 32; i < 36; i++)
    {
        TextDrawHideForPlayer(playerid, Interraction_GlobalTD[i]);
    }
}

stock ShowPlayerWindowsInterraction(playerid)
{
    DebugPanelsInterraction(playerid);
    HidePanelsInterractionForPlayer(playerid);

    for(new i = 10; i < 21; i++)
    {
        TextDrawShowForPlayer(playerid, Interraction_GlobalTD[i]);
    }

    return 1;
}

stock HidePanelsInterractionForPlayer(playerid)
{
    for(new i = 10; i < 21; i++)
    {
        TextDrawHideForPlayer(playerid, Interraction_GlobalTD[i]);
    }

    return 1;
}

stock ShowPlayerDoorsInterraction(playerid)
{
    for(new i = 21; i < 32; i++)
    {
        TextDrawShowForPlayer(playerid, Interraction_GlobalTD[i]);
    }

    return 1;
}

stock HidePlayerDoorsInterraction(playerid)
{
    for(new i = 21; i < 32; i++)
    {
        TextDrawHideForPlayer(playerid, Interraction_GlobalTD[i]);
    }
}

#include <YSI_Coding\y_hooks>
hook OnGameModeInit()
{
    ResetInterractionArray();
    CreateInterractionTextdraw();
    return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    if(pUseInterractionPanels[playerid][pUsedInterractionPanels] == true)
    {
        pUseInterractionPanels[playerid][pUsedInterractionPanels] = false;
    }

    if(pUseInterractionPanels[playerid][pUsedWindowsPanels] == true)
    {
        pUseInterractionPanels[playerid][pUsedWindowsPanels] = false;
    }

    return 1;
}

hook OnPlayerClickTextDraw(playerid, Text:clickedid)
{
    if(clickedid == Text:INVALID_TEXT_DRAW)
    {
        if(pUseInterractionPanels[playerid][pUsedInterractionPanels] == true)
        {
            ResetInterractionPlayerArray(playerid);
            HideInterractionForPlayer(playerid);
            HidePanelsInterractionForPlayer(playerid);
            HidePlayerDoorsInterraction(playerid);
        }
    }

    if(clickedid == Interraction_GlobalTD[5])
    {
        if(pUseInterractionPanels[playerid][pUsedDoorsPanels] == true)
        {
            Msg(playerid, MSG_PREFIX_ERROR, "Ban khong the dieu chinh Windows Panels neu dang dieu chinh Doors Panels.");
            return 1;
        }

        pUseInterractionPanels[playerid][pUsedWindowsPanels] = !pUseInterractionPanels[playerid][pUsedWindowsPanels];
        if(pUseInterractionPanels[playerid][pUsedWindowsPanels] == true)
        {
            ShowPlayerWindowsInterraction(playerid);
            Msg(playerid, MSG_PREFIX_SUCCESS, "Ban dang dieu chinh Windows Panels.");
            return 1;
        }

        if(pUseInterractionPanels[playerid][pUsedWindowsPanels] == false)
        {
            HidePanelsInterractionForPlayer(playerid);
            pUseInterractionPanels[playerid][pUsedWindowsPanels] = false;
            Msg(playerid, MSG_PREFIX_SUCCESS, "Da tat di Windows Panels.");
            return 1;
        }
    }

    if(clickedid == Interraction_GlobalTD[6])
    {
        Interraction_Array[VehicleNearPlayer[playerid]][inter_Trunk] = !Interraction_Array[VehicleNearPlayer[playerid]][inter_Trunk];
        TextDrawHideForPlayer(playerid, Interraction_GlobalTD[1]);
        DebugInterractionPlayer(playerid);
        TextDrawShowForPlayer(playerid, Interraction_GlobalTD[1]);
    }

    if(clickedid == Interraction_GlobalTD[7])
    {
        Interraction_Array[VehicleNearPlayer[playerid]][inter_Hood] = !Interraction_Array[VehicleNearPlayer[playerid]][inter_Hood];
        TextDrawHideForPlayer(playerid, Interraction_GlobalTD[2]);
        DebugInterractionPlayer(playerid);
        TextDrawShowForPlayer(playerid, Interraction_GlobalTD[2]);
    }

    if(clickedid == Interraction_GlobalTD[8])
    {
        Interraction_Array[VehicleNearPlayer[playerid]][inter_lock] = !Interraction_Array[VehicleNearPlayer[playerid]][inter_lock];
        TextDrawHideForPlayer(playerid, Interraction_GlobalTD[3]);
        DebugInterractionPlayer(playerid);
        TextDrawShowForPlayer(playerid, Interraction_GlobalTD[3]);
    }

    if(clickedid == Interraction_GlobalTD[9])
    {
        if(pUseInterractionPanels[playerid][pUsedWindowsPanels] == true)
        {
            Msg(playerid, MSG_PREFIX_ERROR, "Ban khong the dieu chinh Doors Panels neu dang dieu chinh Windows Panels.");
            return 1;
        }

        pUseInterractionPanels[playerid][pUsedDoorsPanels] = !pUseInterractionPanels[playerid][pUsedDoorsPanels];
        if(pUseInterractionPanels[playerid][pUsedDoorsPanels] == true)
        {
            ShowPlayerDoorsInterraction(playerid);
            Msg(playerid, MSG_PREFIX_SUCCESS, "Ban dang dieu chinh Windows Panels.");
            return 1;
        }

        if(pUseInterractionPanels[playerid][pUsedDoorsPanels] == false)
        {
            HidePlayerDoorsInterraction(playerid);
            pUseInterractionPanels[playerid][pUsedDoorsPanels] = false;
            Msg(playerid, MSG_PREFIX_SUCCESS, "Da tat di Windows Panels.");
            return 1;
        }
    }

    if(clickedid == Interraction_GlobalTD[16])
    {
        Interraction_Array[VehicleNearPlayer[playerid]][inter_Windows_Above_Left] = !Interraction_Array[VehicleNearPlayer[playerid]][inter_Windows_Above_Left];
        TextDrawHideForPlayer(playerid, Interraction_GlobalTD[11]);
        DebugPanelsInterraction(playerid);
        TextDrawShowForPlayer(playerid, Interraction_GlobalTD[11]);
    }

    if(clickedid == Interraction_GlobalTD[17])
    {
        Interraction_Array[VehicleNearPlayer[playerid]][inter_Windows_Above_Right] = !Interraction_Array[VehicleNearPlayer[playerid]][inter_Windows_Above_Right];
        TextDrawHideForPlayer(playerid, Interraction_GlobalTD[12]);
        DebugPanelsInterraction(playerid);
        TextDrawShowForPlayer(playerid, Interraction_GlobalTD[12]);
    }

    if(clickedid == Interraction_GlobalTD[18])
    {
        Interraction_Array[VehicleNearPlayer[playerid]][inter_Windows_Below_Left] = !Interraction_Array[VehicleNearPlayer[playerid]][inter_Windows_Below_Left];
        TextDrawHideForPlayer(playerid, Interraction_GlobalTD[13]);
        DebugPanelsInterraction(playerid);
        TextDrawShowForPlayer(playerid, Interraction_GlobalTD[13]);
    }

    if(clickedid == Interraction_GlobalTD[19])
    {
        Interraction_Array[VehicleNearPlayer[playerid]][inter_Windows_Below_Right] = !Interraction_Array[VehicleNearPlayer[playerid]][inter_Windows_Below_Right];
        TextDrawHideForPlayer(playerid, Interraction_GlobalTD[14]);
        DebugPanelsInterraction(playerid);
        TextDrawShowForPlayer(playerid, Interraction_GlobalTD[14]);
    }

    if(clickedid == Interraction_GlobalTD[20])
    {
        Interraction_Array[VehicleNearPlayer[playerid]][inter_All_Windows] = !Interraction_Array[VehicleNearPlayer[playerid]][inter_All_Windows];
        if(Interraction_Array[VehicleNearPlayer[playerid]][inter_All_Windows] == true)
        {
            Interraction_Array[VehicleNearPlayer[playerid]][inter_Windows_Above_Left] = true;
            Interraction_Array[VehicleNearPlayer[playerid]][inter_Windows_Above_Right] = true;
            Interraction_Array[VehicleNearPlayer[playerid]][inter_Windows_Below_Left] = true;
            Interraction_Array[VehicleNearPlayer[playerid]][inter_Windows_Below_Right] = true;

            TextDrawSetString(Interraction_GlobalTD[15], "mdl-2001:All Windows ON");
        }
        else
        {
            Interraction_Array[VehicleNearPlayer[playerid]][inter_Windows_Above_Left] = false;
            Interraction_Array[VehicleNearPlayer[playerid]][inter_Windows_Above_Right] = false;
            Interraction_Array[VehicleNearPlayer[playerid]][inter_Windows_Below_Left] = false;
            Interraction_Array[VehicleNearPlayer[playerid]][inter_Windows_Below_Right] = false;

            TextDrawSetString(Interraction_GlobalTD[15], "mdl-2001:All Windows OFF");
        }

        TextDrawHideForPlayer(playerid, Interraction_GlobalTD[15]);
        Loop(i, 11, 15)
        {
            TextDrawHideForPlayer(playerid, Interraction_GlobalTD[i]);
        }

        DebugPanelsInterraction(playerid);
        
        Loop(i, 11, 15)
        {
            TextDrawShowForPlayer(playerid, Interraction_GlobalTD[i]);
        }
        
        TextDrawShowForPlayer(playerid, Interraction_GlobalTD[15]);
    }

    if(clickedid == Interraction_GlobalTD[27])
    {
        Interraction_Array[VehicleNearPlayer[playerid]][inter_Doors_Above_Left] = !Interraction_Array[VehicleNearPlayer[playerid]][inter_Doors_Above_Left];
        TextDrawHideForPlayer(playerid, Interraction_GlobalTD[22]);
        DebugDoorsPanelsInterraction(playerid);
        TextDrawShowForPlayer(playerid, Interraction_GlobalTD[22]);
    }

    if(clickedid == Interraction_GlobalTD[28])
    {
        Interraction_Array[VehicleNearPlayer[playerid]][inter_Doors_Above_Right] = !Interraction_Array[VehicleNearPlayer[playerid]][inter_Doors_Above_Right];
        TextDrawHideForPlayer(playerid, Interraction_GlobalTD[23]);
        DebugDoorsPanelsInterraction(playerid);
        TextDrawShowForPlayer(playerid, Interraction_GlobalTD[23]);
    }

    if(clickedid == Interraction_GlobalTD[29])
    {
        Interraction_Array[VehicleNearPlayer[playerid]][inter_Doors_Below_Left] = !Interraction_Array[VehicleNearPlayer[playerid]][inter_Doors_Below_Left];
        TextDrawHideForPlayer(playerid, Interraction_GlobalTD[24]);
        DebugDoorsPanelsInterraction(playerid);
        TextDrawShowForPlayer(playerid, Interraction_GlobalTD[24]);
    }

    if(clickedid == Interraction_GlobalTD[30])
    {
        Interraction_Array[VehicleNearPlayer[playerid]][inter_Doors_Below_Right] = !Interraction_Array[VehicleNearPlayer[playerid]][inter_Doors_Below_Right];
        TextDrawHideForPlayer(playerid, Interraction_GlobalTD[25]);
        DebugDoorsPanelsInterraction(playerid);
        TextDrawShowForPlayer(playerid, Interraction_GlobalTD[25]);
    }

    if(clickedid == Interraction_GlobalTD[31])
    {
        Interraction_Array[VehicleNearPlayer[playerid]][inter_All_Doors] = !Interraction_Array[VehicleNearPlayer[playerid]][inter_All_Doors];
        if(Interraction_Array[VehicleNearPlayer[playerid]][inter_All_Doors] == true)
        {
            Interraction_Array[VehicleNearPlayer[playerid]][inter_Doors_Above_Left] = true;
            Interraction_Array[VehicleNearPlayer[playerid]][inter_Doors_Above_Right] = true;
            Interraction_Array[VehicleNearPlayer[playerid]][inter_Doors_Below_Left] = true;
            Interraction_Array[VehicleNearPlayer[playerid]][inter_Doors_Below_Right] = true;

            TextDrawSetString(Interraction_GlobalTD[31], "mdl-2001:All Windows ON");
        }
        else
        {
            Interraction_Array[VehicleNearPlayer[playerid]][inter_Doors_Above_Left] = false;
            Interraction_Array[VehicleNearPlayer[playerid]][inter_Doors_Above_Right] = false;
            Interraction_Array[VehicleNearPlayer[playerid]][inter_Doors_Below_Left] = false;
            Interraction_Array[VehicleNearPlayer[playerid]][inter_Doors_Below_Right] = false;

            TextDrawSetString(Interraction_GlobalTD[31], "mdl-2001:All Windows OFF");
        }

        TextDrawHideForPlayer(playerid, Interraction_GlobalTD[31]);
        Loop(i, 21, 31)
        {
            TextDrawHideForPlayer(playerid, Interraction_GlobalTD[i]);
        }

        DebugDoorsPanelsInterraction(playerid);
        
        Loop(i, 21, 31)
        {
            TextDrawShowForPlayer(playerid, Interraction_GlobalTD[i]);
        }
        
        TextDrawShowForPlayer(playerid, Interraction_GlobalTD[31]);
    }

    if(clickedid == Interraction_GlobalTD[34])
    {
        Interraction_Array[VehicleNearPlayer[playerid]][inter_Engine] = !Interraction_Array[VehicleNearPlayer[playerid]][inter_Engine];
        TextDrawHideForPlayer(playerid, Interraction_GlobalTD[32]);
        DebugInterractionPlayer(playerid);
        TextDrawShowForPlayer(playerid, Interraction_GlobalTD[32]);
    }

    if(clickedid == Interraction_GlobalTD[35])
    {
        Interraction_Array[VehicleNearPlayer[playerid]][inter_Lights] = !Interraction_Array[VehicleNearPlayer[playerid]][inter_Lights];
        TextDrawHideForPlayer(playerid, Interraction_GlobalTD[33]);
        DebugInterractionPlayer(playerid);
        TextDrawShowForPlayer(playerid, Interraction_GlobalTD[33]);
    }

    return 1;
}

CMD:interraction(playerid)
{
    VehicleNearPlayer[playerid] = INVALID_VEHICLE_ID;

    new Float:x, Float:y, Float:z;
    foreach(new vehicleid : Vehicle)
    {
        GetVehiclePos(vehicleid, x, y, z);
        if(IsPlayerInRangeOfPoint(playerid, 3.0, x, y, z))
        {
            VehicleNearPlayer[playerid] = vehicleid;
            break;
        }
    }

    if(VehicleNearPlayer[playerid] == INVALID_VEHICLE_ID)
    {
        Msg(playerid, MSG_PREFIX_ERROR, "Ban khong o gan bat ki chiec xe nao.");
        return 1;
    }

    if(IsPlayerInAnyVehicle(playerid))
    {
        if(GetPlayerVehicleSeat(playerid) != 0)
        {
            Msg(playerid, MSG_PREFIX_ERROR, "Ban khong o vi tri tai xe de thuc hien dieu nay.");
            return 1;
        }

        ShowInterractionForPlayer(playerid);
        Msg(playerid, MSG_PREFIX_SUCCESS, "Ban da bat thanh cong bang dieu khien tren xe.");
    }
    else 
    {
        ShowInterracationOnGround(playerid);
        Msg(playerid, MSG_PREFIX_SUCCESS, "Ban da bat thanh cong bang dieu khien.");
    }

    SelectTextDraw(playerid, 0xFFFFF00FF);
    return 1;
}

CMD:createvehicle(playerid, params[])
{
    new Float:x, Float:y, Float:z;
    GetPlayerPos(playerid, x, y, z);
    CreateVehicle(strval(params), x, y, z, 0.0, 1, 1, 0);
    return 1;
}

/*--------- Credits: Halosetoe (Nguyễn Nam) ---------*/