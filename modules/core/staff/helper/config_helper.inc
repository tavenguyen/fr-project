/*--- Project was created on 12:54 - 7/7/2021---*/
//    Founder: Halosetoe                       //
//    Leader Scripter: Halosetoe              //
//    Scripter: Halosetoe                    //
//    Game Content: Halosetoe               //
/*--------- Freedom Roleplay v0.1 ---------*/

forward bool:GetAdminDuty(playerid);

enum _:E_ADVISOR_HELPER_DATA
{
    advisor_h_Name[MAX_PLAYER_NAME + 1],
    advisor_h_gettime,
    bool:advisor_h_Duty,
    advisor_h_Count_help,
    advisor_h_Level
}

static enum _:E_QUESTION_DATA
{
    e_playerName_request[MAX_PLAYER_NAME + 1],
    e_question_request[128]
}

new 
    List:advisor_h_List,
    List:question_stored;

stock AdvHelper_Create(const name[], bool:duty, count_help, level, bool:addSQL = false)
{
    new helper[E_ADVISOR_HELPER_DATA];

    strcat(helper[advisor_h_Name], name, sizeof(helper[advisor_h_Name]));
    helper[advisor_h_gettime] = 86400;
    helper[advisor_h_Duty] = duty;
    helper[advisor_h_Count_help] = count_help;
    helper[advisor_h_Level] = level;

    if(addSQL == true)
    {
        new query[48 + MAX_PLAYER_NAME + 1 + 50];
        mysql_format(MySQL_GetHandle(), query, sizeof(query), "INSERT INTO `advisors` VALUES ('%e', %d, %d, %d)", name, 1, 0, helper[advisor_h_gettime]);
        mysql_tquery(MySQL_GetHandle(), query);
    }

    return list_add_arr(advisor_h_List, helper);
}

stock bool:Adv_SetDuty(const name[], bool:condition)
{
    new index = Adv_GetIndexInList(name);
    if(index < 0 || index >= list_size(advisor_h_List))
    {
        return false;
    }

    list_set_cell(advisor_h_List, index, advisor_h_Duty, condition);
    return true;
}

stock bool:AdvHelper_Remove(const name[])
{
    new helper[E_ADVISOR_HELPER_DATA];
    for(new Iter:index = list_iter(advisor_h_List); iter_inside(index); iter_move_next(index))
    {
        if(iter_get_arr_safe(index, helper))
        {
            if(!strcmp(name, helper[advisor_h_Name], false))
            {
                Adv_SetDuty(name, false);

                iter_erase_deep(index);

                new query[53 + MAX_PLAYER_NAME + 1];
                mysql_format(MySQL_GetHandle(), query, sizeof(query), "DELETE FROM `advisors` WHERE `advisorCharName` = '%e'", name);
                mysql_tquery(MySQL_GetHandle(), query);

                return true;
            }
        }
    }

    return false;
}

stock bool:AdvHelper_SetAdvisorLevel(playerid, level)
{
    new name[MAX_PLAYER_NAME + 1];
    GetPlayerName(playerid, name, sizeof(name));

    new helper[E_ADVISOR_HELPER_DATA];
    for(new Iter:index = list_iter(advisor_h_List); iter_inside(index); iter_move_next(index))
    {
        if(iter_get_arr_safe(index, helper))
        {
            if(!strcmp(helper[advisor_h_Name], name))
            {
                list_set_cell(advisor_h_List, iter_get_key(index), advisor_h_Duty, level);

                new query[72 + MAX_PLAYER_NAME + 1 + 2];
                mysql_format(MySQL_GetHandle(), query, sizeof(query), "UPDATE `advisors` SET `advisorLevel` = %d WHERE `advisorCharName` = '%e'", level, name);
                mysql_tquery(MySQL_GetHandle(), query);

                return true;
            }
        }
    }    

    return false;
}

stock bool:IsHelperInSQL(const name[])
{
    if(list_size(advisor_h_List) == 0)
    {
        return false;
    }

    new helper[E_ADVISOR_HELPER_DATA];
    for(new Iter:index = list_iter(advisor_h_List); iter_inside(index); iter_move_next(index))
    {
        if(iter_get_arr_safe(index, helper))
        {
            if(!strcmp(helper[advisor_h_Name], name, false))
            {
                return true;
            }
        }
    }

    return false;
}

stock bool:IsHelperDuty()
{
    new character[E_CHARACTER_MEMORY];
    foreach(new playerid : Player)
    {
        if(list_get_arr_safe(characters, character_index[playerid], character))
        {
            if(character[characterPermission] >= 1 && character[characterPermission] <= 3)
            {
                return true;
            }
        }
    }

    return false;
}

stock bool:Adv_GetDuty(const name[])
{
    new helper[E_ADVISOR_HELPER_DATA];
    for(new Iter:index = list_iter(advisor_h_List); iter_inside(index); iter_move_next(index))
    {
        if(iter_get_arr_safe(index, helper))
        {
            if(!strcmp(name, helper[advisor_h_Name], false))
            {
                if(helper[advisor_h_Duty] == true)
                {
                    return true;
                }

                return false;
            }   
        }
    }

    return false;
}

stock Adv_GetIndexInList(const name[])
{
    new helper[E_ADVISOR_HELPER_DATA];
    for(new Iter:index = list_iter(advisor_h_List); iter_inside(index); iter_move_next(index))
    {
        if(iter_get_arr_safe(index, helper))
        {
            if(!strcmp(name, helper[advisor_h_Name], false))
            {
                return iter_get_key(index);
            }   
        }
    }

    return (-1);
}

stock bool:ShowAdvisorInList(playerid)
{
    new str[1048];
    format(str, sizeof(str), "In-character Name\t\t\tCount Help\t\t\tRole\t\t\tDuty\n");

    new helper[E_ADVISOR_HELPER_DATA];
    for(new Iter:index = list_iter(advisor_h_List); iter_inside(index); iter_move_next(index))
    {
        if(iter_get_arr_safe(index, helper))
        {
            format(str, sizeof(str), "%s%s\t\t\t%d\t\t\t%s\t\t\t%s\n", str, helper[advisor_h_Name], helper[advisor_h_Count_help], GetStaffName(helper[advisor_h_Level]), (helper[advisor_h_Duty] == true ? "Onduty" : "Offduty"));
        }
    }

    maindialog:
    new response_main[e_DIALOG_RESPONSE_INFO];
    await_arr(response_main) ShowPlayerAsyncDialog(playerid, DIALOG_STYLE_TABLIST, "Advisors", str, "<<", ">>");
    if(response_main[E_DIALOG_RESPONSE_Response])
    {
        switch(response_main[E_DIALOG_RESPONSE_Listitem])
        {
            default: goto maindialog;
        }
    }

    return true;
}

stock bool:Adv_SendHelperChat(senderid, string[])
{
    format(string, 260 + 12, "[OOC-Heper] %s noi: %s", Account_ReturnName(senderid, 0), string);
    foreach(new playerid : Player)
    {
        new name[MAX_PLAYER_NAME];
        GetPlayerName(playerid, name, sizeof(name));

        if(IsHelperInSQL(name) && Adv_GetDuty(name) == true)
        {
            SendClientMessage(playerid, COLOR_YELLOW, string);
        }   

        if(GetPermissionLevel(playerid) > 3 && GetAdminDuty(playerid) == true)
        {
            SendClientMessage(playerid, COLOR_YELLOW, string);
        }
    }

    return true;
}

stock bool:SendQuestionToStaff(senderid, const question[])
{
    foreach(new playerid : Player)
    {
        new name[MAX_PLAYER_NAME], string[200];
        format(name, MAX_PLAYER_NAME, "%s", Account_ReturnName(playerid, 1));

        new question_arr[E_QUESTION_DATA];
        strcat(question_arr[e_playerName_request], name, MAX_PLAYER_NAME);
        strcat(question_arr[e_question_request], question, 128);

        new index = list_add_arr(question_stored, question_arr);
        format(string, sizeof(string), "[Question #%d] Nguoi choi %s vua dat cau hoi, hay /showquestions de xem & tra loi.", index, Account_ReturnName(senderid, 0));

        new permission = GetPermissionLevel(playerid);
        if(permission > 0 && permission < 4 && Adv_GetDuty(name) == true)
        {
            SendClientMessage(playerid, COLOR_GREY, string);      
        }

        if(permission >= 4 && GetAdminDuty(playerid))
        {
            SendClientMessage(playerid, COLOR_GREY, string);    
        }
    }
}

stock bool:SendAnswerToAll(senderid, index, const answer[])
{
    foreach(new playerid : Player)
    {
        if(!PlayerIsConnected(playerid))
        {
            continue;
        }

        new question_arr[E_QUESTION_DATA];
        if(list_get_arr_safe(question_stored, index, question_arr))
        {
            new string[128 + 33 + MAX_PLAYER_NAME];
            format(string, sizeof(string), "[Newbie] Nguoi choi %s da dat cau hoi: %s", question_arr[e_playerName_request], question_arr[e_question_request]);
            SendClientMessage(playerid, COLOR_YELLOW, string);

            format(string, sizeof(string), "[Newbie] %s da tra loi cau hoi nhu sau: %s", Account_ReturnName(senderid, 0), answer);
            SendClientMessage(playerid, COLOR_YELLOW, string);
        }
    }

    new name[MAX_PLAYER_NAME];
    GetPlayerName(senderid, name, sizeof(name));

    new helper[E_ADVISOR_HELPER_DATA];
    for(new Iter:iter_id = list_iter(advisor_h_List); iter_inside(iter_id); iter_move_next(iter_id))
    {
        if(iter_get_arr_safe(iter_id, helper))
        {
            if(!strcmp(name, helper[advisor_h_Name]))
            {
                new count = helper[advisor_h_Count_help] + 1;
                iter_set_cell(iter_id, advisor_h_Count_help, count);

                new query[76 + 5 + MAX_PLAYER_NAME + 1];
                mysql_format(MySQL_GetHandle(), query, sizeof(query), "UPDATE `advisors` SET `advisorCountHelp` = %d WHERE `advisorCharName` = '%e'", count, name);
                mysql_tquery(MySQL_GetHandle(), query);
                
                break;
            }
        }
    }
    
    return true;
}

stock bool:RemoveQuestion(index)
{
    if(index < 0 || index >= list_size(question_stored))
    {
        return false;
    }

    list_remove_deep(question_stored, index);
    return true;
}

stock bool:HasServerQuestion()
{
    if(list_size(question_stored) == 0)
    {
        return false;
    }

    return true;
}

ShowAllQuestions(playerid)
{
    if(list_size(question_stored) == 0)
    {
        SendClientMessage(playerid, COLOR_GREY, "Khong co cau hoi nao duoc dat ra.");
        return 1;
    }

    new
        String:str = str_new(""), 
        question_arr[E_QUESTION_DATA];
    
    for(new Iter:index = list_iter(question_stored); iter_inside(index); iter_move_next(index))
    {
        if(iter_get_arr_safe(index, question_arr))
        {
            str_set_format(str, "Nguoi choi %s da dat cau hoi #%d: %s", question_arr[e_playerName_request], iter_get_key(index), question_arr[e_question_request]);
            SendClientMessageStr(playerid, COLOR_GREY, str);
        }
    }

    return 1;
}

ClearQuestions(playerid)
{
    for(new Iter:index = list_iter(question_stored); iter_inside(index);)
    {
        iter_erase_deep(index);
    }

    new message[62 + MAX_PLAYER_NAME];
    format(message, sizeof(message), "Ban quan tri %s vua xoa het cac cau hoi trong Question System.", Account_ReturnName(playerid, 1)); 
    SendMessageToAllStaff(message);
    return 1;
}

ShowPlayerQuestionDialog(playerid, index)
{
    new question_arr[E_QUESTION_DATA];
    if(list_get_arr_safe(question_stored, index, question_arr))
    {
        new str[12 + 5], info[26 + MAX_PLAYER_NAME + 1];
        format(info, sizeof(info), "Cau hoi cua nguoi choi: %s", question_arr[e_playerName_request]);
        format(str, sizeof(str), "Question #%d", index);

        new response_main[e_DIALOG_RESPONSE_INFO];
        await_arr(response_main) ShowPlayerAsyncDialog(playerid, DIALOG_STYLE_INPUT, info, str, "Tra loi cau hoi", "Roi khoi cau hoi");
        if(response_main[E_DIALOG_RESPONSE_Response])
        {
            SendAnswerToAll(playerid, index, response_main[E_DIALOG_RESPONSE_InputText]);
            list_remove_deep(question_stored, index);
        }
    }
}

#include <YSI_Coding\y_hooks>
hook OnGameModeInit()
{
    advisor_h_List = list_new();
    question_stored = list_new();
    return 1;
}