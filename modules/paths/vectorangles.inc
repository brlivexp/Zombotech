stock Float: GetZAngleBetweenPoints(Float: x1, Float: y1, Float: x2, Float: y2) return -atan2(x2 - x1, y2 - y1);

stock SetPlayerLookAtPlayer(playerid, giveplayerid) 
{
    new Float: pX, Float: pY, Float: gX, Float: gY, Float: Z;    
	GetPlayerPos(playerid, pX, pY, Z);
	GetPlayerPos(giveplayerid, gX, gY, Z);
	return SetPlayerFacingAngle(playerid, GetZAngleBetweenPoints(pX, pY, gX, gY));
}
