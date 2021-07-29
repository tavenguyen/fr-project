/*--- Project was created on 12:54 - 7/7/2021---*/
//    Founder: Halosetoe                       //
//    Leader Scripter: Halosetoe              //
//    Scripter: Halosetoe                    //
//    Game Content: Halosetoe               //
/*--------- Freedom Roleplay v0.1 ---------*/

enum _:E_PERSONAL_HOUSE_DATA
{
    house_UUID[UUID_LEN],
    house_Describe[MAX_HOUSE_DESCRIBE],
    house_Owner_Name[MAX_PLAYER_NAME + 1],
    house_Price_sell,
    house_Key[24],
    bool:isHouseLocked,
    bool:isHouseSell
}

new List:houses;

stock House_GenerateKey(key[], const size = 24)
{
    format(key, size, "HOUSE-%c%c%c%c-%c%c%c%c", Utils_RandomChar(), Utils_RandomChar(), Utils_RandomChar(), Utils_RandomChar(), Utils_RandomChar(), Utils_RandomChar(), Utils_RandomChar(), Utils_RandomChar());
    return 1;
}

stock House_Create(const house_uuid[])
{
    new house[E_PERSONAL_HOUSE_DATA];
    strcat(house[house_UUID], house_uuid, UUID_LEN);
    format(house[house_Describe], sizeof(house[house_Describe]), "Khong co mieu ta cua ngoi nha.");
    format(house[house_Owner_Name], sizeof(house[house_Owner_Name]), "Khong co chu so huu.");
    House_GenerateKey(house[house_Key]);
    house[house_Price_sell] = 0;
    house[isHouseLocked] = true;
    house[isHouseSell] = true;

    new query[64 + UUID_LEN + MAX_HOUSE_DESCRIBE + MAX_PLAYER_NAME + 1 + 10 + 2];
    mysql_format(MySQL_GetHandle(), query, sizeof(query), 
        "INSERT INTO `houses` VALUES ('%e', '%e', '%e', '%e', %d, %d, %d)", house_uuid, house[house_Describe], house[house_Owner_Name], house[house_Key], 0, 1, 1);
    mysql_tquery(MySQL_GetHandle(), query);
    printf("[debug house] %s", query);

    return list_add_arr(houses, house);
}

stock bool:House_GetUUID(houseid, house_uuid[])
{
    if(houseid < 0 || houseid >= list_size(houses))
    {
        return false;
    }

    new house[E_PERSONAL_HOUSE_DATA];
    if(list_get_arr_safe(houses, houseid, house))
    {
        house_uuid[0] = EOS;
        strcat(house_uuid, house[house_UUID], UUID_LEN);
        return true;
    }

    return false;
}

stock bool:House_SetDescribe(houseid, const describe[])
{
    if(houseid < 0 || houseid >= list_size(houses))
    {
        return false;
    }

    if(strlen(describe) > MAX_HOUSE_DESCRIBE)
    {
        return false;
    }

    list_set_cell(houses, houseid, house_Describe, describe);

    new uuid[UUID_LEN];
    House_GetUUID(houseid, uuid);

    new query[75 + MAX_HOUSE_DESCRIBE + UUID_LEN];
    mysql_format(MySQL_GetHandle(), query, sizeof(query), "UPDATE `houses` SET `house_Describe` = %d WHERE `house_UUID` = '%e' LIMIT 1", describe, uuid);
    mysql_tquery(MySQL_GetHandle(), query);

    return true;
}

stock bool:House_GetDescribe(houseid, describe[])
{
    if(houseid < 0 || houseid >= list_size(houses))
    {
        return false;
    }

    new house[E_PERSONAL_HOUSE_DATA];
    if(list_get_arr_safe(houses, houseid, house))
    {
        if(isnull(house[house_Describe]))
        {
            return false;
        }

        format(describe, MAX_HOUSE_DESCRIBE, "%s", house[house_Describe]);
        return true;
    }

    return false;
}

stock bool:House_SetOwnerName(houseid, const name[])
{
    if(houseid < 0 || houseid >= list_size(houses))
    {
        return false;
    }

    if(strlen(name) > MAX_PLAYER_NAME + 1)
    {
        return false;
    }

    list_set_cell(houses, houseid, house_Owner_Name, name);
    
    new uuid[UUID_LEN];
    House_GetUUID(houseid, uuid);

    new query[77 + MAX_PLAYER_NAME + 1 + 37];
    mysql_format(MySQL_GetHandle(), query, sizeof(query), "UPDATE `houses` SET `house_Owner_Name` = %d WHERE `house_UUID` = '%e' LIMIT 1", name, uuid);
    mysql_tquery(MySQL_GetHandle(), query);

    return true;
}

stock bool:House_GetOwnerName(houseid, name[])
{
    if(houseid < 0 || houseid >= list_size(houses))
    {
        return false;
    }

    new house[E_PERSONAL_HOUSE_DATA];   
    if(list_get_arr_safe(houses, houseid, house))
    {
        name[0] = EOS;
        strcat(name, house[house_Owner_Name], sizeof(house[house_Owner_Name]));

        return true;
    }

    return false;
}

stock bool:House_SetPrice(houseid, price)
{
    if(houseid < 0 || houseid >= list_size(houses))
    {
        return false;
    }

    list_set_cell(houses, houseid, house_Price_sell, price);

    new uuid[UUID_LEN];
    House_GetUUID(houseid, uuid);

    new query[72 + 10 + 37];
    mysql_format(MySQL_GetHandle(), query, sizeof(query), "UPDATE `houses` SET `house_Price` = %d WHERE `house_UUID` = '%e' LIMIT 1", price, uuid);
    mysql_tquery(MySQL_GetHandle(), query);
    return true;
}

stock House_GetPrice(houseid)
{
    if(houseid < 0 || houseid >= list_size(houses))
    {
        return (-1);
    }

    new house[E_PERSONAL_HOUSE_DATA];
    if(list_get_arr_safe(houses, houseid, house))
    {
        return house[house_Price_sell];
    }

    return (-1);
}

stock bool:House_SetLock(houseid, value)
{
    if(houseid < 0 || houseid >= list_size(houses))
    {
        return false;
    }

    new bool:condition = false;
    if(value == 1) 
    {
        condition = true;
    }

    list_set_cell(houses, houseid, isHouseLocked, condition);

    new uuid[UUID_LEN];
    House_GetUUID(houseid, uuid);

    new query[71 + 2 + 37];
    mysql_format(MySQL_GetHandle(), query, sizeof(query), "UPDATE `houses` SET `house_Lock` = %d WHERE `house_UUID` = '%e' LIMIT 1", value, uuid);
    mysql_tquery(MySQL_GetHandle(), query);

    return true;   
}

stock bool:House_ReturnBool_Lock(houseIndex)
{
    if(houseIndex < 0 || houseIndex >= list_size(houses))
    {
        return false;
    }

    new house[E_PERSONAL_HOUSE_DATA];
    if(list_get_arr_safe(houses, houseIndex, house))
    {
        if(house[isHouseLocked] == true)
        {
            return true;
        }
    }

    return false;
}

stock House_ReturnString_Lock(houseIndex)
{
    new string[] = "He thong xay ra truc trac.";
    if(houseIndex < 0 || houseIndex >= list_size(houses))
    {
        return string;
    }

    format(string, sizeof(string), "Khong khoa.");
    if(House_ReturnBool_Lock(houseIndex) == true)
    {
        format(string, sizeof(string), "Dang khoa.");
    }

    return string;
}

stock bool:House_SetSell(houseid, value)
{
    if(houseid < 0 || houseid >= list_size(houses))
    {
        return false;
    }

    new bool:condition = false;
    if(value == 1) 
    {
        condition = true;
    }

    list_set_cell(houses, houseid, isHouseSell, condition);

    new uuid[UUID_LEN];
    House_GetUUID(houseid, uuid);

    new query[71 + 2 + 37];
    mysql_format(MySQL_GetHandle(), query, sizeof(query), "UPDATE `houses` SET `house_Sell` = %d WHERE `house_UUID` = '%e' LIMIT 1", value, uuid);
    mysql_tquery(MySQL_GetHandle(), query);

    return true;   
}

stock bool:IsHouseSell(houseid)
{
    if(houseid < 0 || houseid >= list_size(houses))
    {
        return false;
    }

    new house[E_PERSONAL_HOUSE_DATA];
    if(list_get_arr_safe(houses, houseid, house))
    {
        if(house[isHouseSell] == true)
        {
            return true;
        }
    }

    return false;
}

stock bool:House_ReturnBool_Sell(houseIndex)
{
    if(houseIndex < 0 || houseIndex >= list_size(houses))
    {
        return false;
    }

    new house[E_PERSONAL_HOUSE_DATA];
    if(list_get_arr_safe(houses, houseIndex, house))
    {
        if(house[isHouseSell] == true)
        {
            return true;
        }
    }

    return false;
}

stock House_ReturnString_Sell(houseIndex)
{
    new string[] = "He thong xay ra truc trac.";
    if(houseIndex < 0 || houseIndex >= list_size(houses))
    {
        return string;
    }

    format(string, sizeof(string), "Khong ban");
    if(House_ReturnBool_Sell(houseIndex) == true)
    {
        format(string, sizeof(string), "Dang ban");
    }

    return string;
}

stock House_EditByPlayer(playerid, hID)
{
    ShowPlayerHouseEditDialog(playerid, hID);
    return 1;
}

stock bool:IsPlayerUseEditHouse(playerid)
{
    new character[E_CHARACTER_MEMORY];
    if(list_get_arr_safe(characters, character_index[playerid], character))
    {
        if(character[is_Char_Edit_House] == true)
        {
            return true;
        }
    }

    return false;
}

stock bool:IsHouseLock(houseID)
{
    if(houseID < 0 || houseID >= list_size(houses))
    {
        return false;
    }

    new house[E_PERSONAL_HOUSE_DATA];
    if(list_get_arr_safe(houses, houseID, house))
    {
        if(house[isHouseLocked] == true)
        {
            return true;
        }
    }   

    return false;
}

#include <types\config_door_house>
stock House_GetDoorID(const house_uuid[])
{
    new door_house[E_DOOR_HOUSE_MEMORY];
    for(new Iter:doorid = map_iter(m_doorHouseID); iter_inside(doorid); iter_move_next(doorid))
    {
        if(iter_get_arr_safe(doorid, door_house))
        {
            if(!strcmp(door_house[House_UUID], house_uuid))
            {
                return iter_get_key(doorid);
            }
        }
    }

    return (-1);
}

stock House_GetIconType(houseIndex)
{
    new iconID = -1;
    if(houseIndex < 0 || houseIndex >= list_size(houses))
    {
        return iconID;
    }

    new house_uuid[UUID_LEN];
    House_GetUUID(houseIndex, house_uuid);
    
    new doorid = House_GetDoorID(house_uuid);
    Door_GetIconIndex(doorid, iconID);

    return iconID;
}

stock House_GetIndexByDoorUUID(const door_uuid[])
{
    // Find an index of door house
    new 
        door_house[E_DOOR_HOUSE_MEMORY],
        door_house_index = -1,
        house_UUID_inside[UUID_LEN];

    house_UUID_inside[0] = EOS;
    for(new Iter:door_House_id_iter = map_iter(m_doorHouseID); iter_inside(door_House_id_iter); iter_move_next(door_House_id_iter))
    {
        if(iter_get_arr_safe(door_House_id_iter, door_house))
        {
            if(!strcmp(door_house[door_House_UUID], door_uuid))
            {
                strcat(house_UUID_inside, door_house[House_UUID], UUID_LEN);
                break;
            }
        }
    }

    new house[E_PERSONAL_HOUSE_DATA];
    for(new Iter:house_iter = list_iter(houses); iter_inside(house_iter); iter_move_next(house_iter))
    {
        if(iter_get_arr_safe(house_iter, house))
        {
            if(!strcmp(house[house_UUID], house_UUID_inside))
            {
                door_house_index = iter_get_key(house_iter);
            }
        }
    }

    return door_house_index;
}

ShowPlayerHouseEditDialog(playerid, hID)
{
    new house_uuid[UUID_LEN];
    House_GetUUID(hID, house_uuid);

    new doorid = House_GetDoorID(house_uuid);
    if(doorid != -1)
    {
        new string[50];
        format(string, sizeof(string), "/editdoor %d", doorid);
        printf("[debug] %s", string);

        PC_EmulateCommand(playerid, string);
        return 1;
    }
    
    return 0;
}

#include <YSI_Coding\y_hooks>
hook OnGameModeInit()
{
    houses = list_new();
    return 1;
}