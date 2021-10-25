#if !defined USE_PAWN_PLUS
    #include <PawnPlus>
#endif

static Map:map_gArr_Command;

stock PC_GetAsciiFirstChar(const string[])
{
    for(new index = 65; index < 123; index++)
    {
        if(string[0] == index)
        {
            return index;
        }
    }

    return 1;
}

stock GlobalArray_CommandInit()
{
    new
        command[50], CmdArray:cmd = PC_GetCommandArray(),
        ascii_char;
    
    for(new index = 0; index < PC_GetArraySize(cmd); index++)
    {
        new List:list_arrStoredString = list_new();

        PC_GetCommandName(cmd, index, command, sizeof(command));
        ascii_char = PC_GetAsciiFirstChar(command) - 65;

        if(map_has_key(map_gArr_Command, ascii_char))
        {
            if(map_get_safe(map_gArr_Command, ascii_char, list_arrStoredString))
            {
                list_add_str(list_arrStoredString, command);
                map_set(map_gArr_Command, ascii_char, list_arrStoredString);
            }
        }
        else 
        {
            list_add_str(list_arrStoredString, command);
            map_set(map_gArr_Command, ascii_char, list_arrStoredString);
        }
    }

    return 1;
}

public OnPlayerCommandPerformed(playerid, cmd[], params[], result, flags)
{
    if(result == -1)
    {
        new 
            bool:haskey = false,
            List:list_arrStoredString = list_new(),
            key = PC_GetAsciiFirstChar(cmd) - 65;

        if(map_has_key(map_gArr_Command, key))
        {
            new messageForPlayer[71 + 500];
            if(map_get_safe(map_gArr_Command, key, list_arrStoredString))
            {
                format(messageForPlayer, sizeof(messageForPlayer), "Khong co lenh nay trong he thong, tu dong se goi y cho nguoi choi mot so lenh: ");

                new string[50];
                for(new Iter:index = list_iter(list_arrStoredString); iter_inside(index); iter_move_next(index))
                {
                    iter_get_str(index, string);
                    if(!strcmp(string, cmd, false, strlen(cmd)))
                    {
                        if(haskey == false)
                        {
                            haskey = true;
                        }

                        format(messageForPlayer, sizeof(messageForPlayer), "%s\n%s", messageForPlayer, string);
                    }
                }

                if(haskey == false)
                {
                    format(messageForPlayer, sizeof(messageForPlayer), "%s: Khong co.", messageForPlayer);
                }

                SendClientMessage(playerid, -1, messageForPlayer);
            }
        }

        return 0;
    }

    return 1;
}

#include <YSI_Coding\y_hooks>
hook OnGameModeInit()
{
    map_gArr_Command = map_new();
    map_set_ordered(map_gArr_Command, false);
    GlobalArray_CommandInit();  
    return 1;
}

