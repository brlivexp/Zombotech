#define ZOMBIE_STATUS_STOPPED 0
#define ZOMBIE_STATUS_WALKING 1
#define ZOMBIE_STATUS_FOLLOWING 2
#define ZOMBIE_STATUS_BLOCKED 3
#define ZOMBIE_STATUS_BITING 4
#define ZOMBIE_STATUS_DEAD 5

#define MAX_ZOMBIES 100
#define MAX_ATTACHMENTS 100
#define MAX_ZOMBIE_CLASS  4

#define rvelocity (float(MRandom(40)) * 0.0001)

enum ZombiesData
{
	zombie_class,
	zombie_skin,
	zombie_attachment[MAX_ATTACHMENTS],
	Float:zombie_spawn_x,
	Float:zombie_spawn_y,
	Float:zombie_spawn_z,
	Float:zombie_spawn_a,
	Float:zombie_health,
	zombie_status,
	zombie_update_timer
}

new ZombiesInfo[MAX_ZOMBIES][ZombiesData];
