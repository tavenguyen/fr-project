stock Account_ReturnName(playerid, _type = 1)
{
    new name[MAX_PLAYER_NAME + 1];
    GetPlayerName(playerid, name, MAX_PLAYER_NAME + 1);
    switch(_type)
    {
        case 0:
        {
            String_RemoveChar(name, "_");
            return name;
        }
        case 1:
        {
            return name;
        }
    }

    return name;
}

stock KickEx(playerid, msg_type, const msg[], time = 500)
{
    Msg(playerid, msg_type, msg);
	SetPreciseTimer("KickPlayerDelayed", time, false, "d", playerid);
	return 1;
}

// Msg
stock Msg(playerid, type, const str[])
{
    switch(type)
    {
        case MSG_PREFIX_ERROR:
        {
            SendClientMessageStr(playerid, -1, str_format("[{FF1B1B}FRP-Error{FFFFFF}] %s", str));
        }
        case MSG_PREFIX_SUCCESS:
        {
            SendClientMessageStr(playerid, -1, str_format("[{0BFF19}FRP-Success{FFFFFF}] %s", str));
        }
    }

    return 1;
}

// Textdraw
forward MessageTDLine_HideForPlayer(playerid);
public MessageTDLine_HideForPlayer(playerid)
{
    if(MessageTDLine[playerid][0] != PlayerText:INVALID_PLAYER_TEXT_DRAW)
    {
        PlayerTextDrawSetString(playerid, MessageTDLine[playerid][0], "");
        PlayerTextDrawHide(playerid, MessageTDLine[playerid][0]);

        DeletePreciseTimer(MessageTDLine_Timer[playerid]);
        MessageTDLine_Timer[playerid] = -1;
    }

    return 1;
}

stock MessageTDLine_ShowForPlayer(playerid, const str[], time)
{
    if(MessageTDLine[playerid][0] == PlayerText:INVALID_PLAYER_TEXT_DRAW)
    {
        MessageTDLine[playerid][0] = CreatePlayerTextDraw(playerid, 319.000000, 390.083160, "a");
        PlayerTextDrawLetterSize(playerid, MessageTDLine[playerid][0], 0.206999, 1.133333);
        PlayerTextDrawAlignment(playerid, MessageTDLine[playerid][0], 2);
        PlayerTextDrawColor(playerid, MessageTDLine[playerid][0], -1);
        PlayerTextDrawSetShadow(playerid, MessageTDLine[playerid][0], 1);
        PlayerTextDrawSetOutline(playerid, MessageTDLine[playerid][0], 1);
        PlayerTextDrawBackgroundColor(playerid, MessageTDLine[playerid][0], 255);
        PlayerTextDrawFont(playerid, MessageTDLine[playerid][0], 1);
        PlayerTextDrawSetProportional(playerid, MessageTDLine[playerid][0], 1);
        PlayerTextDrawSetShadow(playerid, MessageTDLine[playerid][0], 1);
    }
    else
    {
        PlayerTextDrawSetString(playerid, MessageTDLine[playerid][0], str);
        PlayerTextDrawShow(playerid, MessageTDLine[playerid][0]);

        MessageTDLine_Timer[playerid] = SetPreciseTimer("MessageTDLine_HideForPlayer", time, false, "i", playerid);
    }

    return 1;
}
