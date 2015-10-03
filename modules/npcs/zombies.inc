#include "../modules/npcs/zombiesdata.inc"

fs GenerateZombies()
{
	for(new i; i < MAX_ZOMBIES; i++)
		SetTimer("CreateZombie", 150 + (i * 2), false);

	return print("Generating zombies...");
}

fp CreateZombie()
{
	ConnectRNPC("Zombie");
	return 1;
}

fs OnZombieConnect(playerid)
{
	new skinid = ZombieSkins[MRandom(sizeof ZombieSkins)];
	//setup skin data for the zombie
	ZombieInfo[playerid][zombie_skin] = skinid;
	ZombieInfo[playerid][zombie_type] = ZombieClassInfo[skinid][ZombieTypeID];
	ZombieInfo[playerid][zombie_health] = ZombieClassInfo[skinid][DefaultHealth];
	ZombieInfo[playerid][zombie_armour] = ZombieClassInfo[skinid][DefaultArmour];
	ZombieInfo[playerid][zombie_status] = ZOMBIE_STATUS_STOPPED;
	ZombieInfo[playerid][zombie_target_body] = INVALID_DEAD_BODY;
	return 1;
}

OnZombieSpawn(playerid)
{
	new skinid = ZombieInfo[playerid][zombie_skin];
	SetPlayerHealth(playerid, ZombieInfo[playerid][zombie_health]);
	SetPlayerArmour(playerid, ZombieInfo[playerid][zombie_armour]);
	SetPlayerSkin(playerid, skinid);

	for(new i; i < 10; i++)
		SetPlayerAttachedObject(playerid, i, 
		AttachmentSkinInfo[skinid][i][AttachmentModel],
		AttachmentSkinInfo[skinid][i][AttachmentBone],
		AttachmentSkinInfo[skinid][i][AttachmentPosX],
		AttachmentSkinInfo[skinid][i][AttachmentPosY],
		AttachmentSkinInfo[skinid][i][AttachmentPosZ],
		AttachmentSkinInfo[skinid][i][AttachmentRotX],
		AttachmentSkinInfo[skinid][i][AttachmentRotY],
		AttachmentSkinInfo[skinid][i][AttachmentRotZ],
		AttachmentSkinInfo[skinid][i][AttachmentSizeX],
		AttachmentSkinInfo[skinid][i][AttachmentSizeY],
		AttachmentSkinInfo[skinid][i][AttachmentSizeZ],
		0xFF << 24 | AttachmentSkinInfo[skinid][i][AttachmentColor1],
		0xFF << 24 | AttachmentSkinInfo[skinid][i][AttachmentColor2]);

	SetPlayerPos(playerid, proxSpawn[playerid][0],proxSpawn[playerid][1],proxSpawn[playerid][2]+1.0);
	return 1;
}

fp OnZombieUpdate(playerid)
{
	return 1;
}