/*--- Project was created on 12:54 - 7/7/2021---*/
//    Founder: Halosetoe                       //
//    Leader Scripter: Halosetoe              //
//    Scripter: Halosetoe                    //
//    Game Content: Halosetoe               //
/*--------- Freedom Roleplay v0.1 ---------*/

#define         ACCOUNT_VERSION         "v0.1"

static const ACCOUNT_REGISTER = 0;
static const ACCOUNT_LOGIN = 1;

static account_index[MAX_PLAYERS];

enum 
{
    DIALOG_REGISTER_ACCOUNT,
    DIALOG_REG_EMAIL_ACCOUNT, 
    DIALOG_LOGIN_ACCOUNT
}

enum _:E_PLAYER_ACCOUNT_MEMORY
{
    accountID,
    accountUUID[UUID_LEN],
    accountName[MAX_PLAYER_NAME + 1],
    accountEmail[MAX_EMAIL_LENGTH],
    accountPassword[MAX_ACCOUNT_PASSWORD + 1]
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

stock bool:Account_Destroy(const name[])
{
    new account[E_PLAYER_ACCOUNT_MEMORY];
    for(new Iter:iter_account_index = list_iter(accountJoined); iter_inside(iter_account_index); iter_move_next(iter_account_index))
    {
        if(!strcmp(account[accountName], name))
        {
            iter_erase_deep(iter_account_index);
            return true;
        }
    }

    return false;
}


static const ACCOUNT_GMAIL_VALID[] = {'g', 'm', 'a', 'i', 'l', '.', 'c', 'o', 'm'};
stock bool:Account_IsEmailValid(const email[])
{
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
                        return false;
                    }
                }
                
                return true;
            }
        }
    }

    return false;
}


#include <YSI_Coding\y_hooks>
hook OnGameModeInit()
{   
    accountJoined = list_new();    
    return 1;
}

hook OnPlayerConnect(playerid)
{
    TogglePlayerSpectating(playerid, true);

    new auth = IsAccountRegistered(playerid);
    MessageTDLine_ShowForPlayer(playerid, "Tim kiem thanh cong, he thong dang xac dinh lai ket qua.", 2500);
    wait_ms(2600);
    if(auth == ACCOUNT_REGISTER)
    {
        MessageTDLine_ShowForPlayer(playerid, "Tai khoan cua ban chua dang ky, hay thuc hien cac thao tac de co mot Account.", 2000);
        Dialog_Show(playerid, DIALOG_REGISTER_ACCOUNT, DIALOG_STYLE_PASSWORD, "Register Account "ACCOUNT_VERSION"", "Ban hay nhap mat khau tai day...", "Next", "Close");
        
        return 1;
    }
    
    if(auth == ACCOUNT_LOGIN)
    {
        printf("Login");
    }

    return 1;
}

Dialog:DIALOG_REGISTER_ACCOUNT(playerid, response, listitem, const inputtext[])
{
    if(response)
    {
        if(strlen(inputtext) < 6)
        {
            return Msg(playerid, MSG_PREFIX_ERROR, "Do dai mat khau khong nho hon 6.");
        }

        new account[E_PLAYER_ACCOUNT_MEMORY];

        UUID(account[accountUUID], UUID_LEN);
        strcat(account[accountName], Account_ReturnName(playerid, 1));
        strcat(account[accountPassword], inputtext); 
        account_index[playerid] = list_add_arr(accountJoined, account);

        Dialog_Show(playerid, DIALOG_REG_EMAIL_ACCOUNT, DIALOG_STYLE_INPUT, "Register Account "ACCOUNT_VERSION"", "Ban hay nhap dia chi Email tai day...", "Next", "Close");
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
                list_set_arr(accountJoined, account_index[playerid], account);

                new query[500];
                mysql_format(MySQL_GetHandle(), query, sizeof(query), "INSERT INTO `accounts` VALUES ('%e', '%e', '%e', '%e')", account[accountName], account[accountUUID], account[accountPassword], inputtext);
                mysql_tquery(MySQL_GetHandle(), query);

                list_remove_deep(accountJoined, account_index[playerid]);

                Msg(playerid, MSG_PREFIX_SUCCESS, "Ban da hoan tat dang ky, hay doi Admin gui Email den cho ban.");
                Kick(playerid);
                return 1;
            }
        }
        else
        {
            Msg(playerid, MSG_PREFIX_ERROR, "Email cua ban khong hop le hoac da co ton tai trong may chu.");
            Dialog_Show(playerid, DIALOG_REG_EMAIL_ACCOUNT, DIALOG_STYLE_INPUT, "Register Account "ACCOUNT_VERSION"", "Ban hay nhap dia chi Email tai day...", "Next", "Close");
            return 1;
        }
    }

    Account_Destroy(Account_ReturnName(playerid, 1));
    Msg(playerid, MSG_PREFIX_ERROR, "Ban da huy bo qua trinh dang ky tai khoan.");
    Kick(playerid);
    return 0;
}