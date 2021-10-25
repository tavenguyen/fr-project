#define                 MAX_PANELS_ITEM                 15
#define                 MDL_OF_PANELS                   "-2003"

static const Float:FIRST_ITEM_X = 133.801391;
static const Float:FIRST_ITEM_Y = 109.708305;

forward OnPlayerSelectPanel(playerid, pages, itemid);

enum _:e_PLAYER_SELECT_ON_PANEL
{
    on_Select_model = 0,
    on_Select_Next_button,
    on_Select_Previous_button,
    on_Select_Close_button
}

static const Float:itemPositionOffsets[MAX_PANELS_ITEM][] = 
{
    {0.0000,    0.0000},
    {81.0000,   0.0000},
    {162.0000,  0.0000},
    {243.0000,  0.0000},
    {324.0000,  0.0000},
    {0.0000,    83.450134},
    {81.0000,   83.450134},
    {162.0000,  83.450134},
    {243.0000,  83.450134},
    {324.0000,  83.450134},
    {0.0000,    166.900268},
    {81.0000,   166.900268},
    {162.0000,  166.900268},
    {243.0000,  166.900268},
    {324.0000,  166.900268}
};

static enum _:E_PLAYER_PANELS_DATA
{
    bool:p_Panels_usePanels,
    p_Panels_maxPages,
    p_Panels_pages,
    p_Panels_key
}

static
    Player_PanelData[MAX_PLAYERS][E_PLAYER_PANELS_DATA],
    Text:PanelTD_Global[3] = {Text:INVALID_TEXT_DRAW},
    PlayerText:PanelTD_Menu[MAX_PLAYERS][1] = {PlayerText:INVALID_PLAYER_TEXT_DRAW, ...},
    PlayerText:PanelTD_PlayerText[MAX_PLAYERS][MAX_PANELS_ITEM] = {{PlayerText:INVALID_PLAYER_TEXT_DRAW, ...}, ...};

stock ResetPlayerPanelData(playerid)
{
    Player_PanelData[playerid][p_Panels_usePanels] = false;
    Player_PanelData[playerid][p_Panels_maxPages] = 1;
    Player_PanelData[playerid][p_Panels_pages] = 1;
    Player_PanelData[playerid][p_Panels_key] = -1;
    return 1;
}

stock bool:ShowPlayerButtonsPanels(playerid)
{
    if(Player_PanelData[playerid][p_Panels_usePanels] == false)
    {
        Player_PanelData[playerid][p_Panels_usePanels] = true;
    }

    for(new i = 0; i < sizeof(PanelTD_Global); i++)
    {
        if(PanelTD_Global[i] != Text:INVALID_TEXT_DRAW)
        {
            TextDrawShowForPlayer(playerid, PanelTD_Global[i]);
        }
    }

    return true;
}

stock bool:HidePlayerButtonsPanels(playerid)
{
    for(new i = 0; i < sizeof(PanelTD_Global); i++)
    {
        if(PanelTD_Global[i] != Text:INVALID_TEXT_DRAW)
        {
            TextDrawHideForPlayer(playerid, PanelTD_Global[i]);
        }
    }

    Player_PanelData[playerid][p_Panels_usePanels] = false;
    return true;
}

stock bool:ShowPlayerPanelsFurniture(playerid)
{
    Player_PanelData[playerid][p_Panels_usePanels] = true;
    PlayerTextDrawShow(playerid, PanelTD_Menu[playerid][0]);
    for(new i = 0; i < MAX_PANELS_ITEM; i++)
    {
        if(PanelTD_PlayerText[playerid][i] != PlayerText:INVALID_PLAYER_TEXT_DRAW)
        {
            PlayerTextDrawShow(playerid, PanelTD_PlayerText[playerid][i]);
        }
    }

    return true;
}

stock bool:HidePlayerPanelsFurniture(playerid)
{
    Player_PanelData[playerid][p_Panels_usePanels] = false;
    PlayerTextDrawHide(playerid, PanelTD_Menu[playerid][0]);
    for(new i = 0; i < MAX_PANELS_ITEM; i++)
    {
        if(PanelTD_PlayerText[playerid][i] != PlayerText:INVALID_PLAYER_TEXT_DRAW)
        {
            PlayerTextDrawHide(playerid, PanelTD_PlayerText[playerid][i]);
        }
    }

    return true;
}

stock bool:DestroyPlayerPanelsFurniture(playerid)
{
    for(new i = 0; i < MAX_PANELS_ITEM; i++)
    {
        if(PanelTD_PlayerText[playerid][i] != PlayerText:INVALID_PLAYER_TEXT_DRAW)
        {
            PlayerTextDrawDestroy(playerid, PanelTD_PlayerText[playerid][i]);
            PanelTD_PlayerText[playerid][i] = PlayerText:INVALID_PLAYER_TEXT_DRAW;
        }
    }

    PlayerTextDrawDestroy(playerid, PanelTD_Menu[playerid][0]);
    PanelTD_Menu[playerid][0] = PlayerText:INVALID_PLAYER_TEXT_DRAW;
    return true;
}

stock bool:ShowPanelForPlayer(playerid, const items[], max_items = MAX_PANELS_ITEM, key)
{
    if(max_items == 0)
    {
        return false;
    }
    
    if(PanelTD_Menu[playerid][0] == PlayerText:INVALID_PLAYER_TEXT_DRAW)
    {
        PanelTD_Menu[playerid][0] = CreatePlayerTextDraw(playerid, 113.000000, 69.250007, "mdl"MDL_OF_PANELS":Furniture");
        PlayerTextDrawLetterSize(playerid, PanelTD_Menu[playerid][0], 0.000000, 0.000000);
        PlayerTextDrawTextSize(playerid, PanelTD_Menu[playerid][0], 439.000000, 306.000000);
        PlayerTextDrawAlignment(playerid, PanelTD_Menu[playerid][0], 1);
        PlayerTextDrawColor(playerid, PanelTD_Menu[playerid][0], -1);
        PlayerTextDrawSetShadow(playerid, PanelTD_Menu[playerid][0], 0);
        PlayerTextDrawSetOutline(playerid, PanelTD_Menu[playerid][0], 0);
        PlayerTextDrawBackgroundColor(playerid, PanelTD_Menu[playerid][0], 255);
        PlayerTextDrawFont(playerid, PanelTD_Menu[playerid][0], 4);
        PlayerTextDrawSetProportional(playerid, PanelTD_Menu[playerid][0], 0);
        PlayerTextDrawSetShadow(playerid, PanelTD_Menu[playerid][0], 0);
    }

    Player_PanelData[playerid][p_Panels_key] = key;
    Player_PanelData[playerid][p_Panels_maxPages] = 1;
    new max_Items_debug = max_items;
    for(new i = 0; i < max_Items_debug; i++)
    {
        if(i < MAX_PANELS_ITEM)
        {
            if(PanelTD_PlayerText[playerid][i] == PlayerText:INVALID_PLAYER_TEXT_DRAW)
            {
                PanelTD_PlayerText[playerid][i] = CreatePlayerTextDraw(playerid, FIRST_ITEM_X + itemPositionOffsets[i][0], FIRST_ITEM_Y + itemPositionOffsets[i][1], "Item Position Offsets");
                PlayerTextDrawLetterSize(playerid, PanelTD_PlayerText[playerid][i], 0.000000, 0.000000);
                PlayerTextDrawTextSize(playerid, PanelTD_PlayerText[playerid][i], 56.000000, 57.000000);
                PlayerTextDrawAlignment(playerid, PanelTD_PlayerText[playerid][i], 1);
                PlayerTextDrawColor(playerid, PanelTD_PlayerText[playerid][i], -1);
                PlayerTextDrawSetShadow(playerid, PanelTD_PlayerText[playerid][i], 0);
                PlayerTextDrawSetOutline(playerid, PanelTD_PlayerText[playerid][i], 0);
                PlayerTextDrawBackgroundColor(playerid, PanelTD_PlayerText[playerid][i], 808464373);
                PlayerTextDrawFont(playerid, PanelTD_PlayerText[playerid][i], 5);
                PlayerTextDrawSetProportional(playerid, PanelTD_PlayerText[playerid][i], 0);
                PlayerTextDrawSetShadow(playerid, PanelTD_PlayerText[playerid][i], 0);
                PlayerTextDrawSetSelectable(playerid, PanelTD_PlayerText[playerid][i], true);
                PlayerTextDrawSetPreviewModel(playerid, PanelTD_PlayerText[playerid][i], items[i]);
                PlayerTextDrawSetPreviewRot(playerid, PanelTD_PlayerText[playerid][i], 0.000000, 0.000000, 0.000000, 1.000000);
            }
        }
        else break;
    }

    ShowPlayerPanelsFurniture(playerid);
    ShowPlayerButtonsPanels(playerid);

    if(max_Items_debug > MAX_PANELS_ITEM)
    {
        Player_PanelData[playerid][p_Panels_maxPages] = (max_Items_debug/MAX_PANELS_ITEM) + 1;
    }

    return true;
}

stock bool:Panel_UpdatePage(playerid, const items[], const max_items, const page)
{
    HidePlayerButtonsPanels(playerid);
    HidePlayerPanelsFurniture(playerid);

    Player_PanelData[playerid][p_Panels_pages] = page;
    PlayerTextDrawShow(playerid, PanelTD_Menu[playerid][0]);
    for(new i = 0; i < max_items; i++)
    {
        if(i < MAX_PANELS_ITEM)
        {
            if(PanelTD_PlayerText[playerid][i] == PlayerText:INVALID_PLAYER_TEXT_DRAW)
            {
                PanelTD_PlayerText[playerid][i] = CreatePlayerTextDraw(playerid, FIRST_ITEM_X + itemPositionOffsets[i][0], FIRST_ITEM_Y + itemPositionOffsets[i][1], "Item Position Offsets");
                PlayerTextDrawLetterSize(playerid, PanelTD_PlayerText[playerid][i], 0.000000, 0.000000);
                PlayerTextDrawTextSize(playerid, PanelTD_PlayerText[playerid][i], 56.000000, 57.000000);
                PlayerTextDrawAlignment(playerid, PanelTD_PlayerText[playerid][i], 1);
                PlayerTextDrawColor(playerid, PanelTD_PlayerText[playerid][i], -1);
                PlayerTextDrawSetShadow(playerid, PanelTD_PlayerText[playerid][i], 0);
                PlayerTextDrawSetOutline(playerid, PanelTD_PlayerText[playerid][i], 0);
                PlayerTextDrawBackgroundColor(playerid, PanelTD_PlayerText[playerid][i], 808464373);
                PlayerTextDrawFont(playerid, PanelTD_PlayerText[playerid][i], 5);
                PlayerTextDrawSetProportional(playerid, PanelTD_PlayerText[playerid][i], 0);
                PlayerTextDrawSetShadow(playerid, PanelTD_PlayerText[playerid][i], 0);
                PlayerTextDrawSetSelectable(playerid, PanelTD_PlayerText[playerid][i], true);
                PlayerTextDrawSetPreviewModel(playerid, PanelTD_PlayerText[playerid][i], items[i]);
                PlayerTextDrawSetPreviewRot(playerid, PanelTD_PlayerText[playerid][i], 0.000000, 0.000000, 0.000000, 1.000000);

            }
            else
            {
                PlayerTextDrawSetPreviewModel(playerid, PanelTD_PlayerText[playerid][i], items[i]);
            }

            PlayerTextDrawShow(playerid, PanelTD_PlayerText[playerid][i]);
        }
        else
        {
            break;
        }
    }

    ShowPlayerButtonsPanels(playerid);
    return true;
}

stock CreatePanelsNext_PreviousPage()
{
    PanelTD_Global[0] = TextDrawCreate(506.500000, 345.166656, "Previous Page");
    TextDrawLetterSize(PanelTD_Global[0], 0.000000, 1.300004);
    TextDrawTextSize(PanelTD_Global[0], 5.000000, 14.000000);
    TextDrawAlignment(PanelTD_Global[0], 2);
    TextDrawColor(PanelTD_Global[0], -1);
    TextDrawUseBox(PanelTD_Global[0], 1);
    TextDrawBoxColor(PanelTD_Global[0], 0);
    TextDrawSetShadow(PanelTD_Global[0], 0);
    TextDrawSetOutline(PanelTD_Global[0], 0);
    TextDrawBackgroundColor(PanelTD_Global[0], 255);
    TextDrawFont(PanelTD_Global[0], 1);
    TextDrawSetProportional(PanelTD_Global[0], 1);
    TextDrawSetShadow(PanelTD_Global[0], 0);
    TextDrawSetSelectable(PanelTD_Global[0], true);

    PanelTD_Global[1] = TextDrawCreate(528.500000, 345.166595, "Next page");
    TextDrawLetterSize(PanelTD_Global[1], 0.000000, 1.300004);
    TextDrawTextSize(PanelTD_Global[1], 5.000000, 14.000000);
    TextDrawAlignment(PanelTD_Global[1], 2);
    TextDrawColor(PanelTD_Global[1], -1);
    TextDrawUseBox(PanelTD_Global[1], 1);
    TextDrawBoxColor(PanelTD_Global[1], 0);
    TextDrawSetShadow(PanelTD_Global[1], 0);
    TextDrawSetOutline(PanelTD_Global[1], 0);
    TextDrawBackgroundColor(PanelTD_Global[1], 255);
    TextDrawFont(PanelTD_Global[1], 1);
    TextDrawSetProportional(PanelTD_Global[1], 1);
    TextDrawSetShadow(PanelTD_Global[1], 0);
    TextDrawSetSelectable(PanelTD_Global[1], true);

    PanelTD_Global[2] = TextDrawCreate(534.500000, 79.849845, "Close button");
    TextDrawLetterSize(PanelTD_Global[2], 0.000000, 1.200003);
    TextDrawTextSize(PanelTD_Global[2], 5.000000, 14.000000);
    TextDrawAlignment(PanelTD_Global[2], 2);
    TextDrawColor(PanelTD_Global[2], -1);
    TextDrawUseBox(PanelTD_Global[2], 1);
    TextDrawBoxColor(PanelTD_Global[2], 0);
    TextDrawSetShadow(PanelTD_Global[2], 0);
    TextDrawSetOutline(PanelTD_Global[2], 0);
    TextDrawBackgroundColor(PanelTD_Global[2], 255);
    TextDrawFont(PanelTD_Global[2], 1);
    TextDrawSetProportional(PanelTD_Global[2], 1);
    TextDrawSetShadow(PanelTD_Global[2], 0);
    TextDrawSetSelectable(PanelTD_Global[2], true);
    return 1;
}

stock bool:IsPlayerUsingPanel(playerid)
{
    if(Player_PanelData[playerid][p_Panels_usePanels] == true)
    {
        return true;
    }

    return false;
}

stock GetPlayerPanelKey(playerid)
{
    return Player_PanelData[playerid][p_Panels_key];
}

stock GetPlayerPanelPages(playerid)
{
    return Player_PanelData[playerid][p_Panels_pages];
}

stock GetPlayerPanelMaxPages(playerid)
{
    return Player_PanelData[playerid][p_Panels_maxPages];
}

#include <YSI_Coding\y_hooks>
hook OnGameModeInit()
{
    for(new i = 0; i < MAX_PLAYERS; i+=1)
    {
        ResetPlayerPanelData(i);
    }

    CreatePanelsNext_PreviousPage();
    return 1;
}

hook OnPlayerClickTextDraw(playerid, Text:clickedid)
{
    if(IsPlayerUsingPanel(playerid) == true)
    {
        if(clickedid == Text:INVALID_TEXT_DRAW)
        {
            ResetPlayerPanelData(playerid);
            HidePlayerButtonsPanels(playerid);
            HidePlayerPanelsFurniture(playerid);
            DestroyPlayerPanelsFurniture(playerid);
            return 1;
        }

        // Previous page
        if(clickedid == PanelTD_Global[0])
        {
            if(GetPlayerPanelPages(playerid) == 1)
            {
                SendClientMessage(playerid, -1, "Ban khong the tro ve duoc nua.");
                return 1;
            }

            CallLocalFunction("OnPlayerSelectPanel", "iiii", playerid, Player_PanelData[playerid][p_Panels_pages], on_Select_Previous_button, 0);
        }

        // Next page
        if(clickedid == PanelTD_Global[1])
        {
            if(GetPlayerPanelMaxPages(playerid) == 1 || GetPlayerPanelMaxPages(playerid) == GetPlayerPanelPages(playerid))
            {
                SendClientMessage(playerid, -1, "Ban khong the qua trang duoc nua.");
                return 1;
            }

            CallLocalFunction("OnPlayerSelectPanel", "iiii", playerid, Player_PanelData[playerid][p_Panels_pages], on_Select_Next_button, 0);
        }

        // Close button
        if(clickedid == PanelTD_Global[2])
        {
            ResetPlayerPanelData(playerid);
            HidePlayerButtonsPanels(playerid);
            HidePlayerPanelsFurniture(playerid);
            DestroyPlayerPanelsFurniture(playerid);
            CallLocalFunction("OnPlayerSelectPanel", "iiii", playerid, Player_PanelData[playerid][p_Panels_pages], on_Select_Close_button, 0);
            return 1;
        }
    }

    return 1;
}

hook OnPlayerClickPlayerTD(playerid, PlayerText:playertextid)
{
    if(IsPlayerUsingPanel(playerid) == true)
    {
        for(new i = 0; i < sizeof(PanelTD_PlayerText); i++)
        {
            if(playertextid == PanelTD_PlayerText[playerid][i])
            {
                new index_test = ((GetPlayerPanelPages(playerid) - 1) * MAX_PANELS_ITEM) + i;
                CallLocalFunction("OnPlayerSelectPanel", "iiii", playerid, Player_PanelData[playerid][p_Panels_pages], on_Select_model, index_test);                     
            }
        }
    }   

    return 1;
}