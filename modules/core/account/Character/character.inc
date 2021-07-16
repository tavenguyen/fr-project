/*--- Project was created on 12:54 - 7/7/2021---*/
//    Founder: Halosetoe                       //
//    Leader Scripter: Halosetoe              //
//    Scripter: Halosetoe                    //
//    Game Content: Halosetoe               //
/*--------- Freedom Roleplay v0.1 ---------*/

stock CharacterCreate_Reset(playerid)
{
    CharacterCreate_Name[playerid][0] = EOS;
    CharacterCreate_Day[playerid] = 1;
    CharacterCreate_Month[playerid] = 1;
    CharacterCreate_Year[playerid] = MIN_CHARACTER_YEAR;
    CharacterCreate_Gender[playerid] = genderNone;
    CharacterCreate_SkinColor[playerid] = skinColor_none;
    CharacterCreate_Skin[playerid] = 1;
    return 1;
}

stock Character_Create(playerid)
{
    ClearChat(playerid);
    FadePlayerScreen(playerid, 0, _, 2000);
    wait_ms(2000);

    SetSpawnInfo(playerid, 0, 1, 153.7668, -1952.2461, 51.3438, 168.0762, 0, 0, 0, 0, 0, 0);
    SetPlayerVirtualWorld(playerid, playerid);
    TogglePlayerSpectating(playerid, false);
    
    SpawnPlayer(playerid);
    InterpolateCameraPos(playerid, 410.730316, -2048.952880, 9.475687, 154.062606, -1956.765380, 52.145137, 5000);
    InterpolateCameraLookAt(playerid, 406.256774, -2046.729248, 9.268309, 155.184997, -1951.946289, 51.426799, 2500);
    
    wait_ms(250);
    TogglePlayerControllable(playerid, false);
    CharacterCreate_Reset(playerid);
    format(CharacterCreate_Name[playerid], sizeof(CharacterCreate_Name), "%s", Account_ReturnName(playerid, 1));
    
    wait_ms(4500);
    GlobalTD_CharacterShow(playerid);
    ShowCharacterCreate(playerid);

    SelectTextDraw(playerid, 0xFFFFF00FF);
    return 1;   
}

stock Character_SelectSkin(playerid)
{
    GlobalTD_CharacterHide(playerid);
    PlayerTD_CharacterHide(playerid);

    CancelSelectTextDraw(playerid);

    InterpolateCameraPos(playerid, 153.880020, -1956.661621, 52.494308, 153.167556, -1955.375000, 51.384300, 5000);
    InterpolateCameraLookAt(playerid, 154.958084, -1952.056640, 50.871875, 154.187622, -1950.491210, 51.055629, 2500);
    
    wait_ms(5000);
    SelectTextDraw(playerid, 0xFFFFF00FF);

    PlayerEditCharacter[playerid] = true;
    GlobalTD_ShowCharacterSelSkin(playerid);
    PlayerTD_ShowCharacterSelSkin(playerid);

    return 1;
}

stock CharacterCreate_Finish(playerid)
{
    GlobalTD_HideCharacterSelSkin(playerid);
    PlayerTD_HideCharacterSelSkin(playerid);
    PlayerEditCharacter[playerid] = false;
    CancelSelectTextDraw(playerid);
    
    isPlayerConnected[playerid] = true;
    new character[E_CHARACTER_MEMORY];

    strcat(character[characterAccount], Account_ReturnName(playerid, 1)); 
    strcat(character[characterName], CharacterCreate_Name[playerid]);
    format(character[characterAccent], sizeof(character[characterAccent]), "none");
    format(character[characterDescribe], sizeof(character[characterDescribe]), "none");
    UUID(character[characterUUID], UUID_LEN);

    character[characterBirthday_Day] = CharacterCreate_Day[playerid]; 
    character[characterBirthday_Month] =CharacterCreate_Month[playerid];
    character[characterBirthday_Year] = CharacterCreate_Year[playerid];
    character[characterAge] = MAX_CHARACTER_YEAR - CharacterCreate_Year[playerid];
    character[characterGender] = CharacterCreate_Gender[playerid];
    character[characterSkinColor] = CharacterCreate_SkinColor[playerid];
    character[characterSkinID] = CharacterCreate_Skin[playerid];
    
    character[characterAdminLevel] = 0;

    character[characterInt] = 0;
    character[characterVW] = 0;
    
    character[characterPosX] = 1642.2733;
    character[characterPosY] = -2333.5156; 
    character[characterPosZ] = 13.5469;
    character[characterFacingAngle] = 358.6078;
    character[characterHealth] = 100.0;
    character[characterArmour] = 0.0;


    ClearChat(playerid);
    FadePlayerScreen(playerid, 0, _, 2000);
    SetPlayerName(playerid, CharacterCreate_Name[playerid]);    
    SetCameraBehindPlayer(playerid);
    SetPlayerPos(playerid, 1642.2733, -2333.5156, 13.5469);
    SetPlayerFacingAngle(playerid, 358.6078);
    SetPlayerInterior(playerid, 0);
    SetPlayerVirtualWorld(playerid, 0);
    TogglePlayerControllable(playerid, true);
    CharacterCreate_Reset(playerid);

    new query[500];
    mysql_format(MySQL_GetHandle(), query, sizeof(query), 
        "INSERT INTO `characters` VALUES ('%e', '%e', '%e', '%e', '%e', %d, %d, %d, %d, %d, %d, %d, %.4f, %.4f, %.4f, %.4f, %d, %d, %.4f, %.4f,\
        %d)",
    character[characterAccount], character[characterName], character[characterUUID], character[characterAccent], character[characterDescribe], character[characterAge], character[characterBirthday_Day],
    character[characterBirthday_Month], character[characterBirthday_Year], character[characterGender], character[characterSkinColor], character[characterSkinID],
    character[characterPosX], character[characterPosY], character[characterPosZ], character[characterFacingAngle], character[characterInt], character[characterVW], 
    character[characterHealth], character[characterArmour], character[characterAdminLevel]);
    
    mysql_tquery(MySQL_GetHandle(), query);

    character_index[playerid] =  list_add_arr(characters, character);
    return character_index[playerid];
}

stock Character_Join(playerid, const name[])
{
    new character[E_CHARACTER_MEMORY];
    for(new Iter:characters_index_iter = list_iter(characters); iter_inside(characters_index_iter); iter_move_next(characters_index_iter))
    {
        if(iter_get_arr_safe(characters_index_iter, character))
        {   
            if(!strcmp(character[characterName], name))
            {
                isPlayerConnected[playerid] = true;
                character_index[playerid] = iter_get_key(characters_index_iter);

                ClearChat(playerid);
                CancelSelectTextDraw(playerid);
                mysql_tquery(MySQL_GetHandle(), "SELECT * FROM `characters`", "OnCharacterReconnect", "dds", playerid, character_index[playerid], name);
                return 1;
            }
        }
    }

    return 0;
}

forward OnCharacterReconnect(playerid, index, const name[]);
public OnCharacterReconnect(playerid, index, const name[])
{
    new character_inside[E_CHARACTER_MEMORY];
    new rows = cache_num_rows();

    new character_temp[E_CHARACTER_MEMORY];
    for(new i = 0; i < rows; i++)
    {
        cache_get_value_name(i, "charName", character_temp[characterName], MAX_PLAYER_NAME + 1);
        if(!strcmp(character_temp[characterName], name))
        {
            cache_get_value_name(i, "charAccount", character_inside[characterAccount], MAX_PLAYER_NAME + 1);
            cache_get_value_name(i, "charName", character_inside[characterName], MAX_PLAYER_NAME + 1);
            cache_get_value_name(i, "charUUID", character_inside[characterUUID], UUID_LEN);
            cache_get_value_int(i, "charAge", character_inside[characterAge]);
            cache_get_value_int(i, "charBirthdayDay", character_inside[characterBirthday_Day]);
            cache_get_value_int(i, "charBirthdayMonth", character_inside[characterBirthday_Month]);
            cache_get_value_int(i, "charBirthdayYear", character_inside[characterBirthday_Year]);
            cache_get_value_int(i, "charGender", character_inside[characterGender]);
            cache_get_value_int(i, "charSkinColor", character_inside[characterSkinColor]);
            cache_get_value_int(i, "charSkin", character_inside[characterSkinID]);
            cache_get_value_float(i, "charPosX", character_inside[characterPosX]);
            cache_get_value_float(i, "charPosY", character_inside[characterPosY]);
            cache_get_value_float(i, "charPosZ", character_inside[characterPosZ]);
            cache_get_value_float(i, "charAngle", character_inside[characterFacingAngle]);
            cache_get_value_int(i, "charInteriorID", character_inside[characterInt]);
            cache_get_value_int(i, "charWorldID", character_inside[characterVW]);   
            cache_get_value_float(i, "charHealth", character_inside[characterHealth]);
            cache_get_value_float(i, "charArmour", character_inside[characterArmour]);
            list_set_arr(characters, index, character_inside);

            SetSpawnInfo(playerid, 0, character_inside[characterSkinID], character_inside[characterPosX], character_inside[characterPosY], character_inside[characterPosZ], character_inside[characterFacingAngle], 0, 0, 0, 0, 0, 0);
            SpawnPlayer(playerid);
            TogglePlayerSpectating(playerid, false);

            SetPlayerName(playerid, name);
           
            SetPlayerInterior(playerid, character_inside[characterInt]);
            SetPlayerVirtualWorld(playerid, character_inside[characterVW]);
            
            SetPlayerHealth(playerid, character_inside[characterHealth]);
            SetPlayerArmour(playerid, character_inside[characterArmour]);
            
            FadePlayerScreen(playerid, 0, _, 2000);

            wait_ms(2000);
            
            Msg(playerid, MSG_PREFIX_SUCCESS, "Chao mung ban den voi may chu.");
            return 1;
        }
    }

    return 0;
}

SaveCharacter(playerid)
{
    new character[E_CHARACTER_MEMORY];
    if(list_get_arr_safe(characters, character_index[playerid], character))
    {
        new Float:x, Float:y, Float:z, Float:angle;
        GetPlayerPos(playerid, x, y, z);
        GetPlayerFacingAngle(playerid, angle);

        new skinid = GetPlayerSkin(playerid);
        new int = GetPlayerInterior(playerid);
        new vw = GetPlayerVirtualWorld(playerid);

        new Float:health, Float:armour;
        GetPlayerHealth(playerid, health);
        GetPlayerArmour(playerid, armour);

        new query[500];
        mysql_format(MySQL_GetHandle(), query, sizeof(query), "UPDATE `characters` SET `charSkin` = %d, `charPosX` = %.4f, `charPosY` = %.4f, `charPosZ` = %.4f, `charAngle` = %.4f, `charInteriorID` = %d, `charWorldID` = %d, `charHealth` = %.4f, `charArmour` = %.4f WHERE `charUUID` = '%e'",
            skinid, x, y, z, angle, int, vw, health, armour, character[characterUUID]);
        mysql_tquery(MySQL_GetHandle(), query);
        printf(query);

        return 1;
    }

    return 0;
}

#include <YSI_Coding\y_hooks>
hook OnPlayerClickTextDraw(playerid, Text:clickedid)
{
    if(PlayerEditCharacter[playerid] == true)
    {
        if(clickedid == GlobalTD_Character[3])
        {
            if(CharacterCreate_Gender[playerid] == genderNone || CharacterCreate_SkinColor[playerid] == skinColor_none)
            {
                return Msg(playerid, MSG_PREFIX_ERROR, "Muc gioi tinh hoac chung toc khong chon, vui long chon de thuc hien tiep cac buoc tiep theo");
            }

            Character_SelectSkin(playerid);
            return 1;
        }

        if(clickedid == Text:INVALID_TEXT_DRAW)
        {
            PlayerEditCharacter[playerid] = false;
            GlobalTD_CharacterHide(playerid);
            PlayerTD_CharacterHide(playerid);
            KickEx(playerid, MSG_PREFIX_ERROR, "Ban da huy qua trinh tao nhanh vat, hay dang nhap lai neu muon tao lai.");
            return 1;
        }

        if(clickedid == GlobalTD_Character[4])
        {
            PlayerEditCharacter[playerid] = false;
            CharacterCreate_Reset(playerid);
            GlobalTD_CharacterHide(playerid);
            PlayerTD_CharacterHide(playerid);
            ClearChat(playerid);
            CallLocalFunction("OnAccountShowList", "is", playerid, Account_ReturnName(playerid, 1));
            return 1;
        }

        if(clickedid == GlobalTD_CharacterSelSkin[1])
        {
            if(CharacterCreate_Skin[playerid] == 1)
            {
                return Msg(playerid, MSG_PREFIX_ERROR, "Ban khong the thao tac nua.");
            }

            CharacterCreate_Skin[playerid]--;
            SetPlayerSkin(playerid, CharacterCreate_Skin[playerid]);

            new string[10];
            if(CharacterCreate_Skin[playerid] < 10) format(string, sizeof(string), "00%d",  CharacterCreate_Skin[playerid]);
            if(CharacterCreate_Skin[playerid] >= 10 &&  CharacterCreate_Skin[playerid] < 100) format(string, sizeof(string), "0%d",  CharacterCreate_Skin[playerid]);
            if(CharacterCreate_Skin[playerid] >= 100) format(string, sizeof(string), "%d",  CharacterCreate_Skin[playerid]);

            PlayerTextDrawHide(playerid, PlayerTD_CharacterSelSkin[playerid][0]);
            PlayerTextDrawSetString(playerid, PlayerTD_CharacterSelSkin[playerid][0], string);
            PlayerTextDrawShow(playerid, PlayerTD_CharacterSelSkin[playerid][0]);

            return 1;
        }

        if(clickedid == GlobalTD_CharacterSelSkin[2])
        {
            if(CharacterCreate_Skin[playerid] == 312)
            {
                return Msg(playerid, MSG_PREFIX_ERROR, "Ban khong the thao tac nua.");
            }

            CharacterCreate_Skin[playerid]++;
            SetPlayerSkin(playerid, CharacterCreate_Skin[playerid]);

            new string[10];
            if(CharacterCreate_Skin[playerid] < 10) format(string, sizeof(string), "00%d", CharacterCreate_Skin[playerid]);
            if(CharacterCreate_Skin[playerid] >= 10 && CharacterCreate_Skin[playerid] < 100) format(string, sizeof(string), "0%d", CharacterCreate_Skin[playerid]);
            if(CharacterCreate_Skin[playerid] >= 100) format(string, sizeof(string), "%d", CharacterCreate_Skin[playerid]);

            PlayerTextDrawHide(playerid, PlayerTD_CharacterSelSkin[playerid][0]);
            PlayerTextDrawSetString(playerid, PlayerTD_CharacterSelSkin[playerid][0], string);
            PlayerTextDrawShow(playerid, PlayerTD_CharacterSelSkin[playerid][0]);

            return 1;
        }

        if(clickedid == GlobalTD_CharacterSelSkin[3])
        {
            Msg(playerid, MSG_PREFIX_SUCCESS, "Ban da hoan tat qua trinh tao nhan vat, chao mung ban den voi thanh pho.");
            CharacterCreate_Finish(playerid);
            
            return 1;
        }
    }

    return 1;
}

hook OnPlayerClickPlayerTD(playerid, PlayerText:playertextid)
{
    if(PlayerEditCharacter[playerid] == true)
    {
    // Character name change.
        if(playertextid == PlayerTD_CharacterCreate[playerid][0])
        {
            SendClientMessage(playerid, -1, "debug");
            Dialog_Show(playerid, DIALOG_CHAR_NAME_INPUT, DIALOG_STYLE_INPUT, "Input Character Name", "Ban hay nhap vao ten nhan vat cua ban.", "Accept", "Close");
        }

        // Birthday - day
        if(playertextid == PlayerTD_CharacterCreate[playerid][2])
        {
            Dialog_Show(playerid, DIALOG_CHAR_BORN_DAY, DIALOG_STYLE_INPUT, "Input Birthday", "Ban hay nhap vao ngay sinh cua nhan vat.", "Accept", "Cancel");
        }

        // Birthday - month
        if(playertextid == PlayerTD_CharacterCreate[playerid][3])
        {
            Dialog_Show(playerid, DIALOG_CHAR_BORN_MONTH, DIALOG_STYLE_INPUT, "Input Birthday", "Ban hay nhap vao day thang sinh cua nhan vat ban.", "Accept", "Cancel");
        }

        // Birthday - year
        if(playertextid == PlayerTD_CharacterCreate[playerid][4])
        {
            Dialog_Show(playerid, DIALOG_CHAR_BORN_YEAR, DIALOG_STYLE_INPUT, "Input Birthday", "Ban hay nhap vao day nam sinh cua nhan vat ban.", "Accept", "Cancel");
        }

        // Gender
        if(playertextid == PlayerTD_CharacterCreate[playerid][5])
        {
            Dialog_Show(playerid, DIALOG_CHAR_GENDER, DIALOG_STYLE_LIST, "Gender Selection", "Male\nFemale", "Accept", "Cancel");
        }

        // Skin Color
        if(playertextid == PlayerTD_CharacterCreate[playerid][6])
        {
            Dialog_Show(playerid, DIALOG_CHAR_SKIN_COLOR, DIALOG_STYLE_LIST, "Skin Color Selection", "White\nYellow\nBlack", "Accept", "Cancel");
        }

        // Select Skin
        if(playertextid == PlayerTD_CharacterSelSkin[playerid][0])
        {   
            Dialog_Show(playerid, DIALOG_CHAR_SELECT_SKIN, DIALOG_STYLE_INPUT, "Skin Input", "Hay nhap vao day Skin ID ma ban muon.", "Accept", "Cancel");
        }
    }

    return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    if(PlayerIsConnected(playerid))
    {
        new szString[100];
        new szDisconnectReason[3][] =
        {
            "Timeout/Crash",
            "Quit",
            "Kick/Ban"
        };

        format(szString, sizeof(szString), "Nguoi choi %s vua thoat khoi may chu (Ly do: %s)", Account_ReturnName(playerid, 0), szDisconnectReason[reason]);
        ProxDetector(playerid, 10.0, COLOR_GREY, szString);
        printf(szString);

        if(SaveCharacter(playerid) == 1) 
        {
            printf("Luu thanh cong nhan vat %s", Account_ReturnName(playerid));
            character_index[playerid] = -1;
        }
        else printf("[ERROR] Luu khong thanh cong nhan vat %s", Account_ReturnName(playerid));
    }
    else printf("[ERROR] Nguoi choi chua dang nhap.");

    return 1;
}
