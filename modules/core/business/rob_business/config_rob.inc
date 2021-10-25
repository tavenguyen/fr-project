#include <YSI_Coding\y_timers>

const E_STREAMER_EXTRA_ROBBERY_ID = 'r' + 'o' + 'b' + 'b' + 'e' + 'r' + 'y'; // 114 + 111 + 98 + 98 + 101 + 114 + 121 = 757 

static enum _:E_BUSINESS_POINT_ROBBERY_DATA
{
    business_robberyIndex,
    business_robberyUUID[UUID_LEN],
    business_pointRobbery_cpID,
    Float:business_pointRobberry_X,
    Float:business_pointRobberry_Y,
    Float:business_pointRobberry_Z,
    business_pointRobbery_int,
    business_pointRobbery_vw,
    businessRobbery_moneyMax,
    businessRobbery_moneyMin,
    businessRobbery_timingCountdown,
    bool:businessRobbery_Alaram,
    bool:businessRobbery_AcpToRob,
    businessRobbery_randAmount
}

static enum _:E_BUSINESS_POINT_TIME_UNIX_DATA
{
    e_business_timeUnix_uuid[UUID_LEN],
    e_business_timeUnix_time
}

// Value is array and key is business index.
new 
    Map:m_storedPlayer_editRob,
    Map:m_business_Robbery,
    Map:m_stored_pRobBusiness,
    Map:m_stored_pTimerRob,
    Map:m_timeUnix_Business_after_rob;

static
    Timer:timer_unix_robbery = Timer:0,
    Timer:timer_robbery;

stock BusinessRob_PointCreate(businessid, amount_point)
{
    if(map_has_key(m_business_Robbery, businessid))
    {
        return false;
    }

    new
        business_point_robbery[E_BUSINESS_POINT_ROBBERY_DATA],
        List:l_business_Robbery_PointRob = list_new();

    for(new loop_amount_point = 0; loop_amount_point < amount_point; loop_amount_point += 1)
    {
        business_point_robbery[business_robberyIndex] = businessid;
        UUID(business_point_robbery[business_robberyUUID], UUID_LEN);
        business_point_robbery[business_pointRobbery_cpID] = -1;
        business_point_robbery[business_pointRobberry_X] = 0.0;
        business_point_robbery[business_pointRobberry_Y] = 0.0;
        business_point_robbery[business_pointRobberry_Z] = 0.0;
        business_point_robbery[business_pointRobbery_int] = 0;
        business_point_robbery[business_pointRobbery_vw] = 0;
        business_point_robbery[businessRobbery_moneyMin] = 0;
        business_point_robbery[businessRobbery_moneyMax] = 1;
        business_point_robbery[businessRobbery_timingCountdown] = 0;
        business_point_robbery[businessRobbery_AcpToRob] = false;
        business_point_robbery[businessRobbery_randAmount] = Random(1, 10); 

        new index = list_add_arr(l_business_Robbery_PointRob, business_point_robbery);
        printf("[debug] index %d was created in business %d", index, businessid);

        new query[99 + 60];
        mysql_format(MySQL_GetHandle(), query, sizeof(query), "INSERT INTO `business_robbery_point` VALUES (%d, '%e', %.4f, %.4f, %.4f, %d, %d, %d, %d, %d, %d, %d, %d, %d)", businessid, business_point_robbery[business_robberyUUID], 0.0, 0.0, 0.0, 0, 0, 1, 0, 0, 0, 0, business_point_robbery[businessRobbery_randAmount], 0);
        mysql_tquery(MySQL_GetHandle(), query);
    }

    return map_set(m_business_Robbery, businessid, l_business_Robbery_PointRob);
}

stock bool:BusinessHasPointRob(businessid)
{
    return map_has_key(m_business_Robbery, businessid);
}

stock bool:Business_EditRobbery(playerid, businessid)
{   
    if(!map_has_key(m_business_Robbery, businessid) && playerid <= INVALID_PLAYER_ID)
    {
        return false;
    }

    if(map_has_key(m_storedPlayer_editRob, playerid))
    {
        return false;
    }

    map_set(m_storedPlayer_editRob, playerid, businessid);
    ShowPlayerEditBusinessRobbery(playerid, businessid);
    return true;
}

stock bool:Business_CloseEditRobbery(playerid, businessid)
{
    if(!map_has_key(m_business_Robbery, businessid) && playerid <= INVALID_PLAYER_ID)
    {
        return false;
    }

    if(!map_has_key(m_storedPlayer_editRob, playerid))
    {
        return false;
    }

    for(new Iter:index = map_iter(m_storedPlayer_editRob); iter_inside(index); iter_move_next(index))
    {
        if(iter_get_key(index) == playerid && iter_get_value(index) == businessid)
        {
            iter_erase_deep(index);
            return true;
        }
    }

    return false;   
}

stock BusinessGetAmountPointToRob(businessid)
{
    if(map_has_key(m_business_Robbery, businessid))
    {
        new List:l_business_Robbery_PointRob = list_new();
        if(map_get_safe(m_business_Robbery, businessid, l_business_Robbery_PointRob))
        {
            return list_size(l_business_Robbery_PointRob);
        }
    }

    return 0;
}

stock bool:BusinessRobbery_GetUUID(businessid, listid, uuid[])
{
    if(!map_has_key(m_business_Robbery, businessid))
    {
        return false;
    }

    new List:l_business_Robbery_PointRob = list_new();
    if(map_get_safe(m_business_Robbery, businessid, l_business_Robbery_PointRob))
    {
        new business_point_robbery[E_BUSINESS_POINT_ROBBERY_DATA];
        uuid[0] = EOS;

        if(list_get_arr_safe(l_business_Robbery_PointRob, listid, business_point_robbery))
        {
            strcat(uuid, business_point_robbery[business_robberyUUID], UUID_LEN);
            return true;
        }
    }

    return false;
}

stock MoneyConvert(money)
{
    new string[50];
    format(string, sizeof(string), "Error.");

    new price = money;

    new value[10];
    valstr(value, price);
    format(string, sizeof(string), "");

    if(strlen(value) > 3)
    {
        new temp = (strlen(value)/3) - 1;
        if(strlen(value) % 3 == 0)
        {
            temp = strlen(value)/3;
        }

        for(new i = 0; i < strlen(value); i++)
        {
            format(string, sizeof(string), "%s%c", string, value[i]);
            if(strlen(value) % 3 != 0)
            {
                if(strlen(value) == 5)
                {
                    if(i == 1)
                    {
                        format(string, sizeof(string), "%s.", string);
                    }
                }
                else
                {
                    if(i == temp - 2 + strlen(value)%3 || i == (temp*3) + strlen(value)%3 - 1)
                    {
                        format(string, sizeof(string), "%s.", string);
                    }
                }
            }
            else
            {
                if(strlen(value) == 6)
                {
                    if(i == 2)
                    {
                        format(string, sizeof(string), "%s.", string);
                    }
                }

                if(strlen(value) == 9)
                {
                    if(i == 2 || i == 5)
                    {
                        format(string, sizeof(string), "%s.", string);
                    }
                }
            }
            
        }
    }   
    else
    {
        format(string, sizeof(string), "%s", value);
    }
    return string;
}

ShowPlayerEditBusinessRobbery(playerid, businessid)
{
    new amount_of_point = BusinessGetAmountPointToRob(businessid);
    
    businessrob_main:
    new str[5000];
    format(str, sizeof(str), "Business Index:\t%d\n", businessid);
    for(new i = 0; i < amount_of_point; i++)
    {
        format(str, sizeof(str), "%sEdit Robbery Point:\t%d\n", str, i);
    }

    if(amount_of_point <= 0)
    {
        format(str, sizeof(str), "Khong co Point de edit, hay thu lai.");
    }

    new response_main[e_DIALOG_RESPONSE_INFO];
    await_arr(response_main) ShowPlayerAsyncDialog(playerid, DIALOG_STYLE_TABLIST, "Robbery Business Edit", str, "<<", ">>");
    if(response_main[E_DIALOG_RESPONSE_Response]) 
    {
        switch(response_main[E_DIALOG_RESPONSE_Listitem])
        {
            case 0: goto businessrob_main;
            default: goto businessrob_edit;
        }
    }   
    else
    {
        Business_CloseEditRobbery(playerid, businessid);
        return SendClientMessage(playerid, -1, "Ban da tat he thong dieu chinh Business Robbery.");
    }

    businessrob_edit:
    new 
        index_of_point = response_main[E_DIALOG_RESPONSE_Listitem] - 1,
        List:l_business_Robbery_PointRob = list_new();

    new business_point_robbery[E_BUSINESS_POINT_ROBBERY_DATA];    
    if(map_has_key(m_business_Robbery, businessid))
    {
        if(map_get_safe(m_business_Robbery, businessid, l_business_Robbery_PointRob))
        {
            if(list_get_arr_safe(l_business_Robbery_PointRob, index_of_point, business_point_robbery))
            {
                SendClientMessage(playerid, -1, "Ban dang o bang dieu chinh.");
            }
        }
    }

    new uuid[UUID_LEN];
    BusinessRobbery_GetUUID(businessid, index_of_point, uuid);
    printf("UUID: %s", uuid);

    new string[1048];
    format(string, sizeof(string), 
        "Business Index:\t%d\n\
        Robbery Point Of Business:\t%d/%d\n\
        Business Position:\tNhan vao day de dieu chinh vi tri\n\
        Money Random (Min: x$ - Max: y$):\t%s$ - %s$\n\
        Robbery Timing:\t%d seconds\n\
        Alaram Police:\t%s\n\
        Accept to Robbery:\t%s",

    businessid, index_of_point, list_size(l_business_Robbery_PointRob), MoneyConvert(business_point_robbery[businessRobbery_moneyMin]), 
    MoneyConvert(business_point_robbery[businessRobbery_moneyMax]), business_point_robbery[businessRobbery_timingCountdown], 
    (business_point_robbery[businessRobbery_Alaram] == true) ? "True" : "False", 
    (business_point_robbery[businessRobbery_AcpToRob] == true) ? "True" : "False");
    
    new response_business_rob_edit_main[e_DIALOG_RESPONSE_INFO];
    await_arr(response_business_rob_edit_main) ShowPlayerAsyncDialog(playerid, DIALOG_STYLE_TABLIST, "Robbery Business Edit", string, "<<", ">>");
    if(response_business_rob_edit_main[E_DIALOG_RESPONSE_Response])
    {
        switch(response_business_rob_edit_main[E_DIALOG_RESPONSE_Listitem])
        {
            case 0: goto businessrob_edit;
            case 1: goto businessrob_edit;
            case 2: goto businessrob_edit_position;
            case 3: goto businessrob_input_money;
            case 4: goto businessrob_input_time;
            case 5: goto businessrob_edit_alaram;
            case 6: goto businessrob_edit_acptoedit;
        }
    }
    else
    {
        goto businessrob_main;
        return 1;
    }

    businessrob_edit_position:
    {
        new 
            Float:x, Float:y, Float:z,
            interiorid, worldid;
        
        GetPlayerPos(playerid, x, y, z);
        interiorid = GetPlayerInterior(playerid);
        worldid = GetPlayerVirtualWorld(playerid);

        if(IsValidDynamicCP(business_point_robbery[business_pointRobbery_cpID]))
        {
            DestroyDynamicCP(business_point_robbery[business_pointRobbery_cpID]);
        }

        new cpid = CreateDynamicCP(x, y, z, 1.0, interiorid, worldid, _, 5.0);
        Streamer_SetIntData(STREAMER_TYPE_CP, cpid, E_STREAMER_EXTRA_ID, E_STREAMER_EXTRA_ROBBERY_ID);

        list_set_cell(l_business_Robbery_PointRob, index_of_point, business_pointRobberry_X, x);
        list_set_cell(l_business_Robbery_PointRob, index_of_point, business_pointRobberry_Y, y);
        list_set_cell(l_business_Robbery_PointRob, index_of_point, business_pointRobberry_Z, z);
        list_set_cell(l_business_Robbery_PointRob, index_of_point, business_pointRobbery_int, interiorid);
        list_set_cell(l_business_Robbery_PointRob, index_of_point, business_pointRobbery_vw, worldid);
        list_set_cell(l_business_Robbery_PointRob, index_of_point, business_pointRobbery_cpID, cpid);
        map_set(m_business_Robbery, businessid, l_business_Robbery_PointRob);
        
        new query[147 + 100];
        mysql_format(MySQL_GetHandle(), query, sizeof(query), "UPDATE `business_robbery_point` SET `pos_x` = %.4f, `pos_y` = %.4f, `pos_z` = %.4f, `int` = %d, `vw` = %d WHERE `businessid` = %d AND `uuid` = '%e'", x, y, z, interiorid, worldid, businessid, uuid);
        mysql_tquery(MySQL_GetHandle(), query);

        SendClientMessage(playerid, -1, "Ban da dieu chinh vi tri moi cua dia diem cuop Business.");
        Streamer_Update(playerid);
        goto businessrob_edit;
    }   

    businessrob_input_money:
    {
        new response_business_input_money[e_DIALOG_RESPONSE_INFO];
        await_arr(response_business_input_money) ShowPlayerAsyncDialog(playerid, DIALOG_STYLE_INPUT, "Hay nhap vao day cu phap: (Min - Max)", "x - y", "<<", ">>");
        if(response_business_input_money[E_DIALOG_RESPONSE_Response])
        {
            new min_money, max_money;
            if(sscanf(response_business_input_money[E_DIALOG_RESPONSE_InputText], "p<->dd", min_money, max_money))
            {
                SendClientMessage(playerid, -1, "Hay nhap dung cu phap!");
                goto businessrob_edit;
                return 1;
            }

            if(min_money > max_money || max_money < min_money || min_money == max_money)
            {
                SendClientMessage(playerid, -1, "Nhap so tien khong phu hop, hay thu lai.");
                goto businessrob_input_money;
                return 1;
            }
            
            list_set_cell(l_business_Robbery_PointRob, index_of_point, businessRobbery_moneyMin, min_money);
            list_set_cell(l_business_Robbery_PointRob, index_of_point, businessRobbery_moneyMax, max_money);
            map_set(m_business_Robbery, businessid, l_business_Robbery_PointRob);

            new query[112 + 20 + UUID_LEN];
            mysql_format(MySQL_GetHandle(), query, sizeof(query), "UPDATE `business_robbery_point` SET `money_Max` = %d, `money_Min` = %d WHERE `businessid` = %d AND `uuid` = '%e'", max_money, min_money, businessid, uuid);
            mysql_tquery(MySQL_GetHandle(), query);

            SendClientMessage(playerid, -1, "Ban da dieu chinh thanh cong gia tien random.");
            goto businessrob_edit;
        }
        else goto businessrob_edit;
    }

    businessrob_input_time:
    {
        new response_business_input_time[e_DIALOG_RESPONSE_INFO];
        await_arr(response_business_input_time) ShowPlayerAsyncDialog(playerid, DIALOG_STYLE_INPUT, "Business Robbery Editing", "Hay nhap vao day thoi gian Coutdown trong luc nguoi choi cuop.", "<<", ">>");
        if(response_business_input_time[E_DIALOG_RESPONSE_Response])
        {
            new time = strval(response_business_input_time[E_DIALOG_RESPONSE_InputText]);
            if(time <= 0)
            {
                SendClientMessage(playerid, -1, "Thoi gian khong hop le, vui long thu lai.");
                goto businessrob_input_time;
                return 1;
            }

            list_set_cell(l_business_Robbery_PointRob, index_of_point, businessRobbery_timingCountdown, time * 1000);
            map_set(m_business_Robbery, businessid, l_business_Robbery_PointRob);

            new query[100 + 20 + UUID_LEN];
            mysql_format(MySQL_GetHandle(), query, sizeof(query), "UPDATE `business_robbery_point` SET `timingCountdown` = %d WHERE `businessid` = %d AND `uuid` = '%e'", time * 1000, businessid, uuid);
            mysql_tquery(MySQL_GetHandle(), query);

            SendClientMessage(playerid, -1, "Ban da dieu chinh thanh cong thoi gian Coutdown.");
            goto businessrob_edit;
        }
        else goto businessrob_edit;
    }

    businessrob_edit_alaram:
    {
        business_point_robbery[businessRobbery_Alaram] = !business_point_robbery[businessRobbery_Alaram];
        list_set_cell(l_business_Robbery_PointRob, index_of_point, businessRobbery_Alaram, business_point_robbery[businessRobbery_Alaram]);
        map_set(m_business_Robbery, businessid, l_business_Robbery_PointRob);

        new query[91 + 2 + UUID_LEN];
        mysql_format(MySQL_GetHandle(), query, sizeof(query), "UPDATE `business_robbery_point` SET `alaram` = %d WHERE `businessid` = %d AND `uuid` = '%e'", (business_point_robbery[businessRobbery_Alaram] == true ? 1 : 0), businessid, uuid);
        mysql_tquery(MySQL_GetHandle(), query);

        if(business_point_robbery[businessRobbery_Alaram] == true)
        {
            SendClientMessage(playerid, -1, "Ban da dieu chinh khi nguoi choi cuop se bao coi ve cho canh sat.");
        }
        else
        {
            SendClientMessage(playerid, -1, "Ban da tat he thong bao dong cho canh sat.");
        }

        goto businessrob_edit;
    }

    businessrob_edit_acptoedit:
    {
        if(business_point_robbery[businessRobbery_AcpToRob] == false)
        {
            if(business_point_robbery[businessRobbery_timingCountdown] == 0 || business_point_robbery[business_pointRobbery_cpID] == -1)
            {
                SendClientMessage(playerid, -1, "Vui long thu lai, hay dieu chinh nhung thu can thiet.");
                goto businessrob_edit;
                return 1;
            }   
        }

        business_point_robbery[businessRobbery_AcpToRob] = !business_point_robbery[businessRobbery_AcpToRob];
        list_set_cell(l_business_Robbery_PointRob, index_of_point, businessRobbery_AcpToRob, business_point_robbery[businessRobbery_AcpToRob]);
        map_set(m_business_Robbery, businessid, l_business_Robbery_PointRob);

        new query[91 + 20 + UUID_LEN];
        mysql_format(MySQL_GetHandle(), query, sizeof(query), "UPDATE `business_robbery_point` SET `acpToRob` = %d, `time_unix` = 0 WHERE `businessid` = %d AND `uuid` = '%e'", (business_point_robbery[businessRobbery_AcpToRob] == true ? 1 : 0), businessid, uuid);
        mysql_tquery(MySQL_GetHandle(), query);

        if(business_point_robbery[businessRobbery_AcpToRob] == true)
        {
            if(map_has_key(m_timeUnix_Business_after_rob, businessid))
            {
                new List:l_business_Robbery_timeUnix = list_new();
                if(map_get_safe(m_timeUnix_Business_after_rob, businessid, l_business_Robbery_timeUnix))
                {
                    new business_time_unix[E_BUSINESS_POINT_TIME_UNIX_DATA];
                    for(new Iter:index = list_iter(l_business_Robbery_timeUnix); iter_inside(index); iter_move_next(index))
                    {
                        if(iter_get_arr_safe(index, business_time_unix))
                        {
                            if(!strcmp(business_time_unix[e_business_timeUnix_uuid], uuid))
                            {
                                iter_erase_deep(index);
                                break;
                            }
                        }
                    }
                }
            }

            SendClientMessage(playerid, -1, "Ban da cho phep nguoi choi co the cuop diem nay.");
        }
        else
        {
            SendClientMessage(playerid, -1, "Ban khong cho phep nguoi choi cuop diem nay.");
        }
        
        goto businessrob_edit;
    }

    return 1;    
}

stock bool:BusinessTimeUnix_GetUUID(businessid, listid, uuid[])
{
    if(!map_has_key(m_timeUnix_Business_after_rob, businessid))
    {
        return false;
    }

    new List:l_business_Robbery_timeUnix = list_new();
    if(map_get_safe(m_timeUnix_Business_after_rob, businessid, l_business_Robbery_timeUnix))
    {
        new business_time_unix[E_BUSINESS_POINT_TIME_UNIX_DATA];
        uuid[0] = EOS;

        if(list_get_arr_safe(l_business_Robbery_timeUnix, listid, business_time_unix))
        {
            strcat(uuid, business_time_unix[e_business_timeUnix_uuid], UUID_LEN);
            return true;
        }
    }

    return false;
}

timer ResetBusiness[1000]()
{
    if(map_size(m_timeUnix_Business_after_rob) <= 0)
    {
        stop timer_unix_robbery;
        timer_unix_robbery = Timer:0;
        printf("Done!");
        return 1;
    }

    for(new Iter:index = map_iter(m_timeUnix_Business_after_rob); iter_inside(index); iter_move_next(index))
    {
        new List:l_business_Robbery_timeUnix = list_new();
        if(iter_get_safe(index, l_business_Robbery_timeUnix))
        {
            if(list_size(l_business_Robbery_timeUnix) == 0)
            {
                iter_erase_deep(index);
                return 1;
            }

            new business_time_unix[E_BUSINESS_POINT_TIME_UNIX_DATA];
            for(new Iter:j = list_iter(l_business_Robbery_timeUnix); iter_inside(j); iter_move_next(j))
            {
                if(iter_get_arr_safe(j, business_time_unix))
                {
                    if(business_time_unix[e_business_timeUnix_time] == 0)
                    {
                        new 
                            randAmount = Random(1, 10),
                            List:l_business_Robbery_PointRob = list_new();
                        
                        for(new Iter:z = map_iter(m_business_Robbery); iter_inside(z); iter_move_next(z))
                        {
                            if(iter_get_safe(z, l_business_Robbery_PointRob))
                            {
                                new business_point_robbery[E_BUSINESS_POINT_ROBBERY_DATA];
                                for(new Iter:v = list_iter(l_business_Robbery_PointRob); iter_inside(v); iter_move_next(v))
                                {
                                    if(iter_get_arr_safe(v, business_point_robbery))
                                    {
                                        if(!strcmp(business_time_unix[e_business_timeUnix_uuid], business_point_robbery[business_robberyUUID]))
                                        {
                                            business_point_robbery[businessRobbery_AcpToRob] = true;
                                            business_point_robbery[businessRobbery_randAmount] = randAmount;

                                            iter_set_arr(v, business_point_robbery);
                                            iter_set(z, l_business_Robbery_PointRob);
                                        }
                                    }
                                }
                            }
                        }

                        new query[108 + 10 + UUID_LEN];
                        mysql_format(MySQL_GetHandle(), query, sizeof(query), "UPDATE `business_robbery_point` SET `time_unix` = %d, `randAmount` = %d, `acpToRob` = %d WHERE `uuid` = '%e'", 0, randAmount, 1, business_time_unix[e_business_timeUnix_uuid]);
                        mysql_tquery(MySQL_GetHandle(), query);

                        iter_erase_deep(j);
                        return 1;
                    }

                    business_time_unix[e_business_timeUnix_time] -= 1;
                    iter_set_arr(j, business_time_unix);
                    iter_set(index, l_business_Robbery_timeUnix);
                }
            }
        }
    }
    
    return 1;
}

timer UpdateRobbery[500](playerid, businessid, listid, time)
{
    if(map_size(m_stored_pRobBusiness) <= 0)
    {
        printf("stop");
        stop timer_robbery;
        return 0;
    }

    if(!map_has_key(m_stored_pRobBusiness, playerid))
    {
        return 0;
    }

    if(!map_has_key(m_stored_pTimerRob, playerid))
    {
        return 0;
    }

    new time_unix_inside = gettime();
    printf("cu run thoi: gettime(): %d | time: %d | playerid: %d businessid: %d listid: %d time: %d", time_unix_inside, map_get(m_stored_pTimerRob, playerid), playerid, businessid, listid, time);

    if(time_unix_inside - map_get(m_stored_pTimerRob, playerid) == time)
    {
        map_set(m_stored_pTimerRob, playerid, time_unix_inside);
        
        if(map_has_key(m_business_Robbery, businessid))
        {
            new List:l_business_Robbery_PointRob = list_new();
            if(map_get_safe(m_business_Robbery, businessid, l_business_Robbery_PointRob))
            {
                new business_point_robbery[E_BUSINESS_POINT_ROBBERY_DATA];
                if(list_get_arr_safe(l_business_Robbery_PointRob, listid, business_point_robbery))
                {
                    if(business_point_robbery[businessRobbery_randAmount] == 0)
                    {
                        map_remove_deep(m_stored_pRobBusiness, playerid);
                        map_remove_deep(m_stored_pTimerRob, playerid);    
                        list_set_cell(l_business_Robbery_PointRob, listid, businessRobbery_AcpToRob, false);
                        map_set(m_business_Robbery, businessid, l_business_Robbery_PointRob);

                        TogglePlayerControllable(playerid, true);
                        SendClientMessage(playerid, -1, "Da cuop thanh cong, ban da nhan duoc tien va cac mon do co gia tri khac.");

                        new 
                            business_time_unix[E_BUSINESS_POINT_TIME_UNIX_DATA],
                            List:l_business_Robbery_timeUnix = list_new();

                        business_time_unix[e_business_timeUnix_time] = 60 * 60 * 3;   
                        strcat(business_time_unix[e_business_timeUnix_uuid], business_point_robbery[business_robberyUUID], UUID_LEN);

                        new query[89 + 10 + UUID_LEN];
                        mysql_format(MySQL_GetHandle(), query, sizeof(query), "UPDATE `business_robbery_point` SET `acpToRob` = %d, `time_unix` = %d WHERE `uuid` = '%e'", 0, business_time_unix[e_business_timeUnix_time], business_point_robbery[business_robberyUUID]);
                        mysql_tquery(MySQL_GetHandle(), query);

                        if(map_has_key(m_timeUnix_Business_after_rob, businessid))
                        {   
                            if(map_get_safe(m_timeUnix_Business_after_rob, businessid, l_business_Robbery_timeUnix))
                            {
                                list_add_arr(l_business_Robbery_timeUnix, business_time_unix);
                            }
                        }
                        else
                        {
                            list_add_arr(l_business_Robbery_timeUnix, business_time_unix);
                            map_set(m_timeUnix_Business_after_rob, businessid, l_business_Robbery_timeUnix);
                        }

                        if(timer_unix_robbery == Timer:0)
                        {
                            timer_unix_robbery = repeat ResetBusiness();
                        }

                        return 1;
                    }

                    printf("dua tien cho nguoi choi: %d", Random(business_point_robbery[businessRobbery_moneyMin], business_point_robbery[businessRobbery_moneyMax]));
                    list_set_cell(l_business_Robbery_PointRob, listid, businessRobbery_randAmount, business_point_robbery[businessRobbery_randAmount] - 1);
                    map_set(m_business_Robbery, businessid, l_business_Robbery_PointRob);
                }
            }
        }
    }
    
    return 0;
}

Player_StartBussinessRob(playerid)
{
    for(new Iter:index = map_iter(m_stored_pRobBusiness); iter_inside(index); iter_move_next(index))
    {
        if(iter_get_key(index) == playerid)
        {   
            new business_point_robbery[E_BUSINESS_POINT_ROBBERY_DATA];
            for(new Iter:j = map_iter(m_business_Robbery); iter_inside(j); iter_move_next(j))
            {
                new List:l_business_Robbery_PointRob = list_new();
                if(iter_get_safe(j, l_business_Robbery_PointRob))
                {
                    for(new Iter:z = list_iter(l_business_Robbery_PointRob); iter_inside(z); iter_move_next(z))
                    {
                        if(iter_get_arr_safe(z, business_point_robbery))
                        {
                            if(business_point_robbery[business_pointRobbery_cpID] == iter_get_value(index))
                            {
                                new businessid = iter_get_key(j);
                                new listid = iter_get_key(z);

                                SendClientMessage(playerid, -1, "Ban dang bat dau cuop.");
                                TogglePlayerControllable(playerid, false);
                                
                                new temp_time = business_point_robbery[businessRobbery_timingCountdown]/1000;
                                if(temp_time < business_point_robbery[businessRobbery_randAmount])
                                {
                                    while(temp_time < business_point_robbery[businessRobbery_randAmount])
                                    {
                                        business_point_robbery[businessRobbery_randAmount] = Random(1, 10);
                                        list_set_cell(l_business_Robbery_PointRob, listid, businessRobbery_randAmount, business_point_robbery[businessRobbery_randAmount]);
                                    }
                                }

                                new time = (business_point_robbery[businessRobbery_timingCountdown]/1000)/(business_point_robbery[businessRobbery_randAmount]);
                                printf("load time: %d | timing countdown: %d | amount: %d", time, business_point_robbery[businessRobbery_timingCountdown], business_point_robbery[businessRobbery_randAmount]);
                                
                                new time_temp = gettime();
                                map_set(m_stored_pTimerRob, playerid, time_temp);
                                timer_robbery = repeat UpdateRobbery(playerid, businessid, listid, time);
                            }
                        }
                    }
                }
            }
        }
    }

    return 0;
}

forward OnRobberyPointLoad();
public OnRobberyPointLoad()
{
    new 
        rows = cache_num_rows(),
        businessid, max_business = 0; 

    // Step 1: Find out max businessid in database
    for(new index = 0; index < rows; index++)
    {   
        cache_get_value_int(index, "businessid", businessid);

        if(businessid > max_business)
        {
            max_business = businessid;
        }
    }

    // Step 2: Find an element that equals index loop of max_business and add into List.
    for(new i = 0; i <= max_business; i++)
    {
        new 
            List:l_business_Robbery_PointRob = list_new(),
            business_point_robbery[E_BUSINESS_POINT_ROBBERY_DATA];

        for(new j = 0; j < rows; j++)
        {
            cache_get_value_int(j, "businessid", businessid);

            if(businessid == i)
            {   
                business_point_robbery[businessRobbery_AcpToRob] = false;
                business_point_robbery[businessRobbery_Alaram] = false;
                business_point_robbery[business_robberyIndex] = businessid;

                cache_get_value_name(j, "uuid", business_point_robbery[business_robberyUUID]);
                cache_get_value_float(j, "pos_x", business_point_robbery[business_pointRobberry_X]);
                cache_get_value_float(j, "pos_y", business_point_robbery[business_pointRobberry_Y]);
                cache_get_value_float(j, "pos_z", business_point_robbery[business_pointRobberry_Z]);
                cache_get_value_int(j, "int", business_point_robbery[business_pointRobbery_int]);
                cache_get_value_int(j, "vw", business_point_robbery[business_pointRobbery_vw]);
                cache_get_value_int(j, "money_Max", business_point_robbery[businessRobbery_moneyMax]);
                cache_get_value_int(j, "money_Min", business_point_robbery[businessRobbery_moneyMin]);
                cache_get_value_int(j, "timingCountdown", business_point_robbery[businessRobbery_timingCountdown]);
                
                new statements = 0;
                cache_get_value_int(j, "acpToRob", statements);
                if(statements == 1)
                {
                    business_point_robbery[businessRobbery_AcpToRob] = true;
                    statements = 0;
                }
                
                cache_get_value_int(j, "alaram", statements);
                if(statements == 1)
                {
                    business_point_robbery[businessRobbery_Alaram] = true;
                }

                cache_get_value_int(j, "randAmount", business_point_robbery[businessRobbery_randAmount]);

                // Create dynamic checkpoint for robbery point.
                business_point_robbery[business_pointRobbery_cpID] = CreateDynamicCP(business_point_robbery[business_pointRobberry_X], business_point_robbery[business_pointRobberry_Y], business_point_robbery[business_pointRobberry_Z], 1.0, business_point_robbery[business_pointRobbery_int], business_point_robbery[business_pointRobbery_vw], _, 5.0);
                Streamer_SetIntData(STREAMER_TYPE_CP, business_point_robbery[business_pointRobbery_cpID], E_STREAMER_EXTRA_ID, E_STREAMER_EXTRA_ROBBERY_ID);

                if(map_has_key(m_business_Robbery, businessid))
                {
                    if(map_get_safe(m_business_Robbery, businessid, l_business_Robbery_PointRob))
                    {
                        list_add_arr(l_business_Robbery_PointRob, business_point_robbery);
                        printf("List size in businessid (%d): %d", businessid, list_size(l_business_Robbery_PointRob));
                    }
                }
                else
                {
                    list_add_arr(l_business_Robbery_PointRob, business_point_robbery);
                    map_set(m_business_Robbery, businessid, l_business_Robbery_PointRob);

                    printf("List size in businessid (%d): %d", businessid, list_size(l_business_Robbery_PointRob));
                }
        
                new 
                    business_time_unix[E_BUSINESS_POINT_TIME_UNIX_DATA],    
                    List:l_business_Robbery_timeUnix = list_new();

                new time_unix = 0;
                cache_get_value_int(j, "time_unix", time_unix);
                if(time_unix != 0)
                {
                    strcat(business_time_unix[e_business_timeUnix_uuid], business_point_robbery[business_robberyUUID], sizeof(business_point_robbery[business_robberyUUID]));
                    business_time_unix[e_business_timeUnix_time] = time_unix;

                    if(map_has_key(m_timeUnix_Business_after_rob, businessid))
                    {
                        if(map_get_safe(m_timeUnix_Business_after_rob, businessid, l_business_Robbery_timeUnix))
                        {
                            list_add_arr(l_business_Robbery_timeUnix, business_time_unix);
                            //map_set(m_timeUnix_Business_after_rob, businessid, l_business_Robbery_timeUnix);
                            
                            printf("Businessid: %d | List size: %d | UUID: %s", businessid, list_size(l_business_Robbery_timeUnix) - 1, business_time_unix[e_business_timeUnix_uuid]);
                        }
                    }
                    else
                    {
                        list_add_arr(l_business_Robbery_timeUnix, business_time_unix);
                        map_set(m_timeUnix_Business_after_rob, businessid, l_business_Robbery_timeUnix);
                        printf("Businessid: %d | List size: %d | UUID: %s", businessid, list_size(l_business_Robbery_timeUnix) - 1, business_time_unix[e_business_timeUnix_uuid]);
                    }
                }
            }
        }
    }

    // Step 3: I have nothing to say xD
    if(map_size(m_timeUnix_Business_after_rob) > 0)
    {
        timer_unix_robbery = repeat ResetBusiness();
    }

    return 1;
}


#include <YSI_Coding\y_hooks>
hook OnGameModeInit()
{
    m_storedPlayer_editRob = map_new();    
    m_business_Robbery = map_new();
    m_stored_pRobBusiness = map_new();
    m_stored_pTimerRob = map_new();
    m_timeUnix_Business_after_rob = map_new();
    mysql_tquery(MySQL_GetHandle(), "SELECT * FROM `business_robbery_point`", "OnRobberyPointLoad");
    return 1;
}

hook OnGameModeExit()
{
    if(timer_unix_robbery != Timer:0)
    {
        for(new Iter:i = map_iter(m_timeUnix_Business_after_rob); iter_inside(i); iter_move_next(i))
        {
            new List:l_business_Robbery_timeUnix = list_new();
            if(iter_get_safe(i, l_business_Robbery_timeUnix))
            {
                new business_time_unix[E_BUSINESS_POINT_TIME_UNIX_DATA];
                for(new Iter:j = list_iter(l_business_Robbery_timeUnix); iter_inside(j); iter_move_next(j))
                {
                    if(iter_get_arr_safe(j, business_time_unix))
                    {
                        new query[72 + 10 + UUID_LEN];
                        mysql_format(MySQL_GetHandle(), query, sizeof(query), "UPDATE `business_robbery_point` SET `time_unix` = %d WHERE `uuid` = '%e'", business_time_unix[e_business_timeUnix_time], business_time_unix[e_business_timeUnix_uuid]);
                        mysql_tquery(MySQL_GetHandle(), query);
                    }
                }
            }
        }
    }
    return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    if(map_has_key(m_storedPlayer_editRob, playerid))
    {
        for(new Iter:index = map_iter(m_storedPlayer_editRob); iter_inside(index); iter_move_next(index))
        {
            if(iter_get_key(index) == playerid)
            {   
                Business_CloseEditRobbery(playerid, iter_get_value(index));
                break;
            }
        }   
    }

    if(map_has_key(m_stored_pRobBusiness, playerid))
    {
        map_remove_deep(m_stored_pRobBusiness, playerid);
    }

    if(map_has_key(m_stored_pTimerRob, playerid))
    {
        map_remove_deep(m_stored_pTimerRob, playerid);
    }

    return 1;
}

hook OnPlayerEnterDynamicCP(playerid, checkpointid)
{
    if(Streamer_GetIntData(STREAMER_TYPE_CP, checkpointid, E_STREAMER_EXTRA_ID) == E_STREAMER_EXTRA_ROBBERY_ID)
    {
        new business_point_robbery[E_BUSINESS_POINT_ROBBERY_DATA];
        for(new Iter:i = map_iter(m_business_Robbery); iter_inside(i); iter_move_next(i))
        {
            new List:l_business_Robbery_PointRob = list_new();
            if(iter_get_safe(i, l_business_Robbery_PointRob))
            {
                for(new Iter:j = list_iter(l_business_Robbery_PointRob); iter_inside(j); iter_move_next(j))
                {
                    if(iter_get_arr_safe(j, business_point_robbery))
                    {
                        if(business_point_robbery[business_pointRobbery_cpID] == checkpointid)
                        {
                            if(business_point_robbery[businessRobbery_AcpToRob] == false)
                            {
                                SendClientMessage(playerid, -1, "Dia diem nay chua san sang de cuop.");
                                return 1;
                            }

                            if(business_point_robbery[businessRobbery_AcpToRob] == true)
                            {
                                // Stored index of list in map.
                                map_set(m_stored_pRobBusiness, playerid, checkpointid);
                                SendClientMessage(playerid, -1, "Ban co the cuop dia diem cua Business nay.");
                                return 1;
                            }
                        }
                    }
                }
            }
        }
    }
    return 1;
}

hook OnPlayerLeaveDynamicCP(playerid, checkpointid)
{
    if(Streamer_GetIntData(STREAMER_TYPE_CP, checkpointid, E_STREAMER_EXTRA_ID) == E_STREAMER_EXTRA_ROBBERY_ID)
    {
        for(new Iter:i = map_iter(m_stored_pRobBusiness); iter_inside(i); iter_move_next(i))
        {
            if(iter_get_key(i) == playerid)
            {
                iter_erase_deep(i);
                return 1;
            }
        }
    }
    return 1;
}
