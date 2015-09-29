#define CATEGORY_MEDIC 1
#define CATEGORY_WEAPONS 2
#define CATEGORY_HOUSING 3
#define CATEGORY_STORAGE 4
#define CATEGORY_TOOLS 5
#define CATEGORY_EXTRA 6

#define DEFAULT 19475//default object id


enum ItemCraftData
{
	crafting_item_category,
	crafting_item_model,
	crafting_item_amount,
	crafting_needed_tool[5],
	crafting_needed_item[5],
	crafting_needed_amount[5],
	crafting_waiting_time
}

new CraftingItems[][ItemCraftData] = 
{
	{CATEGORY_MEDIC, 11747, 1, {19624, DEFAULT, DEFAULT, DEFAULT, DEFAULT}, {11736,  19874,  DEFAULT,  DEFAULT, DEFAULT}, {1, 1, 0, 0, 0}, 3000},
	{CATEGORY_MEDIC, 11738, 1, {DEFAULT, DEFAULT, DEFAULT, DEFAULT, DEFAULT}, {11736,  2891,  1580,  DEFAULT, DEFAULT}, {1, 1, 1, 0, 0}, 3000}
};

enum PlayerCraftingData
{
	bool:is_crafting,
	crafting_item_model,
	crafting_item_amount,
	crafting_timer
};

new PlayerCraftingInfo[MAX_PLAYERS][PlayerCraftingData];

