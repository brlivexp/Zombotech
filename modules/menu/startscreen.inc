ShowPlayerStartScreen(playerid)
{
	for(new i; i < 30; i++) TextDrawShowForPlayer(playerid, StartScreenStatic[i]);
	return 1;
}

HidePlayerStartScreen(playerid)
{
	for(new i; i < 30; i++) TextDrawHideForPlayer(playerid, StartScreenStatic[i]);
	return 1;
}


