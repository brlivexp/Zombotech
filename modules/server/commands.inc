#include "../modules/admin/permissions.inc"

#define DIALOG_SPAWN_ITEMS	9892
#define DIALOG_SPAWN_ITEMS_AMOUNT	9893
#define DIALOG_ADMIN_MENU 	3346

new SelectedSpawnItem[MAX_PLAYERS];

public OnCommandCalled(playerid, params[])
{
	get_cmd_params(goto)
	{
		if(!IsPlayerAdmin(playerid)) return 0;
		new ped;
		if(sscanf(params, "d", ped)) return SendClientMessage(playerid, -1, "usage: /goto [id]");
		new Float:P[3];
		GetPlayerPos(ped, P[0], P[1], P[2]);
		SetPlayerPos(playerid, P[0] - 2.5, P[1] + 2.5, P[2] + 0.4);
		return 1;
	}
	get_cmd_params(grenade)
	{
		CreatePlayerItem(playerid, 342, 1, 100.0, 0, 0);
		return 1;
	}
	get_cmd_params(bat)
	{
		CreatePlayerItem(playerid, 336, 1, 100.0, 0, 0);
		return 1;
	}
	get_cmd_params(spray)
	{
		CreatePlayerItem(playerid, 365, 9999, 100.0, 0, 0);
		return 1;
	}
	get_cmd_params(deagle)
	{
		CreatePlayerItem(playerid, 348, 50, 100.0, 0, 0);
		return 1;
	}
	get_cmd_params(sniper)
	{
		CreatePlayerItem(playerid, 358, 50, 100.0, 0, 0);
		return 1;
	}
	get_cmd_params(ammo)
	{
		new ammoname[16], ammoamount;
		if(sscanf(params, "sd", ammoname, ammoamount)) return SendClientMessage(playerid, -1, "{333333}Correct usage: {FF0000}/ammo <weapon name> <amount>{333333}!");
		if(!strcmp(ammoname, "pistol")) return CreatePlayerItem(playerid, 19995, ammoamount, 100.0, 0, 0);	
		if(!strcmp(ammoname, "rifle")) return CreatePlayerItem(playerid, 3052, ammoamount, 100.0, 0, 0);	
		return 1;
	}
	get_cmd_params(saveitems)
	{
		SavePlayerItems(playerid);
		return 1;
	}
	get_cmd_params(banana)
	{
		CreatePlayerItem(playerid, 19578, 1, 100.0, 0, 0);
		return 1;
	}
	get_cmd_params(juice)
	{
		CreatePlayerItem(playerid, 19563, 1, 100.0, 0, 0);
		return 1;
	}
	get_cmd_params(skin)
	{
		new skin;
		if(sscanf(params, "d", skin)) return SendClientMessage(playerid, -1, "Uso correto: /skin [id]");
		if(IsPlayerAdmin(playerid))
		{
			if(0 < skin < 311) SetPlayerSkin(playerid, skin);
			return 1;
		}
		return 1;
	}
	get_cmd_params(ccreate)
	{
		new model;
		if(sscanf(params, "i", model)) return SendClientMessage(playerid, -1, "Correct usage: /ccreate model");
		
		if(399 < model < 601)
		{
			new Float:x, Float:y, Float:z;
			GetPlayerPos(playerid, x, y, z);
			CreateVehicle(model, x + 1.5, y + 1.5, z + 0.5, 0.0, 0, 0, 1000, 1);
			return 1;
		}
		else return SendClientMessage(playerid, -1, "Invalid vehicle");				
	}
	get_cmd_params(w2)
	{
		new model, amount;
		if(!sscanf(params, "ii", model, amount))
		{
			if(model > 0 && model < 47)
			{
				GivePlayerWeapon(playerid, model, amount);
			}
		}
		return 1;
	}
	get_cmd_params(padlock)
	{
		if(!PlayerEquippedItem[playerid][EItemTime][7])
		{
			PlayerEquippedItem[playerid][EItemModel][7] = 19804;
			PlayerEquippedItem[playerid][EItemTime][7] = gettime() + DaysToSeconds(30);
			PlayerEquippedItem[playerid][EItemExpirable][7] = 1;
		}
		else
		{
			PlayerEquippedItem[playerid][EItemModel][7] = 19804;
			PlayerEquippedItem[playerid][EItemTime][7] += DaysToSeconds(30);
			PlayerEquippedItem[playerid][EItemExpirable][7] = 1;
		}
		UpdatePadlockInfo(playerid);
		return 1;
	}
	get_cmd_params(expired)
	{
		CreatePlayerItem(playerid, 19579, 1, 100.0, 1432080240, 1);
		return 1;
	}
	get_cmd_params(broken)
	{
		CreatePlayerItem(playerid, 19579, 1, 0.0, 0, 0);
		return 1;
	}
	get_cmd_params(hunger)
	{
		new percent;
		if(sscanf(params, "d", percent)) return 0;

		SetProgressLevel(playerid, HUDText[playerid][16], float(percent), 45.0, 153.0, 1.0);
		PlayerTextDrawShow(playerid, HUDText[playerid][16]);
		return 1;
	}
	get_cmd_params(jetpack)
	{
		SetPlayerSpecialAction(playerid, 2);
		SendClientMessage(playerid, -1, "{666666}You've created a {FF0000}jetpack{666666} !");
		return 1;
	}
	get_cmd_params(setworld)
	{
		new vworld, str[60];
		if(sscanf(params, "d", vworld)) return SendClientMessage(playerid, -1, "{333333}Correct usage: {FF0000}/world <id>{333333}!");
		SetPlayerVirtualWorld(playerid, vworld);
		format(str, 60, "{666666}Your world has changed to {FF0000}%d {666666}!", vworld);
		return SendClientMessage(playerid, -1, str);
	}	
	get_cmd_params(setinterior)
	{
		new pinterior, str[60];
		if(sscanf(params, "d", pinterior)) return SendClientMessage(playerid, -1, "{333333}Correct usage: {FF0000}/interior <id>{333333}!");
		SetPlayerInterior(playerid, pinterior);
		format(str, 60, "{666666}Your interior has changed to {FF0000}%d {666666}!", pinterior);
		return SendClientMessage(playerid, -1, str);
	}
	get_cmd_params(hudon)
	{
		ShowPlayerHUD(playerid);
		return 1;
	}
	get_cmd_params(hudoff)
	{
		HidePlayerHUD(playerid);
		return 1;
	}
	get_cmd_params(listitems)
	{
		if(!CountPlayerFreeSlots(playerid)) return SendClientMessage(playerid, -1, "{666666}Error: you don't have free slots to create items!");

		new listitems[5000];
		for(new s; s < sizeof ObjectsInfo; s++)
		{
			format(listitems, sizeof listitems, "%s{%06x}%d\t{%06x}%s\n",  listitems,   ObjectsInfo[s][Object_Color], ObjectsInfo[s][Object_Model], ObjectsInfo[s][Object_Color], ObjectsInfo[s][Object_Name]);
		}
		return ShowPlayerDialog(playerid, DIALOG_SPAWN_ITEMS, DIALOG_STYLE_TABLIST, "Create a Item", listitems, "Select", "Cancel"); 
	}
	get_cmd_params(equipdebug)
	{
		new string[512];
		for(new s; s < 9; s++)
		{
			format(string, 512, "%s(Item %d) id = %d | model = %d\n", string, s, PlayerEquippedItem[playerid][EItemID][s], PlayerEquippedItem[playerid][EItemModel][s]);
		}
		ShowPlayerDialog(playerid, 3444, DIALOG_STYLE_MSGBOX, "Equiped Items", string, "Ok", "");
		return 1;
	}
	get_cmd_params(wears)
	{
		new slotid, string[512];
		if(sscanf(params, "i", slotid)) return SendClientMessage(playerid, 0xFF0000FF, "Invalid slotid value!");

		format(string, 512, "\n---------<debug>-----------\nAttachment data\nPlayer:%d\nSlot:%d\nModel:%d\nBone:%d\nOffsetX:%f\nOffsetY:%f\nOffsetZ:%f\nRotX:%f\nRotY:%f\nRotZ:%f\nScaleX:%f\nScaleY:%f\nScaleZ:%f\ncol1:%d\ncol2:%d\n----------<end>----------\n",
		playerid, slotid, 
		PlayerEquippedItem[playerid][EItemModel][slotid],
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
		ShowPlayerDialog(playerid, 2342, DIALOG_STYLE_MSGBOX, "Wear Debug", string, "alright", "");
		return 1;
	}
	get_cmd_params(resetequip)
	{
		new slotid;
		if(sscanf(params, "i", slotid)) return SendClientMessage(playerid, 0xFF0000FF, "Invalid slotid value!");
		if(SetPlayerAttachedObject(playerid, slotid,
		PlayerEquippedItem[playerid][EItemModel][slotid],
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
		PlayerEquippedItem[playerid][EItemCol2][slotid])) return SendClientMessage(playerid, 0xFF0000FF, "Fail to reload attached object!");
		else return SendClientMessage(playerid, 0x00FF00FF, "Attached object successfully reloaded!");
	}
	get_cmd_params(admins)
	{
		if(!IsValidRule(PlayerInfo[playerid][adminlevel], "admins")) return 0;
		new list[1024], varName[24];

		foreach(new i : Player)
		{
			if(!PlayerInfo[i][adminlevel]) continue;
			GetPlayerName(i, varName, 24);
			format(list, 1024, "Admin: %s - Level: %d", varName, PlayerInfo[i][adminlevel]);
		}
		ShowPlayerDialog(playerid, DIALOG_ADMIN_MENU, DIALOG_STYLE_MSGBOX, "Online Admins", list, "Ok", "");
		return 1;
	}
	get_cmd_params(setlevel)
	{

		if(!IsValidRule(PlayerInfo[playerid][adminlevel], "admins") && !IsPlayerAdmin(playerid)) return 0;
		new user, lvl, username[24], string[128];
		if(sscanf(params, "ui", user, lvl)) return SendClientMessage(playerid, 0xFF0000FF, "Command failed, correct usage: /setlevel <id/name> <level>");
		if(0 > lvl || lvl > 6) return SendClientMessage(playerid, 0xFF0000FF, "Command failed, you must give a level from 1 to 6!");
		if(!IsPlayerConnected(user)) return SendClientMessage(playerid, 0xFF0000FF, "Command failed, that player isn't connected!");
		
		PlayerInfo[user][adminlevel] = lvl;
		
		GetPlayerName(user, username, 24);
		format(string, 128, "{00FF00}You successfully promoted {FF0000}%s{00FF00} to admin level {FF0000}%d{00FF00}!", username, lvl);
		SendClientMessage(playerid, -1, string);
		
		GetPlayerName(playerid, username, 24);
		format(string, 128, "{00FF00}Congratulations, {FF0000}%s{00FF00} gave you admin level {FF0000}%d{00FF00}!", username, lvl);
		SendClientMessage(user, -1, string);
		
		return 1;
	}
	get_cmd_params(startcraft) return ShowPlayerCraftingMenu(playerid);
	get_cmd_params(stopcraft) return HidePlayerCraftingMenu(playerid);
	get_cmd_params(pps)
	{
		new sound;
		if(sscanf(params, "i", sound)) return SendClientMessage(playerid, 0xFF0000FF, "Invalid sound id");
		SendClientMessage(playerid, 0x00FF00FF, "Playing desired sound id");
		return PlayerPlaySound(playerid, sound, 0.0, 0.0, 0.0);
	}
	return 1;
}




