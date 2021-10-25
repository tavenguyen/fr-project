/*--- Project was created on 12:54 - 7/7/2021---*/
//    Founder: Halosetoe                       //
//    Leader Scripter: Halosetoe              //
//    Scripter: Halosetoe                    //
//    Game Content: Halosetoe               //
/*--------- Freedom Roleplay v0.1 ---------*/

#define             FCR_LOCALHOST                "localhost"
#define             FCR_SQL_USER                 "root"
#define             FCR_PASSWORD                 "" // Add password if exist
#define             FCR_DATABASE                 "fcrp-project"      

static MySQL:mysql_handle;
stock MySQL:MySQL_GetHandle()
{
    return MySQL:mysql_handle;
}

public OnQueryError(errorid, const error[], const callback[], const query[], MySQL:handle)
{
    print("ERROR: OnQueryError");
    printf("> errorid: %d", errorid);
    printf("> error: %s", error);
    printf("> callback: %s", callback);
    printf("> query: %s", query);
    printf("> handle: %d", _:handle);
    return 1;
}

#include <YSI_Coding\y_hooks>

static UnixTime;

hook OnGameModeInit()
{    
    mysql_handle = mysql_connect(FCR_LOCALHOST, FCR_SQL_USER, FCR_PASSWORD, FCR_DATABASE);
    if(mysql_errno(mysql_handle) != 0 || mysql_handle == MYSQL_INVALID_HANDLE)
    {
        print("ERROR: Failed to initiate MySQL connection");
        SendRconCommand("exit");
        return 0;
    }
    
    UnixTime = gettime();
    printf("%d", UnixTime);

    print("INFO: MySQL connection initiated succesfully");
    print("INFO: ./core/database/mysql loaded");
    return 1;
}

#include <helper\config_helper>
hook OnGameModeExit()
{
    foreach(new i : Player)
	{
		SaveCharacter(i);
		Kick(i);
	}

    UnixTime = gettime() - UnixTime;
    StoredTimeResetHelper = StoredTimeResetHelper - UnixTime;
    
    new query[500];
    mysql_format(MySQL_GetHandle(), query, sizeof(query), "UPDATE `advisors` SET `advisorGetTime` = %d WHERE advisorLevel = 1", StoredTimeResetHelper);
    if(StoredTimeResetHelper <= 0)
    {
        mysql_format(MySQL_GetHandle(), query, sizeof(query), "UPDATE `advisors` SET `advisorCountHelp` = 0, `advisorGetTime` = 86400 WHERE advisorLevel = 1");
    }

    mysql_tquery(MySQL_GetHandle(), query);
    mysql_close(mysql_handle);
    print("INFO: MySQL connection terminated");
    return 1;
}
