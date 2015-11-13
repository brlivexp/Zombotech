#include "../modules/HUD/aim.inc"

stock ShowPlayerHUD(playerid)
{
	for(new t; t < 15; t++) TextDrawShowForPlayer(playerid, HudStatic[t]);
	for(new pt; pt < 11; pt++) PlayerTextDrawShow(playerid, HudText[playerid][pt]);
}
	
stock HidePlayerHUD(playerid)
{
	for(new t; t < 15; t++) TextDrawHideForPlayer(playerid, HudStatic[t]);
	for(new pt; pt < 11; pt++) PlayerTextDrawHide(playerid, HudText[playerid][pt]);
}
	