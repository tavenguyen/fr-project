ACMD[6]:createdoor(playerid, params[])
{
    new Float:x, Float:y, Float:z;
    GetPlayerPos(playerid, x, y, z);
    
    new index = Door_Create(x, y, z, GetPlayerInterior(playerid), GetPlayerVirtualWorld(playerid));
    new string[128];
    format(string, sizeof(string), "Ban vua tao ra mot Door [%d] o ngay vi tri cua ban, hay su dung /editdoor.", index);
    Msg(playerid, MSG_PREFIX_SUCCESS, string);
    Door_FormatInformation(index);
    return 1;
}

ACMD[6]:editdoor(playerid, params[])
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

    Door_EditByPlayer(playerid, doorid);
    return 1;
}

ACMD[6]:deletedoor(playerid, params[])
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

    Door_Delete(doorid);
    Msg(playerid, MSG_PREFIX_SUCCESS, "Ban da xoa thanh cong.");
    return 1;
}