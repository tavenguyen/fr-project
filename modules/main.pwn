/*--- Project was created on 12:54 - 7/7/2021---*/
//    Founder: Halosetoe                       //
//    Leader Scripter: Halosetoe              //
//    Scripter: Halosetoe                    //
//    Game Content: Halosetoe               //
/*--------- Freedom Roleplay v0.1 ---------*/

#define YSI_NO_CACHE_MESSAGE
#define YSI_YES_HEAP_MALLOC

#define PP_SYNTAX_AWAIT
#define PP_SYNTAX_FOR_LIST
#define PP_SYNTAX_FOR_MAP

native SendClientMessageStr(playerid, color, AmxString:string) = SendClientMessage;

//---------------------------------- Libaries ----------------------------------//
#include <a_samp>
#include <a_mysql>

#include <PawnPlus>
#define         USE_PAWN_PLUS

#include <async-dialogs>

#include <uuid>
#include <streamer>
#include <sscanf2>
#include <Pawn.CMD>

#include <YSI_Data\y_iterate>

#include <easyDialog>
#include <samp-precise-timers>
#include <easyDialog>
//---------------------------------- Configs ----------------------------------//
#include <config-colors>
#include <config-dialogs-id>
//---------------------------------- Settings ----------------------------------//
#include <variable>
#include <define>
#include <callback>
#include <fc_string>
#include <function>

#include <mysql>
#include <load_database>
#include <map>

//---------------------------------- Modules ----------------------------------//
#include <circleloading>    
#include <fadescreen>

#include <account>

// Advisor
#include <admin\admin_function>
#include <admin\admin_cmd>
#include <helper\config_helper>
#include <helper\main_helper>

// Door, House, Business
#include <config_house>
#include <main_house>
#include <config_door>
#include <player_cmd>
#include <main_door>

#include <panels\panel>
#include <panels\config_furniture_panel>
#include <textures\alltextures>
#include <textures\tex_function>

// Player
#include <walking_styles>   

#include <suggestion_cmd>

main(){}

stock String_GetTest(const string[], index2)
{
    new 
        count = 0, first_pos = 0, end_pos = 0, str[50],
        List:l_stored = list_new();

    for(new index = 0; index < strlen(string); index++)
    {
        if(string[index] == '/')
        {
            count++;
            list_add(l_stored, index);
        }
    }
    
    list_add(l_stored, strlen(string));
    
    first_pos = (index2 != 0) ? list_get(l_stored, index2 - 1) + 1 : 0;
    end_pos = list_get(l_stored, index2);

    for(new index = first_pos, count_element = 0; index < end_pos; index++, count_element++)
    {
        str[count_element] += string[index];
    }

    list_delete_deep(l_stored);
    return str;
}

public OnGameModeInit()
{
    SetNameTagDrawDistance(15.0);
    SetWeather(1);
    ManualVehicleEngineAndLights();
	ShowPlayerMarkers(0);
	DisableInteriorEnterExits();
	AllowInteriorWeapons(1);
	EnableStuntBonusForAll(0);
	EnableVehicleFriendlyFire();
    LoadingCircle_CreateTD();
    FCRP_InitMap();
    return 1;
}


