#include "../modules/crafting/craftingdata.inc"


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
	HidePlayerHUD(playerid);
	SetCraftingDefaultConfigs(playerid);
	for(new i; i < 23; i++) TextDrawShowForPlayer(playerid, CraftingStatic[i]);
	for(new j; j < 40; j++) PlayerTextDrawShow(playerid, CraftingText[playerid][j]);
	return 1;
}

HidePlayerCraftingMenu(playerid)
{
	ShowPlayerHUD(playerid);
	for(new i; i < 23; i++) TextDrawHideForPlayer(playerid, CraftingStatic[i]);
	for(new j; j < 40; j++) PlayerTextDrawHide(playerid, CraftingText[playerid][j]);
	return 1;
}

stock LoadCraftingPageItems(playerid, category = 0)
{
	new category_item_model[MAX_CRAFTING_PAGE_ITEMS];
	new lastindex;
	//prepare list of items
	for(new i; i < sizeof(CraftingItems); i++)
	{
		if(CraftingItems[i][crafting_item_category] == category && CraftingItems[i][crafting_item_model])
			if(lastindex < MAX_CRAFTING_PAGE_ITEMS) category_item_model[lastindex] = CraftingItems[i][crafting_item_model];
		lastindex++;
	}

	return 1;
}
