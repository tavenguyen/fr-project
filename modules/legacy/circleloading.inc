static
    LoadingCircle_Timer[MAX_PLAYERS] = -1,
    LoadingCircle_Count[MAX_PLAYERS] = 0,
    Text:LoadingCircle_TD[4] = Text:INVALID_TEXT_DRAW;

stock LoadingCircle_CreateTD()
{
    LoadingCircle_TD[0] = TextDrawCreate(275.499847, 338.250305, "mdl-2000:circle_loading");
    TextDrawLetterSize(LoadingCircle_TD[0], 0.000000, 0.000000);
    TextDrawTextSize(LoadingCircle_TD[0], 90.000000, 90.000000);
    TextDrawAlignment(LoadingCircle_TD[0], 1);
    TextDrawColor(LoadingCircle_TD[0], -1);
    TextDrawSetShadow(LoadingCircle_TD[0], 0);
    TextDrawSetOutline(LoadingCircle_TD[0], 0);
    TextDrawBackgroundColor(LoadingCircle_TD[0], 255);
    TextDrawFont(LoadingCircle_TD[0], 4);
    TextDrawSetProportional(LoadingCircle_TD[0], 0);
    TextDrawSetShadow(LoadingCircle_TD[0], 0);  

    LoadingCircle_TD[1] = TextDrawCreate(276.500000, 335.833374, "mdl-2000:circle_loading2");
    TextDrawLetterSize(LoadingCircle_TD[1], 0.000000, 0.000000);
    TextDrawTextSize(LoadingCircle_TD[1], 90.000000, 90.000000);
    TextDrawAlignment(LoadingCircle_TD[1], 1);
    TextDrawColor(LoadingCircle_TD[1], -1);
    TextDrawSetShadow(LoadingCircle_TD[1], 0);
    TextDrawSetOutline(LoadingCircle_TD[1], 0);
    TextDrawBackgroundColor(LoadingCircle_TD[1], 255);
    TextDrawFont(LoadingCircle_TD[1], 4);
    TextDrawSetProportional(LoadingCircle_TD[1], 0);
    TextDrawSetShadow(LoadingCircle_TD[1], 0);

    LoadingCircle_TD[2] = TextDrawCreate(283.799957, 335.899902, "mdl-2000:circle_loading4");
    TextDrawLetterSize(LoadingCircle_TD[2], 0.000000, 0.000000);
    TextDrawTextSize(LoadingCircle_TD[2], 90.000000, 90.000000);
    TextDrawAlignment(LoadingCircle_TD[2], 1);
    TextDrawColor(LoadingCircle_TD[2], -1);
    TextDrawSetShadow(LoadingCircle_TD[2], 0);
    TextDrawSetOutline(LoadingCircle_TD[2], 0);
    TextDrawBackgroundColor(LoadingCircle_TD[2], 255);
    TextDrawFont(LoadingCircle_TD[2], 4);
    TextDrawSetProportional(LoadingCircle_TD[2], 0);
    TextDrawSetShadow(LoadingCircle_TD[2], 0);

    LoadingCircle_TD[3] = TextDrawCreate(283.999938, 337.766693, "mdl-2000:circle_loading5");
    TextDrawLetterSize(LoadingCircle_TD[3], 0.000000, 0.000000);
    TextDrawTextSize(LoadingCircle_TD[3], 90.000000, 90.000000);
    TextDrawAlignment(LoadingCircle_TD[3], 1);
    TextDrawColor(LoadingCircle_TD[3], -1);
    TextDrawSetShadow(LoadingCircle_TD[3], 0);
    TextDrawSetOutline(LoadingCircle_TD[3], 0);
    TextDrawBackgroundColor(LoadingCircle_TD[3], 255);
    TextDrawFont(LoadingCircle_TD[3], 4);
    TextDrawSetProportional(LoadingCircle_TD[3], 0);
    TextDrawSetShadow(LoadingCircle_TD[3], 0);
}

stock LoadingCircle_Start(playerid, time = 200)
{
    LoadingCircle_Timer[playerid] = SetTimerEx("LoadingCircle_TimerFunction", time, true, "i", playerid);
    return 1;
}

stock LoadingCircle_Stop(playerid)
{
    TextDrawHideForPlayer(playerid, LoadingCircle_TD[0]);
    TextDrawHideForPlayer(playerid, LoadingCircle_TD[1]);
    TextDrawHideForPlayer(playerid, LoadingCircle_TD[2]);
    TextDrawHideForPlayer(playerid, LoadingCircle_TD[3]);

    KillTimer(LoadingCircle_Timer[playerid]);
    LoadingCircle_Count[playerid] = 0;
}

forward LoadingCircle_TimerFunction(playerid);
public LoadingCircle_TimerFunction(playerid)
{
    if(LoadingCircle_Count[playerid] != 0) TextDrawHideForPlayer(playerid, LoadingCircle_TD[LoadingCircle_Count[playerid] - 1]);
    if(LoadingCircle_Count[playerid] <= 3) TextDrawShowForPlayer(playerid, LoadingCircle_TD[LoadingCircle_Count[playerid]]);
    LoadingCircle_Count[playerid]++;

    if(LoadingCircle_Count[playerid] > 4)
    {
        LoadingCircle_Count[playerid] = 0;
    }
    return 1;

}

