#define ZOMBIE_STATUS_NONE -1
#define ZOMBIE_STATUS_STOPPED 0
#define ZOMBIE_STATUS_ROAMING 1
#define ZOMBIE_STATUS_FOLLOWING 2
#define ZOMBIE_STATUS_BLOCKED 3
#define ZOMBIE_STATUS_BITING 4 
#define ZOMBIE_STATUS_DEAD 5
#define ZOMBIE_STATUS_CALCULATING 6

#define ZOMBIE_TYPE_INVALID 0
#define ZOMBIE_TYPE_CIVILIAN 1
#define ZOMBIE_TYPE_MILITARY 2
#define ZOMBIE_TYPE_POLICE 3
#define ZOMBIE_TYPE_FIREFIGHTER 4
#define ZOMBIE_TYPE_HOMELESS 5

#define COLLISION_TYPE_STUMBLE 0
#define COLLISION_TYPE_STOP 1

#define MAX_ZOMBIES (10)
#define MAX_ATTACHMENTS 10
#define MAX_SKINS 	211

#define FNULL 0.0

#define RandomVelocity (float(MRandom(40)) * 0.0001)

#define MOVE_SPEED_SPRINT			(0.0095)
#define MOVE_SPEED_RUN				(0.0057)
#define MOVE_SPEED_WALK				(0.0025)

enum ZombieClassData
{
	ZombieTypeID,
	Float:DefaultHealth,
	Float:DefaultArmour,
	Float:DefaultMaxDamage,
	Float:DefaultMinDamage,
	Float:DefaultResistance,
	Float:DefaultMaxLeapHeight,
	Float:DefaultDetectionRadius,
	Float:DefaultMoveSpeed,
	bool:HasExtraAttachments
};
new ZombieClassInfo[MAX_SKINS][ZombieClassData];

new ZombieSkins[] = 
{
	4,
	162
};

enum AttachmentSkinData
{
	AttachmentModel,
	AttachmentBone,
	Float:AttachmentPosX,
	Float:AttachmentPosY,
	Float:AttachmentPosZ,
	Float:AttachmentRotX,
	Float:AttachmentRotY,
	Float:AttachmentRotZ,
	Float:AttachmentSizeX,
	Float:AttachmentSizeY,
	Float:AttachmentSizeZ,
	AttachmentColor1,
	AttachmentColor2
};
new AttachmentSkinInfo[MAX_SKINS][MAX_ATTACHMENTS][AttachmentSkinData];

enum ZombiesData
{
	zombie_npcid,
	zombie_type,
	zombie_skin,
	zombie_attachment[MAX_ATTACHMENTS],//SetPlayerAttached object - has bone
	zombie_extra_attachments[MAX_ATTACHMENTS],//AttachObjectToPlayer - doesn't have bone (useful for torso items)
	Float:zombie_health,
	Float:zombie_armour,//used by police zombies
	zombie_status,//calculating, following, dead, stopped, blocked, biting, roaming
	zombie_update_timer,
	zombie_targetplayer,
	zombie_target_body,//used for dead bodies
	Float:zombie_follow_vector[3],
	bool:playerstreamed[MAX_PLAYERS],
	Float:zombie_collision_vector[3],
	zombie_collision_type
};
new ZombieInfo[MAX_ZOMBIES][ZombiesData];

LoadZombieSkins()
{	
	//skin 4
	SetupZombieSkinData(4, 0, 3003, 2, 0.119032, 0.077540, -0.035783, 0.000000, 0.000000, 0.000000, 0.400000, 0.400000, 0.400000, 0xFFFFFF, 0xFFFFFF);
	SetupZombieSkinData(4, 1, 3003, 2, 0.115167, 0.078132, 0.033312, 0.000000, 0.000000, 0.000000, 0.400000, 0.400000, 0.400000, 0xFFFFFF, 0xFFFFFF);
	SetupZombieSkinData(4, 2, 2806, 1, -0.060283, 0.155969, 0.006858, 90.000000, 351.857879, 110.000000, 0.300000, 0.300000, 0.300000, 0xAF111C, 0xAF111C);
	SetupZombieSkinData(4, 3, 2806, 1, 0.116303, 0.117782, 0.062566, 90.000000, 351.857879, 110.000000, 0.300000, 0.300000, 0.300000 , 0xAF111C, 0xAF111C);
	SetupZombieSkinData(4, 4, 2806, 1, 0.130433, 0.120186, -0.053575, 268.207611, 9.505919, 108.599533, 0.300000, 0.300000, 0.300000, 0xAF111C, 0xAF111C);
	SetupZombieSkinData(4, 5, 2806, 18, 0.025855, -0.071688, -0.047783, 190.000000, 15.000000, 99.000000, 0.100000, 0.100000, 0.100000, 0xAF111C, 0xAF111C);
	SetupZombieSkinData(4, 6, 2804, 7, 0.333616, 0.078171, 0.014960, 61.066390, 357.074951, 90.000000, 0.400000, 0.600000, 0.400000, 0xAF111C, 0xAF111C);
	SetupZombieSkinData(4, 7, 2804, 8, 0.333616, 0.044793, -0.067208, 270.000000, 23.960044, 90.000000, 0.400000, 0.600000, 0.400000, 0xAF111C, 0xAF111C);
	SetupZombieSkinData(4, 8, 2804, 12, 0.233839, 0.032086, -0.000254, 270.000000, 1.050521, 90.000000, 0.300000, 0.600000, 0.400000, 0xAF111C, 0xAF111C);
	SetupZombieSkinData(4, 9, 2804, 12, 0.256693, -0.064328, -0.009049, 270.000000, 350.445190, 90.000000, 0.300000, 0.600000, 0.400000, 0xAF111C, 0xAF111C);	
	
	//skin 162
	SetupZombieSkinData(162, 0, 3003, 2, 0.085594, 0.082489, 0.028680, 0.000000, 0.000000, 0.000000, 0.613528, 0.576035, 0.475660, 0xFFFFFF, 0xFFFFFF ); // k_poolballcue - olho esquerdo
	SetupZombieSkinData(162, 1, 3003, 2, 0.082179, 0.079389, -0.033194, 345.747283, 63.987533, 0.000000, 0.613528, 0.576035, 0.475660, 0xFFFFFF, 0xFFFFFF); // k_poolballcue - olho direito
	SetupZombieSkinData(162, 2, 2804, 1, 0.099359, 0.138227, -0.014541, 256.316284, 7.421461, 296.197753, 0.669468, 0.600000, 0.579540, 0xAF111C, 0xAF111C ); // CJ_MEAT_1 - peito direito
	SetupZombieSkinData(162, 3, 2804, 1, 0.086654, 0.138227, 0.008487, 97.806625, 359.692108, 296.197753, 0.669468, 0.600000, 0.579540, 0xAF111C, 0xAF111C); // CJ_MEAT_1 - peito esquerdo
	SetupZombieSkinData(162, 4, 2806, 1, 0.000000, 0.152520, 0.000000, 263.708404, 0.000000, 287.533843, 0.344415, 0.200000, 0.393224, 0xAF111C, 0xAF111C ); // CJ_MEAT_2 - estomago
	SetupZombieSkinData(162, 5, 2806, 3, 0.086628, 0.020558, 0.030311, 148.828826, 0.000000, 286.031402, 0.229553, 0.200000, 0.306282, 0xAF111C, 0xAF111C ); // CJ_MEAT_2 - ombro esquerdo
	SetupZombieSkinData(162, 6, 2806, 4, 0.155685, 0.011566, -0.042313, 132.740859, 96.022956, 211.319015, -0.098667, 0.091859, -0.909853, 0xAF111C, 0xAF111C ); // CJ_MEAT_2 - ombro direito
	SetupZombieSkinData(162, 7, 2806, 2, 0.018751, 0.052789, -0.053213, 16.325899, 12.536803, 272.266479, -0.125444, 0.100000, -0.127154, 0xAF111C, 0xAF111C ); // CJ_MEAT_2 - bochecha direita
	SetupZombieSkinData(162, 8, 2806, 2, 0.033698, 0.043727, 0.0, 354.842315, 354.532623, 285.991363, -0.125444, 0.100000, -0.127154, 0xAF111C, 0xAF111C ); // CJ_MEAT_2 - bochecha esq
	SetupZombieSkinData(162, 9, 2804, 1, 0.050000, -0.02000, 0.00, 87.0, -19.0, -63.0, 0.62, 0.68, 0.62, 0xAF111C, 0xAF111C);
	return 1;
}



LoadZombiesClasses()
{
	SetupZombiesClass(4, ZOMBIE_TYPE_HOMELESS, 80.0, 0.0, 35.0, 15.0, 5.0, 1.2, 40.0, MOVE_SPEED_RUN, false);
	SetupZombiesClass(162, ZOMBIE_TYPE_HOMELESS, 80.0, 0.0, 35.0, 15.0, 5.0, 1.2, 40.0, MOVE_SPEED_RUN, false);
	return 1;
}

SetupZombieSkinData(skinid, index, model, bone, Float:PosX, Float:PosY, Float:PosZ, Float:RotX, Float:RotY, Float:RotZ, Float:SizeX, Float:SizeY, Float:SizeZ, color1, color2)
{
	AttachmentSkinInfo[skinid][index][AttachmentModel] = model;
	AttachmentSkinInfo[skinid][index][AttachmentBone] = bone;
	AttachmentSkinInfo[skinid][index][AttachmentPosX] = PosX;
	AttachmentSkinInfo[skinid][index][AttachmentPosY] = PosY;
	AttachmentSkinInfo[skinid][index][AttachmentPosZ] = PosZ;
	AttachmentSkinInfo[skinid][index][AttachmentRotX] = RotX;
	AttachmentSkinInfo[skinid][index][AttachmentRotY] = RotY;
	AttachmentSkinInfo[skinid][index][AttachmentRotZ] = RotZ;
	AttachmentSkinInfo[skinid][index][AttachmentSizeX] = SizeX;
	AttachmentSkinInfo[skinid][index][AttachmentSizeY] = SizeY;
	AttachmentSkinInfo[skinid][index][AttachmentSizeZ] = SizeZ;
	AttachmentSkinInfo[skinid][index][AttachmentColor1] = color1;
	AttachmentSkinInfo[skinid][index][AttachmentColor2] = color2;
	return 1;
}

SetupZombiesClass(skinid, classid, Float:Health, Float:Armour, Float:MaxDamage, Float:MinDamage, Float:Resistance, Float:MaxLeapHeight, Float:DetectionRadius, Float:MoveSpeed, bool:ExtraAttachments)
{
	ZombieClassInfo[skinid][ZombieTypeID] = classid;
	ZombieClassInfo[skinid][DefaultHealth] = Health;
	ZombieClassInfo[skinid][DefaultArmour] = Armour;
	ZombieClassInfo[skinid][DefaultMaxDamage] = MaxDamage;
	ZombieClassInfo[skinid][DefaultMinDamage] = MinDamage;
	ZombieClassInfo[skinid][DefaultResistance] = Resistance;
	ZombieClassInfo[skinid][DefaultMaxLeapHeight] = MaxLeapHeight;
	ZombieClassInfo[skinid][DefaultDetectionRadius] = DetectionRadius;
	ZombieClassInfo[skinid][DefaultMoveSpeed] = MoveSpeed;
	ZombieClassInfo[skinid][HasExtraAttachments] = ExtraAttachments;
	return 1;
}

bool:IsValidZombieSkin(skinid)
{
	if(ZombieClassInfo[skinid][ZombieTypeID] == ZOMBIE_TYPE_INVALID) return false;
	return true;
}