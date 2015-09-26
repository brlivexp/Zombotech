enum PlayerData
{
	pid,
	name[24],
	password[20],
	mail[64],
	adminlevel,
	kills,
	deaths,
	zombiekills,
	level,
	experience,
	Float:health,
	Float:kevlar,
	Float:pos_x,
	Float:pos_y,
	Float:pos_z,
	Float:pos_a,
	virtualworld,
	interior,
	lastlogin,
	vipcoins,
	bagtype,
	bool:logged,
	bool:RequestingClass
}
new PlayerInfo[MAX_PLAYERS][PlayerData];

PlayerFileLoad(playerid, pname[])
{
	new query[256];
	
	mysql_format(MySQL, query, sizeof(query), "SELECT * FROM `users` WHERE `name` = '%s';", pname);
	mysql_tquery(MySQL, query, "OnPlayerFileLoad", "i", playerid);
	return 1;
}


PlayerFileRegisterLoad(playerid, pname[])
{
	new query[256];
	mysql_format(MySQL, query, sizeof(query), "SELECT * FROM `users` WHERE `name` = '%s' LIMIT 1;", pname);
	mysql_tquery(MySQL, query, "OnPlayerFileLoad", "i", playerid);
	return 1;
}

forward OnPlayerFileLoad(playerid);
public OnPlayerFileLoad(playerid)
{
    if(cache_num_rows()) 
    {		
		PlayerInfo[playerid][pid] = cache_get_field_content_int(0, "id");	
		cache_get_field_content(0, "password", PlayerInfo[playerid][password], MySQL, 32);
		cache_get_field_content(0, "name", PlayerInfo[playerid][name], MySQL, 24);
		cache_get_field_content(0, "mail", PlayerInfo[playerid][mail], MySQL, 64);
		PlayerInfo[playerid][adminlevel] = cache_get_field_content_int(0, "adminlevel");
		PlayerInfo[playerid][kills] = cache_get_field_content_int(0, "kills");
		PlayerInfo[playerid][deaths] = cache_get_field_content_int(0, "deaths");
		PlayerInfo[playerid][zombiekills] = cache_get_field_content_int(0, "zombiekills");
		PlayerInfo[playerid][level] = cache_get_field_content_int(0, "level");
		PlayerInfo[playerid][experience] = cache_get_field_content_int(0, "experience");
		PlayerInfo[playerid][health] = cache_get_field_content_float(0, "health");
		PlayerInfo[playerid][kevlar] = cache_get_field_content_float(0, "kevlar");
		PlayerInfo[playerid][pos_x] = cache_get_field_content_float(0, "pos_x");
		PlayerInfo[playerid][pos_y] = cache_get_field_content_float(0, "pos_y");
		PlayerInfo[playerid][pos_z] = cache_get_field_content_float(0, "pos_z");
		PlayerInfo[playerid][pos_a] = cache_get_field_content_float(0, "pos_a");
		PlayerInfo[playerid][virtualworld] = cache_get_field_content_int(0, "virtualworld");
		PlayerInfo[playerid][interior] = cache_get_field_content_int(0, "interior");
		PlayerInfo[playerid][lastlogin] = cache_get_field_content_int(0, "lastlogin");
		PlayerInfo[playerid][vipcoins] = cache_get_field_content_int(0, "vipcoins");
		PlayerInfo[playerid][bagtype] = cache_get_field_content_int(0, "bagtype");
		HidePlayerMainMenu(playerid);
		HidePlayerLoginMenu(playerid);
    }
	return 1;
}

VerifyPlayerLogin(playerid, nickname[], player_password[])
{
	new query[256], HashedPass[32];
	SHA256_PassHash(player_password, "ztah", HashedPass, sizeof HashedPass);
	mysql_format(MySQL, query, 256, "SELECT * FROM `users` WHERE `name` = '%s' AND `password` = '%s'", nickname, HashedPass);
	new Cache:result = mysql_query(MySQL, query, true);
	
	if(cache_num_rows())
	{	
		PlayerInfo[playerid][logged] = true;
		PlayerFileLoad(playerid, nickname);
		SetPlayerCameraToSpawn(playerid);
		TogglePlayerSpectating(playerid, false);
		SetPVarInt(playerid, "SpawnLiberado",1);
		OnPlayerRequestClass(playerid, 0);
		SetPlayerName(playerid, nickname);
		return cache_delete(result);
	}
	cache_delete(result);
	return SendInfoText(playerid, "Login Failure", "We couldn't find an account with these info, please, check your details. If you forgot your password you can recover it clicking on the ~r~recover~w~ button below.", 7000);
}

forward SaveAccounts();
public SaveAccounts()
{
	foreach(new i : Player)
	{
		if(PlayerInfo[i][RequestingClass] || !PlayerInfo[i][logged]) continue;
		if(!IsPlayerNPC(i))
			SetTimerEx("SavePlayer", 150 * i, false, "i", i);
	}
	
	return 1;
}

forward SavePlayer(playerid);
public SavePlayer(playerid) return PlayerFileSave(playerid);

PlayerFileSave(playerid)
{
	GetPlayerPos(playerid, PlayerInfo[playerid][pos_x],	PlayerInfo[playerid][pos_y], PlayerInfo[playerid][pos_z]);
	GetPlayerFacingAngle(playerid, PlayerInfo[playerid][pos_a]);
	GetPlayerHealth(playerid, PlayerInfo[playerid][health]);
	GetPlayerArmour(playerid, PlayerInfo[playerid][kevlar]);

	new query[1536];
	mysql_format(MySQL, query, 1024, "UPDATE `users` SET `adminlevel` = %d, `kills` = %d, `deaths` = %d, `zombiekills` = %d, `level` = %d, `experience` = %d, `health` = '%f', `kevlar`= '%f', `pos_x` = %f, `pos_y` = %f, `pos_z` = %f, `pos_a` = %f, `virtualworld` = %d, `interior` = %d, `lastlogin` = %d, `vipcoins` = %d, `bagtype` = %d WHERE `id` = %d;",
	PlayerInfo[playerid][adminlevel],
	PlayerInfo[playerid][kills],
	PlayerInfo[playerid][deaths],
	PlayerInfo[playerid][zombiekills],
	PlayerInfo[playerid][level],
	PlayerInfo[playerid][experience],
	PlayerInfo[playerid][health],
	PlayerInfo[playerid][kevlar],
	PlayerInfo[playerid][pos_x],
	PlayerInfo[playerid][pos_y],
	PlayerInfo[playerid][pos_z],
	PlayerInfo[playerid][pos_a],
	PlayerInfo[playerid][virtualworld],
	PlayerInfo[playerid][interior],
	gettime(),
	PlayerInfo[playerid][vipcoins],
	PlayerInfo[playerid][bagtype],
	PlayerInfo[playerid][pid]);

	mysql_tquery(MySQL, query, "", "");

	SavePlayerItems(playerid);
	return 1;
}


LoadPlayerSavedData(playerid)
{
	SetPlayerPos(playerid, PlayerInfo[playerid][pos_x], PlayerInfo[playerid][pos_y], PlayerInfo[playerid][pos_z]);
	SetPlayerFacingAngle(playerid, PlayerInfo[playerid][pos_a]);
	SetPlayerVirtualWorld(playerid, PlayerInfo[playerid][virtualworld]);
	SetPlayerInterior(playerid, PlayerInfo[playerid][interior]);
	return 1;
}