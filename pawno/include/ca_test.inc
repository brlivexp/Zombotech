CMD:detectcol(playerid)
{
	new Float:p[6];
	GetPlayerPos(playerid, p[0], p[1], p[2]);
	GetXYInFrontOfPlayer(playerid, p[3], p[4], 10.0);

	p[5] = p[2];
	
	new rota = validNPCRoute(p[0], p[1], p[2], p[3], p[4], p[5]);

	if(rota) return SendClientMessage(playerid, 0x00FF00, #No collisions detected!);
	return SendClientMessage(playerid, 0xFF0000, #collision detected and object created!);
}


stock validNPCRoute(Float:fX, Float:fY, Float:fZ, Float:tX, Float:tY, Float:tZ)	{

	new Float:__tmpF[3];

	CA_RayCastLine(fX, fY, fZ, tX, tY, tZ, __tmpF[0], __tmpF[1], __tmpF[2]);

	//Debug
	CreateObject(18900, __tmpF[0], __tmpF[1], __tmpF[2], 0.0, 0.0, 0.0); //Cria objeto na colisão.
	//
	Create3DTextLabel("collision here faggot", 0x008080FF, __tmpF[0], __tmpF[1], __tmpF[2], 200, 0, 1);

	if((__tmpF[0] == 0.0) && (__tmpF[1] == 0.0) && (__tmpF[2] == 0.0))
		return 1;

	return 0;
}


/*
	Ex: 1

		bot_x, bot_y, bot_z -> Coordenadas do bot
		tox, toy, toz		-> Coordenadas destino

		new rota = validNPCRoute(bot_x, bot_y, bot_z, tox, toy, toz);
		if(rota) // Rota valida.
	
	Ex 2:

	(Função melhorada da antiga usada no MapAndreas)
		*	Pega a colisão partindo de uma altura especifica.


	toz = getminZPosAt(tox, toy, toz + 2.0);


	forward Float:getminZPosAt(Float:x, Float:y, Float:z);
	public Float:getminZPosAt(Float:x, Float:y, Float:z) {
	
		new Float:endX, Float:endY, Float:endZ;

		CA_RayCastLine(x, y, z, x, y, -2000.0, endX, endY, endZ);

		return endZ;
	}

*/