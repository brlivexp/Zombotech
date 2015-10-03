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
	SetPlayerVirtualWorld(playerid, playerid);
	SetPlayerPos(playerid, -1951.9847, 709.2784, 46.5625);
	SetPlayerFacingAngle(playerid, 0.0);
	InterpolateCameraPos(playerid, -1940.9475, 729.7084, 46.8430, -1952.1494, 714.9960, 46.9683, 3000,  CAMERA_MOVE);
	InterpolateCameraLookAt(playerid, -1940.9001, 728.7051, 46.7380, -1952.1409, 713.9916, 46.9133, 3000, CAMERA_MOVE);
	return 1;
}
