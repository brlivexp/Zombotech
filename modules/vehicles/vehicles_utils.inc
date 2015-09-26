
stock encode_panels(flp, frp, rlp, rrp, windshield, front_bumper, rear_bumper)
{
    return flp | (frp << 4) | (rlp << 8) | (rrp << 12) | (windshield << 16) | (front_bumper << 20) | (rear_bumper << 24);
}


stock encode_doors(bonnet, boot, driver_door, passenger_door, behind_driver_door = 0, behind_passenger_door = 0)
{
    #pragma unused behind_driver_door
    #pragma unused behind_passenger_door
    return bonnet | (boot << 8) | (driver_door << 16) | (passenger_door << 24);
}

stock encode_lights(light1, light2, light3, light4)
{
    return light1 | (light2 << 1) | (light3 << 2) | (light4 << 3);
}



stock decode_tires(tires, &tire1, &tire2, &tire3, &tire4)
{
    tire1 = tires & 1;
    tire2 = tires >> 1 & 1;
    tire3 = tires >> 2 & 1;
    tire4 = tires >> 3 & 1;
}

stock encode_tires(tire1, tire2, tire3, tire4)
{
	return tire1 | (tire2 << 1) | (tire3 << 2) | (tire4 << 3);
}

stock GetVehicleSide(playerid, vehicleid)
{
	static Float:x[5],Float:y[5],Float:z[5];

	GetPosBetweenVehicle(vehicleid, x[0], y[0], z[0],.dangle = -180.0);
	GetPosBetweenVehicle(vehicleid, x[1], y[1], z[1],.dangle = -000.0);
	GetPosBetweenVehicle(vehicleid, x[2], y[2], z[2],.dangle = -090.0);
	GetPosBetweenVehicle(vehicleid, x[3], y[3], z[3],.dangle =  090.0);

	z[0] = GetPlayerDistanceFromPoint(playerid, x[0], y[0], z[0]);
	z[1] = GetPlayerDistanceFromPoint(playerid, x[1], y[1], z[1]);
	z[2] = GetPlayerDistanceFromPoint(playerid, x[2], y[2], z[2]);
	z[3] = GetPlayerDistanceFromPoint(playerid, x[3], y[3], z[3]);

	if(z[0]<z[1])
	if(z[0]<z[2])
	if(z[0]<z[3])
	return VEHICLE_FRONT;

	if(z[1]<z[2])
	if(z[1]<z[3])
	return VEHICLE_BACK;

	if(z[2]<z[3])
	return VEHICLE_LEFT;

	return VEHICLE_RIGHT;
}

stock GetPosBetweenVehicle(vehicleid, &Float:x, &Float:y, &Float:z, Float:offset=0.5, Float:dangle = 0.0)
{
	new Float:vehicleSize[3], Float:vehiclePos[3];
	GetVehiclePos(vehicleid, vehiclePos[0], vehiclePos[1], vehiclePos[2]);
	GetVehicleModelInfo(GetVehicleModel(vehicleid), VEHICLE_MODEL_INFO_SIZE, vehicleSize[0], vehicleSize[1], vehicleSize[2]);
	GetXYBehindVehicle(vehicleid, vehiclePos[0], vehiclePos[1], (vehicleSize[1]/2)+offset, dangle);
	x = vehiclePos[0];
	y = vehiclePos[1];
	z = vehiclePos[2];
	return 1;
}

stock GetXYBehindVehicle(vehicleid, &Float:q, &Float:w, Float:distance, Float:dangle = 0.0)
{
	new Float:a;
	GetVehiclePos(vehicleid, q, w, a);
	GetVehicleZAngle(vehicleid, a);
	q += (distance * -floatsin(-a-dangle, degrees));
	w += (distance * -floatcos(-a-dangle, degrees));
}



