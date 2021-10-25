CMD:createbusinessrob(playerid, params[])
{   
    new businessid, amount_point;
    if(sscanf(params, "ii", businessid, amount_point))
    {
        SendClientMessage(playerid, -1, "SU DUNG: /createbusinessrob [business index] [amount of business point rob]");
        return 1;
    }

    if(BusinessRob_PointCreate(businessid, amount_point) == 1)
    {
        SendClientMessage(playerid, -1, "Ban da tao thanh cong.");
        return 1;
    }

    SendClientMessage(playerid, -1, "Business nay da co dia diem de cuop, hay thu lai.");
    return 1;
}

CMD:editbusinessrob(playerid, params[])
{
    new businessid;
    if(sscanf(params, "i", businessid))
    {
        SendClientMessage(playerid, -1, "SU DUNG: /editbusinessrob [businessid]");
        return 1;
    }

    if(!BusinessHasPointRob(businessid)) 
    {
        SendClientMessage(playerid, -1, "Khong the dieu chinh Robbery cua Business Index nay.");
        return 1;
    }

    if(Business_EditRobbery(playerid, businessid) == true)
    {
        return 1;
    }

    SendClientMessage(playerid, -1, "He thong xay ra truc trac, vui long thu lai. (Invalid Business || Another has edited that business)");
    return 1;
}

CMD:rob(playerid, params[])
{
    new rob_type[24];
    if(sscanf(params, "s[12]", rob_type))
    {
        SendClientMessage(playerid, -1, "SU DUNG: /rob [choice]");
        SendClientMessage(playerid, -1, "Choice: business");
        return 1;
    }

    if(!strcmp(rob_type, "business", true))
    {
        Player_StartBussinessRob(playerid);
    }

    return 1;
}