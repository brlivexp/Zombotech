
new Socket: servidorMods;

new modsList[][] = {
	// nome, download
	
   "infernus.dff", "http://down2money.net/getfile.php?D=1&URI=Wm05akwySnZkV2x3Y0daZmMyRnViMloxTURjM05EZ3lOall3TVRCa01qZHpNemczTVc5dk5qUXpOalE0T1hOek5qbDFZV3h6YjJKc0wyWnJaSE56LlpXMWhhV3hBWW5KMWJtOWtZWE5wYkhaaExtTnZiUT09LjE0MDYxODM0MDg%3D/infernus.dff&d",
   "infernus.txd", "http://down2money.net/getfile.php?D=1&URI=Wm05akwySnZkV2x3Y0daZmMyRnViMloxTURjM05EZ3lOall3TVRCa01qZHpNemczTVc5dk5qUXpOalE0T1hOek5qbDFZV3h6YjJKc0wyWnJkSGhrLlpXMWhhV3hBWW5KMWJtOWtZWE5wYkhaaExtTnZiUT09LjE0MDYxODMzMzQ%3D/infernus.txd&d"
};



public onSocketReceiveData(Socket:id, remote_clientid, data[], data_len)
{

	if(!strcmp(data, "GMODS", false)) {
	    for(new i; i < sizeof modsList; i+=2) {
	    	static to[0xff];
	    	format(to, 0xff, "|%s=>%s", modsList[i], modsList[i+1]);
			socket_sendto_remote_client(servidorMods,remote_clientid, to);
		}
		socket_close_remote_client(servidorMods, remote_clientid);
	}
	#if defined MyLib_onSocketReceiveData
        MyLib_onSocketReceiveData(id, remote_clientid, data, data_len);
    #endif
	return true;
}

#if defined _ALS_onSocketReceiveData
    #undef onSocketReceiveData
#else
    #define _ALS_onSocketReceiveData
#endif
#define onSocketReceiveData MyLib_onSocketReceiveData
#if defined MyLib_onSocketReceiveData
    forward MyLib_onSocketReceiveData(Socket:id, remote_clientid, data[], data_len);
#endif


public OnGameModeExit() {

   if(is_socket_valid(servidorMods))
        socket_destroy(servidorMods);

	#if defined MyLib_OnGameModeExit
        MyLib_OnGameModeExit();
    #endif
	return true;
}

#if defined _ALS_OnGameModeExit
    #undef OnGameModeExit
#else
    #define _ALS_OnGameModeExit
#endif
#define OnGameModeExit MyLib_OnGameModeExit
#if defined MyLib_OnGameModeExit
    forward MyLib_OnGameModeExit();
#endif



public OnGameModeInit() {

	// iniciar servidor para mods na porta 8080
    servidorMods = socket_create(TCP);
    if(is_socket_valid(servidorMods))
    {
        socket_set_max_connections(servidorMods, 500);
        socket_listen(servidorMods, 8080);
    }

    // imprimir com todas modificações
	print("Lista de modificações:");
	for(new i; i < sizeof modsList; i+=2) {
	    	static to[0xff];
	    	format(to, 0xff, "%s => %s", modsList[i], modsList[i+1]);
		    print(to);
	}
	#if defined MyLib_OnGameModeInit
        MyLib_OnGameModeInit();
    #endif
	return true;
}

#if defined _ALS_OnGameModeInit
    #undef OnGameModeInit
#else
    #define _ALS_OnGameModeInit
#endif
#define OnGameModeInit MyLib_OnGameModeInit
#if defined MyLib_OnGameModeInit
    forward MyLib_OnGameModeInit();
#endif