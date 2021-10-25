#if !defined FURNITURE_TEXTURE_SERVER_NAME
    #define  FURNITURE_TEXTURE_SERVER_NAME   "SAG:MP"
#endif

static enum _:E_FURNITURE_DATA
{
    furData_modelid,
    furData_modelName[50]
}

static Map:m_stored_List_furniture;

stock GetFurnitureType(type)
{
    new string2[50];
    switch(type)
    {
        case 0: format(string2, sizeof(string2), "Walls");
        case 1: format(string2, sizeof(string2), "Doors & Windows");
        case 2: format(string2, sizeof(string2), "Clothes");
        case 3: format(string2, sizeof(string2), "Tables & Chairs");
        case 4: format(string2, sizeof(string2), "Bar items");
        case 5: format(string2, sizeof(string2), "Crates, drums and racks");
        case 6: format(string2, sizeof(string2), "Food and drinks");
        case 7: format(string2, sizeof(string2), "Furniture");
        case 8: format(string2, sizeof(string2), "Household Items");
        case 9: format(string2, sizeof(string2), "Lights");
        case 10: format(string2, sizeof(string2), "Plants");
        case 11: format(string2, sizeof(string2), "Shop items");
        case 12: format(string2, sizeof(string2), "Trash");
        case 13: format(string2, sizeof(string2), "Custom objects");
        default: format(string2, sizeof(string2), "Item nay chua co - Invalid type %d", type);
    }   

    return string2;
}

ShowPlayerFurnitureList(playerid)
{
    new str[500];
    for(new index = 0; index < map_size(m_stored_List_furniture); index++)
    {
        format(str, sizeof(str), "%s%s\n", str, GetFurnitureType(index));
    }

    new response_main[e_DIALOG_RESPONSE_INFO];
    await_arr(response_main) ShowPlayerAsyncDialog(playerid, DIALOG_STYLE_TABLIST, "Furniture List - "FURNITURE_TEXTURE_SERVER_NAME"", str, "<<" , ">>");
    if(response_main[E_DIALOG_RESPONSE_Response])   
    {
        new key = response_main[E_DIALOG_RESPONSE_Listitem];
        if(map_has_key(m_stored_List_furniture, key))
        {
            new List:l_stored_Furniture = list_new();
            if(map_get_safe(m_stored_List_furniture, key, l_stored_Furniture))
            {
                new furniture_data[E_FURNITURE_DATA];
                new items[MAX_PANELS_ITEM];

                for(new Iter:index = list_iter(l_stored_Furniture, 0); iter_inside(index); iter_move_next(index))
                {
                    if(iter_get_arr_safe(index, furniture_data))
                    {
                        if(iter_get_key(index) >= MAX_PANELS_ITEM)
                        {
                            break;
                        }

                        items[iter_get_key(index)] = furniture_data[furData_modelid];         
                    }
                }

                ShowPanelForPlayer(playerid, items, list_size(l_stored_Furniture), key);
                SelectTextDraw(playerid, 0xFFFFF00FF);
            }
        }
    }

    return 1;
}

stock LogFurnitureSize(key)
{
    if(map_has_key(m_stored_List_furniture, key))
    {
        new List:l_stored_Furniture = list_new();
        if(map_get_safe(m_stored_List_furniture, key, l_stored_Furniture))
        {
            printf("[debug] List size: %d with key: %d", list_size(l_stored_Furniture), key);
        }
    }

    return 0;
}

forward OnFurnitureLoad();
public OnFurnitureLoad()
{
    new 
        rows = cache_num_rows(),
        type = 0;

    new furniture_data[E_FURNITURE_DATA];
    for(new i = 0; i < rows; i++)
    {
        cache_get_value_int(i, "furnitureType", type);
        cache_get_value_int(i, "furnitureIndex", furniture_data[furData_modelid]);
        cache_get_value_name(i, "furnitureName", furniture_data[furData_modelName]);

        if(map_has_key(m_stored_List_furniture, type))
        {
            new List:l_stored_Furniture = list_new();
            if(map_get_safe(m_stored_List_furniture, type, l_stored_Furniture))
            {
                list_add_arr(l_stored_Furniture, furniture_data);
                map_set(m_stored_List_furniture, type, l_stored_Furniture);
            }
        }
        else
        {
            new List:l_stored_Furniture = list_new();
            list_add_arr(l_stored_Furniture, furniture_data);
            map_set(m_stored_List_furniture, type, l_stored_Furniture);
        }
    }

    return 1;
}

#include <YSI_Coding\y_hooks>
hook OnGameModeInit()
{
    m_stored_List_furniture = map_new();
    mysql_tquery(MySQL_GetHandle(), "SELECT * FROM furniture ORDER BY `furnitureType`, `furnitureIndex`", "OnFurnitureLoad");
    return 1;
}

hook OnPlayerSelectPanel(playerid, pages, itemid, itemModel)
{
    if(IsPlayerUsingPanel(playerid) == true)
    {
        switch(itemid)
        {
            case on_Select_model:
            {
                new key = GetPlayerPanelKey(playerid);
                if(map_has_key(m_stored_List_furniture, key))
                {
                    new List:l_stored_Furniture = list_new();
                    if(map_get_safe(m_stored_List_furniture, key, l_stored_Furniture))
                    {
                        new furniture_data[E_FURNITURE_DATA];
                        new items[MAX_PANELS_ITEM];
                        new count = 0;

                        new page_test = ((GetPlayerPanelPages(playerid) > 1) ? ((GetPlayerPanelPages(playerid) - 1) * MAX_PANELS_ITEM) - MAX_PANELS_ITEM : ((GetPlayerPanelPages(playerid) - 1) * MAX_PANELS_ITEM));
                        for(new Iter:index = list_iter(l_stored_Furniture, page_test); iter_inside(index); iter_move_next(index))
                        {
                            if(iter_get_arr_safe(index, furniture_data))
                            {
                                items[count] = furniture_data[furData_modelid];           

                                if(count >= itemModel)
                                {
                                    break;
                                }

                                count++;
                            }
                        }
                    }
                }
            }

            case on_Select_Previous_button:
            {
                new key = GetPlayerPanelKey(playerid);
                if(map_has_key(m_stored_List_furniture, key))
                {
                    new List:l_stored_Furniture = list_new();
                    if(map_get_safe(m_stored_List_furniture, key, l_stored_Furniture))
                    {
                        new furniture_data[E_FURNITURE_DATA];
                        new items[MAX_PANELS_ITEM];
                        new count = 0;

                        new page_test = ((GetPlayerPanelPages(playerid) - 1) * MAX_PANELS_ITEM) - MAX_PANELS_ITEM;
                        for(new Iter:index = list_iter(l_stored_Furniture, page_test); iter_inside(index); iter_move_next(index))
                        {
                            if(iter_get_arr_safe(index, furniture_data))
                            {
                                items[count] = furniture_data[furData_modelid];           
                                printf("items count: %d - %d | %d | ind: %d", items[count], furniture_data[furData_modelid], count, iter_get_key(index));

                                if(count >= MAX_PANELS_ITEM - 1)
                                {
                                    printf("debug %d | list size: %d", page_test, list_size(l_stored_Furniture));
                                    Panel_UpdatePage(playerid, items, list_size(l_stored_Furniture), GetPlayerPanelPages(playerid) - 1);
                                    break;
                                }

                                count++;
                            }
                        }
                    }
                }
            }

            case on_Select_Next_button:
            {
                new key = GetPlayerPanelKey(playerid);
                if(map_has_key(m_stored_List_furniture, key))
                {
                    new List:l_stored_Furniture = list_new();
                    if(map_get_safe(m_stored_List_furniture, key, l_stored_Furniture))
                    {
                        new furniture_data[E_FURNITURE_DATA];
                        new items[MAX_PANELS_ITEM];
                        new count = 0;

                        new page_debug = ((GetPlayerPanelPages(playerid)) * MAX_PANELS_ITEM);
                        for(new Iter:index = list_iter(l_stored_Furniture, page_debug); iter_inside(index); iter_move_next(index))
                        {
                            if(iter_get_arr_safe(index, furniture_data))
                            {
                                items[count] = furniture_data[furData_modelid];         
                                printf("items count: %d - %d | %d | ind: %d", items[count], furniture_data[furData_modelid], count, iter_get_key(index));
                                
                                if(count >= MAX_PANELS_ITEM - 1 || iter_get_key(index) >= list_size(l_stored_Furniture) - 1)
                                {
                                    printf("debug %d | list size: %d | page: %d - %d", page_debug, list_size(l_stored_Furniture), GetPlayerPanelPages(playerid), GetPlayerPanelMaxPages(playerid));
                                    Panel_UpdatePage(playerid, items, list_size(l_stored_Furniture) - (GetPlayerPanelPages(playerid) * MAX_PANELS_ITEM), GetPlayerPanelPages(playerid) + 1);
                                    break;
                                }

                                count++;
                            }
                        }
                    }
                }
            }

            case on_Select_Close_button:
            {
                SendClientMessage(playerid, -1, "Ban da dong thanh cong Panel.");
            }
        }
    }

    return 1;
}

CMD:test(playerid)
{
    ShowPlayerFurnitureList(playerid);
    return 1;
}

#include <YSI_Coding\y_timers>

new Float:rx_obj, Float:ry_obj, Float:rz_obj;

timer RotationObject[100](objectid)
{
    if(rz_obj == 100.0)
    {
        rz_obj = 0.0;
    }
    
    rz_obj += 2.0;
    SetDynamicObjectRot(objectid, rx_obj, ry_obj, rz_obj);
    SendClientMessageStr(0, -1, str_format("Move: %f", rz_obj));
    return 1;
}

CMD:test2(playerid, params[])
{
    new Float:x, Float:y, Float:z;
    GetPlayerPos(playerid, x, y, z);
    new index = CreateDynamicObject(strval(params), x, y, z, 0.0, 0.0, 0.0, 0, 0);
    rx_obj = 0.0;
    ry_obj = 0.0;
    rz_obj = 0.0;
    repeat RotationObject(index);
    return 1;
}