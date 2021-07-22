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

static const DOOR_EXTERIOR_ICON_TYPE = 19197;

enum
{
    doorType_Small,
    doorType_Medium,
    doorType_Large
}

enum _:E_DOORS_MEMORY
{
    doorUUID[UUID_LEN],
    doorName[MAX_DOOR_NAME],
    doorOwnedName[MAX_PLAYER_NAME + 1],
    doorType,
    doorID_Pickup,
    is_Door_sell,
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

new List:entrances_list;

stock Door_Create(Float:x, Float:y, Float:z, interiorid, worldid)
{
    new door[E_DOORS_MEMORY];
    UUID(door[doorUUID], UUID_LEN);
    format(door[doorName], sizeof(door[doorName]), "Khong co ten.");
    format(door[doorOwnedName], sizeof(door[doorOwnedName]), "Khong co chu so huu.");
    door[is_Door_sell] = 1;
    door[doorPrice] = MAX_DOOR_PRICE;
    door[is_Door_locked] = 1;
    door[doorExt_IconType] = DOOR_EXTERIOR_ICON_TYPE;
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
    door[doorType] = doorType_Small;
    door[playerEditDoorID] = INVALID_PLAYER_ID;

    new query[113 + UUID_LEN + 400];
    mysql_format(MySQL_GetHandle(), query, sizeof(query), 
        "INSERT INTO `doors` VALUES ('%e', '%e', '%e', %d, %d, %d, %d, %.4f, %.4f, %.4f, %d, %d, %.4f, %.4f, %.4f, %d, %d, %d)", 
    door[doorUUID], door[doorName], door[doorOwnedName], door[is_Door_sell], door[doorPrice], door[is_Door_locked], door[doorExt_IconType],
    door[doorExt_posX], door[doorExt_posY], door[doorExt_posZ], door[doorExt_Int], door[doorExt_VW],
    door[doorInt_posX], door[doorInt_posY], door[doorInt_posZ], door[doorInt_Int], door[doorInt_VW],
    door[doorType]);
    mysql_tquery(MySQL_GetHandle(), query);

    door[doorID_Pickup] = CreateDynamicPickup(door[doorExt_IconType], 1, x, y, z, worldid, interiorid, _);
    printf("%d", door[doorID_Pickup]);
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
        if(door[is_Door_sell] == 1)
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
        if(IsValidDynamicPickup(door[doorID_Pickup]))
        {
            DestroyDynamicPickup(door[doorID_Pickup]);
        }

        if(IsValidDynamic3DTextLabel(door[doorExt_Text3D]))
        {
            DestroyDynamic3DTextLabel(door[doorExt_Text3D]);
        }
        
        new text[128];
        if(door[is_Door_sell] == 1)
        {
            format(text, sizeof(text), "%s\nChu cua Door: %s\nTinh trang: %s - Gia thanh ban: %s$\nTinh trang cua: %s", door[doorName], door[doorOwnedName], Door_GetSold(index), Door_GetPrice(index), Door_GetLocked(index));
        }
        else
        {
            format(text, sizeof(text), "%s\nChu cua Door: %s\nTinh trang cua: %s", door[doorName], door[doorOwnedName], Door_GetLocked(index));
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

stock Door_GetType(doorid)
{
    new string[] = "Khong tim thay Door";
    if(doorid < 0 || doorid >= list_size(entrances_list))
    {
        return string;
    }

    new door_inside[E_DOORS_MEMORY];
    if(list_get_arr_safe(entrances_list, doorid, door_inside))
    {
        switch(door_inside[doorType])
        {
            case doorType_Small: format(string, sizeof(string), "Small Door");
            case doorType_Medium: format(string, sizeof(string), "Medium Door");
            case doorType_Large: format(string, sizeof(string), "Large Door");
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
            Door Owned Name:\t%s\n\
            Door Name:\t%s\n\
            Sold:\t%s\n\
            Price:\t%s$\n\
            Lock:\t%s\n\
            Exterior Icon Type:\t%d\n\
            Exterior Edit Position\t%s\n\
            Interior Edit Position\t%s\n\
            Door Type\t%s",
        doorid, Account_ReturnName(door[playerEditDoorID], 0), door[doorOwnedName], door[doorName], Door_GetSold(doorid), Door_GetPrice(doorid),
        Door_GetLocked(doorid), door[doorExt_IconType], "Hay nhan vao day de lay dia diem Exterior", "Hay nhan vao day de lay dia diem Interior",
        Door_GetType(doorid));
        
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
                case 4: goto doorSold_edit;
                case 5: goto doorPrice_edit;
                case 6: goto doorLock_edit;
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

            goto doormaindialog;
        }
        else goto doormaindialog;

        doorSold_edit:
        door[is_Door_sell] = !door[is_Door_sell];
        list_set_arr(entrances_list, doorid, door);

        Door_FormatInformation(doorid);

        new query_sold[62 + UUID_LEN + 1];
        mysql_format(MySQL_GetHandle(), query_sold, sizeof(query_sold), "UPDATE `doors` SET `doorIsSold` = %d WHERE `doorUUID` = '%e'", door[is_Door_sell], door[doorUUID]);
        mysql_tquery(MySQL_GetHandle(), query_sold);

        Msg(playerid, MSG_PREFIX_SUCCESS, "Ban da chuyen doi thanh cong trang thai mua/ban cua Door.");
        
        goto doormaindialog;

        doorPrice_edit:
        if(door[is_Door_sell] == 0)
        {
            Msg(playerid, MSG_PREFIX_ERROR, "Door nay khong duoc ban, ban khong the dieu chinh gia ban cua Door.");
            goto doormaindialog;
        }

        new response_edit_pricedoor[e_DIALOG_RESPONSE_INFO];
        await_arr(response_edit_pricedoor) ShowPlayerAsyncDialog(playerid, DIALOG_STYLE_INPUT, "Edit Door Price", "Ban hay nhap vao day so tien ma ban muon ban Door.", "Accept", "Cancel");
        if(response_edit_pricedoor[E_DIALOG_RESPONSE_Response])
        {
            new value = strval(response_edit_pricedoor[E_DIALOG_RESPONSE_InputText]);
            if(value > MAX_DOOR_PRICE)
            {
                Msg(playerid, MSG_PREFIX_ERROR, "Ban khong the nhap so tien lon hon muc quy dinh.");
                goto doormaindialog;
            }

            door[doorPrice] = value;
            list_set_arr(entrances_list, doorid, door);

            Door_FormatInformation(doorid);

            new query[70 + 9 + UUID_LEN];
            mysql_format(MySQL_GetHandle(), query, sizeof(query), "UPDATE `doors` SET `doorPrice` = %d WHERE `doorUUID` = '%e'", door[doorPrice], door[doorUUID]);
            mysql_tquery(MySQL_GetHandle(), query);

            goto doormaindialog;
        }
        else goto doormaindialog;

        doorLock_edit:
        door[is_Door_locked] = !door[is_Door_locked];
        list_set_arr(entrances_list, doorid, door);

        Door_FormatInformation(doorid);

        new query_lock[60 + UUID_LEN + 1];
        mysql_format(MySQL_GetHandle(), query_lock, sizeof(query_lock), "UPDATE `doors` SET `doorLocked` = %d WHERE `doorUUID` = '%e'", door[is_Door_sell], door[doorUUID]);
        mysql_tquery(MySQL_GetHandle(), query_lock);

        Msg(playerid, MSG_PREFIX_SUCCESS, "Ban da chuyen doi thanh cong trang thai khoa/mo khoa cua Door.");
        goto doormaindialog;

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

            new query[65 + 10 + UUID_LEN];
            mysql_format(MySQL_GetHandle(), query, sizeof(query), "UPDATE `doors` SET `doorExtIconType` = %d WHERE `doorUUID` = '%e'", value, door[doorUUID]);
            mysql_tquery(MySQL_GetHandle(), query);

            Msg(playerid, MSG_PREFIX_SUCCESS, "Ban da dieu chinh thanh cong ID Icon Type cua Door.");
            goto doormaindialog;
        }
        else goto doormaindialog;

        doorEdit_ExteriorPos:
        GetPlayerPos(playerid, door[doorExt_posX], door[doorExt_posY], door[doorExt_posZ]);
        door[doorExt_Int] =  GetPlayerInterior(playerid);
        door[doorExt_VW] = GetPlayerVirtualWorld(playerid);
        list_set_arr(entrances_list, doorid, door);

        Door_FormatInformation(doorid);

        new query_Ext[500];
        mysql_format(MySQL_GetHandle(), query_Ext, sizeof(query_Ext), "UPDATE `doors` SET `doorExt_posX` = %.4f, `doorExt_posY` = %.4f, `doorExt_posZ` = %.4f, `doorExt_Int` = %d, `doorExt_VW` = %d WHERE `doorUUID` = '%e'",door[doorExt_posX], door[doorExt_posY], door[doorExt_posZ], door[doorExt_Int], door[doorExt_VW], door[doorUUID]);
        mysql_tquery(MySQL_GetHandle(), query_Ext);

        Msg(playerid, MSG_PREFIX_SUCCESS, "Ban da dieu chinh thanh cong vi tri cua Exterior.");
        goto doormaindialog;

        doorEdit_InteriorPos:
        GetPlayerPos(playerid, door[doorInt_posX], door[doorInt_posY], door[doorInt_posZ]);
        door[doorInt_Int] = GetPlayerInterior(playerid);
        door[doorInt_VW] = GetPlayerVirtualWorld(playerid);
        list_set_arr(entrances_list, doorid, door);

        Door_FormatInformation(doorid);

        new query_Int[500];
        mysql_format(MySQL_GetHandle(), query_Int, sizeof(query_Int), "UPDATE `doors` SET `doorInt_posX` = %.4f, `doorInt_posY` = %.4f, `doorInt_posZ` = %.4f, `doorInt_Int` = %d, `doorInt_VW` = %d WHERE `doorUUID` = '%e'", door[doorInt_posX], door[doorInt_posY], door[doorInt_posZ], door[doorInt_Int], door[doorInt_VW], door[doorUUID]);
        mysql_tquery(MySQL_GetHandle(), query_Int);

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
                    if(door[doorType] == doorType_Small)
                    {
                        Msg(playerid, MSG_PREFIX_ERROR, "Ban khong the chon loai Door nay nua.");
                        goto doorEdit_Type;
                    }

                    door[doorType] = doorType_Small;
                    list_set_arr(entrances_list, doorid, door);
                }
                case 1:
                {
                    if(door[doorType] == doorType_Medium)
                    {
                        Msg(playerid, MSG_PREFIX_ERROR, "Ban khong the chon loai Door nay nua.");
                        goto doorEdit_Type;
                    }

                    door[doorType] = doorType_Medium;
                    list_set_arr(entrances_list, doorid, door);
                }
                case 2:
                {
                    if(door[doorType] == doorType_Large)
                    {
                        Msg(playerid, MSG_PREFIX_ERROR, "Ban khong the chon loai Door nay nua.");
                        goto doorEdit_Type;
                    }

                    door[doorType] = doorType_Large;
                    list_set_arr(entrances_list, doorid, door);
                }
            }

            new query[58 + 2 + UUID_LEN];
            mysql_format(MySQL_GetHandle(), query, sizeof(query), "UPDATE `doors` SET `doorType` = %d WHERE `doorUUID` = '%e'", door[doorType], door[doorUUID]);
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

#include <YSI_Coding\y_hooks>
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