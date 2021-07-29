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

#include <admin\admin_function>
#include <admin\admin_cmd>

#include <config_house>
#include <main_house>

#include <config_door>
#include <player_cmd>

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
    LoadingCircle_CreateTD();
    FCRP_InitMap();
    return 1;
}

public OnPlayerCommandReceived(playerid, cmd[], params[], flags)
{
    if(PlayerIsConnected(playerid) == false) 
    {
        return Msg(playerid, MSG_PREFIX_ERROR, "Ban chua dang nhap vao may chu.");
    }
    else if(GetPermissionLevel(playerid) < flags && flags != 0)
    {
        Msg(playerid, MSG_PREFIX_ERROR, "Ban khong co quyen de thuc hien dieu nay.");
        return 0;
    }

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