ShowCustomHUDForPlayer(playerid)
{
	for(new k; k < 46; k++) TextDrawShowForPlayer(playerid, HudText[playerid][k]);
	for(new t; t < 4; t++)TextDrawShowForPlayer(playerid, LogoTxd[playerid][t]);
	ShowPlayerProgressBar(playerid, LevelBar[playerid]);
	for(new b; b < 5; b++) ShowPlayerProgressBar(playerid, NeedsBar[playerid][b]);
	return 1;
}

