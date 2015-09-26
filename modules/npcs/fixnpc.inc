
/*
* Fixar algumas funções do RNPC 
* e corrigir declarações do FCNPC
* Deixar compatível com os dois plugins:
* npc.FUNC(params)
*
**/


#if !defined _FCNPC_included
	
	#define RNPC 

	#if defined RNPC_StopPlayback
	#undef RNPC_StopPlayback
	#endif 
	#define RNPC_StopPlayback FIX_RNPC

	stock FIX_RNPC(i) {

		static Float:a, Float:b, Float:c;
		GetPlayerPos(i,a,b,c);
		MoveRNPC(i,a,b+0.3,c, 0.006);
		return true;
	}


	forward FCNPC_OnCreate(npcid);
	

#else
	#pragma library "FCNPC"
	#undef MAX_NODES
#endif



#define npc. npc__




new Float:NPC_WALK = (0.0015);
new Float:NPC_RUN = (0.0055);
//new Float:NPC_SPRINT = (0.0095);






stock npc__Stop(n) {

		
	#if defined RNPC
		return RNPC_StopPlayback(n);
	#else
		return FCNPC_Stop(n);
       	#endif
}
   

stock npc__moveTo(n, Float:x, Float:y, Float:z, Float: vel) {

		
	#if defined RNPC
		return  MoveRNPC (n, x,y,z, vel );
	#else
		return  FCNPC_GoTo (n, x,y,z, vel <= NPC_RUN ? MOVE_TYPE_WALK : vel <= NPC_SPRINT ? MOVE_TYPE_RUN : MOVE_TYPE_SPRINT , 0, 1);
       	#endif   
}





stock npc__SetRate(rate) {
	#if defined RNPC
		return RNPC_SetUpdateRate(rate);
	#else
		return FCNPC_SetUpdateRate(rate);
	#endif
}





stock npc__Connect(name[]) {

	#if defined RNPC
		return  ConnectRNPC(name);
	#else
         	return  FCNPC_Create(name);
	#endif
}





stock npc__SetPos(n, Float:x, Float:y, Float:z) {

	#if defined RNPC
		return  SetPlayerPos(n, x, y, z);
	#else
         	return  FCNPC_SetPosition(n, x, y, z);
	#endif
}





stock npc__GetPos(n, &Float:x, &Float:y, &Float:z) {

	#if defined RNPC
		return  GetPlayerPos(n, x, y, z);
	#else
         	return  FCNPC_GetPosition(n, x, y, z);
	#endif
}

stock MapAndreas_FindZ_For2DCoordEx(Float:x, Float:y, &Float:z) {



	if(x >= 3000.0) x = 2999.0;
	if(x <= -3000.0) x = -2999.0;
	
	if(y >= 3000.0) y = 2999.0;
	if(y <= -3000.0) y = -2999.0;
	
	MapAndreas_FindZ_For2DCoord(x,y,z);
}

#define MapAndreas_FindZ_For2DCoord MapAndreas_FindZ_For2DCoordEx
