CMD:createpayphone(playerid, params[])
{
    if(payPhoneAmount == MAX_PAYPHONE)
    {
        return SendClientMessage(playerid, -1, "Ban khong the tao them!");
    }
    
    new Float:x, Float:y, Float:z;
    GetPlayerPos(playerid, x, y, z);

    PayPhone_Create(playerid, x, y, z, _, _, _, GetPlayerInterior(playerid), GetPlayerVirtualWorld(playerid));
    Msg(playerid, MSG_PREFIX_SUCCESS, "Ban da tao thanh cong.");

    return 1;
}

CMD:deletepayphone(playerid, params[])
{
    if(payPhoneAmount == 0)
    {
        return SendClientMessage(playerid, -1, "May chu khong ton tai Payphone de xoa.");
    }
    
    new index;
    if(sscanf(params, "i", index))
    {
        SendClientMessage(playerid, -1, "SU DUNG: /deletepayphone [id-payphone]");
        return 1;
    }

    PayPhone_DestroyByIndex(index);
    return 1;
}
