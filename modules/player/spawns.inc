SaveSpawnsPos(filename[]) {

	new File: f ;

	f = fopen(filename,filemode:io_write);

	static Float: x,Float: y,Float: z;


	for(new i; i != MAX_SPAWNS; i++) {
	    GetVectorPath(gSpawns, i, x, y, z);
		fwrite(f, sprintf("%f,%f,%f\r\n", x,y,z));
	}

	fclose(f);
	return true;
}

LoadSpawnsPos(filename[]) {

	new File:file_ptr;
	new line[512];
	new Float:SpawnX;
	new Float:SpawnY;
	new Float:SpawnZ;

    new Carregando;

	file_ptr = fopen(filename,filemode:io_read);

	if(!file_ptr) return 0;

	while(fread(file_ptr,line) > 0) {
	    if(!sscanf(line, "p,fff",SpawnX,SpawnY,SpawnZ)) {
	        Carregando++;
	        StoreVectorPath(gSpawns, SpawnX, SpawnY, SpawnZ);
        }
	}

	fclose(file_ptr);

	printf("Foram carregados %d spawns", Carregando);
	return true;
}



fp GenerateSpawns () {

	static Float:x, Float:y, Float:z, i;

	i = 0;

	for( ; i ^ MAX_SPAWNS; i++) {

		MRandFloatRange(-2999.0, 2999.0, x);
		MRandFloatRange(-2999.0, 2999.0, y);

        MapAndreas_FindZ_For2DCoord(x,y,z);

		if(16.0 > z > 5.0 && MapAndreasRoundGround(x,y,z, 20.0))
		    StoreVectorPath(gSpawns, x, y, z);
		else
		    if(i) i--;
	}
	return true;
}


fp ActiveSpawn(p)
{ 
	return SetPVarInt(p, "spawned", 1);
}