/*********************************************************************************************************/
/*                                       MAIN INCLUDES                                                   */
/*********************************************************************************************************/
#include <a_samp>
#include <colAndreas>
#include <a_mysql>
#include <progress2>
#include <streamer>
#include <foreach>
#include <YSF>
#include <CTime>
#include <ibranch>
#include <iCMD>
#include <cstl>
//#include <route>
#include <rnpc>
#include <mrandom>
//#include <timerfix>

/*********************************************************************************************************/
/*                                       SERVER DEFINES                                                  */
/*********************************************************************************************************/
#define DEV_VERSION 		"gamemodetext ..:Dev 0.1.1b:.."
#define MAX_SPAWNS 			(06000)
#define gSpawns				0xF40F4
#define fp%0(%1)								forward %0(%1); public %0(%1)
#define fs%0(%1)								stock %0(%1)


/*********************************************************************************************************/
/*                                       SERVER VARIABLES                                                */
/*********************************************************************************************************/
new blackmap;
new PlayerUpdateTimer[MAX_PLAYERS];//transformar em enum
new Float: proxSpawn[MAX_PLAYERS][3];
new szStrsPrintf[1024];

/*********************************************************************************************************/
/*                                       SERVER INCLUDES                                                 */
/*********************************************************************************************************/
//updated//


#include "../modules/server/utils.inc"
#include "../modules/sqlite/utils.inc"
#include "../modules/player/spawns.inc"
#include "../modules/paths/vectorangles.inc"
#include "../modules/server/isscanf.inc"
#include "../modules/paths/n_vectors.inc"
#include "../modules/paths/nodes.inc"
#include "../modules/server/time.inc"
#include "../modules/server/configs.inc"
#include "../modules/saves/files.inc"
#include "../modules/textdraws/textdraws.inc"
#include "../modules/textdraws/iprogress.inc"
#include "../modules/admin/main.inc"
#include "../modules/hud/main.inc"
#include "../modules/player/infobox.inc"
#include "../modules/inventory/main.inc"
#include "../modules/crafting/main.inc"
#include "../modules/maps/maps.inc"
#include "../modules/menu/main.inc"
#include "../modules/player/class.inc"
#include "../modules/actors/bodies.inc"
#include "../modules/player/anims.inc"//preload
#include "../modules/npcs/zombiesdata.inc"
#include "../modules/server/commands.inc"
/*********************************************************************************************************/
/*                                       SERVER CALLBACKS                                                */
/*********************************************************************************************************/

#pragma dynamic 30000

main()
{
	print("-------------------------------------------------------------------------------");
}


public OnGameModeInit()
{
	CA_Init();
    UsePlayerPedAnims();
   	Streamer_SetVisibleItems(STREAMER_TYPE_OBJECT, 999);
	
	print("-------------------------------------");
	print("Loading database...");
	print("-------------------------------------");
	MySQLStartConnection();

	print("-------------------------------------");
	print("Loading Spawn points...");
	print("-------------------------------------");

	if(fexist("spawns.db"))
		LoadSpawnsPos("spawns.db");
	else
		GenerateSpawns();

	SaveSpawnsPos("spawns.db");
	
	print("-------------------------------------");
	print("Loading player classes...");
	print("-------------------------------------");
	LoadClasses();
	
	print("-------------------------------------");
	print("Loading black map...");
	print("-------------------------------------");	
	blackmap = GangZoneCreate(-3500.0,-3500.0,3500.0,3500.0);
	
	print("-------------------------------------");
	print("Generating dead bodies...");
	print("-------------------------------------");
	SetupRandomDeadBodies();

	print("-------------------------------------");
	print("Generating dropped objects...");
	print("-------------------------------------");
	ResetDroppedObjects();
	
	print("-------------------------------------");
	print("Loading custom maps....");
	print("-------------------------------------");
	LoadMaps();

	print("-------------------------------------");
	print("Loading zombies...");
	print("-------------------------------------");
	LoadZombieSkins();
	//ConnectAllZombies();
    
    print("-------------------------------------");
    print("Loading server utils...");
    print("-------------------------------------");
	SetTimer("UpdateZombies",	00700, true);
	SetTimer("UpdateServer",	00900, true);
   	SetTimer("SaveAccounts", 300000, true);

 	SetWeather(26);
 	SetWorldTime(02);
 	
	ShowPlayerMarkers(PLAYER_MARKERS_MODE_STREAMED);
	LimitPlayerMarkerRadius(5.0);
	EnableStuntBonusForAll(0);
	DisableInteriorEnterExits();


	SendRconCommand(DEV_VERSION);
	SendRconCommand("mapname ..:Zombie NPCS:..");
	SendRconCommand("gravity 0.008");
	SendRconCommand("weburl http://ips-team.com");
	SendRconCommand("hostname .:[ipsTeam] Zombotech Apocalypse:.");

	print("-------------------------------------");
	print("Loading Server-Textdraws...");
	print("-------------------------------------");
	LoadServerTextDraws();

	return true;
}

public OnGameModeExit()
{
	MySQLCloseConnection();
	return 1;
}

public OnPlayerConnect(playerid)
{	
	if(!IsPlayerNPC(playerid))
	{
		PreloadAnimations(playerid);
		PlayerLoginInfo[playerid][FirstSpawn] = true;
   		ResetInventoryInfo(playerid);
   		ResetAllowanceInfo(playerid);
	    RemoveMaps(playerid);
	    CancelSelectTextDraw(playerid);
	    LoadPlayerTextDraws(playerid);
	    ClearInfoBoxData(playerid);
	    ResetInventoryInfo(playerid);
	    CleanPlayerLoginData(playerid);
	    ResetPlayerAttachments(playerid);
		SetTimerEx("OnPlayerConnected", 1000, false, "i", playerid);
		EnablePlayerCameraTarget(playerid, 1);

		
	}
	else OnPlayerSpawn(playerid);
	GetVectorPath(gSpawns, MRandom(MAX_SPAWNS), proxSpawn[playerid][0], proxSpawn[playerid][1], proxSpawn[playerid][2]);
	return true;
}

fp OnPlayerConnected(playerid)
{
	if(IsPlayerNPC(playerid)) return 1;
	TogglePlayerSpectating(playerid, 1);

    SetPlayerInterior(playerid, 1);
    SetPlayerWeather(playerid, 1);
	InterpolateCameraPos(playerid, 2527.8372, -1674.9968, 1016.3289, 2536.0066, -1674.4677, 1017.0624, 10000);
	InterpolateCameraLookAt(playerid, 2526.8403, -1674.9524, 1016.2308, 2537.0039, -1674.4753, 1016.9648, 12000);
		
	SetTimerEx("OnPlayerInterpolate", 13000, false, "i", playerid);
	
	SendClientMessage(playerid, -1, ""); SendClientMessage(playerid, -1, ""); SendClientMessage(playerid, -1, ""); SendClientMessage(playerid, -1, "");
	SendClientMessage(playerid, -1, ""); SendClientMessage(playerid, -1, ""); SendClientMessage(playerid, -1, ""); SendClientMessage(playerid, -1, "");
	SendClientMessage(playerid, -1, ""); SendClientMessage(playerid, -1, ""); SendClientMessage(playerid, -1, ""); SendClientMessage(playerid, -1, "");
	SendClientMessage(playerid, -1, ""); SendClientMessage(playerid, -1, ""); SendClientMessage(playerid, -1, ""); SendClientMessage(playerid, -1, "");
	
	return true;
}

fp OnPlayerInterpolate(playerid)
{
	ShowPlayerMainMenu(playerid);	
	PlayerUpdateTimer[playerid] = SetTimerEx("OnPlayerUpdateEx", 50, true, "i", playerid);
	return true;
}


fp OnPlayerUpdateEx(playerid)
{
	if(!IsPlayerSpawned(playerid)) return 0;
	if(GetPlayerCameraObject(playerid) == INVALID_OBJECT_ID) return 0;

	for(new item; item < MAX_ITEMS; item++)
	{
		if(!IsPlayerInRangeOfPoint(playerid, 2.5, DroppedItem[item][DItemPosX], DroppedItem[item][DItemPosY], DroppedItem[item][DItemPosZ])) continue;
		if(DroppedItem[item][DItemObj] == GetPlayerCameraObject(playerid))
		{
			PlayerTargetItem[playerid] = item;
		    return ShowPlayerLootInfo(playerid, item);	
		}
	}

	return HidePlayerLootInfo(playerid);
}


public OnPlayerRequestSpawn(playerid)
{
	if(PlayerLoginInfo[playerid][Selecting]) return 0;
	if(!IsPlayerNPC(playerid))
	{
		SetPlayerVirtualWorld(playerid, 0);
		ShowPlayerHUD(playerid);
	}	
	return 1;
}

public OnPlayerRequestClass(playerid, classid)
{
	if(IsPlayerNPC(playerid)) return true;
	PlayerInfo[playerid][RequestingClass] = true;
	if(GetPVarInt(playerid, "SpawnLiberado")) return true;
	return false;
	
}

public OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ)
{
    if(IsPlayerAdmin(playerid)) return SetPlayerPosFindZ(playerid, fX, fY, fZ);
    
    return true;
}

public OnPlayerAmmoChange(playerid, weaponid, newammo, oldammo)
{
	new slot = GetEquipableModelType(GetModelFromWeapon(weaponid));
	if(0 <= slot <= 3)
		PlayerEquippedItem[playerid][EItemAmount][slot] = newammo;
	else return printf("Server skipped ammo data for user %s (%d, %d, %d)", GetPlayerNameEx(playerid), weaponid, newammo, oldammo);
	return 1;
}

public OnPlayerCurrentWeaponChange(playerid, new_weapon, oldweapon)
{
	new color, Float:rx, Float:ry, Float:rz, Float:zoom;
	PlayerTextDrawFont(playerid, HUDText[playerid][41], !new_weapon ? 4 : 5);
	GetObjectTXDInfo(GetModelFromWeapon(new_weapon), color, rx, ry, rz, zoom);
	PlayerTextDrawSetPreviewRot(playerid, HUDText[playerid][41], rx, ry, rz, 1.2);
	PlayerTextDrawSetPreviewModel(playerid, HUDText[playerid][41], GetModelFromWeapon(new_weapon));
	if(!IsPlayerInInventory(playerid)) PlayerTextDrawShow(playerid, HUDText[playerid][41]);

	
	return 1;
}

public OnPlayerText(playerid, text[])
{
	if(!GetPVarInt(playerid, "SpawnLiberado")) return false;
 	return true;
}

public OnPlayerSpawn(playerid)
{
	if(!IsPlayerNPC(playerid))
	{
		if(PlayerLoginInfo[playerid][FirstSpawn]) 
		{
			LoadPlayerItems(playerid);
			PlayerLoginInfo[playerid][FirstSpawn] = false;
			LoadPlayerSavedData(playerid);
		}
		else
		{
			ReloadPlayerAttachments(playerid);
			ReloadPlayerWeapons(playerid);
			SetPlayerPos(playerid, proxSpawn[playerid][0],proxSpawn[playerid][1],proxSpawn[playerid][2]+1.0);
		} 

		PlayerInfo[playerid][RequestingClass] = false;
		SetCameraBehindPlayer(playerid);
		GangZoneShowForPlayer(playerid, blackmap, 0x000000FF);
		//ShowPlayerAim(playerid);
    }
	SetTimerEx("ActiveSpawn", 500, false,  "d", playerid);
	
	if(IsPlayerNPC(playerid)) 
	{
	    SetPVarInt(playerid, "SpawnLiberado", 1); 	   
        SetPlayerPos(playerid, proxSpawn[playerid][0],proxSpawn[playerid][1],proxSpawn[playerid][2]+1.0);
		return true;
	}
	return true;
}


public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if(newkeys & KEY_YES)
	{
	    if(!IsPlayerInInventory(playerid))
	    {
	    	HidePlayerLootInfo(playerid);
	    	HidePlayerHUD(playerid);
	    	ShowPlayerInventory(playerid);
	    }
		else
		{
			ShowPlayerHUD(playerid);
			HidePlayerInventory(playerid);
		} 
	}
	if(newkeys & KEY_NO && PlayerTargetItem[playerid] && !IsPlayerInAnyVehicle(playerid))
	{
	    if(!CountPlayerFreeSlots(playerid)) return SendInfoText(playerid, "Inventory", "Your inventory is full, you can not pickup more items!", 3000);
	    if(UnableToPickup[playerid]) return 1;
	    new itemid = PlayerTargetItem[playerid],
	    model = DroppedItem[itemid][DItemModel],
		amount = DroppedItem[itemid][DItemAmount],
		Float:durability = DroppedItem[itemid][DItemDurability],
		itime = DroppedItem[itemid][DItemTime],
		expirable = DroppedItem[itemid][DItemExpirable];
        GivePlayerItem(playerid, itemid, model, amount, durability, itime, expirable);
        RemoveDroppedItem(itemid);
        SavePlayerItems(playerid);
        UnableToPickup[playerid] = true;
        SetTimerEx("SetPlayerAbleToPickup", 1000, false, "i", playerid);
	}
	return true;
}

public OnPlayerClickPlayerTextDraw(playerid, PlayerText:playertextid)
{
	if(playertextid == InfoBoxText[playerid][8]) return HideInfoBox(playerid);

	if(playertextid == RegisterScreenText[playerid][0]) ShowPlayerDialog(playerid, DIALOG_REGISTER_NAME, DIALOG_STYLE_INPUT, "{FF0000}Insert your nickname!",   "Insert your nickname on the box below to register.\n\n\n{FF0000}WARNING: If your nickname contains special characters, it might be broken into the register screen.\n{FFFFFF}But don't worry, it doesn't affect the typed text.\nMax Lenght: {FF0000}18", "Done", "");
	if(playertextid == RegisterScreenText[playerid][1]) ShowPlayerDialog(playerid, DIALOG_REGISTER_PASSWORD, DIALOG_STYLE_PASSWORD, "{FF0000}Insert your password!", "Insert your password on the box below to register.\n\n\n{FF0000}Your password will be hidden, don't worry, zombies can't see it.\nMax Lenght: {FF0000}16", "Done", "");
	if(playertextid == RegisterScreenText[playerid][2]) ShowPlayerDialog(playerid, DIALOG_REGISTER_REPASSWORD, DIALOG_STYLE_PASSWORD, "{FF0000}Repeat your password!", "Repeat your password below to confirm.\n\n\n{FF0000}Your password will be hidden, don't worry, zombies can't see it.\nMax Lenght: {FF0000}16", "Done", "");
	if(playertextid == RegisterScreenText[playerid][3]) ShowPlayerDialog(playerid, DIALOG_REGISTER_MAIL, DIALOG_STYLE_INPUT, "{FF0000}Insert your mail!", "Insert a valid mail here, so if you lost your password you can recover by your mail\n{FF0000}WARNING: If your mail contains special characters, it might be broken into the register screen.\n{FFFFFF}But don't worry, it doesn't affect the typed text.\nMax Lenght: {FF0000}32", "Done", "");

	if(playertextid == LoginScreenText[playerid][0]) ShowPlayerDialog(playerid, DIALOG_LOGIN_NAME, DIALOG_STYLE_INPUT, "{FF0000}Insert your nickname!", "Insert your nickname on the box below to login.\n\n\n{FF0000}WARNING: If your nickname contains special characters, it might be broken into the login screen.\n{FFFFFF}But don't worry, it doesn't affect the typed text.", "Done", "");
	if(playertextid == LoginScreenText[playerid][1]) ShowPlayerDialog(playerid, DIALOG_LOGIN_PASSWORD, DIALOG_STYLE_PASSWORD, "{FF0000}Insert your password!", "Insert your password on the box below to login.\n\n\n{FF0000}Your password will be hidden, don't worry, zombies can't see it.", "Done", "");
 	if(playertextid == InventoryText[playerid][5]) HidePlayerInventory(playerid);
	if(playertextid == InventoryText[playerid][63])
	{
		if(CurrentInventoryPage[playerid] == 1) return 0;	    
	    CurrentInventoryPage[playerid] --;
		LoadInventoryPageItems(playerid);
		LoadPlayerBagInfo(playerid);
		return 1;
	}
	if(playertextid == InventoryText[playerid][64])
	{
		if(PlayerInfo[playerid][bagtype] == 1) return 0;
	    if(CurrentInventoryPage[playerid] == 1 && PlayerInfo[playerid][bagtype] < 2) return 0;
	    if(CurrentInventoryPage[playerid] == 2 && PlayerInfo[playerid][bagtype] < 3) return 0;
	    if(CurrentInventoryPage[playerid] == 3 && PlayerInfo[playerid][bagtype] < 4) return 0;
	    if(CurrentInventoryPage[playerid] == 4) return 0;
	    
		CurrentInventoryPage[playerid] ++;
		LoadInventoryPageItems(playerid);
		LoadPlayerBagInfo(playerid);
		return 1;	
	}
	
	if(playertextid == InventoryText[playerid][31] && PlayerEquippedItem[playerid][EItemID][0] && !UnableToEquip[playerid]) return OnPlayerUnequipItem(playerid, 0);//weapon 0
	if(playertextid == InventoryText[playerid][36] && PlayerEquippedItem[playerid][EItemID][1] && !UnableToEquip[playerid]) return OnPlayerUnequipItem(playerid, 1);//weapon 1
	if(playertextid == InventoryText[playerid][41] && PlayerEquippedItem[playerid][EItemID][2] && !UnableToEquip[playerid]) return OnPlayerUnequipItem(playerid, 2);//weapon 2
	if(playertextid == InventoryText[playerid][46] && PlayerEquippedItem[playerid][EItemID][3] && !UnableToEquip[playerid]) return OnPlayerUnequipItem(playerid, 3);//weapon 3
	if(playertextid == InventoryText[playerid][53] && PlayerEquippedItem[playerid][EItemID][4] && !UnableToEquip[playerid]) return OnPlayerUnequipItem(playerid, 4);//wear 1
	if(playertextid == InventoryText[playerid][56] && PlayerEquippedItem[playerid][EItemID][5] && !UnableToEquip[playerid]) return OnPlayerUnequipItem(playerid, 5);//wear 2
	if(playertextid == InventoryText[playerid][59] && PlayerEquippedItem[playerid][EItemID][6] && !UnableToEquip[playerid]) return OnPlayerUnequipItem(playerid, 6);//wear 3
	if(playertextid == InventoryText[playerid][15] && PlayerEquippedItem[playerid][EItemID][7] && !UnableToEquip[playerid]) return OnPlayerUnequipItem(playerid, 7);//padlock


	for(new i = 20; i < 30; i++) if(playertextid == InventoryText[playerid][i]) return OnPlayerSelectSlot(playerid, i, i - 20, CurrentInventoryPage[playerid]);
	
	if(playertextid == InventoryText[playerid][0])
	{
		
		new slot = PlayerSelectedSlot[playerid];

		if(IsObjectUsable(PlayerItem[playerid][ItemModel][slot])) return OnPlayerUseItem(playerid, PlayerItem[playerid][ItemModel][slot], slot, PlayerItem[playerid][ItemID][slot],  1);

		return SendInfoText(playerid, "Inventory", "You can't use this kind of item", 3000);
	}
	if(playertextid == InventoryText[playerid][1])
	{
		new slot = PlayerSelectedSlot[playerid];
		new itemid = PlayerItem[playerid][ItemID][slot];		
		new model = PlayerItem[playerid][ItemModel][slot];
		new amount = PlayerItem[playerid][ItemAmount][slot];
		new Float:durability = PlayerItem[playerid][ItemDurability][slot];
		new itime = PlayerItem[playerid][ItemTime][slot];
		new expirable = PlayerItem[playerid][ItemExpirable][slot];

		if(slot == -1 || itemid == -1 || GetEquipableModelType(model) == 10 || GetEquipableModelType(model) == 8) return SendInfoText(playerid, "Inventory", "You can't equip this kind of item!", 5000);
		OnPlayerEquipItem(playerid, GetEquipableModelType(model), itemid, model, amount, durability, itime, expirable, false);
		return 1;
	}
	if(playertextid == InventoryText[playerid][2])
	{
		if(IsPlayerInAnyVehicle(playerid)) return SendInfoText(playerid, "Inventory", "You can't drop items while driver or passenger", 4000);
		new slot = PlayerSelectedSlot[playerid];
		new itemid = PlayerItem[playerid][ItemID][slot];		
		new model = PlayerItem[playerid][ItemModel][slot];
		new amount = PlayerItem[playerid][ItemAmount][slot];
		new Float:durability = PlayerItem[playerid][ItemDurability][slot];
		new itime = PlayerItem[playerid][ItemTime][slot];
		new expirable = PlayerItem[playerid][ItemExpirable][slot];

		if(slot == -1 || itemid == -1 || !itemid || !model) return SendInfoText(playerid, "Inventory", "Empty slot or invalid item!", 4000);
		return DropPlayerItem(playerid, itemid,  model, amount, durability, itime, expirable);
	}
	if(playertextid == InventoryText[playerid][3])
	{
		new slot = PlayerSelectedSlot[playerid];

		if(!PlayerItem[playerid][ItemID][slot] || PlayerItem[playerid][ItemID][slot] == -1 || PlayerItem[playerid][ItemID][slot] == DEFAULT_OBJECT_MODEL) return SendInfoText(playerid, "Inventory", "You must select a item to split.", 3000);
		if(PlayerItem[playerid][ItemTime][slot]) return SendInfoText(playerid, "Inventory", "You cannot split an expirable item!", 3000);
		if(PlayerItem[playerid][ItemAmount][slot] < 50) return SendInfoText(playerid, "Inventory", "You cannot split item with this item (minimum amount: 50)!", 3000);
		
		SplitPlayerItem(playerid, slot);
		return 1;
	}
	if(playertextid == InventoryText[playerid][19])
	{
		if(PlayerInfo[playerid][bagtype] > 1 && PlayerEquippedItem[playerid][EItemModel][8])
		{
			if(IsBackPackClean(playerid))
			{
				if(CountPlayerPageFreeSlots(playerid, 1) < 1) return SendInfoText(playerid, "Inventory", "You need at least one empty slot to unequip this backpack!", 3000);
				CreatePlayerItem(playerid, PlayerEquippedItem[playerid][EItemModel][8], 1, 100.0, PlayerEquippedItem[playerid][EItemTime][8], PlayerEquippedItem[playerid][EItemExpirable][8]);
				return SetPlayerBagType(playerid, 1, 0, 19475, 100.0, 0, 0, true);
			}
			else return SendInfoText(playerid, "Inventory", "You can't remove a backpack while still have items on second page and ahead!", 3000);
		}
		return SendInfoText(playerid, "Inventory", "You don't have a backpack!", 3000);
	}
	if(playertextid == InventoryText[playerid][65])
	{
		if(!PlayerEquippedItem[playerid][EItemModel][4] || !PlayerEquippedItem[playerid][EItemID][4]) return SendInfoText(playerid, "Inventory", "You aren't using any item to edit.", 3000);
		HidePlayerInventory(playerid);
		EditAttachedObject(playerid, 4);
		return 1;
	}
	if(playertextid == InventoryText[playerid][66])
	{
		if(!PlayerEquippedItem[playerid][EItemModel][5] || !PlayerEquippedItem[playerid][EItemID][5]) return SendInfoText(playerid, "Inventory", "You aren't using any item to edit.", 3000);
		HidePlayerInventory(playerid);
		EditAttachedObject(playerid, 5);
		return 1;
	}
	if(playertextid == InventoryText[playerid][67])
	{
		if(!PlayerEquippedItem[playerid][EItemModel][6] || !PlayerEquippedItem[playerid][EItemID][6]) return SendInfoText(playerid, "Inventory", "You aren't using any item to edit.", 3000);
		HidePlayerInventory(playerid);
		EditAttachedObject(playerid, 6);
		return 1;
	}
	if(playertextid == InventoryText[playerid][18])
	{
		if(PlayerInfo[playerid][bagtype] <= 1) return SendInfoText(playerid, "Inventory", "You aren't using any backpack to edit.", 3000);
		HidePlayerInventory(playerid);
		EditAttachedObject(playerid, 8);
		//put color info here
	}
	if(playertextid == InventoryText[playerid][15])
	{
		if(PlayerEquippedItem[playerid][EItemModel][7] == 19804 && PlayerEquippedItem[playerid][EItemID][7] && PlayerEquippedItem[playerid][EItemTime][7] > gettime())
		{
			new itime = PlayerEquippedItem[playerid][EItemTime][7], iexpirable = PlayerEquippedItem[playerid][EItemExpirable][7];
			RemoveEquippedItem(playerid, 7);
			CreatePlayerItem(playerid, 19804, 1, 100.0, itime, iexpirable);
			return 1;
		}
		return SendInfoText(playerid, "Inventory", "You don't have a valid padlock equiped!", 3000);
	}
	return 1;
}

public OnPlayerClickTextDraw(playerid, Text:clickedid)
{
	if(_:clickedid == INVALID_TEXT_DRAW)
	{
		if(IsPlayerInInventory(playerid)) HidePlayerInventory(playerid);
		if(PlayerLoginInfo[playerid][Selecting]) SelectTextDraw(playerid, 0xFF0000FF);
	}
	if(clickedid == LoginScreenStatic[19] && PlayerLoginInfo[playerid][PlayerLoginName] && PlayerLoginInfo[playerid][PlayerLoginPassword]) VerifyPlayerLogin(playerid, PlayerLoginInfo[playerid][PlayerLoginName], PlayerLoginInfo[playerid][PlayerLoginPassword]); 
	if(clickedid == StartScreenStatic[25]) OnPlayerSelectMenuOption(playerid, 0);
	if(clickedid == StartScreenStatic[26]) OnPlayerSelectMenuOption(playerid, 1);
	if(clickedid == StartScreenStatic[29]) OnPlayerSelectMenuOption(playerid, 4);
	if(clickedid == LoginScreenStatic[22] || clickedid == RegisterScreenStatic[25] || clickedid == CreditScreenStatic[20]) OnPlayerSelectMenuOption(playerid, 5);
	if(clickedid == RegisterScreenStatic[22])
	{
		if(3 > strlen(PlayerLoginInfo[playerid][PlayerRegisterName]) > 17 || 3 > strlen(PlayerLoginInfo[playerid][PlayerRegisterPassword]) > 16 || 3 > strlen(PlayerLoginInfo[playerid][PlayerRegisterRePassword]) > 16 || 6 > strlen(PlayerLoginInfo[playerid][PlayerRegisterMail]) > 32)	return SendInfoText(playerid, "Registration Failure", "You left some empty field, complete the fields with your information to proceed with your registration!", 4000);
			
		if(strcmp(PlayerLoginInfo[playerid][PlayerRegisterPassword], PlayerLoginInfo[playerid][PlayerRegisterRePassword]))
			return SendInfoText(playerid, "Registration Failure", "The inputted passwords doesn't match, please check your password to continue!", 6000);

		new query[256];
		mysql_format(MySQL, query, 256, "SELECT * FROM `users` WHERE `name` = '%s';", PlayerLoginInfo[playerid][PlayerRegisterName]);
		new Cache:result = mysql_query(MySQL, query, true);

		if(cache_num_rows())
		{
			SendInfoText(playerid, "Registration Failure", "There is already an account with this nickname, please, choose a different name and try again!", 6000);
			return cache_delete(result);
		}
		new HashedPass[32];
		SHA256_PassHash(PlayerLoginInfo[playerid][PlayerRegisterRePassword], "ztah", HashedPass, sizeof HashedPass);
		
		mysql_format(MySQL, query, 256, "INSERT INTO `users` VALUES (NULL, '%s', '%s', '%s',   '0',  '0',  '0',  '0',  '0',  '0',  '100',  '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',  '1');", PlayerLoginInfo[playerid][PlayerRegisterName], HashedPass, PlayerLoginInfo[playerid][PlayerRegisterMail]);
		mysql_tquery(MySQL, query, "OnPlayerRegister", "i", playerid);
		return cache_delete(result);
	}
	return 1;
}

public OnPlayerEditAttachedObject(playerid, response, index, modelid, boneid, Float:fOffsetX, Float:fOffsetY, Float:fOffsetZ, Float:fRotX, Float:fRotY, Float:fRotZ, Float:fScaleX, Float:fScaleY, Float:fScaleZ)
{
	if(!response)//discard changes
	{
		SendClientMessage(playerid, 0x00FF00, "Attached object edition has been discarded.");
        SetPlayerAttachedObject(playerid, index, modelid, boneid, 
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
	else
	{
		if(-0.5 < fOffsetX > 0.5 || -0.5 < fOffsetY > 0.5 || -0.3 < fOffsetZ > 0.3)
		{
			SendClientMessage(playerid, 0xFF0000FF, "Attached object offsets too far from character, all the changes has been cleared!");
			SetPlayerAttachedObject(playerid, index, modelid, boneid, 
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
			return 1;
		}
		if(-1.5 < fScaleX > 1.5 || -1.5 < fScaleY >  1.5 || -1.5 < fScaleZ > 1.5)
		{
			SendClientMessage(playerid, 0xFF0000FF, "Attached object sizes too big, all the changes has been cleared!");
			SetPlayerAttachedObject(playerid, index, modelid, boneid, 
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
		SendClientMessage(playerid, 0x00FF00FF, "Attached object settings successfully saved!");
		PlayerEquippedItem[playerid][EItemOffX][index] = fOffsetX;
		PlayerEquippedItem[playerid][EItemOffY][index] = fOffsetY;
		PlayerEquippedItem[playerid][EItemOffZ][index] = fOffsetZ;
		PlayerEquippedItem[playerid][EItemRotX][index] = fRotX;
		PlayerEquippedItem[playerid][EItemRotY][index] = fRotY;
		PlayerEquippedItem[playerid][EItemRotZ][index] = fRotZ;
		PlayerEquippedItem[playerid][EItemSclX][index] = fScaleX;
		PlayerEquippedItem[playerid][EItemSclY][index] = fScaleY;
		PlayerEquippedItem[playerid][EItemSclZ][index] = fScaleZ;
	}
	return 1;
}

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	switch(dialogid)
	{
		case DIALOG_SPAWN_ITEMS:
		{
			if(!response) return 1;
			SelectedSpawnItem[playerid] = listitem;
			return ShowPlayerDialog(playerid, DIALOG_SPAWN_ITEMS_AMOUNT, DIALOG_STYLE_INPUT, "{FF0000}How many?", "{666666}How many items do you want?", "Done", "Cancel");
		}
		case DIALOG_SPAWN_ITEMS_AMOUNT:
		{
			if(!response) return SelectedSpawnItem[playerid] = 0;
			
			return CreatePlayerItem(playerid, ObjectsInfo[SelectedSpawnItem[playerid]][Object_Model], strval(inputtext), 100.0, 0, 0);
		}
		case DIALOG_LOGIN_NAME:
		{
			if(~strfind(inputtext, ";") || ~strfind(inputtext, "--")) return SendInfoText(playerid, "Warning", "Your information contain unallowed characters", 3000);
			if(response && 3 < strlen(inputtext) < 19) OnPlayerInputField(playerid, FIELD_LOGIN_NAME, inputtext); 
			else OnPlayerInputField(playerid, INVALID_FIELD_ID, "");
		}
		case DIALOG_LOGIN_PASSWORD:
		{
			if(~strfind(inputtext, ";") || ~strfind(inputtext, "--")) return SendInfoText(playerid, "Warning", "Your information contain unallowed characters", 3000);
			if(response && 3 < strlen(inputtext) < 17) OnPlayerInputField(playerid, FIELD_LOGIN_PASSWORD, inputtext); 
			else OnPlayerInputField(playerid, INVALID_FIELD_ID, "");
		}
		case DIALOG_REGISTER_NAME:
		{
			if(~strfind(inputtext, ";") || ~strfind(inputtext, "--")) return SendInfoText(playerid, "Warning", "Your information contain unallowed characters", 3000);
			if(response && 3 < strlen(inputtext) < 19) OnPlayerInputField(playerid, FIELD_REGISTER_NAME, inputtext);
			else OnPlayerInputField(playerid, INVALID_FIELD_ID, "");
		}
		case DIALOG_REGISTER_PASSWORD:
		{
			if(~strfind(inputtext, ";") || ~strfind(inputtext, "--")) return SendInfoText(playerid, "Warning", "Your information contain unallowed characters", 3000);
			if(response && 3 < strlen(inputtext) < 17) OnPlayerInputField(playerid, FIELD_REGISTER_PASSWORD, inputtext);
			else OnPlayerInputField(playerid, INVALID_FIELD_ID, "");
		}
		case DIALOG_REGISTER_REPASSWORD:
		{
			if(~strfind(inputtext, ";") || ~strfind(inputtext, "--")) return SendInfoText(playerid, "Warning", "Your information contain unallowed characters", 3000);
			if(response && 3 < strlen(inputtext) < 17) OnPlayerInputField(playerid, FIELD_REGISTER_REPASSWORD, inputtext);
			else OnPlayerInputField(playerid, INVALID_FIELD_ID, "");
		}
		case DIALOG_REGISTER_MAIL:
		{
			if(~strfind(inputtext, ";") || ~strfind(inputtext, "--")) return SendInfoText(playerid, "Warning", "Your information contain unallowed characters", 3000);
			if(response && 8 < strlen(inputtext) < 33 && strfind(inputtext , "@") > 0) OnPlayerInputField(playerid, FIELD_REGISTER_MAIL, inputtext);
			else OnPlayerInputField(playerid, INVALID_FIELD_ID, "");
		}
	}
	return 1;
}
public OnPlayerDeath(playerid, killerid, reason)
{
	if(!IsPlayerNPC(playerid)) ClearAnimations(playerid);
	SetPVarInt(playerid, "spawned", 0);
    GetVectorPath(gSpawns, MRandom(MAX_SPAWNS), proxSpawn[playerid][0], proxSpawn[playerid][1], proxSpawn[playerid][2]);
    return 1;
}



public OnPlayerDisconnect(playerid, reason)
{
	if(!IsPlayerNPC(playerid))
	{		
		if(PlayerInfo[playerid][logged] && !PlayerInfo[playerid][RequestingClass]) PlayerFileSave(playerid);
		KillTimer(PlayerUpdateTimer[playerid]);
		PlayerInfo[playerid][logged] = false;
	}
	return true;
}