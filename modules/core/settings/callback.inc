#include <YSI_Coding\y_hooks>

hook OnPlayerDisconnect(playerid, reason)
{
    LoadingCircle_Stop(playerid);
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
        else if (array_AutoToggle[playerid][WHISPER_TOGGLE]) {
            if(strlen(text) > MAX_CHAT_STRING)
            {
                new new_line[128], old_line[128];
                strmid(new_line, text, MAX_CHAT_STRING, strlen(text));
                strmid(old_line, text, 0, MAX_CHAT_STRING);

                new cmd[144];
                format(cmd, sizeof(cmd), "Ban dang tham thi voi %s%s: %s...", Account_ReturnName(iWhisperTargetID[playerid], 0), Character_GetAccent(playerid), old_line);
                SendClientMessage(playerid, COLOR_YELLOW, cmd);
                
                format(cmd, sizeof(cmd), "... %s", new_line);
                SendClientMessage(playerid, COLOR_YELLOW, cmd);

                format(cmd, sizeof(cmd), "%s dang tham thi voi ban%s: %s...", Account_ReturnName(playerid, 0), Character_GetAccent(playerid), old_line);
                SendClientMessage(iWhisperTargetID[playerid], COLOR_YELLOW, cmd);

                format(cmd, sizeof(cmd), "... %s", new_line);
                SendClientMessage(iWhisperTargetID[playerid], COLOR_YELLOW, cmd);

                return 1;   
            }
            else {
                new cmd[144];
                format(cmd, sizeof(cmd), "Ban dang tham thi voi %s%s: %s", Account_ReturnName(iWhisperTargetID[playerid], 0), Character_GetAccent(playerid), text);
                SendClientMessage(playerid, COLOR_YELLOW, cmd);

                format(cmd, sizeof(cmd), "%s dang tham thi voi ban%s: %s", Account_ReturnName(playerid, 0), Character_GetAccent(playerid), text);
                SendClientMessage(iWhisperTargetID[playerid], COLOR_YELLOW, cmd);
            }
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