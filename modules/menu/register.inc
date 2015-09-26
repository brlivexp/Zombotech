#define DIALOG_REGISTER_NAME		110
#define DIALOG_REGISTER_PASSWORD 	111
#define DIALOG_REGISTER_REPASSWORD	112
#define DIALOG_REGISTER_MAIL		113

ShowPlayerRegisterMenu(playerid)
{
	HidePlayerStartScreen(playerid);
	PlayerTextDrawSetString(playerid, MainText[playerid][0], "Sign Up!");
	PlayerTextDrawSetString(playerid, MainText[playerid][1], "Don't have an account yet?~n~Fill the boxes below to proceed with your registration.");
	for(new i; i < 2; i++) PlayerTextDrawShow(playerid, MainText[playerid][i]);
	for(new p; p < 4; p++) PlayerTextDrawShow(playerid, RegisterScreenText[playerid][p]);
	for(new j; j < 26; j++) TextDrawShowForPlayer(playerid, RegisterScreenStatic[j]);
	
	return 1;
}

HidePlayerRegisterMenu(playerid)
{
	PlayerTextDrawSetString(playerid, MainText[playerid][0], "Welcome!");
	PlayerTextDrawSetString(playerid, MainText[playerid][1], "Hello.~n~Welcome to Zombotech Apocalypse server~n~Select an option below to continue...");

	for(new j; j < 26; j++) TextDrawHideForPlayer(playerid, RegisterScreenStatic[j]);
	for(new p; p < 4; p++) PlayerTextDrawHide(playerid, RegisterScreenText[playerid][p]);
	return 1;
}


forward OnPlayerRegister(playerid);
public OnPlayerRegister(playerid)
{
	if(strlen(PlayerLoginInfo[playerid][PlayerRegisterName])) SetPlayerName(playerid, PlayerLoginInfo[playerid][PlayerRegisterName]);
	else Kick(playerid);
	HidePlayerRegisterMenu(playerid);
	HidePlayerMainMenu(playerid);
	PlayerFileRegisterLoad(playerid, PlayerLoginInfo[playerid][PlayerRegisterName]);
	SetPlayerCameraToSpawn(playerid);
	CleanPlayerLoginData(playerid);
	TogglePlayerSpectating(playerid, false);
	SetPVarInt(playerid, "SpawnLiberado",1);
	OnPlayerRequestClass(playerid, 0);
	PlayerInfo[playerid][logged] = true;
	return 1;
}