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
#include <varaible>
#include <define>
#include <callback>
#include <fc_string>
#include <function>

#include <mysql>
#include <load_database>

//---------------------------------- Modules ----------------------------------//
#include <fadescreen>
#include <account>
#include <player_cmd>

#include <admin\admin_function>
#include <admin\admin_cmd>

#include <config_door>
#include <main_door>

main(){}

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
    return 1;
}

public OnPlayerCommandPerformed(playerid, cmd[], params[], result, flags)
{
    if (result == -1)
    {
        Msg(playerid, MSG_PREFIX_ERROR, "Lenh nay khong ton tai, vui long thu lai hoac ban co the /trogiup de tim kiem lenh.");
        return 0;
    }

    return 1;
}