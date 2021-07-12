//======================================================
//Fade & Flash screen by Michael F

const SCREEN_FLSH_UPDT_VAL = 50;

enum epFdScreen {
    bool:active,
    nextval,
    basecolor,
    inor,
    nextUpd,
    waitFor,
    PlayerText:_tdx
} new pFdScreen[MAX_PLAYERS][epFdScreen];

new ColorPal[] = {0x00000005, 0x00000010, 0x00000015, 0x00000020, 0x00000030, 0x00000035, 0x00000040, 0x00000045, 0x00000050, 0x00000055, 0x00000065, 0x00000070, 0x00000075,
                  0x00000086, 0x00000093, 0x00000098, 0x0000009A, 0x000000AB, 0x000000DF, 0x000000CF, 0x000000FF};

forward ScreenUtilProcessor(playerid);

stock ResetPlayerScreen(playerid)
{
    if(pFdScreen[playerid][_tdx] != 0);
        PlayerTextDrawDestroy(playerid, pFdScreen[playerid][_tdx]), pFdScreen[playerid][_tdx] = PlayerText:INVALID_TEXT_DRAW;
    return 1;
}

stock FadePlayerScreen(playerid, inout, bascl = 0x000000FF, pwaitFor = SCREEN_FLSH_UPDT_VAL)
{
    if(pFdScreen[playerid][active])return 1;

    switch(inout)
    {
        case 0:
        {  
            pFdScreen[playerid][nextval]   = sizeof(ColorPal); //Backwards (black to clear) last index to zero
            pFdScreen[playerid][inor]      = 0;
            pFdScreen[playerid][basecolor] = bascl;
        }
        case 1:
        {
            pFdScreen[playerid][nextval]   = 0; //From zero index to last
            pFdScreen[playerid][inor]      = 1;
            pFdScreen[playerid][basecolor] = bascl;

        }
    }
    pFdScreen[playerid][_tdx] = CreatePlayerTextDraw(playerid,-7.000000, 0.000000, "_");
    PlayerTextDrawBackgroundColor(playerid,pFdScreen[playerid][_tdx], 255);
    PlayerTextDrawFont(playerid,pFdScreen[playerid][_tdx], 1);
    PlayerTextDrawLetterSize(playerid,pFdScreen[playerid][_tdx], 0.500000, 50.399963);
    PlayerTextDrawColor(playerid,pFdScreen[playerid][_tdx], -1);
    PlayerTextDrawSetOutline(playerid,pFdScreen[playerid][_tdx], 0);
    PlayerTextDrawSetProportional(playerid,pFdScreen[playerid][_tdx], 1);
    PlayerTextDrawSetShadow(playerid,pFdScreen[playerid][_tdx], 1);
    PlayerTextDrawUseBox(playerid,pFdScreen[playerid][_tdx], 1);
    PlayerTextDrawBoxColor(playerid,pFdScreen[playerid][_tdx], 0x000000FF);
    PlayerTextDrawTextSize(playerid,pFdScreen[playerid][_tdx], 646.000000, 0.000000);
    PlayerTextDrawSetSelectable(playerid,pFdScreen[playerid][_tdx], 0);
    if(inout == 0)PlayerTextDrawShow(playerid, pFdScreen[playerid][_tdx]);
    SetTimerEx("ScreenUtilProcessor", pwaitFor, false, "i", playerid);
    pFdScreen[playerid][active] = true;
    return 1;
}

public ScreenUtilProcessor(playerid) //Improve with fixes2 if needed
{
    if(!IsPlayerConnected(playerid))return 1;
    if(pFdScreen[playerid][active])
    {
        switch(pFdScreen[playerid][inor])
        {
            case 0:
            {
                if(pFdScreen[playerid][nextval] == 0)
                {
                    PlayerTextDrawDestroy(playerid, pFdScreen[playerid][_tdx]);
                    pFdScreen[playerid][_tdx] = PlayerText:INVALID_TEXT_DRAW;
                    return pFdScreen[playerid][active] = false;
                }
                pFdScreen[playerid][nextval] --;
            }

            case 1:
            {
                if(pFdScreen[playerid][nextval] == sizeof(ColorPal)-1)
                {
                    pFdScreen[playerid][_tdx] = PlayerText:INVALID_TEXT_DRAW;
                    return pFdScreen[playerid][active] = false;
                }
                pFdScreen[playerid][nextval] ++;
            }

        }
        PlayerTextDrawBoxColor(playerid, pFdScreen[playerid][_tdx], ColorPal[pFdScreen[playerid][nextval]]);
        PlayerTextDrawHide(playerid, pFdScreen[playerid][_tdx]);
        PlayerTextDrawShow(playerid, pFdScreen[playerid][_tdx]);
        SetTimerEx("ScreenUtilProcessor", SCREEN_FLSH_UPDT_VAL, false, "i", playerid);
    }
    return 1;
}

//======================================================