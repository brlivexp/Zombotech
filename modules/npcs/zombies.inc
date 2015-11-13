#include "../modules/npcs/zombiesdata.inc"
#include "../modules/npcs/zombiesutils.inc"

GenerateZombies()
{
	print("Preparing zombies data...");
	for(new c = MAX_ZOMBIES -1; c >  100; c--)
	{
		new skinid = ZombieSkins[MRandom(sizeof ZombieSkins)];

		ZombieInfo[c][zombie_type] = ZombieClassInfo[skinid][ZombieTypeID];
		ZombieInfo[c][zombie_health] = ZombieClassInfo[skinid][DefaultHealth];
		ZombieInfo[c][zombie_armour] = ZombieClassInfo[skinid][DefaultArmour];
		ZombieInfo[c][zombie_skin] = skinid;
		ZombieInfo[c][zombie_status] = ZOMBIE_STATUS_NONE;
	}
	print("Generating zombies...");

	for(new z = MAX_ZOMBIES -1; z > 100; z--)
	{
		new strname[24];
		format(strname, 24, "Zombie[%d]", z);
		FCNPC_Create(strname);
	}
	return 1;
}

public FCNPC_OnCreate(npcid)
{
    FCNPC_Spawn(npcid, ZombieInfo[npcid][zombie_skin], proxSpawn[npcid][0],proxSpawn[npcid][1],proxSpawn[npcid][2]+1.0);
    SetTimerEx("OnZombieUpdate", 300, true, "i", npcid);
	return 1;
}

public FCNPC_OnSpawn(npcid)
{
	new skinid = ZombieInfo[npcid][zombie_skin];

	for(new a; a < MAX_ATTACHMENTS; a++)
	{
		SetPlayerAttachedObject(npcid, a,
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
	return 1;
}

fp OnZombieUpdate(npcid)
{
	switch(ZombieInfo[npcid][zombie_status])
	{
		case ZOMBIE_STATUS_NONE:
		{
			foreach(new i : Player)
			{
				if(!IsPlayerNPC(i))
				{
					new Float:p[3];
					GetPlayerPos(npcid, p[0], p[1], p[2]);
					new type = ZombieInfo[npcid][zombie_skin];
					if(IsPlayerInRangeOfPoint(i, ZombieClassInfo[type][DefaultDetectionRadius], p[0], p[1], p[2])) return SetZombieToFollowPlayer(npcid, i);
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
	ApplyAnimation(zombieid, "PED", "WALK_DRUNK", 4.1, 1, 1, 1, 0, 0, 2);
	//target vars
	new Float:tPosX, Float:tPosY, Float:tPosZ;
	//zombie vars
	//new Float:zPosX, Float:zPosY, Float:zPosZ;
	//get peds data
	//GetPlayerPos(zombieid, zPosX, zPosY, zPosZ);
	GetPlayerPos(playerid, tPosX, tPosY, tPosZ);

	new Float:speed;
	MRandFloatRange(-0.12123, 0.12123, speed);
	FCNPC_GoTo(zombieid, tPosX, tPosY, tPosZ, MOVE_TYPE_RUN, 4.1, 1, speed);

	return 1;
}
