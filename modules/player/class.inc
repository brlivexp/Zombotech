LoadClasses()
{
	for(new s = 1; s < 311; s ++)
	{
		if(s == 74 || s == 26) continue;
		AddPlayerClass(s, 999.0, 999.0, 13.0, 0.0, 0, 0, 0, 0, 0, 0);
	}
	return 1;	
}

SetPlayerCameraToSpawn(playerid)
{	
	SetPlayerVirtualWorld(playerid, 131);
	SetPlayerPos(playerid, 369.8813,-2025.9816,7.6719);
	SetPlayerFacingAngle(playerid, 0.0);
	InterpolateCameraPos(playerid, 409.110260, -1999.427978, 32.751544,  369.7387, -2022.0483, 8.9106, 7000, CAMERA_MOVE);
	InterpolateCameraLookAt(playerid, 405.364593, -2002.259521, 31.033386, 369.8813,-2025.9816,7.6719, 9000, CAMERA_MOVE);
	return 1;
}
