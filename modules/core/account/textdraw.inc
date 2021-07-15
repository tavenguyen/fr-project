/*--- Project was created on 12:54 - 7/7/2021---*/
//    Founder: Halosetoe                       //
//    Leader Scripter: Halosetoe              //
//    Scripter: Halosetoe                    //
//    Game Content: Halosetoe               //
/*--------- Freedom Roleplay v0.1 ---------*/


new 
    Text:GlobalTD_AccountLogin[3] = Text:INVALID_TEXT_DRAW,
    Text:GlobalTD_CharacterSelSkin[4] = Text:INVALID_TEXT_DRAW,
    Text:GlobalTD_Character[5] = Text:INVALID_TEXT_DRAW,
    PlayerText:PlayerTD_AccountLogin[MAX_PLAYERS][2] = { {PlayerText:INVALID_PLAYER_TEXT_DRAW}, ... },
    PlayerText:PlayerTD_CharacterCreate[MAX_PLAYERS][7] = { {PlayerText:INVALID_PLAYER_TEXT_DRAW}, ... },
    PlayerText:PlayerTD_CharacterSelSkin[MAX_PLAYERS][1] = {PlayerText:INVALID_PLAYER_TEXT_DRAW, ...};

stock F_GlobalTD_AccountLogin()
{
    GlobalTD_AccountLogin[0] = TextDrawCreate(47.400070, 90.250007, "mdl-2000:fc_register_login");
    TextDrawLetterSize(GlobalTD_AccountLogin[0], 0.000000, 0.000000);
    TextDrawTextSize(GlobalTD_AccountLogin[0], 181.000000, 96.000000);
    TextDrawAlignment(GlobalTD_AccountLogin[0], 1);
    TextDrawColor(GlobalTD_AccountLogin[0], -1);
    TextDrawSetShadow(GlobalTD_AccountLogin[0], 0);
    TextDrawSetOutline(GlobalTD_AccountLogin[0], 0);
    TextDrawBackgroundColor(GlobalTD_AccountLogin[0], 255);
    TextDrawFont(GlobalTD_AccountLogin[0], 4);
    TextDrawSetProportional(GlobalTD_AccountLogin[0], 0);
    TextDrawSetShadow(GlobalTD_AccountLogin[0], 0);

    GlobalTD_AccountLogin[1] = TextDrawCreate(137.700103, 97.833328, "login");
    TextDrawLetterSize(GlobalTD_AccountLogin[1], 0.286999, 1.109999);
    TextDrawAlignment(GlobalTD_AccountLogin[1], 2);
    TextDrawColor(GlobalTD_AccountLogin[1], -56);
    TextDrawSetShadow(GlobalTD_AccountLogin[1], 0);
    TextDrawSetOutline(GlobalTD_AccountLogin[1], 0);
    TextDrawBackgroundColor(GlobalTD_AccountLogin[1], 255);
    TextDrawFont(GlobalTD_AccountLogin[1], 2);
    TextDrawSetProportional(GlobalTD_AccountLogin[1], 1);
    TextDrawSetShadow(GlobalTD_AccountLogin[1], 0);

    GlobalTD_AccountLogin[2] = TextDrawCreate(137.700103, 168.335327, "> LOGIN <");
    TextDrawLetterSize(GlobalTD_AccountLogin[2], 0.286999, 1.109999);
    TextDrawTextSize(GlobalTD_AccountLogin[2], 10.000000, 67.000000);
    TextDrawAlignment(GlobalTD_AccountLogin[2], 2);
    TextDrawColor(GlobalTD_AccountLogin[2], -56);
    TextDrawUseBox(GlobalTD_AccountLogin[2], 1);
    TextDrawBoxColor(GlobalTD_AccountLogin[2], 0);
    TextDrawSetShadow(GlobalTD_AccountLogin[2], 0);
    TextDrawSetOutline(GlobalTD_AccountLogin[2], 0);
    TextDrawBackgroundColor(GlobalTD_AccountLogin[2], 255);
    TextDrawFont(GlobalTD_AccountLogin[2], 2);
    TextDrawSetProportional(GlobalTD_AccountLogin[2], 1);
    TextDrawSetShadow(GlobalTD_AccountLogin[2], 0);
    TextDrawSetSelectable(GlobalTD_AccountLogin[2], true);
}

stock F_PlayerTD_AccountLogin(playerid)
{
    PlayerTD_AccountLogin[playerid][0] = CreatePlayerTextDraw(playerid, 138.100128, 121.632965, "KeAndre_Richardson");
    PlayerTextDrawLetterSize(playerid, PlayerTD_AccountLogin[playerid][0], 0.286999, 1.109999);
    PlayerTextDrawAlignment(playerid, PlayerTD_AccountLogin[playerid][0], 2);
    PlayerTextDrawColor(playerid, PlayerTD_AccountLogin[playerid][0], -56);
    PlayerTextDrawUseBox(playerid, PlayerTD_AccountLogin[playerid][0], 1);
    PlayerTextDrawBoxColor(playerid, PlayerTD_AccountLogin[playerid][0], 0);
    PlayerTextDrawSetShadow(playerid, PlayerTD_AccountLogin[playerid][0], 0);
    PlayerTextDrawSetOutline(playerid, PlayerTD_AccountLogin[playerid][0], 0);
    PlayerTextDrawBackgroundColor(playerid, PlayerTD_AccountLogin[playerid][0], 255);
    PlayerTextDrawFont(playerid, PlayerTD_AccountLogin[playerid][0], 1);
    PlayerTextDrawSetProportional(playerid, PlayerTD_AccountLogin[playerid][0], 1);
    PlayerTextDrawSetShadow(playerid, PlayerTD_AccountLogin[playerid][0], 0);

    PlayerTD_AccountLogin[playerid][1] = CreatePlayerTextDraw(playerid, 138.100128, 144.133850, "CLICK HERE");
    PlayerTextDrawLetterSize(playerid, PlayerTD_AccountLogin[playerid][1], 0.286999, 1.109999);
    PlayerTextDrawTextSize(playerid, PlayerTD_AccountLogin[playerid][1], 10.000000, 118.000000);
    PlayerTextDrawAlignment(playerid, PlayerTD_AccountLogin[playerid][1], 2);
    PlayerTextDrawColor(playerid, PlayerTD_AccountLogin[playerid][1], -56);
    PlayerTextDrawUseBox(playerid, PlayerTD_AccountLogin[playerid][1], 1);
    PlayerTextDrawBoxColor(playerid, PlayerTD_AccountLogin[playerid][1], 0);
    PlayerTextDrawSetShadow(playerid, PlayerTD_AccountLogin[playerid][1], 0);
    PlayerTextDrawSetOutline(playerid, PlayerTD_AccountLogin[playerid][1], 0);
    PlayerTextDrawBackgroundColor(playerid, PlayerTD_AccountLogin[playerid][1], 255);
    PlayerTextDrawFont(playerid, PlayerTD_AccountLogin[playerid][1], 1);
    PlayerTextDrawSetProportional(playerid, PlayerTD_AccountLogin[playerid][1], 1);
    PlayerTextDrawSetShadow(playerid, PlayerTD_AccountLogin[playerid][1], 0);
    PlayerTextDrawSetSelectable(playerid, PlayerTD_AccountLogin[playerid][1], true);

    PlayerTextDrawSetString(playerid, PlayerTD_AccountLogin[playerid][0], Account_ReturnName(playerid, 1));

    for(new i = 0; i < 2; i++)
    {
        PlayerTextDrawShow(playerid, PlayerTD_AccountLogin[playerid][i]);
    }

    return 1;
}

stock F_GlobalTD_AccountLoginShow(playerid)
{
    for(new i = 0; i < sizeof(GlobalTD_AccountLogin); i++)
    {
        TextDrawShowForPlayer(playerid, GlobalTD_AccountLogin[i]);
    }

    return 1;
}

stock F_GlobalTD_AccountLoginHide(playerid)
{
    for(new i = 0; i < sizeof(GlobalTD_AccountLogin); i++)
    {
        TextDrawHideForPlayer(playerid, GlobalTD_AccountLogin[i]);
    }

    return 1;
}


stock F_PlayerTD_AccountLoginHide(playerid)
{
    for(new i = 0; i < sizeof(PlayerTD_AccountLogin); i++)
    {
        PlayerTextDrawHide(playerid, PlayerTD_AccountLogin[playerid][i]);
        PlayerTextDrawDestroy(playerid, PlayerTD_AccountLogin[playerid][i]);
    }

    return 1;
}

stock GlobalTD_CharacterCreate()
{
    GlobalTD_Character[0] = TextDrawCreate(358.500000, 21.416652, "mdl-2000:fc_character_create");
    TextDrawLetterSize(GlobalTD_Character[0], 0.000000, 0.000000);
    TextDrawTextSize(GlobalTD_Character[0], 260.000000, 311.000000);
    TextDrawAlignment(GlobalTD_Character[0], 1);
    TextDrawColor(GlobalTD_Character[0], -1);
    TextDrawSetShadow(GlobalTD_Character[0], 0);
    TextDrawSetOutline(GlobalTD_Character[0], 0);
    TextDrawBackgroundColor(GlobalTD_Character[0], 255);
    TextDrawFont(GlobalTD_Character[0], 4);
    TextDrawSetProportional(GlobalTD_Character[0], 0);
    TextDrawSetShadow(GlobalTD_Character[0], 0);

    GlobalTD_Character[1] = TextDrawCreate(535.901367, 171.517135, "/");
    TextDrawLetterSize(GlobalTD_Character[1], 0.214999, 1.407501);
    TextDrawAlignment(GlobalTD_Character[1], 2);
    TextDrawColor(GlobalTD_Character[1], 255);
    TextDrawSetShadow(GlobalTD_Character[1], 0);
    TextDrawSetOutline(GlobalTD_Character[1], 0);
    TextDrawBackgroundColor(GlobalTD_Character[1], 255);
    TextDrawFont(GlobalTD_Character[1], 1);
    TextDrawSetProportional(GlobalTD_Character[1], 1);
    TextDrawSetShadow(GlobalTD_Character[1], 0);

    GlobalTD_Character[2] = TextDrawCreate(548.098388, 171.517135, "/");
    TextDrawLetterSize(GlobalTD_Character[2], 0.214999, 1.407501);
    TextDrawAlignment(GlobalTD_Character[2], 2);
    TextDrawColor(GlobalTD_Character[2], 255);
    TextDrawSetShadow(GlobalTD_Character[2], 0);
    TextDrawSetOutline(GlobalTD_Character[2], 0);
    TextDrawBackgroundColor(GlobalTD_Character[2], 255);
    TextDrawFont(GlobalTD_Character[2], 1);
    TextDrawSetProportional(GlobalTD_Character[2], 1);
    TextDrawSetShadow(GlobalTD_Character[2], 0);

    GlobalTD_Character[3] = TextDrawCreate(582.500000, 304.933532, "Confirm");
    TextDrawLetterSize(GlobalTD_Character[3], 0.270999, 1.366665);
    TextDrawTextSize(GlobalTD_Character[3], 10.000000, 32.000000);
    TextDrawAlignment(GlobalTD_Character[3], 2);
    TextDrawColor(GlobalTD_Character[3], 255);
    TextDrawUseBox(GlobalTD_Character[3], 1);
    TextDrawBoxColor(GlobalTD_Character[3], 0);
    TextDrawSetShadow(GlobalTD_Character[3], 0);
    TextDrawSetOutline(GlobalTD_Character[3], 0);
    TextDrawBackgroundColor(GlobalTD_Character[3], 255);
    TextDrawFont(GlobalTD_Character[3], 1);
    TextDrawSetProportional(GlobalTD_Character[3], 1);
    TextDrawSetShadow(GlobalTD_Character[3], 0);
    TextDrawSetSelectable(GlobalTD_Character[3], true);

    GlobalTD_Character[4] = TextDrawCreate(393.849822, 305.516754, "Cancel");
    TextDrawLetterSize(GlobalTD_Character[4], 0.270999, 1.366665);
    TextDrawTextSize(GlobalTD_Character[4], 10.000000, 46.000000);
    TextDrawAlignment(GlobalTD_Character[4], 2);
    TextDrawColor(GlobalTD_Character[4], 255);
    TextDrawUseBox(GlobalTD_Character[4], 1);
    TextDrawBoxColor(GlobalTD_Character[4], 0);
    TextDrawSetShadow(GlobalTD_Character[4], 0);
    TextDrawSetOutline(GlobalTD_Character[4], 0);
    TextDrawBackgroundColor(GlobalTD_Character[4], 255);
    TextDrawFont(GlobalTD_Character[4], 1);
    TextDrawSetProportional(GlobalTD_Character[4], 1);
    TextDrawSetShadow(GlobalTD_Character[4], 0);
    TextDrawSetSelectable(GlobalTD_Character[4], true);
}

stock ShowCharacterCreate(playerid)
{
    PlayerTD_CharacterCreate[playerid][0] = CreatePlayerTextDraw(playerid, 546.800292, 76.233932, "KeAndre_Richardson");
    PlayerTextDrawLetterSize(playerid, PlayerTD_CharacterCreate[playerid][0], 0.214999, 1.407500);
    PlayerTextDrawTextSize(playerid, PlayerTD_CharacterCreate[playerid][0], 12.000000, 120.000000);
    PlayerTextDrawAlignment(playerid, PlayerTD_CharacterCreate[playerid][0], 2);
    PlayerTextDrawColor(playerid, PlayerTD_CharacterCreate[playerid][0], 255);
    PlayerTextDrawUseBox(playerid, PlayerTD_CharacterCreate[playerid][0], 1);
    PlayerTextDrawBoxColor(playerid, PlayerTD_CharacterCreate[playerid][0], 0);
    PlayerTextDrawSetShadow(playerid, PlayerTD_CharacterCreate[playerid][0], 0);
    PlayerTextDrawSetOutline(playerid, PlayerTD_CharacterCreate[playerid][0], 0);
    PlayerTextDrawBackgroundColor(playerid, PlayerTD_CharacterCreate[playerid][0], 255);
    PlayerTextDrawFont(playerid, PlayerTD_CharacterCreate[playerid][0], 1);
    PlayerTextDrawSetProportional(playerid, PlayerTD_CharacterCreate[playerid][0], 1);
    PlayerTextDrawSetShadow(playerid, PlayerTD_CharacterCreate[playerid][0], 0);
    PlayerTextDrawSetSelectable(playerid, PlayerTD_CharacterCreate[playerid][0], true);

    PlayerTD_CharacterCreate[playerid][1] = CreatePlayerTextDraw(playerid, 544.400024, 125.633567, "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
    PlayerTextDrawLetterSize(playerid, PlayerTD_CharacterCreate[playerid][1], 0.147999, 1.483332);
    PlayerTextDrawAlignment(playerid, PlayerTD_CharacterCreate[playerid][1], 2);
    PlayerTextDrawColor(playerid, PlayerTD_CharacterCreate[playerid][1], 255);
    PlayerTextDrawSetShadow(playerid, PlayerTD_CharacterCreate[playerid][1], 0);
    PlayerTextDrawSetOutline(playerid, PlayerTD_CharacterCreate[playerid][1], 0);
    PlayerTextDrawBackgroundColor(playerid, PlayerTD_CharacterCreate[playerid][1], 255);
    PlayerTextDrawFont(playerid, PlayerTD_CharacterCreate[playerid][1], 1);
    PlayerTextDrawSetProportional(playerid, PlayerTD_CharacterCreate[playerid][1], 1);
    PlayerTextDrawSetShadow(playerid, PlayerTD_CharacterCreate[playerid][1], 0);

    PlayerTD_CharacterCreate[playerid][2] = CreatePlayerTextDraw(playerid, 528.602661, 172.350631, "06");
    PlayerTextDrawLetterSize(playerid, PlayerTD_CharacterCreate[playerid][2], 0.214999, 1.407500);
    PlayerTextDrawTextSize(playerid, PlayerTD_CharacterCreate[playerid][2], 10.000000, 4.000000);
    PlayerTextDrawAlignment(playerid, PlayerTD_CharacterCreate[playerid][2], 2);
    PlayerTextDrawColor(playerid, PlayerTD_CharacterCreate[playerid][2], 255);
    PlayerTextDrawUseBox(playerid, PlayerTD_CharacterCreate[playerid][2], 1);
    PlayerTextDrawBoxColor(playerid, PlayerTD_CharacterCreate[playerid][2], 0);
    PlayerTextDrawSetShadow(playerid, PlayerTD_CharacterCreate[playerid][2], 0);
    PlayerTextDrawSetOutline(playerid, PlayerTD_CharacterCreate[playerid][2], 0);
    PlayerTextDrawBackgroundColor(playerid, PlayerTD_CharacterCreate[playerid][2], 255);
    PlayerTextDrawFont(playerid, PlayerTD_CharacterCreate[playerid][2], 1);
    PlayerTextDrawSetProportional(playerid, PlayerTD_CharacterCreate[playerid][2], 1);
    PlayerTextDrawSetShadow(playerid, PlayerTD_CharacterCreate[playerid][2], 0);
    PlayerTextDrawSetSelectable(playerid, PlayerTD_CharacterCreate[playerid][2], true);

    PlayerTD_CharacterCreate[playerid][3] = CreatePlayerTextDraw(playerid, 541.999877, 172.417190, "11");
    PlayerTextDrawLetterSize(playerid, PlayerTD_CharacterCreate[playerid][3], 0.214999, 1.407500);
    PlayerTextDrawTextSize(playerid, PlayerTD_CharacterCreate[playerid][3], 10.000000, 4.000000);
    PlayerTextDrawAlignment(playerid, PlayerTD_CharacterCreate[playerid][3], 2);
    PlayerTextDrawColor(playerid, PlayerTD_CharacterCreate[playerid][3], 255);
    PlayerTextDrawUseBox(playerid, PlayerTD_CharacterCreate[playerid][3], 1);
    PlayerTextDrawBoxColor(playerid, PlayerTD_CharacterCreate[playerid][3], 0);
    PlayerTextDrawSetShadow(playerid, PlayerTD_CharacterCreate[playerid][3], 0);
    PlayerTextDrawSetOutline(playerid, PlayerTD_CharacterCreate[playerid][3], 0);
    PlayerTextDrawBackgroundColor(playerid, PlayerTD_CharacterCreate[playerid][3], 255);
    PlayerTextDrawFont(playerid, PlayerTD_CharacterCreate[playerid][3], 1);
    PlayerTextDrawSetProportional(playerid, PlayerTD_CharacterCreate[playerid][3], 1);
    PlayerTextDrawSetShadow(playerid, PlayerTD_CharacterCreate[playerid][3], 0);
    PlayerTextDrawSetSelectable(playerid, PlayerTD_CharacterCreate[playerid][3], true);

    PlayerTD_CharacterCreate[playerid][4] = CreatePlayerTextDraw(playerid, 557.496093, 172.400482, "1995");
    PlayerTextDrawLetterSize(playerid, PlayerTD_CharacterCreate[playerid][4], 0.214999, 1.407500);
    PlayerTextDrawTextSize(playerid, PlayerTD_CharacterCreate[playerid][4], 10.000000, 13.000000);
    PlayerTextDrawAlignment(playerid, PlayerTD_CharacterCreate[playerid][4], 2);
    PlayerTextDrawColor(playerid, PlayerTD_CharacterCreate[playerid][4], 255);
    PlayerTextDrawUseBox(playerid, PlayerTD_CharacterCreate[playerid][4], 1);
    PlayerTextDrawBoxColor(playerid, PlayerTD_CharacterCreate[playerid][4], 0);
    PlayerTextDrawSetShadow(playerid, PlayerTD_CharacterCreate[playerid][4], 0);
    PlayerTextDrawSetOutline(playerid, PlayerTD_CharacterCreate[playerid][4], 0);
    PlayerTextDrawBackgroundColor(playerid, PlayerTD_CharacterCreate[playerid][4], 0);
    PlayerTextDrawFont(playerid, PlayerTD_CharacterCreate[playerid][4], 1);
    PlayerTextDrawSetProportional(playerid, PlayerTD_CharacterCreate[playerid][4], 1);
    PlayerTextDrawSetShadow(playerid, PlayerTD_CharacterCreate[playerid][4], 0);
    PlayerTextDrawSetSelectable(playerid, PlayerTD_CharacterCreate[playerid][4], true);

    PlayerTD_CharacterCreate[playerid][5] = CreatePlayerTextDraw(playerid, 543.496948, 221.633911, "CLICK HERE");
    PlayerTextDrawLetterSize(playerid, PlayerTD_CharacterCreate[playerid][5], 0.214999, 1.407500);
    PlayerTextDrawTextSize(playerid, PlayerTD_CharacterCreate[playerid][5], 10.000000, 51.000000);
    PlayerTextDrawAlignment(playerid, PlayerTD_CharacterCreate[playerid][5], 2);
    PlayerTextDrawColor(playerid, PlayerTD_CharacterCreate[playerid][5], 255);
    PlayerTextDrawUseBox(playerid, PlayerTD_CharacterCreate[playerid][5], 1);
    PlayerTextDrawBoxColor(playerid, PlayerTD_CharacterCreate[playerid][5], 0);
    PlayerTextDrawSetShadow(playerid, PlayerTD_CharacterCreate[playerid][5], 0);
    PlayerTextDrawSetOutline(playerid, PlayerTD_CharacterCreate[playerid][5], 0);
    PlayerTextDrawBackgroundColor(playerid, PlayerTD_CharacterCreate[playerid][5], 255);
    PlayerTextDrawFont(playerid, PlayerTD_CharacterCreate[playerid][5], 1);
    PlayerTextDrawSetProportional(playerid, PlayerTD_CharacterCreate[playerid][5], 1);
    PlayerTextDrawSetShadow(playerid, PlayerTD_CharacterCreate[playerid][5], 0);
    PlayerTextDrawSetSelectable(playerid, PlayerTD_CharacterCreate[playerid][5], true);

    PlayerTD_CharacterCreate[playerid][6] = CreatePlayerTextDraw(playerid, 543.896728, 270.886810, "CLICK HERE");
    PlayerTextDrawLetterSize(playerid, PlayerTD_CharacterCreate[playerid][6], 0.217928, 1.424999);
    PlayerTextDrawTextSize(playerid, PlayerTD_CharacterCreate[playerid][6], 10.000000, 49.000000);
    PlayerTextDrawAlignment(playerid, PlayerTD_CharacterCreate[playerid][6], 2);
    PlayerTextDrawColor(playerid, PlayerTD_CharacterCreate[playerid][6], 255);
    PlayerTextDrawUseBox(playerid, PlayerTD_CharacterCreate[playerid][6], 1);
    PlayerTextDrawBoxColor(playerid, PlayerTD_CharacterCreate[playerid][6], 0);
    PlayerTextDrawSetShadow(playerid, PlayerTD_CharacterCreate[playerid][6], 0);
    PlayerTextDrawSetOutline(playerid, PlayerTD_CharacterCreate[playerid][6], 0);
    PlayerTextDrawBackgroundColor(playerid, PlayerTD_CharacterCreate[playerid][6], 255);
    PlayerTextDrawFont(playerid, PlayerTD_CharacterCreate[playerid][6], 1);
    PlayerTextDrawSetProportional(playerid, PlayerTD_CharacterCreate[playerid][6], 1);
    PlayerTextDrawSetShadow(playerid, PlayerTD_CharacterCreate[playerid][6], 0);
    PlayerTextDrawSetSelectable(playerid, PlayerTD_CharacterCreate[playerid][6], true);

    new string[128];
    format(string, sizeof(string), "%s", Account_ReturnName(playerid));
    PlayerTextDrawSetString(playerid, PlayerTD_CharacterCreate[playerid][0], string);
    PlayerTextDrawSetString(playerid, PlayerTD_CharacterCreate[playerid][1], "38th Washington St, Jefferson, Los Santos.");

    format(string, sizeof(string), "0%d", CharacterCreate_Day[playerid]);
    PlayerTextDrawSetString(playerid, PlayerTD_CharacterCreate[playerid][2], string);

    format(string, sizeof(string), "0%d", CharacterCreate_Month[playerid]);
    PlayerTextDrawSetString(playerid, PlayerTD_CharacterCreate[playerid][3], string);

    format(string, sizeof(string), "%d", CharacterCreate_Year[playerid]);
    PlayerTextDrawSetString(playerid, PlayerTD_CharacterCreate[playerid][4], string);

    if(CharacterCreate_Gender[playerid] == genderNone)
    {
        PlayerTextDrawSetString(playerid, PlayerTD_CharacterCreate[playerid][5], "None");
    }

    if(CharacterCreate_SkinColor[playerid] == skinColor_none)
    {
        PlayerTextDrawSetString(playerid, PlayerTD_CharacterCreate[playerid][6], "None");
    }

    for(new i = 0; i < 7; i++)
    {
        PlayerTextDrawShow(playerid, PlayerTD_CharacterCreate[playerid][i]);
    }
    
    PlayerEditCharacter[playerid] = true;
    return 1;
}

stock GlobalTD_CharacterSelectSkin()
{
    GlobalTD_CharacterSelSkin[0] = TextDrawCreate(258.658721, 400.017089, "box");
    TextDrawLetterSize(GlobalTD_CharacterSelSkin[0], 0.000000, 4.150000);
    TextDrawTextSize(GlobalTD_CharacterSelSkin[0], 375.000000, 0.000000);
    TextDrawAlignment(GlobalTD_CharacterSelSkin[0], 1);
    TextDrawColor(GlobalTD_CharacterSelSkin[0], -1);
    TextDrawUseBox(GlobalTD_CharacterSelSkin[0], 1);
    TextDrawBoxColor(GlobalTD_CharacterSelSkin[0], 690629631);
    TextDrawSetShadow(GlobalTD_CharacterSelSkin[0], 0);
    TextDrawSetOutline(GlobalTD_CharacterSelSkin[0], 1);
    TextDrawBackgroundColor(GlobalTD_CharacterSelSkin[0], 255);
    TextDrawFont(GlobalTD_CharacterSelSkin[0], 1);
    TextDrawSetProportional(GlobalTD_CharacterSelSkin[0], 1);
    TextDrawSetShadow(GlobalTD_CharacterSelSkin[0], 0);

    GlobalTD_CharacterSelSkin[1] = TextDrawCreate(264.999969, 400.466400, "LD_BEAT:left");
    TextDrawLetterSize(GlobalTD_CharacterSelSkin[1], 0.000000, 0.000000);
    TextDrawTextSize(GlobalTD_CharacterSelSkin[1], 19.000000, 23.000000);
    TextDrawAlignment(GlobalTD_CharacterSelSkin[1], 1);
    TextDrawColor(GlobalTD_CharacterSelSkin[1], -1111373825);
    TextDrawSetShadow(GlobalTD_CharacterSelSkin[1], 0);
    TextDrawSetOutline(GlobalTD_CharacterSelSkin[1], 0);
    TextDrawBackgroundColor(GlobalTD_CharacterSelSkin[1], 255);
    TextDrawFont(GlobalTD_CharacterSelSkin[1], 4);
    TextDrawSetProportional(GlobalTD_CharacterSelSkin[1], 0);
    TextDrawSetShadow(GlobalTD_CharacterSelSkin[1], 0);
    TextDrawSetSelectable(GlobalTD_CharacterSelSkin[1], true);

    GlobalTD_CharacterSelSkin[2] = TextDrawCreate(347.899993, 400.366333, "LD_BEAT:right");
    TextDrawLetterSize(GlobalTD_CharacterSelSkin[2], 0.000000, 0.000000);
    TextDrawTextSize(GlobalTD_CharacterSelSkin[2], 19.000000, 23.000000);
    TextDrawAlignment(GlobalTD_CharacterSelSkin[2], 1);
    TextDrawColor(GlobalTD_CharacterSelSkin[2], -1111373825);
    TextDrawSetShadow(GlobalTD_CharacterSelSkin[2], 0);
    TextDrawSetOutline(GlobalTD_CharacterSelSkin[2], 0);
    TextDrawBackgroundColor(GlobalTD_CharacterSelSkin[2], 255);
    TextDrawFont(GlobalTD_CharacterSelSkin[2], 4);
    TextDrawSetProportional(GlobalTD_CharacterSelSkin[2], 0);
    TextDrawSetShadow(GlobalTD_CharacterSelSkin[2], 0);
    TextDrawSetSelectable(GlobalTD_CharacterSelSkin[2], true);
    
    
    GlobalTD_CharacterSelSkin[3] = TextDrawCreate(316.299957, 423.283203, "Accept");
    TextDrawLetterSize(GlobalTD_CharacterSelSkin[3], 0.265999, 1.203333);
    TextDrawTextSize(GlobalTD_CharacterSelSkin[3], 5.000000, 40.000000);
    TextDrawAlignment(GlobalTD_CharacterSelSkin[3], 2);
    TextDrawColor(GlobalTD_CharacterSelSkin[3], -1);
    TextDrawUseBox(GlobalTD_CharacterSelSkin[3], 1);
    TextDrawBoxColor(GlobalTD_CharacterSelSkin[3], 454893567);
    TextDrawSetShadow(GlobalTD_CharacterSelSkin[3], 0);
    TextDrawSetOutline(GlobalTD_CharacterSelSkin[3], 1);
    TextDrawBackgroundColor(GlobalTD_CharacterSelSkin[3], 255);
    TextDrawFont(GlobalTD_CharacterSelSkin[3], 1);
    TextDrawSetProportional(GlobalTD_CharacterSelSkin[3], 1);
    TextDrawSetShadow(GlobalTD_CharacterSelSkin[3], 0);
    TextDrawSetSelectable(GlobalTD_CharacterSelSkin[3], true);

    return 1;
}

stock PlayerTD_ShowCharacterSelSkin(playerid)
{
    PlayerTD_CharacterSelSkin[playerid][0] = CreatePlayerTextDraw(playerid, 316.299987, 405.949829, "001");
    PlayerTextDrawLetterSize(playerid, PlayerTD_CharacterSelSkin[playerid][0], 0.333999, 1.343333);
    PlayerTextDrawTextSize(playerid, PlayerTD_CharacterSelSkin[playerid][0], 5.000000, 30.000000);
    PlayerTextDrawAlignment(playerid, PlayerTD_CharacterSelSkin[playerid][0], 2);
    PlayerTextDrawColor(playerid, PlayerTD_CharacterSelSkin[playerid][0], -1);
    PlayerTextDrawUseBox(playerid, PlayerTD_CharacterSelSkin[playerid][0], 1);
    PlayerTextDrawBoxColor(playerid, PlayerTD_CharacterSelSkin[playerid][0], 0);
    PlayerTextDrawSetShadow(playerid, PlayerTD_CharacterSelSkin[playerid][0], 0);
    PlayerTextDrawSetOutline(playerid, PlayerTD_CharacterSelSkin[playerid][0], 1);
    PlayerTextDrawBackgroundColor(playerid, PlayerTD_CharacterSelSkin[playerid][0], 255);
    PlayerTextDrawFont(playerid, PlayerTD_CharacterSelSkin[playerid][0], 1);
    PlayerTextDrawSetProportional(playerid, PlayerTD_CharacterSelSkin[playerid][0], 1);
    PlayerTextDrawSetShadow(playerid, PlayerTD_CharacterSelSkin[playerid][0], 0);
    PlayerTextDrawSetSelectable(playerid, PlayerTD_CharacterSelSkin[playerid][0], true);
    
    PlayerTextDrawShow(playerid, PlayerTD_CharacterSelSkin[playerid][0]);
    return 1;
}

stock GlobalTD_CharacterShow(playerid)
{
    for(new i = 0; i < sizeof(GlobalTD_Character); i++)
        TextDrawShowForPlayer(playerid, GlobalTD_Character[i]);
    
    PlayerEditCharacter[playerid] = true;
    return 1;
}

stock GlobalTD_CharacterHide(playerid)
{
    for(new i = 0; i < sizeof(GlobalTD_Character); i++)
        TextDrawHideForPlayer(playerid, GlobalTD_Character[i]);

    PlayerEditCharacter[playerid] = false;
    return 1;
}

stock PlayerTD_CharacterHide(playerid)
{
    PlayerEditCharacter[playerid] = false;
    for(new i = 0; i < 7; i++)
    {
        PlayerTextDrawHide(playerid, PlayerTD_CharacterCreate[playerid][i]);
        PlayerTextDrawDestroy(playerid, PlayerTD_CharacterCreate[playerid][i]);
        PlayerTD_CharacterCreate[playerid][i] = PlayerText:INVALID_PLAYER_TEXT_DRAW;
    }

    return 1;
}

stock GlobalTD_ShowCharacterSelSkin(playerid)
{
    for(new i = 0; i < sizeof(GlobalTD_CharacterSelSkin); i++)
    {
        if(GlobalTD_CharacterSelSkin[i] != Text:INVALID_TEXT_DRAW)
        {
            TextDrawShowForPlayer(playerid, GlobalTD_CharacterSelSkin[i]);
        }
    }

    return 1;
}

stock GlobalTD_HideCharacterSelSkin(playerid)
{
    for(new i = 0; i < sizeof(GlobalTD_CharacterSelSkin); i++)
    {
        if(GlobalTD_CharacterSelSkin[i] != Text:INVALID_TEXT_DRAW)
        {
            TextDrawHideForPlayer(playerid, GlobalTD_CharacterSelSkin[i]);
        }
    }

    return 1;
}

stock PlayerTD_HideCharacterSelSkin(playerid)
{
    PlayerTextDrawHide(playerid, PlayerTD_CharacterSelSkin[playerid][0]);
    PlayerTextDrawDestroy(playerid, PlayerTD_CharacterSelSkin[playerid][0]);
    PlayerTD_CharacterSelSkin[playerid][0] = PlayerText:INVALID_PLAYER_TEXT_DRAW;
    return 1;
}