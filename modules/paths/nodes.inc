#define LOOT_SURVIVOR 0
#define LOOT_CIVILIAN 1
#define LOOT_INDUSTRIAL 2
#define LOOT_POLICE 3
#define LOOT_MILITARY 4
#define LOOT_MEDICAL 5

enum NodeInfo
{
	Float:NodeX,
	Float:NodeY,
	Float:NodeZ,
	link1ID,
	navi1ID,
	link2ID,
	navi2ID,
	link3ID,
	navi3ID,
	link4ID,
	navi4ID,
	bool:RoadNode_Taken
};
enum PedNodeInfo
{
	Float:PNodeX,
	Float:PNodeY,
	Float:PNodeZ,
	bool:PedNode_Taken
};
enum SpotNodeInfo
{
	Float:SNodeX,
	Float:SNodeY,
	Float:SNodeZ,
	Spawn_Type,
	bool:SpotNode_Taken
};
new RoadNodes[27083][NodeInfo];
new PedNodes[37705][PedNodeInfo];
new SpotNodes[9886][SpotNodeInfo];

LoadRoadNodes()
{
	print("Server is now loading roadnodes...");
	new loaded, line[256];
	new File:file_ptr;

	file_ptr = fopen("roadnodes.db", filemode:io_read);

	if(!file_ptr) return print("Error, server could not find roadnodes.db");

	static Float:f[3], i[8], bool:l; 

	while(fread(file_ptr, line) > 0)
	{
	    if(!sscanf(line, "p,fffddddddddl", f[0], f[1], f[2], i[0], i[1], i[2], i[3], i[4], i[5], i[6], i[7], l))
		{
		    RoadNodes[loaded][NodeX] = f[0];
	    	RoadNodes[loaded][NodeY] = f[1];
	    	RoadNodes[loaded][NodeZ] = f[2];
	    	RoadNodes[loaded][link1ID] = i[0];
			RoadNodes[loaded][navi1ID] = i[1];
			RoadNodes[loaded][link2ID] = i[2];
			RoadNodes[loaded][navi2ID] = i[3];
			RoadNodes[loaded][link3ID] = i[4];
			RoadNodes[loaded][navi3ID] = i[5];
			RoadNodes[loaded][link4ID] = i[6];
			RoadNodes[loaded][navi4ID] = i[7];
			RoadNodes[loaded][RoadNode_Taken] = l;	    	
			loaded++;	    
		} 	        
	}

	fclose(file_ptr);

	printf("Server loaded %d roadnodes", loaded);
	return 1;
}

LoadPedNodes()
{
	print("Server is now loading pednodes...");
	new loaded, line[256];
	new File:file_ptr;

	file_ptr = fopen("pednodes.db", filemode:io_read);

	if(!file_ptr) return print("Error, server could not find pednodes.db");

	static Float:f[3], bool:l; 

	while(fread(file_ptr, line) > 0)
	{
	    if(!sscanf(line, "p,fffl", f[0], f[1], f[2], l))
		{
		    PedNodes[loaded][PNodeX] = f[0];
	    	PedNodes[loaded][PNodeY] = f[1];
	    	PedNodes[loaded][PNodeZ] = f[2];
			PedNodes[loaded][PedNode_Taken] = l;	    	
			loaded++;	    
		} 	        
	}

	fclose(file_ptr);

	printf("Server loaded %d pednodes", loaded);
	return 1;
}

LoadSpotNodes()
{
	print("Server is now loading spotnodes...");
	new loaded, line[256];
	new File:file_ptr;

	file_ptr = fopen("spotnodes.db", filemode:io_read);

	if(!file_ptr) return print("Error, server could not find spotnodes.db");

	static Float:f[3], i, bool:l; 

	while(fread(file_ptr, line) > 0)
	{
	    if(!sscanf(line, "p,fffdl", f[0], f[1], f[2], i, l))
		{
		    SpotNodes[loaded][SNodeX] = f[0];
	    	SpotNodes[loaded][SNodeY] = f[1];
	    	SpotNodes[loaded][SNodeZ] = f[2];
	    	SpotNodes[loaded][Spawn_Type] = i;
			SpotNodes[loaded][SpotNode_Taken] = l;	    	
			loaded++;	    
		} 	        
	}

	fclose(file_ptr);

	printf("Server loaded %d spotnodes", loaded);
	return 1;
}