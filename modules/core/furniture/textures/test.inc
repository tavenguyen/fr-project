CMD:createobj(playerid, params[])
{
    new Float:x, Float:y, Float:z;
    GetPlayerPos(playerid, x, y, z);
    new index = CreateDynamicObject(strval(params), x, y, z, 0.0, 0.0, 0.0);
    printf("Index: %d", index);
    return 1;
}

CMD:test(playerid, params[])
{
    new objectid, index;
    if(sscanf(params, "ii", objectid, index))
    {
        return 1;
    }

    SetDynamicObjectMaterial(objectid, 0, FurnitureTexture[index][fT_index], FurnitureTexture[index][fT_txdName], FurnitureTexture[index][fT_textureName]);
    printf("oke: %d %s %s", FurnitureTexture[index][fT_index], FurnitureTexture[index][fT_txdName], FurnitureTexture[index][fT_textureName]);
    return 1;
}

CMD:furtexture(playerid)
{
    ShowPlayerFurnitureTextureList(playerid);
    return 1;
}