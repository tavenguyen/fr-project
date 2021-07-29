flags:createdoor(CMD_FLAG_ADM_HEAD)
CMD:createdoor(playerid, params[])
{   
    new 
        Float:x, Float:y, Float:z,
        index = -1, string[128];
    
    GetPlayerPos(playerid, x, y, z);
    
    index = Door_Create(x, y, z, GetPlayerInterior(playerid), GetPlayerVirtualWorld(playerid));

    format(string, sizeof(string), "Ban vua tao ra mot Door [%d] o ngay vi tri cua ban, hay su dung /editdoor.", index);
    Msg(playerid, MSG_PREFIX_SUCCESS, string);
    
    Door_FormatInformation(index);
    return 1;
}

flags:editdoor(CMD_FLAG_ADM_HEAD)
CMD:editdoor(playerid, params[])
{
    new doorid;
    if(sscanf(params, "d", doorid))
    {
        return Msg(playerid, MSG_PREFIX_USAGE, "SU DUNG: /editdoor [door id]");
    }

    if(doorid < 0 || doorid >= list_size(entrances_list))
    {
        return Msg(playerid, MSG_PREFIX_ERROR, "Door ID nay khong hop le, vui long thu lai.");
    }

    new playerEdit = GetPlayerEditDoor(doorid);
    if(playerEdit != INVALID_PLAYER_ID)
    {
        new string[54 + MAX_PLAYER_NAME + 1];
        format(string, sizeof(string), "Door ID nay dang duoc %s chinh sua, vui long thu lai.", Account_ReturnName(playerEdit, 0));
        return Msg(playerid, MSG_PREFIX_ERROR, string);
    }

    if(!IsTypeDoor(doorid) && !IsPlayerUseEditHouse(playerid))
    {
        return Msg(playerid, MSG_PREFIX_ERROR, "Ban khong the chinh sua Door nay.");
    }

    Door_EditByPlayer(playerid, doorid);
    return 1;
}

flags:deletedoor(CMD_FLAG_ADM_HEAD)
CMD:deletedoor(playerid, params[])
{
    new doorid;
    if(sscanf(params, "d", doorid))
    {
        return Msg(playerid, MSG_PREFIX_USAGE, "SU DUNG: /deletedoor [door id]");
    }

    if(doorid < 0 || doorid >= list_size(entrances_list))
    {
        return Msg(playerid, MSG_PREFIX_ERROR, "Door ID nay khong hop le, vui long thu lai.");
    }

    new playerEdit = GetPlayerEditDoor(doorid);
    if(playerEdit != INVALID_PLAYER_ID)
    {
        new string[54 + MAX_PLAYER_NAME + 1];
        format(string, sizeof(string), "Door ID nay dang duoc %s chinh sua, vui long thu lai.", Account_ReturnName(playerEdit, 0));
        return Msg(playerid, MSG_PREFIX_ERROR, string);
    }

    Door_DeleteByIndex(doorid);
    Msg(playerid, MSG_PREFIX_SUCCESS, "Ban da xoa thanh cong.");
    return 1;
}