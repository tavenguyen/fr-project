/*--- Project was created on 12:54 - 7/7/2021---*/
//    Founder: Halosetoe                       //
//    Leader Scripter: Halosetoe              //
//    Scripter: Halosetoe                    //
//    Game Content: Halosetoe               //
/*--------- Freedom Roleplay v0.1 ---------*/

#define                 MAX_DISTANCE_DOOR                    15.0

#define                 MAX_PLAYERS_SMALL_DOOR               5
#define                 MAX_PLAYERS_MEDIUM_DOOR              10
#define                 MAX_PLAYERS_LARGE_DOOR               15

#define                 INVALID_DOOR_ID                     -1

static const DOOR_EXTERIOR_ICON_TYPE = 19197;

forward bool:House_GetOwnerName(houseid, name[]);
forward bool:House_GetUUID(houseid, house_uuid[]);
forward bool:IsHouseLock(houseID);
forward bool:House_SetSell(houseid, value);
forward bool:IsHouseSell(houseid);
forward bool:House_SetLock(houseid, value); 
forward bool:House_SetPrice(houseid, price);

enum _:DoorTypeRoom
{
    doorTypeRoom_Small,
    doorTypeRoom_Medium,
    doorTypeRoom_Large
}

enum _:DoorType
{
    doorType_none,
    doorType_House,
    doorType_Business
}

enum _:E_DOORS_MEMORY
{
    doorUUID[UUID_LEN],
    doorName[MAX_DOOR_NAME],
    doorTypeRoom,   
    doorType,
    doorID_Pickup,
    doorExt_IconType,
    playerEditDoorID,
    Text3D:doorExt_Text3D,
    Float:doorExt_posX,
    Float:doorExt_posY,
    Float:doorExt_posZ,
    doorExt_Int,
    doorExt_VW,
    Float:doorInt_posX,
    Float:doorInt_posY,
    Float:doorInt_posZ,
    door_count_players,
    doorInt_Int,
    doorInt_VW,
}

static doorID_pEdit[MAX_PLAYERS] = -1;
static iconType_Door[] = {1672, 1212, 2037, 1644, 1240, 2709, 1314, 1273, 1239, 1272, 1274, 2710,
                          1213, 1275, 1254, 2034, 1313, 19602, 2044, 1241, 2033, 18631, 11738, 1247,
                          1242, 1654, 11736, 19832, 1650, 1253, 1252, 1575, 1576, 1577, 1578, 1579,
                          1580, 1248, 1277, 1210, 2061, 19522, 19523, 19524, 19131, 19134, 19132, 1636,
                          19135, 2045, 1581, 1276, 954, 2690, 2057, 1582, 19133, 2035, 2059, 1310,
                          1550, 1279, 1318, 19130, 2228, 2058, 2036, 2237, 2060, 19197, 19198, 19054};

static string_iconType[2000];

new
    doorID_playerNear[MAX_PLAYERS] = -1;

new 
    List:entrances_list,
    Map:checkpointMap_Door;

stock Door_Create(Float:x, Float:y, Float:z, interiorid, worldid)
{
    new door[E_DOORS_MEMORY];
    
    UUID(door[doorUUID], UUID_LEN);
    format(door[doorName], sizeof(door[doorName]), "Khong co ten.");
    door[doorExt_posX] = x;
    door[doorExt_posY] = y;
    door[doorExt_posZ] = z;
    door[doorExt_Int] = interiorid;
    door[doorExt_VW] = worldid;
    door[doorInt_posX] = 0.0;
    door[doorInt_posY] = 0.0;
    door[doorInt_posZ] = 0.0;
    door[doorInt_Int] = interiorid;
    door[doorInt_VW] = worldid;
    door[doorExt_IconType] = DOOR_EXTERIOR_ICON_TYPE;
    door[doorTypeRoom] = doorTypeRoom_Small;
    door[doorType] = doorType_none;
    door[playerEditDoorID] = INVALID_PLAYER_ID;
    door[door_count_players] = 0;

    door[doorID_Pickup] = CreateDynamicPickup(door[doorExt_IconType], 1, x, y, z, worldid, interiorid, _);
 
    new query[113 + UUID_LEN + 400];
    mysql_format(MySQL_GetHandle(), query, sizeof(query), 
            "INSERT INTO `doors` VALUES ('%e', '%e', %d, %d, %d, %.4f, %.4f, %.4f, %d, %d, %.4f, %.4f, %.4f, %d, %d)", 
        door[doorUUID], door[doorName], door[doorType], door[doorTypeRoom], door[doorExt_IconType],
        door[doorExt_posX], door[doorExt_posY], door[doorExt_posZ], door[doorExt_Int], door[doorExt_VW],
        door[doorInt_posX], door[doorInt_posY], door[doorInt_posZ], door[doorInt_Int], door[doorInt_VW]);

    mysql_tquery(MySQL_GetHandle(), query);

    return list_add_arr(entrances_list, door);
}

stock Door_DeleteByIndex(doorid)
{
    new 
        character[E_CHARACTER_MEMORY],
        door[E_DOORS_MEMORY];

    if(list_get_arr_safe(entrances_list, doorid, door))
    {
        foreach(new playerid : Player)
        {
            if(!PlayerIsConnected(playerid))
            {
                continue;
            }

            if(list_get_arr_safe(characters, character_index[playerid], character))
            {
                if(character[characterInDoor] == doorid)
                {
                    Streamer_UpdateEx(playerid, door[doorExt_posX], door[doorExt_posY], door[doorExt_posZ], door[doorExt_VW], door[doorExt_Int], 1000, 1);
                    Msg(playerid, MSG_PREFIX_SUCCESS, "Door nay bi ban quan tri xoa, he thong tu dong cho ban ra Exterior Pos cua Door.");
                
                    character[characterInDoor] = INVALID_DOOR_ID;
                    list_set_arr(characters, character_index[playerid], character);

                    new query[500];
                    mysql_format(MySQL_GetHandle(), query, sizeof(query), "UPDATE `characters` SET `charInDoor` = %d, `charPosX` = %.4f, `charPosY` = %.4f, `charPosZ` = %.4f, `charInteriorID` = %d, `charWorldID` = %d WHERE `charUUID` = '%e'", character[characterInDoor], door[doorExt_posX], door[doorExt_posY], door[doorExt_posZ], door[doorExt_Int], door[doorExt_VW], character[characterUUID]);
                    mysql_tquery(MySQL_GetHandle(), query);
                    printf(query);
                }
            }
        }
    }

    for(new Iter:player = list_iter(characters); iter_inside(player); iter_move_next(player))
    {
        if(iter_get_arr_safe(player, character))
        {
            if(character[characterInDoor] == doorid)
            {
                character[characterInDoor] = INVALID_DOOR_ID;
                character[characterPosX] = door[doorExt_posX];
                character[characterPosY] = door[doorExt_posY];
                character[characterPosZ] = door[doorExt_posZ];

                iter_set_arr(player, character);

                new query[500];
                mysql_format(MySQL_GetHandle(), query, sizeof(query), "UPDATE `characters` SET `charInDoor` = %d, `charPosX` = %.4f, `charPosY` = %.4f, `charPosZ` = %.4f, `charInteriorID` = %d, `charWorldID` = %d WHERE `charUUID` = '%e'", character[characterInDoor], door[doorExt_posX], door[doorExt_posY], door[doorExt_posZ], door[doorExt_Int], door[doorExt_VW], character[characterUUID]);
                mysql_query(MySQL_GetHandle(), query);
            }
        }
    }

    for(new Iter:index = map_iter(checkpointMap_Door); iter_inside(index); iter_move_next(index))
    {
        new doorInIter;
        if(iter_get_value_safe(index, doorInIter))
        {
            if(doorInIter == doorid)
            {
                DestroyDynamicCP(iter_get_key(index));
                iter_erase_deep(index);
                break;
            }
        }
    }

    if(list_get_arr_safe(entrances_list, doorid, door))
    {
        DestroyDynamicPickup(door[doorID_Pickup]);
        DestroyDynamic3DTextLabel(door[doorExt_Text3D]);
    }


    new query[44 + UUID_LEN];
    mysql_format(MySQL_GetHandle(), query, sizeof(query), "DELETE FROM `doors` WHERE `doorUUID` = '%e'", door[doorUUID]);
    mysql_tquery(MySQL_GetHandle(), query);
    
    list_remove_deep(entrances_list, doorid);
    return 0;
}

stock Door_DestroyByUUID(const door_uuid[])
{
    new door[E_DOORS_MEMORY];
    for(new Iter:doorID = list_iter(entrances_list); iter_inside(doorID); iter_move_next(doorID))
    {
        if(iter_get_arr_safe(doorID, door))
        {
            if(!strcmp(door[doorUUID], door_uuid))
            {
                Door_DeleteByIndex(iter_get_key(doorID));
                return 1;
            }
        }
    }

    return 0;
}

stock GetDoorType(const str[])
{
    if(!strcmp(str, "door", true))
    {
        return doorType_none;
    }

    if(!strcmp(str, "house", true))
    {
        return doorType_House;
    }

    if(!strcmp(str, "business", true))
    {
        return doorType_Business;
    }

    return (-1);
}

stock bool:Door_GetUUID(doorid, uuid[])
{
    if(doorid < 0 || doorid >= list_size(entrances_list))
    {
        return false;
    }

    new door[E_DOORS_MEMORY];
    if(list_get_arr_safe(entrances_list, doorid, door))
    {
        uuid[0] = EOS;
        strcat(uuid, door[doorUUID], sizeof(door[doorUUID]));
        return true;
    }

    return false;
}

stock bool:IsTypeDoor(doorid)
{
    if(doorid < 0 || doorid >= list_size(entrances_list))
    {
        return false;
    }

    new door[E_DOORS_MEMORY];
    if(list_get_arr_safe(entrances_list, doorid, door))
    {
        if(door[doorType] != doorType_none)
        {
            return false;
        }
    }

    return true;
}

stock bool:Door_SetType(doorid, type)
{
    if(doorid < 0 || doorid >= list_size(entrances_list))
    {
        return false;
    }

    new uuid[UUID_LEN];
    Door_GetUUID(doorid, uuid);

    new query[66 + 2 + 37];
    mysql_format(MySQL_GetHandle(), query, sizeof(query), "UPDATE `doors` SET `doorType` = %d WHERE `doorUUID` = '%e' LIMIT 1", type, uuid);
    mysql_tquery(MySQL_GetHandle(), query);
    list_set_cell(entrances_list, doorid, doorType, type);
    return true;
}

stock Door_GetPrice(index)
{
    new string[50];
    format(string, sizeof(string), "Error.");

    if(index < 0 || index >= list_size(entrances_list))
    {
        return string;
    }

    new door[E_DOORS_MEMORY];
    if(list_get_arr_safe(entrances_list, index, door))
    {
        new price = 0;
        if(door[doorType] == doorType_House)
        {
            new hID = House_GetIndexByDoorUUID(door[doorUUID]);
            price = House_GetPrice(hID);
        }

        new value[10];
        valstr(value, price);
        format(string, sizeof(string), "");

        if(strlen(value) > 3)
        {
            new temp = (strlen(value)/3) - 1;
            if(strlen(value) % 3 == 0)
            {
                temp = strlen(value)/3;
            }

            for(new i = 0; i < strlen(value); i++)
            {
                format(string, sizeof(string), "%s%c", string, value[i]);
                if(strlen(value) % 3 != 0)
                {
                    if(strlen(value) == 5)
                    {
                        if(i == 1)
                        {
                            format(string, sizeof(string), "%s.", string);
                        }
                    }
                    else
                    {
                        if(i == temp - 2 + strlen(value)%3 || i == (temp*3) + strlen(value)%3 - 1)
                        {
                            format(string, sizeof(string), "%s.", string);
                        }
                    }
                }
                else
                {
                    if(strlen(value) == 6)
                    {
                        if(i == 2)
                        {
                            format(string, sizeof(string), "%s.", string);
                        }
                    }

                    if(strlen(value) == 9)
                    {
                        if(i == 2 || i == 5)
                        {
                            format(string, sizeof(string), "%s.", string);
                        }
                    }
                }
                
            }
        }   
        else
        {
            format(string, sizeof(string), "%s", value);
        }
    }
    return string;
}

stock bool:Door_FormatInformation(index)
{
    if(index < 0 || index >= list_size(entrances_list))
    {
        return false;
    }

    new door[E_DOORS_MEMORY];
    if(list_get_arr_safe(entrances_list, index, door))
    {
        if(IsValidDynamicPickup(door[doorID_Pickup]))
        {
            DestroyDynamicPickup(door[doorID_Pickup]);
        }

        if(IsValidDynamic3DTextLabel(door[doorExt_Text3D]))
        {
            DestroyDynamic3DTextLabel(door[doorExt_Text3D]);
        }
        
        new text[128];
        switch(door[doorType])
        {
            case doorType_none: format(text, sizeof(text), "%s", door[doorName]);
            case doorType_House:
            {
                new 
                    houseid = House_GetIndexByDoorUUID(door[doorUUID]);
                    
                format(text, sizeof(text), "House Index: %d\nOwner House: %s\n%s", houseid, Door_GetOwner(index), House_ReturnString_Lock(houseid));
                if(IsHouseSell(houseid))
                {
                    format(text, sizeof(text), "House Index: %d\nOwner House: %s\n%s - Price: %s$\n%s", houseid, Door_GetOwner(index), House_ReturnString_Sell(houseid), Door_GetPrice(index), House_ReturnString_Lock(houseid));
                }
            }
        }

        door[doorID_Pickup] = CreateDynamicPickup(door[doorExt_IconType], 1, door[doorExt_posX], door[doorExt_posY], door[doorExt_posZ], door[doorExt_VW], door[doorExt_Int]);
        door[doorExt_Text3D] = CreateDynamic3DTextLabel(text, -1, door[doorExt_posX], door[doorExt_posY], door[doorExt_posZ] + 0.7, 5.0, _, _, _, door[doorExt_VW], door[doorExt_Int], _, 5.0);

        list_set_arr(entrances_list, index, door);
    }

    return false;
}

stock GetPlayerEditDoor(doorid)
{
    if(doorid < 0 || doorid >= list_size(entrances_list))
    {
        return INVALID_PLAYER_ID;
    }

    new door[E_DOORS_MEMORY];
    if(list_get_arr_safe(entrances_list, doorid, door))
    {
        return door[playerEditDoorID];
    }

    return INVALID_PLAYER_ID;
}

stock Door_GetTypeRoom(doorid)
{
    new door[E_DOORS_MEMORY];
    if(list_get_arr_safe(entrances_list, doorid, door))
    {
        return door[doorTypeRoom];
    }

    return (-1);
}

stock Door_GetStrTypeRoom(doorid)
{
    new string[] = "Khong tim thay Door";
    if(doorid < 0 || doorid >= list_size(entrances_list))
    {
        return string;
    }

    new type = Door_GetTypeRoom(doorid);
    switch(type)
    {
        case doorTypeRoom_Small: format(string, sizeof(string), "Small Door");
        case doorTypeRoom_Medium: format(string, sizeof(string), "Medium Door");
        case doorTypeRoom_Large: format(string, sizeof(string), "Large Door");
    }

    return string;
}

stock Door_GetType(doorid)
{
    if(doorid < 0 || doorid >= list_size(entrances_list))
    {
        printf("error #1: INVALID DOOR INDEX (Door_GetType)");
        return INVALID_DOOR_ID;
    }

    new door[E_DOORS_MEMORY];
    if(list_get_arr_safe(entrances_list, doorid, door))
    {
        return door[doorType];
    }

    return INVALID_DOOR_ID;
}

stock Door_GetMaxPlayers(doorid)
{
    if(doorid < 0 || doorid >= list_size(entrances_list))
    {
        return 0;
    }

    new door_inside[E_DOORS_MEMORY];
    if(list_get_arr_safe(entrances_list, doorid, door_inside))
    {
        switch(door_inside[doorTypeRoom])
        {
            case doorTypeRoom_Small: return MAX_PLAYERS_SMALL_DOOR;
            case doorTypeRoom_Medium: return MAX_PLAYERS_MEDIUM_DOOR;
            case doorTypeRoom_Large: return MAX_PLAYERS_LARGE_DOOR;
        }
    }

    return 0;
}

stock Door_GetOwner(doorid)
{
    new string[30];
    format(string, sizeof(string), "He thong xay ra truc trac.");

    if(doorid < 0 || doorid >= list_size(entrances_list))
    {
        return string;
    }

    new type = Door_GetType(doorid);
    switch(type)
    {
        case doorType_none:
        {
            format(string, sizeof(string), "Door khong co chu so huu.");
        }
        case doorType_House:
        {
            new uuid[UUID_LEN];
            Door_GetUUID(doorid, uuid);

            new 
                house_index = House_GetIndexByDoorUUID(uuid),
                house_owner_name[MAX_PLAYER_NAME + 1];

            House_GetOwnerName(house_index, house_owner_name);
            format(string, sizeof(string), "%s", house_owner_name);
            return string;
        }
        case doorType_Business:
        {
            // Update
        }
    }

    return string;
}

stock Door_ReturnStr_Sell(doorid)
{
    new string[30];
    format(string, sizeof(string), "Door khong hop le.");

    if(doorid < 0 || doorid >= list_size(entrances_list))
    {
        return string;
    }

    new door[E_DOORS_MEMORY];
    if(list_get_arr_safe(entrances_list, doorid, door))
    {
        switch(door[doorType])
        {
            case doorType_none: 
            {
                format(string, sizeof(string), "Door nay khong the ban.");
                return string;
            }

            case doorType_House:
            {
                new hID = House_GetIndexByDoorUUID(door[doorUUID]);
                format(string, sizeof(string), "%s", House_ReturnString_Sell(hID));
                return string;
            }
            
            case doorType_Business:
            {
                // Update
            }
        }
    }

    return string;
}

stock Door_ReturnPrice(doorid)
{
    if(doorid < 0 || doorid >= list_size(entrances_list))
    {
        printf("[debug] #error 1: invalid door index (Door_ReturnPrice)");
        return INVALID_DOOR_ID;
    }

    new door[E_DOORS_MEMORY];
    if(list_get_arr_safe(entrances_list, doorid, door))
    {
        switch(door[doorType])
        {
            case doorType_none: 
            {
                return 0;
            }

            case doorType_House:
            {
                new hID = House_GetIndexByDoorUUID(door[doorUUID]);
                return House_GetPrice(hID);
            }
            
            case doorType_Business:
            {
                // Update
            }
        }
    }

    printf("[debug] #error 1: invalid door index (Door_ReturnPrice)");
    return INVALID_DOOR_ID;
}

stock Door_ReturnStr_Locked(doorid)
{
    new string[30];
    format(string, sizeof(string), "Door khong hop le.");

    if(doorid < 0 || doorid >= list_size(entrances_list))
    {
        return string;
    }

    new door[E_DOORS_MEMORY];
    if(list_get_arr_safe(entrances_list, doorid, door))
    {
        switch(door[doorType])
        {
            case doorType_none: 
            {
                format(string, sizeof(string), "Door nay khong the khoa.");
                return string;
            }

            case doorType_House:
            {
                new hID = House_GetIndexByDoorUUID(door[doorUUID]);
                format(string, sizeof(string), "%s", House_ReturnString_Lock(hID));
                return string;
            }
            
            case doorType_Business:
            {
                // Update
            }
        }
    }

    return string;
}

stock Door_EditByPlayer(playerid, doorid)
{
    new door[E_DOORS_MEMORY];
    if(list_get_arr_safe(entrances_list, doorid, door))
    {
        door[playerEditDoorID] = playerid;
        list_set_arr(entrances_list, doorid, door);
        
        doorID_pEdit[playerid] = doorid;
        
        doormaindialog:
        task_yield(1);

        new str[1028];
        format(str, sizeof(str), 
            "Door ID:\t%d\n\
            Door Editting:\t%s\n\
            Door Owned:\t%s\n\
            Door Name:\t%s\n\
            Door Sell:\t%s\n\
            Door Price:\t%s$\n\
            Door Lock:\t%s\n\
            Exterior Icon Type:\t%d\n\
            Exterior Edit Position\tHay nhan vao day de lay dia diem Exterior\n\
            Interior Edit Position\tHay nhan vao day de lay dia diem Interior\n\
            Door Sized Type\t%s",
        doorid, Account_ReturnName(door[playerEditDoorID], 0), Door_GetOwner(doorid), door[doorName],
        Door_ReturnStr_Sell(doorid), Door_GetPrice(doorid), Door_ReturnStr_Locked(doorid),
        door[doorExt_IconType], Door_GetStrTypeRoom(doorid));
        
        new response_main[e_DIALOG_RESPONSE_INFO];
	    await_arr(response_main) ShowPlayerAsyncDialog(playerid, DIALOG_STYLE_TABLIST, "Door Edit", str, "Accept", "Cancel");
        if(response_main[E_DIALOG_RESPONSE_Response]) 
        {
            switch(response_main[E_DIALOG_RESPONSE_Listitem])
            {
                case 0: goto doormaindialog;
                case 1: goto doormaindialog;
                case 2: goto doormaindialog;
                case 3: goto doorName_edit;
                case 4: goto doorEdit_Sell;
                case 5: goto doorEdit_Price;
                case 6: goto doorEdit_Lock;
                case 7: goto doorIconType_input;
                case 8: goto doorEdit_ExteriorPos;
                case 9: goto doorEdit_InteriorPos;
                case 10: goto doorEdit_Type;
                default: goto dooredit_error;
            }
        }
        else
        {
            door[playerEditDoorID] = INVALID_PLAYER_ID;
            list_set_arr(entrances_list, doorid, door);
        
            doorID_pEdit[playerid] = -1;

            return 1;
        }

        doorName_edit:
        if(door[doorType] != doorType_none)
        {
            Msg(playerid, MSG_PREFIX_ERROR, "Ban khong the chinh sua Door Name cua Door ID nay.");
            goto doormaindialog;
            return 1;
        }

        new response_edit_namedoor[e_DIALOG_RESPONSE_INFO];
	    await_arr(response_edit_namedoor) ShowPlayerAsyncDialog(playerid, DIALOG_STYLE_INPUT, "Edit Door Name", "Ban hay nhap vao day ten ma ban muon doi.", "Accept", "Cancel");
        
        if(response_edit_namedoor[E_DIALOG_RESPONSE_Response]) 
        {   
            format(door[doorName], sizeof(door[doorName]), "%s", response_edit_namedoor[E_DIALOG_RESPONSE_InputText]); 
            list_set_arr(entrances_list, doorid, door);

            Msg(playerid, MSG_PREFIX_SUCCESS, "Ban da chinh sua thanh cong ten cua Door.");
        
            new query[60 + MAX_DOOR_NAME + UUID_LEN + 1];
            mysql_format(MySQL_GetHandle(), query, sizeof(query), "UPDATE `doors` SET `doorName` = '%e' WHERE `doorUUID` = '%e'", door[doorName], door[doorUUID]);
            mysql_tquery(MySQL_GetHandle(), query);

            Door_FormatInformation(doorid);
            Streamer_Update(playerid);

            goto doormaindialog;
        }
        else goto doormaindialog;

        doorEdit_Sell:
        switch(door[doorType])
        {
            case doorType_none:
            {
                Msg(playerid, MSG_PREFIX_ERROR, "The loai Door nay khong the dieu chinh.");
                goto doormaindialog;
            }
            case doorType_House:
            {
                new hID = House_GetIndexByDoorUUID(door[doorUUID]);
                if(IsHouseSell(hID) == true)
                {
                    House_SetSell(hID, 0);
                }
                else
                {
                    House_SetSell(hID, 1);
                }

                Door_FormatInformation(doorid);
                Msg(playerid, MSG_PREFIX_SUCCESS, "Ban da dieu chinh thanh cong.");
                Streamer_Update(playerid);
                goto doormaindialog;
            }
            case doorType_Business:
            {
                // Update
            }
        }

        doorEdit_Price:
        new response_editprice[e_DIALOG_RESPONSE_INFO];
        await_arr(response_editprice) ShowPlayerAsyncDialog(playerid, DIALOG_STYLE_INPUT, "Input price", "Hay nhap vao day so tien de ban", "Accept", "Close");
        if(response_editprice[E_DIALOG_RESPONSE_Response])
        {
            new price = strval(response_editprice[E_DIALOG_RESPONSE_InputText]);
            if(price < 0 || price > 999999999)
            {
                Msg(playerid, MSG_PREFIX_ERROR, "Ban khong the dieu chinh so tien khong hop le.");
                goto doorEdit_Price;
            }

            switch(door[doorType])
            {
                case doorType_none:
                {
                    Msg(playerid, MSG_PREFIX_ERROR, "The loai Door nay khong the dieu chinh.");
                    goto doormaindialog;
                }
                case doorType_House:
                {
                    new hID = House_GetIndexByDoorUUID(door[doorUUID]);
                    House_SetPrice(hID, price);
                    Msg(playerid, MSG_PREFIX_SUCCESS, "Ban da dieu chinh thanh cong.");
                    Door_FormatInformation(doorid);
                    Streamer_Update(playerid);
                    goto doormaindialog;
                }
                case doorType_Business:
                {
                    // Update
                }
            }
        }
        else goto doormaindialog;

        doorEdit_Lock:
        switch(door[doorType])
        {
            case doorType_none:
            {
                Msg(playerid, MSG_PREFIX_ERROR, "The loai Door nay khong the dieu chinh.");
                goto doormaindialog;
            }
            case doorType_House:
            {
                new hID = House_GetIndexByDoorUUID(door[doorUUID]);
                if(IsHouseLock(hID) == true)
                {
                    House_SetLock(hID, 0);
                }
                else
                {
                    House_SetLock(hID, 1);
                }

                Door_FormatInformation(doorid);
                Streamer_Update(playerid);
                Msg(playerid, MSG_PREFIX_SUCCESS, "Ban da dieu chinh thanh cong.");
                goto doormaindialog;
            }
            case doorType_Business:
            {
                // Update
            }
        }

        doorIconType_input:
        new response_input_IconType[e_DIALOG_RESPONSE_INFO];
        await_arr(response_input_IconType) ShowPlayerAsyncDialog(playerid, DIALOG_STYLE_INPUT, "Edit Door Icon Type", string_iconType, "Accept", "Cancel");
        if(response_input_IconType[E_DIALOG_RESPONSE_Response])
        {
            new value = strval(response_input_IconType[E_DIALOG_RESPONSE_InputText]);
            new bool:condition = false;

            for(new i = 0; i < 6*12; i++) 
            {
                if(iconType_Door[i] == value)
                {
                    condition = true;
                    break;
                }
            }

            if(condition == false)
            {
                Msg(playerid, MSG_PREFIX_ERROR, "ID ban nhap vao khong phu hop voi quy dinh, vui long thu lai.");
                goto doormaindialog;
            }

            door[doorExt_IconType] = value;
            list_set_arr(entrances_list, doorid, door);

            Door_FormatInformation(doorid);
            Streamer_Update(playerid);

            new query[65 + 10 + UUID_LEN];
            mysql_format(MySQL_GetHandle(), query, sizeof(query), "UPDATE `doors` SET `doorExtIconType` = %d WHERE `doorUUID` = '%e'", value, door[doorUUID]);
            mysql_tquery(MySQL_GetHandle(), query);

            Msg(playerid, MSG_PREFIX_SUCCESS, "Ban da dieu chinh thanh cong ID Icon Type cua Door.");
            goto doormaindialog;
        }
        else goto doormaindialog;

        doorEdit_ExteriorPos:
        new door_inside_ext[E_DOORS_MEMORY];
        for(new Iter:index = list_iter(entrances_list); iter_inside(index); iter_move_next(index))
        {
            if(iter_get_arr_safe(index, door_inside_ext) && iter_get_key(index) != doorid)
            {
                if(IsPlayerInRangeOfPoint(playerid, 1.0, door_inside_ext[doorExt_posX], door_inside_ext[doorExt_posY], door_inside_ext[doorExt_posZ]))
                {
                    Msg(playerid, MSG_PREFIX_ERROR, "Ban khong the dat vi tri Exterior cua Door gan voi Door khac.");
                    goto doormaindialog;
                }
            }
        }

        GetPlayerPos(playerid, door[doorExt_posX], door[doorExt_posY], door[doorExt_posZ]);
        door[doorExt_Int] =  GetPlayerInterior(playerid);
        door[doorExt_VW] = GetPlayerVirtualWorld(playerid);
        list_set_arr(entrances_list, doorid, door);

        Door_FormatInformation(doorid);
        Streamer_Update(playerid);

        new query_Ext[500];
        mysql_format(MySQL_GetHandle(), query_Ext, sizeof(query_Ext), "UPDATE `doors` SET `doorExt_posX` = %.4f, `doorExt_posY` = %.4f, `doorExt_posZ` = %.4f, `doorExt_Int` = %d, `doorExt_VW` = %d WHERE `doorUUID` = '%e'",door[doorExt_posX], door[doorExt_posY], door[doorExt_posZ], door[doorExt_Int], door[doorExt_VW], door[doorUUID]);
        mysql_tquery(MySQL_GetHandle(), query_Ext);

        Msg(playerid, MSG_PREFIX_SUCCESS, "Ban da dieu chinh thanh cong vi tri cua Exterior.");
        goto doormaindialog;

        doorEdit_InteriorPos:
        new door_inside_int[E_DOORS_MEMORY];
        for(new Iter:index = list_iter(entrances_list); iter_inside(index); iter_move_next(index))
        {
            if(iter_get_arr_safe(index, door_inside_int) && iter_get_key(index) != doorid)
            {
                if(IsPlayerInRangeOfPoint(playerid, 1.0, door_inside_int[doorInt_posX], door_inside_int[doorInt_posY], door_inside_int[doorInt_posZ]))
                {
                    Msg(playerid, MSG_PREFIX_ERROR, "Ban khong the dat vi tri Interior cua Door gan voi Door khac.");
                    goto doormaindialog;
                }
            }
        }

        GetPlayerPos(playerid, door[doorInt_posX], door[doorInt_posY], door[doorInt_posZ]);
        door[doorInt_Int] = GetPlayerInterior(playerid);
        door[doorInt_VW] = GetPlayerVirtualWorld(playerid);
        list_set_arr(entrances_list, doorid, door);

        Door_FormatInformation(doorid);
        Streamer_Update(playerid);

        new query_Int[500];
        mysql_format(MySQL_GetHandle(), query_Int, sizeof(query_Int), "UPDATE `doors` SET `doorInt_posX` = %.4f, `doorInt_posY` = %.4f, `doorInt_posZ` = %.4f, `doorInt_Int` = %d, `doorInt_VW` = %d WHERE `doorUUID` = '%e'", door[doorInt_posX], door[doorInt_posY], door[doorInt_posZ], door[doorInt_Int], door[doorInt_VW], door[doorUUID]);
        mysql_tquery(MySQL_GetHandle(), query_Int);

        for(new Iter:cpid = map_iter(checkpointMap_Door); iter_inside(cpid); iter_move_next(cpid))
        {
            new checkpointID, doorID_inIter; 
            if(iter_get_value_safe(cpid, doorID_inIter))
            {
                if(doorID_inIter == doorid)
                {
                    if(iter_get_key_safe(cpid, checkpointID))
                    {
                        DestroyDynamicCP(checkpointID);
                        iter_erase_deep(cpid);
                        break;
                    }
                }
            }
        }

        new cp_Index = CreateDynamicCP(door[doorInt_posX], door[doorInt_posY], door[doorInt_posZ], 1.0, door[doorInt_VW], door[doorInt_Int], _, 2.0);
        Streamer_SetIntData(STREAMER_TYPE_CP, cp_Index, E_STREAMER_EXTRA_ID, E_EXTRA_ID_DOOR);

        map_add(checkpointMap_Door, cp_Index, doorid);

        Msg(playerid, MSG_PREFIX_SUCCESS, "Ban da dieu chinh thanh cong vi tri cua Interior.");
        goto doormaindialog;

        doorEdit_Type:
        new response_edit_typedoor[e_DIALOG_RESPONSE_INFO];
        await_arr(response_edit_typedoor) ShowPlayerAsyncDialog(playerid, DIALOG_STYLE_LIST, "Ban hay chon loai danh cho Door", "Small\nMedium\nLarge", "Accept", "Cancel");
        if(response_edit_typedoor[E_DIALOG_RESPONSE_Response])
        {
            switch(response_edit_typedoor[E_DIALOG_RESPONSE_Listitem])
            {
                case 0: 
                {
                    if(door[doorTypeRoom] == doorTypeRoom_Small)
                    {
                        Msg(playerid, MSG_PREFIX_ERROR, "Ban khong the chon loai Door nay nua.");
                        goto doorEdit_Type;
                    }

                    door[doorTypeRoom] = doorTypeRoom_Small;
                    list_set_arr(entrances_list, doorid, door);
                }
                case 1:
                {
                    if(door[doorTypeRoom] == doorTypeRoom_Medium)
                    {
                        Msg(playerid, MSG_PREFIX_ERROR, "Ban khong the chon loai Door nay nua.");
                        goto doorEdit_Type;
                    }

                    door[doorTypeRoom] = doorTypeRoom_Medium;
                    list_set_arr(entrances_list, doorid, door);
                }
                case 2:
                {
                    if(door[doorTypeRoom] == doorTypeRoom_Large)
                    {
                        Msg(playerid, MSG_PREFIX_ERROR, "Ban khong the chon loai Door nay nua.");
                        goto doorEdit_Type;
                    }

                    door[doorTypeRoom] = doorTypeRoom_Large;
                    list_set_arr(entrances_list, doorid, door);
                }
            }

            new query[58 + 2 + UUID_LEN];
            mysql_format(MySQL_GetHandle(), query, sizeof(query), "UPDATE `doors` SET `doorTypeRoom` = %d WHERE `doorUUID` = '%e'", door[doorTypeRoom], door[doorUUID]);
            mysql_tquery(MySQL_GetHandle(), query);

            Msg(playerid, MSG_PREFIX_SUCCESS, "Ban da chon thanh cong loai moi danh cho Door.");

            goto doormaindialog;
        }

        dooredit_error:
        Msg(playerid, MSG_PREFIX_ERROR, "Case nay khong co hoac dang duoc cap nhat.");
        goto doormaindialog;
    }

    return 1;
}

stock GetDoorIDNearPlayer(playerid)
{
    new 
        door[E_DOORS_MEMORY],
        vw = GetPlayerVirtualWorld(playerid),
        interiorid = GetPlayerInterior(playerid);

    for(new Iter:doorid = list_iter(entrances_list); iter_inside(doorid); iter_move_next(doorid))
    {
        if(iter_get_arr_safe(doorid, door))
        {
            if(door[doorExt_Int] == interiorid && door[doorExt_VW] == vw)
            {
                if(IsPlayerInRangeOfPoint(playerid, 1.0, door[doorExt_posX], door[doorExt_posY], door[doorExt_posZ]))
                {
                    return iter_get_key(doorid);
                }
            }
        }
    }

    return (-1);
}

stock bool:IsPlayerInDoor(playerid)
{
    new character[E_CHARACTER_MEMORY];
    if(list_get_arr_safe(characters, character_index[playerid], character))
    {
        if(character[characterInDoor] != INVALID_DOOR_ID)
        {
            return true;
        }
    }

    return false;
}

stock IsDoorLocked(doorid)
{
    new type = Door_GetType(doorid);
    switch(type)
    {
        case doorType_none: return false;
        case doorType_House:
        {
            new uuid[UUID_LEN];
            Door_GetUUID(doorid, uuid); 
            
            new houseindex = House_GetIndexByDoorUUID(uuid);
            if(IsHouseLock(houseindex) == true)
            {
                return true;
            }

            return false;
        }
    }

    return false;
}

stock PlayerInDoorLeave(playerid)
{
    new character[E_CHARACTER_MEMORY];
    if(list_get_arr_safe(characters, character_index[playerid], character))
    {
        if(character[characterInDoor] == INVALID_DOOR_ID)
        {
            return 0;
        }

        if(character[characterInDoor] < 0 || character[characterInDoor] >= list_size(entrances_list))
        {
            return 0;
        }

        new door[E_DOORS_MEMORY];
        if(list_get_arr_safe(entrances_list, character[characterInDoor], door))
        {
            door[door_count_players]--;
            list_set_arr(entrances_list, character[characterInDoor], door);

            return 1;
        }
    }

    return 0;
}

Door_StreamPlayerToInterior(playerid, index, bool:useAdminCommand = false)
{
    new door[E_DOORS_MEMORY];
    list_get_arr_safe(entrances_list, index, door);
    
    if(door[doorInt_posX] == 0.0 && door[doorInt_posY] == 0.0 && door[doorInt_posZ] == 0.0)
    {
        Msg(playerid, MSG_PREFIX_ERROR, "Interior nay chua duoc thiet lap, vui long thu lai.");
        return 0;
    }

    if(useAdminCommand == false)
    {
        if(door[door_count_players] == Door_GetMaxPlayers(index))
        {
            Msg(playerid, MSG_PREFIX_ERROR, "Ban khong the vao vi da du so luong nguoi choi trong Door.");
            return 1;
        }
    }   

    new character[E_CHARACTER_MEMORY];
    if(list_get_arr_safe(characters, character_index[playerid], character))
    {
        if(useAdminCommand == false)
        {
            if(character[characterInDoor] == index)
            {
                Msg(playerid, MSG_PREFIX_ERROR, "Ban dang o trong Door nay, ban khong the vao trong duoc nua.");
                return 1;
            }

            if(character[characterInDoor] != INVALID_DOOR_ID)
            {
                list_get_arr_safe(entrances_list, character[characterInDoor], door);
                door[door_count_players]--;

                list_set_arr(entrances_list, character[characterInDoor], door);
                SendClientMessageStr(playerid, -1, str_format("Door ID: %d | Door Count Players: %d", character[characterInDoor], door[door_count_players]));
            }
        }

        character[characterInDoor] = index;
        list_set_arr(characters, character_index[playerid], character);

        new query[65 + UUID_LEN + 10];
        mysql_format(MySQL_GetHandle(), query, sizeof(query), "UPDATE `characters` SET `charInDoor` = %d WHERE `charUUID` = '%e'", index, character[characterUUID]);
        mysql_query(MySQL_GetHandle(), query);

        list_get_arr_safe(entrances_list, index, door);

        FadePlayerScreen(playerid, 0, _, 1000);
        Streamer_UpdateEx(playerid, door[doorInt_posX], door[doorInt_posY], door[doorInt_posZ], door[doorInt_VW], door[doorInt_Int], _, 1000, 1);
        
        if(useAdminCommand == false)
        {
            door[door_count_players]++;
            list_set_arr(entrances_list, index, door);

            SendClientMessageStr(playerid, -1, str_format("Door ID: %d | Door Count Players: %d", character[characterInDoor], door[door_count_players]));
        }
    }

    return 1;
}

Door_StreamPlayerToExterior(playerid, index, bool:useAdminCommand = false)
{
    new door[E_DOORS_MEMORY];
    if(list_get_arr_safe(entrances_list, index, door))
    {
        if(useAdminCommand == false)
        {
            door[door_count_players]--;
            list_set_arr(entrances_list, index, door);
            SendClientMessageStr(playerid, -1, str_format("[debug] Door ID: %d | Door Count Players: %d", index, door[door_count_players]));
        }

        FadePlayerScreen(playerid, 0, _, 1000);
        Streamer_UpdateEx(playerid, door[doorExt_posX], door[doorExt_posY], door[doorExt_posZ], door[doorExt_VW], door[doorExt_Int], _, 1000, 1);
    
        new character[E_CHARACTER_MEMORY];
        if(list_get_arr_safe(characters, character_index[playerid], character))
        {
            character[characterInDoor] = INVALID_DOOR_ID;
            list_set_arr(characters, character_index[playerid], character);

            new query[65 + UUID_LEN + 10];
            mysql_format(MySQL_GetHandle(), query, sizeof(query), "UPDATE `characters` SET `charInDoor` = %d WHERE `charUUID` = '%e'", character[characterInDoor], character[characterUUID]);
            mysql_query(MySQL_GetHandle(), query);
            return 1;
        }
    }
    
    return 0;
}


#include <YSI_Coding\y_hooks>

#include <types\config_door_house>

hook OnGameModeInit()
{
    new dem = 0;
    format(string_iconType, sizeof(string_iconType), "Ban co the chon mot so ID cua Icon duoc quy dinh o duoi day, ban khong duoc su dung ID khac:");

    for(new i = 1; i <= 6; i++)
    {
        format(string_iconType, sizeof(string_iconType), "%s\n\t[", string_iconType);

        for(new j = 0; j < 12; j++)
        {
            if(j != 11)
            {
                format(string_iconType, sizeof(string_iconType), "%s%d, ", string_iconType, iconType_Door[(1*j) + dem + i - 1]);
            }
            else format(string_iconType, sizeof(string_iconType), "%s%d", string_iconType, iconType_Door[(1*j) + dem + i - 1]);
        }

        format(string_iconType, sizeof(string_iconType), "%s]", string_iconType);
        dem += 11;
    }
    
    entrances_list = list_new();
    checkpointMap_Door = map_new();
    m_doorHouseID = map_new();
}

hook OnPlayerDisconnect(playerid, reason)
{
    if(PlayerIsConnected(playerid))
    {
        new door[E_DOORS_MEMORY];
        if(doorID_pEdit[playerid] != -1)
        {
            if(list_get_arr_safe(entrances_list, doorID_pEdit[playerid], door))
            {
                door[playerEditDoorID] = INVALID_PLAYER_ID;

                list_set_arr(entrances_list, doorID_pEdit[playerid], door);
                doorID_pEdit[playerid] = -1;
            }
        }
    }
    return 1;
}

hook OnPlayerEnterDynamicCP(playerid, checkpointid)
{
    if(Streamer_GetIntData(STREAMER_TYPE_CP, checkpointid, E_STREAMER_EXTRA_ID) == E_EXTRA_ID_DOOR)
    {
        for(new Iter:index = map_iter(checkpointMap_Door); iter_inside(index); iter_move_next(index))
        {
            new key;
            if(iter_get_key_safe(index, key))
            {   
                if(key == checkpointid)
                {
                    doorID_playerNear[playerid] = iter_get_value(index);

                    break;
                }
            }
        }   
    }

    return 1;
}

hook OnPlayerLeaveDynamicCP(playerid, checkpointid)
{
    if(Streamer_GetIntData(STREAMER_TYPE_CP, checkpointid, E_STREAMER_EXTRA_ID) == E_EXTRA_ID_DOOR)
    {
        if(doorID_playerNear[playerid] != -1)
        {
            doorID_playerNear[playerid] = -1;
        }
    }

    return 1;
}
