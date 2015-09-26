/*
*
* Função importante para o IA do NPC
* Essa função checa se entre nX nY e pX pY tem algum obstaculo
* Ex: muro, casas, postes, arvores, então ele retorna FALSE
* Isto evita que o NPC passe por cima das casas ou prédios ;)
* No entanto, como MapAndreas não é muito preciso, o NPC pode passar por cima de pequenos muros
*
*/

#if defined _route_included
        #endinput
#endif
 
#define _route_included

stock DiagonalRoute(Float:x1,Float:y1,Float:z1,Float:x2,Float:y2,Float:z2,Float:maxSteps=75.0,Float:maxHeigth = 2.0, id = -1)
{

	static
		Float:a,
		Float:x3,
		Float:y3,
		Float:z3;
	
	a = atan2(y2-y1,x2-x1);
	

	x3 = floatsin(-a-90, degrees); x3 *= floatabs(x2-x1)/floatabs(x3)/maxSteps;
	y3 = floatcos(-a-90, degrees); y3 *= floatabs(y2-y1)/floatabs(y3)/maxSteps;



	if(x1 > x2) {
		for( ; x1 > x2; ) {
		
			y2 += y3;
			x2 += x3;
			
			MapAndreas_FindZ_For2DCoord(x2, y2, z3);

			if(floatabs(z2-z3) > maxHeigth ) {
				return  false;
			}
			z2 = z3;

			if(~id) {
				for (new i = 0, j = vector_size(gVehiclesStream[id]) ; i < j  ; i++) {
				
		        	static v;
      				v = vector_get(gVehiclesStream[id], i);
			
				
			
					static Float: vehSize[3];
					GetVehiclePos(v, vehSize[0], vehSize[1], vehSize[2]);
					if(distance(vehSize[0], vehSize[1], vehSize[2], x2, y2, z2) < 7.0) 
						return false;
			
				}
			}


	
		}
	}
	else {
		for( ; x1 < x2; ) {
			// y2 x2
			y2 += y3;
			x2 += x3;
			MapAndreas_FindZ_For2DCoord(x2, y2, z3);

			if(floatabs(z2-z3) > maxHeigth ) {
				return  false;
			}
			z2 = z3;


			if(~id) {
				for (new i = 0, j = vector_size(gVehiclesStream[id]) ; i < j  ; i++) {
				
		        	static v;
      				v = vector_get(gVehiclesStream[id], i);
			
				
			
					static Float: vehSize[3];
					GetVehiclePos(v, vehSize[0], vehSize[1], vehSize[2]);
					if(distance(vehSize[0], vehSize[1], vehSize[2], x2, y2, z2) < 7.0) 
						return false;
			
				}
			}


		}
	}
	

	
 	return floatabs(z3-z1) < maxHeigth;
}