/*--- Project was created on 12:54 - 7/7/2021---*/
//    Founder: Halosetoe                       //
//    Leader Scripter: Halosetoe              //
//    Scripter: Halosetoe                    //
//    Game Content: Halosetoe               //
/*--------- Freedom Roleplay v0.1 ---------*/

flags:advisoronduty(CMD_FLAG_HELPER)
CMD:advisoronduty(playerid, params[])
{
    if(GetPermissionLevel(playerid) > 3)
    {
        Msg(playerid, MSG_PREFIX_ERROR, "Ban khong the su dung lenh nay, hay su dung /staffon.");
        return 1;
    }

    new name[MAX_PLAYER_NAME];
    GetPlayerName(playerid, name, MAX_PLAYER_NAME);

    if(Adv_GetDuty(name) == true)
    {
        Adv_SetDuty(name, false);
        Msg(playerid, MSG_PREFIX_SUCCESS, "Ban vua tat Duty cua Advisor, ban se khong thay tin nhan gi den tu he thong Advisor.");
    }
    else
    {
        Adv_SetDuty(name, true);
        Msg(playerid, MSG_PREFIX_SUCCESS, "Ban vua bat Duty cua Advisor, hay lam viec that bung no.");
    }
    return 1;
}

flags:helperchat(CMD_FLAG_HELPER)
CMD:helperchat(playerid, params[])
{
    new name[MAX_PLAYER_NAME];
    GetPlayerName(playerid, name, MAX_PLAYER_NAME);

    new permission = GetPermissionLevel(playerid);
    if(Adv_GetDuty(name) == false && permission >= 1 && permission <= 3)
    {
        Msg(playerid, MSG_PREFIX_ERROR, "Ban khong the su dung lenh nay neu khong Advisor Onduty.");
        return 1;
    }

    if(GetAdminDuty(playerid) == false && permission > 3)
    {
        Msg(playerid, MSG_PREFIX_ERROR, "Ban khong the su dung lenh nay neu khong Staff Onduty.");
        return 1;
    }

    new chat_str[260];
    if(sscanf(params, "s[260]", chat_str))
    {
        Msg(playerid, MSG_PREFIX_USAGE, "SU DUNG: /helperchat [message]");
        return 1;
    }

    if(isnull(chat_str))
    {
        return 1;
    }

    Adv_SendHelperChat(playerid, chat_str);
    return 1;
}

flags:showquestions(CMD_FLAG_HELPER)
CMD:showquestions(playerid)
{
    if((GetPermissionLevel(playerid) >= 1 && GetPermissionLevel(playerid) < 4 && Adv_GetDuty(Account_ReturnName(playerid))) || (GetPermissionLevel(playerid) >= 4 && GetAdminDuty(playerid)))
    {
        ShowAllQuestions(playerid);
        return 1;
    }
    
    Msg(playerid, MSG_PREFIX_ERROR, "Xay ra loi, vui long thu lai.");
    return 1;
}

CMD:newb(playerid, params[])
{
    new string[128];
    if(sscanf(params, "s[128]", string))
    {
        Msg(playerid, MSG_PREFIX_USAGE, "SU DUNG: /newb [question]");
        return 1;
    }

    if(isnull(string))
    {
        return 1;
    }

    if((IsHelperDuty() == true) || (IsHelperDuty() == false && IsAdminDuty() == true))
    {
        SendQuestionToStaff(playerid, string);
        Msg(playerid, MSG_PREFIX_SUCCESS, "Ban da dat cau hoi thanh cong.");
        return 1;
    }

    
    //SendQuestionToEveryone(playerid, string);
    return 1;
}

flags:clearquestions(CMD_FLAG_ADM_SENIOR)
CMD:clearquestions(playerid)
{
    if(HasServerQuestion() == false)
    {
        Msg(playerid, MSG_PREFIX_ERROR, "Khong co cau hoi de xoa.");
        return 1;
    }

    if(ClearQuestions(playerid))
    {
        Msg(playerid, MSG_PREFIX_SUCCESS, "Ban da xoa thanh cong tat ca cau hoi.");
    }
    else Msg(playerid, MSG_PREFIX_ERROR, "Xoa khong thanh cong.");

    return 1;
}

CMD:ignorequestion(playerid, params[])
{
    new index;
    if(sscanf(params, "d", index))
    {
        Msg(playerid, MSG_PREFIX_USAGE, "SU DUNG: /ignorequestion [index]");
        return 1;
    }

    if(index < 0 || index >= list_size(question_stored))
    {
        Msg(playerid, MSG_PREFIX_ERROR, "Khong co cau hoi nay trong he thong.");
        return 1;
    }

    if(RemoveQuestion(index))
    {
        Msg(playerid, MSG_PREFIX_SUCCESS, "Ban da xoa thanh cong cau hoi.");
    }
    else Msg(playerid, MSG_PREFIX_ERROR, "Xoa khong thanh cong.");
    return 1;
}

flags:answerquestion(CMD_FLAG_ADM_SENIOR)
CMD:answerquestion(playerid, params[])
{
    new index;
    if(sscanf(params, "d", index))
    {
        Msg(playerid, MSG_PREFIX_USAGE, "SU DUNG: /answerquestion [index]");
        return 1;
    }

    if(index < 0 || index >= list_size(question_stored))
    {
        Msg(playerid, MSG_PREFIX_ERROR, "Khong co cau hoi nay trong he thong.");
        return 1;
    }

    ShowPlayerQuestionDialog(playerid, index);
    return 1;
}

CMD:advisors(playerid)
{
    ShowAdvisorInList(playerid);
    return 1;
}