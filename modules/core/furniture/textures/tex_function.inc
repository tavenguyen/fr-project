#define                         MAX_TEXTURES_FURNITURE                          9064
#define                         MAX_LINES_IN_FURNITURE_TEXTURE                  30
#define                         FURNITURE_TEXTURE_SERVER_NAME                   "SAG:MP"

//#include <PawnPlus>
//#include <async-dialogs>

ShowPlayerFurnitureTextureList(playerid)
{
    new str[1048 + 1048 + 40], index = 0;
    new List:l_storedUseColor = list_new();

    maindialog:
    if(!list_valid(l_storedUseColor))
    {
        l_storedUseColor = list_new();
    }

    format(str, sizeof(str), "Index\tTexture Index\tTXD Name\t\tTexture Name\n");
    for(new i = index*(MAX_LINES_IN_FURNITURE_TEXTURE + 1); i < sizeof(FurnitureTexture); i++)
    {
        new bool:usecolor = false, value_id;
        for(new Iter:index_iter = list_iter(l_storedUseColor); iter_inside(index_iter); iter_move_next(index_iter))
        {
            if(iter_get(index_iter, value_id) == i)
            {
                usecolor = true;
                iter_erase_deep(index_iter);
                break;
            }
        }

        format(str, sizeof(str), "%s%s%d\t%s%d\t%s%s\t\t%s%s\n", str, (usecolor == true) ? "{FF0000}" : "", i, (usecolor == true) ? "{FF0000}" : "", FurnitureTexture[i][fT_index], (usecolor == true) ? "{FF0000}" : "", FurnitureTexture[i][fT_txdName], (usecolor == true) ? "{FF0000}" : "", FurnitureTexture[i][fT_textureName]);
    
        if((i - index) % MAX_LINES_IN_FURNITURE_TEXTURE == 0 && (i - index) != index*MAX_LINES_IN_FURNITURE_TEXTURE)
        {
            format(str, sizeof(str), "%s>> Nhan vao day de di den trang ke tiep\n>> Nhan vao day de tro ve trang phia truoc\n>> Nhan vao day de tim kiem\n>> Nhan vao day de di den trang ma ban muon.", str);
            break;
        }
    }

    new string[33 + 50];
    format(string, sizeof(string), "Texture List - Furniture "FURNITURE_TEXTURE_SERVER_NAME" | Pages: %d", index);

    new response_main[e_DIALOG_RESPONSE_INFO];
    await_arr(response_main) ShowPlayerAsyncDialog(playerid, DIALOG_STYLE_TABLIST, string, str, "<<" , ">>");
    if(response_main[E_DIALOG_RESPONSE_Response])
    {
        // Next page
        if(response_main[E_DIALOG_RESPONSE_Listitem] == MAX_LINES_IN_FURNITURE_TEXTURE + 2)
        {
            if(index * (MAX_LINES_IN_FURNITURE_TEXTURE + 1) > MAX_TEXTURES_FURNITURE)
            {
                Msg(playerid, MSG_PREFIX_ERROR, "Khong the qua trang duoc nua.");
                goto maindialog;
                return 0; 
            }

            index++;
            goto maindialog;
            return 1;
        }

        // Back page
        if(response_main[E_DIALOG_RESPONSE_Listitem] == MAX_LINES_IN_FURNITURE_TEXTURE + 3)
        {
            if(index == 0)
            {
                Msg(playerid, MSG_PREFIX_ERROR, "Khong the tro ve duoc nua.");
                goto maindialog;
                return 0;
            }

            index--;
            goto maindialog;
            return 1;
        }

        // Find index, txd, texture
        if(response_main[E_DIALOG_RESPONSE_Listitem] == MAX_LINES_IN_FURNITURE_TEXTURE + 4)
        {
            find_main:
            new response_main_find[e_DIALOG_RESPONSE_INFO];
            await_arr(response_main_find) ShowPlayerAsyncDialog(playerid, DIALOG_STYLE_LIST, "Find System - Furniture "FURNITURE_TEXTURE_SERVER_NAME" | Index & TXD Name & Texture Name", "Index\nTXD Name\nTexture Name", "<<", ">>");
            if(response_main_find[E_DIALOG_RESPONSE_Response])
            {
                switch(response_main_find[E_DIALOG_RESPONSE_Listitem])
                {
                    // Index
                    case 0:
                    {
                        new response_main_find_inputIndex[e_DIALOG_RESPONSE_INFO];
                        await_arr(response_main_find_inputIndex) ShowPlayerAsyncDialog(playerid, DIALOG_STYLE_INPUT, "Find Index - Furniture "FURNITURE_TEXTURE_SERVER_NAME"", "Ban hay nhap vao day Index de tim", "Accept", "Cancel");
                        if(response_main_find_inputIndex[E_DIALOG_RESPONSE_Response])
                        {
                            new input_idx = strval(response_main_find_inputIndex[E_DIALOG_RESPONSE_InputText]);
                            if(input_idx < 0 || input_idx > MAX_TEXTURES_FURNITURE)
                            {
                                SendClientMessage(playerid, -1, "Index khong hop le.");
                                goto find_main;
                            }

                            index = 0;
                            for(new i = 0; i < sizeof(FurnitureTexture); i++)
                            {
                                if(i == input_idx)
                                {
                                    list_add(l_storedUseColor, i);
                                    SendClientMessage(playerid, -1, "Ban da tim thanh cong.");
                                    goto maindialog;
                                }

                                if((i - index) % MAX_LINES_IN_FURNITURE_TEXTURE == 0 && (i - index) != index*MAX_LINES_IN_FURNITURE_TEXTURE)
                                {
                                    index++;
                                }
                            }
                        }
                    }

                    // TXD Name
                    case 1:
                    {
                        new response_main_find_inputTXD[e_DIALOG_RESPONSE_INFO];
                        await_arr(response_main_find_inputTXD) ShowPlayerAsyncDialog(playerid, DIALOG_STYLE_INPUT, "Find TXD Name - Furniture "FURNITURE_TEXTURE_SERVER_NAME"", "Ban hay nhap vao day TXD Name de tim", "Accept", "Cancel");
                        if(response_main_find_inputTXD[E_DIALOG_RESPONSE_Response])
                        {
                            if(isnull(response_main_find_inputTXD[E_DIALOG_RESPONSE_InputText]))
                            {
                                SendClientMessage(playerid, -1, "Khong hop le, vui long thu lai.");
                                goto find_main;
                            }

                            index = 0;

                            new bool:conditions = false;
                            for(new i = 0; i < sizeof(FurnitureTexture); i++)
                            {
                                if(!strcmp(FurnitureTexture[i][fT_txdName], response_main_find_inputTXD[E_DIALOG_RESPONSE_InputText], false))
                                {
                                    list_add(l_storedUseColor, i);
                                    conditions = true;
                                }
                                else
                                {
                                    if(conditions == true)
                                    {
                                        SendClientMessage(playerid, -1, "Ban da tim thanh cong."); 
                                        goto maindialog;
                                        return 1;
                                    }
                                }

                                if((i - index) % MAX_LINES_IN_FURNITURE_TEXTURE == 0 && (i - index) != index*MAX_LINES_IN_FURNITURE_TEXTURE)
                                {
                                    index++;
                                }
                            }

                            SendClientMessage(playerid, -1, "He thong khong tim thay TXD Name nay trong du lieu, vui long thu lai.");
                            goto find_main;
                        }
                        else goto maindialog;
                    }

                    // Texture Name
                    case 2:
                    {
                        new response_main_find_inputTexture[e_DIALOG_RESPONSE_INFO];
                        await_arr(response_main_find_inputTexture) ShowPlayerAsyncDialog(playerid, DIALOG_STYLE_INPUT, "Find Texture Name - Furniture "FURNITURE_TEXTURE_SERVER_NAME"", "Ban hay nhap vao day TXD Name de tim", "Accept", "Cancel");
                        if(response_main_find_inputTexture[E_DIALOG_RESPONSE_Response])
                        {
                            if(isnull(response_main_find_inputTexture[E_DIALOG_RESPONSE_InputText]))
                            {
                                SendClientMessage(playerid, -1, "Khong hop le, vui long thu lai.");
                                goto find_main;
                            }

                            index = 0;
                            new bool:conditions = false;
                            for(new i = 0; i < sizeof(FurnitureTexture); i++)
                            {
                                if(!strcmp(FurnitureTexture[i][fT_textureName], response_main_find_inputTexture[E_DIALOG_RESPONSE_InputText], false))
                                {
                                    list_add(l_storedUseColor, i);
                                    conditions = true;
                                }
                                else
                                {
                                    if(conditions == true)
                                    {
                                        SendClientMessage(playerid, -1, "Ban da tim thanh cong."); 
                                        goto maindialog;
                                        return 1;
                                    }
                                }

                                if((i - index) % MAX_LINES_IN_FURNITURE_TEXTURE == 0 && (i - index) != index*MAX_LINES_IN_FURNITURE_TEXTURE)
                                {
                                    index++;
                                }
                            }

                            SendClientMessage(playerid, -1, "He thong khong tim thay Texture Name nay trong du lieu, vui long thu lai.");
                            goto find_main;
                        }
                        else goto maindialog;
                    }
                }
            }
            else goto maindialog;
        }

        // Go to the page that you wanted.
        if(response_main[E_DIALOG_RESPONSE_Listitem] == MAX_LINES_IN_FURNITURE_TEXTURE + 5)
        {
            new input_pages[e_DIALOG_RESPONSE_INFO];
            await_arr(input_pages) ShowPlayerAsyncDialog(playerid, DIALOG_STYLE_INPUT, "Input Pages - Furniture "FURNITURE_TEXTURE_SERVER_NAME"", "Hay nhap vao day trang so ma ban muon den", "Accept", "Back");
            if(input_pages[E_DIALOG_RESPONSE_Response])
            {
                new pages = strval(input_pages[E_DIALOG_RESPONSE_InputText]);
                if(pages * (MAX_LINES_IN_FURNITURE_TEXTURE + 1) <= MAX_TEXTURES_FURNITURE)
                {
                    index = pages;
                    list_delete_deep(l_storedUseColor);
                    SendClientMessage(playerid, -1, "Ban da nhap thanh cong.");
                    goto maindialog;
                }
                else
                {
                    SendClientMessage(playerid, -1, "Page nay khong phu hop, vui long thu lai.");
                    goto maindialog;
                }
            }
        }

        // Set material to object
        // Saves object to database
        SendClientMessage(playerid, -1, "Ban da chon thanh cong Texture danh cho Object.");
    }

    return 1;
}