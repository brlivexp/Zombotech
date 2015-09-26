forward CreateZombie(npcindex);

public CreateZombie(npcindex)
{
	new string[32];
	format(string, 32, "Zombie[%d]", npcindex);
	ConnectRNPC(string);
	return 1;
}

GenerateZombies()
{
	if(GetServerVarAsInt("maxnpc") < MAX_ZOMBIES) return print("Error: Server maximum npcs is lower than zombies amount!");
	print("Loading server zombies...");
	SendRconCommand("password oaspkoaskposakop");	
	foreach(new playerid : Player)
	{
		Kick(playerid);
	}
	
	new TotalClassSlots[MAX_ZOMBIE_CLASS];//handler

	for(new class; class < MAX_ZOMBIE_CLASSES; class++)
	{
		TotalClassSlots[class] = MAX_ZOMBIES / floatround(ZombieClassInfo[class][SpawnAverage]);
	}
	
	for(new i; i < MAX_ZOMBIES; i++)
	{
		SetTimerEx("CreateZombie", 150 * i, false, "i", i);
	}
	return 1;
}

SetZombieClass(zombieid, classid)
{
	return 1;
}

