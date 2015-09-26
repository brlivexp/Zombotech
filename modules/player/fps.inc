new CameraObject[MAX_PLAYERS];

SetPlayerCameraFPS(playerid)
{
	CameraObject[playerid] = CreateObject(18698, 0.0, 0.0, -10.0, 0.0, 0.0, 0.0, 0.1);
	AttachObjectToPlayer(CameraObject[playerid], playerid, 0.11, -0.413, 0.81000, 0.000000, 0.000000, 0.000000);
	AttachCameraToObject(playerid, CameraObject[playerid]);
	return 1;
}