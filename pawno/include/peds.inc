/*
        PEDs Include (peds.inc)
        * Since samp 0.3.7 have actors system(which is coolest upgrade ever!), i have planned on peds(tpe of npcs) creator using pawn (not C++)
        * This include let you make AI and cool effects and peds without writing thier AI.
        * SAMP have provided collisions for actors, which is Awesome and for you as well, cause now ped will collide!
 
        Author: (creator)
        * Gammix
 
        Contributors:
        * Pottus - ideas and improvement
        * a_angles - took help for making the ped face points
        * seif - took help from bodyparts code
 
        (c) Copyright 2015
        * This file is provided as is (no warranties).
*/
/*
FUNCTIONS:
native PED_Connect(skin, Float:x, Float:y, Float:z, Float:rotation = 0.0);
native PED_IsConnected(pedid);
native PED_Disconnect(pedid);
native PED_SetPos(pedid, Float:x, Float:y, Float:z);
native PED_GetPos(pedid, &Float:x, &Float:y, &Float:z);
native PED_SetFacingAngle(pedid, Float:angle);
native PED_GetFacingAngle(pedid, &Float:angle);
native PED_SetVirtualWorld(pedid, world);
native PED_GetVirtualWorld(pedid);
native PED_IsInRangeOfPoint(pedid, Float:range, Float:x, Float:y, Float:z);
native PED_SetFacingPoint(pedid, Float:x, Float:y);
native PED_IsFacingPoint(pedid, Float:x, Float:y, Float:range = 10.0);
native PED_SetFacingPlayer(pedid, playerid);
native PED_IsFacingPlayer(pedid, playerid);
native PED_IsBehindPlayer(pedid, playerid, Float:range = 10.0);
native PED_SetHealth(pedid, Float:health);
native PED_GetHealth(pedid, &Float:health);
native PED_GotoPoint(pedid, Float:x, Float:y, Float:z, bool:walk = false);
native PED_FollowPlayer(pedid, playerid);
native PED_GetFollowingPlayer(pedid);
native PED_ApplyAnimation(pedid, animlib[], animname[], Float:fDelta, loop, lockx, locky, freeze, time);
native PED_Stop(pedid);
native PED_Spawn(pedid);
native PED_SetSpawnInfo(pedid, Float:x, Float:y, Float:z, Float:rotation);
native PED_IsMoving(pedid);
native PED_SetWalkingStyle(pedid, walkingstyle);
native PED_GetWalkingStyle(pedid);
native PED_SetRunningStyle(pedid, runningstyle);
native PED_GetRunningStyle(pedid);
native PED_GetState(pedid);
native PED_IsStreamedIn(pedid, forplayerid);
native _
native GetPlayerCameraTargetPED(playerid);
native GetPlayerTargetPED(playerid);
 
CALLBACKS:
public PED_OnConnect(pedid);
public PED_OnDisconnect(pedid);
public PED_OnSpawn(pedid);
public PED_OnReachDestination(pedid, Float:x, Float:y, Float:z);
public PED_OnStateChange(pedid, newstate, oldstate);
public PED_OnStreamIn(pedid, forplayerid);
public PED_OnStreamOut(pedid, forplayerid);
*/
 
//just kiding !:D!
#define INVALID_PED_ID  INVALID_ACTOR_ID
 
//walking styles
#define PED_WALKING_DEFAULT     0
#define PED_WALKING_NORMAL      1
#define PED_WALKING_GANGSTA     2
#define PED_WALKING_GANGSTA2    3
#define PED_WALKING_OLD         4
#define PED_WALKING_FAT_OLD     5
#define PED_WALKING_FAT         6
#define PED_WALKING_LADY        7
#define PED_WALKING_LADY2       8
#define PED_WALKING_WHORE       9
#define PED_WALKING_WHORE2      10
#define PED_WALKING_DRUNK       11
#define PED_WALKING_BLIND       12
#define PED_WALKING_ARMED       13
 
//ped states
#define PED_STATE_NONE          0
#define PED_STATE_WALKING       1
#define PED_STATE_RUNNING       2
 
//running styles
#define PED_RUNNING_DEFAULT     0
#define PED_RUNNING_NORMAL      1
#define PED_RUNNING_GANGSTA     2
#define PED_RUNNING_GANGSTA2    3
#define PED_RUNNING_OLD         4
#define PED_RUNNING_FAT_OLD     5
#define PED_RUNNING_FAT         6
#define PED_RUNNING_LADY        7
#define PED_RUNNING_LADY2       8
#define PED_RUNNING_WHORE       9
#define PED_RUNNING_WHORE2      10
#define PED_RUNNING_DRUNK       11
#define PED_RUNNING_BLIND       12
#define PED_RUNNING_ARMED       13
 
enum PedEnum
{
        bool:P_EXIST,
        Float:P_X,
        Float:P_Y,
        Float:P_Z,
        Float:P_ROT,
        P_TIMER,
        Float:P_HEALTH,
        Float:P_GOTOX,
        Float:P_GOTOY,
        Float:P_GOTOZ,
        P_STATE,
        P_WALKSTYLE,
        P_RUNSTYLE,
        P_FOLLOWING,
        bool:P_FOLLOWINGWALK
}
static gPED[MAX_ACTORS][PedEnum];
 
//looking at ped function
static gPlayerLooking[MAX_ACTORS];
 
public OnPlayerConnect(playerid)
{
        gPlayerLooking[playerid] = INVALID_PED_ID;
 
        #if defined HoOK_OnPlayerConnect
                HoOK_OnPlayerConnect(playerid);
        #endif
        return 1;
}
#if defined _ALS_OnPlayerConnect
        #undef OnPlayerConnect
#else
        #define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect HoOK_OnPlayerConnect
#if defined HoOK_OnPlayerConnect
        forward HoOK_OnPlayerConnect(playerid);
#endif
 
//internal functions
stock Float:PED_GetDistance(Float:x1, Float:y1, Float:z1, Float:x2, Float:y2, Float:z2)
{
        return floatsqroot( (( x1 - x2 ) * ( x1 - x2 )) + (( y1 - y2 ) * ( y1 - y2 )) + (( z1 - z2 ) * ( z1 - z2 )) );
}
 
stock PED_AngleInRangeOfAngle(Float:a1, Float:a2, Float:range = 10.0)
{
        a1 -= a2;
        if((a1 < range) && (a1 > -range)) return true;
        return false;
}
 
//include funcions
stock PED_Connect(skin, Float:x, Float:y, Float:z, Float:rotation = 0.0)
{
        if(skin < 0 || skin > 311) return INVALID_PED_ID;
 
        new _actor = CreateActor(skin, x, y, z, rotation);
 
        if(_actor == INVALID_PED_ID) return INVALID_PED_ID;
 
        gPED[_actor][P_EXIST] = true;
        gPED[_actor][P_X] = x;
        gPED[_actor][P_Y] = y;
        gPED[_actor][P_Z] = z;
        gPED[_actor][P_ROT] = rotation;
        gPED[_actor][P_HEALTH] = 100.0;
        gPED[_actor][P_GOTOX] = -1000.0;
        gPED[_actor][P_GOTOY] = -1000.0;
        gPED[_actor][P_GOTOZ] = -1000.0;
        gPED[_actor][P_WALKSTYLE] = 0;
        gPED[_actor][P_RUNSTYLE] = 0;
        gPED[_actor][P_STATE] = PED_STATE_NONE;
        gPED[_actor][P_FOLLOWING] = INVALID_PLAYER_ID;
        gPED[_actor][P_FOLLOWINGWALK] = false;
 
        gPED[_actor][P_TIMER] = SetTimerEx("PED_OnTimeUpdate", 100, true, "i", _actor);
 
        CallLocalFunction("PED_OnConnect", "i", _actor);
        CallLocalFunction("PED_OnSpawn", "i", _actor);
        return _actor;
}
 
stock PED_IsConnected(pedid) return gPED[pedid][P_EXIST];
 
stock PED_Disconnect(pedid)
{
        if(! PED_IsConnected(pedid)) return false;
 
        gPED[pedid][P_EXIST] = false;
 
        DestroyActor(pedid);
        KillTimer(gPED[pedid][P_TIMER]);
 
        CallLocalFunction("PED_OnDisconnect", "i", pedid);
        return true;
}
 
stock PED_SetPos(pedid, Float:x, Float:y, Float:z)
{
        if(! PED_IsConnected(pedid)) return false;
 
        return SetActorPos(pedid, x, y, z);
}
 
stock PED_GetPos(pedid, &Float:x, &Float:y, &Float:z)
{
        if(! PED_IsConnected(pedid)) return false;
 
        return GetActorPos(pedid, x, y, z);
}
 
stock PED_SetFacingAngle(pedid, Float:angle)
{
        if(! PED_IsConnected(pedid)) return false;
 
        return SetActorFacingAngle(pedid, angle);
}
 
stock PED_GetFacingAngle(pedid, &Float:angle)
{
        if(! PED_IsConnected(pedid)) return false;
 
        return GetActorFacingAngle(pedid, angle);
}
 
stock PED_SetVirtualWorld(pedid, world)
{
        if(! PED_IsConnected(pedid)) return false;
 
        return SetActorVirtualWorld(pedid, world);
}
 
stock PED_GetVirtualWorld(pedid)
{
        if(! PED_IsConnected(pedid)) return false;
 
        return GetActorVirtualWorld(pedid);
}
 
stock PED_IsInRangeOfPoint(pedid, Float:range, Float:x, Float:y, Float:z)
{
        if(! PED_IsConnected(pedid)) return false;
 
        new Float:pos[3];
        PED_GetPos(pedid, pos[0], pos[1], pos[2]);
 
        if(PED_GetDistance(pos[0], pos[1], pos[2], x, y, z) <= range) return true;
        return false;
}
 
stock PED_SetFacingPoint(pedid, Float:x, Float:y)
{
        if(! PED_IsConnected(pedid)) return false;
 
        new Float:pX, Float:pY, Float:pZ;
        PED_GetPos(pedid, pX, pY, pZ);
 
        new Float:angle;
 
        if( y > pY ) angle = (-acos((x - pX) / floatsqroot((x - pX)*(x - pX) + (y - pY)*(y - pY))) - 90.0);
        else if( y < pY && x < pX ) angle = (acos((x - pX) / floatsqroot((x - pX)*(x - pX) + (y - pY)*(y - pY))) - 450.0);
        else if( y < pY ) angle = (acos((x - pX) / floatsqroot((x - pX)*(x - pX) + (y - pY)*(y - pY))) - 90.0);
 
        if(x > pX) angle = (floatabs(floatabs(angle) + 180.0));
        else angle = (floatabs(angle) - 180.0);
 
        PED_SetFacingAngle(pedid, angle);
        return true;
}
 
stock PED_IsFacingPoint(pedid, Float:x, Float:y, Float:range = 10.0)
{
        if(! PED_IsConnected(pedid)) return false;
 
        new Float:X, Float:Y, Float:Z, Float:A;
        PED_GetPos(pedid, X, Y, Z);
        PED_GetFacingAngle(pedid, A);
 
        new Float:angle;
 
        if( Y > y ) angle = (-acos((X - x) / floatsqroot((X - x)*(X - x) + (Y - y)*(Y - y))) - 90.0);
        else if( Y < y && X < x ) angle = (acos((X - x) / floatsqroot((X - x)*(X - x) + (Y - y)*(Y - y))) - 450.0);
        else if( Y < y ) angle = (acos((X - x) / floatsqroot((X - x)*(X - x) + (Y - y)*(Y - y))) - 90.0);
 
        if(PED_AngleInRangeOfAngle(-angle, A, range)) return true;
        return false;
}
 
stock PED_SetFacingPlayer(pedid, playerid)
{
        if(! PED_IsConnected(pedid)) return false;
        if(! IsPlayerConnected(playerid)) return false;
 
        new Float:pX, Float:pY, Float:pZ;
        GetPlayerPos(playerid, pX, pY, pZ);
 
        return PED_SetFacingPoint(pedid, pX, pY);
}
 
stock PED_IsFacingPlayer(pedid, playerid)
{
        if(! PED_IsConnected(pedid)) return false;
        if(! IsPlayerConnected(playerid)) return false;
 
        new Float:pX, Float:pY, Float:pZ;
        GetPlayerPos(playerid, pX, pY, pZ);
 
        return PED_IsFacingPoint(pedid, pX, pY);
}
 
stock PED_IsBehindPlayer(pedid, playerid, Float:range = 10.0)
{
        if(! PED_IsConnected(pedid)) return false;
        if(! IsPlayerConnected(playerid)) return false;
 
        new Float:za, Float:pa;
        PED_GetFacingAngle(pedid, za);
        GetPlayerFacingAngle(playerid, pa);
 
        if(PED_AngleInRangeOfAngle(za, pa, range) && PED_IsFacingPlayer(playerid, playerid)) return true;
        return false;
}
 
stock PED_SetHealth(pedid, Float:health)
{
        if(! PED_IsConnected(pedid)) return false;
 
        gPED[pedid][P_HEALTH] = health;
        return true;
}
 
stock PED_GetHealth(pedid, &Float:health)
{
        if(! PED_IsConnected(pedid)) return false;
 
        health = gPED[pedid][P_HEALTH];
        return true;
}
 
stock PED_ApplyAnimation(pedid, animlib[], animname[], Float:fDelta, loop, lockx, locky, freeze, time)
{
        if(! PED_IsConnected(pedid)) return false;
 
        return ApplyActorAnimation(pedid, animlib, animname, fDelta, loop, lockx, locky, freeze, time);
}
 
stock PED_GotoPoint(pedid, Float:x, Float:y, Float:z, bool:walk = false)
{
        if(! PED_IsConnected(pedid)) return false;
 
    //PED_Stop(pedid);
        PED_SetFacingPoint(pedid, x, y);
 
        if(walk)
        {
            switch(gPED[pedid][P_WALKSTYLE])
            {
                        case PED_WALKING_NORMAL: PED_ApplyAnimation(pedid, "PED", "WALK_civi", 4.1, 1, 1, 1, 1, 0);
                        case PED_WALKING_GANGSTA: PED_ApplyAnimation(pedid, "PED", "WALK_gang1", 4.1, 1, 1, 1, 1, 0);
                        case PED_WALKING_GANGSTA2: PED_ApplyAnimation(pedid, "PED", "WALK_gang2", 4.1, 1, 1, 1, 1, 0);
                        case PED_WALKING_OLD: PED_ApplyAnimation(pedid, "PED", "WALK_old", 4.1, 1, 1, 1, 1, 0);
                        case PED_WALKING_FAT_OLD: PED_ApplyAnimation(pedid, "PED", "WALK_fatold", 4.1, 1, 1, 1, 1, 0);
                        case PED_WALKING_FAT: PED_ApplyAnimation(pedid, "PED", "WALK_fat", 4.1, 1, 1, 1, 0, 1);
                        case PED_WALKING_LADY: PED_ApplyAnimation(pedid, "PED", "WOMAN_walknorm", 4.1, 1, 1, 1, 1, 0);
                        case PED_WALKING_LADY2: PED_ApplyAnimation(pedid, "PED", "WOMAN_walkbusy", 4.1, 1, 1, 1, 1, 0);
                        case PED_WALKING_WHORE: PED_ApplyAnimation(pedid, "PED", "WOMAN_walkpro", 4.1, 1, 1, 1, 1, 0);
                        case PED_WALKING_WHORE2: PED_ApplyAnimation(pedid, "PED", "WOMAN_walksexy", 4.1, 1, 1, 1, 1, 0);
                        case PED_WALKING_DRUNK: PED_ApplyAnimation(pedid, "PED", "WALK_drunk", 4.1, 1, 1, 1, 1, 0);
                        case PED_WALKING_BLIND: PED_ApplyAnimation(pedid, "PED", "Walk_Wuzi", 4.1, 1, 1, 1, 1, 0);
                        case PED_WALKING_ARMED: PED_ApplyAnimation(pedid, "PED", "WALK_armed", 4.1, 1, 1, 1, 1, 0);
                        default: PED_ApplyAnimation(pedid, "PED", "WALK_player", 4.1, 1, 1, 1, 1, 0);
                }
                if(gPED[pedid][P_STATE] != PED_STATE_WALKING)
                {
                        CallLocalFunction("PED_OnStateChange", "iii", pedid, PED_STATE_WALKING, gPED[pedid][P_STATE]);
                gPED[pedid][P_STATE] = PED_STATE_WALKING;
                }
        }
        else
        {
            switch(gPED[pedid][P_RUNSTYLE])
            {
                        case PED_RUNNING_NORMAL: PED_ApplyAnimation(pedid, "PED", "run_civi", 4.1, 1, 1, 1, 1, 0);
                        case PED_RUNNING_GANGSTA: PED_ApplyAnimation(pedid, "PED", "run_gang1", 4.1, 1, 1, 1, 1, 0);
                        case PED_RUNNING_GANGSTA2: PED_ApplyAnimation(pedid, "PED", "run_gang1", 4.1, 1, 1, 1, 1, 0);
                        case PED_RUNNING_OLD: PED_ApplyAnimation(pedid, "PED", "run_old", 4.1, 1, 1, 1, 1, 0);
                        case PED_RUNNING_FAT_OLD: PED_ApplyAnimation(pedid, "PED", "run_fatold", 4.1, 1, 1, 1, 1, 0);
                        case PED_RUNNING_FAT: PED_ApplyAnimation(pedid, "PED", "run_fat", 4.1, 1, 1, 1, 0, 1);
                        case PED_RUNNING_LADY: PED_ApplyAnimation(pedid, "PED", "woman_run", 4.1, 1, 1, 1, 1, 0);
                        case PED_RUNNING_LADY2: PED_ApplyAnimation(pedid, "PED", "WOMAN_runbusy", 4.1, 1, 1, 1, 1, 0);
                        case PED_RUNNING_WHORE: PED_ApplyAnimation(pedid, "PED", "woman_runpanic", 4.1, 1, 1, 1, 1, 0);
                        case PED_RUNNING_WHORE2: PED_ApplyAnimation(pedid, "PED", "WOMAN_runsexy", 4.1, 1, 1, 1, 1, 0);
                        case PED_RUNNING_DRUNK: PED_ApplyAnimation(pedid, "PED", "WALK_drunk", 4.1, 1, 1, 1, 1, 0);
                        case PED_RUNNING_BLIND: PED_ApplyAnimation(pedid, "PED", "Run_Wuzi", 4.1, 1, 1, 1, 1, 0);
                        case PED_RUNNING_ARMED: PED_ApplyAnimation(pedid, "PED", "run_armed", 4.1, 1, 1, 1, 1, 0);
                        default: PED_ApplyAnimation(pedid, "PED", "run_player", 4.1, 1, 1, 1, 1, 0);
                }
                if(gPED[pedid][P_STATE] != PED_STATE_RUNNING)
                {
                        CallLocalFunction("PED_OnStateChange", "iii", pedid, PED_STATE_RUNNING, gPED[pedid][P_STATE]);
                gPED[pedid][P_STATE] = PED_STATE_RUNNING;
                }
        }
 
    gPED[pedid][P_GOTOX] = x;
    gPED[pedid][P_GOTOY] = y;
    gPED[pedid][P_GOTOZ] = z;
        return true;
}
 
stock PED_FollowPlayer(pedid, playerid, bool:walk = false)
{
        if(! PED_IsConnected(pedid)) return false;
        if(! IsPlayerConnected(playerid)) return false;
 
        gPED[pedid][P_FOLLOWING] = playerid;
        gPED[pedid][P_FOLLOWINGWALK] = walk;
 
        new Float:pos[3];
        GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
    PED_GotoPoint(pedid, pos[0], pos[1], pos[2], walk);
        return true;
}
 
stock PED_GetFollowingPlayer(pedid)
{
        if(! PED_IsConnected(pedid)) return false;
 
        return gPED[pedid][P_FOLLOWING];
}
 
stock PED_SetWalkingStyle(pedid, walkingstyle)
{
        if(! PED_IsConnected(pedid)) return false;
        if(walkingstyle < 0 || walkingstyle > 13) return false;
 
        gPED[pedid][P_WALKSTYLE] = walkingstyle;
        return true;
}
 
stock PED_GetWalkingStyle(pedid)
{
        if(! PED_IsConnected(pedid)) return false;
 
        return gPED[pedid][P_WALKSTYLE];
}
 
stock PED_SetRunningStyle(pedid, runningstyle)
{
        if(! PED_IsConnected(pedid)) return false;
 
        gPED[pedid][P_RUNSTYLE] = runningstyle;
        return true;
}
 
stock PED_GetRunningStyle(pedid)
{
        if(! PED_IsConnected(pedid)) return false;
 
        return gPED[pedid][P_RUNSTYLE];
}
 
stock PED_GetState(pedid)
{
        if(! PED_IsConnected(pedid)) return false;
 
        return gPED[pedid][P_STATE];
}
 
stock PED_Stop(pedid)
{
        if(! PED_IsConnected(pedid)) return false;
 
        if(gPED[pedid][P_STATE] != PED_STATE_NONE)
        {
        CallLocalFunction("PED_OnStateChange", "iii", pedid, PED_STATE_NONE, gPED[pedid][P_STATE]);//calling !:D!
        gPED[pedid][P_STATE] = PED_STATE_NONE;
        }
       
        gPED[pedid][P_FOLLOWING] = INVALID_PLAYER_ID;
        return ClearActorAnimations(pedid);
}
 
stock PED_Spawn(pedid)
{
        if(! PED_IsConnected(pedid)) return false;
 
        ClearActorAnimations(pedid);
 
        PED_SetHealth(pedid, 100.0);
        PED_SetVirtualWorld(pedid, 0);
        PED_SetPos(pedid, 0.0, 0.0, 0.0);
        PED_SetPos(pedid, gPED[pedid][P_X], gPED[pedid][P_Y], gPED[pedid][P_Z]);
        PED_SetFacingAngle(pedid, gPED[pedid][P_ROT]);
    gPED[pedid][P_STATE] = PED_STATE_NONE;
        gPED[pedid][P_FOLLOWING] = INVALID_PLAYER_ID;
 
        CallLocalFunction("PED_OnSpawn", "i", pedid);
        return true;
}
 
stock PED_SetSpawnInfo(pedid, Float:x, Float:y, Float:z, Float:rotation)
{
        if(! PED_IsConnected(pedid)) return false;
 
    gPED[pedid][P_X] = x;
    gPED[pedid][P_Y] = y;
    gPED[pedid][P_Z] = z;
    gPED[pedid][P_ROT] = rotation;
    return true;
}
 
//player functions
stock GetPlayerCameraTargetPED(playerid)
{
        if(! IsPlayerConnected(playerid)) return false;
 
        return GetPlayerCameraTargetActor(playerid);
}
 
#if ! defined KEY_AIM
        #define KEY_AIM 128
#endif
stock GetPlayerTargetPED(playerid)
{
        if(! IsPlayerConnected(playerid)) return false;
 
        new target_ped = GetPlayerCameraTargetPED(playerid);
        if(target_ped != INVALID_PED_ID)
    {
        new keys, updown, leftright;
        GetPlayerKeys(playerid, keys, updown, leftright);
 
        if(     GetPlayerWeapon(playerid) >= 22 &&
                        GetPlayerWeapon(playerid) <= 38 &&
                        keys & KEY_AIM)
        {
                        return target_ped;
        }
    }
        return INVALID_PED_ID;
}
 
stock PED_IsStreamedIn(pedid, forplayerid)
{
        if(! PED_IsConnected(pedid)) return false;
        if(! IsPlayerConnected(forplayerid)) return false;
 
        return IsActorStreamedIn(pedid, forplayerid);
}
 
//internal callback
forward PED_OnTimeUpdate(pedid);
public PED_OnTimeUpdate(pedid)
{
        if(     PED_GetState(pedid) == PED_STATE_RUNNING ||
                PED_GetState(pedid) == PED_STATE_WALKING)
        {
            if(PED_IsInRangeOfPoint(pedid, 2.0, gPED[pedid][P_GOTOX], gPED[pedid][P_GOTOY], gPED[pedid][P_GOTOZ]))//will be adding a better version when actors include gets an update from Kalcor*!
        {
            print("REACHED");
            PED_Stop(pedid);
            CallLocalFunction("PED_OnReachDestination", "ifff", pedid, gPED[pedid][P_GOTOX], gPED[pedid][P_GOTOY], gPED[pedid][P_GOTOZ]);
 
            if(gPED[pedid][P_FOLLOWING] != INVALID_PLAYER_ID)
            {
                                new Float:pos[3];
                                GetPlayerPos(gPED[pedid][P_FOLLOWING], pos[0], pos[1], pos[2]);
                            PED_GotoPoint(pedid, pos[0], pos[1], pos[2], gPED[pedid][P_FOLLOWINGWALK]);
            }
            return 1;
        }
        }
        return 1;
}
 
public OnActorStreamIn(actorid, forplayerid)
{
        if(gPED[actorid][P_EXIST]) CallLocalFunction("PED_OnStreamIn", "ii", actorid, forplayerid);
 
        #if defined HoOK_OnActorStreamIn
                HoOK_OnActorStreamIn(actorid, forplayerid);
        #endif
        return 1;
}
#if defined _ALS_OnActorStreamIn
        #undef OnActorStreamIn
#else
        #define _ALS_OnActorStreamIn
#endif
#define OnActorStreamIn HoOK_OnActorStreamIn
#if defined HoOK_OnActorStreamIn
        forward HoOK_OnActorStreamIn(actorid, forplayerid);
#endif
 
public OnActorStreamOut(actorid, forplayerid)
{
        if(gPED[actorid][P_EXIST]) CallLocalFunction("PED_OnStreamOut", "ii", actorid, forplayerid);
 
        #if defined HoOK_OnActorStreamOut
                HoOK_OnActorStreamOut(actorid, forplayerid);
        #endif
        return 1;
}
#if defined _ALS_OnActorStreamOut
        #undef OnActorStreamOut
#else
        #define _ALS_OnActorStreamOut
#endif
#define OnActorStreamOut HoOK_OnActorStreamOut
#if defined HoOK_OnActorStreamOut
        forward HoOK_OnActorStreamOut(actorid, forplayerid);
#endif
 
forward PED_OnConnect(pedid);
forward PED_OnDisconnect(pedid);
forward PED_OnSpawn(pedid);
forward PED_OnReachDestination(pedid, Float:x, Float:y, Float:z);
forward PED_OnStateChange(pedid, newstate, oldstate);
forward PED_OnStreamIn(pedid, playerid);
forward PED_OnStreamOut(pedid, playerid);
