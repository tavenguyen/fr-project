flags:makeadmin(CMD_FLAG_ADM_EXECUTIVE)
CMD:makeadmin(playerid, params[])
{
    new targetid, adminlevel;
    if(sscanf(params, "ui", targetid, adminlevel))
    {
        return Msg(playerid, MSG_PREFIX_USAGE, "SU DUNG: /makeadmin [targeid] [admin level]");
    }

    if(!PlayerIsConnected(playerid))
    {
        return Msg(playerid, MSG_PREFIX_ERROR, "Nguoi choi nay khong co trong may chu, vui long thu lai.");
    }

    if(playerid == targetid)
    {
        return Msg(playerid, MSG_PREFIX_ERROR, "Ban khong the tu chinh cap do ban quan tri cho ban than cua minh.");
    }

    if(adminlevel < 0 || adminlevel > MAX_ADMIN_LEVEL)
    {
        return Msg(playerid, MSG_PREFIX_ERROR, "Admin Level nay khong hop le, vui long thu lai.");
    }

    if(GetAdminLevel(targetid) == adminlevel)
    {
        return Msg(playerid, MSG_PREFIX_ERROR, "Ban khong the dieu chinh duoc thu hang Staff cua nguoi nay.");
    }

    if(GetAdminLevel(targetid) == 1 && adminlevel != 1)
    {
        if(adminlevel == 2)
        {
            AdvHelper_SetAdvisorLevel(targetid, 2);
        }
        else AdvHelper_Remove(Account_ReturnName(targetid));
    }

    Character_SetAdminLevel(targetid, adminlevel);
        
    new string[240];
    format(string, sizeof(string), "Ban vua chinh cap do ban quan tri cua nguoi choi %s la %d.", Account_ReturnName(targetid, 0), adminlevel);
    SendClientMessage(playerid, COLOR_YELLOW, string);

    format(string, sizeof(string), "Ban vua duoc ban quan tri %s chinh cho cap do quan ban tri la %d.", Account_ReturnName(playerid, 0), adminlevel);
    SendClientMessage(targetid, COLOR_YELLOW, string);

    format(string, sizeof(string), "Nguoi choi %s [MA: %s] vua chinh cap do ban quan tri cho %s [MA: %s] la %d.", Account_ReturnName(playerid), Account_ReturnMAName(playerid), Account_ReturnName(targetid), Account_ReturnMAName(playerid), adminlevel);
    printf(string);
    return 0;
}

flags:staffon(CMD_FLAG_ADM_REPORTER)
CMD:staffon(playerid, params[])
{
    new character[E_CHARACTER_MEMORY];
    if(list_get_arr_safe(characters, character_index[playerid], character))
    {
        character[isAdminOnduty] = !character[isAdminOnduty];
        list_set_arr(characters, character_index[playerid], character);

        if(character[isAdminOnduty])
        {
            SendClientMessage(playerid, COLOR_GREY, "Ban vua bat che do lam viec ban quan tri.");
            
            new string[40 + MAX_PLAYER_NAME];
            format(string, sizeof(string), "{abd6c6}Ban quan tri %s vua bat che do lam viec.", Account_ReturnName(playerid, 0));
            SendClientMessageToAll(-1, string);
            return 1;
        }

        SendClientMessage(playerid, COLOR_GREY, "Ban vua tat di che do lam viec ban quan tri.");
    }    

    return 1;
}

flags:gotopos(CMD_FLAG_ADM_REPORTER)
CMD:gotopos(playerid, params[])
{
    new Float:x, Float:y, Float:z, interiorid, worldid;
    if(sscanf(params, "p<,>fffI(0)I(0)", x, y, z, interiorid, worldid))
    {
        Msg(playerid, MSG_PREFIX_USAGE, "SU DUNG: /gotopos [x] [y] [z] [int] [worldid].");
        return 1;
    }
    Streamer_UpdateEx(playerid, x, y, z, interiorid, worldid, _, 2000, 1);
    Msg(playerid, MSG_PREFIX_SUCCESS, "Ban da den vi tri ma ban muon.");
    return 1;
}

flags:gotoplayer(CMD_FLAG_ADM_REPORTER)
CMD:gotoplayer(playerid, params[])
{
    new targetid;
    if(sscanf(params, "d", targetid))  
    {
        Msg(playerid, MSG_PREFIX_USAGE, "SU DUNG: /gotoplayer [targetid].");
        return 1;
    }

    if(targetid == playerid)
    {
        Msg(playerid, MSG_PREFIX_ERROR, "Ban khong the Tele den chinh ban than cua minh.");
        return 1;
    }

    if(!PlayerIsConnected(targetid))
    {
        Msg(playerid, MSG_PREFIX_ERROR, "Ban khong the Tele den nguoi choi chua ket noi den may chu.");
        return 1;
    }   

    SetPlayerToTargetPos(playerid, targetid);
    Msg(playerid, MSG_PREFIX_SUCCESS, "Ban da den vi tri cua nguoi choi.");
    return 1;
}

CMD:makeadminao(playerid, params[])
{
    new character[E_CHARACTER_MEMORY];
    if(list_get_arr_safe(characters, character_index[playerid], character))
    {
        Character_SetAdminLevel(playerid, strval(params));
    }

    return 1;
}

