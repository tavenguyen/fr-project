/*------ Project was created on 12:54 - 7/7/2021-----*/
//    Founder: Halosetoe                            //
//    Leader Scripter: Halosetoe                    //
//    Scripter: Halosetoe, Huynh                    //
//    Game Content: Halosetoe                       //
/*-------------- Freedom Roleplay v0.1 --------------*/

public OnPlayerCommandText(playerid, cmdtext[])
{
    if(PlayerIsConnected(playerid) == false) 
    {
        return Msg(playerid, MSG_PREFIX_ERROR, "Ban chua dang nhap vao may chu.");
    }
    return 0;
} 

CMD:me(playerid, params[])
{
    new string[200];
    if(sscanf(params, "s[200]", string)) return Msg(playerid, MSG_PREFIX_USAGE, "SU DUNG: /me [hanh dong].");
    SendSplitString(playerid, 1, string);
    return 1;
}

CMD:do(playerid, params[])
{
    new string[200];
    if(sscanf(params, "s[200]", string)) return Msg(playerid, MSG_PREFIX_USAGE, "SU DUNG: /do [mo to su viec].");
    SendSplitString(playerid, 2, string);
    return 1;
}

CMD:low(playerid, params[])
{
    new string[200];
    if(sscanf(params, "s[200]", string)) return Msg(playerid, MSG_PREFIX_USAGE, "SU DUNG: /l(ow) [noi nho].");
    SendSplitString(playerid, 3, string);
    return 1;
}
alias:low("l")

CMD:shout(playerid, params[])
{
    new string[200];
    if(sscanf(params, "s[200]", string)) return Msg(playerid, MSG_PREFIX_USAGE, "SU DUNG: /l(ow) [noi nho].");
    SendSplitString(playerid, 4, string);
    return 1;
}
alias:shout("s")

CMD:whisper(playerid, params[])
{
    new targetid, choice[200];
    if(sscanf(params, "ds[200]", targetid, choice))
    {   
        return Msg(playerid, MSG_PREFIX_USAGE, "SU DUNG: /w(hisper) [targetid] [tin nhan].");
    }

    if(!PlayerIsConnected(targetid))
    {
        return Msg(playerid, MSG_PREFIX_ERROR, "Nguoi choi nay hien tai khong co trong may chu.");
    }

    if(playerid == targetid)
    {
        return Msg(playerid, MSG_PREFIX_ERROR, "Ban khong the tu /whisper cho ban than cua ban.");
    }

    new Float:x, Float:y, Float:z;
    GetPlayerPos(targetid, x, y, z);

    if(!IsPlayerInRangeOfPoint(playerid, 2.0, x, y, z))
    {
        return Msg(playerid, MSG_PREFIX_ERROR, "Nguoi choi khong o gan ban, vui long thu lai.");
    }

    if(strlen(choice) > MAX_CHAT_STRING)
    {
        new new_line[128], old_line[128];
        strmid(new_line, choice, MAX_CHAT_STRING, strlen(choice));
        strmid(old_line, choice, 0, MAX_CHAT_STRING);

        new cmd[144];
        format(cmd, sizeof(cmd), "Ban dang tham thi voi %s%s: %s...", Account_ReturnName(targetid, 0), Character_GetAccent(playerid), old_line);
        SendClientMessage(playerid, COLOR_YELLOW, cmd);
        
        format(cmd, sizeof(cmd), "... %s", new_line);
        SendClientMessage(playerid, COLOR_YELLOW, cmd);

        format(cmd, sizeof(cmd), "%s dang tham thi voi ban%s: %s...", Account_ReturnName(playerid, 0), Character_GetAccent(playerid), old_line);
        SendClientMessage(targetid, COLOR_YELLOW, cmd);

        format(cmd, sizeof(cmd), "... %s", new_line);
        SendClientMessage(targetid, COLOR_YELLOW, cmd);

        return 1;   
    }

    new cmd[144];
    format(cmd, sizeof(cmd), "Ban dang tham thi voi %s%s: %s", Account_ReturnName(targetid, 0), Character_GetAccent(playerid), choice);
    SendClientMessage(playerid, COLOR_YELLOW, cmd);

    format(cmd, sizeof(cmd), "%s dang tham thi voi ban%s: %s", Account_ReturnName(playerid, 0), Character_GetAccent(playerid), choice);
    SendClientMessage(targetid, COLOR_YELLOW, cmd);

    return 1;
}
alias:whisper("w")

CMD:pm(playerid, params[])
{
    new targetid, choice[144];
    if(sscanf(params, "ds[144]", targetid, choice))
    {   
        return Msg(playerid, MSG_PREFIX_USAGE, "SU DUNG: /pm [targetid] [tin nhan ooc].");
    }

    if(!PlayerIsConnected(targetid))
    {
        return Msg(playerid, MSG_PREFIX_ERROR, "Nguoi choi nay hien tai khong co trong may chu.");
    }

    if(playerid == targetid)
    {
        return Msg(playerid, MSG_PREFIX_ERROR, "Ban khong the tu /whisper cho ban than cua ban.");
    }

    new string[144];
    format(string, sizeof(string), "Ban dang noi chuyen OOC voi %s: %s", Account_ReturnName(targetid, 0), choice);
    SendClientMessage(playerid, COLOR_YELLOW, string);

    format(string, sizeof(string), "Nguoi choi %s dang nhan OOC den ban: %s", Account_ReturnName(playerid, 0), choice);
    SendClientMessage(playerid, COLOR_YELLOW, string);
    return 1;
}

CMD:b(playerid, params[])
{
    new choice[144];
    if(sscanf(params, "s[144]", choice))
    {
        Msg(playerid, MSG_PREFIX_USAGE, "SU DUNG: /b [tin nhan ooc].");
        return 1;
    }

    new string[144];
    format(string, sizeof(string), "(( [%d] %s noi: %s ))", playerid, Account_ReturnName(playerid), choice);
    ProxDetector(playerid, 10.0, COLOR_GREY, string);
    return 1;
}

CMD:accent(playerid, params[])
{
    new choice[MAX_CHARACTER_ACCENT + 1];
    if(sscanf(params, "s[24]", choice))
    {
        Msg(playerid, MSG_PREFIX_USAGE, "SU DUNG: /accent [giong noi]");
        Msg(playerid, MSG_PREFIX_USAGE, "Co the /accent none de loai bo giong noi.");
        return 1;
    }

    if(strlen(choice) > MAX_CHARACTER_ACCENT)
    {
        return Msg(playerid, MSG_PREFIX_ERROR, "Ban khong the dat qua gioi han cua Accent.");
    }

    new character[E_CHARACTER_MEMORY];
    if(list_get_arr_safe(characters, character_index[playerid], character))
    {
        format(character[characterAccent], sizeof(character[characterAccent]), "%s", choice);
        list_set_arr(characters, character_index[playerid], character);
        
        new string[34 + 24];
        format(string, sizeof(string), "Ban da chuyen doi giong noi sang %s.", choice);
        Msg(playerid, MSG_PREFIX_SUCCESS, string);

        new query[67 + 24 + UUID_LEN];
        mysql_format(MySQL_GetHandle(), query, sizeof(query), "UPDATE `characters` SET `charAccent` = '%e' WHERE `charUUID` = '%e'", choice, character[characterUUID]);
        mysql_tquery(MySQL_GetHandle(), query);

        return 1;
    }
    
    return 0;
}

CMD:mota(playerid, params[])
{
    new choice[24];
    if(sscanf(params, "s[24]", choice))
    {
        Msg(playerid, MSG_PREFIX_USAGE, "SU DUNG: /mota [choice]");
        Msg(playerid, MSG_PREFIX_USAGE, "Choice: show, myself, remove.");
        return 1;
    }
    
    if(!strcmp(choice, "show", true, 4))
    {
        new targetid;
        if(sscanf(params[5], "d", targetid))
        {
            Msg(playerid, MSG_PREFIX_USAGE, "SU DUNG: /mota show [targetid]");
            return 1;
        }    

        if(!PlayerIsConnected(targetid))
        {
            return Msg(playerid, MSG_PREFIX_ERROR, "Nguoi choi nay hien tai khong co trong may chu.");
        }

        new Float:x, Float:y, Float:z;
        GetPlayerPos(targetid, x, y, z);

        if(!IsPlayerInRangeOfPoint(playerid, 5.0, x, y, z))
        {
            return Msg(playerid, MSG_PREFIX_ERROR, "Ban khong the xem mo ta cua nguoi choi nay voi mot khoang cach qua xa.");
        }

        new character[E_CHARACTER_MEMORY];
        if(list_get_arr_safe(characters, character_index[targetid], character))
        {
            new string[MAX_CHARACTER_DESCRIBE + 29 + MAX_PLAYER_NAME + 1];

            format(string, sizeof(string), "Mo ta cua nguoi choi %s la: {fc6565}%s", Account_ReturnName(targetid, 0), character[characterDescribe]);
            if(!strcmp(character[characterDescribe], "none"))
            {
                if(playerid != targetid) 
                {
                    format(string, sizeof(string), "{fc6565}Nguoi choi %s khong co mo ta.", Account_ReturnName(targetid, 0));
                }
                else
                {
                    format(string, sizeof(string), "{fc6565}Mo ta cua ban than ban hien tai khong co.");
                }
            }

            SendClientMessage(playerid, -1, string);
            return 1;
        }

        return 0;
    }
    else if(!strcmp(choice, "myself", true, 6))
    {
        new str_describe[128];
        if(sscanf(params[7], "s[128]", str_describe))
        {
            Msg(playerid, MSG_PREFIX_USAGE, "SU DUNG: /mota myself [mo ta ban than cua ban]");
            return 1;
        }

        if(strlen(str_describe) > MAX_CHARACTER_DESCRIBE)
        {
            return Msg(playerid, MSG_PREFIX_ERROR, "Ban khong duoc nhap mo ta qua so luong quy dinh.");
        }

        new character[E_CHARACTER_MEMORY];
        if(list_get_arr_safe(characters, character_index[playerid], character))
        {
            format(character[characterDescribe], sizeof(character[characterDescribe]), "%s", str_describe);
            list_set_arr(characters, character_index[playerid], character);

            new string[128];
            format(string, sizeof(string), "Ban da mo ta ban than cua ban rang %s", str_describe);
            Msg(playerid, MSG_PREFIX_SUCCESS, string);

            new query[69 + 128 + UUID_LEN + 1];
            mysql_format(MySQL_GetHandle(), query, sizeof(query), "UPDATE `characters` SET `charDescribe` = '%e' WHERE `charUUID` = '%e'", str_describe, character[characterUUID]);
            mysql_tquery(MySQL_GetHandle(), query);

            return 1;
        }

        return 0;
    }
    else if(!strcmp(choice, "remove", true, 6))
    {
        new character[E_CHARACTER_MEMORY];
        if(list_get_arr_safe(characters, character_index[playerid], character))
        {
            if(!strcmp(character[characterDescribe], "none"))
            {
                Msg(playerid, MSG_PREFIX_ERROR, "Ban khong co mo ta de xoa.");
                return 1;
            }
            else
            {
                format(character[characterDescribe], sizeof(character[characterDescribe]), "none");
                Msg(playerid, MSG_PREFIX_SUCCESS, "Ban da xoa di mo ta cua ban than ban.");

                new query[69 + 4 + UUID_LEN];
                mysql_format(MySQL_GetHandle(), query, sizeof(query), "UPDATE `characters` SET `charDescribe` = '%e' WHERE `charUUID` = '%e'", "none", character[characterUUID]);
                mysql_tquery(MySQL_GetHandle(), query);

                return 1;
            }
        }
    }
    else Msg(playerid, MSG_PREFIX_ERROR, "Khong co su lua chon ma ban nhap vao, hay thu lai.");

    return 0;
}

CMD:al(playerid, params[])
{
    if (array_AutoToggle[playerid][SHOUT_TOGGLE]){
        SendClientMessage(playerid, COLOR_GREY, "Khong the bat tu dong noi nho khi ban chua tat tu dong het to.");
    }
    else if (array_AutoToggle[playerid][WHISPER_TOGGLE]){
        SendClientMessage(playerid, COLOR_GREY, "Khong the bat tu dong noi nho khi ban chua tat tu dong thi tham.");
    }
    else {
        array_AutoToggle[playerid][LOW_TOGGLE] = !array_AutoToggle[playerid][LOW_TOGGLE];

        if (array_AutoToggle[playerid][LOW_TOGGLE]) {
            SendClientMessage(playerid, COLOR_GREY, "Ban da bat che do tu dong noi nho.");
        }
        else {
            SendClientMessage(playerid, COLOR_GREY, "Ban da tat che do tu dong noi nho.");
        }
    }

    return 1;
}

CMD:as(playerid, params[])
{
    if (array_AutoToggle[playerid][LOW_TOGGLE]){
        SendClientMessage(playerid, COLOR_GREY, "Khong the bat tu dong het to khi ban chua tat tu dong noi nho.");
    }
    else if (array_AutoToggle[playerid][WHISPER_TOGGLE]){
        SendClientMessage(playerid, COLOR_GREY, "Khong the bat tu dong het to khi ban chua tat tu dong thi tham.");
    }
    else {
        array_AutoToggle[playerid][SHOUT_TOGGLE] = !array_AutoToggle[playerid][SHOUT_TOGGLE];

        if (array_AutoToggle[playerid][SHOUT_TOGGLE]) {
            SendClientMessage(playerid, COLOR_GREY, "Ban da bat che do tu dong het to.");
        }
        else {
            SendClientMessage(playerid, COLOR_GREY, "Ban da tat che do tu dong het to.");
        }
    }

    return 1;
}

CMD:aw(playerid, params[])
{
    new targetid, string[256];

    if (array_AutoToggle[playerid][LOW_TOGGLE]){
        SendClientMessage(playerid, COLOR_GREY, "Khong the bat tu dong thi tham khi ban chua tat tu dong noi nho.");
    }
    else if (array_AutoToggle[playerid][SHOUT_TOGGLE]){
        SendClientMessage(playerid, COLOR_GREY, "Khong the bat tu dong thi tham khi ban chua tat tu dong het to.");
    }
    else {

        if (sscanf(params, "i", targetid)){
            array_AutoToggle[playerid][WHISPER_TOGGLE] = false;
            return Msg(playerid, MSG_PREFIX_USAGE, "SU DUNG: /aw(hisper) [targetid].");
        }
        else {
            // Get position of player.
            new Float:x, Float:y, Float:z;
            GetPlayerPos(targetid, x, y, z);

            // Check if Player connected
            if(!PlayerIsConnected(targetid))
            {
                return Msg(playerid, MSG_PREFIX_ERROR, "Nguoi choi nay hien tai khong co trong may chu.");
            }
            else if(playerid == targetid)
            {
                return Msg(playerid, MSG_PREFIX_ERROR, "Ban khong the tu whisper cho ban than cua ban.");
            }
            else if(!IsPlayerInRangeOfPoint(playerid, 2.0, x, y, z)) 
            {
                return Msg(playerid, MSG_PREFIX_ERROR, "Nguoi choi khong o gan ban, vui long thu lai.");
            }
            else {
                array_AutoToggle[playerid][WHISPER_TOGGLE] = !array_AutoToggle[playerid][WHISPER_TOGGLE];
                iWhisperTargetID[playerid] = targetid;

                if (array_AutoToggle[playerid][WHISPER_TOGGLE]) {
                    format(string, sizeof(string), "Ban da bat che do tu dong thi tham voi %s", Account_ReturnName(targetid, 0));
                    SendClientMessage(playerid, COLOR_GREY, string);
                }
                else {
                    SendClientMessage(playerid, COLOR_GREY, "Ban da tat che do tu dong thi tham.");
                }
            }
        }
    }

    return 1;
}

CMD:admins(playerid, params[])
{
    new character[E_CHARACTER_MEMORY];
    new bool:hasAdmin = false;

    foreach(new i : Player)
    {
        if(list_get_arr_safe(characters, character_index[i], character))
        {
            if(character[characterAdminLevel] != 0)
            {
                if(hasAdmin == false)
                {
                    SendClientMessage(playerid, -1, "{19702e}Ban quan tri hien tai dang co mat trong may chu:");

                    hasAdmin = true;
                }
                
                SendClientMessageStr(playerid, -1, str_format("{d4000e}ID:{ffffff} %d | {d4000e}Admin Level:{ffffff} %d | {d4000e}Admin Name:{ffffff} %s | {d4000e}Onduty:{ffffff} %s", i, character[characterAdminLevel], character[characterAccount], Admin_ReturnStrDuty(i)));
            }
        }
    }

    if(hasAdmin == false)
    {
        SendClientMessage(playerid, -1, "{19702e}Khong co ban quan tri nao trong may chu.");
    }   

    return 1;
}