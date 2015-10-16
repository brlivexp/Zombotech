#include "../modules/inventory/itemsconfigs.inc"
#include "../modules/inventory/objectsdata.inc"
#include "../modules/inventory/rates.inc"
#include "../modules/inventory/loot.inc"


forward OnLoadPlayerItems(playerid);
forward OnDroppedItemsLoad();
forward OnCreatePlayerItem(playerid, itemid, model, amount, Float:durability, itemtime, expirable);
forward ResetEquipAllowed(playerid);
forward ResetPickupAllowed(playerid);
forward ResetDropAllowed(playerid);
forward SetPlayerEquippedItem(playerid, slotid, model, amount);
forward OnLoadEquippedItems(playerid);
forward OnDroppedItemsReset();
forward LoadPlayerBagtype(playerid);


ShowPlayerInventory(playerid)
{
	KillTimer(PlayerUpdateTimer[playerid]);
	HidePlayerHUD(playerid);
	LoadInventoryPageItems(playerid);
	for(new k; k < 38; k++) TextDrawShowForPlayer(playerid, InventoryStatic[k]);
	for(new y; y < 78; y++) PlayerTextDrawShow(playerid, InventoryText[playerid] [y]);
	SelectTextDraw(playerid, 0x80808080);
	PlayerInInventory[playerid] = true;
	LoadPlayerBagInfo(playerid);
	CheckBrokenItems(playerid);
	CheckExpiredItems(playerid);
	ResetSelectedSlots(playerid);
	return 1;
}

HidePlayerInventory(playerid)
{
	PlayerUpdateTimer[playerid] = SetTimerEx("OnPlayerUpdateEx", 100, true, "i", playerid);
	for(new k; k < 38; k++) TextDrawHideForPlayer(playerid, InventoryStatic[k]);
	for(new y; y < 78; y++) PlayerTextDrawHide(playerid, InventoryText[playerid][y]);
	CancelSelectTextDraw(playerid);
	PlayerInInventory[playerid] = false;
	ResetInventoryPageInfo(playerid);
	ShowPlayerHUD(playerid);
	return 1;
}

IsPlayerInInventory(playerid)
{
	if(PlayerInInventory[playerid]) return true;
	return false;
}

CountPlayerFreeSlots(playerid)
{
	new slots;
	for(new s; s < 10 * PlayerInfo[playerid][bagtype]; s++)	if(IsInventorySlotFree(playerid, s)) slots ++;
	return slots;
}

CountPlayerPageFreeSlots(playerid, page)
{
	new count;
	switch(page)
	{
		case 1:
		{
			for(new i; i < 10; i++)
				if(IsInventorySlotFree(playerid, i)) count++;
			return count;
		}
		case 2:
		{
			for(new i = 10; i < 20; i++)
				if(IsInventorySlotFree(playerid, i)) count++;
			return count;
		}
		case 3:
		{
			for(new i = 20; i < 30; i++)
				if(IsInventorySlotFree(playerid, i)) count++;
			return count;
		}
		case 4:
		{
			for(new i = 30; i < 40; i++)
				if(IsInventorySlotFree(playerid, i)) count++;
			return count;
		}
	}
	return 0;
}

bool:IsBackPackClean(playerid)
{
	for(new h = 10; h < MAX_INVENTORY_ITEMS; h++)
	{
		if(!IsInventorySlotFree(playerid, h)) return false; 
	}		
	return true;
}

IsInventorySlotFree(playerid, slotid) 
{
	if(!PlayerItem[playerid][ItemID][slotid] && !PlayerItem[playerid][ItemModel][slotid] && !PlayerItem[playerid][ItemAmount][slotid]) return 1;
	return 0;
}


ResetInventorySlots(playerid)
{
	for(new r; r < MAX_INVENTORY_ITEMS; r++)
	{
		PlayerItem[playerid][ItemModel][r] = 0;
		PlayerItem[playerid][ItemID][r] = 0;
		PlayerItem[playerid][ItemAmount][r] = 0;
		PlayerItem[playerid][ItemDurability][r] = 0.0;
		PlayerItem[playerid][ItemTime][r] = 0;
		PlayerItem[playerid][ItemExpirable][r] = 0;
	}
	
	for(new e; e < MAX_EQUIPPED_INVENTORY_SLOTS; e++)
	{
		PlayerEquippedItem[playerid][EItemID][e] = 0;
		PlayerEquippedItem[playerid][EItemModel][e] = 0;
		PlayerEquippedItem[playerid][EItemAmount][e] = 0;
		PlayerEquippedItem[playerid][EItemDurability][e] = 0.0;
		PlayerEquippedItem[playerid][EItemTime][e] = 0;
		PlayerEquippedItem[playerid][EItemExpirable][e] = 0;
	}
	return 1;
}

ResetInventoryPageInfo(playerid)
{
	CurrentInventoryPage[playerid] = 1;
	PlayerSelectedSlot[playerid] = -1;
	return 1;
}

ResetInventoryInfo(playerid)
{	
	CurrentInventoryPage[playerid] = 1;
	PlayerSelectedSlot[playerid] = -1;
	ResetInventorySlots(playerid);
	PlayerInInventory[playerid] = false;
	return 1;
}

ReloadPlayerAttachments(playerid)
{
	for(new index = 4; index < 6; index++)
	{
		if(PlayerEquippedItem[playerid][EItemModel][index] && PlayerEquippedItem[playerid][EItemID][index])
		{
			SetPlayerAttachedObject(playerid, index, 
			PlayerEquippedItem[playerid][EItemModel][index],
			GetClothModelBone(PlayerEquippedItem[playerid][EItemModel][index]),
		   	PlayerEquippedItem[playerid][EItemOffX][index],
		    PlayerEquippedItem[playerid][EItemOffY][index],
		    PlayerEquippedItem[playerid][EItemOffZ][index],
		    PlayerEquippedItem[playerid][EItemRotX][index],
		    PlayerEquippedItem[playerid][EItemRotY][index],
		    PlayerEquippedItem[playerid][EItemRotZ][index],
		    PlayerEquippedItem[playerid][EItemSclX][index],
		    PlayerEquippedItem[playerid][EItemSclY][index],
		    PlayerEquippedItem[playerid][EItemSclZ][index],
		    PlayerEquippedItem[playerid][EItemCol1][index],
		    PlayerEquippedItem[playerid][EItemCol2][index]);
		}
	}	
	if(PlayerInfo[playerid][bagtype] != 1)
	{
		SetPlayerAttachedObject(playerid, 8, 
		PlayerEquippedItem[playerid][EItemModel][8],
		BONE_SPINE,
	   	PlayerEquippedItem[playerid][EItemOffX][8],
	    PlayerEquippedItem[playerid][EItemOffY][8],
	    PlayerEquippedItem[playerid][EItemOffZ][8],
	    PlayerEquippedItem[playerid][EItemRotX][8],
	    PlayerEquippedItem[playerid][EItemRotY][8],
	    PlayerEquippedItem[playerid][EItemRotZ][8],
	    PlayerEquippedItem[playerid][EItemSclX][8],
	    PlayerEquippedItem[playerid][EItemSclY][8],
	    PlayerEquippedItem[playerid][EItemSclZ][8],
	    PlayerEquippedItem[playerid][EItemCol1][8],
	    PlayerEquippedItem[playerid][EItemCol2][8]);
	}
	return 1;
}

ReloadPlayerWeapons(playerid)
{
	ResetPlayerWeapons(playerid);
	for(new i; i < 4; i++)
		if(PlayerEquippedItem[playerid][EItemID][i] && GetWeaponFromModel(PlayerEquippedItem[playerid][EItemModel][i]) && PlayerEquippedItem[playerid][EItemDurability][i] > 0.0)
			GivePlayerWeapon(playerid, GetWeaponFromModel(PlayerEquippedItem[playerid][EItemModel][i]), PlayerEquippedItem[playerid][EItemAmount][i]);
	return 1;
}



public LoadPlayerBagtype(playerid)
{
	new Float:OffX, Float:OffY,Float:OffZ, Float:RotX, Float:RotY, Float:RotZ, Float:SclX, Float:SclY, Float:SclZ, Color1, Color2, model;
	
	OffX = cache_get_field_content_float(0, "OffsetX");
	OffY = cache_get_field_content_float(0, "OffsetY");
	OffZ = cache_get_field_content_float(0, "OffsetZ");
	RotX = cache_get_field_content_float(0, "RotX");
	RotY = cache_get_field_content_float(0, "RotY");
	RotZ = cache_get_field_content_float(0, "RotZ");
	SclX = cache_get_field_content_float(0, "ScaleX");
	SclY = cache_get_field_content_float(0, "ScaleY");
	SclZ = cache_get_field_content_float(0, "ScaleZ");
	Color1 = cache_get_field_content_int(0, "Color1");
	Color2 = cache_get_field_content_int(0, "Color2");
	model = cache_get_field_content_int(0, "modelid");

	PlayerEquippedItem[playerid][EItemModel][8] = model;
	PlayerEquippedItem[playerid][EItemOffX][8] = OffX;
	PlayerEquippedItem[playerid][EItemOffY][8] = OffY;
	PlayerEquippedItem[playerid][EItemOffZ][8] = OffZ;
	PlayerEquippedItem[playerid][EItemRotX][8] = RotX;
	PlayerEquippedItem[playerid][EItemRotY][8] = RotY;
	PlayerEquippedItem[playerid][EItemRotZ][8] = RotZ;
	PlayerEquippedItem[playerid][EItemSclX][8] = SclX;
	PlayerEquippedItem[playerid][EItemSclY][8] = SclY;
	PlayerEquippedItem[playerid][EItemSclZ][8] = SclZ;
	PlayerEquippedItem[playerid][EItemCol1][8] = Color1;
	PlayerEquippedItem[playerid][EItemCol2][8] = Color2;

	
	SetPlayerAttachedObject(playerid, 8, model, 1, OffX, OffY, OffZ, RotX, RotY, RotZ, SclX, SclY, SclZ, Color1, Color2);
	return 1;
}

SetPlayerBagType(playerid, type, itemid, model, Float:durability, time, expirable, bool:loaded = false)
{
	PlayerInfo[playerid][bagtype] = type;
	LoadPlayerBagInfo(playerid);
	
	new query[512];

	mysql_format(MySQL, query, 128, "UPDATE `users` SET `bagtype` = '%d' WHERE `id` = %d", type, PlayerInfo[playerid][pid]);
	mysql_tquery(MySQL, query, "", "");

	switch(type)
	{
		case 1:
		{
			mysql_format(MySQL, query, 128, "DELETE FROM `equiped_items` WHERE `slotid` = 8 AND `playerid` = %d", PlayerInfo[playerid][pid]);
			mysql_tquery(MySQL, query, "", "");

			RemovePlayerEquippedItem(playerid, 8);
			return RemovePlayerAttachedObject(playerid, 8);
		} 
		case 2: 
		{
			PlayerEquippedItem[playerid][EItemID][8] = itemid;
			PlayerEquippedItem[playerid][EItemModel][8] = model;
			PlayerEquippedItem[playerid][EItemAmount][8] = 1;
			PlayerEquippedItem[playerid][EItemDurability][8] = durability;
			PlayerEquippedItem[playerid][EItemTime][8] = time;
			PlayerEquippedItem[playerid][EItemExpirable][8] = expirable;
			PlayerEquippedItem[playerid][EItemBone][8]	= BONE_SPINE;
			

			if(!loaded)
			{
				PlayerEquippedItem[playerid][EItemOffX][8] = -0.168829;
				PlayerEquippedItem[playerid][EItemOffY][8] = -0.077197;
				PlayerEquippedItem[playerid][EItemOffZ][8] = 0.0;
				PlayerEquippedItem[playerid][EItemRotX][8] = 0.0;
				PlayerEquippedItem[playerid][EItemRotY][8] = 0.0;
				PlayerEquippedItem[playerid][EItemRotZ][8] = 0.0;
				PlayerEquippedItem[playerid][EItemSclX][8] = 1.1;
				PlayerEquippedItem[playerid][EItemSclY][8] = 1.1;
				PlayerEquippedItem[playerid][EItemSclZ][8] = 1.1;
				PlayerEquippedItem[playerid][EItemCol1][8] = 0xFFFFFFFF;
				PlayerEquippedItem[playerid][EItemCol2][8] = 0xFFFFFFFF;
				
				mysql_format(MySQL, query, 512, "INSERT INTO `equiped_items` VALUES(%d, %d, %d, %d, %d, %f, %d, %d, %d, '%f', '%f', '%f', '%f', '%f', '%f',  '%f', '%f', '%f', '%d', '%d');",
				PlayerInfo[playerid][pid], 8,
				PlayerEquippedItem[playerid][EItemID][8],
				PlayerEquippedItem[playerid][EItemModel][8],
				PlayerEquippedItem[playerid][EItemAmount][8],
				PlayerEquippedItem[playerid][EItemDurability][8],
				PlayerEquippedItem[playerid][EItemTime][8],
				PlayerEquippedItem[playerid][EItemExpirable][8],
				PlayerEquippedItem[playerid][EItemBone][8],
				PlayerEquippedItem[playerid][EItemOffX][8],
				PlayerEquippedItem[playerid][EItemOffY][8],
				PlayerEquippedItem[playerid][EItemOffZ][8],
				PlayerEquippedItem[playerid][EItemRotX][8],
				PlayerEquippedItem[playerid][EItemRotY][8],
				PlayerEquippedItem[playerid][EItemRotZ][8],
				PlayerEquippedItem[playerid][EItemSclX][8],
				PlayerEquippedItem[playerid][EItemSclY][8],
				PlayerEquippedItem[playerid][EItemSclZ][8],
				PlayerEquippedItem[playerid][EItemCol1][8],
				PlayerEquippedItem[playerid][EItemCol2][8]);
				mysql_tquery(MySQL, query, "","");

				return SetPlayerAttachedObject(playerid, 8, 3026, 1, -0.168829, -0.077197, 0.000000, 0.000000, 0.000000, 0.000000, 1.100000, 1.100000, 1.100000);
			}
			else 
			{				
				mysql_format(MySQL, query, 128, "SELECT * FROM `equiped_items` WHERE `playerid` = %d AND `slotid` = 8", PlayerInfo[playerid][pid]);
				mysql_tquery(MySQL, query, "LoadPlayerBagtype", "i", playerid);
				return 1;
			}				
		}
		case 3:
		{
			PlayerEquippedItem[playerid][EItemID][8] = itemid;
			PlayerEquippedItem[playerid][EItemModel][8] = model;
			PlayerEquippedItem[playerid][EItemAmount][8] = 1;
			PlayerEquippedItem[playerid][EItemDurability][8] = durability;
			PlayerEquippedItem[playerid][EItemTime][8] = time;
			PlayerEquippedItem[playerid][EItemExpirable][8] = expirable;
			PlayerEquippedItem[playerid][EItemBone][8]	= BONE_SPINE;			

			if(!loaded)//if server needs to create the table
			{
				PlayerEquippedItem[playerid][EItemOffX][8] = 0.057849;
				PlayerEquippedItem[playerid][EItemOffY][8] = -0.123179;
				PlayerEquippedItem[playerid][EItemOffZ][8] = -0.027480;
				PlayerEquippedItem[playerid][EItemRotX][8] = 9.241791;
				PlayerEquippedItem[playerid][EItemRotY][8] = 87.611961;
				PlayerEquippedItem[playerid][EItemRotZ][8] = 0.0;
				PlayerEquippedItem[playerid][EItemSclX][8] = 1.0;
				PlayerEquippedItem[playerid][EItemSclY][8] = 1.0;
				PlayerEquippedItem[playerid][EItemSclZ][8] = 1.0;
				PlayerEquippedItem[playerid][EItemCol1][8] = 0xFFFFFFFF;
				PlayerEquippedItem[playerid][EItemCol2][8] = 0xFFFFFFFF;
			

				mysql_format(MySQL, query, 512, "INSERT INTO `equiped_items` VALUES(%d, %d, %d, %d, %d, %f, %d, %d, %d, '%f', '%f', '%f', '%f', '%f', '%f',  '%f', '%f', '%f', '%d', '%d');",
				PlayerInfo[playerid][pid], 8,
				PlayerEquippedItem[playerid][EItemID][8],
				PlayerEquippedItem[playerid][EItemModel][8],
				PlayerEquippedItem[playerid][EItemAmount][8],
				PlayerEquippedItem[playerid][EItemDurability][8],
				PlayerEquippedItem[playerid][EItemTime][8],
				PlayerEquippedItem[playerid][EItemExpirable][8],
				PlayerEquippedItem[playerid][EItemBone][8],
				PlayerEquippedItem[playerid][EItemOffX][8],
				PlayerEquippedItem[playerid][EItemOffY][8],
				PlayerEquippedItem[playerid][EItemOffZ][8],
				PlayerEquippedItem[playerid][EItemRotX][8],
				PlayerEquippedItem[playerid][EItemRotY][8],
				PlayerEquippedItem[playerid][EItemRotZ][8],
				PlayerEquippedItem[playerid][EItemSclX][8],
				PlayerEquippedItem[playerid][EItemSclY][8],
				PlayerEquippedItem[playerid][EItemSclZ][8],
				PlayerEquippedItem[playerid][EItemCol1][8],
				PlayerEquippedItem[playerid][EItemCol2][8]);
				mysql_tquery(MySQL, query, "","");
				return SetPlayerAttachedObject(playerid, 8, 371, 1, 0.057849, -0.123179, -0.027480, 9.241791, 87.611961, 0.000000, 1.000000, 1.000000, 1.000000);
			}		
			else 
			{
				mysql_format(MySQL, query, 128, "SELECT * FROM `equiped_items` WHERE `playerid` = %d AND `slotid` = 8", PlayerInfo[playerid][pid]);
				mysql_tquery(MySQL, query, "LoadPlayerBagtype", "i", playerid);
				return 1;
			}

		} 
		case 4: 
		{
			PlayerEquippedItem[playerid][EItemModel][8] = model;
			PlayerEquippedItem[playerid][EItemAmount][8] = 1;
			PlayerEquippedItem[playerid][EItemDurability][8] = durability;
			PlayerEquippedItem[playerid][EItemTime][8] = time;
			PlayerEquippedItem[playerid][EItemExpirable][8] = expirable;
			PlayerEquippedItem[playerid][EItemBone][8]	= BONE_SPINE;

			if(!loaded)
			{
				PlayerEquippedItem[playerid][EItemOffX][8] = 0.100000;
				PlayerEquippedItem[playerid][EItemOffY][8] = -0.050000;
				PlayerEquippedItem[playerid][EItemOffZ][8] = 0.0;
				PlayerEquippedItem[playerid][EItemRotX][8] = 0.0;
				PlayerEquippedItem[playerid][EItemRotY][8] = 90.0;
				PlayerEquippedItem[playerid][EItemRotZ][8] = 0.0;
				PlayerEquippedItem[playerid][EItemSclX][8] = 1.0;
				PlayerEquippedItem[playerid][EItemSclY][8] = 1.0;
				PlayerEquippedItem[playerid][EItemSclZ][8] = 1.0;
				PlayerEquippedItem[playerid][EItemCol1][8] = 0xFFFFFFFF;
				PlayerEquippedItem[playerid][EItemCol2][8] = 0xFFFFFFFF;


				//reciclar query futuramente
				PlayerEquippedItem[playerid][EItemID][8] = itemid;				
				mysql_format(MySQL, query, 512, "INSERT INTO `equiped_items` VALUES(%d, %d, %d, %d, %d, %f, %d, %d, %d, '%f', '%f', '%f', '%f', '%f', '%f',  '%f', '%f', '%f', '%d', '%d');",
				PlayerInfo[playerid][pid], 8,
				PlayerEquippedItem[playerid][EItemID][8],
				PlayerEquippedItem[playerid][EItemModel][8],
				PlayerEquippedItem[playerid][EItemAmount][8],
				PlayerEquippedItem[playerid][EItemDurability][8],
				PlayerEquippedItem[playerid][EItemTime][8],
				PlayerEquippedItem[playerid][EItemExpirable][8],
				PlayerEquippedItem[playerid][EItemBone][8],
				PlayerEquippedItem[playerid][EItemOffX][8],
				PlayerEquippedItem[playerid][EItemOffY][8],
				PlayerEquippedItem[playerid][EItemOffZ][8],
				PlayerEquippedItem[playerid][EItemRotX][8],
				PlayerEquippedItem[playerid][EItemRotY][8],
				PlayerEquippedItem[playerid][EItemRotZ][8],
				PlayerEquippedItem[playerid][EItemSclX][8],
				PlayerEquippedItem[playerid][EItemSclY][8],
				PlayerEquippedItem[playerid][EItemSclZ][8],
				PlayerEquippedItem[playerid][EItemCol1][8],
				PlayerEquippedItem[playerid][EItemCol2][8]);
				mysql_tquery(MySQL, query, "","");
				return SetPlayerAttachedObject(playerid, 8, 19559, 1, 0.100000, -0.050000, 0.000000, 0.000000, 90.000000, 0.000000, 1.000000, 1.000000, 1.000000);
			}
			else 
			{
				mysql_format(MySQL, query, 128, "SELECT * FROM `equiped_items` WHERE `playerid` = %d AND `slotid` = 8", PlayerInfo[playerid][pid]);
				mysql_tquery(MySQL, query, "LoadPlayerBagtype", "i", playerid);
				return 1;
			}	
		}
		default: return RemovePlayerAttachedObject(playerid, 8);
	}
	return 1;
}

LoadPlayerBagInfo(playerid)
{
	new string[32];
	format(string, sizeof(string), "%d/%d", CurrentInventoryPage[playerid], PlayerInfo[playerid][bagtype]);
	PlayerTextDrawSetString(playerid, InventoryText[playerid][62], string);
	format(string, sizeof(string), "Pages: %d", PlayerInfo[playerid][bagtype]);
	PlayerTextDrawSetString(playerid, InventoryText[playerid][6], string);
	format(string, sizeof(string), "Max item: %d", PlayerInfo[playerid][bagtype] * 10);
	PlayerTextDrawSetString(playerid, InventoryText[playerid][7], string);
	format(string, sizeof(string), "Current page: %d", CurrentInventoryPage[playerid]);
	PlayerTextDrawSetString(playerid, InventoryText[playerid][8], string);
	format(string, sizeof(string), "Free slots: %d", CountPlayerFreeSlots(playerid));
	PlayerTextDrawSetString(playerid, InventoryText[playerid][9], string);
	format(string, sizeof(string), "Ocuppied slots: %d", (PlayerInfo[playerid][bagtype] * 10) - CountPlayerFreeSlots(playerid));
	PlayerTextDrawSetString(playerid, InventoryText[playerid][10], string);
	format(string, sizeof(string), "Selected slot: %d", PlayerSelectedSlot[playerid]);
	PlayerTextDrawSetString(playerid, InventoryText[playerid][11], string);
	PlayerTextDrawSetPreviewModel(playerid, InventoryText[playerid][4], GetPlayerSkin(playerid));
	
	UpdatePadlockInfo(playerid);
	UpdateBackpackInfo(playerid);
	
	if(IsPlayerInInventory(playerid))
	{
		for(new i = 4; i < 12; i++) PlayerTextDrawShow(playerid, InventoryText[playerid][i]);
		PlayerTextDrawShow(playerid, InventoryText[playerid][62]);
	}
	return 1;
}

UpdatePadlockInfo(playerid)
{
	if(PlayerEquippedItem[playerid][EItemModel][7] == 19804 && PlayerEquippedItem[playerid][EItemExpirable][7] && PlayerEquippedItem[playerid][EItemTime][7] <= gettime()) RemovePlayerPadlock(playerid);
	new ipadlock = 19804;
	if(PlayerEquippedItem[playerid][EItemModel][7] != 19804) ipadlock = DEFAULT_OBJECT_MODEL;	
	
	
	PlayerTextDrawSetPreviewModel(playerid, InventoryText[playerid][12], ipadlock);
	
	if(ipadlock == 19804)
	{
		PlayerTextDrawSetString(playerid, InventoryText[playerid][13], "Status: ~g~Locked");
		new string[64], date[32];
		GetDateFromTime(PlayerEquippedItem[playerid][EItemTime][7], date);
		format(string, sizeof(string), "Expire: %s", date); 
		PlayerTextDrawSetString(playerid, InventoryText[playerid][14], string);
	}
	else
	{
		PlayerTextDrawSetString(playerid, InventoryText[playerid][13], "Status: ~r~Unlocked");
		PlayerTextDrawSetString(playerid, InventoryText[playerid][14], "Expire: --/--/--");
	}
	if(!IsPlayerInInventory(playerid)) return 1;
	PlayerTextDrawShow(playerid, InventoryText[playerid][12]);
	PlayerTextDrawShow(playerid, InventoryText[playerid][13]);
	PlayerTextDrawShow(playerid, InventoryText[playerid][14]);
	return 1;
}

RemovePlayerPadlock(playerid)
{
	//executar query para deletar o item... //
	SendClientMessage(playerid, -1, "{FF0000}Your padlock has expired!");
	PlayerEquippedItem[playerid][EItemTime][7] = 0;
	PlayerEquippedItem[playerid][EItemID][7] = 0;
	PlayerEquippedItem[playerid][EItemAmount][7] = 0;
	PlayerEquippedItem[playerid][EItemModel][7] = 0;
	PlayerEquippedItem[playerid][EItemDurability][7] = 100.0;
	PlayerEquippedItem[playerid][EItemExpirable][7] = 0;
	return 1;
}

UpdateBackpackInfo(playerid)
{
	new backpackname[32], backpackmodel;
	GetBagTypeInfo(PlayerInfo[playerid][bagtype], backpackmodel, backpackname);
	PlayerTextDrawSetPreviewModel(playerid, InventoryText[playerid][16], backpackmodel);
	PlayerTextDrawSetString(playerid, InventoryText[playerid][17], backpackname);	
	if(!IsPlayerInInventory(playerid)) return 1;
	PlayerTextDrawShow(playerid, InventoryText[playerid][16]);
	PlayerTextDrawShow(playerid, InventoryText[playerid][17]);
	return 1;
}

LoadInventoryPageItems(playerid)
{
	new mmodelid, string[64];
	switch(CurrentInventoryPage[playerid])
	{		
		case 1:
		{
			for(new i = 20; i < 30; i++)
			{
				mmodelid = PlayerItem[playerid][ItemModel][i - 20];
				if(!mmodelid) mmodelid = DEFAULT_OBJECT_MODEL;
				static color, Float:rx, Float:ry, Float:rz, Float:zoom;
				GetObjectTXDInfo(mmodelid, color, rx, ry, rz, zoom);
				PlayerTextDrawColor(playerid, InventoryText[playerid][i], color << 8 | 0xFF);
				PlayerTextDrawSetPreviewRot(playerid, InventoryText[playerid][i], rx, ry, rz, zoom);
				PlayerTextDrawSetPreviewModel(playerid, InventoryText[playerid][i], mmodelid < 20000 ? mmodelid : mmodelid / 100);				
				format(string, 64, "%s ~r~(%d)", GetObjectName(mmodelid), PlayerItem[playerid][ItemAmount][i - 20]);
				PlayerTextDrawSetString(playerid, InventoryText[playerid][i + 48], string);
				if(IsPlayerInInventory(playerid))
				{
					PlayerTextDrawShow(playerid, InventoryText[playerid][i]);
					PlayerTextDrawShow(playerid, InventoryText[playerid][i + 48]);
				}		
			}			
		}
		case 2:
		{
			for(new i = 20; i < 30; i++)
			{
				mmodelid = PlayerItem[playerid][ItemModel][i - 10];
				if(!mmodelid) mmodelid = DEFAULT_OBJECT_MODEL;
				static color, Float:rx, Float:ry, Float:rz, Float:zoom;
				GetObjectTXDInfo(mmodelid, color, rx, ry, rz, zoom);
				PlayerTextDrawColor(playerid, InventoryText[playerid][i], color << 8 | 0xFF);
				PlayerTextDrawSetPreviewRot(playerid, InventoryText[playerid][i], rx, ry, rz, zoom);
				PlayerTextDrawSetPreviewModel(playerid, InventoryText[playerid][i], mmodelid < 20000 ? mmodelid : mmodelid / 100);				
				format(string, 64, "%s ~r~(%d)", GetObjectName(mmodelid), PlayerItem[playerid][ItemAmount][i - 10]);
				PlayerTextDrawSetString(playerid, InventoryText[playerid][i + 48], string);
				if(IsPlayerInInventory(playerid))
				{
					PlayerTextDrawShow(playerid, InventoryText[playerid][i]);
					PlayerTextDrawShow(playerid, InventoryText[playerid][i + 48]);
				}		
			}
		}
		case 3:
		{
			for(new i = 20; i < 30; i++)
			{
				mmodelid = PlayerItem[playerid][ItemModel][i];
				if(!mmodelid) mmodelid = DEFAULT_OBJECT_MODEL;
				static color, Float:rx, Float:ry, Float:rz, Float:zoom;
				GetObjectTXDInfo(mmodelid, color, rx, ry, rz, zoom);
				PlayerTextDrawColor(playerid, InventoryText[playerid][i], color << 8 | 0xFF);
				PlayerTextDrawSetPreviewRot(playerid, InventoryText[playerid][i], rx, ry, rz, zoom);
				PlayerTextDrawSetPreviewModel(playerid, InventoryText[playerid][i], mmodelid < 20000 ? mmodelid : mmodelid / 100);				
				format(string, 64, "%s ~r~(%d)", GetObjectName(mmodelid), PlayerItem[playerid][ItemAmount][i]);
				PlayerTextDrawSetString(playerid, InventoryText[playerid][i + 48], string);
				if(IsPlayerInInventory(playerid))
				{
					PlayerTextDrawShow(playerid, InventoryText[playerid][i]);
					PlayerTextDrawShow(playerid, InventoryText[playerid][i + 48]);
				}		
			}
		}
		case 4:
		{
			for(new i = 20; i < 30; i++)
			{
				mmodelid = PlayerItem[playerid][ItemModel][i + 10];
				if(!mmodelid) mmodelid = DEFAULT_OBJECT_MODEL;
				static color, Float:rx, Float:ry, Float:rz, Float:zoom;
				GetObjectTXDInfo(mmodelid, color, rx, ry, rz, zoom);
				PlayerTextDrawColor(playerid, InventoryText[playerid][i], color << 8 | 0xFF);
				PlayerTextDrawSetPreviewRot(playerid, InventoryText[playerid][i], rx, ry, rz, zoom);
				PlayerTextDrawSetPreviewModel(playerid, InventoryText[playerid][i], mmodelid < 20000 ? mmodelid : mmodelid / 100);				
				format(string, 64, "%s ~r~(%d)", GetObjectName(mmodelid), PlayerItem[playerid][ItemAmount][i + 10]);
				PlayerTextDrawSetString(playerid, InventoryText[playerid][i + 48], string);
				if(IsPlayerInInventory(playerid))
				{
					PlayerTextDrawShow(playerid, InventoryText[playerid][i]);
					PlayerTextDrawShow(playerid, InventoryText[playerid][i + 48]);
				}		
			}
		}
	}
	LoadInventoryEquippedItems(playerid);
	ResetSelectedSlots(playerid);
	return 1;
}

LoadInventoryEquippedItems(playerid)
{	
	new string[64];
	for(new slotid; slotid < MAX_EQUIPPED_INVENTORY_SLOTS; slotid++)
	{		
		new model = PlayerEquippedItem[playerid][EItemModel][slotid];
		
		if(!model) continue;
		switch(slotid)
		{
			case 0://primary
			{
				PlayerTextDrawSetPreviewModel(playerid, InventoryText[playerid][30], model);
				format(string, 64, "Weapon: %s", GetObjectName(model));
				PlayerTextDrawSetString(playerid, InventoryText[playerid][32], string);
				format(string, 64, "Ammo: %d", PlayerEquippedItem[playerid][EItemAmount][slotid]);
				PlayerTextDrawSetString(playerid, InventoryText[playerid][33], string);
				format(string, 64, "Durability: %d/100", floatround(PlayerEquippedItem[playerid][EItemDurability][slotid]));
				PlayerTextDrawSetString(playerid, InventoryText[playerid][34], string);
				
				for(new i = 30; i < 35; i++) PlayerTextDrawShow(playerid, InventoryText[playerid][i]);
			}
			case 1://secondary
			{
				PlayerTextDrawSetPreviewModel(playerid, InventoryText[playerid][35], model);
				format(string, 64, "Weapon: %s", GetObjectName(model));
				PlayerTextDrawSetString(playerid, InventoryText[playerid][37], string);
				format(string, 64, "Ammo: %d", PlayerEquippedItem[playerid][EItemAmount][slotid]);
				PlayerTextDrawSetString(playerid, InventoryText[playerid][38], string);
				format(string, 64, "Durability: %d/100", floatround(PlayerEquippedItem[playerid][EItemDurability][slotid]));
				PlayerTextDrawSetString(playerid, InventoryText[playerid][39], string);
				
				for(new i = 35; i < 40; i++) PlayerTextDrawShow(playerid, InventoryText[playerid][i]);
			}
			case 2://melee
			{
				PlayerTextDrawSetPreviewModel(playerid, InventoryText[playerid][40], model);
				format(string, 64, "Weapon: %s", GetObjectName(model));
				PlayerTextDrawSetString(playerid, InventoryText[playerid][42], string);
				format(string, 64, "Amount: %d", PlayerEquippedItem[playerid][EItemAmount][slotid]);
				PlayerTextDrawSetString(playerid, InventoryText[playerid][43], string);
				format(string, 64, "Durability: %d/100", floatround(PlayerEquippedItem[playerid][EItemDurability][slotid]));
				PlayerTextDrawSetString(playerid, InventoryText[playerid][44], string);
				
				for(new i = 40; i < 45; i++) PlayerTextDrawShow(playerid, InventoryText[playerid][i]);
			}
			case 3://explosives
			{
				PlayerTextDrawSetPreviewModel(playerid, InventoryText[playerid][45], model);
				format(string, 64, "Tool: %s", GetObjectName(model));
				PlayerTextDrawSetString(playerid, InventoryText[playerid][47], string);
				format(string, 64, "Amount: %d", PlayerEquippedItem[playerid][EItemAmount][slotid]);
				PlayerTextDrawSetString(playerid, InventoryText[playerid][48], string);
				format(string, 64, "Durability: %d/100", floatround(PlayerEquippedItem[playerid][EItemDurability][slotid]));
				PlayerTextDrawSetString(playerid, InventoryText[playerid][49], string);
				
				for(new i = 45; i < 50; i++) PlayerTextDrawShow(playerid, InventoryText[playerid][i]);
			}
			case 4://wear 1
			{
				new date[32];
				
				PlayerTextDrawSetPreviewModel(playerid, InventoryText[playerid][50], model);
				format(string, 64, "Wear: %s", GetObjectName(model));
				PlayerTextDrawSetString(playerid, InventoryText[playerid][54], string);
				
				GetDateFromTime(PlayerEquippedItem[playerid][EItemTime][4], date);
				if(PlayerEquippedItem[playerid][EItemExpirable][4]) format(string, 64, "Expire: %s",  date);
				else format(string, 64, "Durability: %d", floatround(PlayerEquippedItem[playerid][EItemDurability][4]));				
				PlayerTextDrawSetString(playerid, InventoryText[playerid][55], string);
				
				PlayerTextDrawShow(playerid, InventoryText[playerid][50]);
				PlayerTextDrawShow(playerid, InventoryText[playerid][54]);
				PlayerTextDrawShow(playerid, InventoryText[playerid][55]);
			}
			case 5://wear 2
			{
				new date[32];
				
				PlayerTextDrawSetPreviewModel(playerid, InventoryText[playerid][51], model);
				format(string, 64, "Wear: %s", GetObjectName(model));
				PlayerTextDrawSetString(playerid, InventoryText[playerid][57], string);
				
				
				GetDateFromTime(PlayerEquippedItem[playerid][EItemTime][5], date);
				if(PlayerEquippedItem[playerid][EItemExpirable][5]) format(string, 64, "Expire: %s",  date);
				else format(string, 64, "Durability: %d", floatround(PlayerEquippedItem[playerid][EItemDurability][5]));	
				PlayerTextDrawSetString(playerid, InventoryText[playerid][58], string);
		
				PlayerTextDrawShow(playerid, InventoryText[playerid][51]);
				PlayerTextDrawShow(playerid, InventoryText[playerid][57]);
				PlayerTextDrawShow(playerid, InventoryText[playerid][58]);
			}
			case 6://wear 3
			{
				new date[32];
				
				PlayerTextDrawSetPreviewModel(playerid, InventoryText[playerid][52], model);
				format(string, 64, "Wear: %s", GetObjectName(model));
				PlayerTextDrawSetString(playerid, InventoryText[playerid][60], string);
				
				GetDateFromTime(PlayerEquippedItem[playerid][EItemTime][6], date);
				if(PlayerEquippedItem[playerid][EItemExpirable][6]) format(string, 64, "Expire: %s",  date);
				else format(string, 64, "Durability: %d", floatround(PlayerEquippedItem[playerid][EItemDurability][6]));	
				PlayerTextDrawSetString(playerid, InventoryText[playerid][61], string);
				
				PlayerTextDrawShow(playerid, InventoryText[playerid][52]);
				PlayerTextDrawShow(playerid, InventoryText[playerid][60]);
				PlayerTextDrawShow(playerid, InventoryText[playerid][61]);
				
			}
			case 7: UpdatePadlockInfo(playerid); //padlock			
			case 8: UpdateBackpackInfo(playerid);//backpack
		}
	}
	return 1;
}

GivePlayerItem(playerid, itemid, modelid, amount, &Float:durability = 100.0, &itemtime = 0, &expirable = 0)
{
	if(!CountPlayerFreeSlots(playerid)) return SendInfoText(playerid, "Inventory", "~r~Your bag is full, you can not pickup more items!", 3500);
	
	if(IsModelStackable(modelid))
	{
		new index = ResearchInventoryItem(playerid, modelid);
		if(index != -1)
		{
			if(PlayerItem[playerid][ItemAmount][index] + amount <= GetObjectMaxStack(modelid))
			{
				PlayerItem[playerid][ItemAmount][index] += amount;
				UpdatePlayerSlot(playerid, index);
				new query[128];
				mysql_format(MySQL, query, 128, "UPDATE `items` SET `model` = %d, `owner` = '-1' WHERE `id` = %d", DEFAULT_OBJECT_MODEL, itemid);
				mysql_tquery(MySQL, query, "", "");				
				return 1;
			}
		}
	}
	for(new s; s < 10 * PlayerInfo[playerid][bagtype]; s ++)
	{
		if(IsInventorySlotFree(playerid, s))
		{
			PlayerItem[playerid][ItemID][s] = itemid;
			PlayerItem[playerid][ItemModel][s] = modelid;
			PlayerItem[playerid][ItemAmount][s] = amount;
			PlayerItem[playerid][ItemDurability][s] = durability;
			PlayerItem[playerid][ItemTime][s] = itemtime;
			PlayerItem[playerid][ItemExpirable][s] = expirable;
			UpdatePlayerSlot(playerid, s);
			LoadPlayerBagInfo(playerid);
			
			return 1;
		}
	}
	return 1;
}

UpdatePlayerSlot(playerid, slotid)
{
	if(!IsPlayerInInventory(playerid)) return 1;
	
	new string[32], kmodelid = PlayerItem[playerid][ItemModel][slotid];
	if(!kmodelid) kmodelid = DEFAULT_OBJECT_MODEL;
	format(string, sizeof(string), "%s ~r~(%d)", GetObjectName(kmodelid), PlayerItem[playerid][ItemAmount][slotid]);
	
	if(slotid < 10 && CurrentInventoryPage[playerid] == 1)
	{
		static color, Float:rx, Float:ry, Float:rz, Float:zoom;
		GetObjectTXDInfo(kmodelid, color, rx, ry, rz, zoom);
		PlayerTextDrawColor(playerid, InventoryText[playerid][slotid + 20], color << 8 | 0xFF);
		PlayerTextDrawSetPreviewRot(playerid, InventoryText[playerid][slotid + 20], rx, ry, rz, zoom);					
				
		PlayerTextDrawSetString(playerid, InventoryText[playerid][slotid + 68], string);
		PlayerTextDrawSetPreviewModel(playerid, InventoryText[playerid][slotid + 20], kmodelid < 20000 ? kmodelid : kmodelid / 100);
		PlayerTextDrawShow(playerid, InventoryText[playerid][slotid + 20]);
		PlayerTextDrawShow(playerid, InventoryText[playerid][slotid + 68]);
	}
	if( 9 < slotid < 20 && CurrentInventoryPage[playerid] == 2)
	{
		static color, Float:rx, Float:ry, Float:rz, Float:zoom;
		GetObjectTXDInfo(kmodelid, color, rx, ry, rz, zoom);
		if(color != 0xFFFFFF) PlayerTextDrawColor(playerid, InventoryText[playerid][slotid + 10], color << 8 | 0xFF);
		PlayerTextDrawSetPreviewRot(playerid, InventoryText[playerid][slotid + 10], rx, ry, rz, zoom);

		PlayerTextDrawSetString(playerid, InventoryText[playerid][slotid + 58], string);
		PlayerTextDrawSetPreviewModel(playerid, InventoryText[playerid][slotid + 10], kmodelid < 20000 ? kmodelid : kmodelid / 100);
		PlayerTextDrawShow(playerid, InventoryText[playerid][slotid + 10]);
		PlayerTextDrawShow(playerid, InventoryText[playerid][slotid + 58]);
	}
	if(19 < slotid < 30 && CurrentInventoryPage[playerid] == 3)
	{
		static color, Float:rx, Float:ry, Float:rz, Float:zoom;
		GetObjectTXDInfo(kmodelid, color, rx, ry, rz, zoom);
		if(color != 0xFFFFFF) PlayerTextDrawColor(playerid, InventoryText[playerid][slotid], color << 8 | 0xFF);
		PlayerTextDrawSetPreviewRot(playerid, InventoryText[playerid][slotid], rx, ry, rz, zoom);

		PlayerTextDrawSetString(playerid, InventoryText[playerid][slotid + 48], string);
		PlayerTextDrawSetPreviewModel(playerid, InventoryText[playerid][slotid], kmodelid < 20000 ? kmodelid : kmodelid / 100);
		PlayerTextDrawShow(playerid, InventoryText[playerid][slotid]);
		PlayerTextDrawShow(playerid, InventoryText[playerid][slotid + 48]);
	}
	if( 29 < slotid < 40 && CurrentInventoryPage[playerid] == 4)
	{
		static color, Float:rx, Float:ry, Float:rz, Float:zoom;
		GetObjectTXDInfo(kmodelid, color, rx, ry, rz, zoom);
		if(color != 0xFFFFFF) PlayerTextDrawColor(playerid, InventoryText[playerid][slotid - 10], color << 8 | 0xFF);
		PlayerTextDrawSetPreviewRot(playerid, InventoryText[playerid][slotid - 10], rx, ry, rz, zoom);

		PlayerTextDrawSetString(playerid, InventoryText[playerid][slotid + 38], string);
		PlayerTextDrawSetPreviewModel(playerid, InventoryText[playerid][slotid - 10], kmodelid < 20000 ? kmodelid : kmodelid / 100);
		PlayerTextDrawShow(playerid, InventoryText[playerid][slotid - 10]);
		PlayerTextDrawShow(playerid, InventoryText[playerid][slotid + 38]);
	}
	return 1;
}



/////////////////////////////////////////////////////////////////
CreatePlayerItem(playerid, model, amount, Float:durability = 100.0, itemtime = 0, expirable = 0)
{
	if(!CountPlayerFreeSlots(playerid)) return SendClientMessage(playerid, -1, "{FF0000}Your bag is full, you can't recieve more items");
	if(model == DEFAULT_OBJECT_MODEL) return SendClientMessage(playerid, -1, "Invalid object model (default)");
	
	new query[256], item;

	mysql_format(MySQL, query, 128, "SELECT * FROM `items` WHERE `model` = %d ORDER BY `id` ASC LIMIT 1;", DEFAULT_OBJECT_MODEL);
	new Cache:qresult = mysql_query(MySQL, query, true);
	
	if(cache_num_rows())
	{
		item = cache_get_field_content_int(0, "id");
		cache_delete(qresult);
		mysql_format(MySQL, query, sizeof(query), "UPDATE `items` SET `model` = %d, `amount` = %d, `owner` = %d, `durability` = '%f', `time` = %d, `expirable` = %d WHERE `id` = %d;",
		model, amount, PlayerInfo[playerid][pid], durability, itemtime, expirable, item);
		mysql_pquery(MySQL, query, "OnCreatePlayerItem", "ddddddd", playerid, item, model, amount, durability, itemtime, expirable);
	}	
	else
	{
		cache_delete(qresult);
		new Cache:result = mysql_query(MySQL, "SELECT * FROM `items` ORDER BY `id` DESC LIMIT 1;", true);
		if(cache_num_rows()) item = cache_get_field_content_int(0, "id") + 1;
		else item = 1;
		if(item >= MAX_ITEMS) return printf("Server couldn't create the item %s for player %d due to items limit reached!",  GetObjectName(model), PlayerInfo[playerid][pid]);
		mysql_format(MySQL, query, sizeof(query), "INSERT INTO `items` VALUES('%d', '%d', '%d', '%d', '-1.0', '-1.0', '-1.0', '0', '0', '%f', '%d', '%d');",
		item, model, amount, PlayerInfo[playerid][pid], durability, itemtime, expirable);
		mysql_tquery(MySQL, query, "OnCreatePlayerItem", "ddddddd", playerid, item, model, amount, durability, itemtime, expirable);
		cache_delete(result);
	}
	return 1;
}

CreateDroppedItem(itemid, model, amount, Float:x, Float:y, Float:z, vworld, pinterior, Float:durability = 100.0, itemtime = 0, expirable = 0, bool:use_z_index = false)
{	
	new label[50], Float:rx, Float:ry, Float:rz, label_color, Float:label_variance, Float:zindexh;
	label_color = GetObjectColor(model);
	GetObjectDropData(model, rx, ry, rz, label_variance, zindexh);
	if(!use_z_index) CA_FindZ_For2DCoord(x, y, z);
	format(label, sizeof(label), "Item: {%06x}%s", label_color, GetObjectName(model));
	DroppedItem[itemid][DItemLabel] = CreateDynamic3DTextLabel(label, 0xFFFFFFFF, x, y, z + 0.3 + label_variance + zindexh, 12.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, vworld, pinterior);
	DroppedItem[itemid][DItemModel] = model;
	DroppedItem[itemid][DItemAmount] = amount;
	DroppedItem[itemid][DItemPosX] = x;
	DroppedItem[itemid][DItemPosY] = y;
	DroppedItem[itemid][DItemPosZ] = z;	
	DroppedItem[itemid][DItemObj] = CreateDynamicObject(model < 20000 ? model : model  / 100, x, y, z + 0.1 + zindexh, rx, ry, 0.0, vworld, pinterior);
	DroppedItem[itemid][DItemDurability] = durability;
	DroppedItem[itemid][DItemTime] = itemtime;
	DroppedItem[itemid][DItemExpirable] = expirable;
	DroppedItem[itemid][DItemWorld] = vworld;
	DroppedItem[itemid][DItemInterior] = pinterior;

	//ignore textures and colors on weapons
	if(GetWeaponFromModel(model) == -1)
	{
		new txr_lib[32], txr_name[32], matcolor;
		GetObjectTXRInfo(model, txr_lib, txr_name, matcolor);
		SetDynamicObjectMaterial(DroppedItem[itemid][DItemObj], 0, model < 20000 ? model : model  / 100, txr_lib, txr_name, 0xFF << 24 | matcolor);
	}
	return 1;
}

RemoveDroppedItem(itemid)
{
	DestroyDynamic3DTextLabel(DroppedItem[itemid][DItemLabel]);
	DestroyDynamicObject(DroppedItem[itemid][DItemObj]);
	DroppedItem[itemid][DItemModel] = DEFAULT_OBJECT_MODEL;
	DroppedItem[itemid][DItemAmount] = 0;
	DroppedItem[itemid][DItemPosX] = 0;
	DroppedItem[itemid][DItemPosY] = 0;
	DroppedItem[itemid][DItemPosZ] = 0;
	DroppedItem[itemid][DItemDurability] = 100.0;
	DroppedItem[itemid][DItemTime] = 0;
	DroppedItem[itemid][DItemExpirable] = 0;
	DroppedItem[itemid][DItemWorld] = 0;
	DroppedItem[itemid][DItemInterior] = 0;
	return 1;
}

RemovePlayerItem(playerid, itemid)
{
	for(new i; i < 10 * PlayerInfo[playerid][bagtype]; i++)
	{
		if(PlayerItem[playerid][ItemID][i] == itemid)
		{
			PlayerItem[playerid][ItemID][i] = 0;
			PlayerItem[playerid][ItemAmount][i] = 0;
			PlayerItem[playerid][ItemModel][i] = 0;
			PlayerItem[playerid][ItemDurability][i] = 100.0;
			PlayerItem[playerid][ItemTime][i] = 0;
			PlayerItem[playerid][ItemExpirable][i] = 0;
			UpdatePlayerSlot(playerid, i);
			return 1;		
		}
	}
	return 1;
}

RemoveEquippedItem(playerid, slotid)
{
	if(3 < slotid < 7) RemovePlayerAttachedObject(playerid, slotid);
	PlayerEquippedItem[playerid][EItemID][slotid] = 0;
	PlayerEquippedItem[playerid][EItemModel][slotid] = DEFAULT_OBJECT_MODEL;
	PlayerEquippedItem[playerid][EItemAmount][slotid] = 0;
	PlayerEquippedItem[playerid][EItemTime][slotid] = 0;
	PlayerEquippedItem[playerid][EItemDurability][slotid]= 100.0;
	PlayerEquippedItem[playerid][EItemExpirable][slotid] =  0;
	PlayerEquippedItem[playerid][EItemBone][slotid]	= 0;
	PlayerEquippedItem[playerid][EItemOffX][slotid] = 0.0;
	PlayerEquippedItem[playerid][EItemOffY][slotid] = 0.0;
	PlayerEquippedItem[playerid][EItemOffZ][slotid] = 0.0;
	PlayerEquippedItem[playerid][EItemRotX][slotid] = 0.0;
	PlayerEquippedItem[playerid][EItemRotY][slotid] = 0.0;
	PlayerEquippedItem[playerid][EItemRotZ][slotid] = 0.0;
	PlayerEquippedItem[playerid][EItemSclX][slotid] = 0.0;
	PlayerEquippedItem[playerid][EItemSclY][slotid] = 0.0;
	PlayerEquippedItem[playerid][EItemSclZ][slotid] = 0.0;
	PlayerEquippedItem[playerid][EItemCol1][slotid] = 0;
	PlayerEquippedItem[playerid][EItemCol2][slotid] = 0;
	
	if(IsPlayerInInventory(playerid)) LoadInventoryEquippedItems(playerid);
	return 1;
}

DestroyPlayerItem(playerid, itemid)
{
	new query[128];
	mysql_format(MySQL, query, 128, "UPDATE `items` SET `model` = %d, `owner` = '-1' WHERE `id` = %d", DEFAULT_OBJECT_MODEL, itemid);
	mysql_tquery(MySQL, query, "", "");
	RemovePlayerItem(playerid, itemid);
	return 1;
}



DestroyEquippedItem(playerid, slotid)
{
	new query[128];
	mysql_format(MySQL, query, 128, "UPDATE `equiped_items` SET `modelid` = %d, `playerid` = '-1' WHERE `playerid` = %d AND `slotid` = %d;", DEFAULT_OBJECT_MODEL, PlayerInfo[playerid][pid], slotid);
	mysql_tquery(MySQL, query, "", "");
	RemoveEquippedItem(playerid, slotid);
	return 1;
}

CheckExpiredItems(playerid)
{
	new istring[128];
	for(new i = 4; i < 8; i++)
	{
		if(PlayerEquippedItem[playerid][EItemExpirable][i] && PlayerEquippedItem[playerid][EItemTime][i] <= gettime())
		{
			format(istring, 128, "Your item %s has expired and removed from inventory", GetObjectName(PlayerEquippedItem[playerid][EItemModel][i]));
			SendInfoText(playerid, "Inventory", istring, 3000);
			DestroyEquippedItem(playerid, i);
		}
	}
	for(new j; j < PlayerInfo[playerid][bagtype] * 10; j++)
	{
		if(PlayerItem[playerid][ItemExpirable][j] && PlayerItem[playerid][ItemTime][j] <= gettime())
		{
			format(istring, 128, "Your item %s has expired and removed from inventory", GetObjectName(PlayerItem[playerid][ItemModel][j]));
			SendInfoText(playerid, "Inventory", istring, 3000);
			DestroyPlayerItem(playerid, PlayerItem[playerid][ItemID][j]);
		}
	}
	return 1;
}

CheckBrokenItems(playerid)
{
	new istring[128];
	for(new i = 4; i < 8; i++)
	{
		if(PlayerEquippedItem[playerid][EItemID][i] && !PlayerEquippedItem[playerid][EItemDurability][i])
		{
			format(istring, 128, "Your item %s has broken and removed from inventory", GetObjectName(PlayerEquippedItem[playerid][EItemModel][i]));
			SendInfoText(playerid, "Inventory", istring, 3000);
			DestroyEquippedItem(playerid, i);
		}
	}
	for(new j; j < PlayerInfo[playerid][bagtype] * 10; j++)
	{
		if(PlayerItem[playerid][ItemID][j] && !PlayerItem[playerid][ItemDurability][j])
		{
			format(istring, 128, "Your item %s has broken and removed from inventory", GetObjectName(PlayerItem[playerid][ItemModel][j]));
			SendInfoText(playerid, "Inventory", istring, 3000);
			DestroyPlayerItem(playerid, PlayerItem[playerid][ItemID][j]);
		}
	}
	return 1;
}


DropPlayerItem(playerid, itemid,  model, amount, Float:durability = 100.0, itemtime = 0, expirable = 0)
{
	new label[256], vworld, pinterior, Float:rx, Float:ry, Float:rz, Float:x, Float:y, Float:z, Float:cx, Float:cy, Float:cz, color, Float:diff, Float:diff2, Float:variation, Float:label_variance, Float:zindexh;
	MRandFloatRange(-0.7, 0.7, diff);
	MRandFloatRange(-0.5, 0.5, diff2);
	MRandFloatRange(0.1, 1.2, variation);
	GetXYInFrontOfPlayer(playerid, x, y, variation);
	GetPlayerPos(playerid, cx, cy, cz);
	PlayerPlaySound(playerid, 1085, 0,0,0);
	CA_FindZ_For2DCoord(x, y, z);

	if(z > cz) z = cz - 0.9;

	GetObjectDropData(model, rx, ry, rz, label_variance, zindexh);
	color = GetObjectColor(model);
	vworld = GetPlayerVirtualWorld(playerid);
	pinterior = GetPlayerInterior(playerid);
	format(label, 32, "Item: {%06x}%s", color, GetObjectName(model));	
	
	DroppedItem[itemid][DItemLabel] = CreateDynamic3DTextLabel(label, 0xFFFFFFFFF, x + diff + diff2, y + diff + diff2, z + 0.3 + label_variance + zindexh, 12.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, vworld, pinterior);
	DroppedItem[itemid][DItemModel] = model;
	DroppedItem[itemid][DItemAmount] = amount;
	DroppedItem[itemid][DItemPosX] = x + diff + diff2;
	DroppedItem[itemid][DItemPosY] = y + diff + diff2;
	DroppedItem[itemid][DItemPosZ] = z + 0.1;	
	DroppedItem[itemid][DItemObj] = CreateDynamicObject(model < 20000 ? model : model / 100, x + diff + diff2, y + diff + diff2, z + 0.1 + zindexh, rx, ry, 0.0, vworld, pinterior);
	DroppedItem[itemid][DItemDurability] = durability;
	DroppedItem[itemid][DItemTime] = itemtime;
	DroppedItem[itemid][DItemExpirable] = expirable;
	DroppedItem[itemid][DItemWorld] = vworld;
	DroppedItem[itemid][DItemInterior] = pinterior;
	if(GetWeaponFromModel(model) == -1)
	{
		new txr_lib[32], txr_name[32], matcolor;
		GetObjectTXRInfo(model, txr_lib, txr_name, matcolor);
		SetDynamicObjectMaterial(DroppedItem[itemid][DItemObj], 0, model < 20000 ? model : model  / 100, txr_lib, txr_name, 0xFF << 24 | matcolor);
	}
	mysql_format(MySQL, label, sizeof(label), "UPDATE `items` SET `owner` = '-1', `coord_x` = '%f', `coord_y` = '%f', `coord_z` = '%f', `world` = '%d', `interior` = '%d',  `durability` = '%f', `time` = '%d', `expirable` = '%d' WHERE `id` = '%d'", x + diff + diff2, y + diff + diff2, z + 0.2, vworld, pinterior, durability, itemtime, expirable, itemid);
	mysql_tquery(MySQL, label, "", "");
	RemovePlayerItem(playerid, itemid);
	UnableToDrop[playerid] = true;

	SetTimerEx("SetPlayerAbleToDrop", 1000, false, "i", playerid); 
	return 1;
}

LoadPlayerItems(playerid)
{
	new query[512];
	mysql_format(MySQL, query, sizeof(query), "SELECT * FROM `items` WHERE `owner` = '%d'", PlayerInfo[playerid][pid]);
	mysql_tquery(MySQL, query, "OnLoadPlayerItems", "d", playerid);
	
	mysql_format(MySQL, query, sizeof(query), "SELECT * FROM `equiped_items` WHERE `playerid` = '%d'", PlayerInfo[playerid][pid]);
	mysql_tquery(MySQL, query, "OnLoadEquippedItems", "d",  playerid);
	
	return 1;
}

public OnCreatePlayerItem(playerid, itemid, model, amount, Float:durability, itemtime, expirable)
{
	GivePlayerItem(playerid, itemid, model, amount, durability, itemtime, expirable);
	return 1;
}



public OnLoadEquippedItems(playerid)
{	
	for(new row; row < cache_num_rows(); row++)
	{
		
		static itemid, slotid, model, amount, Float:durability, itemtime, expirable, Bone, Float:OffX, Float:OffY, Float:OffZ, Float:RotX, Float:RotY, Float:RotZ, Float:SclX, Float:SclY, Float:SclZ, Col1, Col2;
		itemid = cache_get_field_content_int(row, "itemid");
		model = cache_get_field_content_int(row, "modelid");
		if(!model || !itemid) continue;//jump to next item in case it be default model or invalid id
		amount = cache_get_field_content_int(row, "amount");
		durability = cache_get_field_content_float(row, "durability");
		itemtime = cache_get_field_content_int(row, "time");
		expirable = cache_get_field_content_int(row, "expirable");
		slotid = cache_get_field_content_int(row, "slotid");
		Bone = cache_get_field_content_int(row, "bone");
		OffX = cache_get_field_content_float(row, "OffsetX");
		OffY = cache_get_field_content_float(row, "OffsetY");
		OffZ = cache_get_field_content_float(row, "OffsetZ"); 
		RotX = cache_get_field_content_float(row, "RotX");
		RotY = cache_get_field_content_float(row, "RotY"); 
		RotZ = cache_get_field_content_float(row, "RotZ");	
		SclX = cache_get_field_content_float(row, "ScaleX");
		SclY = cache_get_field_content_float(row, "ScaleY");	
		SclZ = cache_get_field_content_float(row, "ScaleZ");
		Col1 = cache_get_field_content_int(row, "Color1");
		Col2 = cache_get_field_content_int(row, "Color2");

		OnPlayerEquipItem(playerid, slotid, itemid, model, amount, durability, itemtime, expirable, true, Bone, OffX, OffY, OffZ, RotX, RotY, RotZ,	SclX, SclY,	SclZ, Col1, Col2);
	}	
	return 1;
}

OnPlayerEquipItem(playerid, slotid, itemid, model, amount, Float:durability, time, expirable, bool:loaded = false, Bone = 0, Float:OffX  = 0.0, Float:OffY = 0.0, Float:OffZ  = 0.0, Float:RotX = 0.0, Float:RotY = 0.0, Float:RotZ = 0.0, Float:SclX = 1.0, Float:SclY = 1.0, Float:SclZ = 1.0, Col1 = 0xFFFFFFFF, Col2 = 0xFFFFFFFF)
{
	if(UnableToEquip[playerid] && !loaded) return 0;
	if(slotid == 8) 
	{
		if(PlayerInfo[playerid][bagtype] < 2 || loaded) SetPlayerBagType(playerid, GetBagTypeFromModel(model), itemid, model, PlayerItem[playerid][ItemDurability][slotid], PlayerItem[playerid][ItemTime][slotid], PlayerItem[playerid][ItemExpirable][slotid], false); 
			else return SendInfoText(playerid, "Inventory", "You already have a backpack in use, remove it before using another one.", 3000);
		return DestroyPlayerItem(playerid, itemid);
	}
	if(model == DEFAULT_OBJECT_MODEL) return SendClientMessage(playerid, 0xFF0000FF, "Error: invalid model id while loading equipped item!");
	if(slotid != GetEquipableModelType(model)) return SendClientMessage(playerid, 0xFF0000FF, "Error: invalid slot while loading equipped item!");
	if(slotid > 1 && PlayerEquippedItem[playerid][EItemID][slotid]) return SendInfoText(playerid, "Inventory", "Error: There is already a weapon equipped, you must unequip it before equip another one.", 3500);	
	//filter items data
	switch(slotid)
	{
		//case ammo
		case -1:
		{
			new slot = GetAmmoEquipableSlot(model);
			if(PlayerEquippedItem[playerid][EItemAmount][slot] >= MAX_WEAPON_AMMO) return SendInfoText(playerid, "Inventory", "This weapon has too much ammo.", 3000);
		
			if(PlayerEquippedItem[playerid][EItemAmount][slot] + amount > MAX_WEAPON_AMMO)
			{
				new iTot = 1000 - PlayerEquippedItem[playerid][EItemAmount][slot];
				new iLeft = amount - iTot;

				PlayerEquippedItem[playerid][EItemAmount][slot] = MAX_WEAPON_AMMO;
				SetPlayerAmmo(playerid, GetWeaponFromModel(PlayerEquippedItem[playerid][EItemModel][slot]), PlayerEquippedItem[playerid][EItemAmount][slot]);
				LoadInventoryEquippedItems(playerid);
				for(new x; x < 10 * PlayerInfo[playerid][bagtype]; x++)
				{
					if(PlayerItem[playerid][ItemID][x] == itemid)
					{
						PlayerItem[playerid][ItemAmount][x] = iLeft;
						UpdatePlayerSlot(playerid, x);
						return 1;
					}
				}
			}
			else
			{
				DestroyPlayerItem(playerid, itemid);
				PlayerEquippedItem[playerid][EItemAmount][slot] += amount;
			}
			if(!IsAmmoFromWeapon(model, PlayerEquippedItem[playerid][EItemModel][slot])) return SendInfoText(playerid, "Inventory", "Ammo type different from equiped weapon!", 3500);
			PlayerPlaySound(playerid, 1150, 0,0,0);	
			
			SetPlayerAmmo(playerid, GetWeaponFromModel(PlayerEquippedItem[playerid][EItemModel][slot]), PlayerEquippedItem[playerid][EItemAmount][slot]);
			return LoadInventoryEquippedItems(playerid);
		}
		//case primary or secondary
		case 0, 1:
		{
			//check if uses the same type of ammo
			if(PlayerEquippedItem[playerid][EItemModel] != DEFAULT_OBJECT_MODEL && PlayerEquippedItem[playerid][EItemID][slotid] && GetAmmoFromWeaponModel(model) == GetAmmoFromWeaponModel(PlayerEquippedItem[playerid][EItemModel][slotid]) && !loaded)
			{
				if(amount)
				{
					PlayerPlaySound(playerid, 1150, 0,0,0);
					//check for ammo limit
					if(PlayerEquippedItem[playerid][EItemAmount][slotid] + amount > MAX_WEAPON_AMMO)
					{
						if(PlayerEquippedItem[playerid][EItemAmount][slotid] >= MAX_WEAPON_AMMO) return SendInfoText(playerid, "Inventory", "This weapon has too much ammo.", 3000);
					
						new iTot = 1000 - PlayerEquippedItem[playerid][EItemAmount][slotid];
						new iLeft = amount - iTot;

						PlayerEquippedItem[playerid][EItemAmount][slotid] = MAX_WEAPON_AMMO;
						SetPlayerAmmo(playerid, GetWeaponFromModel(PlayerEquippedItem[playerid][EItemModel][slotid]), PlayerEquippedItem[playerid][EItemAmount][slotid]);
						LoadInventoryEquippedItems(playerid);
						for(new x; x < 10 * PlayerInfo[playerid][bagtype]; x++)
						{
							if(PlayerItem[playerid][ItemID][x] == itemid)
							{
								PlayerItem[playerid][ItemAmount][x] = iLeft;
								UpdatePlayerSlot(playerid, x);
								return 1;
							}
						}
					}
					else
					{
						for(new x; x < 10 * PlayerInfo[playerid][bagtype]; x++)
						{
							if(PlayerItem[playerid][ItemID][x] == itemid)
							{
								PlayerItem[playerid][ItemAmount][x] = 0;
								UpdatePlayerSlot(playerid, x);
							}
						}
						PlayerEquippedItem[playerid][EItemAmount][slotid] += amount;
						SetPlayerAmmo(playerid, GetWeaponFromModel(PlayerEquippedItem[playerid][EItemModel][slotid]), PlayerEquippedItem[playerid][EItemAmount][slotid]);
						LoadInventoryEquippedItems(playerid);
						return 1;
					}
				}
				else return SendInfoText(playerid, "Inventory", "This weapon has no ammo left to equip!", 3500);
			}
			else if(PlayerEquippedItem[playerid][EItemID][slotid]) return SendInfoText(playerid, "Inventory", "There is already a weapon equipped, you must unequip it before equip another one.", 3500);	
		}
		//case clothes
		case 4..6: if(GetClothModelBone(model) != INVALID_BONE) Bone = GetClothModelBone(model);

		case 7:
		{
			if(PlayerEquippedItem[playerid][EItemModel][7] == 19804 && PlayerEquippedItem[playerid][EItemID][7])
			{
				if(!time && PlayerEquippedItem[playerid][EItemModel][7]) return SendInfoText(playerid, "Inventory", "This padlock is no longer expirable! You can't extend your current expiration with this.", 3000);
				PlayerPlaySound(playerid, 1150, 0,0,0);	
				PlayerEquippedItem[playerid][EItemTime][7] += time;
				return UpdatePadlockInfo(playerid);
			}
		}
	}	

	if(!loaded)
	{
		new query[512], Cache:result;

		DestroyPlayerItem(playerid, itemid);

		mysql_format(MySQL, query, 128, "SELECT * FROM `equiped_items` WHERE `modelid` = '%d' ORDER BY `itemid` ASC;", DEFAULT_OBJECT_MODEL);
		result = mysql_query(MySQL, query, true);
		if(cache_num_rows())
		{
			itemid = cache_get_field_content_int(0, "itemid");
			cache_delete(result);
			mysql_format(MySQL, query, 512, 
			"UPDATE `equiped_items` SET `playerid`= '%d',`slotid`='%d',`modelid`= '%d',`amount`= '%d',`durability`='%f',`time`= '%d',`expirable`= '%d',`bone`= '%d',`OffsetX`= '%f',`OffsetY`= '%f',`OffsetZ`='%f',`RotX`= '%f',`RotY`= '%f',`RotZ`= '%f',`ScaleX`= '%f',`ScaleY`= '%f',`ScaleZ`='%f',`Color1`='%d',`Color2`='%d' WHERE `itemid` = '%d';",
			PlayerInfo[playerid][pid], slotid,  model, amount, durability, time, expirable, Bone, OffX, OffY, OffZ, RotX, RotY, RotZ, SclX, SclY, SclZ, Col1, Col2, itemid);
			mysql_tquery(MySQL, query, "", "");
		}
		else
		{
			cache_delete(result);
			result = mysql_query(MySQL, "SELECT * FROM `equiped_items` ORDER BY `itemid` DESC LIMIT 1;", true);
			if(cache_num_rows()) itemid = cache_get_field_content_int(0, "itemid") + 1;
			else itemid = 1;

			mysql_format(MySQL, query, 512, "INSERT INTO `equiped_items` VALUES(%d, %d, %d, %d, %d, %f, %d, %d, %d, '%f', '%f', '%f', '%f', '%f', '%f', '%f', '%f', '%f', '%d', '%d');",
			PlayerInfo[playerid][pid], slotid, itemid, model, amount, durability, time, expirable, Bone, OffX, OffY, OffZ, RotX, RotY, RotZ, SclX, SclY,	SclZ, Col1, Col2); 
			mysql_tquery(MySQL, query, "", "");
		}				

				
		if(itemid >= MAX_ITEMS) return SendInfoText(playerid, "Inventory", "Server couldn't create your equiped item due to limit has been reached!", 3000);

		UnableToEquip[playerid] = true;		
		SetTimerEx("SetPlayerAbleToEquip", 1000, false, "i", playerid);
		
		if(-1 < GetEquipableModelType(model) < 8)
		{
			PlayerEquippedItem[playerid][EItemID][slotid] = itemid;
			PlayerEquippedItem[playerid][EItemModel][slotid] = model;
			PlayerEquippedItem[playerid][EItemAmount][slotid] = amount;
			PlayerEquippedItem[playerid][EItemDurability][slotid] = durability;
			PlayerEquippedItem[playerid][EItemTime][slotid] = time;
			PlayerEquippedItem[playerid][EItemExpirable][slotid] = expirable;
			PlayerEquippedItem[playerid][EItemBone][slotid]	= Bone;
			PlayerEquippedItem[playerid][EItemOffX][slotid] = OffX;
			PlayerEquippedItem[playerid][EItemOffY][slotid] = OffY;
			PlayerEquippedItem[playerid][EItemOffZ][slotid] = OffZ;
			PlayerEquippedItem[playerid][EItemRotX][slotid] = RotX;
			PlayerEquippedItem[playerid][EItemRotY][slotid] = RotY;
			PlayerEquippedItem[playerid][EItemRotZ][slotid] = RotZ;
			PlayerEquippedItem[playerid][EItemSclX][slotid] = SclX;
			PlayerEquippedItem[playerid][EItemSclY][slotid] = SclY;
			PlayerEquippedItem[playerid][EItemSclZ][slotid] = SclZ;
			PlayerEquippedItem[playerid][EItemCol1][slotid] = Col1;
			PlayerEquippedItem[playerid][EItemCol2][slotid] = Col2;
			
		}
		SetTimerEx("SetPlayerEquippedItem", 1000, false, "iiii", playerid, slotid, model, amount);
		if(IsPlayerInInventory(playerid)) LoadInventoryEquippedItems(playerid);
		return 1;
	}	
	else
	{	
		PlayerEquippedItem[playerid][EItemID][slotid] = itemid;
		PlayerEquippedItem[playerid][EItemModel][slotid] = model;
		PlayerEquippedItem[playerid][EItemAmount][slotid] = amount;
		PlayerEquippedItem[playerid][EItemDurability][slotid] = durability;
		PlayerEquippedItem[playerid][EItemTime][slotid] = time;
		PlayerEquippedItem[playerid][EItemExpirable][slotid] = expirable;
		PlayerEquippedItem[playerid][EItemBone][slotid]	= Bone;
		PlayerEquippedItem[playerid][EItemOffX][slotid] = OffX;
		PlayerEquippedItem[playerid][EItemOffY][slotid] = OffY;
		PlayerEquippedItem[playerid][EItemOffZ][slotid] = OffZ;
		PlayerEquippedItem[playerid][EItemRotX][slotid] = RotX;
		PlayerEquippedItem[playerid][EItemRotY][slotid] = RotY;
		PlayerEquippedItem[playerid][EItemRotZ][slotid] = RotZ;
		PlayerEquippedItem[playerid][EItemSclX][slotid] = SclX;
		PlayerEquippedItem[playerid][EItemSclY][slotid] = SclY;
		PlayerEquippedItem[playerid][EItemSclZ][slotid] = SclZ;
		PlayerEquippedItem[playerid][EItemCol1][slotid] = Col1;
		PlayerEquippedItem[playerid][EItemCol2][slotid] = Col2;
		SetTimerEx("SetPlayerEquippedItem", 1000, false, "iiii", playerid, slotid, model, amount);
		if(IsPlayerInInventory(playerid)) LoadInventoryEquippedItems(playerid);
	}
	
	return 1;
}

public SetPlayerEquippedItem(playerid, slotid, model, amount)
{
	switch(slotid)
	{
		case -1: 
		{
			new slot = GetAmmoEquipableSlot(model);
			GivePlayerWeapon(playerid, GetWeaponFromModel(PlayerEquippedItem[playerid][EItemModel][slot]), amount);
			PlayerEquippedItem[playerid][EItemAmount][slot] += amount;
		}
		case 0..3: GivePlayerWeapon(playerid, GetWeaponFromModel(model), amount);
		case 4..6:
		{
			printf("\n---------<debug>-----------\nSetting attachment data\nPlayer:%d\nSlot:%d\nModel:%d\nBone:%d\nOffsetX:%f\nOffsetY:%f\nOffsetZ:%f\nRotX:%f\nRotY:%f\nRotZ:%f\nScaleX:%f\nScaleY:%f\nScaleZ:%f\ncol1:%d\ncol2:%d\n----------<end>----------\n",
			playerid, slotid, model,
			PlayerEquippedItem[playerid][EItemBone][slotid],
			PlayerEquippedItem[playerid][EItemOffX][slotid],
			PlayerEquippedItem[playerid][EItemOffY][slotid],
			PlayerEquippedItem[playerid][EItemOffZ][slotid],
			PlayerEquippedItem[playerid][EItemRotX][slotid],
			PlayerEquippedItem[playerid][EItemRotY][slotid],
			PlayerEquippedItem[playerid][EItemRotZ][slotid],
			PlayerEquippedItem[playerid][EItemSclX][slotid],
			PlayerEquippedItem[playerid][EItemSclY][slotid],
			PlayerEquippedItem[playerid][EItemSclZ][slotid],
			PlayerEquippedItem[playerid][EItemCol1][slotid],
			PlayerEquippedItem[playerid][EItemCol2][slotid]);

			if(!SetPlayerAttachedObject(playerid, slotid, model,
			PlayerEquippedItem[playerid][EItemBone][slotid],
			PlayerEquippedItem[playerid][EItemOffX][slotid],
			PlayerEquippedItem[playerid][EItemOffY][slotid],
			PlayerEquippedItem[playerid][EItemOffZ][slotid],
			PlayerEquippedItem[playerid][EItemRotX][slotid],
			PlayerEquippedItem[playerid][EItemRotY][slotid],
			PlayerEquippedItem[playerid][EItemRotZ][slotid],
			PlayerEquippedItem[playerid][EItemSclX][slotid],
			PlayerEquippedItem[playerid][EItemSclY][slotid],
			PlayerEquippedItem[playerid][EItemSclZ][slotid],
			PlayerEquippedItem[playerid][EItemCol1][slotid],
			PlayerEquippedItem[playerid][EItemCol2][slotid])) print("<Attachment set fail on function SetPlayerEquippedItem!>");
			else print("<Attachment set successfully executed on function SetPlayerEquippedItem!>");
		}
	}
	return 1;
}

RemovePlayerEquippedItem(playerid, model)
{
	switch(GetEquipableModelType(model))
	{
		case 0, 1, 2, 3: SetPlayerAmmo(playerid, GetWeaponFromModel(model), 0);
	}
	return 1;
}

OnPlayerUnequipItem(playerid, slotid)
{
	if(UnableToEquip[playerid]) return 0;
	if(!CountPlayerFreeSlots(playerid)) return SendInfoText(playerid, "Inventory", "Your inventory is full, you can't unequip items now.", 3000);
	new model = PlayerEquippedItem[playerid][EItemModel][slotid];
	new amount = PlayerEquippedItem[playerid][EItemAmount][slotid];
	new itemtime = PlayerEquippedItem[playerid][EItemTime][slotid];
	new expirable = PlayerEquippedItem[playerid][EItemExpirable][slotid];
	new Float:durability = PlayerEquippedItem[playerid][EItemDurability][slotid];
	DestroyEquippedItem(playerid, slotid);
	CreatePlayerItem(playerid, model, amount, durability, itemtime, expirable);
	UnableToEquip[playerid] = true;
	RemovePlayerEquippedItem(playerid, model);
	SetTimerEx("SetPlayerAbleToEquip", 1000, false, "i", playerid);
	PlayerPlaySound(playerid, 1150, 0,0,0);
	return 1;
}

OnPlayerSelectSlot(playerid, textid, slotid, currentpage)
{
	PlayerPlaySound(playerid, 1084, 0,0,0);
	switch(currentpage)
	{
		case 1: PlayerSelectedSlot[playerid] = slotid;
		case 2: PlayerSelectedSlot[playerid] = slotid + 10;
		case 3: PlayerSelectedSlot[playerid] = slotid + 20;
		case 4: PlayerSelectedSlot[playerid] = slotid + 30;
	}
	for(new i = 20; i < 30; i++)
	{
		//clean the previous selected ids
		if(PlayerTextDrawGetBackgroundCol(playerid, InventoryText[playerid][i]) == 0xFF0000FF)
		{
			PlayerTextDrawBackgroundColor(playerid, InventoryText[playerid][i], 255);
			PlayerTextDrawShow(playerid, InventoryText[playerid][i]);
		}
		//update the selected textdraw color
		if(i == textid) PlayerTextDrawBackgroundColor(playerid, InventoryText[playerid][i], 0xFF0000FF);
		PlayerTextDrawShow(playerid, InventoryText[playerid][i]);
	}
	return 1;
	
}

ResetSelectedSlots(playerid)
{
	PlayerSelectedSlot[playerid] = -1;
	for(new i = 20; i < 30; i++)
	{
		PlayerTextDrawBackgroundColor(playerid, InventoryText[playerid][i], 255);
		if(IsPlayerInInventory(playerid)) PlayerTextDrawShow(playerid, InventoryText[playerid][i]); 
	}
	return 1;
}
public OnLoadPlayerItems(playerid)
{
	if(cache_num_rows())
	{
		for(new row; row < cache_num_rows(); row++)
		{
			static model, amount, itemid, Float:durability, itemtime, expirable;
			itemid = cache_get_field_content_int(row, "id");
			model = cache_get_field_content_int(row, "model");
			amount = cache_get_field_content_int(row, "amount");
			durability = cache_get_field_content_float(row, "durability");
			itemtime = cache_get_field_content_int(row, "time");
			expirable = cache_get_field_content_int(row, "expirable");
			if(model == DEFAULT_OBJECT_MODEL || !model) continue;
			GivePlayerItem(playerid, itemid, model, amount, durability, itemtime, expirable);
		}
	}
	return 1;
}

SavePlayerItems(playerid)
{
	new query[800];
	for(new i; i < 10 * PlayerInfo[playerid][bagtype]; i++)
	{
		if(!PlayerItem[playerid][ItemID][i] || !PlayerItem[playerid][ItemModel][i]) continue;
		mysql_format(MySQL, query, sizeof(query), "UPDATE `items` SET `owner` = '%d', `amount` = '%d', `model` = '%d',  `durability` = '%f', `time`= '%d', `expirable` = '%d', `coord_x` = '0', `coord_y` = '0', `coord_z` = '0' WHERE `id` = '%d';",
		PlayerInfo[playerid][pid], PlayerItem[playerid][ItemAmount][i], PlayerItem[playerid][ItemModel][i], PlayerItem[playerid][ItemDurability][i], PlayerItem[playerid][ItemTime][i], PlayerItem[playerid][ItemExpirable][i], PlayerItem[playerid][ItemID][i]);
		mysql_tquery(MySQL, query, "", "");
	}

	for(new e; e < MAX_EQUIPPED_INVENTORY_SLOTS; e++)
	{		
		if(!PlayerEquippedItem[playerid][EItemID][e] || !PlayerEquippedItem[playerid][EItemModel][e]) continue;
		mysql_format(MySQL, query, sizeof(query),
		"UPDATE `equiped_items` SET `amount` = %d, `modelid` = %d, `durability` = '%f', `time`= '%d', `expirable` = '%d', `itemid` = %d, `bone` = %d, `OffsetX` = '%f', `OffsetY` = '%f', `OffsetZ` = '%f', `RotX` = '%f', `RotY` = '%f', `RotZ` = '%f', `ScaleX` = '%f', `ScaleY` = '%f', `ScaleZ` = '%f', `Color1` = %d, `Color2` = %d   WHERE `playerid` = %d AND `slotid` = '%d';",
		PlayerEquippedItem[playerid][EItemAmount][e],
		PlayerEquippedItem[playerid][EItemModel][e],
		PlayerEquippedItem[playerid][EItemDurability][e],
		PlayerEquippedItem[playerid][EItemTime][e],
		PlayerEquippedItem[playerid][EItemExpirable][e],
		PlayerEquippedItem[playerid][EItemID][e],
		PlayerEquippedItem[playerid][EItemBone][e],
		PlayerEquippedItem[playerid][EItemOffX][e],
		PlayerEquippedItem[playerid][EItemOffY][e],
		PlayerEquippedItem[playerid][EItemOffZ][e],
		PlayerEquippedItem[playerid][EItemRotX][e],
		PlayerEquippedItem[playerid][EItemRotY][e],
		PlayerEquippedItem[playerid][EItemRotZ][e],
		PlayerEquippedItem[playerid][EItemSclX][e],
		PlayerEquippedItem[playerid][EItemSclY][e],
		PlayerEquippedItem[playerid][EItemSclZ][e],
		PlayerEquippedItem[playerid][EItemCol1][e],
		PlayerEquippedItem[playerid][EItemCol2][e],
		PlayerInfo[playerid][pid],
		e);
		mysql_tquery(MySQL, query, "", "");
	}
	return 1;
}

stock LoadDroppedItems()
{
	new query[64];
	mysql_format(MySQL, query, sizeof(query), "SELECT * FROM `items` WHERE `owner` = -1");
	mysql_tquery(MySQL, query, "OnDroppedItemsLoad", "");	
	return 1;
}

public OnDroppedItemsLoad()
{			
	for(new d; d < cache_num_rows(); d++)
	{
		static id, model, amount, Float:x, Float:y, Float:z, vworld, pinterior, Float:durability, itemtime, expirable;
		id = cache_get_field_content_int(d, "id");
		model = cache_get_field_content_int(d, "model");
		amount = cache_get_field_content_int(d, "amount");
		x = cache_get_field_content_float(d, "coord_x");
		y = cache_get_field_content_float(d, "coord_y");
		z = cache_get_field_content_float(d, "coord_z");
		vworld = cache_get_field_content_int(d, "world");
		pinterior = cache_get_field_content_int(d, "interior");
		durability = cache_get_field_content_float(d, "durability");
		itemtime = cache_get_field_content_int(d, "time");
		expirable = cache_get_field_content_int(d, "expirable");
		CreateDroppedItem(id, model, amount, x, y, z, vworld, pinterior, durability, itemtime, expirable);
	}	
	return 1;
}

SplitPlayerItem(playerid, slotid)
{
	if(UnableToSplit[playerid]) return 0;
	if(!CountPlayerFreeSlots(playerid)) return SendInfoText(playerid, "Inventory", "You don't have free slots to split this item!", 3000);
	if(GetWeaponFromModel(PlayerItem[playerid][ItemModel][slotid]) != -1)
	{
		UnableToSplit[playerid] = true;
		UnableToEquip[playerid] = true;
		new ammo = GetAmmoFromWeaponModel(PlayerItem[playerid][ItemModel][slotid]);
		if(!ammo) return SendInfoText(playerid, "Inventory", "We're sorry, you cannot split this type of weapon.", 3000);
		new amount = PlayerItem[playerid][ItemAmount][slotid] / 2;
		PlayerItem[playerid][ItemAmount][slotid] = amount;
		if(IsPlayerInInventory(playerid)) UpdatePlayerSlot(playerid, slotid);
		CreatePlayerItem(playerid, ammo, amount, 100.0,  PlayerItem[playerid][ItemTime][slotid], PlayerItem[playerid][ItemExpirable][slotid]);
		SetTimerEx("SetPlayerAbleToEquip", 1000, false, "i", playerid);
		SetTimerEx("SetPlayerAbleToSplit", 1000, false, "i", playerid);
		return 1;
	}
	UnableToSplit[playerid] = true;
	UnableToEquip[playerid] = true;
	SetTimerEx("SetPlayerAbleToEquip", 1000, false, "i", playerid);
	SetTimerEx("SetPlayerAbleToSplit", 1000, false, "i", playerid);
	new amount = PlayerItem[playerid][ItemAmount][slotid] / 2;
	PlayerItem[playerid][ItemAmount][slotid] = amount;
	if(IsPlayerInInventory(playerid)) UpdatePlayerSlot(playerid, slotid);
	CreatePlayerItem(playerid, PlayerItem[playerid][ItemModel][slotid], amount, 100.0,  PlayerItem[playerid][ItemTime][slotid], PlayerItem[playerid][ItemExpirable][slotid]);
	return 1;
}

OnPlayerUseItem(playerid, model, slot, itemid, use_amount)
{
	#pragma unused model
	if( PlayerItem[playerid][ItemAmount][slot] == use_amount ) DestroyPlayerItem(playerid, itemid);
	else
	{
		PlayerItem[playerid][ItemAmount][slot]--;
		UpdatePlayerSlot(playerid, slot);
	}
	PlayerPlaySound(playerid, 1083, 0,0,0);
	return 1;
}

ResetDroppedObjects()
{
	mysql_tquery(MySQL, "UPDATE `items` SET `model` = '19475' WHERE `owner` = '-1';", "OnDroppedItemsReset", "");

	return 1;
}

public OnDroppedItemsReset()
{
	print("Server dropped objects cleared...\nGenerating drop rates...");
	RegenerateLoots();
}


ResearchInventoryItem(playerid, modelid)
{
	for(new i; i < 10 * PlayerInfo[playerid][bagtype]; i++)
		if(PlayerItem[playerid][ItemID][i] && PlayerItem[playerid][ItemModel][i] == modelid) return i;

	return -1;
}