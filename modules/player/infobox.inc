forward HideInfoBox(playerid);

new InfoBoxTimer[MAX_PLAYERS];

SendInfoText(playerid, title[], text[], time)
{
	new string[256];
	format(string, 256, "%s", text);
	new size = strlen(text);
	if(size > 45) strins(string, "~n~", 45, 181);
	if(size > 90) strins(string, "~n~", 90, 181);
	if(size > 135) strins(string, "~n~", 135, 181);
	if(size >= 180) strins(string, "~n~", 180, 181);

	PlayerTextDrawSetString(playerid, InfoBoxText[playerid][4], title);
	PlayerTextDrawSetString(playerid, InfoBoxText[playerid][5], string);
	for(new j; j < 9; j++) PlayerTextDrawShow(playerid, InfoBoxText[playerid][j]);	
	KillTimer(InfoBoxTimer[playerid]);
	InfoBoxTimer[playerid] = SetTimerEx("HideInfoBox", time ? time : 7000, false, "i", playerid);
	return 1;
}

public HideInfoBox(playerid)
{
	KillTimer(InfoBoxTimer[playerid]);
	InfoBoxTimer[playerid] = -1;
	for(new j; j < 9; j++) PlayerTextDrawHide(playerid, InfoBoxText[playerid][j]);
	return 1;
}

ClearInfoBoxData(playerid)
{
	KillTimer(InfoBoxTimer[playerid]);
	InfoBoxTimer[playerid] = -1;
	return 1;
}