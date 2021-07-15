#include <YSI_Coding\y_hooks>

hook OnPlayerDisconnect(playerid, reason)
{
    PlayerTextDrawHide(playerid, MessageTDLine[playerid][0]);
    if(MessageTDLine_Timer[playerid] != -1)
    {
        DeletePreciseTimer(MessageTDLine_Timer[playerid]);
        MessageTDLine_Timer[playerid] = -1;
    }

    if(MessageTDLine[playerid][0] != PlayerText:INVALID_PLAYER_TEXT_DRAW)
    {
        PlayerTextDrawDestroy(playerid, MessageTDLine[playerid][0]);
        MessageTDLine[playerid][0] = PlayerText:INVALID_PLAYER_TEXT_DRAW;
    }
    return 1;
}

hook OnPlayerText(playerid, text[])
{
    if(isPlayerConnected[playerid] == true)
    {

        if (array_AutoToggle[playerid][LOW_TOGGLE]) {
            SendSplitString(playerid, 3, text);
        }
        else if (array_AutoToggle[playerid][SHOUT_TOGGLE]) {
            SendSplitString(playerid, 4, text);
        }
        else {
            SendSplitString(playerid, 0, text);
        }
    }

    return 0;
}

forward KickPlayerDelayed(playerid);
public KickPlayerDelayed(playerid)
{
	Kick(playerid);
	return 1;
}