/*--- Project was created on 12:54 - 7/7/2021---*/
//    Founder: Halosetoe                       //
//    Leader Scripter: Halosetoe              //
//    Scripter: Halosetoe                    //
//    Game Content: Halosetoe               //
/*--------- Freedom Roleplay v0.1 ---------*/

#include <bcrypt>

#define         ACCOUNT_VERSION         "v0.1"

static const ACCOUNT_GMAIL_VALID[] = {'g', 'm', 'a', 'i', 'l', '.', 'c', 'o', 'm'};
static const BCRYPT_COST = 12;

const ACCOUNT_REGISTER = 0;
const ACCOUNT_LOGIN = 1;

new account_index[MAX_PLAYERS];

enum _:E_PLAYER_ACCOUNT_MEMORY
{
    accountID,
    accountUUID[UUID_LEN],
    accountName[MAX_PLAYER_NAME + 1],
    accountEmail[MAX_EMAIL_LENGTH],
    accountPassword[MAX_ACCOUNT_PASSWORD + 1],
    accountCharacterName1[MAX_PLAYER_NAME + 7],
    accountCharacterName2[MAX_PLAYER_NAME + 7],
    accountCharacterName3[MAX_PLAYER_NAME + 7]
}

new List:accountJoined;

stock IsAccountRegistered(playerid)
{
    new name[MAX_PLAYER_NAME + 1];
    new account[E_PLAYER_ACCOUNT_MEMORY];

    name = Account_ReturnName(playerid, 1);

    new auth = ACCOUNT_REGISTER;
    for(new Iter:iter_account_index = list_iter(accountJoined); iter_inside(iter_account_index); iter_move_next(iter_account_index))
    {
        if(iter_get_arr_safe(iter_account_index, account))
        {
            if(!strcmp(account[accountName], name, false))
            {
                auth = ACCOUNT_LOGIN;
            }
        }
    }

    return auth;
}

stock bool:Account_Destroy(playerid, const name[])
{
    new account[E_PLAYER_ACCOUNT_MEMORY];
    for(new Iter:iter_account_index = list_iter(accountJoined); iter_inside(iter_account_index); iter_move_next(iter_account_index))
    {
        if(!strcmp(account[accountName], name))
        {
            account_index[playerid] = -1;
            iter_erase_deep(iter_account_index);
            return true;
        }
    }

    return false;
}

stock bool:Account_IsEmailValid(const email[])
{
    new bool:check_valid = true;
    if(email[strlen(email) - 10] == '@')
    {
        if(!strcmp(email[strlen(email) - 9], ACCOUNT_GMAIL_VALID[0], false, 9))
        {
            new account[E_PLAYER_ACCOUNT_MEMORY];
            for(new Iter:account_index_iter = list_iter(accountJoined); iter_inside(account_index_iter); iter_move_next(account_index_iter))
            {
                if(iter_get_arr_safe(account_index_iter, account))
                {
                    if(!strcmp(account[accountEmail], email))
                    {
                        check_valid = false;
                    }
                }
            }
        }
        else check_valid = false;
    }
    else check_valid = false;
    return check_valid;
}

Dialog:DIALOG_LOGIN_ACCOUNT(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        if(isnull(inputtext) || strlen(inputtext) > MAX_ACCOUNT_PASSWORD)
        {
            Msg(playerid, MSG_PREFIX_ERROR, "Mat khau khong phu hop, vui long thu lai!");
            Dialog_Show(playerid, DIALOG_LOGIN_ACCOUNT, DIALOG_STYLE_PASSWORD, "Login Account "ACCOUNT_VERSION"", "Ban hay nhap mat khau de dang nhap tai khoan", "Next", "Close");
        }

        new account[E_PLAYER_ACCOUNT_MEMORY];
        for(new Iter:account_index_iter = list_iter(accountJoined); iter_inside(account_index_iter); iter_move_next(account_index_iter))
        {
            if(iter_get_arr_safe(account_index_iter, account))
            {
                if(!strcmp(account[accountName], Account_ReturnName(playerid, 1)))
                {
                    account_index[playerid] = iter_get_key(account_index_iter);
                    bcrypt_check(inputtext, account[accountPassword], "OnPasswordChecked", "d", playerid);
                    return 1;
                }   
            }
        }
    }

    printf("debug: %d", account_index[playerid]);
    KickEx(playerid, MSG_PREFIX_ERROR, "Ban da huy qua trinh dang nhap tai khoan.");
    return 1;
}

Dialog:DIALOG_REGISTER_ACCOUNT(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        if(strlen(inputtext) < 6)
        {
            return Msg(playerid, MSG_PREFIX_ERROR, "Do dai mat khau khong nho hon 6.");
        }

        bcrypt_hash(inputtext, BCRYPT_COST, "OnPasswordHashed", "i", playerid);
    }
    return 1;
}

Dialog:DIALOG_REG_EMAIL_ACCOUNT(playerid, response, listitem, const inputtext[])
{
    if(response)
    {
        if(Account_IsEmailValid(inputtext))
        {
            new account[E_PLAYER_ACCOUNT_MEMORY];
            if(list_get_arr_safe(accountJoined, account_index[playerid], account))
            {
                strcat(account[accountEmail], inputtext);

                format(account[accountCharacterName1], sizeof(account[accountCharacterName1]), "Nhan vat chua duoc khoi tao...");
                format(account[accountCharacterName2], sizeof(account[accountCharacterName2]), "Nhan vat chua duoc khoi tao...");
                format(account[accountCharacterName3], sizeof(account[accountCharacterName3]), "Nhan vat chua duoc khoi tao...");

                list_set_arr(accountJoined, account_index[playerid], account);

                new query[500];
                mysql_format(MySQL_GetHandle(), query, sizeof(query), "INSERT INTO `accounts` VALUES ('%e', '%e', '%e', '%e', '%e', '%e', '%e')", account[accountName], account[accountUUID], account[accountPassword], inputtext, account[accountCharacterName1], account[accountCharacterName2], account[accountCharacterName3]);
                mysql_tquery(MySQL_GetHandle(), query);

                mysql_format(MySQL_GetHandle(), query, sizeof(query), "SELECT * FROM `characters`", account[accountName]);
                mysql_tquery(MySQL_GetHandle(), query, "OnAccountShowList", "isf", playerid, account[accountName], true);
                return 1;
            }
        }

        Msg(playerid, MSG_PREFIX_ERROR, "Email cua ban khong hop le hoac da co ton tai trong may chu.");
        Dialog_Show(playerid, DIALOG_REG_EMAIL_ACCOUNT, DIALOG_STYLE_INPUT, "Register Account "ACCOUNT_VERSION"", "Ban hay nhap dia chi Email tai day...", "Next", "Close");
        return 1;
    }

    Account_Destroy(playerid, Account_ReturnName(playerid, 1));

    printf("debug: %d", account_index[playerid]);
    KickEx(playerid, MSG_PREFIX_ERROR, "Ban da huy bo qua trinh dang ky tai khoan.");
    return 0;
}

Dialog:DIALOG_CHARACTER_LIST(playerid, response, listitem, const inputtext[])
{
    if(response)
    {
        new account[E_PLAYER_ACCOUNT_MEMORY];
        list_get_arr_safe(accountJoined, account_index[playerid], account);

        switch(listitem)
        {
            case 0:
            {
                if(!strcmp(account[accountCharacterName1], "Nhan vat chua duoc khoi tao..."))
                {
                    Character_Create(playerid, listitem);
                    return 1;
                }
            }
            case 1:
            {
                if(!strcmp(account[accountCharacterName2], "Nhan vat chua duoc khoi tao..."))
                {
                    Character_Create(playerid, listitem);
                    return 1;
                }
            }
            case 2:
            {
                if(!strcmp(account[accountCharacterName3], "Nhan vat chua duoc khoi tao..."))
                {
                    Character_Create(playerid, listitem);
                    return 1;
                }
            }
        }
        return 1;
    }
    
    printf("debug: %d", account_index[playerid]);
    KickEx(playerid, MSG_PREFIX_ERROR, "Ban da huy qua trinh chon nhan vat/tao nhan vat.");
    return 1;
}

forward OnPasswordHashed(playerid);
public OnPasswordHashed(playerid)
{
    new hash[BCRYPT_HASH_LENGTH];
    bcrypt_get_hash(hash);

    new account[E_PLAYER_ACCOUNT_MEMORY];
    UUID(account[accountUUID], UUID_LEN);
    strcat(account[accountName], Account_ReturnName(playerid, 1));
    strcat(account[accountPassword], hash); 
    strcat(account[accountEmail], "Tai khoan nay chua co Email.");
    account_index[playerid] = list_add_arr(accountJoined, account);

    Dialog_Show(playerid, DIALOG_REG_EMAIL_ACCOUNT, DIALOG_STYLE_INPUT, "Register Account "ACCOUNT_VERSION"", "Ban hay nhap dia chi Email tai day...", "Next", "Close");
    return 1;
}

forward OnPasswordChecked(playerid);
public OnPasswordChecked(playerid)
{
    new bool:match = bcrypt_is_equal();
    MessageTDLine_ShowForPlayer(playerid, "Mat khau cang dai thi kiem tra cang lau, hay doi trong giay lat...", 2000);
    if(match == true)
    {
        MessageTDLine_ShowForPlayer(playerid, "Ban da dang nhap tai khoan thanh cong.", 2000);

        new account_inside[E_PLAYER_ACCOUNT_MEMORY];
        list_get_arr_safe(accountJoined, account_index[playerid], account_inside);

        new query[500];
        mysql_format(MySQL_GetHandle(), query, sizeof(query), "SELECT * FROM `characters`", account_inside[accountName]);
        mysql_tquery(MySQL_GetHandle(), query, "OnAccountShowList", "isb", playerid, account_inside[accountName], false);
    }
    else
    {
        Msg(playerid, MSG_PREFIX_ERROR, "Mat khau khong hop le, vui long thu lai!");
        Dialog_Show(playerid, DIALOG_LOGIN_ACCOUNT, DIALOG_STYLE_PASSWORD, "Login Account "ACCOUNT_VERSION"", "Ban hay nhap mat khau de dang nhap tai khoan", "Next", "Close");
    }

    return 1;
}

forward OnAccountShowList(playerid, const name[], bool:isPlayerRegistered);
public OnAccountShowList(playerid, const name[], bool:isPlayerRegistered)
{
    new name_db[MAX_PLAYER_NAME + 1];
    new count = 0;

    new account[E_PLAYER_ACCOUNT_MEMORY];
    list_get_arr_safe(accountJoined, account_index[playerid], account);

    if(isPlayerRegistered == true)
    {
        format(account[accountCharacterName1], sizeof(account[accountCharacterName1]), "Nhan vat chua duoc khoi tao...");
        format(account[accountCharacterName2], sizeof(account[accountCharacterName2]), "Nhan vat chua duoc khoi tao...");
        format(account[accountCharacterName3], sizeof(account[accountCharacterName3]), "Nhan vat chua duoc khoi tao...");
    
        new rows = cache_num_rows();
        for(new index = 0; index < rows; index++)
        {
            if(count == 3)
            {
                break;
            }

            cache_get_value_name(index, "charAccount", name_db, MAX_PLAYER_NAME + 1);
            if(!strcmp(name_db, name, false))
            {
                new nameChar[MAX_PLAYER_NAME + 1];
                cache_get_value_name(index, "charName", nameChar, MAX_PLAYER_NAME + 1);
                count++;

                switch(count)
                {
                    case 1: format(account[accountCharacterName1], sizeof(account[accountCharacterName1]), "%s", nameChar);
                    case 2: format(account[accountCharacterName2], sizeof(account[accountCharacterName2]), "%s", nameChar);
                    case 3: format(account[accountCharacterName3], sizeof(account[accountCharacterName3]), "%s", nameChar);
                }
            }
        }
        list_set_arr(accountJoined, account_index[playerid], account);

        new query[500];
        mysql_format(MySQL_GetHandle(), query, sizeof(query), "UPDATE `accounts` SET `accountCharacterName1` = '%e', `accountCharacterName2` = '%e', `accountCharacterName3` = '%e' WHERE `account_Name` = '%e'", account[accountCharacterName1], account[accountCharacterName2], account[accountCharacterName3], account[accountName]);
        mysql_tquery(MySQL_GetHandle(), query);
    }


    new string[128];
    format(string, sizeof(string), "%s\n%s\n%s", account[accountCharacterName1], account[accountCharacterName2], account[accountCharacterName3]);
    Dialog_Show(playerid, DIALOG_CHARACTER_LIST, DIALOG_STYLE_LIST, "Your account in database "ACCOUNT_VERSION"", string, "Select", "Cancel");
    return 1;
}
