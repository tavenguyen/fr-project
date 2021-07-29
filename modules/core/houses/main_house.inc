/*--- Project was created on 12:54 - 7/7/2021---*/
//    Founder: Halosetoe                       //
//    Leader Scripter: Halosetoe              //
//    Scripter: Halosetoe                    //
//    Game Content: Halosetoe               //
/*--------- Freedom Roleplay v0.1 ---------*/

flags:createhouse(CMD_FLAG_ADM_DIRECTOR)
CMD:createhouse(playerid, params[])
{
    new 
        Float:x, Float:y, Float:z, uuid[UUID_LEN];

    UUID(uuid, UUID_LEN);
    GetPlayerPos(playerid, x, y, z);

    if(DoorHouse_Create(uuid, x, y, z, GetPlayerInterior(playerid), GetPlayerVirtualWorld(playerid)) == 1)
    {
        House_Create(uuid);

        new doorid = House_GetDoorID(uuid);
        Door_FormatInformation(doorid);
    }
    return 1;
}

flags:edithouse(CMD_FLAG_ADM_DIRECTOR)
CMD:edithouse(playerid, params[])
{
    new hID;
    if(sscanf(params, "d", hID)) 
    {
        Msg(playerid, MSG_PREFIX_USAGE, "SU DUNG: /edithouse [door id]");
        return 1;
    }

    if(hID < 0 || hID >= list_size(houses)) 
    {
        Msg(playerid, MSG_PREFIX_ERROR, "Door id nay khong hop le, vui long thu lai.");
        return 1;
    }

    list_set_cell(characters, character_index[playerid], is_Char_Edit_House, true);
    
    House_EditByPlayer(playerid, hID);
    
    list_set_cell(characters, character_index[playerid], is_Char_Edit_House, false);
    return 1;
}

flags:gotohouse(CMD_FLAG_ADM_REPORTER)
CMD:gotohouse(playerid, params[])
{
    new houseid, type[10];
    if(sscanf(params, "ds[10]", houseid, type))
    {
        Msg(playerid, MSG_PREFIX_USAGE, "SU DUNG: /gotohouse [house id] [type]");
        Msg(playerid, MSG_PREFIX_USAGE, "Type: exterior, interior");
        return 1;
    }

    if(houseid < 0 || houseid >= list_size(houses))
    {
        Msg(playerid, MSG_PREFIX_ERROR, "Khong ton tai House ID nay.");
        return 1;
    }

    if(!strcmp(type, "exterior", true))
    {
        new house_uuid[UUID_LEN];
        House_GetUUID(houseid, house_uuid);
        
        new doorid = House_GetDoorID(house_uuid);
        if(Door_StreamPlayerToExterior(playerid, doorid, true))
        {
            Msg(playerid, MSG_PREFIX_SUCCESS, "Ban da den vi tri Exterior cua ngoi nha ban chon.");
        }
        
        return 1;
    }
    else if(!strcmp(type, "interior", true))
    {
        new house_uuid[UUID_LEN];
        House_GetUUID(houseid, house_uuid);
        
        new doorid = House_GetDoorID(house_uuid);
        if(Door_StreamPlayerToInterior(playerid, doorid, true))
        {
            Msg(playerid, MSG_PREFIX_SUCCESS, "Ban da den vi tri Interior cua ngoi nha ban chon.");
        }
        
        return 1;
    }

    Msg(playerid, MSG_PREFIX_ERROR, "Khong co su lua chon nay trong lenh, vui long thu lai.");
    return 1;
}