#include "../modules/paths/diagonalroute.inc"

fp UnableMapIconItens() {

	for (new x ; GetPlayerPoolSize() > x; x++)
	{
        RemovePlayerMapIcon(x, 0);
    }
    return true;
}

fs GetPlayerNameEx(playerid)
{
	new name[24];
	GetPlayerName(playerid, name, 24);
	return name;
}

fs ResetPlayerAttachments(playerid)
{
	for(new i; i < MAX_PLAYER_ATTACHED_OBJECTS; i++)
    {
        if(IsPlayerAttachedObjectSlotUsed(playerid, i)) RemovePlayerAttachedObject(playerid, i);
    }
    return 1;
}


fs GetPlayerCameraObject(playerid)
	return Streamer_GetItemStreamerID(playerid, STREAMER_TYPE_OBJECT, GetPlayerCameraTargetObject(playerid));


fp StoreVectorPath(npcid, Float:x, Float:y, Float:z) {

    vector_push_back_float(npcid, x);
    vector_push_back_float(npcid, y);
    vector_push_back_float(npcid, z);

    return true;
}
fp GetVectorPath(npcid, vectorid, &Float:x, &Float:y, &Float:z) {

    
    vectorid *= 3;

    if(vector_size(npcid) > vectorid) {
    
        x = vector_get_float(npcid, vectorid);
        y = vector_get_float(npcid, vectorid+1);
        z = vector_get_float(npcid, vectorid+2);
    }
}

fs MapAndreasRoundGround(Float:x, Float:y, Float:z, Float: size = 2.0) {

	static Float: xx[7], Float:yy[7];
	
	//
	
	xx[0] = x;
	yy[0] = y;
	
	xx[1] = x+size;
	yy[1] = y;
	
	xx[2] = x+size;
	yy[2] = y+size;
	
	xx[3] = x;
	yy[3] = y+size;
	
	//
	
	xx[4] = x-size;
	yy[4] = y;

	xx[5] = x-size;
	yy[5] = y-size;

	xx[6] = x;
	yy[6] = y-size;


	return
		DiagonalRoute(x, y, z, xx[1],yy[1],z, .maxSteps = 15.0) &&
		DiagonalRoute(x, y, z, xx[2],yy[2],z, .maxSteps = 15.0) &&
		DiagonalRoute(x, y, z, xx[3],yy[3],z, .maxSteps = 15.0) &&
		DiagonalRoute(x, y, z, xx[4],yy[4],z, .maxSteps = 15.0) &&
		DiagonalRoute(x, y, z, xx[5],yy[5],z, .maxSteps = 15.0) &&
		DiagonalRoute(x, y, z, xx[6],yy[6],z, .maxSteps = 15.0)
	;
}
