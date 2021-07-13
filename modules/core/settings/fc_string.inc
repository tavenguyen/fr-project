stock bool:String_RemoveChar(name[], charToDel)
{
    for(new index = 0; index < strlen(name); index++)
    {
        if(name[index] == charToDel)
        {
            name[index] = ' ';
            return true;
        }
    }

    return true;
}