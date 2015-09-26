#include "../modules/crafting/craftingdata.inc"

enum CraftingData
{
	bool:is_crafting,
	crafting_timer,
	crafting_item_model,
	crafting_item_amount
};
new PlayerCraftingInfo[MAX_PLAYERS][CraftingData];

stock ResetPlayerCraftingData(playerid)
{
	return 1;
}

stock SetCraftingDefaultConfigs(playerid)
{
	PlayerTextDrawSetString(playerid, CraftingText[playerid][0], "Category: Medic");
	return 1;
}

ShowPlayerCraftingMenu(playerid)
{
	SetCraftingDefaultConfigs(playerid);
	for(new i; i < 23; i++) TextDrawShowForPlayer(playerid, CraftingStatic[i]);
	for(new j; j < 40; j++) PlayerTextDrawShow(playerid, CraftingText[playerid][j]);
	return 1;
}

HidePlayerCraftingMenu(playerid)
{
	for(new i; i < 23; i++) TextDrawHideForPlayer(playerid, CraftingStatic[i]);
	for(new j; j < 40; j++) PlayerTextDrawHide(playerid, CraftingText[playerid][j]);
	return 1;
}