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

//---------------------------------- Libaries ----------------------------------//
#include <a_samp>
#include <a_mysql>

#include <PawnPlus>
#include <uuid>

#include <easyDialog>
#include <samp-precise-timers>
#include <easyDialog>
//---------------------------------- Settings ----------------------------------//
#include <config-colors>
//---------------------------------- Settings ----------------------------------//
#include <define>
#include <varaible>
#include <callback>
#include <fc_string>
#include <function>

#include <mysql>
#include <load_database>

//---------------------------------- Modules ----------------------------------//
#include <account>

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


