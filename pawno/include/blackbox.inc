/* 
	Hoooks
*/


forward HookTogglePlayerControllable(playerid, toggle);
public HookTogglePlayerControllable(playerid, toggle)
{
	if(toggle == 0)
	{
		CallRemoteFunction("OnPlayerFreeze", "i", playerid);
	}
	else
	{
		CallRemoteFunction("OnPlayerUnfreeze", "i", playerid);
	}	
	return TogglePlayerControllable(playerid, toggle);
}

#if defined _ALS_TogglePlayerControllable
    #undef TogglePlayerControllable
#else
    #define _ALS_TogglePlayerControllable
#endif

#define TogglePlayerControllable HookTogglePlayerControllable


forward HookSetPlayerPos(playerid, Float:x, Float:y, Float:z);
public HookSetPlayerPos(playerid, Float:x, Float:y, Float:z)
{
	CallRemoteFunction("OnPlayerPositionChange", "ifff", playerid, x, y, z);	
	return SetPlayerPos(playerid, x, y, z);
}
#if defined _ALS_SetPlayerPos
    #undef SetPlayerPos
#else
    #define _ALS_SetPlayerPos
#endif

#define SetPlayerPos HookSetPlayerPos

forward HookSetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
public HookSetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective)
{
	if(engine)
	{
		CallRemoteFunction("OnVehicleEngineStart", "i", vehicleid);
	}
	return SetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
}
#if defined _ALS_SetVehicleParamsEx
    #undef SetVehicleParamsEx
#else
    #define _ALS_SetVehicleParamsEx
#endif

#define SetVehicleParamsEx HookSetVehicleParamsEx