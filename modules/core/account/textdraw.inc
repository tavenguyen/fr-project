new 
    Text:GlobalTD_Character[3] = Text:INVALID_TEXT_DRAW,
    PlayerText:PlayerTD_CharacterCreate[MAX_PLAYERS][7] = { {PlayerText:INVALID_PLAYER_TEXT_DRAW}, ... };

new bool:PlayerEditCharacter[MAX_PLAYERS] = false;

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

    GlobalTD_Character[2] = TextDrawCreate(546.398803, 171.517135, "/");
    TextDrawLetterSize(GlobalTD_Character[2], 0.214999, 1.407501);
    TextDrawAlignment(GlobalTD_Character[2], 2);
    TextDrawColor(GlobalTD_Character[2], 255);
    TextDrawSetShadow(GlobalTD_Character[2], 0);
    TextDrawSetOutline(GlobalTD_Character[2], 0);
    TextDrawBackgroundColor(GlobalTD_Character[2], 255);
    TextDrawFont(GlobalTD_Character[2], 1);
    TextDrawSetProportional(GlobalTD_Character[2], 1);
    TextDrawSetShadow(GlobalTD_Character[2], 0);
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

    PlayerTD_CharacterCreate[playerid][3] = CreatePlayerTextDraw(playerid, 541.200073, 172.517196, "11");
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

    format(string, sizeof(string), "%d", CharacterCreate_Day[playerid]);
    PlayerTextDrawSetString(playerid, PlayerTD_CharacterCreate[playerid][2], string);

    format(string, sizeof(string), "%d", CharacterCreate_Month[playerid]);
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