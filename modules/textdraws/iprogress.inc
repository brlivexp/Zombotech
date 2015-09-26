#define BAR_COLOR_WARNING
#define BAR_COLOR_NORMAL

stock SetProgressLevel(playerid, PlayerText:playertext, Float:barlevel, Float:start, Float:end, Float:sizeY = 1.0)
{
	if(0.0 > barlevel > 100.0) return 0;

	new Float:full = end - start;
	new Float:result = start + ((full * barlevel) / 100);

	PlayerTextDrawTextSize(playerid, playertext, barlevel < 51.0 ? result - 5.0 : result, sizeY);
	return 1;
}