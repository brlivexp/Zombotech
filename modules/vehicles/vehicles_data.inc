enum VehiclesData
{
	vehicleid,
	model,
	owner[MAX_PLAYER_NAME],
	Float:fuel,
	Float:health,
	Float:oil,
	bool:hasEngine,
	bool:hasTires[4],
	expireTime,
	attachments[16]
}

enum VehiclesItems
{
	VItemID,
	VItemModel,
	VItemAmount,
	Float:VItemDurability,
	VItemTime,
	VItemExpirable
}

new VehiclesInfo[MAX_VEHICLES][VehiclesData];
new VehicleItem[MAX_VEHICLES][VehiclesItems];
