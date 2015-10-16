#define MAX_DROPPED_ITEMS sizeof(SpotNodes)
#define MAX_RANDOM_MODELS 1000

#define LOOT_NONE -1
#define LOOT_SURVIVOR 0
#define LOOT_CIVILIAN 1
#define LOOT_INDUSTRIAL 2
#define LOOT_POLICE 3
#define LOOT_MILITARY 4
#define LOOT_MEDICAL 5

new AcessID[MAX_DROPPED_ITEMS];


stock RegenerateLoots()
{
	new lastitemid, cquery[128];
	mysql_format(MySQL, cquery, 128, "SELECT * FROM `items` WHERE `owner` = '-1' AND `model` = '19475' LIMIT %d;", MAX_DROPPED_ITEMS);
	new Cache:result = mysql_query(MySQL, cquery, true);
	for(new qq; qq < cache_num_rows(); qq++)
	{
		if(MAX_DROPPED_ITEMS <= qq) break;
		AcessID[qq] = cache_get_field_content_int(qq, "id");
	}

	printf("Loaded %d already have created ids for update...\nDestroying cache...", cache_num_rows());
	cache_delete(result);
	print("Creating loots...");

	
					
	for(new o; o < MAX_DROPPED_ITEMS; o++)
	{
		new LootType = SpotNodes[o][Spawn_Type];
		new tmpModel = GetRandomModelType(LootType),
		Float:tmpPosX = SpotNodes[o][SNodeX],
		Float:tmpPosY = SpotNodes[o][SNodeY],
		Float:tmpPosZ = SpotNodes[o][SNodeZ];

		new minimum, maximum;
		GetObjectDropAmount(tmpModel, minimum, maximum);
		new tmpAmount = MRandRange(minimum, maximum);
			
		if(AcessID[o])
		{
			new query[256];
			mysql_format(MySQL, query, 256, "UPDATE `items` SET `model` = '%d', `amount` = '%d', `coord_x` = '%f', `coord_y` = '%f', `coord_z` = '%f', `interior` = '0', `world`= '0', `durability` = '100.0', `time` = '0', `expirable` = '0' WHERE `id` = '%d';", tmpModel, tmpAmount, tmpPosX, tmpPosY, tmpPosZ, AcessID[o]);
			mysql_tquery(MySQL, query, "", "");
			CreateDroppedItem(AcessID[o], tmpModel, tmpAmount, tmpPosX, tmpPosY, tmpPosZ, 0, 0, 100.0, 0, 0, true);
			//printf("recreated item %d with model %d", AcessID[o], tmpModel);
		}
		else
		{
			static query[256];

			if(!lastitemid)
			{
				
				new Cache:qresult = mysql_query(MySQL, "SELECT * FROM `items` ORDER BY `id` DESC LIMIT 1;");
				lastitemid = cache_get_field_content_int(0, "id") + 1;
				cache_delete(qresult);
			}
			else lastitemid++;	

			mysql_format(MySQL, query, 256, "INSERT INTO `items` VALUES ('%d', '%d', '%d', '-1', '%f', '%f', '%f', '0', '0', '100', '0', '0');", lastitemid, tmpModel, tmpAmount, tmpPosX, tmpPosY, tmpPosZ);
			mysql_tquery(MySQL, query, "", "");
			CreateDroppedItem(lastitemid, tmpModel, tmpAmount, tmpPosX, tmpPosY, tmpPosZ, 0, 0, 100.0, 0, 0, true);
			//printf("created item %d with model %d", lastitemid, tmpModel);
		}
		
	}
	return print("Loots sucessfully generated...");
}


GetRandomModelType(type)
{
	//holds the RAO
	new RandomModel[MAX_RANDOM_MODELS];

	new Float:TotalDropRate,
	bool:AllowedObject[sizeof ObjectsInfo],
	LastAssignedID;

	for(new i; i < sizeof(ObjectsInfo); i++)
	{
		if(ObjectsInfo[i][Object_DropRate] > 0.0 && ObjectsInfo[i][loot_type] == type)
		{
			TotalDropRate += ObjectsInfo[i][Object_DropRate];
			AllowedObject[i] = true;
		}
	}

	new ObjectLimiter = floatround(MAX_RANDOM_MODELS/TotalDropRate);
	
	for(new k; k < sizeof(ObjectsInfo); k++)
	{
		if(!AllowedObject[k]) continue;

		new Float:rate = ObjectsInfo[k][Object_DropRate];		
		new objLimit = floatround(ObjectLimiter * rate);
		new objCount;
			
		for(new o_slot = LastAssignedID; o_slot < MAX_RANDOM_MODELS && objCount < objLimit;  o_slot++)
		{			
			if(!RandomModel[o_slot])
			{
				RandomModel[o_slot] = ObjectsInfo[k][Object_Model];
				objCount++;
				LastAssignedID++;
			}			
		}		
	}
	return RandomModel[MRandom(sizeof RandomModel)];	
}