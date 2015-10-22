stock Float:GetZombieRunSpeed(zombieid)
{
	new skinid = ZombieInfo[zombieid][zombie_skin];
	/*new Float:rspeed;
	MRandFloatRange(0.0, floatdiv(ZombieClassInfo[skinid][DefaultMoveSpeed], 10.0), rspeed);*/
	return ZombieClassInfo[skinid][DefaultMoveSpeed] ;
}

stock Float:GetDistanceBetweenPlayers(playerid,targetplayerid)
{
    new Float:x1,Float:y1,Float:z1,Float:x2,Float:y2,Float:z2;
    if(!IsPlayerConnected(playerid) || !IsPlayerConnected(targetplayerid)) {
        return -1.00;
    }
    GetPlayerPos(playerid,x1,y1,z1);
    GetPlayerPos(targetplayerid,x2,y2,z2);
    return floatsqroot(floatpower(floatabs(floatsub(x2,x1)),2)+floatpower(floatabs(floatsub(y2,y1)),2)+floatpower(floatabs(floatsub(z2,z1)),2));
}