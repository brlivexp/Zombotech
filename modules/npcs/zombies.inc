
fs CreateZombie()
{
	//get a id for the zombies array
	new zombieid = GetPlayerPoolSize() ? GetPlayerPoolSize() + 1 : GetPlayerPoolSize();
	//get a random skin from the list
	new skinid = ZombieSkins[MRand(sizeof ZombieSkins)];
	//setup skin data for the zombie
	ZombiesInfo[zombieid][zombie_skin] = skinid;
	ZombiesInfo[zombieid][zombie_type] = ZombieClassInfo[skinid][ZombieTypeID];
	ZombiesInfo[zombieid][zombie_health] = ZombieClassInfo[skinid][DefaultHealth];
	ZombiesInfo[zombieid][zombie_armour] = ZombieClassInfo[skinid][DefaultArmour];
	ZombiesInfo[zombieid][zombie_armour] = ZombieClassInfo[skinid][DefaultArmour];
	ZombiesInfo[zombieid][zombie_status] = ZOMBIE_STATUS_STOPPED;
	ZombieInfo[zombieid][zombie_target_body] = INVALID_DEAD_BODY;
	//connect NPC
	new strname[24];
	format(strname, "Zombie[%d]");
	ZombiesInfo[zombieid][zombie_npcid] = ConnectRNPC(strname);
	return 1;
}

fp OnZombieUpdate(npcid)
{
	return 1;
}