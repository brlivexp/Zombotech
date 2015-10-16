#define MAX_INVENTORY_ITEMS 40
#define MAX_EQUIPPED_INVENTORY_SLOTS	9
#define DEFAULT_OBJECT_MODEL	19475

#define MAX_WEAPON_AMMO		1000

#define AMMO_TYPE_PISTOL 0
#define AMMO_TYPE_SMG 1 
#define AMMO_TYPE_SHOTGUN 2 
#define AMMO_TYPE_RIFLE 2
#define AMMO_TYPE_ASSAULT_RIFLE 3

#define INVALID_BONE 0
#define BONE_SPINE 1  
#define BONE_HEAD 2
#define BONE_LEFT_UPPER_ARM 3
#define BONE_RIGHT_UPPER_ARM 4
#define BONE_LEFT_HAND 5
#define BONE_RIGHT_HAND 6 
#define BONE_LEFT_THIGH 7
#define BONE_RIGHT_THIGH 8
#define BONE_LEFT_FOOT 9
#define BONE_RIGHT_FOOT 10 
#define BONE_RIGHT_CALF 11 
#define BONE_LEFT_CALF 12
#define BONE_LEFT_FOREARM 13
#define BONE_RIGHT_FOREARM 14
#define BONE_LEFT_CLAVICLE 15
#define BONE_RIGHT_CLAVICLE 16
#define BONE_NECK 17 
#define BONE_JAW 18

enum InventoryItems
{
	ItemID[MAX_INVENTORY_ITEMS],
	ItemModel[MAX_INVENTORY_ITEMS],
	ItemAmount[MAX_INVENTORY_ITEMS],
	Float:ItemDurability[MAX_INVENTORY_ITEMS],
	ItemTime[MAX_INVENTORY_ITEMS],
	ItemExpirable[MAX_INVENTORY_ITEMS]
}

enum EquippedItems
{
	EItemID[MAX_EQUIPPED_INVENTORY_SLOTS],
	EItemModel[MAX_EQUIPPED_INVENTORY_SLOTS],
	EItemAmount[MAX_EQUIPPED_INVENTORY_SLOTS],
	Float:EItemDurability[MAX_EQUIPPED_INVENTORY_SLOTS],
	EItemTime[MAX_EQUIPPED_INVENTORY_SLOTS],
	EItemExpirable[MAX_EQUIPPED_INVENTORY_SLOTS],
	EItemBone[MAX_EQUIPPED_INVENTORY_SLOTS],
	Float:EItemOffX[MAX_EQUIPPED_INVENTORY_SLOTS],
	Float:EItemOffY[MAX_EQUIPPED_INVENTORY_SLOTS],
	Float:EItemOffZ[MAX_EQUIPPED_INVENTORY_SLOTS],
	Float:EItemRotX[MAX_EQUIPPED_INVENTORY_SLOTS],
	Float:EItemRotY[MAX_EQUIPPED_INVENTORY_SLOTS],
	Float:EItemRotZ[MAX_EQUIPPED_INVENTORY_SLOTS],
	Float:EItemSclX[MAX_EQUIPPED_INVENTORY_SLOTS],
	Float:EItemSclY[MAX_EQUIPPED_INVENTORY_SLOTS],
	Float:EItemSclZ[MAX_EQUIPPED_INVENTORY_SLOTS],
	EItemCol1[MAX_EQUIPPED_INVENTORY_SLOTS],
	EItemCol2[MAX_EQUIPPED_INVENTORY_SLOTS]
}

enum DroppedItems
{
	DItemObj,
	Text3D:DItemLabel,
	DItemModel,
	DItemAmount,
	Float:DItemPosX,
	Float:DItemPosY,
	Float:DItemPosZ,
	DItemWorld,
	DItemInterior,
	Float:DItemDurability,
	DItemTime,
	DItemExpirable
}


GetAmmoFromWeaponModel(model)
{
	switch(model)
	{
		case 357, 358: return 3052;
		case 346..348: return 19995;
		case 352, 353, 372: return 2037;
		case 349..351: return 2040;
		case 355, 356: return 3016;
		case 359: return 1636;
	}
	return 0;
}

GetAmmoEquipableSlot(model)
{
	switch(model)
	{
		case 3052, 2040, 3016: return 0;
		case 19995, 2037: return 1;
		case 1636: return 3;//special (rpg)
	}
	return 0;
}

bool:IsAmmoFromWeapon(ammo_model, weapon_model)
{
	switch(weapon_model)
	{
		case 357, 358: if(ammo_model == 3052) return true;//rifle
		case 346..348: if(ammo_model == 19995) return true;//pistol
		case 352, 353, 372: if(ammo_model == 2037) return true;//smg
		case 349..351: if(ammo_model == 2040) return true;//shotgun
		case 355, 356: if(ammo_model == 3016) return true;//assault
		case 359: if(ammo_model == 1636) return true;//tool rpg
	}
	return false;
}

GetEquipableModelType(model)
{
	switch(model)
	{
		case 3052, 19995, 2037, 2040, 3016, 1636: return -1;//ammo
		case 349..351, 355..358: return 0;//primary
		case 346..348, 352, 353, 372: return 1;//secondary
		case 321..326, 331, 333..339, 341, 365..369: return 2;//melee
		case 359..364: return 3;//special
		case 2052,2053,2054,18636,18638..18640: return 4;//head wears
		case 1242, 19142: return 5;//body wears
		case 19804: return 7; //padlock
		case 371, 3026, 19559: return 8;//backpacks
		default: return 10;
	}
	return 0;
}


GetWeaponFromModel(model)
{
	switch(model)
	{
		case 331: return 1;
		case 333: return 2;
		case 334: return 3;
		case 335: return 4;
		case 336: return 5;
		case 337: return 6;
		case 338: return 7;
		case 339: return 8;
		case 341: return 9;
		case 321: return 10;
		case 322: return 11;
		case 323: return 12;
		case 324: return 13;
		case 325: return 14;
		case 326: return 15;
		case 342: return 16;
		case 343: return 17;
		case 344: return 18;
		case 346: return 22;
		case 347: return 23;
		case 348: return 24;
		case 349: return 25;
		case 350: return 26;
		case 351: return 27;
		case 352: return 28;
		case 353: return 29;
		case 355: return 30;
		case 356: return 31;
		case 372: return 32;
		case 357: return 33;
		case 358: return 34;
		case 359: return 35;
		case 360: return 36;
		case 361: return 37;
		case 362: return 38;
		case 363: return 39;
		case 364: return 40;
		case 365: return 41;
		case 366: return 42;
		case 367: return 43;
		case 368: return 44;
		case 369: return 45;
		case 371: return 46;		
	}
	return -1;
}

GetModelFromWeapon(weapon)
{
	switch(weapon)
	{
        case 0: return 19475;
		case 1: return 331;
		case 2: return 333;
		case 3: return 334;
		case 4: return 335;
		case 5: return 336;
		case 6: return 337;
		case 7: return 338;
		case 8: return 339;
		case 9: return 341;
		case 10: return 321;
		case 11: return 322;
		case 12: return 323;
		case 13: return 324;
		case 14: return 325;
		case 15: return 326;
		case 16: return 342;
		case 17: return 343;
		case 18: return 344;
		case 22: return 346;
		case 23: return 347;
		case 24: return 348;
		case 25: return 349;
		case 26: return 350;
		case 27: return 351;
		case 28: return 352;
		case 29: return 353;
		case 30: return 355;
		case 31: return 356;
		case 32: return 372;
		case 33: return 357;
		case 34: return 358;
		case 35: return 359;
		case 36: return 360;
		case 37: return 361;
		case 38: return 362;
		case 39: return 363;
		case 40: return 364;
		case 41: return 365;
		case 42: return 366;
		case 43: return 367;
		case 44: return 368;
		case 45: return  369;
		case 46: return  371;		
	}
	return -1;
}

GetBagTypeInfo(backtype, &backmodel, backname[32])
{
	switch(backtype)
	{
		case 1: backmodel = 19475, backname = "None";
		case 2: backmodel = 3026, backname = "Iron backpack";
		case 3: backmodel = 371, backname = "Alice backpack";
		case 4: backmodel = 19559, backname = "Camping backpack";
		default: backmodel = 19475, backname = "None";
	}
	return 1;
}

GetBagTypeFromModel(model)
{
	switch(model)
	{
		case 3026: return 2;
		case 371: return 3;
		case 19559: return 4;
		default: return 1;
	}
	return 1;
}

stock GetPlayerAmmoFromWeapon(playerid, weaponid)
{
	new weapon, ammo;
	GetPlayerWeaponData(playerid, GetWeaponSlot(weaponid), weapon, ammo);
	return ammo;
}

//clothes


stock GetClothModelBone(model)
{
	switch(model)
	{
		case 2052,2053,2054,18636,18638..18640: return BONE_HEAD;
		case 19142: return BONE_SPINE;
		default: return INVALID_BONE;
	}
	return INVALID_BONE;
}

bool:IsObjectUsable(modelid)
{
	new Float:ehunger, Float: ethirst, Float:edamage,Float:eenergy, Float:etemp, Float:ehealth;

	GetObjectEffects(modelid, ehunger, ethirst, edamage, eenergy, etemp, ehealth);

	if(ehunger || ethirst || eenergy || ehealth || GetBagTypeFromModel(modelid) != 1) return true;
	return false;
}

//Vars
new bool:PlayerInInventory[MAX_PLAYERS char];
new DroppedItem[MAX_ITEMS][DroppedItems];
new PlayerEquippedItem[MAX_PLAYERS][EquippedItems];
new PlayerItem[MAX_PLAYERS][InventoryItems];
new CurrentInventoryPage[MAX_PLAYERS char];
new PlayerSelectedSlot[MAX_PLAYERS char];
new bool:UnableToDrop[MAX_PLAYERS char];
new bool:UnableToPickup[MAX_PLAYERS char];
new bool:UnableToEquip[MAX_PLAYERS char];
new bool:UnableToSplit[MAX_PLAYERS char];
new PlayerTargetItem[MAX_PLAYERS];

ResetAllowanceInfo(playerid)
{
	UnableToEquip[playerid] = false;
	UnableToDrop[playerid] = false;
	UnableToPickup[playerid] = false;
}

forward SetPlayerAbleToEquip(playerid);
public SetPlayerAbleToEquip(playerid)
{
	UnableToEquip[playerid] = false;
}

forward SetPlayerAbleToDrop(playerid);
public SetPlayerAbleToDrop(playerid)
{
	UnableToDrop[playerid] = false;
}

forward SetPlayerAbleToPickup(playerid);
public SetPlayerAbleToPickup(playerid)
{
	UnableToPickup[playerid] = false;
}

forward SetPlayerAbleToSplit(playerid);
public SetPlayerAbleToSplit(playerid)
{
	UnableToSplit[playerid] = false;
}