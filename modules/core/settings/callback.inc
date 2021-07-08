#include <YSI_Coding\y_hooks>
hook OnPlayerDisconnect(playerid, reason)
{
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