#define MAX_DEAD_BODIES 1000
#define MAX_RANDOM_BODIES 600
#define MAX_PLAYER_BODIES 400

enum DeadBodyData
{
	deadbodyid,
	deadskin,
	deadanimlib[32],
	dadanimname[32],
	Float:deadPosX,
	Float:deadPosY,
	Float:deadPosZ,
	Float:deadAngle
};
new DeadBodyInfo[MAX_DEAD_BODIES][DeadBodyData];

enum DeadAnimData
{
	danimlib[32],
	danimname[32]
};

new DeadBodyAnimList[][DeadAnimData] =
{
	{"CRACK", "CRCKIDLE1"},
	{"CRACK", "CRCKIDLE2"},
	{"CRACK", "CRCKIDLE3"},
	{"CRACK", "CRCKIDLE4"}
};

stock SetupRandomDeadBodies()
{
	for(new i; i < MAX_RANDOM_BODIES; i++)
	{
		new index = MRandom(sizeof PedNodes);
		new animindex = random(sizeof DeadBodyAnimList);
		new Float:aAxis;
		MRandFloatRange(0.0, 270.0, aAxis);

		SetupDeadBody(i, MRandRange(7, 200), animindex, PedNodes[index][PNodeX], PedNodes[index][PNodeY], PedNodes[index][PNodeZ], aAxis);
	}	
	return 1;
}

stock SetupDeadBody(actorid, skinid, animindex, Float:posX, Float:posY, Float:posZ, Float:angle)
{
	DeadBodyInfo[actorid][deadbodyid] = CreateActor(skinid, posX, posY, posZ, angle);
	PreloadActorAnimations(actorid);
	SetTimerEx("SetupDeadBodyAnim", 2000, false, "ii", actorid, animindex);
	return 1;
}

fp SetupDeadBodyAnim(actorid, animindex)
{
	if(!IsValidActor(DeadBodyInfo[actorid][deadbodyid]))
		return printf("server skipped invalid actor %d", actorid);

	ApplyActorAnimation(DeadBodyInfo[actorid][deadbodyid], DeadBodyAnimList[animindex][danimlib], DeadBodyAnimList[animindex][danimname], 4.1, 1, 1, 1, 1, 0);
	return 1;
}