/*--- Project was created on 12:54 - 7/7/2021---*/
//    Founder: Halosetoe                       //
//    Leader Scripter: Halosetoe              //
//    Scripter: Halosetoe                    //
//    Game Content: Halosetoe               //
/*--------- Freedom Roleplay v0.1 ---------*/


new
    CharacterCreate_Name[MAX_PLAYERS][MAX_PLAYER_NAME + 1],
    CharacterCreate_Day[MAX_PLAYERS],
    CharacterCreate_Month[MAX_PLAYERS],
    CharacterCreate_Year[MAX_PLAYERS],
    CharacterCreate_Gender[MAX_PLAYERS],
    CharacterCreate_SkinColor[MAX_PLAYERS],
    CharacterCreate_Skin[MAX_PLAYERS];

new
    bool:is_pCheckPassword[MAX_PLAYERS] = false,
    bool:PlayerEditCharacter[MAX_PLAYERS] = false;

enum 
{
    genderNone,
    genderMale,
    genderFemale,
    skinColor_none = 0,
    skinColor_white,
    skinColor_yellow,
    skinColor_black
}

enum _:E_CHARACTER_MEMORY
{
    characterAccount[MAX_PLAYER_NAME + 1],
    characterName[MAX_PLAYER_NAME + 1],
    characterUUID[UUID_LEN],
    characterAge,
    characterBirthday_Day,
    characterBirthday_Month,
    characterBirthday_Year,
    characterGender,
    characterSkinColor,
    characterSkinID,
    Float:characterPosX,
    Float:characterPosY,
    Float:characterPosZ,
    Float:characterFacingAngle,
    characterInt,
    characterVW,
    Float:characterHealth,
    Float:characterArmour,
    characterAccent[MAX_CHARACTER_ACCENT],
    characterDescribe[MAX_CHARACTER_DESCRIBE],
    
    // Admin System
    characterAdminLevel,
    characterPermission,
    bool:isAdminOnduty,
    
    // House, Door, Business
    characterInDoor,
    bool:is_Char_Edit_House,
}

new character_index[MAX_PLAYERS] = -1;
new List:characters;