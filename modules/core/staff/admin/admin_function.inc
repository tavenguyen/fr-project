stock Admin_ReturnStrDuty(playerid)
{
    new character_inside[E_CHARACTER_MEMORY];
    new string[10];
    if(list_get_arr_safe(characters, character_index[playerid], character_inside))
    {
        format(string, sizeof(string), "Offduty");
        if(character_inside[isAdminOnduty])
        {
            format(string, sizeof(string), "Onduty");
        }
    }

    return string;
}

stock GetStaffName(flags)
{
    new staff_name[20];
    format(staff_name, sizeof(staff_name), "Member");

    switch(flags)
    {
        case CMD_FLAG_HELPER: 
        {
            format(staff_name, sizeof(staff_name), "Helper"); 
        }
        case CMD_FLAG_SUPPORTER:
        {
            format(staff_name, sizeof(staff_name), "Supporter");
        }
        case CMD_FLAG_ADM_TESTER:
        {
            format(staff_name, sizeof(staff_name), "Tester");
        }
        case CMD_FLAG_ADM_REPORTER:
        {
            format(staff_name, sizeof(staff_name), "Reporter Admin");
        }
        case CMD_FLAG_ADM_JUNIOR:
        {
            format(staff_name, sizeof(staff_name), "Junior Admin");
        }
        case CMD_FLAG_ADM_SENIOR:
        {
            fomart(staff_name, sizeof(staff_name), "Senior Admin");
        }
        case CMD_FLAG_ADM_HEAD:
        {
            format(staff_name, sizeof(staff_name), "Head Admin");
        }
        case CMD_FLAG_ADM_DIRECTOR:
        {
            format(staff_name, sizeof(staff_name), "Director Admin");
        }
        case CMD_FLAG_ADM_EXECUTIVE:
        {
            format(staff_name, sizeof(staff_name), "Executive Admin");
        }
    }
    
    return staff_name;
}