/*
	Classes

		0-Walkers
			-Movement speed: normal (walk)
			-Damage type: punch/bite
			-Damage amount: 10 ~ 20 hp 
			-Night extra damage: +5
			-Leap size: 0.4m 
			-Detection radius: 40.0m (medium)
			-Special power: extra health (+5)
			-Special radius: -

		1-Infecteds
			-Movement speed: fast (run)
			-Damage type: punch/bite
			-Damage amount: 15 ~ 25 hp (short)
			-Night extra damage: +15
			-Leap size: 1.5m (medium)
			-Detection radius: 70.0m (large)
			-Extra power: Speed & leap increased (+10)
			-Special radius: -

		2-Purses
			-Movement speed: slow (walk)
			-Damage type: Body explosion (+auto-death)
			-Damage amount: 80 ~ 100 hp/player radius (large)
			-Night extra damage: +30
			-Leap size: 0.3m (short)
			-Detection radius: 50.0m (medium)
			-Extra power: None		

		3-Thugs
			-Movement speed: very slow (walk)
			-Damage type: Strong delayed punch (3sec)
			-Damage amount: 50 ~ 70 hp (large)
			-Night extra damage: +20
			-Leap size: 0.5m (short)
			-Detection radius: 35.0m (short)
			-Extra power: +10% damage
			-Special amount: -
*/

#define MAX_ZOMBIE_CLASSES 4
#define MAX_ZOMBIE_TAG	12

#define DAMAGE_TYPE_PUNCH_BITE 0
#define DAMAGE_TYPE_EXPLOSION	1
#define DAMAGE_TYPE_PUNCH_DELAY 2

#define SPECIAL_POWER_NONE 0
#define SPECIAL_POWER_DAMAGE 1
#define SPECIAL_POWER_HEALTH 2
#define SPECIAL_POWER_SPEED_JUMP 4

enum ZombieClassData
{
	ClassID,
	ZombieTag[MAX_ZOMBIE_TAG],
	Float:SpawnAverage,
	Float:Speed,
	DamageType,
	Float:MinDamage,
	Float:MaxDamage,
	Float:BonusDamage,//handled in % (damage enchancement at night)
	Float:LeapSize,
	Float:DetectionRadius,
	SpecialPower,
	Float:SpecialPowerRadius,
	Float:SpecialPowerAmount
}

new ZombieClassInfo[MAX_ZOMBIE_CLASSES][ZombieClassData] =
{
/*	ID |  Tag     |Spawn (%) |  Speed | Damage type 		 |	MinDMG|	   MaxDMG| |BonDMG| Leap |Detection|   Special Power       	|SpecialRadius| Special Amount */	
	{0, "Walker",   50.0, 		0.0015, DAMAGE_TYPE_PUNCH_BITE,  10.0, 		20.0,    10.0, 	 0.4, 	40.0, 	SPECIAL_POWER_HEALTH, 		0.0, 		10.0},
	{1,	"Infected", 20.0, 		0.0057, DAMAGE_TYPE_PUNCH_BITE,  15.0, 		25.0,    15.0,   1.5, 	70.0, 	SPECIAL_POWER_SPEED_JUMP, 	1.7, 		0.0062},
	{2, "Purse",    20.0, 		0.0012, DAMAGE_TYPE_EXPLOSION,   80.0, 		100.0,   30.0,   0.3, 	50.0, 	SPECIAL_POWER_NONE, 		0.0, 		0.0},
	{3, "Thug",     10.0, 		0.0008, DAMAGE_TYPE_PUNCH_DELAY, 50.0, 		70.0,    20.0, 	 0.5, 	35.0, 	SPECIAL_POWER_DAMAGE, 		0.0, 		10.0}
};

new ZombieClass[MAX_ZOMBIES];