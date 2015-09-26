ShowPlayerCreditsMenu(playerid)
{
	HidePlayerStartScreen(playerid);
	PlayerTextDrawSetString(playerid, MainText[playerid][0], "Credits!");
	PlayerTextDrawSetString(playerid, MainText[playerid][1], "Thanks to everybody here this server exists.~n~What about say thank you to them?~n~Start thanking ~g~~h~Kalcor~w~ for creating SA:MP.");
	for(new i; i < 21; i++) TextDrawShowForPlayer(playerid, CreditScreenStatic[i]);
	for(new j; j < 2; j++) PlayerTextDrawShow(playerid, MainText[playerid][j]);
	return 1;
}

HidePlayerCreditsMenu(playerid)
{
	for(new i; i < 21; i++) TextDrawHideForPlayer(playerid, CreditScreenStatic[i]);
	return 1;
}