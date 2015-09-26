#define INVALID_FIELD_ID		-1
#define	FIELD_LOGIN_NAME		0
#define FIELD_LOGIN_PASSWORD 	1
#define	FIELD_REGISTER_NAME		2
#define FIELD_REGISTER_PASSWORD	3
#define	FIELD_REGISTER_REPASSWORD	4
#define FIELD_REGISTER_MAIL		5

#define MENU_LOGIN		0
#define MENU_REGISTER	1
#define MENU_OPTIONS	2
#define MENU_ABOUT		3
#define	MENU_CREDITS	4
#define MENU_BACK		5

#define DIALOG_LOGIN_NAME		101
#define	DIALOG_LOGIN_PASSWORD	102


enum PlayerLoginData
{
	 bool:Selecting,
	 bool:FirstSpawn,
	 PlayerCurrentMenu,
	 PlayerLoginName[24],
	 PlayerLoginPassword[16],
	 PlayerRegisterName[24],
	 PlayerRegisterPassword[16],
	 PlayerRegisterRePassword[16],
	 PlayerRegisterMail[32]
}
new PlayerLoginInfo[MAX_PLAYERS][PlayerLoginData];

CleanPlayerLoginData(playerid)
{
	PlayerLoginInfo[playerid][Selecting] = false;
	PlayerLoginInfo[playerid][PlayerCurrentMenu] = MENU_BACK;
	PlayerLoginInfo[playerid][PlayerLoginName][0] = EOS;
	PlayerLoginInfo[playerid][PlayerLoginPassword][0] = EOS;
	PlayerLoginInfo[playerid][PlayerRegisterName][0] = EOS;
	PlayerLoginInfo[playerid][PlayerRegisterPassword][0] = EOS;
	PlayerLoginInfo[playerid][PlayerRegisterRePassword][0] = EOS;
	PlayerLoginInfo[playerid][PlayerRegisterMail][0] = EOS;

	
	return 1;
}

OnPlayerInputField(playerid, field, inputtext[])
{ 
	switch(field)
	{
		case INVALID_FIELD_ID: return 1;
		case FIELD_LOGIN_NAME:
		{			
			format(PlayerLoginInfo[playerid][PlayerLoginName], 24, "%s", inputtext);			
			PlayerTextDrawSetString(playerid, LoginScreenText[playerid][0], inputtext);
			if(PlayerLoginInfo[playerid][PlayerCurrentMenu] == MENU_LOGIN) PlayerTextDrawShow(playerid, LoginScreenText[playerid][0]);
			return 1;
		}
		case FIELD_LOGIN_PASSWORD:
		{
			format(PlayerLoginInfo[playerid][PlayerLoginPassword], 24, "%s", inputtext);
			PasswordEncode(inputtext, strlen(inputtext));
			PlayerTextDrawSetString(playerid, LoginScreenText[playerid][1], inputtext);
			if(PlayerLoginInfo[playerid][PlayerCurrentMenu] == MENU_LOGIN) PlayerTextDrawShow(playerid, LoginScreenText[playerid][1]);
			return 1;
		}
		case FIELD_REGISTER_NAME:
		{
			format(PlayerLoginInfo[playerid][PlayerRegisterName], 24, "%s", inputtext);
			PlayerTextDrawSetString(playerid, RegisterScreenText[playerid][0], inputtext);
			if(PlayerLoginInfo[playerid][PlayerCurrentMenu] == MENU_REGISTER) PlayerTextDrawShow(playerid, RegisterScreenText[playerid][0]);
		}
		case FIELD_REGISTER_PASSWORD:
		{
			format(PlayerLoginInfo[playerid][PlayerRegisterPassword], 24, "%s", inputtext);
			PasswordEncode(inputtext, strlen(inputtext));
			PlayerTextDrawSetString(playerid, RegisterScreenText[playerid][1], inputtext);
			if(PlayerLoginInfo[playerid][PlayerCurrentMenu] == MENU_REGISTER) PlayerTextDrawShow(playerid, RegisterScreenText[playerid][1]);
			return 1;
		}
		case FIELD_REGISTER_REPASSWORD:
		{
			format(PlayerLoginInfo[playerid][PlayerRegisterRePassword], 24, "%s", inputtext);
			PasswordEncode(inputtext, strlen(inputtext));
			PlayerTextDrawSetString(playerid, RegisterScreenText[playerid][2], inputtext);
			if(PlayerLoginInfo[playerid][PlayerCurrentMenu] == MENU_REGISTER) PlayerTextDrawShow(playerid, RegisterScreenText[playerid][2]);
			return 1;
		}
		case FIELD_REGISTER_MAIL:
		{
			format(PlayerLoginInfo[playerid][PlayerRegisterMail], 32, "%s", inputtext);
			new string[32];
			SubMail(string, inputtext);
			PlayerTextDrawSetString(playerid, RegisterScreenText[playerid][3], string);
			if(PlayerLoginInfo[playerid][PlayerCurrentMenu] == MENU_REGISTER) PlayerTextDrawShow(playerid, RegisterScreenText[playerid][3]);
			return 1;
		}

	}
	return 1;
}

ShowPlayerLoginMenu(playerid)
{
	HidePlayerStartScreen(playerid);
	PlayerTextDrawSetString(playerid, MainText[playerid][0], "Sign In!");
	PlayerTextDrawSetString(playerid, MainText[playerid][1], "Do you already have an account?~n~If yes, fill the boxes below and click on login button.~n~Otherwise, click on back button and create an account...");
	for(new i; i < 2; i++) PlayerTextDrawShow(playerid, MainText[playerid][i]);
	for(new j; j < 23; j++) TextDrawShowForPlayer(playerid, LoginScreenStatic[j]);
	for(new l; l < 2; l++) PlayerTextDrawShow(playerid, LoginScreenText[playerid][l]);
	return 1;
}


HidePlayerLoginMenu(playerid)
{
	for(new j; j < 23; j++) TextDrawHideForPlayer(playerid, LoginScreenStatic[j]);
	for(new l; l < 2; l++) PlayerTextDrawHide(playerid, LoginScreenText[playerid][l]);
	PlayerTextDrawSetString(playerid, MainText[playerid][0], "Welcome!");
	PlayerTextDrawSetString(playerid, MainText[playerid][1], "Hello.~n~Welcome to Zombotech Apocalypse server~n~Select an option below to continue...");
	return 1;
}

PasswordEncode(string[], size)
{	
	for(new s; s <= size; s++)
	{		
		if(s ^ size) string[s] = ']';
		else string[s] = EOS;
	}
	return 1;
}

SubMail(dest[32], source[]) return strmid(dest, source, 0, strfind(source, "@"));