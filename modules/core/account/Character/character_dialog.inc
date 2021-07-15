/*--- Project was created on 12:54 - 7/7/2021---*/
//    Founder: Halosetoe                       //
//    Leader Scripter: Halosetoe              //
//    Scripter: Halosetoe                    //
//    Game Content: Halosetoe               //
/*--------- Freedom Roleplay v0.1 ---------*/


Dialog:DIALOG_CHAR_NAME_INPUT(playerid, response, listitem, const inputtext[])
{
    if(response)
    {
        if(IsRoleplayName(inputtext))
        {
            PlayerTextDrawHide(playerid, PlayerTD_CharacterCreate[playerid][0]);
            PlayerTextDrawSetString(playerid, PlayerTD_CharacterCreate[playerid][0], inputtext);
            PlayerTextDrawShow(playerid, PlayerTD_CharacterCreate[playerid][0]);

            format(CharacterCreate_Name[playerid], sizeof(CharacterCreate_Name), "%s", inputtext);
            return 1;
        }
        else Msg(playerid, MSG_PREFIX_ERROR, "Ten nay khong phu hop voi may chu, vui long thu lai.");
    }

    return 0;
}

Dialog:DIALOG_CHAR_BORN_DAY(playerid, response, listitem, const inputtext[])
{
    if(response)
    {
        new day = strval(inputtext);
        new bool:isLunarMonth = false;

        if(day > 0 && day < 32)
        {
            if(day == 31)
            {
                for(new i = 0; i < sizeof(lunarMonth); i++)
                {
                    if(CharacterCreate_Month[playerid] == lunarMonth[i])
                    {
                        isLunarMonth = true;
                        break;
                    }
                }

                if(isLunarMonth == false)
                {
                    return Msg(playerid, MSG_PREFIX_ERROR, "Ngay nay khong co trong thang ma ban chon, hay thuc hien lai.");
                }
            }

            if(CharacterCreate_Month[playerid] == 2)
            {
                if(day == 29)
                {
                    if(!IsLunarYear(CharacterCreate_Year[playerid]))
                    {
                        return Msg(playerid, MSG_PREFIX_ERROR, "Nam ma ban chon khong phai la nam nhuan, nen khong co ngay 29 vao thang 2");
                    }
                }
            }

            CharacterCreate_Day[playerid] = day;
            Msg(playerid, MSG_PREFIX_SUCCESS, "Ban da lua chon ngay thanh cong!");

            new string[10];

            if(day < 10) format(string, sizeof(string), "0%d", CharacterCreate_Day[playerid]);
            if(day >= 10) format(string, sizeof(string), "%d", CharacterCreate_Day[playerid]);

            PlayerTextDrawHide(playerid, PlayerTD_CharacterCreate[playerid][2]);
            PlayerTextDrawSetString(playerid, PlayerTD_CharacterCreate[playerid][2], string);
            PlayerTextDrawShow(playerid, PlayerTD_CharacterCreate[playerid][2]);
        }
        else Msg(playerid, MSG_PREFIX_ERROR, "Ngay sinh khong phu hop, vui long thu lai.");
    }
    return 0;
}

Dialog:DIALOG_CHAR_BORN_MONTH(playerid, response, listitem, const inputtext[])
{
    if(response)
    {
        new month = strval(inputtext);
        if(month > 0 && month < 13)
        {
            CharacterCreate_Month[playerid] = month;
            
            new string[10];
            if(month < 10) format(string, sizeof(string), "0%d", month);
            if(month >= 10) format(string, sizeof(string), "%d", month);

            PlayerTextDrawHide(playerid, PlayerTD_CharacterCreate[playerid][3]);
            PlayerTextDrawSetString(playerid, PlayerTD_CharacterCreate[playerid][3], string);
            PlayerTextDrawShow(playerid, PlayerTD_CharacterCreate[playerid][3]);
            
            Msg(playerid, MSG_PREFIX_SUCCESS, "Ban da nhap thanh cong thang sinh cua ban.");
        }
        else Msg(playerid, MSG_PREFIX_ERROR, "Thang sinh cua ban khong hop le, vui long thu lai.");
    }

    return 0;
}

Dialog:DIALOG_CHAR_BORN_YEAR(playerid, response, listitem, const inputtext[])
{
    if(response)
    {
        new year = strval(inputtext);
        if(year >= MIN_CHARACTER_YEAR && year <= MAX_CHARACTER_YEAR - 15)
        {
            CharacterCreate_Year[playerid] = year;

            new string[128];
            format(string, sizeof(string), "%d", year);

            PlayerTextDrawHide(playerid, PlayerTD_CharacterCreate[playerid][4]);
            PlayerTextDrawSetString(playerid, PlayerTD_CharacterCreate[playerid][4], string);
            PlayerTextDrawShow(playerid, PlayerTD_CharacterCreate[playerid][4]);

            format(string, sizeof(string), "Ban da nhap thanh cong nam sinh cua ban, tinh den hien tai ban dang %d tuoi", MAX_CHARACTER_YEAR - year);
            Msg(playerid, MSG_PREFIX_SUCCESS, string);
        }
        else Msg(playerid, MSG_PREFIX_ERROR, "So tuoi khong hop le hoac ban khong the nhap vai so tuoi nho hon 15");
    }

    return 0;
}

Dialog:DIALOG_CHAR_GENDER(playerid, response, listitem, const inputtext[])
{
    if(response)
    {
        switch(listitem)
        {
            // Male
            case 0:
            {
                CharacterCreate_Gender[playerid] = genderMale;

                new string[100];
                format(string, sizeof(string), "Male");
               
                PlayerTextDrawHide(playerid, PlayerTD_CharacterCreate[playerid][5]);
                PlayerTextDrawSetString(playerid, PlayerTD_CharacterCreate[playerid][5], string);
                PlayerTextDrawShow(playerid, PlayerTD_CharacterCreate[playerid][5]);

                format(string, sizeof(string), "Ban vua chon gioi tinh Nam.");
                Msg(playerid, MSG_PREFIX_SUCCESS, string);
                return 1;
            }
            // Female
            case 1:
            {
                CharacterCreate_Gender[playerid] = genderFemale;

                new string[100];
                format(string, sizeof(string), "Female");
               
                PlayerTextDrawHide(playerid, PlayerTD_CharacterCreate[playerid][5]);
                PlayerTextDrawSetString(playerid, PlayerTD_CharacterCreate[playerid][5], string);
                PlayerTextDrawShow(playerid, PlayerTD_CharacterCreate[playerid][5]);

                format(string, sizeof(string), "Ban vua chon gioi tinh Nu.");
                Msg(playerid, MSG_PREFIX_SUCCESS, string);
                return 1;
            }
        }
    }

    return 0;
}

Dialog:DIALOG_CHAR_SKIN_COLOR(playerid, response, listitem, const inputtext[])
{
    if(response)
    {
        switch(listitem)
        {
            // White
            case 0:
            {
                CharacterCreate_SkinColor[playerid] = skinColor_white;

                new string[100];
                format(string, sizeof(string), "Oropeoit");

                PlayerTextDrawHide(playerid, PlayerTD_CharacterCreate[playerid][6]);
                PlayerTextDrawSetString(playerid, PlayerTD_CharacterCreate[playerid][6], string);
                PlayerTextDrawShow(playerid, PlayerTD_CharacterCreate[playerid][6]);

                format(string, sizeof(string), "Ban vua chon nguoi da trang.");
                Msg(playerid, MSG_PREFIX_SUCCESS, string);
                return 1;
            }
            case 1:
            {
                CharacterCreate_SkinColor[playerid] = skinColor_yellow;

                new string[100];
                format(string, sizeof(string), "Mongoloit");

                PlayerTextDrawHide(playerid, PlayerTD_CharacterCreate[playerid][6]);
                PlayerTextDrawSetString(playerid, PlayerTD_CharacterCreate[playerid][6], string);
                PlayerTextDrawShow(playerid, PlayerTD_CharacterCreate[playerid][6]);

                format(string, sizeof(string), "Ban vua chon nguoi da vang.");
                Msg(playerid, MSG_PREFIX_SUCCESS, string);
                return 1;
            }
            case 2:
            {
                CharacterCreate_SkinColor[playerid] = skinColor_black;

                new string[100];
                format(string, sizeof(string), "Negroit");

                PlayerTextDrawHide(playerid, PlayerTD_CharacterCreate[playerid][6]);
                PlayerTextDrawSetString(playerid, PlayerTD_CharacterCreate[playerid][6], string);
                PlayerTextDrawShow(playerid, PlayerTD_CharacterCreate[playerid][6]);

                format(string, sizeof(string), "Ban vua chon nguoi da den.");
                Msg(playerid, MSG_PREFIX_SUCCESS, string);
            }
        }
    }

    return 0;
}

Dialog:DIALOG_CHAR_SELECT_SKIN(playerid, response, listitem, const inputtext[])
{
    if(response)
    {
        new skinid = strval(inputtext);
        if(skinid > 0 && skinid < 313)
        {
            CharacterCreate_Skin[playerid] = strval(inputtext);
            SetPlayerSkin(playerid, skinid);
            
            new string[10];
            if(skinid < 10) format(string, sizeof(string), "00%d", skinid);
            if(skinid >= 10 && skinid < 100) format(string, sizeof(string), "0%d", skinid);
            if(skinid >= 100) format(string, sizeof(string), "%d", skinid);

            PlayerTextDrawHide(playerid, PlayerTD_CharacterSelSkin[playerid][0]);
            PlayerTextDrawSetString(playerid, PlayerTD_CharacterSelSkin[playerid][0], string);
            PlayerTextDrawShow(playerid, PlayerTD_CharacterSelSkin[playerid][0]);
            
            Msg(playerid, MSG_PREFIX_SUCCESS, "Ban da nhap thanh cong Skin id.");
            return 1;
        }
        else Msg(playerid, MSG_PREFIX_ERROR, "Skin id nay khong hop le, vui long thu lai.");
    }

    return 0;
}