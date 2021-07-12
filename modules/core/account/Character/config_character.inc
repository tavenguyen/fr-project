new
    CharacterCreate_Name[MAX_PLAYERS][MAX_PLAYER_NAME + 1],
    CharacterCreate_Day[MAX_PLAYERS],
    CharacterCreate_Month[MAX_PLAYERS],
    CharacterCreate_Year[MAX_PLAYERS],
    CharacterCreate_Gender[MAX_PLAYERS],
    CharacterCreate_SkinColor[MAX_PLAYERS];

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