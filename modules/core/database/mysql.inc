/*--- Project was created on 12:54 - 7/7/2021---*/
//    Founder: Halosetoe                       //
//    Leader Scripter: Halosetoe              //
//    Scripter: Halosetoe                    //
//    Game Content: Halosetoe               //
/*--------- Freedom Roleplay v0.1 ---------*/

#define             FCR_LOCALHOST                "localhost"
#define             FCR_SQL_USER                 "root"
#define             FCR_PASSWORD                 ""
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

hook OnGameModeInit()
{    
    mysql_handle = mysql_connect(FCR_LOCALHOST, FCR_SQL_USER, FCR_PASSWORD, FCR_DATABASE);
    if(mysql_errno(mysql_handle) != 0 || mysql_handle == MYSQL_INVALID_HANDLE)
    {
        print("ERROR: Failed to initiate MySQL connection");
        SendRconCommand("exit");
        return 0;
    }
    print("INFO: MySQL connection initiated succesfully");
    print("INFO: ./core/database/mysql loaded");

    return 1;
}

hook OnGameModeExit()
{
    mysql_close(mysql_handle);
    print("INFO: MySQL connection terminated");

    return 1;
}