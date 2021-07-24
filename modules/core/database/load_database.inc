#include <account>
#include <config_door>

#include <YSI_Coding\y_hooks>
hook OnGameModeInit()
{
    mysql_tquery(MySQL_GetHandle(), "SELECT * FROM `accounts`", "OnAccountLoad");
    mysql_tquery(MySQL_GetHandle(), "SELECT * FROM `characters`", "OnCharacterLoad");
    mysql_tquery(MySQL_GetHandle(), "SELECT * FROM `doors`", "OnDoorLoad");
    return 1;
}

forward OnAccountLoad();
public OnAccountLoad()
{
    new account[E_PLAYER_ACCOUNT_MEMORY];
    new rows = cache_num_rows();

    for(new index = 0; index < rows; index++)
    {
        cache_get_value_name(index, "account_Name", account[accountName], MAX_PLAYER_NAME + 1);
        cache_get_value_name(index, "account_UUID", account[accountUUID], UUID_LEN);
        cache_get_value_name(index, "account_Password", account[accountPassword], MAX_ACCOUNT_PASSWORD + 1);
        cache_get_value_name(index, "account_Email", account[accountEmail], MAX_EMAIL_LENGTH);

        cache_get_value_name(index, "accountCharacterName1", account[accountCharacterName1], MAX_PLAYER_NAME + 7);
        cache_get_value_name(index, "accountCharacterName2", account[accountCharacterName2], MAX_PLAYER_NAME + 7);
        cache_get_value_name(index, "accountCharacterName3", account[accountCharacterName3], MAX_PLAYER_NAME + 7);

        if(!strcmp(account[accountCharacterName1], ""))
        {
            format(account[accountCharacterName1], sizeof(account[accountCharacterName1]), "Nhan vat chua duoc khoi tao...");
        }

        if(!strcmp(account[accountCharacterName2], ""))
        {
            format(account[accountCharacterName2], sizeof(account[accountCharacterName2]), "Nhan vat chua duoc khoi tao...");
        }

        if(!strcmp(account[accountCharacterName3], ""))
        {
            format(account[accountCharacterName3], sizeof(account[accountCharacterName3]), "Nhan vat chua duoc khoi tao...");
        }

        list_add_arr(accountJoined, account);
    }

    printf("Loaded %d accounts from database.", rows);
    return 1;
}

forward OnCharacterLoad();
public OnCharacterLoad()
{
    new rows = cache_num_rows();
    for(new index = 0; index < rows; index++)
    {
        new character[E_CHARACTER_MEMORY];
        cache_get_value_name(index, "charAccount", character[characterAccount], MAX_PLAYER_NAME + 1);
        cache_get_value_name(index, "charName", character[characterName], MAX_PLAYER_NAME + 1);
        cache_get_value_name(index, "charUUID", character[characterUUID], UUID_LEN);
        cache_get_value_int(index, "charAge", character[characterAge]);
        cache_get_value_int(index, "charBirthdayDay", character[characterBirthday_Day]);
        cache_get_value_int(index, "charBirthdayMonth", character[characterBirthday_Month]);
        cache_get_value_int(index, "charBirthdayYear", character[characterBirthday_Year]);
        cache_get_value_int(index, "charGender", character[characterGender]);
        cache_get_value_int(index, "charSkinColor", character[characterSkinColor]);
        cache_get_value_int(index, "charSkin", character[characterSkinID]);
        cache_get_value_float(index, "charPosX", character[characterPosX]);
        cache_get_value_float(index, "charPosY", character[characterPosY]);
        cache_get_value_float(index, "charPosZ", character[characterPosZ]);
        cache_get_value_float(index, "charAngle", character[characterFacingAngle]);
        cache_get_value_int(index, "charInteriorID", character[characterInt]);
        cache_get_value_int(index, "charWorldID", character[characterVW]);
        cache_get_value_float(index, "charHealth", character[characterHealth]);
        cache_get_value_float(index, "charArmour", character[characterArmour]);
        cache_get_value_name(index, "charAccent", character[characterAccent], MAX_CHARACTER_ACCENT);
        cache_get_value_name(index, "charDescribe", character[characterDescribe], MAX_CHARACTER_DESCRIBE);
        cache_get_value_int(index, "charAdmin", character[characterAdminLevel]);
        cache_get_value_int(index, "charInDoor", character[characterInDoor]);

        list_add_arr(characters, character);
    }
    
    printf("Loaded %d characters from database.", rows);
    return 1;
}

forward OnDoorLoad();
public OnDoorLoad()
{
    new rows = cache_num_rows();
    new door[E_DOORS_MEMORY];

    for(new index = 0; index < rows; index++)
    {
        cache_get_value_name(index, "doorUUID", door[doorUUID], UUID_LEN);
        cache_get_value_name(index, "doorName", door[doorName], MAX_DOOR_NAME);
        cache_get_value_name(index, "doorOwnedName", door[doorOwnedName], MAX_PLAYER_NAME + 1);
        cache_get_value_int(index, "doorIsSold", door[is_Door_sell]);
        cache_get_value_int(index, "doorPrice", door[doorPrice]);
        cache_get_value_int(index, "doorLocked", door[is_Door_locked]);
        cache_get_value_int(index, "doorExtIconType", door[doorExt_IconType]);
        cache_get_value_float(index, "doorExt_posX", door[doorExt_posX]);
        cache_get_value_float(index, "doorExt_posY", door[doorExt_posY]);
        cache_get_value_float(index, "doorExt_posZ", door[doorExt_posZ]);
        cache_get_value_int(index, "doorExt_Int", door[doorExt_Int]);
        cache_get_value_int(index, "doorExt_VW", door[doorExt_VW]);
        cache_get_value_float(index, "doorInt_posX", door[doorInt_posX]);
        cache_get_value_float(index, "doorInt_posY", door[doorInt_posY]);
        cache_get_value_float(index, "doorInt_posZ", door[doorInt_posZ]);
        cache_get_value_int(index, "doorInt_Int", door[doorInt_Int]);
        cache_get_value_int(index, "doorInt_VW", door[doorInt_VW]);
        cache_get_value_int(index, "doorTypeRoom", door[doorTypeRoom]);
        
        door[playerEditDoorID] = INVALID_PLAYER_ID;
        
        new doorid = list_add_arr(entrances_list, door);

        new cp_Index = CreateDynamicCP(door[doorInt_posX], door[doorInt_posY], door[doorInt_posZ], 1.0, door[doorInt_VW], door[doorInt_Int], _, 2.0);
        Streamer_SetIntData(STREAMER_TYPE_CP, cp_Index, E_STREAMER_EXTRA_ID, E_EXTRA_ID_DOOR);

        Door_FormatInformation(doorid);
        map_add(checkpointMap_Door, cp_Index, doorid);
    }

    printf("Loaded %d doors from database.", rows);
    return 1;
}