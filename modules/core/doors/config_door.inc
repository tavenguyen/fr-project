/*--- Project was created on 12:54 - 7/7/2021---*/
//    Founder: Halosetoe                       //
//    Leader Scripter: Halosetoe              //
//    Scripter: Halosetoe                    //
//    Game Content: Halosetoe               //
/*--------- Freedom Roleplay v0.1 ---------*/

static const DOOR_EXTERIOR_ICON_TYPE = 19197;

enum _:E_DOORS_MEMORY
{
    doorUUID[UUID_LEN],
    doorName[MAX_DOOR_NAME],
    doorOwnedName[MAX_PLAYER_NAME + 1],
    doorID_Pickup,
    is_Door_sold,
    is_Door_locked,
    doorPrice,
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
    doorInt_Int,
    doorInt_VW
}

static doorID_pEdit[MAX_PLAYERS] = -1;

new List:entrances_list;

stock Door_Create(Float:x, Float:y, Float:z, interiorid, worldid)
{
    new door[E_DOORS_MEMORY];
    UUID(door[doorUUID], UUID_LEN);
    format(door[doorName], sizeof(door[doorName]), "Khong co ten.");
    format(door[doorOwnedName], sizeof(door[doorOwnedName]), "Khong co chu so huu.");
    door[is_Door_sold] = 1;
    door[doorPrice] = MAX_DOOR_PRICE;
    door[is_Door_locked] = 1;
    door[doorExt_IconType] = DOOR_EXTERIOR_ICON_TYPE;
    door[doorExt_posX] = x;
    door[doorExt_posY] = y;
    door[doorExt_posZ] = z;
    door[doorExt_Int] = interiorid;
    door[doorExt_VW] = worldid;
    door[doorInt_posX] = x;
    door[doorInt_posY] = y;
    door[doorInt_posZ] = z;
    door[doorInt_Int] = interiorid;
    door[doorInt_VW] = worldid;
    door[playerEditDoorID] = INVALID_PLAYER_ID;

    new query[113 + UUID_LEN + 400];
    mysql_format(MySQL_GetHandle(), query, sizeof(query), "INSERT INTO `doors` VALUES ('%e', '%e', '%e', %d, %d, %d, %d, %.4f, %.4f, %.4f, %d, %d, %.4f, %.4f, %.4f, %d, %d)", 
        door[doorUUID], door[doorName], door[doorOwnedName], door[is_Door_sold], door[doorPrice], door[is_Door_locked], door[doorExt_IconType],
        door[doorExt_posX], door[doorExt_posY], door[doorExt_posZ], door[doorExt_Int], door[doorExt_VW],
        door[doorInt_posX], door[doorInt_posY], door[doorInt_posZ], door[doorInt_Int], door[doorInt_VW]);
    mysql_tquery(MySQL_GetHandle(), query);

    door[doorID_Pickup] = CreateDynamicPickup(door[doorExt_IconType], 0, x, y, z, worldid, interiorid);
    return list_add_arr(entrances_list, door);
}

stock Door_GetSold(index)
{
    new string[50];
    format(string, sizeof(string), "");

    if(index < 0 || index >= list_size(entrances_list))
    {
        return string;
    }

    new door[E_DOORS_MEMORY];
    if(list_get_arr_safe(entrances_list, index, door))
    {
        format(string, sizeof(string), "Khong ban");
        if(door[is_Door_sold] == 1)
        {
            format(string, sizeof(string), "Dang ban");
        }
    }

    return string;
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
        new value[10];
        valstr(value, door[doorPrice]);
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
                        if(i == 2)
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

stock Door_GetLocked(index)
{
    new string[50];
    format(string, sizeof(string), "");

    if(index < 0 || index >= list_size(entrances_list))
    {
        return string;
    }

    new door[E_DOORS_MEMORY];
    if(list_get_arr_safe(entrances_list, index, door))
    {
        format(string, sizeof(string), "Khong khoa");
        if(door[is_Door_locked] == 1)
        {
            format(string, sizeof(string), "Khoa");
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
        new text[128];
        if(door[is_Door_sold] == 1)
        {
            format(text, sizeof(text), "%s\nChu cua Door: %s\nTinh trang: %s - Gia thanh ban: %s$\nTinh trang cua: %s", door[doorName], door[doorOwnedName], Door_GetSold(index), Door_GetPrice(index), Door_GetLocked(index));
        }
        else
        {
            format(text, sizeof(text), "%s\nChu cua Door: %s\nTinh trang cua: %s", door[doorName], door[doorOwnedName], Door_GetLocked(index));
        }

        door[doorExt_Text3D] = CreateDynamic3DTextLabel(text, -1, door[doorExt_posX], door[doorExt_posY], door[doorExt_posZ] + 1.0, 5.0, _, _, _, door[doorExt_VW], door[doorExt_Int], _, 5.0);
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

stock Door_EditByPlayer(playerid, doorid)
{
    new door[E_DOORS_MEMORY];
    if(list_get_arr_safe(entrances_list, doorid, door))
    {
        door[playerEditDoorID] = playerid;
        list_set_arr(entrances_list, doorid, door);
        
        doorID_pEdit[playerid] = doorid;
    }

    return 1;
}

#include <YSI_Coding\y_hooks>
hook OnPlayerDisconnect(playerid, reason)
{
    if(PlayerIsConnected(playerid))
    {
        new door[E_DOORS_MEMORY];
        if(list_get_arr_safe(entrances_list, doorID_pEdit[playerid], door))
        {
            door[playerEditDoorID] = INVALID_PLAYER_ID;
            doorID_pEdit[playerid] = -1;
        }
    }

    return 1;
}