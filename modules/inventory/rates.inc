#define MAX_DROPPED_ITEMS sizeof(SpotNodes)

new RandomAcessObjects[MAX_DROPPED_ITEMS];
new AcessID[MAX_DROPPED_ITEMS];

GenerateDropRateObjects()
{
	new DropableObjects, LastAssignedID, Float:TotalDropRate;
	new TotalObjects = sizeof(ObjectsInfo);
	
	/*---------->COUNT OBJECTS AND RATES<----------*/
	
	for(new mi; mi < TotalObjects; mi++)
	{
		if(ObjectsInfo[mi][Object_DropRate] > 0)
		{
			TotalDropRate += ObjectsInfo[mi][Object_DropRate];
			DropableObjects++;
		}
	}
	
	new ObjectLimiter = floatround(MAX_DROPPED_ITEMS/TotalDropRate);	
	
	
	for(new obj; obj < TotalObjects; obj++)
	{
		if(!ObjectsInfo[obj][Object_DropRate]) continue;	
		
		new Float:rate = ObjectsInfo[obj][Object_DropRate];		
		new objLimit = floatround(ObjectLimiter * rate);
		new objCount;
		
		for(new o_slot = LastAssignedID; o_slot < MAX_DROPPED_ITEMS && objCount < objLimit;  o_slot++)
		{			
			if(!RandomAcessObjects[o_slot])
			{
				RandomAcessObjects[o_slot] = ObjectsInfo[obj][Object_Model];
				objCount++;
				LastAssignedID++;
				//printf("Slot %d has assumed the model %d!", o_slot, RandomAcessObjects[o_slot]);
			}			
		}		
	}
	print("Generating loots...");
	RegenerateLoots();
	return 1;
}

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
		new tmpModel = random(sizeof RandomAcessObjects),
		Float:tmpPosX = SpotNodes[o][SNodeX],
		Float:tmpPosY = SpotNodes[o][SNodeY],
		Float:tmpPosZ = SpotNodes[o][SNodeZ];
			
		if(AcessID[o])
		{
			new query[256];
			mysql_format(MySQL, query, 256, "UPDATE `items` SET `model` = '%d', `coord_x` = '%f', `coord_y` = '%f', `coord_z` = '%f', `interior` = '0', `world`= '0', `durability` = '100.0', `time` = '0', `expirable` = '0' WHERE `id` = '%d';", RandomAcessObjects[tmpModel], tmpPosX, tmpPosY, tmpPosZ, AcessID[o]);
			mysql_tquery(MySQL, query, "", "");
			CreateDroppedItem(AcessID[o], RandomAcessObjects[tmpModel], 1, tmpPosX, tmpPosY, tmpPosZ, 0, 0, 100.0, 0, 0, true);
			//printf("recreated item %d with model %d", AcessID[o], RandomAcessObjects[tmpModel]);
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

			mysql_format(MySQL, query, 256, "INSERT INTO `items` VALUES ('%d', '%d', '1', '-1', '%f', '%f', '%f', '0', '0', '100', '0', '0');", lastitemid, RandomAcessObjects[tmpModel], tmpPosX, tmpPosY, tmpPosZ);
			mysql_tquery(MySQL, query, "", "");
			CreateDroppedItem(lastitemid, RandomAcessObjects[tmpModel], 1, tmpPosX, tmpPosY, tmpPosZ, 0, 0, 100.0, 0, 0, true);
			//printf("created item %d with model %d", lastitemid, RandomAcessObjects[tmpModel]);
		}
		
	}
	return print("Loots sucessfully generated...");
}

