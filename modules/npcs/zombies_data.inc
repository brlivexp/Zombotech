#define ZOMBIE_STATUS_STOPPED 0
#define ZOMBIE_STATUS_ROAMING 1
#define ZOMBIE_STATUS_FOLLOWING 2
#define ZOMBIE_STATUS_BLOCKED 3
#define ZOMBIE_STATUS_BITING 4 //Biting dead bodies
#define ZOMBIE_STATUS_DEAD 5

#define ZOMBIE_TYPE_CIVILIAN 0
#define ZOMBIE_TYPE_MILITARY 1
#define ZOMBIE_TYPE_POLICE 2
#define ZOMBIE_TYPE_FIREFIGHTER 3
#define ZOMBIE_TYPE_HOMELESS 4


#define MAX_ZOMBIES 100
#define MAX_ATTACHMENTS 10
#define MAX_SKINS 	211

#define FNULL 0.0

#define RandomVelocity (float(MRandom(40)) * 0.0001)

enum AttachmentSkinData
{
	boneid,
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
}
new AttachmentSkinInfo[MAX_SKINS][MAX_ATTACHMENTS][AttachmentSkinData];

enum ZombieData
{
	zombie_type,
	zombie_skin,
	zombie_attachment[MAX_ATTACHMENTS],//SetPlayerAttached object - has bone
	zombie_extra_attachments[MAX_ATTACHMENTS],//AttachObjectToPlayer - doesn't have bone (useful for torso items)
	Float:zombie_health,
	Float:zombie_kevlar,//used by police zombies
	zombie_status,//calculating, following, dead, stopped, blocked, biting, roaming
	zombie_update_timer,
	zombie_targetplayer,
	zombie_target_body,//used for dead bodies
	Float:zombie_follow_vector[3],
	bool:streamed_player[MAX_PLAYERS]
};

new ZombieInfo[MAX_ZOMBIES][ZombiesData];

SetupSkinsAttachments()
{
	//skin 4
	SetZombieSkinData(4, 0, 3003, 2, 0.119032, 0.077540, -0.035783, 0.000000, 0.000000, 0.000000, 0.400000, 0.400000, 0.400000 ); // k_poolballcue - <skin 4 - left blank eyes>
	SetZombieSkinData(4, 1, 3003, 2, 0.115167, 0.078132, 0.033312, 0.000000, 0.000000, 0.000000, 0.400000, 0.400000, 0.400000 ); // k_poolballcue - <skin 4 - right blank eyes>
	SetZombieSkinData(4, 2, 2806, 1, -0.060283, 0.155969, 0.006858, 90.000000, 351.857879, 110.000000, 0.300000, 0.300000, 0.300000 ); // CJ_MEAT_2 - <skin 4 - stomach>
	SetZombieSkinData(4, 3, 2806, 1, 0.116303, 0.117782, 0.062566, 90.000000, 351.857879, 110.000000, 0.300000, 0.300000, 0.300000 ); // CJ_MEAT_2 - <skin 4 - left chest>
	SetZombieSkinData(4, 4, 2806, 1, 0.130433, 0.120186, -0.053575, 268.207611, 9.505919, 108.599533, 0.300000, 0.300000, 0.300000 ); // CJ_MEAT_2 - <skin 4 - right chest>
	SetZombieSkinData(4, 5, 2806, 18, 0.025855, -0.071688, -0.047783, 190.000000, 15.000000, 99.000000, 0.100000, 0.100000, 0.100000 ); // CJ_MEAT_2 - <skin 4 - right jaw>
	SetZombieSkinData(4, 6, 2804, 7, 0.333616, 0.078171, 0.014960, 61.066390, 357.074951, 90.000000, 0.400000, 0.600000, 0.400000 ); // CJ_MEAT_1 - <skin 4 - left thigh>
	SetZombieSkinData(4, 7, 2804, 8, 0.333616, 0.044793, -0.067208, 270.000000, 23.960044, 90.000000, 0.400000, 0.600000, 0.400000 ); // CJ_MEAT_1 - <skin 4 - right thigh>
	SetZombieSkinData(4, 8, 2804, 12, 0.233839, 0.032086, -0.000254, 270.000000, 1.050521, 90.000000, 0.300000, 0.600000, 0.400000 ); // CJ_MEAT_1 - <skin 4 - right calf>
	SetZombieSkinData(4, 9, 2804, 12, 0.256693, -0.064328, -0.009049, 270.000000, 350.445190, 90.000000, 0.300000, 0.600000, 0.400000 ); // CJ_MEAT_1 - <skin 4 - left calf>
}

SetZombieSkinData(skinid, index, model, bone, Float:aX, Float:aY, Float:aZ, Float:aRx, Float:aRy, Float:aRz, Float:aSx, Float:aSy, Float:aSz, &aCol1 = 0xFFFFFFFF, &aCol2 = 0xFFFFFFFF)
{
	AttachmentSkinInfo[skinid][index][boneid] = bone;
	AttachmentSkinInfo[skinid][index][AttachmentPosX] = aX;
	AttachmentSkinInfo[skinid][index][AttachmentPosY] = aY;
	AttachmentSkinInfo[skinid][index][AttachmentPosZ] = aZ;
	AttachmentSkinInfo[skinid][index][AttachmentRotX] = aRx;
	AttachmentSkinInfo[skinid][index][AttachmentRotY] = aRy;
	AttachmentSkinInfo[skinid][index][AttachmentRotZ] = aRz;
	AttachmentSkinInfo[skinid][index][AttachmentSizeX] = aSx;
	AttachmentSkinInfo[skinid][index][AttachmentSizeY] = aSy;
	AttachmentSkinInfo[skinid][index][AttachmentSizeZ] = aSz;
	AttachmentSkinInfo[skinid][index][AttachmentColor1] = aCol1;
	AttachmentSkinInfo[skinid][index][AttachmentColor2] = aCol2;
 	return 1;
}