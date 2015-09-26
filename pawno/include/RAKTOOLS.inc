#if !defined _RAKTOOLS_included
#define _RAKTOOLS_included

#include <a_samp>
#tryinclude <RAK>
#tryinclude "RAK"

#define RPC_Widescreen	(0x6F | 111)

stock TogglePlayerHUD(playerid, bool:toggle)
{
	new BitStream:stream = InitBitStream();
	
	WriteToBitStream(stream, BS_UCHAR, !toggle);
	
	SendRPC(playerid, RPC_Widescreen, stream);
	
	ReleaseBitStream(stream);
}

#endif