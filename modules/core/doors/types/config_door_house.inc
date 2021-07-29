/*--- Project was created on 12:54 - 7/7/2021---*/
//    Founder: Halosetoe                       //
//    Leader Scripter: Halosetoe              //
//    Scripter: Halosetoe                    //
//    Game Content: Halosetoe               //
/*--------- Freedom Roleplay v0.1 ---------*/

enum _:E_DOOR_HOUSE_MEMORY
{
    House_UUID[UUID_LEN],
    door_House_UUID[UUID_LEN]
}

new Map:m_doorHouseID;

stock DoorHouse_Create(const house_uuid[], Float:x, Float:y, Float:z, interiorid, worldid)
{
    new 
        index = Door_Create(x, y, z, interiorid, worldid),
        door_House[E_DOOR_HOUSE_MEMORY];

    Door_SetType(index, doorType_House);
    strcopy(door_House[House_UUID], house_uuid, UUID_LEN);
    Door_GetUUID(index, door_House[door_House_UUID]);

    new query[78 + 37 + 37 + 10];
    mysql_format(MySQL_GetHandle(), query, sizeof(query), "INSERT INTO `houses_portal` (houseportal_uuid, house_uuid) VALUES ('%e', '%e')", door_House[door_House_UUID], door_House[House_UUID]);
    mysql_tquery(MySQL_GetHandle(), query);

    return map_add_arr(m_doorHouseID, index, door_House);
}

stock DoorHouse_DestroyByUUID(const house_uuid[])
{
    new door_house[E_DOOR_HOUSE_MEMORY];
    for(new Iter:index = map_iter(m_doorHouseID); iter_inside(index); iter_move_next(index))
    {
        if(iter_get_arr_safe(index, door_house))
        {
            if(!strcmp(door_house[House_UUID], house_uuid))
            {
                Door_DestroyByUUID(door_house[door_House_UUID]);

                iter_erase_deep(index);
                return 1;
            }
        }
    }

    return 0;
}

stock Door_GetIconIndex(doorid, &doorHouse_IconIndex)
{
    if(doorid < 0 || doorid >= list_size(entrances_list))
    {
        return 0;
    }

    new door[E_DOORS_MEMORY];
    if(list_get_arr_safe(entrances_list, doorid, door))
    {
        doorHouse_IconIndex = door[doorExt_IconType];
        return 1;
    }

    return 0;
}

stock bool:IsDoorEditting(doorid)
{
    new door_uuid[UUID_LEN];
    Door_GetUUID(doorid, door_uuid);
    
    if(isnull(door_uuid))
    {
        return false;
    }

    new house_index = House_GetIndexByDoorUUID(door_uuid);
    if(House_ReturnID_Editor(house_index) != INVALID_PLAYER_ID)
    {
        return true;
    }

    return false;
}

stock House_ReturnID_Editor(houseID)
{
    new house_uuid[UUID_LEN];
    House_GetUUID(houseID, house_uuid);

    new doorid = House_GetIndexByDoorUUID(house_uuid);
    if(doorid < 0 || doorid >= list_size(entrances_list))
    {
        printf("[debug] error #1: Invalid doorid | Function: House_ReturnID_Editor");
        return INVALID_DOOR_ID;
    }

    new door[E_DOORS_MEMORY];
    if(list_get_arr_safe(entrances_list, doorid, door))
    {
        return door[playerEditDoorID];
    }

    return INVALID_PLAYER_ID;
}