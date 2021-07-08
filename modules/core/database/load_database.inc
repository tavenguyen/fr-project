#include <account>

#include <YSI_Coding\y_hooks>
hook OnGameModeInit()
{
    mysql_tquery(MySQL_GetHandle(), "SELECT * FROM `accounts`", "OnAccountLoad");
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

        list_add_arr(accountJoined, account);
    }

    printf("Loaded %d accounts from database.", rows);
    return 1;
}