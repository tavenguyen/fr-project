new
    CharacterCreate_Name[MAX_PLAYERS][MAX_PLAYER_NAME + 1],
    CharacterCreate_Day[MAX_PLAYERS],
    CharacterCreate_Month[MAX_PLAYERS],
    CharacterCreate_Year[MAX_PLAYERS],
    CharacterCreate_Gender[MAX_PLAYERS],
    CharacterCreate_SkinColor[MAX_PLAYERS],
    CharacterCreate_Skin[MAX_PLAYERS];

new bool:PlayerEditCharacter[MAX_PLAYERS] = false;

enum 
{
    genderNone,
    genderMale,
    genderFemale,

    skinColor_none,
    skinColor_white,
    skinColor_yellow,
    skinColor_black
}

new lunarMonth[] = {1, 3, 5, 7, 8, 10, 12};

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
    characterVW
}

new character_index[MAX_PLAYERS] = -1;
new List:characters;