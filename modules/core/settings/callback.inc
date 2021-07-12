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
        new string[128];
        format(string, sizeof(string), "%s noi: %s", Account_ReturnName(playerid, 0), text);
        ProxDetector(playerid, 10.0, -1, string);
    }   
    return false;
}

forward KickPlayerDelayed(playerid);
public KickPlayerDelayed(playerid)
{
	Kick(playerid);
	return 1;
}