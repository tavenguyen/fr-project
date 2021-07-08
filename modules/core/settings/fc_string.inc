stock bool:String_RemoveChar(str[], const str2[])
{
    for(new index = 0; index < strlen(str); index++)
    {
        if(!strcmp(str[index], str2))
        {
            str[index] = EOS;
            break;
        }
    }

    return true;
}