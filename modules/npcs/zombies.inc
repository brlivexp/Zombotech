#include "../modules/npcs/zombiesdata.inc"
#include "../modules/npcs/zombiesutils.inc"

GenerateZombies()
{
	print("Preparing zombies data...");
	for(new c; c < MAX_ZOMBIES; c++)
	{
		new skinid = ZombieSkins[MRandom(sizeof ZombieSkins)];

		ZombieInfo[c][zombie_type] = ZombieClassInfo[skinid][ZombieTypeID];
		ZombieInfo[c][zombie_health] = ZombieClassInfo[skinid][DefaultHealth];
		ZombieInfo[c][zombie_armour] = ZombieClassInfo[skinid][DefaultArmour];
		ZombieInfo[c][zombie_skin] = skinid;
		ZombieInfo[c][zombie_status] = ZOMBIE_STATUS_NONE;
	}
	print("Generating zombies...");

	for(new z; z < MAX_ZOMBIES; z++)
		SetTimerEx("ConnectZombie", 1700, false, "i", z);
	return 1;
}

fp ConnectZombie(z)
{
	new strname[24];
	format(strname, 24, "Zombie[%d]", z);
	ZombieInfo[z][zombie_npcid] = ConnectRNPC(strname);
	return 1;
}

OnZombieSpawn(playerid)
{
	SetPlayerPos(playerid, proxSpawn[playerid][0],proxSpawn[playerid][1],proxSpawn[playerid][2]+1.0);
	SetPlayerSkin(playerid, ZombieInfo[playerid][zombie_skin]);
	SetPlayerHealth(playerid, ZombieInfo[playerid][zombie_health]);
	SetPlayerArmour(playerid, ZombieInfo[playerid][zombie_armour]);

	new skinid = ZombieInfo[playerid][zombie_skin];

	for(new a; a < MAX_ATTACHMENTS; a++)
	{
		SetPlayerAttachedObject(playerid, a, 
		AttachmentSkinInfo[skinid][a][AttachmentModel],
		AttachmentSkinInfo[skinid][a][AttachmentBone],
		AttachmentSkinInfo[skinid][a][AttachmentPosX],
		AttachmentSkinInfo[skinid][a][AttachmentPosY],
		AttachmentSkinInfo[skinid][a][AttachmentPosZ],
		AttachmentSkinInfo[skinid][a][AttachmentRotX],
		AttachmentSkinInfo[skinid][a][AttachmentRotY],
		AttachmentSkinInfo[skinid][a][AttachmentRotZ],
		AttachmentSkinInfo[skinid][a][AttachmentSizeX],
		AttachmentSkinInfo[skinid][a][AttachmentSizeY],
		AttachmentSkinInfo[skinid][a][AttachmentSizeZ],
		0xFF << 24 | AttachmentSkinInfo[skinid][a][AttachmentColor1],
		0xFF << 24 | AttachmentSkinInfo[skinid][a][AttachmentColor2]);		
	}
	SetPlayerPos(playerid, proxSpawn[playerid][0],proxSpawn[playerid][1],proxSpawn[playerid][2]+1.0);
	
	//alpha testing - move to movement states
	

	KillTimer(ZombieInfo[playerid][zombie_update_timer]);
	ZombieInfo[playerid][zombie_update_timer] = SetTimerEx("OnZombieUpdate", 500, true, "i", playerid);
	return 1;
}

fp OnZombieUpdate(playerid)
{
	switch(ZombieInfo[playerid][zombie_status])
	{
		case ZOMBIE_STATUS_NONE:
		{
			foreach(new i : Player)
			{
				if(!IsPlayerNPC(i))
				{

					
					new Float:p[3];
					GetPlayerPos(ZombieInfo[playerid][zombie_npcid], p[0], p[1], p[2]);
					new type = ZombieInfo[playerid][zombie_skin];
					if(IsPlayerInRangeOfPoint(i, ZombieClassInfo[type][DefaultDetectionRadius], p[0], p[1], p[2])) return SetZombieToFollowPlayer(playerid, i);
				}
			}
		}
		case ZOMBIE_STATUS_STOPPED:
		{

		}
		case ZOMBIE_STATUS_ROAMING:
		{

		}
		case ZOMBIE_STATUS_FOLLOWING:
		{

		}
		case ZOMBIE_STATUS_BLOCKED:
		{

		}
		case ZOMBIE_STATUS_BITING:
		{

		}
		case ZOMBIE_STATUS_DEAD:
		{

		}
		case ZOMBIE_STATUS_CALCULATING:
		{

		}
	}
	return 1;
}

SetZombieToFollowPlayer(zombieid, playerid)
{
	ApplyAnimation(ZombieInfo[zombieid][zombie_npcid], "PED", "WALK_DRUNK", 4.1, 1, 1, 1, 0, 0, 2);
	//target vars
	new Float:tPosX, Float:tPosY, Float:tPosZ;
	//zombie vars
	new Float:zPosX, Float:zPosY, Float:zPosZ;
	//get peds data
	GetPlayerPos(zombieid, zPosX, zPosY, zPosZ);
	GetPlayerPos(playerid, tPosX, tPosY, tPosZ);	
	
	MoveRNPC(ZombieInfo[zombieid][zombie_npcid], tPosX, tPosY, tPosZ, MOVE_SPEED_RUN);
			
	return 1;
}