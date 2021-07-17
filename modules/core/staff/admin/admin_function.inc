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