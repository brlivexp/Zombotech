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
	SetPlayerInterior(playerid, 1);
	SetPlayerVirtualWorld(playerid, playerid);
	SetPlayerPos(playerid, 2531.2891, -1676.7344, 1004.7344);
	SetPlayerFacingAngle(playerid, 0.0);
	InterpolateCameraPos(playerid, 2536.0066, -1674.4677, 1017.0624, 2532.0164, -1674.8923, 1016.7307, 7000, CAMERA_MOVE);
	InterpolateCameraLookAt(playerid, 2537.0039, -1674.4753, 1016.9648, 2531.0171, -1674.8708, 1016.5422, 9000, CAMERA_MOVE);
	return 1;
}
