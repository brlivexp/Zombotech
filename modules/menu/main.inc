#include "../modules/menu/startscreen.inc"
#include "../modules/menu/login.inc"
#include "../modules/menu/register.inc"
#include "../modules/menu/credits.inc"

ShowPlayerMainMenu(playerid)
{
	PlayerLoginInfo[playerid][Selecting] = true;
	ShowPlayerStartScreen(playerid);
	PlayerTextDrawSetString(playerid, MainText[playerid][0], "Welcome!");
	PlayerTextDrawSetString(playerid, MainText[playerid][1], "Hello.~n~Welcome to ~r~Zombotech Apocalypse server~n~~w~Select an option below to continue...");
	for(new i=4; i < 9; i++) TextDrawShowForPlayer(playerid, MainStatic[i]);	
	for(new j; j < 2; j++) PlayerTextDrawShow(playerid, MainText[playerid][j]);
	SelectTextDraw(playerid, 0xFF0000FF);
	return 1;
}

HidePlayerMainMenu(playerid)
{
	for(new i; i < 9; i++) TextDrawHideForPlayer(playerid, MainStatic[i]);
	for(new j; j < 2; j++) PlayerTextDrawHide(playerid, MainText[playerid][j]);
	CancelSelectTextDraw(playerid);
	PlayerLoginInfo[playerid][Selecting] = false;
}

OnPlayerSelectMenuOption(playerid, option)
{
	switch(option)
	{
		case MENU_LOGIN: 
		{
			PlayerLoginInfo[playerid][PlayerCurrentMenu] = MENU_LOGIN;
			return ShowPlayerLoginMenu(playerid);
		}
		case MENU_REGISTER:
		{
			PlayerLoginInfo[playerid][PlayerCurrentMenu] = MENU_REGISTER;
			return ShowPlayerRegisterMenu(playerid);
		} 
		case MENU_BACK:
		{
			ShowPlayerStartScreen(playerid);
			HidePlayerLoginMenu(playerid);
			HidePlayerRegisterMenu(playerid);
			HidePlayerCreditsMenu(playerid);
			PlayerLoginInfo[playerid][PlayerCurrentMenu] = MENU_BACK;
		}
		case MENU_CREDITS:
		{			
			PlayerLoginInfo[playerid][PlayerCurrentMenu] = MENU_CREDITS;
			return ShowPlayerCreditsMenu(playerid);
		}
	}
	return 1;
}