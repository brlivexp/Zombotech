/*********************************************************************************************************/
/*                                       MAIN INCLUDES                                                   */
/*********************************************************************************************************/
#include <a_samp>
#include <colAndreas>
#include <a_mysql>
#include <progress2>
#include <streamer>
#include <YSF>
#include <cuf>
#include <CTime>
#include <ibranch>
#include <iCMD>
#include <cstl>
#include <route>
//#include <timerfix>

/*********************************************************************************************************/
/*                                       SERVER DEFINES                                                  */
/*********************************************************************************************************/
#define DEV_VERSION "gamemodetext ..:Dev 0.1.1a:.."

#define MAX_ZOMBIES			(00350)
#define MAX_MAPPER          (80000)
#define MAX_SPAWNS 			(06000)
#define MIN_DIS				150.0 
#define ITEMS_BOX           (00013)


#define gPlayersOnline				0xF40F2
#define gBotsOnline					0xF40F3
#define gSpawns						0xF40F4

#define gPlayersStream[%0]			(0xF40F5 + %0)
#define gVehiclesStream[%0]			(0xF4240 + %0)

#define rvelocity (float(MRandom(40)) * 0.0001)

#define sprintf(%1) \
		(format(szStrsPrintf, 1024, %1),szStrsPrintf)

#define db_get_field_float(%0,%1) \
        (db_get_field_assoc(%0,%1,szStrsPrintf,1024),floatstr(szStrsPrintf))


#define db_get_field_val(%0,%1) \
        (db_get_field_assoc(%0,%1,szStrsPrintf,1024),strval(szStrsPrintf))

/*********************************************************************************************************/
/*                                       SERVER VARIABLES                                                */
/*********************************************************************************************************/

new bool: IsWalking			[MAX_PLAYERS char] ;
new bool: IsCalculating		[MAX_PLAYERS char] ;
new bool: IsDeadNPC         [MAX_PLAYERS char] ;
new bool: IsStoppedNPC      [MAX_PLAYERS char] ;

new currentVector 			[MAX_PLAYERS] ;

new ZombiesIDS 				[MAX_PLAYERS] 	= {	0xFFFFFFFF, 	...};
new playerFollowing			[MAX_PLAYERS] 	= {	0xFFFFFFFF, 	...};
new blackmap;

new Float: proxSpawn[MAX_PLAYERS][3];


static szStrsPrintf[1024];

new bool:unabletohit[MAX_PLAYERS char];
new hitzombietimer[MAX_PLAYERS];
new Float:ZombieHealth[MAX_PLAYERS];
new PlayerUpdateTimer[MAX_PLAYERS];
/*********************************************************************************************************/
/*                                       SERVER INCLUDES                                                 */
/*********************************************************************************************************/
#include "../modules/server/isscanf.inc"
#include "../modules/npcs/rnpc.inc"
#include "../modules/npcs/fixnpc.inc"
#include "../modules/paths/nodes.inc"
#include "../modules/server/time.inc"
#include "../modules/server/configs.inc"
#include "../modules/paths/vectorangles.inc"
#include "../modules/paths/merrandom.inc"
#include "../modules/saves/files.inc"
#include "../modules/textdraws/textdraws.inc"
#include "../modules/textdraws/iprogress.inc"
#include "../modules/admin/main.inc"
#include "../modules/HUD/main.inc"
#include "../modules/player/infobox.inc"
#include "../modules/inventory/inventory.inc"
//#include "../modules/vehicles.inc"
#include "../modules/npcs/utils.inc"
#include "../modules/paths/diagonalroute.inc"
#include "../modules/server/commands.inc"
#include "../modules/paths/n_vectors.inc"
#include "../modules/maps/maps.inc"
#include "../modules/menu/main.inc"
#include "../modules/player/class.inc"

/*********************************************************************************************************/
/*                                       SERVER CALLBACKS                                                */
/*********************************************************************************************************/

#pragma dynamic 30000

main()
{
	print("Raaaaaawr...");
}


public OnGameModeInit()
{
	CA_Init();
    UsePlayerPedAnims();
   	Streamer_SetVisibleItems(STREAMER_TYPE_OBJECT, 999);

	npc.SetRate(100);
	
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
	ConnectAllZombies();
    
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
		vector_push_back(gPlayersOnline, playerid);
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

	/*switch(new_weapon)
	{
		case 34, 35: return HidePlayerAim(playerid);
		default: return ShowPlayerAim(playerid);
	}*/
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
		GangZoneShowForPlayer(playerid, blackmap, 0x394952FF);
		//ShowPlayerAim(playerid);
    }
	SetTimerEx("ActiveSpawn", 500, false,  "d", playerid);
	
	ApplyAnimation(playerid,	"KNIFE", 		"null", 0.0,0,0,0,0,0,0);
	ApplyAnimation(playerid,	"PED", 			"null", 0.0,0,0,0,0,0,0);
	ApplyAnimation(playerid,	"RIOT", 		"null", 0.0,0,0,0,0,0,0);
	ApplyAnimation(playerid,	"CARRY", 		"null", 0.0,0,0,0,0,0,0);
	ApplyAnimation(playerid, 	"ON_LOOKERS", 	"null", 0.0,0,0,0,0,0,0);
	ApplyAnimation(playerid, 	"BD_FIRE", 		"null", 0.0,0,0,0,0,0,0);
	
	if(IsPlayerNPC(playerid)) 
	{
		ZombieHealth[playerid] = 100.0;
	    SetPVarInt(playerid, "SpawnLiberado", 1);
	    
	    SetPlayerAttachedObject( playerid, 0, 3003, 2, 0.085594, 0.082489, 0.028680, 0.000000, 0.000000, 0.000000, 0.613528, 0.576035, 0.475660, 0xFFCC9900, 0xFFCC9900 ); // k_poolballcue - olho esquerdo
		SetPlayerAttachedObject( playerid, 1, 3003, 2, 0.082179, 0.079389, -0.033194, 345.747283, 63.987533, 0.000000, 0.613528, 0.576035, 0.475660, 0xFFCC9900, 0xFFCC9900); // k_poolballcue - olho direito
		SetPlayerAttachedObject( playerid, 2, 2804, 1, 0.099359, 0.138227, -0.014541, 256.316284, 7.421461, 296.197753, 0.669468, 0.600000, 0.579540, 0xFF700000, 0xFF700000 ); // CJ_MEAT_1 - peito direito
		SetPlayerAttachedObject( playerid, 3, 2804, 1, 0.086654, 0.138227, 0.008487, 97.806625, 359.692108, 296.197753, 0.669468, 0.600000, 0.579540, 0xFF700000, 0xFF700000); // CJ_MEAT_1 - peito esquerdo
		SetPlayerAttachedObject( playerid, 4, 2806, 1, 0.000000, 0.152520, 0.000000, 263.708404, 0.000000, 287.533843, 0.344415, 0.200000, 0.393224, 0xFF700000, 0xFF700000 ); // CJ_MEAT_2 - estomago
		SetPlayerAttachedObject( playerid, 5, 2806, 3, 0.086628, 0.020558, 0.030311, 148.828826, 0.000000, 286.031402, 0.229553, 0.200000, 0.306282, 0xFF700000, 0xFF700000 ); // CJ_MEAT_2 - ombro esquerdo
		SetPlayerAttachedObject( playerid, 6, 2806, 4, 0.155685, 0.011566, -0.042313, 132.740859, 96.022956, 211.319015, -0.098667, 0.091859, -0.909853, 0xFF700000, 0xFF700000 ); // CJ_MEAT_2 - ombro direito
		SetPlayerAttachedObject( playerid, 7, 2806, 2, 0.018751, 0.052789, -0.053213, 16.325899, 12.536803, 272.266479, -0.125444, 0.100000, -0.127154, 0xFF700000, 0xFF700000 ); // CJ_MEAT_2 - bochecha direita
		SetPlayerAttachedObject( playerid, 8, 2806, 2, 0.033698, 0.043727, 0.0, 354.842315, 354.532623, 285.991363, -0.125444, 0.100000, -0.127154, 0xFF700000, 0xFF700000 ); // CJ_MEAT_2 - bochecha esq
		SetPlayerAttachedObject( playerid, 9, 2804, 1, 0.05, -0.02, 0.00, 87.0, -19.0, -63.0, 0.62, 0.68, 0.62, 0xFF700000, 0xFF700000);
        SetPlayerPos(playerid, proxSpawn[playerid][0],proxSpawn[playerid][1],proxSpawn[playerid][2]+1.0);
        SetPlayerSkin(playerid, 162);
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
	static idx ;
	
	if(IsPlayerNPC(playerid)) {
		~(idx = vector_find(gBotsOnline, playerid)) && vector_remove(gBotsOnline, idx);
	}
	else
	{
		~(idx = vector_find(gPlayersOnline, playerid)) && vector_remove(gPlayersOnline, idx);
	}
	return true;
}





public OnPlayerStreamOut(playerid, forplayerid)
{
    if(!IsPlayerNPC(playerid) && IsPlayerNPC(forplayerid)) {
    
		static
			idx ;
			
		~(idx = vector_find(gPlayersStream[forplayerid], playerid)) && vector_remove(gPlayersStream[forplayerid], idx);
    }
    return 1;
}




public OnPlayerStreamIn(playerid, forplayerid)
{
    if(!IsPlayerNPC(playerid) && IsPlayerNPC(forplayerid)) {
        vector_push_back(gPlayersStream[forplayerid], playerid);
    }
    return 1;
}




public OnPlayerGiveDamage(playerid, damagedid, Float: amount, weaponid, bodypart)
{
	if(IsPlayerNPC(damagedid))
	{
	    if( IsDeadNPC{damagedid} )return false;
		
		ClearAnimations(damagedid);
		ApplyAnimation(damagedid, "DILDO", "DILDO_Hit_1", 4.1, 0, 1, 1, 1, 1000, 1);
		unabletohit[damagedid] = true;
		KillTimer(hitzombietimer[damagedid]);
		hitzombietimer[damagedid] = SetTimerEx("OnNPCTakeMeleeDamage", 1000, false, "i", damagedid);
		
		switch(weaponid)
		{
		    case 0..15, 42: ZombieHealth[damagedid] -= 20.0;
			case 22, 23: ZombieHealth[damagedid] -=30.0;
			case 24: ZombieHealth[damagedid] -= 50.0;
			case 25..27: ZombieHealth[damagedid] -= 65.0;
			case 28, 29, 32: ZombieHealth[damagedid] -= 28.0;
			case 30, 31: ZombieHealth[damagedid] -= 80.0;
			case 33, 34: ZombieHealth[damagedid] -= 100.0;
			default: ZombieHealth[damagedid] -= 50.0;
		}
		
	    if(bodypart == 9) KillZombie(damagedid);

		
		if(ZombieHealth[damagedid] <= 0.0) KillZombie(damagedid);
	}
	return true;
}

KillZombie(zombieid)
{
    ClearAnimations(zombieid);
	npc.Stop(zombieid);

	ApplyAnimation(zombieid, "KNIFE", "KILL_Knife_Ped_Die", 4.1, 0, 1, 1, 1, 0, 1);

	SetTimerEx("SetSpawnAgain", 60000, false, "di", zombieid,0);

	IsDeadNPC{zombieid} = true;
	return 1;
}

fp OnNPCTakeMeleeDamage(zombieid)
{
    unabletohit[zombieid] = false;
	if(!IsDeadNPC{zombieid}) ClearAnimations(zombieid);
	return 1;
}

public GPS_WhenRouteIsCalculated(routeid,node_id_array[],amount_of_nodes,Float:distance,Float:Polygon[],Polygon_Size,Float:NodePosX[],Float:NodePosY[],Float:NodePosZ[]){

	
    IsCalculating{routeid} = false;

    if( IsDeadNPC{routeid} )
		return false;
		
	if(amount_of_nodes <= 5)
		return IsWalking{routeid} = false;

	static
		Float: xx,
		Float: yy,
		Float: zz;

	npc.GetPos(routeid, xx,yy,zz);

	GetNodePos(NearestNodeFromPoint(xx,yy,zz,.UseAreas=1), xx,yy,zz);

    StoreVectorPath(routeid, xx, yy, zz+0.5);
	
	for(new i = 1 ; i < amount_of_nodes; i++)
	    StoreVectorPath(routeid, NodePosX[i]+float(MRandom(6)-3), NodePosY[i]+float(MRandom(6)-3), NodePosZ[i]+0.5);
    
 	return true;
}



/**
* Callback chamada quando zumbi tira vida do player
* zp = zumbi(zombie ped), pp = player (player ped), dp (distance between peds) = distancia entre eles
**/

new bool:biting[MAX_PLAYERS char];

fp OnNPCGivePlayerDamage(zp, pp, Float:dp)
{
    static Float:h;
    GetPlayerHealth(pp, h);

	if(dp < 1.2 && !biting[zp] && !unabletohit[zp])
	{
	    if(h > 0.0)
		{
			SetPlayerHealth(pp, h - 25.0);
		    SetPlayerLookAtPlayer(zp, pp);
		    ApplyAnimation(zp, "KNIFE", "KILL_Knife_Player",  4.1, 0, 1, 1, 0, 1000, 1);//zombie bite
			biting[zp] = true;
			
			new animlib[32], animname[32];
	        GetAnimationName(GetPlayerAnimationIndex(pp),animlib,32,animname,32);
			if(strcmp(animname, "KILL_Knife_Ped_Damage")) ApplyAnimation(pp, "KNIFE", "KILL_Knife_Ped_Damage",  4.1, 0, 1, 1, 0, 1000, 1);//player hurt
		}
	    SetTimerEx("OnPlayerTakeDamageFromZombie", 1300, false, "ii", pp, zp);
	}
	return true;
}


fp OnPlayerTakeDamageFromZombie(playerid, zombieid)
{
	static Float:healt;
	GetPlayerHealth(playerid, healt);
	if(healt > 0.0) ClearAnimations(playerid);
	if(!IsDeadNPC{zombieid})
	{
		ClearAnimations(zombieid);
		ApplyAnimation(zombieid, "FOOD", "EAT_Chicken", 4.1, 0, 1, 1, 0, 2000, 1);
	}
	SetTimerEx("ReleaseZombieBit", 2000, false, "i", zombieid);
	return 1;
}

fp ReleaseZombieBit(zombieid)
{
	biting[zombieid] = false;
	ClearAnimations(zombieid);
	return 1;
}
/*
* Função que ativa o spawn do jogador
*/

fp ActiveSpawn(p) {

	IsPlayerNPC(p) && vector_push_back(gBotsOnline, p);
	
	return 	SetPVarInt(p, "spawned", 1);
}





/*
* Função que faz o zumbi nascer novamente
**/

fp SetSpawnAgain(id, data)
{
	if(data == 1) return IsDeadNPC{id} = false;
	
	static
		Float:nx, Float:px,
		Float:ny, Float:py,
		Float:nz, Float:pz,
		bool:locked, proxs ;

    locked = true;

	while(locked) {

		GetVectorPath(gSpawns, MRandom(MAX_SPAWNS), nx, ny, nz);
        proxs = 0;

		for (new i = 0; i < vector_size(gPlayersOnline) ; i++) {
	        GetPlayerPos(vector_get(gPlayersOnline, i), px,py,pz);

	        if(distance(px, py, pz, nx, ny, nz) <= 150.0) {
	            proxs++;
	            break;
	        }
	    }

	    if(!proxs) {
	        locked = false;
	        break;
	    }
    }

    npc.SetPos(id, nx, ny, nz + 1.0);
    ZombieHealth[id] = 100.0;
    SetTimerEx("SetSpawnAgain", 2000, false, "di", id,1);
  	

    return true;

}




/**
* Parte que atualiza diversos dados do servidor
**/


fp UpdateServer()
{

	static t, idx ;
	t = gettime();
	
	if(t % 60 == 0)
	{
		for (new i = 0, playerid; i < vector_size(gPlayersOnline); i++)
		{
			playerid = (vector_get(gPlayersOnline, i));
	        
	        if(!GetPVarInt(playerid, "spawned")) continue;
	        
	        //aqui faz update de fome, sede etc...
		}
	}
	
	if(t % 5 == 0) {
		for(new v; v ^ MAX_VEHICLES ; ++v) {
		    if(GetVehicleModel(v)) {
				for (new i = 0, j = vector_size(gBotsOnline) ; i < j  ; i++) {
				
		        	static
						n,
		        		Float:x,
						Float:y,
						Float:z;

					n = vector_get(gBotsOnline, i);
					
		        	GetVehiclePos(v, x, y, z);

					if(IsPlayerInRangeOfPoint(n, 50.0, x,y,z))
						vector_push_back(gVehiclesStream[n], v);
					else
						~(idx = vector_find(gVehiclesStream[n], v)) && vector_remove(gVehiclesStream[n], idx);
						
				}
		    }
		}
	}
	return true;
}










fp UnableMapIconItens() {

	for (new x ; vector_size(gPlayersOnline) > x; x++) {
        static j;
		j = vector_get(gPlayersOnline, x);
        RemovePlayerMapIcon(j, 0);
    }
    return true;
}



/**
* Tudo o que se passsa com os zumbis está nessa callback.
* Algoritimos de IA, registros de caminhada, perseguir jogadores, etc
***/

fp UpdateZombies() {

	static p ;

	// pegar todos bots online
	for (new i = 0, j = vector_size(gBotsOnline) ; i < j  ; i++) {
	    
        static n;

		n = vector_get(gBotsOnline, i);

		// se o npc estiver morto, pular para o próximo
		if( IsDeadNPC{n} || IsCalculating{n})
					continue;
		
		// verificar se ele está seguindo alguém
		if( ~playerFollowing[n] ) 	{
		
			static
				Float: x,
				Float: y,
				Float: z ;
				
			p = playerFollowing[n];
			
			// caso estiver seguinr alguem, verificar se ele spawno, está na agua, ou de carro
			if(!GetPlayerPos(p, x, y, z) || !IsPlayerSpawned(p) || IsPlayerInWeather(p)  || IsPlayerInAnyVehicle(p)) {
			    playerFollowing[n] = -1;
			    currentVector[n] = 0;
			    vector_clear(n);
				continue;
			}
				
			// caso estiver ok, mandar ele para posição
			static
				Float: lastX,
				Float: lastY,
				Float: lastZ;

			npc.GetPos(n, lastX, lastY, lastZ);


			// a cada 30 segundos tocar um som para o player
		    if(gettime() - GetPVarInt(p, "lastAudio") >= 30) {
		        PlayZombieSound(p, lastX, lastY, lastZ);
		        SetPVarInt(p, "lastAudio", gettime());
		    }

			// pegar distancia entre eles

			static Float: dis ;

			dis = distance(x,y,z,lastX,lastY,lastZ);
			


			if(z - lastZ > 1.50 && dis < 7.0) {
				IsStoppedNPC{n} = true;
				vector_clear(n);
			    currentVector[n] = 0 ;
				ApplyAnimation(n, "ON_LOOKERS", "wave_loop", 4.1, 0, 1, 1, 1, 0, 1);
				RNPC_StopPlayback(n);
			    continue;
			}

			if(IsStoppedNPC{n}) {
				IsStoppedNPC{n} = false;
				ApplyAnimation(n, "BD_FIRE", "BD_Fire1", 4.1, 0, 1, 1, 1, 1, 1);
				ClearAnimations(n);
			}

			// caso o player conseguiu fugir, parar de seguir
			if(dis >= MIN_DIS) {
				playerFollowing[n] = -1;
			    currentVector[n] = 0;
			    vector_clear(n);
				continue;
			}
			else if(dis <= 1.2) {
			    // caso a distancia for menor que 1.2, resetar o vector e tirar vida do jogador
				currentVector[n] = 0;
			    vector_clear(n);
			    OnNPCGivePlayerDamage(n,p,dis);
				continue;
			}
			
			// verificar se há obstaculos na frente
			if(DiagonalRoute(x,y,z,lastX,lastY,lastZ)) {
			    // caso der, procurar um atalho
			    new Float:xxxx = NPC_RUN + rvelocity;
			    npc.moveTo(n,x,y,z, xxxx);
			    vector_clear(n);
			    currentVector[n] = 0 ;
			    continue;
			}

			if( !currentVector[n] ) {
			
			    // caso for a primeira vez que ele segue, fazer o primeiro registro no vector
			    new Float:xxxx = NPC_RUN + rvelocity;
				npc.moveTo(n,x,y,z, xxxx);
			    
			    currentVector[n] = 1 ;

			    StoreVectorPath(n, x, y, z);
			}
			else {
			

				// pegar posição anterior do vector
			    GetVectorPath(n, currentVector[n]-1, lastX, lastY, lastZ);

				static Float: zTemp ;
				
				// verificar altura do terreno
				CA_FindZ_For2DCoord(x, y, zTemp);

				if(z - zTemp > 1.5 && dis < 6.0 ) {
					IsStoppedNPC{n} = true;
					ApplyAnimation(n, "ON_LOOKERS", "wave_loop", 4.1, 0, 1, 1, 1, 0, 1);
				    continue;
				}
				else if(IsStoppedNPC{n}) {
				    IsStoppedNPC{n} = false;
				    ApplyAnimation(n, "BD_FIRE", "BD_Fire1", 4.1, 0, 1, 1, 1, 1, 1);
				    ClearAnimations(n);
				}

				// apenas criar novo vector caso a distancia anterior do player for maior que 1
			    if(distance(x,y,z, lastX, lastY, lastZ) >= 1.0)
			        StoreVectorPath(n, x, y, z);


				// caso o vector estiver tudo registrado, aguardar ..
				if(vector_size(n) == currentVector[n] * 3)
					continue;

				// caso ele estiver chegado no destino, avançar para o próximo
				if(IsPlayerInRangeOfPoint(n, 1.0, lastX, lastY, lastZ) ) {
				    GetVectorPath(n, currentVector[n], x,y,z);

					new Float:xxxx = NPC_RUN + rvelocity;
					npc.moveTo(n,x,y,z, xxxx);
				
				    currentVector[n]++;
				}

			}
		}
		else {

			// aqui será executado se ele não tiver perseguindo ninguem
  			p = GetProximityZombie(n);
  			
  			// caso achou alguem pra perseguir
			if(~p) {
			    IsWalking{n} = false;
				playerFollowing [ n ] = p;
			}
			else {
			    // caso não achou, e ainda não está caminhando
				if(IsWalking{n} && !IsCalculating{n}) {
					static
						Float:x,
						Float:y,
						Float:z;
				    
				    // caso for primeiro registro de cminhada
				    if(!currentVector[n]) {
						// salvar novos dados
				        GetVectorPath(n, 0, x,y,z);
				        // mandar ele pra la
				        npc.moveTo(n, x,y,z+0.3, NPC_WALK);
			    		currentVector[n] = 1 ;

				    }
					else {
					
					    // caso o número de registro for igual a caminahda atual do jogador, ele já caminhou tudo que tinha
					    if(vector_size(n) == currentVector[n] * 3) {
					        currentVector[n] = 0;
					        playerFollowing[n] = -1;
					        IsWalking{n} = false;
					        IsCalculating{n} = false;
					        return vector_clear(n);
					    }
					    
					    // caso contrário, continuar caminhando
                        GetVectorPath(n, currentVector[n]-1, x,y,z);
                        
                        // caso ele chegar no registro anterior, avançar para o próximo
						if(IsPlayerInRangeOfPoint(n, 1.0, x, y, z) ) {
					    	GetVectorPath(n, currentVector[n], x,y,z);
					    	npc.moveTo(n, x,y,z, NPC_WALK);
					    	currentVector[n]++;
				    	}
					}
				}
				else {
				    // caso ele ainda não tiver começado a caminhar
				    StartWalkingPath(n);
				    IsWalking{n} = true;
    				currentVector[n] = 0;
			    }
			    
			}
		}
	}
	return true;
}

fp StartWalkingPath(npcid) {

	if(	IsWalking{npcid} || IsCalculating{npcid} || IsDeadNPC{npcid})
			return false;

	static Float:x, Float:y, Float:z;

	GetVectorPath(gSpawns, MRandom(MAX_SPAWNS), x, y, z);

	CalculatePath(NearestPlayerNode(npcid), NearestNodeFromPoint(x,y,z), npcid, .GrabNodePositions = true);
	
    IsCalculating{npcid} = true;
    
	return true;
}

fp GetProximityZombie(npcid) {


	if(!IsPlayerSpawned(npcid))
	    return false;

	static
		Float: x,
		Float: y,
		Float: z;


	static
		Float: px,
		Float: py,
		Float: pz;

	static
		Float: mindis, minid, Float: dis;

	mindis = 999999999.9;
	minid = -1;

	if(!npc.GetPos(npcid, x, y, z))
		return false;

	for (new i = 0, j = vector_size(gPlayersStream[npcid]) ; i ^ j  ; i++)
	{
		new p = vector_get(gPlayersStream[npcid], i);

		if(!GetPlayerPos(p, px, py, pz) || IsPlayerInWeather(p) || !IsPlayerSpawned(p) || IsPlayerInAnyVehicle(p))
		    continue;

		dis = distance(px,py,pz,x,y,z);

		if(floatabs(z-pz) >= 1.0) {
		    continue;
		}
		
		if(mindis >= dis) {
		    mindis = dis;
		    minid = p;
		}
    }
    return mindis < MIN_DIS ? minid : -1;
}


public FCNPC_OnCreate(npcid) {


	static Float:x, Float:y, Float:z;

	new r = MRandom(MAX_SPAWNS);
	GetVectorPath(gSpawns, r, x, y, z);
	
   	npc.SetPos(npcid, x,y,z+1.0);
   	SetPlayerSkin(npcid, 162);

	return true;
}



fp ConnectAllZombies()
{
	new ZombiesLimit = GetServerVarAsInt("maxnpc");
	for(new i; i < ZombiesLimit; i++) {
        SetTimerEx("ConnectZombie", 150*i, false,  "d", (i));
	}
	return true;
}





fp GenerateSpawns () {

	static Float:x, Float:y, Float:z, i;

	i = 0;

	for( ; i ^ MAX_SPAWNS; i++) {

		MRandFloatRange(-2999.0, 2999.0, x);
		MRandFloatRange(-2999.0, 2999.0, y);

        MapAndreas_FindZ_For2DCoord(x,y,z);

		if(16.0 > z > 5.0 && MapAndreasRoundGround(x,y,z, 20.0))
		    StoreVectorPath(gSpawns, x, y, z);
		else
		    if(i) i--;
	}
	return true;
}

fs PlayZombieSound(playerid, Float:x = 0.0, Float:y = 0.0, Float:z = 0.0) {
	switch(MRandom(7)) {
		case 0:PlayAudioStreamForPlayer(playerid, "http://baixar.mixmusicas.com.br/Audio_0.mp3",x,y,z,35.0,1);
		case 1:PlayAudioStreamForPlayer(playerid, "http://baixar.mixmusicas.com.br/Audio_1.mp3",x,y,z,35.0,1);
		case 2:PlayAudioStreamForPlayer(playerid, "http://baixar.mixmusicas.com.br/Audio_2.mp3",x,y,z,35.0,1);
		case 3:PlayAudioStreamForPlayer(playerid, "http://baixar.mixmusicas.com.br/Audio_3.mp3",x,y,z,35.0,1);
		case 4:PlayAudioStreamForPlayer(playerid, "http://baixar.mixmusicas.com.br/Audio_4.mp3",x,y,z,35.0,1);
		case 5:PlayAudioStreamForPlayer(playerid, "http://baixar.mixmusicas.com.br/Audio_5.mp3",x,y,z,35.0,1);
		case 6:PlayAudioStreamForPlayer(playerid, "http://baixar.mixmusicas.com.br/Audio_6.mp3",x,y,z,35.0,1);
	}
	return true;
}



fs MapAndreasRoundGround(Float:x, Float:y, Float:z, Float: size = 2.0) {

	static Float: xx[7], Float:yy[7];
	
	//
	
	xx[0] = x;
	yy[0] = y;
	
	xx[1] = x+size;
	yy[1] = y;
	
	xx[2] = x+size;
	yy[2] = y+size;
	
	xx[3] = x;
	yy[3] = y+size;
	
	//
	
	xx[4] = x-size;
	yy[4] = y;

	xx[5] = x-size;
	yy[5] = y-size;

	xx[6] = x;
	yy[6] = y-size;


	return
		DiagonalRoute(x, y, z, xx[1],yy[1],z, .maxSteps = 15.0) &&
		DiagonalRoute(x, y, z, xx[2],yy[2],z, .maxSteps = 15.0) &&
		DiagonalRoute(x, y, z, xx[3],yy[3],z, .maxSteps = 15.0) &&
		DiagonalRoute(x, y, z, xx[4],yy[4],z, .maxSteps = 15.0) &&
		DiagonalRoute(x, y, z, xx[5],yy[5],z, .maxSteps = 15.0) &&
		DiagonalRoute(x, y, z, xx[6],yy[6],z, .maxSteps = 15.0)
	;
}

fs SaveSpawnsPos(filename[]) {

	new File: f ;

	f = fopen(filename,filemode:io_write);

	static Float: x,Float: y,Float: z;


	for(new i; i != MAX_SPAWNS; i++) {
	    GetVectorPath(gSpawns, i, x, y, z);
		fwrite(f, sprintf("%f,%f,%f\r\n", x,y,z));
	}

	fclose(f);
	return true;
}

fs LoadSpawnsPos(filename[]) {

	new File:file_ptr;
	new line[512];
	new Float:SpawnX;
	new Float:SpawnY;
	new Float:SpawnZ;

    new Carregando;

	file_ptr = fopen(filename,filemode:io_read);

	if(!file_ptr) return 0;

	while(fread(file_ptr,line) > 0) {
	    if(!sscanf(line, "p,fff",SpawnX,SpawnY,SpawnZ)) {
	        Carregando++;
	        StoreVectorPath(gSpawns, SpawnX, SpawnY, SpawnZ);
        }
	}

	fclose(file_ptr);

	printf("Foram carregados %d spawns", Carregando);
	return true;
}

stock token_by_delim(const string[], return_str[], delim, start_index)
{
	new x=0;
	while(string[start_index] != EOS && string[start_index] != delim) {
	    return_str[x] = string[start_index];
	    x++;
	    start_index++;
	}
	return_str[x] = EOS;
	if(string[start_index] == EOS) start_index = (-1);
	return start_index;
}


#define MAX_INI_ENTRY_TEXT 80

stock DB_Escape(text[])
{
	new
		ret[MAX_INI_ENTRY_TEXT * 2],
		ch,
		i,
		j;
	while ((ch = text[i++]) && j < sizeof (ret))
	{
		if (ch == '\'')
		{
			if (j < sizeof (ret) - 2)
			{
				ret[j++] = '\'';
				ret[j++] = '\'';
			}
		}
		else if (j < sizeof (ret))
		{
			ret[j++] = ch;
		}
		else
		{
			j++;
		}
	}
	ret[sizeof (ret) - 1] = '\0';
	return ret;
}
