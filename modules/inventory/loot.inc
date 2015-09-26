ShowPlayerLootInfo(playerid, itemid)
{
	new model = DroppedItem[itemid][DItemModel], date[32],
	Float:lhunger, Float:lthirst, Float:ldamage, Float:lhealth, Float:ltemp, Float:lenergy, string[64];
	PlayerTextDrawColor(playerid, LootText[playerid][1], (GetObjectColor(model) << 8) | 0xFF);
	PlayerTextDrawSetString(playerid, LootText[playerid][1], GetObjectName(model));
	format(string, 32, "Amount: %d", DroppedItem[itemid][DItemAmount]);
	PlayerTextDrawSetString(playerid, LootText[playerid][2], string);
	format(string, 32, "Durability: %03d", floatround(DroppedItem[itemid][DItemDurability]));
	PlayerTextDrawSetString(playerid, LootText[playerid][3], string);
	PlayerTextDrawSetString(playerid, LootText[playerid][4], GetObjectDescription(model));
	GetDateFromTime(DroppedItem[itemid][DItemTime], date);
	format(string, 64, "Expire: %s", date);
	PlayerTextDrawSetString(playerid, LootText[playerid][5], DroppedItem[itemid][DItemTime] ? string : "Permanent Item");
	
	GetObjectEffects(model, lhunger, lthirst, ldamage, lenergy, ltemp, lhealth);
	
	PlayerTextDrawColor(playerid, LootText[playerid][6], ldamage > 0 ? 0x00FF00FF : 0xFF0000FF);
	PlayerTextDrawColor(playerid, LootText[playerid][7], lhunger > 0 ? 0x00FF00FF : 0xFF0000FF);
	PlayerTextDrawColor(playerid, LootText[playerid][8], lthirst > 0 ? 0x00FF00FF : 0xFF0000FF);
	PlayerTextDrawColor(playerid, LootText[playerid][9], ltemp   > 0 ? 0x00FF00FF : 0xFF0000FF);
	PlayerTextDrawColor(playerid, LootText[playerid][10],lenergy > 0 ? 0x00FF00FF : 0xFF0000FF);
	PlayerTextDrawColor(playerid, LootText[playerid][11],lhealth > 0 ? 0x00FF00FF : 0xFF0000FF);
	
	format(string, 32, "%03d", floatround(ldamage));
	PlayerTextDrawSetString(playerid, LootText[playerid][6], string);
	format(string, 32, "%03d", floatround(lhunger));
	PlayerTextDrawSetString(playerid, LootText[playerid][7], string);
	format(string, 32, "%03d", floatround(lthirst));
	PlayerTextDrawSetString(playerid, LootText[playerid][8], string);
	format(string, 32, "%03d", floatround(ltemp));
	PlayerTextDrawSetString(playerid, LootText[playerid][9], string);
	format(string, 32, "%03d", floatround(lenergy));
	PlayerTextDrawSetString(playerid, LootText[playerid][10], string);
	format(string, 32, "%03d", floatround(lhealth));
	PlayerTextDrawSetString(playerid, LootText[playerid][11], string);
	
	for(new h; h < 33; h++) TextDrawShowForPlayer(playerid, LootStatic[h]);
	for(new i = 1; i < 12; i++) PlayerTextDrawShow(playerid, LootText[playerid][i]);
	
	
	if(PlayerTextDrawGetPreviewModel(playerid, LootText[playerid][0]) ^ model)
	{
		new Float:rx, Float:ry, Float:rz, Float:zoom, color;
		GetObjectTXDInfo(model, color, rx, ry, rz, zoom);
		PlayerTextDrawColor(playerid, LootText[playerid][0], color << 8 | 0xFF);
		PlayerTextDrawSetPreviewModel(playerid, LootText[playerid][0], model);
		PlayerTextDrawSetPreviewRot(playerid, LootText[playerid][0], rx, ry, rz, zoom);
		PlayerTextDrawShow(playerid, LootText[playerid][0]);
	}
	return 1;
}

HidePlayerLootInfo(playerid)
{
	PlayerTargetItem[playerid] = 0;
	PlayerTextDrawSetPreviewModel(playerid, LootText[playerid][0], DEFAULT_OBJECT_MODEL);
	
	for(new h; h < 33; h++) TextDrawHideForPlayer(playerid, LootStatic[h]);
	for(new i; i < 12; i++) PlayerTextDrawHide(playerid, LootText[playerid][i]);	
	return 1;
}