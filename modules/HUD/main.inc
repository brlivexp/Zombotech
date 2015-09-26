#include "../modules/HUD/aim.inc"

stock ShowPlayerHUD(playerid)
	for(new t; t < 45; t++) PlayerTextDrawShow(playerid, HUDText[playerid][t]);

stock HidePlayerHUD(playerid)
	for(new t; t < 45; t++) PlayerTextDrawHide(playerid, HUDText[playerid][t]);