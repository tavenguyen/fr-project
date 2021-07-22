/*--- Project was created on 12:54 - 7/7/2021---*/
//    Founder: Halosetoe                       //
//    Leader Scripter: Halosetoe              //
//    Scripter: Halosetoe                    //
//    Game Content: Halosetoe               //
/*--------- Freedom Roleplay v0.1 ---------*/

#include <Character/config_character>
#include <textdraw>
#include <Character/character_dialog>

#include <Character/character>

#include <Account/config_account>

#include <YSI_Coding\y_hooks>
hook OnGameModeInit()
{   
    accountJoined = list_new();  
    characters = list_new();
    
    F_GlobalTD_AccountLogin();
    GlobalTD_CharacterCreate();  
    GlobalTD_CharacterSelectSkin();
    return 1;
}

hook OnGameModeExit()
{
    for(new Iter:account_index_iter = list_iter(accountJoined); iter_inside(account_index_iter);)
    {
        iter_erase_deep(account_index_iter);
    }
    
    return 1;
}

hook OnPlayerConnect(playerid)
{
    isPlayerConnected[playerid] = false;
    is_pCheckPassword[playerid] = false;
    character_index[playerid] = -1;
    Inputtext_AccountLogin[playerid][0] = EOS;
    
    if(account_index[playerid] != -1)
    {
        account_index[playerid] = -1;
    }

    SetPlayerColor(playerid, -1);
    TogglePlayerSpectating(playerid, true);

    new auth = IsAccountRegistered(playerid);
    MessageTDLine_ShowForPlayer(playerid, "Tim kiem thanh cong, he thong dang xac dinh lai ket qua.", 2500);
    wait_ms(2600);

    if(auth == ACCOUNT_REGISTER)
    {
        Dialog_Show(playerid, DIALOG_REGISTER_ACCOUNT, DIALOG_STYLE_PASSWORD, "Register Account "ACCOUNT_VERSION"", "Ban hay nhap mat khau tai day de dang ky tai khoan:", "Next", "Close");

        MessageTDLine_ShowForPlayer(playerid, "Tai khoan cua ban chua dang ky, hay thuc hien cac thao tac de co mot Account.", 2000);   
        return 1;
    }
    
    if(auth == ACCOUNT_LOGIN)
    {
        ClearChat(playerid);
        F_GlobalTD_AccountLoginShow(playerid);
        F_PlayerTD_AccountLogin(playerid);
        SelectTextDraw(playerid, 0xFFFFF00FF);
    }

    return 1;
}

hook OnPlayerClickTextDraw(playerid, Text:clickedid)
{
    if(PlayerIsConnected(playerid) == false)
    {
        if(clickedid == GlobalTD_AccountLogin[2])
        {
            if(is_pCheckPassword[playerid] == false)
            {
                new account[E_PLAYER_ACCOUNT_MEMORY];
                for(new Iter:account_index_iter = list_iter(accountJoined); iter_inside(account_index_iter); iter_move_next(account_index_iter))
                {
                    if(iter_get_arr_safe(account_index_iter, account))
                    {
                        if(!strcmp(account[accountName], Account_ReturnName(playerid, 1)))
                        {
                            is_pCheckPassword[playerid] = true;
                            account_index[playerid] = iter_get_key(account_index_iter);
                            LoadingCircle_Start(playerid, 150);
                            MessageTDLine_ShowForPlayer(playerid, "Mat khau cang dai thi kiem tra cang lau, hay doi trong giay lat...", 3500);

                            bcrypt_check(Inputtext_AccountLogin[playerid], account[accountPassword], "OnPasswordChecked", "d", playerid);
                            return 1;
                        }   
                    }
                }
            }
            else MessageTDLine_ShowForPlayer(playerid, "Tai khoan cua ban dang trong qua trinh tim kiem, hay dot mot lat.", 2000);
        }
    }

    return 1;
}

hook OnPlayerClickPlayerTD(playerid, PlayerText:playertextid)
{
    if(PlayerIsConnected(playerid) == false)
    {
        if(playertextid == PlayerTD_AccountLogin[playerid][1])
        {
            Dialog_Show(playerid, DIALOG_LOGIN_ACCOUNT, DIALOG_STYLE_PASSWORD, "Login Account "ACCOUNT_VERSION"", "Ban hay nhap mat khau de dang nhap tai khoan", "Next", "Close");
        }
    }

    return 1;
}