#include <account>

#include <YSI_Coding\y_hooks>
hook OnGameModeInit()
{
    mysql_tquery(MySQL_GetHandle(), "SELECT * FROM `accounts`", "OnAccountLoad");
    mysql_tquery(MySQL_GetHandle(), "SELECT * FROM `characters`", "OnCharacterLoad");
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

        list_add_arr(characters, character);
    }
    
    printf("Loaded  %d characters from database.", rows);
    return 1;
}