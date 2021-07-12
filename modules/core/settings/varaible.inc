new
    bool:isPlayerConnected[MAX_PLAYERS] = false,
    MessageTDLine_Timer[MAX_PLAYERS] = -1,
    PlayerText:MessageTDLine[MAX_PLAYERS][1] = { PlayerText:INVALID_PLAYER_TEXT_DRAW, ...};

enum _:MSG_PREFIX
{
    MSG_PREFIX_ERROR,
    MSG_PREFIX_SUCCESS
}
