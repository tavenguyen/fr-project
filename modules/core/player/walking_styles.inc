#define                             INVALID_WALKING_STYLES                      -1

// Credits: https://github.com/Mergevos/samp-walking-styles/blob/master/walking_styles.inc

static const TIME_UPDATE_ANIMATION = 300;

static enum _:e_Walking_Styles
{
	WALKING_STYLE_DEFAULT = 0,
	WALKING_STYLE_NORMAL,
	WALKING_STYLE_PED,
	WALKING_STYLE_GANGSTA,
	WALKING_STYLE_GANGSTA2,
	WALKING_STYLE_OLD,
	WALKING_STYLE_FAT_OLD,
	WALKING_STYLE_FAT,
	WALKING_STYLE_WOMANOLD,
	WALKING_STYLE_WOMANFATOLD,
	WALKING_STYLE_SHUFFLE,
	WALKING_STYLE_LADY,
	WALKING_STYLE_LADY2,
	WALKING_STYLE_WHORE,
	WALKING_STYLE_WHORE2,
	WALKING_STYLE_DRUNK,
	WALKING_STYLE_BLIND
}

static const NameAnimations[][] =
{
    "WALK_player",
    "WALK_civi",
    "WALK_gang1",
    "WALK_gang2",
    "WALK_old",
    "WALK_fatold",
    "WALK_fat",
    "WOMAN_walkold",
    "WOMAN_walkfatold",
    "WALK_shuffle",
    "WOMAN_walknorm",
    "WOMAN_walkbusy",
    "WOMAN_walkpro",
    "WOMAN_walksexy",
    "WALK_drunk",
    "WALK_Wuzi"
};

//----------------------------------------------------------------------------------------------///

static 
	timer_Walking[MAX_PLAYERS], 
	style_Walking[MAX_PLAYERS];

static const indexes_animations[] = {1231, 1224, 1226, 1276, 1278, 1280, 1228, 1230, 1458};

stock SetPlayerWalkingStyle(playerid, styles)
{
    style_Walking[playerid] = styles;
    return 1;
}

stock GetPlayerWalkingStyle(playerid)
{
    return style_Walking[playerid];
}

#include <YSI_Coding\y_hooks>
hook OnPlayerConnect(playerid)
{
    timer_Walking[playerid] = INVALID_WALKING_STYLES;
    style_Walking[playerid] = WALKING_STYLE_DEFAULT;
    return 1;
}

hook OnPlayerDisconnect(playerid)
{
    if(timer_Walking[playerid] != INVALID_WALKING_STYLES)
    {
        KillTimer(timer_Walking[playerid]);
    } 
    return 1;
}

hook OnPlayerUpdate(playerid)
{
    if(style_Walking[playerid] > WALKING_STYLE_DEFAULT && timer_Walking[playerid] == INVALID_WALKING_STYLES)
    {
        new keys, updown, leftright;
        GetPlayerKeys(playerid, keys, updown, leftright);
        if(((!!updown  || !!leftright) && (keys & KEY_WALK) ))
        {
            new index = GetPlayerAnimationIndex(playerid);
            for(new i = 0; i < sizeof(indexes_animations); i++)
            {
                if(index == indexes_animations[i])
                {
                    ApplyAnimation(playerid, "PED", NameAnimations[style_Walking[playerid] - 1], 4.1, 1, 1, 1, 1, 1);
                    timer_WalkAnimation(playerid);
                    break;
                }
            }
        }
    }
    return 1;
}

forward timer_WalkAnimation(playerid);
public timer_WalkAnimation(playerid)
{
    timer_Walking[playerid] = -1;

    if(style_Walking[playerid] <= 0) 
    {
        return false;
    }

    new keys, updown, leftright;
    GetPlayerKeys(playerid,keys,updown,leftright);
    
    if(((!!updown  || !!leftright) && (keys & KEY_WALK)))
    {
        new temp_index_anim = GetPlayerAnimationIndex(playerid);
        for(new i = 0; i < sizeof(indexes_animations); i++)
        {
            if(temp_index_anim == indexes_animations[i])
            {   
                timer_Walking[playerid] = SetTimerEx("timer_WalkAnimation", TIME_UPDATE_ANIMATION, false, "d", playerid);
                return true;
            }
        }
    }

	return ApplyAnimation(playerid, "PED", NameAnimations[style_Walking[playerid]-1], 4.0, 0, 0, 0, 0, 1); 
}

CMD:walkstyles(playerid, params[])
{
    extract params -> new walkingstyles; else return SendClientMessage(playerid, COLOR_GREY, "SU DUNG: /walkstyles [1 - 16]");
    if(walkingstyles < 0 || walkingstyles > 16)
    {
        SendClientMessage(playerid, -1, "Walking Styles khong phu hop, vui long thu lai.");
        return 1;
    }

    if(GetPlayerWalkingStyle(playerid) == walkingstyles)
    {
        SendClientMessage(playerid, -1, "Ban khong the dieu chinh Walking Style nay.");
        return 1;
    }

    SetPlayerWalkingStyle(playerid, walkingstyles);
    SendClientMessage(playerid, -1, "Ban da dieu chinh thanh cong Walking Style.");
    return 1;
}