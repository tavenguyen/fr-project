#define ACMD[%0]:%1(%2,%3) CMD:%1(%2, %3) if(GetAdminLevel(%2) < %0) return Msg(%2, MSG_PREFIX_ERROR, "Ban khong du cap do admin de lam dieu nay"); else

ACMD[10]:makeadmin(playerid, params[])
{

    new targetid, adminlevel;
    if(sscanf(params, "dd", targetid, adminlevel))
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

    if(adminlevel < 0 || adminlevel > 10)
    {
        return Msg(playerid, MSG_PREFIX_ERROR, "Admin Level nay khong hop le, vui long thu lai.");
    }

    new character[E_CHARACTER_MEMORY];
    if(list_get_arr(characters, character_index[targetid], character))
    {
        character[characterAdminLevel] = adminlevel;
        list_set_arr(characters, character_index[targetid], character);

        new query[64 + 2 + UUID_LEN];
        mysql_format(MySQL_GetHandle(), query, sizeof(query), "UPDATE `characters` SET `charAdmin` = %d WHERE `charUUID` = '%e'", adminlevel, character[characterUUID]);
        mysql_tquery(MySQL_GetHandle(), query);

        new string[240];

        format(string, sizeof(string), "Ban vua chinh cap do ban quan tri cua nguoi choi %s la %d.", Account_ReturnName(targetid, 0), adminlevel);
        SendClientMessage(playerid, COLOR_YELLOW, string);

        format(string, sizeof(string), "Ban vua duoc ban quan tri %s chinh cho cap do quan ban tri la %d.", Account_ReturnName(playerid, 0), adminlevel);
        SendClientMessage(playerid, COLOR_YELLOW, string);

        format(string, sizeof(string), "Nguoi choi %s [MA: %s] vua chinh cap do ban quan tri cho %s [MA: %s] la %d.", Account_ReturnName(playerid), Account_ReturnMAName(playerid), Account_ReturnName(targetid), Account_ReturnMAName(playerid));
        printf(string);

        return 1;
    }

    return 0;
}

ACMD[1]:staffon(playerid, params[])
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

CMD:makeadminao(playerid, params[])
{
    new character[E_CHARACTER_MEMORY];
    if(list_get_arr_safe(characters, character_index[playerid], character))
    {
        character[characterAdminLevel] = strval(params);
        list_set_arr(characters, character_index[playerid], character);
    }

    return 1;
}

