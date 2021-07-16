new
    Inputtext_AccountLogin[MAX_PLAYERS][256],
    bool:isPlayerConnected[MAX_PLAYERS] = false,
    MessageTDLine_Timer[MAX_PLAYERS] = -1,
    PlayerText:MessageTDLine[MAX_PLAYERS][1] = { PlayerText:INVALID_PLAYER_TEXT_DRAW, ...};

enum _:MSG_PREFIX
{
    MSG_PREFIX_ERROR,
    MSG_PREFIX_SUCCESS,
    MSG_PREFIX_USAGE
}

enum _:AutoToggle
{
    LOW_TOGGLE,
    SHOUT_TOGGLE,
    WHISPER_TOGGLE,
    CAR_WHISPER_TOGGLE
}

new bool:array_AutoToggle[MAX_PLAYERS][AutoToggle];
new iWhisperTargetID[MAX_PLAYERS];
// new bool:bLowToggle = false;