/**************
 * RAK v1.0   *
 * @bartekdvd *
 **************/

#if !defined _RAK_included
#define _RAK_included

enum
{
	BS_BOOL,
	BS_CHAR,
	BS_UCHAR,
	BS_SHORT,
	BS_USHORT,
	BS_INT,
	BS_UINT,
	BS_FLOAT,
	BS_STRING,
	BSC_BOOL,
	BSC_CHAR,
	BSC_UCHAR,
	BSC_SHORT,
	BSC_USHORT,
	BSC_INT,
	BSC_UINT,
	BSC_FLOAT,
	BSC_STRING,
	BS_NQUAT,
	BS_VECTOR,
	BS_ARRAY_BYTE,
	BS_ARRAY_WORD,
	BS_ARRAY_DWORD
};

native BitStream:InitBitStream();
native WriteToBitStream(BitStream:stream, type, {Float,_}:...);
native ReleaseBitStream(BitStream:stream);
native SendRPC(playerid, RPC, BitStream:stream);
native SendRPCToAll(RPC, BitStream:stream);
native SendData(playerid, BitStream:stream);
native SendDataToAll(BitStream:stream);
native AddTickSignal(index);
native RemoveTickSignal(index);

#endif

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