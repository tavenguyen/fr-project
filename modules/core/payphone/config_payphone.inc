#define                 MAX_PAYPHONE                    10

static enum E_PAYPHONE_MEMORY
{   
    pP_Index,
    pP_objID,
    pP_pIDEdit,
    pP_numberPhone,
    Text3D:pP_TextID,
    Float:pP_posX,
    Float:pP_posY,
    Float:pP_posZ,
    Float:pP_posRX,
    Float:pP_posRY,
    Float:pP_posRZ,
    bool:is_pP_valid,
    pP_interiorID,
    pP_worldid
}

new payPhoneAmount = 0;

static
    PayPhone[MAX_PAYPHONE][E_PAYPHONE_MEMORY];

ResetPayPhone(index, bool:condition = false)
{
    PayPhone[index][pP_Index] = -1;
    PayPhone[index][pP_objID] = INVALID_OBJECT_ID;
    PayPhone[index][pP_TextID] = Text3D:INVALID_3DTEXT_ID;
    PayPhone[index][pP_pIDEdit] = INVALID_PLAYER_ID;
    PayPhone[index][pP_posX] = 0.0;
    PayPhone[index][pP_posY] = 0.0;
    PayPhone[index][pP_posZ] = 0.0;
    PayPhone[index][pP_posRX] = 0.0;
    PayPhone[index][pP_posRY] = 0.0;
    PayPhone[index][pP_posRZ] = 0.0;
    PayPhone[index][is_pP_valid] = false;
    PayPhone[index][pP_interiorID] = 0;
    PayPhone[index][pP_worldid] = 0;

    if(condition == true)
    {
        new query[500];
        mysql_format(MySQL_GetHandle(), query, sizeof(query), "DELETE FROM `payphone` WHERE `pP_index` = %d", index);
        mysql_tquery(MySQL_GetHandle(), query);
    }
    
    payPhoneAmount--;
    return 1;
}

SavePayPhone(index, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz, interiorid, worldid)
{
    PayPhone[index][pP_posX] = x;
    PayPhone[index][pP_posY] = y;
    PayPhone[index][pP_posZ] = z;
    PayPhone[index][pP_posRX] = rx;
    PayPhone[index][pP_posRY] = ry;
    PayPhone[index][pP_posRZ] = rz;
    PayPhone[index][pP_interiorID] = interiorid;
    PayPhone[index][pP_worldid] = worldid;
    PayPhone[index][is_pP_valid] = true;

    DestroyDynamic3DTextLabel(PayPhone[index][pP_TextID]);

    new string[100];
    format(string, sizeof(string), "Payphone %d\nSu dung /payphonecall de goi cho mot so dien thoai.", index);
    PayPhone[index][pP_TextID] = CreateDynamic3DTextLabel(string, -1, x, y - 0.5, z + 0.5, 5.0, _, _, _, worldid, interiorid);

    new query[500];
    mysql_format(MySQL_GetHandle(), query, sizeof(query), "UPDATE `payphone` SET `pP_posX` = %.4f, `pP_posY` = %.4f, `pP_posZ` = %.4f, `pP_posRX` = %.4f, `pP_posRY` = %.4f, `pP_posRZ` = %.4f, `pP_interiorid` = %d, `pP_worldid` = %d WHERE `pP_Index` = %d", x, y, z, rx, ry, rz, interiorid, worldid, PayPhone[index][pP_Index]);
    mysql_tquery(MySQL_GetHandle(), query);
    printf("Save payphone %d index", index);

    return 1;
}

stock PayPhone_Create(playerid, Float:x, Float:y, Float:z, Float:rx = 0.0, Float:ry = 0.0, Float:rz = 0.0, interiorid, worldid)
{   
    for(new index = 0; index < MAX_PAYPHONE; index++)
    {
        if(PayPhone[index][is_pP_valid] == false)
        {
            PayPhone[index][pP_Index] = index;
            PayPhone[index][pP_objID] = CreateDynamicObject(1216, x + 1.0, y + 1.0, z, rx, ry, rz, worldid, interiorid);
            GetDynamicObjectPos(PayPhone[index][pP_objID], PayPhone[index][pP_posX], PayPhone[index][pP_posY], PayPhone[index][pP_posZ]);
            EditDynamicObject(playerid, PayPhone[index][pP_objID]);
            PayPhone[index][pP_pIDEdit] = playerid; 
            PayPhone[index][pP_interiorID] = interiorid;
            PayPhone[index][pP_worldid] = worldid;

            new query[500];
            mysql_format(MySQL_GetHandle(), query, sizeof(query), "INSERT INTO `payphone` VALUES (%d, %.4f, %.4f, %.4f, %.4f, %.4f, %.4f, %d, %d)", index, x, y, z, rx, ry, rz, interiorid, worldid);
            mysql_tquery(MySQL_GetHandle(), query);
            
            payPhoneAmount++;
            return 1;
        }
    }

    return 0;
}

stock PayPhone_Destroy(objectid)
{
    for(new i = 0; i < MAX_PAYPHONE; i++)
    {
        if(PayPhone[i][pP_objID] == objectid)
        {
            DestroyDynamic3DTextLabel(PayPhone[i][pP_TextID]);
            DestroyDynamicObject(objectid); 
            ResetPayPhone(i, true);
            return 1;
        }
    }

    return 0;
}

stock bool:PayPhone_DestroyByIndex(index)
{
    if(PayPhone[index][is_pP_valid] == true)
    {
        DestroyDynamic3DTextLabel(PayPhone[index][pP_TextID]);
        DestroyDynamicObject(PayPhone[index][pP_objID]);
        ResetPayPhone(index, true);
        return true;
    }
    
    return false;
}

stock PayPhone_GetObjectIDByPlayer(playerid)
{
    for(new i = 0; i < MAX_PAYPHONE; i++)
    {
        if(PayPhone[i][pP_pIDEdit] == playerid)
        {
            return PayPhone[i][pP_objID];
        }
    }

    return INVALID_OBJECT_ID;
}

stock GetPayPhoneIndexByObject(objectid)
{
    for(new i = 0; i < MAX_PAYPHONE; i++)
    {
        if(PayPhone[i][pP_objID] == objectid)
        {
            return i;
        }
    }

    return (-1); 
}

#include <YSI_Coding\y_hooks>
hook OnPlayerEditDynObject(playerid, objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{
    new pObjectID = PayPhone_GetObjectIDByPlayer(playerid);
    printf("objectid %d", pObjectID);

    if(pObjectID == objectid)
    {
        if(response == EDIT_RESPONSE_CANCEL)
        {
            PayPhone_Destroy(objectid);
            SendClientMessage(playerid, -1, "Ban da huy bo qua trinh tao Payphone.");
            return 1;
        }

        if(response == EDIT_RESPONSE_FINAL)
        {
            new index = GetPayPhoneIndexByObject(objectid);

            SavePayPhone(index, x, y, z, rx, ry, rz, GetPlayerInterior(playerid), GetPlayerVirtualWorld(playerid));
            SendClientMessage(playerid, -1, "Ban da dieu chinh thanh cong vi tri cua Payphone.");
            
            PayPhone[index][pP_pIDEdit] = -1;
            return 1;
        }
    }

    return 0;
}

hook OnGameModeInit()
{
    for(new i = 0; i < MAX_PAYPHONE; i++)
    {
        ResetPayPhone(i);
    }

    mysql_tquery(MySQL_GetHandle(), "SELECT * FROM `payphone`", "OnPayPhoneLoad");
    return 1;
}

forward OnPayPhoneLoad();
public OnPayPhoneLoad()
{
    new rows = cache_num_rows();
    for(new index = 0; index < rows; index++)
    {
        new string[80];

        PayPhone[index][is_pP_valid] = true;
        cache_get_value_int(index, "pP_Index", PayPhone[index][pP_Index]);
        cache_get_value_float(index, "pP_posX", PayPhone[index][pP_posX]);
        cache_get_value_float(index, "pP_posY", PayPhone[index][pP_posY]);
        cache_get_value_float(index, "pP_posZ", PayPhone[index][pP_posZ]);
        cache_get_value_float(index, "pP_posRX", PayPhone[index][pP_posRX]);
        cache_get_value_float(index, "pP_posRY", PayPhone[index][pP_posRY]);
        cache_get_value_float(index, "pP_posRZ", PayPhone[index][pP_posRZ]);
        cache_get_value_int(index, "pP_interiorid", PayPhone[index][pP_interiorID]);
        cache_get_value_int(index, "pP_worldid", PayPhone[index][pP_worldid]);

        format(string, sizeof(string), "Payphone %d\nSu dung /payphonecall de goi cho mot so dien thoai.", index);
        PayPhone[index][pP_TextID] = CreateDynamic3DTextLabel(string, -1, PayPhone[index][pP_posX], PayPhone[index][pP_posY] - 0.5, PayPhone[index][pP_posZ] + 0.5, 5.0, _, _, _, PayPhone[index][pP_worldid], PayPhone[index][pP_interiorID]);
        PayPhone[index][pP_objID] = CreateDynamicObject(1216, PayPhone[index][pP_posX], PayPhone[index][pP_posY], PayPhone[index][pP_posZ], PayPhone[index][pP_posRX], PayPhone[index][pP_posRY], PayPhone[index][pP_posRZ], PayPhone[index][pP_worldid], PayPhone[index][pP_interiorID]);
    }

    if(rows != 0)
    {
        payPhoneAmount = rows;
    }
    else payPhoneAmount = 0;
    
    printf("Loaded %d payphone from database", rows);
    return 1;
}


