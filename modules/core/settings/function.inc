
#include <Character/config_character>

stock Account_ReturnName(playerid, _type = 1)
{
    new name[MAX_PLAYER_NAME + 1];
    GetPlayerName(playerid, name, MAX_PLAYER_NAME + 1);
    switch(_type)
    {
        case 0:
        {
            String_RemoveChar(name, '_');
            return name;
        }
        case 1:
        {
            return name;
        }
    }

    return name;
}

stock bool:PlayerIsConnected(playerid)
{
	if(isPlayerConnected[playerid] == true)
	{
		return true;
	}

	return false;
}

stock ClearChat(playerid)
{
    new t = 50;
    while(t-- >= 0)
    {
        SendClientMessage(playerid, -1, "");
    }
    return 1;
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
        case MSG_PREFIX_USAGE:
        {
            SendClientMessageStr(playerid, COLOR_GREY, str_format("%s", str));
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
        MessageTDLine[playerid][0] = CreatePlayerTextDraw(playerid, 318.000000, 427.416534, "MESSAGE BOX BY HALOSETOE");
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

stock bool:IsLunarYear(year)
{
    if(year % 400 == 0 && year % 100 != 0 || year % 400 == 0)
    {
        return true;
    }

    return false;
}

stock ProxDetector(playerid, Float:max_range, color, const string[], Float:max_ratio = 1.6)
{
	new
		Float:pos_x,
		Float:pos_y,
		Float:pos_z,
		Float:range,
		Float:range_ratio,
		Float:range_with_ratio,
		clr_r, clr_g, clr_b,
		Float:color_r, Float:color_g, Float:color_b;

	if (!GetPlayerPos(playerid, pos_x, pos_y, pos_z)) {
		return 0;
	}

	color_r = float(color >> 24 & 0xFF);
	color_g = float(color >> 16 & 0xFF);
	color_b = float(color >> 8 & 0xFF);
	range_with_ratio = max_range * max_ratio;

	foreach (new i : Player) 
    {
		if (!IsPlayerStreamedIn(i, playerid)) 
        {
			continue;
		}

        if(!PlayerIsConnected(i))
        {
            continue;
        }

		range = GetPlayerDistanceFromPoint(i, pos_x, pos_y, pos_z);
		if (range > max_range) {
			continue;
		}

		range_ratio = (range_with_ratio - range) / range_with_ratio;
		clr_r = floatround(range_ratio * color_r);
		clr_g = floatround(range_ratio * color_g);
		clr_b = floatround(range_ratio * color_b);

		SendClientMessage(i, (color & 0xFF) | (clr_b << 8) | (clr_g << 16) | (clr_r << 24), string);
	}

	SendClientMessage(playerid, color, string);
	return 1;
}

stock bool:IsRoleplayName(const name[])
{
    if(strlen(name) <= MAX_PLAYER_NAME)
    {
        new t = strlen(name);
        new count = 0;
        new position = 0;

        while(t-- >= 0)
        {
            if(name[t] == '_')
            {
                count++;
                position = t;
            }
        }
        
        if(count == 1)
        {
            if(name[position + 1] >= 65 && name[0] >= 65)
            {
                t = strlen(name);
                while(t-- > 0)
                {
                    if(t != position + 1)
                    {
                        if(name[t] < 65 || name[t] > 122)
                        {
                            return false;
                        }

                        if(name[t] > 90 && name[t] < 97 && name[t] != '_')
                        {
                            return false;
                        }
                    }
                }

                return true;
            }
        }
    }

    return false;
}

stock bool:CharCapitalization(string[])
{
    if(string[0] >= 97 && string[0] <= 122)
    {
        string[0] -= 32;
        return true;
    }

    return false;
}

stock SendSplitString(playerid, type, string[])
{
    if(type != 1)
    {
        CharCapitalization(string);
    }

    switch(type)
    {
        // chat
        case 0:
        {
            if(strlen(string) > MAX_CHAT_STRING)
            {
                new new_line[128], old_line[128];
                strmid(new_line, string, MAX_CHAT_STRING, strlen(string));
                strmid(old_line, string, 0, MAX_CHAT_STRING);

                new cmd[144];
                format(cmd, sizeof(cmd), "%s noi%s: %s...", Account_ReturnName(playerid, 0), Character_GetAccent(playerid), old_line);
                ProxDetector(playerid, 10.0, -1, cmd);
                
                format(cmd, sizeof(cmd), "... %s", new_line);
                ProxDetector(playerid, 10.0, -1, cmd);

                return 1;
            }

            new cmd[144];
            format(cmd, sizeof(cmd), "%s noi%s: %s", Account_ReturnName(playerid, 0), Character_GetAccent(playerid), string);
            ProxDetector(playerid, 10.0, -1, cmd);
            SetPlayerChatBubble(playerid, cmd, -1, 10.0, 3000);
            return 1;
        }
        // me
        case 1:
        {
            if(strlen(string) > MAX_CHAT_STRING)    
            {
                new new_line[128], old_line[128];
                strmid(new_line, string, MAX_CHAT_STRING, strlen(string));
                strmid(old_line, string, 0, MAX_CHAT_STRING);

                new cmd[144];
                format(cmd, sizeof(cmd), "* %s %s...", Account_ReturnName(playerid, 0), old_line);
                ProxDetector(playerid, 10.0, COLOR_ROLEPLAY, cmd);
                
                format(cmd, sizeof(cmd), "... %s (( %s ))", new_line, Account_ReturnName(playerid, 0));
                ProxDetector(playerid, 10.0, COLOR_ROLEPLAY, cmd);

                return 1;
            }

            new cmd[144];
            format(cmd, sizeof(cmd), "* %s %s", Account_ReturnName(playerid, 0), string);
            ProxDetector(playerid, 10.0, COLOR_ROLEPLAY, cmd);
            SetPlayerChatBubble(playerid, cmd, COLOR_ROLEPLAY, 10.0, 3000);

            return 1;
        }
        // do
        case 2:
        {   
            if(strlen(string) > MAX_CHAT_STRING)
            {
                new new_line[128], old_line[128];
                strmid(new_line, string, MAX_CHAT_STRING, strlen(string));
                strmid(old_line, string, 0, MAX_CHAT_STRING);

                new cmd[144];
                format(cmd, sizeof(cmd), "* %s...", old_line);
                ProxDetector(playerid, 10.0, COLOR_ROLEPLAY, cmd);
                
                format(cmd, sizeof(cmd), "... %s (( %s ))", new_line, Account_ReturnName(playerid, 0));
                ProxDetector(playerid, 10.0, COLOR_ROLEPLAY, cmd);

                return 1;
            }
            
            new cmd[144];
            format(cmd, sizeof(cmd), "* %s (( %s ))", string, Account_ReturnName(playerid, 0));
            ProxDetector(playerid, 10.0, COLOR_ROLEPLAY, cmd);
            return 1;
        }  
        // low
        case 3:
        {
            if(strlen(string) > MAX_CHAT_STRING)
            {
                new new_line[128], old_line[128];
                strmid(new_line, string, MAX_CHAT_STRING, strlen(string));
                strmid(old_line, string, 0, MAX_CHAT_STRING);

                new cmd[144];
                format(cmd, sizeof(cmd), "%s noi nho%s: %s...", Account_ReturnName(playerid, 0), Character_GetAccent(playerid), old_line);
                ProxDetector(playerid, 5.0, -1, cmd);
                
                format(cmd, sizeof(cmd), "... %s", new_line);
                ProxDetector(playerid, 5.0, -1, cmd);

                return 1;
            }

            new cmd[144];
            format(cmd, sizeof(cmd), "%s noi nho%s: %s", Account_ReturnName(playerid, 0), Character_GetAccent(playerid), string);
            ProxDetector(playerid, 5.0, -1, cmd);

            return 1;
        } 
        // shout
        case 4:
        {
            if(strlen(string) > MAX_CHAT_STRING)
            {
                new new_line[128], old_line[128];
                strmid(new_line, string, MAX_CHAT_STRING, strlen(string));
                strmid(old_line, string, 0, MAX_CHAT_STRING);

                new cmd[144];
                format(cmd, sizeof(cmd), "%s het to%s: %s...", Account_ReturnName(playerid, 0), Character_GetAccent(playerid), old_line);
                ProxDetector(playerid, 15.0, -1, cmd);
                
                format(cmd, sizeof(cmd), "... %s", new_line);
                ProxDetector(playerid, 15.0, -1, cmd);

                return 1;
            }

            new cmd[144];
            format(cmd, sizeof(cmd), "%s het to%s: %s", Account_ReturnName(playerid, 0), Character_GetAccent(playerid), string);
            ProxDetector(playerid, 15.0, -1, cmd);

            return 1;
        }
    }

    return 0;
}

stock Character_GetAccent(playerid)
{
    new string[144 + 24];
    new character[E_CHARACTER_MEMORY];

    if(list_get_arr_safe(characters, character_index[playerid], character))
    {
        if(!strcmp(character[characterAccent], "none"))
        {   
            format(string, sizeof(string), "");
        }
        else
        {
            format(string, sizeof(string), " [%s]", character[characterAccent]);
        }
    }

    return string;
}

stock GetAdminLevel(playerid)
{
    new character[E_CHARACTER_MEMORY];
    if(list_get_arr_safe(characters, character_index[playerid], character))
    {
        return character[characterAdminLevel];
    }

    return 0;
}

stock Account_ReturnMAName(playerid)
{
    new string[128];
    format(string, sizeof(string), "");

    new character[E_CHARACTER_MEMORY];
    if(list_get_arr_safe(characters, character_index[playerid], character))
    {
        format(string, sizeof(string), "%s", character[characterAccount]);
    }
    
    return string;
}