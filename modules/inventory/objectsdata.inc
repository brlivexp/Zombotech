#define LOOT_NONE -1
#define LOOT_SURVIVOR 0
#define LOOT_CIVILIAN 1
#define LOOT_INDUSTRIAL 2
#define LOOT_POLICE 3
#define LOOT_MILITARY 4
#define LOOT_MEDICAL 5

enum ObjectsData
{
	Object_Model,
	Object_Name[50],
	Float:Object_DropRate,
	Float:Object_eHunger,
	Float:Object_eThirst,
	Float:Object_eDamage,
	Float:Object_eEnergy,
	Float:Object_eTemp,
	Float:Object_eHealth,
	Object_Color,
	Object_TXD_Color,
	Float:Object_TXD_rx,
	Float:Object_TXD_ry,
	Float:Object_TXD_rz,
	Float:Object_TXD_Zoom,
	Float:Object_rx,
	Float:Object_ry,
	Float:Object_rz,
	Object_material_color,
	bool:Stackable,
	Max_stack,
	Float:Label_additional_height,
	Float:Object_zindex_height,
	min_drop_amount,
	max_drop_amount,
	loot_type,
	Object_TXR_Lib[32],
	Object_TXR_Name[32],
	Object_Description[200]
}

/********************************************************************************************************************/
/*											Objects	Info															*/
/********************************************************************************************************************/
new ObjectsInfo[][ObjectsData] =
{
/*
*/
	{19579,			"Bread Loaf",	  		6.0,					100.0,					0.0,					0.0,			  	  0.0,			0.0,				0.0,			(0xCC9966),			(0xFFFFFF),			0.0,		0.0,		-55.0,		1.2,			0.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				1,		LOOT_CIVILIAN,					"none", 				 "none",						"You found a Bread Loaf, eat the bread bitch!"},
	{19571,			"Pizza Box",	  		4.0,					100.0,					0.0,					0.0,			  	  0.0,			0.0,				0.0,			(0xFFCC66),			(0xFFFFFF),			0.0,		0.0,		0.0,		1.2,			90.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				1,		LOOT_CIVILIAN,					"none", 				 "none",						"You found a Box of Pizza!~n~Pizza Stack Co. left you this gift!"},
	{2703,			"Burger",	  			9.0,					85.0,					0.0,					0.0,			  	  0.0,			0.0,				0.0,			(0xFFCC00),			(0xFFFFFF),			235.0,		-83.0,		-55.0,		1.2,			270.0,			-83.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				1,		LOOT_CIVILIAN,					"none", 				 "none",						"You found a Burger!~n~Don't forget to say thanks BurgerShot while eat!"},
	{19561,			"Corn Cereal",	  		10.0,					65.0,					0.0,					0.0,			  	  0.0,			0.0,				0.0,			(0xFFCC99),			(0xFFFFFF),			0.0,		0.0,		0.0,		1.2,			0.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				1,		LOOT_CIVILIAN,					"none", 				 "none",						"You found a Box of Cereal!~n~Crispy flakes for the win!"},
	{19562,			"Cereal",	  			10.0,					65.0,					0.0,					0.0,			  	  0.0,			0.0,				0.0,			(0xFFCC99),			(0xFFFFFF),			0.0,		0.0,		0.0,		1.2,			0.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				1,		LOOT_CIVILIAN,					"none", 				 "none",						"You found a Box of Cereal!~n~Want a Cock o Pops?"},
	{19568,			"Ice Cream Pot",	  	10.0,					60.0,					0.0,					0.0,			  	  0.0,			0.0,				0.0,			(0xFFFF99),			(0xFFFFFF),			-35.0,		0.0,		-55.0,		1.2,			-35.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				1,		LOOT_CIVILIAN,					"none", 				 "none",						"You found an Ice Cream Pot!~n~You can split it to get ice cream bars!"},
	{2769,			"Taco",	  				10.0,					60.0,					0.0,					0.0,			  	  0.0,			0.0,				0.0,			(0xFFFFCC),			(0xFFFFFF),			-35.0,		0.0,		-55.0,		1.2,			-35.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				1,		LOOT_CIVILIAN,					"none", 				 "none",						"You found a Taco!~n~Comida mexicana cabron!"},
	{19560,			"Raw Meat Tray",	  	10.0,					35.0,					0.0,					0.0,			  	  0.0,			0.0,				0.0,			(0xFF6666),			(0xFFFFFF),			0.0,		0.0,		0.0,		1.2,			0.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				1,		LOOT_CIVILIAN,					"none", 				 "none",						"You found a Meat Tray!~n~Cook it to get 3 cooked meat steaks~n~If you eat this without cook, you can get diarrhea."},
	{19566,			"Box of Raw Fishes",	10.0,					35.0,					0.0,					0.0,			  	  0.0,			0.0,				0.0,			(0xFF99CC),			(0xFFFFFF),			0.0,		0.0,		0.0,		1.2,			90.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				1,		LOOT_INDUSTRIAL,				"none", 				 "none",						"You found a Box of Fish!~n~Cook it to get 3 cooked fishes~n~If you eat this without cook, you can get diarrhea~n~and sickness."},
	{19630,			"Cooked Fish",			0.0,					80.0,					0.0,					0.0,			  	  0.0,			0.0,				0.0,			(0xA8A8A8),			(0xFFFFFF),			0.0,		0.0,		0.0,		1.2,			90.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				1,		LOOT_INDUSTRIAL,				"none", 				 "none",						"You found a Cooked Fish!~n~It can't kiss you anymore!"},
	{19882,			"Cooked Meat",			0.0,					80.0,					0.0,					0.0,			  	  0.0,			0.0,				0.0,			(0x993300),			(0xFFFFFF),			0.0,		0.0,		-55.0,		1.2,			0.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				1,		LOOT_INDUSTRIAL,				"none", 				 "none",						"You found a Cooked Meat!~n~Eat it before it eat you!"},
	{19847,			"Cooked Leg Ham",		0.0,					100.0,					0.0,					0.0,			  	  0.0,			0.0,				0.0,			(0x990000),			(0xFFFFFF),			0.0,		0.0,		-55.0,		1.2,			0.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				1,		LOOT_INDUSTRIAL,				"none", 				 "none",						"You found a Leg Ham!~n~You don't need to cook, eat it!"},
	{19883,			"Slice of Bread",		14.0,					20.0,					0.0,					0.0,			  	  0.0,			0.0,				0.0,			(0xCC9966),			(0xFFFFFF),			0.0,		0.0,		0.0,		1.2,			0.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				1,		LOOT_INDUSTRIAL,				"none", 				 "none",						"You found a Slice of Bread!~n~This item can be retrieved by splitting a bread~n~loaf."},
	{2702,			"Slice of Pizza",		13.0,					30.0,					0.0,					0.0,			  	  0.0,			0.0,				0.0,			(0xFFCC66),			(0xFFFFFF),			180.0,		90.0,		0.0,		1.2,			0.0,			280.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				1,		LOOT_INDUSTRIAL,				"none", 				 "none",						"You found a Slice of Pizza!~n~This item can be retrieved by splitting a box~n~of pizza."},
	{19565,			"Ice Cream Bar",	  	8.0,					75.0,					0.0,					0.0,			  	  0.0,			0.0,				0.0,			(0x993300),			(0xFFFFFF),			0.0,		0.0,		0.0,		1.2,			90.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				1,		LOOT_INDUSTRIAL,				"none", 				 "none",						"You found an Ice Cream Bar!~n~Eat it before it melts on your nutsack!"},
	{19582,			"Raw Meat",	  			9.0,					20.0,					0.0,					0.0,			  	  0.0,			0.0,				0.0,			(0xFF6666),			(0xFFFFFF),			0.0,		0.0,		-55.0,		1.2,			0.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				1,		LOOT_INDUSTRIAL,				"none", 				 "none",						"You found a Raw Meat!~n~Cook it to feed more hunger!~n~If you eat this without cook, you can get diarrhea~n~and sickness."},
	{1600,			"Raw Fish",				5.0,					18.0,					0.0,					0.0,			  	  0.0,			0.0,				0.0,			(0xA8A8A8),			(0xFFFFFF),			0.0,		0.0,		0.0,		1.2,			0.0,			100.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				1,		LOOT_INDUSTRIAL,				"none", 				 "none",						"You found a Raw Fish, is it a fish kisser?~n~Run, it is!~n~This item can be retrieved by splitting~n~a box of fishes."},
	{2804,			"Raw Leg Ham",		    4.0,					35.0,					0.0,					0.0,			  	  0.0,			0.0,				0.0,			(0xFF6666),			(0xFFFFFF),			0.0,		0.0,		225.0,		1.2,			0.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				1,		LOOT_INDUSTRIAL,				"none", 				 "none",						"You found a Raw Leg Ham!~n~If you eat this without cook, you can get diarrhea~n~and sickness."},
	{11741,			"Chocolate Cake",	    2.0,					100.0,					0.0,					0.0,			  	  0.0,			0.0,				0.0,			(0x663300),			(0xFFFFFF),			-35.0,		0.0,		280.0,		1.2,			-35.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				1,		LOOT_INDUSTRIAL,				"none", 				 "none",						"You found a Cake, today is your birthday?~n~You can split it to get cake slices."},
	{11742,			"Slice of Cake",	    12.0,					30.0,					0.0,					0.0,			  	  0.0,			0.0,				0.0,			(0x663300),			(0xFFFFFF),			-35.0,		0.0,		225.0,		1.2,			-35.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				1,		LOOT_INDUSTRIAL,				"none", 				 "none",						"You found a Cake Slice, today is your birthday?~n~This item can be retrieved by splitting a chocolate~n~cake."},
	{19574,			"Orange",	    		16.0,					30.0,					0.0,					0.0,			  	  0.0,			0.0,				0.0,			(0xFF9900),			(0xFFFFFF),			-35.0,		0.0,		225.0,		1.2,			-35.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				1,		LOOT_CIVILIAN,					"none", 				 "none",						"You found an Orange, vitamin C bitch!"},
	{19575,			"Apple",	  			16.0,					30.0,					0.0,					0.0,			  	  0.0,			0.0,				0.0,			(0xFF3333),			(0xFFFFFF),			-35.0,		0.0,		225.0,		1.2,			-35.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				1,		LOOT_CIVILIAN,					"none", 				 "none",						"You found an Apple!~n~Bite it and Steve Jobs will be your friend!"},
	{19576,			"Green Apple",			14.0,					30.0,					0.0,					0.0,			  	  0.0,			0.0,				0.0,			(0x99CC00),			(0xFFFFFF),			-35.0,		0.0,		225.0,		1.2,			-35.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				1,		LOOT_CIVILIAN,					"none", 				 "none",						"You found a Green Apple!~n~Bite it and Steve Jobs will be your friend forever!"},
	{19577,			"Tomatoe",	    		12.0,					30.0,					0.0,					0.0,			  	  0.0,			0.0,				0.0,			(0xFF0033),			(0xFFFFFF),			-35.0,		0.0,		225.0,		1.2,			-35.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				1,		LOOT_CIVILIAN,					"none", 				 "none",						"You found a Tomatoe!~n~Don't smash this if you don't like ketchup!"},
	{19578,			"Banana",	  			12.0,					30.0,					0.0,					0.0,			  	  0.0,			0.0,				0.0,			(0xFFFF00),			(0xFFFFFF),			-35.0,		0.0,		225.0,		1.2,			-35.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				1,		LOOT_CIVILIAN,					"none", 				 "none",						"You found a Banana!~n~Slice and his crew probably killed it!"},
/*
	Drinks
	|>model<|________|>name<|____________|>rate<|___________|>effect_hunger<|______|>effect_thirst<|______|>effect_damage<|_____|>effect_sleep<|_____|>effect_temp|_____|>effect_health|_____|>color<|_______|>txd_color<|______|>txd_rx<|___|>txd_ry<|___|>txd_rz<|___|>txd_zoom<|____|>obj_rx<|___|>obj_ry<|___|>obj_rz<|___|>obj_color<|______|>stackable<|___|>max_stack<|____|>label_height<|__|>object_z_index<|_|>txr_lib<|____________|>txr_name<|__________________|>Description<|
*/
	{19563,			"Orange Juice",	  		8.0,					  0.0,					90.0,					0.0,			  	  0.0,			0.0,				0.0,			(0xFF9900),			(0xFFFFFF),			0.0,		0.0,		0.0,		1.2,			0.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				1,		LOOT_CIVILIAN,					"none", 				 "none",						"You found an Orange Juice!~n~Who smashed the organge to do it?"},
	{19564,			"Green Apple Juice",	8.0,					  0.0,					90.0,					0.0,			  	  0.0,			0.0,				0.0,			(0x99CC00),			(0xFFFFFF),			0.0,		0.0,		0.0,		1.2,			0.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				1,		LOOT_CIVILIAN,					"none", 				 "none",						"You found a Green Apple Juice!~n~Steve Jobs hates who crunched his apple!"},
	{19569,			"Milk Carton",			7.0,					  0.0,					100.0,					0.0,			  	  0.0,			0.0,				0.0,			(0xF0F0F0),			(0xFFFFFF),			0.0,		0.0,		0.0,		1.2,			0.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				1,		LOOT_CIVILIAN,					"none", 				 "none",						"You found a Milk Carton!~n~Be careful, it can be monkey cum in a box"},
	{19570,			"Milk Bottle",			12.0,					  0.0,					95.0,					0.0,			  	  0.0,			0.0,				0.0,			(0xF0F0F0),			(0xFFFFFF),			0.0,		0.0,		0.0,		1.2,			0.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				1,		LOOT_CIVILIAN,					"none", 				 "none",						"You found a Milk Bottle!~n~Be careful, it can be monkey cum in a bottle!"},
	{19835,			"Coffee Cup",			13.0,					  0.0,					75.0,					0.0,			  	  25.0,			0.0,				0.0,			(0x996633),			(0xFFFFFF),			0.0,		0.0,		90.0,		1.2,			0.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				1,		LOOT_CIVILIAN,					"none", 				 "none",						"You found a Cup of Coffee!~n~How does it still hot after so long time?"},
	{19820,			"Tequila",				6.0,					  0.0,					45.0,					0.0,			  	  0.0,			0.0,				0.0,			(0xFFCC66),			(0xFFFFFF),			0.0,		0.0,		90.0,		1.2,			0.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.6,			0.0,			1, 				1,		LOOT_INDUSTRIAL,				"none", 				 "none",						"You found a Tequila Bottle, get drunk bitch!"},
	{1951,			"Black Beer",			5.0,					  0.0,					25.0,					0.0,			  	  0.0,			0.0,				0.0,			(0x383838),			(0xFFFFFF),			0.0,		0.0,		90.0,		1.2,			0.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				1,		LOOT_INDUSTRIAL,				"none", 				 "none",						"You found a Black Beer Bottle!~n~Coke-Cola with alcohol? Made by Decano Co!"},
	{19824,			"Golden Champagne",		0.0,					  0.0,					100.0,					0.0,			  	  0.0,			0.0,				0.0,			(0xFFCC00),			(0xFF6600),			0.0,		0.0,		90.0,		1.2,			0.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.6,			0.0,			1, 				1,		LOOT_NONE,						"none", 				 "none",						"You found a Golden Champagne Bottle!~n~Directly from high Dubai!"},
	{2601,			"Sprunk Soda",			16.0,					  0.0,					75.0,					0.0,			  	  0.0,			0.0,				0.0,			(0x66CC00),			(0xFFFFFF),			0.0,		0.0,		280.0,		1.2,			0.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				1,		LOOT_CIVILIAN,					"none", 				 "none",						"You found a Sprunk Bottle, lemonade with gas!"},
	{1551,			"Water Bottle",			3.0,					  0.0,					100.0,					0.0,			  	  0.0,			0.0,				0.0,			(0xFFFFFF),			(0xFFFFFF),			0.0,		0.0,		0.0,		1.2,			0.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.3,			0.0,			1, 				1,		LOOT_CIVILIAN,					"none", 	 			 "none",						"You found a Water Bottle, drink it!"},
	{1484,			"Empty Bottle",			20.0,					  0.0,					0.0,					0.0,			  	  0.0,			0.0,				0.0,			(0xFFFFFF),			(0xFFFFFF),			0.0,		0.0,		0.0,		1.2,			-10.0,			30.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				1,		LOOT_CIVILIAN,					"none", 				 "none",						"You found an Empty Water Bottle!~n~You need to fill it with water to drink!"},
	{1668,			"Vodka",				10.0,					  0.0,					45.0,					0.0,			  	  0.0,			0.0,				0.0,			(0xD8D8D8),			(0xFFFFFF),			0.0,		0.0,		0.0,		1.2,			0.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				1,		LOOT_CIVILIAN,					"none", 				 "none",						"You found a Vodka Bottle!~n~Saarf and Jack left you this gift!"},
	{1666,			"Can of Beer",			12.0,					  0.0,					30.0,					0.0,			  	  0.0,			0.0,				0.0,			(0xCC9900),			(0xFFFFFF),			0.0,		0.0,		0.0,		1.2,			0.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				1,		LOOT_CIVILIAN,					"none", 				 "none",						"You found a Can of Beer, cevada amigo!"},
/*
	Weapons
	|>model<|________|>name<|____________|>rate<|___________|>effect_hunger<|______|>effect_thirst<|______|>effect_damage<|_____|>effect_sleep<|_____|>effect_temp|_____|>effect_health|_____|>color<|_______|>txd_color<|______|>txd_rx<|___|>txd_ry<|___|>txd_rz<|___|>txd_zoom<|____|>obj_rx<|___|>obj_ry<|___|>obj_rz<|___|>obj_color<|______|>stackable<|___|>max_stack<|____|>label_height<|__|>object_z_index<|_|>txr_lib<|_____________|>txr_name<|__________________|>Description<|
*/	
	{331,			"Brass Knuckles",		0.0,					  0.0,					0.0,					70.0,			  	  0.0,			0.0,				0.0,			(0x999999),			(0xFFFFFF),			0.0,		0.0,		-55.0,		2.4,			90.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				1,		LOOT_NONE,						"none", 				 "none",						"You found a Brass Knuckles!~n~Not so useful as a rpg but better than nothing!"},
	{333,			"Golf Club",			25.0,					  0.0,					0.0,					70.0,			  	  0.0,			0.0,				0.0,			(0x999999),			(0xFFFFFF),			0.0,		0.0,		-55.0,		2.4,			90.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				1,		LOOT_CIVILIAN,					"none", 				 "none",						"You found a Golf Club!~n~Are you going to play golf? Leave it!"},
	{334,			"Nightstick",			10.0,					  0.0,					0.0,					70.0,			  	  0.0,			0.0,				0.0,			(0x999999),			(0xFFFFFF),			0.0,		0.0,		-55.0,		2.4,			90.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				1,		LOOT_POLICE,					"none", 				 "none",						"You found a Night Stick!~n~Dropped by some COP asshole!"},
	{335,			"Knife",				14.0,					  0.0,					0.0,					70.0,			  	  0.0,			0.0,				0.0,			(0x999999),			(0xFFFFFF),			0.0,		0.0,		-55.0,		2.4,			90.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				1,		LOOT_SURVIVOR,					"none", 				 "none",						"You found a Knife!~n~Cut your enemies's head with this!"},
	{336,			"Baseball Bat",			10.0,					  0.0,					0.0,					15.0,			  	  0.0,			0.0,				0.0,			(0x999999),			(0xFFFFFF),			180.0,		90.0,		0.0,		2.4,			90.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				1,		LOOT_CIVILIAN,					"none", 				 "none",						"You found a Baseball Bat, watch out my balls!"},
	{337,			"Shovel",				13.0,					  0.0,					0.0,					70.0,			  	  0.0,			0.0,				0.0,			(0x999999),			(0xFFFFFF),			0.0,		0.0,		-55.0,		2.4,			-10.0,			270.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				1,		LOOT_CIVILIAN,					"none", 				 "none",						"You found a Shovel!~n~Oh that's sweet! You can now dig your own grave."},
	{338,			"Pool cue",				10.0,					  0.0,					0.0,					70.0,			  	  0.0,			0.0,				0.0,			(0x999999),			(0xFFFFFF),			0.0,		0.0,		-55.0,		2.4,			85.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				1,		LOOT_CIVILIAN,					"none", 				 "none",						"You found a Pool Cue!~n~Did you ever listened the story of this pool cue?~n~Ofcourse you didn't, it is useless."},
	{339,			"Katana",				15.0,					  0.0,					0.0,					70.0,			  	  0.0,			0.0,				0.0,			(0x8B0000),			(0xFFFFFF),			0.0,		0.0,		-55.0,		2.4,			85.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				1,		LOOT_SURVIVOR,					"none", 				 "none",						"You found a Katana!~n~Its your lucky day! Michonne left you a gift!"},
	{326,			"Cane",					16.0,					  0.0,					0.0,					70.0,			  	  0.0,			0.0,				0.0,			(0x999999),			(0xFFFFFF),			0.0,		0.0,		-55.0,		2.4,			85.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				1,		LOOT_CIVILIAN,					"none", 				 "none",						"You found a Cane!~n~Hey grandpa, who brought you back to life?"},
	
	{342,			"Grenade",				8.0,					  0.0,					0.0,					70.0,			  	  0.0,			0.0,				0.0,			(0x556B2F),			(0xFFFFFF),			0.0,		0.0,		-55.0,		2.4,			90.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				1,		LOOT_MILITARY,					"none", 				 "none",						"You found a Grenade!~n~Well, how can I say this?...~n~Allahu Akbar, booooooooooooooom!"},
	{344,			"Molotov Cocktail",		10.0,					  0.0,					0.0,					70.0,			  	  0.0,			0.0,				0.0,			(0xB22222),			(0xFFFFFF),			0.0,		0.0,		-55.0,		2.4,			90.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				1,		LOOT_SURVIVOR,					"none", 				 "none",						"You found a Molotov Cocktail!~n~Are you trying to date any firefighter lady?~n~They are now bringing you a hose faggot!"},

	{346,			"Colt 45",				18.0,					  0.0,					0.0,					50.0,			  	  0.0,			0.0,				0.0,			(0x999999),			(0xFFFFFF),			0.0,		0.0,		-55.0,		2.4,			90.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			8, 				20,		LOOT_SURVIVOR,					"none", 				 "none",						"You found a Colt 45!~n~Not strong as a Deagle but better than a Dildo!"},
	{347,			"Silenced Colt 45",		16.0,					  0.0,					0.0,					50.0,			  	  0.0,			0.0,				0.0,			(0x999999),			(0xFFFFFF),			0.0,		0.0,		-55.0,		2.4,			90.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			8, 				18,		LOOT_POLICE,					"none", 				 "none",						"You found a silenced Colt 45!~n~The typical weapon of back shooters!~n~Watchout coward!"},
	{348,			"Desert Eagle",			12.0,					  0.0,					0.0,					50.0,			  	  0.0,			0.0,				0.0,			(0x999999),			(0xFFFFFF),			0.0,		0.0,		-55.0,		2.4,			90.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			5, 				15,		LOOT_POLICE,					"none", 				 "none",						"You found a Desert Eagle!~n~Are you strong enough to shoot it while c-bug?!"},

	{349,			"Shotgun",				20.0,					  0.0,					0.0,					50.0,			  	  0.0,			0.0,				0.0,			(0x8B4513),			(0xFFFFFF),			0.0,		0.0,		-55.0,		2.4,			90.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			10, 			25,		LOOT_POLICE,					"none", 				 "none",						"You found a Shotgun!~n~Useless in long distances but one of best weapons in short ones!"},
	{350,			"Sawnoff Shotgun",		18.0,					  0.0,					0.0,					50.0,			  	  0.0,			0.0,				0.0,			(0x8B4513),			(0xFFFFFF),			0.0,		0.0,		-55.0,		2.4,			90.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			5, 				10,		LOOT_SURVIVOR,					"none", 				 "none",						"You found a Sawnoff Shotgun!~n~Oh, you're not strong enough to hold 2 of this?~n~Go get some pratice loser!"},
	{351,			"SPAS 12",				18.0,					  0.0,					0.0,					50.0,			  	  0.0,			0.0,				0.0,			(0x999999),			(0xFFFFFF),			0.0,		0.0,		-55.0,		2.4,			440.0,			-10.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			12, 			24,		LOOT_MILITARY,					"none", 				 "none",						"You found a SPAS 12!~n~God damn, this weapon is stronger and heavier than my dick!"},

	{352,			"Micro UZI",			15.0,					  0.0,					0.0,					50.0,			  	  0.0,			0.0,				0.0,			(0x999999),			(0xFFFFFF),			0.0,		0.0,		-55.0,		2.4,			90.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			20, 			30,		LOOT_MILITARY,					"none", 				 "none",						"You found a Micro UZI!~n~POP POP POP POP, are you shooting popcorns?"},
	{353,			"MP5",					13.0,					  0.0,					0.0,					50.0,			  	  0.0,			0.0,				0.0,			(0x999999),			(0xFFFFFF),			0.0,		0.0,		-55.0,		2.4,			80.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			20, 			35,		LOOT_POLICE,					"none", 				 "none",						"You found a MP5!~n~I know son, you're not pro enough to handle a Deagle..."},
	{372,			"TEC-9",				14.0,					  0.0,					0.0,					50.0,			  	  0.0,			0.0,				0.0,			(0x999999),			(0xFFFFFF),			0.0,		0.0,		-55.0,		2.4,			90.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			20, 			30,		LOOT_POLICE,					"none", 				 "none",						"You found a TEC-10!~n~And yes, 10 cause 7 8 9!~w~Was seven a zombie? O.o"},

	{355,			"AK47",					10.0,					  0.0,					0.0,					50.0,			  	  0.0,			0.0,				0.0,			(0xA0522D),			(0xFFFFFF),			0.0,		0.0,		-55.0,		2.4,			95.0,			100.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			15, 			45,		LOOT_MILITARY,					"none", 				 "none",						"You found a AK47!~n~Vladmir Putin left you this russian gift!~n~Made in Russia - 1947."},
	{356,			"M4A1",					11.0,					  0.0,					0.0,					50.0,			  	  0.0,			0.0,				0.0,			(0x999999),			(0xFFFFFF),			0.0,		0.0,		-55.0,		2.4,			95.0,			100.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			15, 			45,		LOOT_MILITARY,					"none", 				 "none",						"You found a M4A1!~n~Hell no!~n~How could someone die using this kind of weapon?"},
	{357,			"Country Rifle",		7.0,					  0.0,					0.0,					50.0,			  	  0.0,			0.0,				0.0,			(0x663333),			(0xFFFFFF),			0.0,		0.0,		-55.0,		2.4,			100.0,			100.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			10, 			30,		LOOT_SURVIVOR,					"none", 				 "none",						"You found a Country Rifle!~n~PT Player the farmer dropped this shit!"},
	{358,			"Sniper Rifle",			6.0,					  0.0,					0.0,					70.0,			  	  0.0,			0.0,				0.0,			(0x663333),			(0xFFFFFF),			0.0,		0.0,		-55.0,		2.4,			100.0,			100.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			10, 			30,		LOOT_MILITARY,					"none", 				 "none",						"You found a Sniper Rifle!~n~Are you a camper asshole? Campers must die!"},
	{359,			"RPG",					0.0,					  0.0,					0.0,					50.0,			  	  0.0,			0.0,				0.0,			(0x383838),			(0xFFFFFF),			0.0,		0.0,		-55.0,		2.4,			90.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				3,		LOOT_NONE,						"none", 				 "none",						"You found a RPG!~n~The dream of any muslim! Be careful when use this!"},
	{360,			"Heat Seeker",			0.0,					  0.0,					0.0,					50.0,			  	  0.0,			0.0,				0.0,			(0x383838),			(0xFFFFFF),			0.0,		0.0,		-55.0,		2.4,			90.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				5,		LOOT_NONE,						"none", 				 "none",						"You found a Heat Seeker!~n~God damn, do you know how rare it is?"},
	{361,			"Flame Thrower",		0.0,					  0.0,					0.0,					50.0,			  	  0.0,			0.0,				0.0,			(0x383838),			(0xFFFFFF),			0.0,		0.0,		-55.0,		2.4,			90.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				100,	LOOT_NONE,						"none", 				 "none",						"You found a Flame Thrower!~n~Burn the bitches babyyyyyyyyyy!"},
	{362,			"Minigun",				0.0,					  0.0,					0.0,					50.0,			  	  0.0,			0.0,				0.0,			(0x383838),			(0xFFFFFF),			0.0,		0.0,		-55.0,		2.4,			80.0,			0.0,		0.0,		0xFFFFFF,			false,			0, 					0.0,			0.0,			1, 				100,	LOOT_NONE,						"none", 				 "none",						"You found a Minigun!~n~Are you admin? NO?!~n~Are you ready for your ban?"},

	{363,			"C4 charge",			2.0,					  0.0,					0.0,					50.0,			  	  0.0,			0.0,				0.0,			(0x383838),			(0xFFFFFF),			0.0,		0.0,		-55.0,		2.4,			270.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				1,		LOOT_NONE,						"none", 				 "none",						"You found a C4!~n~Blow up the campers and any faggots on your way!"},
	{364,			"C4 detonator",			2.0,					  0.0,					0.0,					50.0,			  	  0.0,			0.0,				0.0,			(0x383838),			(0xFFFFFF),			0.0,		0.0,		-55.0,		2.4,			90.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				1,		LOOT_NONE,						"none", 				 "none",						"You found a C4 Detonator!~n~Click and boom baby hahahaha!"},
	{365,			"Spray",				30.0,					  0.0,					0.0,					50.0,			  	  0.0,			0.0,				0.0,			(0x556B2F),			(0xFFFFFF),			0.0,		0.0,		-55.0,		2.4,			90.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				100,	LOOT_CIVILIAN,					"none", 				 "none",						"You found a Spray Can!~n~Tshhhhhhhhhhhhhhhhhhh tshhhhhhh!~n~Dropped by Justin Bieber and pedobear."},
	{366,			"Fire Extinguisher",	30.0,					  0.0,					0.0,					50.0,			  	  0.0,			0.0,				0.0,			(0x8B0000),			(0xFFFFFF),			0.0,		0.0,		-55.0,		2.4,			0.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				100,	LOOT_INDUSTRIAL,				"none", 				 "none",						"You found a Fire Extinguisher!~n~If you stun me with this smoke I kill you bitch!"},
	{367,			"Camera",				20.0,					  0.0,					0.0,					50.0,			  	  0.0,			0.0,				0.0,			(0xDCDCDC),			(0xFFFFFF),			0.0,		0.0,		-55.0,		2.4,			0.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				1,		LOOT_CIVILIAN,					"none", 				 "none",						"You found a Camera!~n~Search for your enemies, zoom in and out!"},
	{368,			"Night Googles",		0.0,					  0.0,					0.0,					50.0,			  	  0.0,			0.0,				0.0,			(0x32CD32),			(0xFFFFFF),			0.0,		0.0,		-55.0,		2.4,			90.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				1,		LOOT_MILITARY,					"none", 				 "none",						"You found a Night Vision Googles!~n~Made for dark nights and blind guys!"},
	{369,			"Thermal Googles",		0.0,					  0.0,					0.0,					50.0,			  	  0.0,			0.0,				0.0,			(0xFFA500),			(0xFFFFFF),			0.0,		0.0,		-55.0,		2.4,			90.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				1,		LOOT_MILITARY,					"none", 				 "none",						"You found a Thermal Vision!~n~Made by Spion 007, the KP fag!"},
/*
	Ammo
		|>model<|________|>name<|____________|>rate<|___________|>effect_hunger<|______|>effect_thirst<|______|>effect_damage<|_____|>effect_sleep<|_____|>effect_temp|_____|>effect_health|_____|>color<|_______|>txd_color<|______|>txd_rx<|___|>txd_ry<|___|>txd_rz<|___|>txd_zoom<|____|>obj_rx<|___|>obj_ry<|___|>obj_rz<|___|>obj_color<|______|>stackable<|___|>max_stack<|____|>label_height<|__|>object_z_index<|_|>txr_lib<|_____________|>txr_name<|__________________|>Description<|
*/	
	{3052,			"Rifle Ammo",			10.0,					  0.0,					0.0,					00.0,			  	  0.0,			0.0,				0.0,			(0x999999),			(0xFFFFFF),			0.0,		0.0,		-55.0,		2.4,			0.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			10, 			20,		LOOT_MILITARY,					"none", 				 "none",						"You found a Box of Rifle Ammo!~n~You're a lucky man, now gtfo, camper fag."},
	{19995,			"Pistol Ammo",			20.0,					  0.0,					0.0,					00.0,			  	  0.0,			0.0,				0.0,			(0x999999),			(0xFFFFFF),			0.0,		0.0,		-55.0,		2.4,			0.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			10, 			45,		LOOT_POLICE,					"none", 				 "none",						"You found a Pistol Ammo Clip!~n~Useful for cross zombie heads!"},
	{2037,			"SMG Ammo",				20.0,					  0.0,					0.0,					00.0,			  	  0.0,			0.0,				0.0,			(0x999999),			(0xFFFFFF),			0.0,		0.0,		-55.0,		2.4,			0.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			10, 			30,		LOOT_POLICE,					"none", 				 "none",						"You found a SMG Ammo cartouche!~n~WTF? It looks like nails, are you using a~n~drilling machine?"},
	{2040,			"Shotgun Ammo",			20.0,					  0.0,					0.0,					00.0,			  	  0.0,			0.0,				0.0,			(0x999999),			(0xFFFFFF),			0.0,		0.0,		-55.0,		2.4,			0.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			10, 			15,		LOOT_POLICE,					"none", 				 "none",						"You found a Shotgun Ammo box!~n~Wow, be careful, these bullets are also known~n~as hole makers!"},
	{3016,			"Assault Ammo",			20.0,					  0.0,					0.0,					00.0,			  	  0.0,			0.0,				0.0,			(0x999999),			(0xFFFFFF),			0.0,		0.0,		-55.0,		2.4,			0.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			10, 			70,		LOOT_MILITARY,					"none", 				 "none",						"You found an Assault Rifle Ammo!~n~Dropped by Osama bin Laden!"},
	{1636,			"RPG Ammo",				0.0,					  0.0,					0.0,					00.0,			  	  0.0,			0.0,				0.0,			(0xFF0000),			(0xFFFFFF),			0.0,		0.0,		-55.0,		2.4,			0.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			10, 			10,		LOOT_NONE,						"none", 				 "none",						"You found a RPG ammo!~n~Holy fuck, even Osama would be afraid!~n~-le Osama- You said RPG o.o? AAAAH BOOOOM!"},
/*
	Clothes
		|>model<|________|>name<|____________|>rate<|___________|>effect_hunger<|______|>effect_thirst<|______|>effect_damage<|_____|>effect_sleep<|_____|>effect_temp|_____|>effect_health|_____|>color<|_______|>txd_color<|______|>txd_rx<|___|>txd_ry<|___|>txd_rz<|___|>txd_zoom<|____|>obj_rx<|___|>obj_ry<|___|>obj_rz<|___|>obj_color<|______|>stackable<|___|>max_stack<|____|>label_height<|__|>object_z_index<|_|>txr_lib<|_____________|>txr_name<|__________________|>Description<|
*/
//head
	{2052,			"Army Tommy Hat",		20.0,					  0.0,					0.0,					00.0,			  	  0.0,			0.0,				0.0,			(0x2E8B57),			(0xFFFFFF),			0.0,		0.0,		-55.0,		2.4,			0.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				1,		LOOT_CIVILIAN,					"none", 				 "none",						"You found a Tommy Hat!~n~Dropped by an american soldier!~n~Uncle sam, are you here?"},
	{2053,			"Army Jerry Hat",		20.0,					  0.0,					0.0,					00.0,			  	  0.0,			0.0,				0.0,			(0x2E8B57),			(0xFFFFFF),			0.0,		0.0,		-55.0,		2.4,			0.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				1,		LOOT_CIVILIAN,					"none", 				 "none",						"You found a Jerry Hat!~n~Dropped by an american soldier!~n~Uncle sam, are you here?"},
	{2054,			"Marine CPT Hat",		20.0,					  0.0,					0.0,					00.0,			  	  0.0,			0.0,				0.0,			(0xFFF5EE),			(0xFFFFFF),			0.0,		0.0,		-55.0,		2.4,			0.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				1,		LOOT_CIVILIAN,					"none", 				 "none",						"You found a Marine CPT Hat!~n~Be a good sailor, fool!"},
	{18636,			"Police Cap",			20.0,					  0.0,					0.0,					00.0,			  	  0.0,			0.0,				0.0,			(0x00008B),			(0xFFFFFF),			0.0,		0.0,		-55.0,		2.4,			0.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				1,		LOOT_CIVILIAN,					"none", 				 "none",						"You found a Police cap!~n~Hands up motherfucker, police here!~n~Whatever you say will be used against you~n~on the court!"},
	{18638,			"Worker Hat",			20.0,					  0.0,					0.0,					00.0,			  	  0.0,			0.0,				0.0,			(0xF0E68C),			(0xFFFFFF),			0.0,		0.0,		-55.0,		2.4,			0.0,			270.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				1,		LOOT_CIVILIAN,					"none", 				 "none",						"You found a Worket Hat!~n~Enjoy your creativity and do some special~n~crafting!"},
	{18639,			"Black Hat",			20.0,					  0.0,					0.0,					00.0,			  	  0.0,			0.0,				0.0,			(0x151515),			(0xFFFFFF),			0.0,		0.0,		-55.0,		2.4,			0.0,			270.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				1,		LOOT_CIVILIAN,					"none", 				 "none",						"You found a Black Hat!~n~A hacker hat or an evil farmer one?"},
	{18640,			"Tim Maia Hair",		20.0,					  0.0,					0.0,					00.0,			  	  0.0,			0.0,				0.0,			(0xA0522D),			(0xFFFFFF),			0.0,		0.0,		-55.0,		2.4,			0.0,			270.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				1,		LOOT_CIVILIAN,					"none", 				 "none",						"You found a Tim Maia Hair!~n~Do you know him? The brazilian singer, also~n~known as Adejair JR. R.I.P Tim Maia..."},
//body

	{19142,			"Swat Kevlar",			12.0,					  0.0,					0.0,					00.0,			  	  0.0,			0.0,				0.0,			(0x708090),			(0xFFFFFF),			0.0,		0.0,		-55.0,		2.4,			90.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				1,		LOOT_POLICE,					"none", 				 "none",						"You found a Swat Kevlar!~n~Feeling superprotected now homie?~n~This item will make you resist to some shots~n~on your chest!"},
/*	
	Special
		|>model<|________|>name<|____________|>rate<|___________|>effect_hunger<|______|>effect_thirst<|______|>effect_damage<|_____|>effect_sleep<|_____|>effect_temp|_____|>effect_health|_____|>color<|_______|>txd_color<|______|>txd_rx<|___|>txd_ry<|___|>txd_rz<|___|>txd_zoom<|____|>obj_rx<|___|>obj_ry<|___|>obj_rz<|___|>obj_color<|______|>stackable<|___|>max_stack<|____|>label_height<|__|>object_z_index<|_|>txr_lib<|_____________|>txr_name<|__________________|>Description<|
*/
	{19804,			"Padlock",				0.0,					  0.0,					0.0,					00.0,			  	  0.0,			0.0,				0.0,			(0xFFCC00),			(0xFFFFFF),			0.0,		0.0,		0.0,		2.4,			90.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				1,		LOOT_NONE,						"none", 				 "none",						"You found a Padlock!~n~God damn you're a lucky bastard!~n~What are you waiting for use it moron?~n~(~b~~h~~h~special item~w~)"},
	{1212,			"Red Dollars",			40.0,					  0.0,					0.0,					00.0,			  	  0.0,			0.0,				0.0,			(0xFF0000),			(0xFF0000),			0.0,		0.0,		0.0,		2.4,			0.0,			0.0,		0.0,		(0xFF0000),			true,			0, 					0.0,			0.0,			1, 				50,		LOOT_CIVILIAN,					"none", 				 "none",						"You found some dollars!~n~Saving some dollars you can buy things on~n~safe zones with this money."},
	{19941,			"Gold Bar",				0.0,					  0.0,					0.0,					00.0,			  	  0.0,			0.0,				0.0,			(0xFFCC00),			(0xFFFFFF),			0.0,		0.0,		0.0,		2.4,			0.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				1,		LOOT_NONE,						"none", 				 "none",						"~b~You found a gold bar!~n~I wanna be your friend, you're rich!~n~Use it to get cash!"},
	
/*
	Tools
	|>model<|________|>name<|____________|>rate<|___________|>effect_hunger<|______|>effect_thirst<|______|>effect_damage<|_____|>effect_sleep<|_____|>effect_temp|_____|>effect_health|_____|>color<|_______|>txd_color<|______|>txd_rx<|___|>txd_ry<|___|>txd_rz<|___|>txd_zoom<|____|>obj_rx<|___|>obj_ry<|___|>obj_rz<|___|>obj_color<|______|>stackable<|___|>max_stack<|____|>label_height<|__|>object_z_index<|_|>txr_lib<|_____________|>txr_name<|__________________|>Description<|
*/
	{18644,			"Screwdriver",			14.0,					  0.0,					0.0,					00.0,			  	  0.0,			0.0,				0.0,			(0xFF9933),			(0xFFFFFF),			0.0,		0.0,		0.0,		2.4,			90.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				1,		LOOT_INDUSTRIAL,					"none", 				 "none",						"You found a Screwdriver!~n~Life is full of unexpected, perhaps you ~n~need a screwdriver."},
	{19590,			"Slicing Knife",		14.0,					  0.0,					0.0,					00.0,			  	  0.0,			0.0,				0.0,			(0xFFCC99),			(0xFFFFFF),			0.0,		0.0,		0.0,		2.4,			90.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				1,		LOOT_INDUSTRIAL,					"none", 				 "none",						"You found a Slicing-Knife!~n~You can now cut items on crafting bench."},
	{19921,			"Toolbox",				3.0,					  0.0,					0.0,					00.0,			  	  0.0,			0.0,				0.0,			(0x996666),			(0xFFFFFF),			0.0,		0.0,		0.0,		2.4,			90.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				1,		LOOT_INDUSTRIAL,					"none", 				 "none",						"You found a Tool Box!~n~This box contains all the tools, split it~n~to get them, or simple use it!"},
	{18632,			"Fishing rod",			19.0,					  0.0,					0.0,					00.0,			  	  0.0,			0.0,				0.0,			(0x333366),			(0xFFFFFF),			0.0,		0.0,		0.0,		2.4,			90.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				1,		LOOT_INDUSTRIAL,					"none", 				 "none",						"You found a Fishing Rod!~n~As the saying goes, better a fish in hand~n~than two flying.~n~Wait, they fly? O.O"},
	{19627,			"Wrench",				17.0,					  0.0,					0.0,					00.0,			  	  0.0,			0.0,				0.0,			(0x666666),			(0xFFFFFF),			0.0,		0.0,		0.0,		2.4,			0.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				1,		LOOT_INDUSTRIAL,					"none", 				 "none",						"You found a Wrench!~n~Useful for repair things!"},
	{19627,			"Wheel Wrench",			16.0,					  0.0,					0.0,					00.0,			  	  0.0,			0.0,				0.0,			(0x333333),			(0xFFFFFF),			0.0,		0.0,		0.0,		2.4,			0.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				1,		LOOT_INDUSTRIAL,					"none", 				 "none",						"You found a Wheel Wrench!~n~Useful for changing tires!"},
	{18634,			"Crowbar",				16.0,					  0.0,					0.0,					00.0,			  	  0.0,			0.0,				0.0,			(0x660000),			(0xFFFFFF),			0.0,		0.0,		0.0,		2.4,			0.0,			90.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				1,		LOOT_INDUSTRIAL,					"none", 				 "none",						"You found a Crowbar!~n~You can now open vehicles gears!"},
	{18635,			"Hammer",				19.0,					  0.0,					0.0,					00.0,			  	  0.0,			0.0,				0.0,			(0xCC6666),			(0xFFFFFF),			0.0,		0.0,		0.0,		2.4,			90.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				1,		LOOT_INDUSTRIAL,					"none", 				 "none",						"You found a Hammer!~n~Huge step into the crafting life, I would~n~keep it."},
	{19631,			"Sledge hammer",		4.0,					  0.0,					0.0,					00.0,			  	  0.0,			0.0,				0.0,			(0x999999),			(0xFFFFFF),			0.0,		0.0,		0.0,		2.4,			0.0,			90.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				1,		LOOT_INDUSTRIAL,					"none", 				 "none",						"You found a Sledge Hammer!~n~Smash things never been so funny before."},
	{18641,			"Flashlight",			10.0,					  0.0,					0.0,					00.0,			  	  0.0,			0.0,				0.0,			(0xFFFF99),			(0xFFFFFF),			0.0,		0.0,		0.0,		2.4,			90.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				1,		LOOT_INDUSTRIAL,					"none", 				 "none",						"You found a Flashlight!~n~You're no longer blind anymore on the darkness."},
	{18642,			"Taser",				6.0,					  0.0,					0.0,					00.0,			  	  0.0,			0.0,				0.0,			(0x99CCFF),			(0xFFFFFF),			0.0,		0.0,		0.0,		2.4,			90.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				1,		LOOT_INDUSTRIAL,					"none", 				 "none",						"You found a Taser!~n~Why does it exists? This shit don't even works."},
	{19896,			"Box of Matches",		25.0,					  0.0,					0.0,					00.0,			  	  0.0,			0.0,				0.0,			(0xCC0000),			(0xFFFFFF),			0.0,		0.0,		0.0,		2.4,			0.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				1,		LOOT_CIVILIAN,						"none", 				 "none",						"You found a Box of Matches! Buuuuuuuuuuuuuurn bitch!"},
	{19917,			"Engine",				20.0,					  0.0,					0.0,					00.0,			  	  0.0,			0.0,				0.0,			(0x4169E1),			(0xFFFFFF),			0.0,		0.0,		0.0,		2.4,			0.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.8,			0.0,			1, 				1,		LOOT_CIVILIAN,						"none", 				 "none",						"You found a Engine!~n~Is this a v8? Doesn't matter, what really~n~matter is how does it fit on your backpack? o.O"},
	{1073,			"Tire",					20.0,					  0.0,					0.0,					00.0,			  	  0.0,			0.0,				0.0,			(0x101010),			(0xFFFFFF),			0.0,		0.0,		0.0,		2.4,			0.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.6,			0.4,			1, 				1,		LOOT_CIVILIAN,						"none", 				 "none",						"You found a Tire!~n~Roll, roll, roll like a fatty pussy."},
	{19621,			"Oil Can",				8.0,					  0.0,					0.0,					00.0,			  	  0.0,			0.0,				0.0,			(0x993300),			(0xFF9966),			0.0,		0.0,		0.0,		2.4,			0.0,			0.0,		0.0,		(0xFF9966),			false,			0, 					0.0,			0.0,			1, 				1,		LOOT_CIVILIAN,						"none", 				 "none",						"You found a Oil Can!~n~Have you ever changed your oil?~n~In a good way of course."},
	{1650,			"Gas Can",				8.0,					  0.0,					0.0,					00.0,			  	  0.0,			0.0,				0.0,			(0xCC3300),			(0xFF9966),			0.0,		0.0,		0.0,		2.4,			90.0,			0.0,		0.0,		(0xFF9966),			false,			0, 					0.0,			0.0,			1, 				1,		LOOT_CIVILIAN,						"none", 				 "none",						"You found a Gas Can!~n~Full of gasoline, it's rare nowadays."},
	{1962100,		"Empty Oil Can",		18.0,					  0.0,					0.0,					00.0,			  	  0.0,			0.0,				0.0,			(0xFF6633),			(0xFFFFFF),			0.0,		0.0,		0.0,		2.4,			0.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				1,		LOOT_CIVILIAN,						"none", 				 "none",						"You found a Oil Can!~n~Have you ever changed your oil?~n~In a good way of course."},
	{165000,		"Empty Gas Can",		18.0,					  0.0,					0.0,					00.0,			  	  0.0,			0.0,				0.0,			(0xFF9933),			(0xFFFFFF),			0.0,		0.0,		0.0,		2.4,			90.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				1,		LOOT_CIVILIAN,						"none", 				 "none",						"You found a Gas Can!~n~Full of gasoline, it's rare nowadays."},
/*
	Resources
	|>model<|________|>name<|____________|>rate<|___________|>effect_hunger<|______|>effect_thirst<|______|>effect_damage<|_____|>effect_sleep<|_____|>effect_temp|_____|>effect_health|_____|>color<|_______|>txd_color<|______|>txd_rx<|___|>txd_ry<|___|>txd_rz<|___|>txd_zoom<|____|>obj_rx<|___|>obj_ry<|___|>obj_rz<|___|>obj_color<|______|>stackable<|___|>max_stack<|____|>label_height<|__|>object_z_index<|_|>txr_lib<|_____________|>txr_name<|__________________|>Description<|
*/
	{1463,			"Wooden Planks",		10.0,					  0.0,					0.0,					00.0,			  	  0.0,			0.0,				0.0,			(0x663300),			(0xFFFFFF),			0.0,		0.0,		0.0,		2.4,			0.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.5,			0.0,			1, 				10,		LOOT_CIVILIAN,					"none", 				 "none",						"You found some Wood Planks!~n~Many things can be done with this, or maybe no..."},
	{19793,			"Wood",					15.0,					  0.0,					0.0,					00.0,			  	  0.0,			0.0,				0.0,			(0x663300),			(0xFFFFFF),			0.0,		0.0,		0.0,		2.4,			0.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				1,		LOOT_CIVILIAN,					"none", 				 "none",						"You found a Wood!~n~Does a wood need a description?~n~Well, it's just, wood..."},
	{19826,			"Metal Fragments",		2.0,					  0.0,					0.0,					00.0,			  	  0.0,			0.0,				0.0,			(0xCCCCCC),			(0xFFFFFF),			0.0,		0.0,		0.0,		2.4,			90.0,			0.0,		0.0,		(0xFFFFFF),			true,			100, 				0.0,			0.0,			1, 				5,		LOOT_INDUSTRIAL,				"none", 				 "none",						"You found some Metal Fragments!~n~Maybe one of the most important resources on~n~ the crafting."},
	{19843,			"Metal Panel",			13.0,					  0.0,					0.0,					00.0,			  	  0.0,			0.0,				0.0,			(0xCCCCCC),			(0xFFFFFF),			0.0,		0.0,		0.0,		2.4,			0.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				1,		LOOT_CIVILIAN,					"none", 				 "none",						"You found a Metal Panel!~n~Useful for crafting stuff."},
	{1577,			"Gold ore",				0.0,					  0.0,					0.0,					00.0,			  	  0.0,			0.0,				0.0,			(0xFFCC00),			(0xFFFFFF),			0.0,		0.0,		0.0,		2.4,			0.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				3,		LOOT_NONE,						"none", 				 "none",						"You found some Gold Ore!~n~Holy fuck, you're rich!~n~You can now craft gold bars, cash baby, cash!"},
	{1575,			"Metal ore",			0.0,					  0.0,					0.0,					00.0,			  	  0.0,			0.0,				0.0,			(0xCCCCCC),			(0xFFFFFF),			0.0,		0.0,		0.0,		2.4,			0.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				10,		LOOT_NONE,						"none", 				 "none",						"You found some Metal Ore!~n~You can now crash metal fragments and so on..."},
	{3929,			"Rocks",				14.0,					  0.0,					0.0,					00.0,			  	  0.0,			0.0,				0.0,			(0x444444),			(0xFFFFFF),			0.0,		0.0,		0.0,		2.4,			0.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.6,			0.0,			5, 				20,		LOOT_CIVILIAN,					"none", 				 "none",						"You found some Rocks!~n~Rocks doesn't really rocks, it sucks, cause they are~n~just rocks."},
	{19873,			"Paper",				16.0,					  0.0,					0.0,					00.0,			  	  0.0,			0.0,				0.0,			(0xFFFFFF),			(0xFFFFFF),			0.0,		0.0,		0.0,		2.4,			0.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				3,		LOOT_CIVILIAN,					"none", 				 "none",						"You found a Paper!~n~Are you a good or a bad boy?If bad, you can roll~n~some weed. Otherwise, you can craft items!"},
	{19874,			"Soap",					16.0,					  0.0,					0.0,					00.0,			  	  0.0,			0.0,				0.0,			(0xFFFFFF),			(0xFFFFFF),			0.0,		0.0,		0.0,		2.4,			0.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				1,		LOOT_CIVILIAN,					"none", 				 "none",						"You found a Soap!~n~Not so much useful, nobody takes a bath nowadays.~n~Anyways some craftings need it."},
	{2846,			"Clothes",				30.0,					  0.0,					0.0,					00.0,			  	  0.0,			0.0,				0.0,			(0xFF66FF),			(0xFFFFFF),			0.0,		0.0,		0.0,		2.4,			0.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			3, 				6,		LOOT_CIVILIAN,					"none", 				 "none",						"You found some Clothes!~n~Not for wearing, but for crafting!~n~You can craft bandages with this."},
	
/*	
	Backpacks
	|>model<|________|>name<|____________|>rate<|___________|>effect_hunger<|______|>effect_thirst<|______|>effect_damage<|_____|>effect_sleep<|_____|>effect_temp|_____|>effect_health|_____|>color<|_______|>txd_color<|______|>txd_rx<|___|>txd_ry<|___|>txd_rz<|___|>txd_zoom<|____|>obj_rx<|___|>obj_ry<|___|>obj_rz<|___|>obj_color<|______|>stackable<|___|>max_stack<|____|>label_height<|__|>object_z_index<|_|>txr_lib<|_____________|>txr_name<|__________________|>Description<|
*/
	{3026,			"Iron Backpack",		30.0,					  0.0,					0.0,					00.0,			  	  0.0,			0.0,				0.0,			(0xA9A9A9),			(0xFFFFFF),			0.0,		0.0,		0.0,		2.4,			270.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				1,		LOOT_CIVILIAN,					"none", 				 "none",						"You found a Iron Backpack!~n~Not so large, but enough to give you 10 more slots."},
	{371,			"Alice Backpack",		20.0,					  0.0,					0.0,					00.0,			  	  0.0,			0.0,				0.0,			(0xFF4500),			(0xFFFFFF),			0.0,		0.0,		0.0,		2.4,			270.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				1,		LOOT_CIVILIAN,					"none", 				 "none",						"You found a Alice Backpack!~n~Congratulations, you can now store 30 dildos on~n~ your back!"},
	{19559,			"Camping Backpack",		10.0,					  0.0,					0.0,					00.0,			  	  0.0,			0.0,				0.0,			(0x4169E1),			(0xFFFFFF),			0.0,		0.0,		0.0,		2.4,			270.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				1,		LOOT_INDUSTRIAL,				"none", 				 "none",						"You found a Camping Backpack!~n~Consider yourself a lucky man!~n~This is the largest backpack arround baby."},
/*
	Medical
	|>model<|________|>name<|____________|>rate<|___________|>effect_hunger<|______|>effect_thirst<|______|>effect_damage<|_____|>effect_sleep<|_____|>effect_temp|_____|>effect_health|_____|>color<|_______|>txd_color<|______|>txd_rx<|___|>txd_ry<|___|>txd_rz<|___|>txd_zoom<|____|>obj_rx<|___|>obj_ry<|___|>obj_rz<|___|>obj_color<|______|>stackable<|___|>max_stack<|____|>label_height<|__|>object_z_index<|_|>txr_lib<|_____________|>txr_name<|__________________|>Description<|
*/
	{11748,			"Nausea Tablets",		15.0,					  0.0,					0.0,					00.0,			  	  0.0,			0.0,				0.0,			(0x99CC99),			(0xFFFFFF),			0.0,		0.0,		0.0,		2.4,			0.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				1,		LOOT_MEDICAL, 				"none", 				 "none",						"You found some Nausea Tablets!~n~Use it to stop nausea, vomit and diarrhea."},
	{1580,			"Blood Bag",			5.0,					  0.0,					0.0,					00.0,			  	  0.0,			0.0,				0.0,			(0xCC0000),			(0xFFFFFF),			0.0,		0.0,		0.0,		2.4,			0.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				1,		LOOT_MEDICAL, 				"none", 				 "none",						"You found a Blood Bag!~n~Use it to refill your blood, it takes a while~n~Blood recover average time: 1.0/s (+skill bonus)"},
	{11747,			"Bandage",				12.0,					  0.0,					0.0,					00.0,			  	  0.0,			0.0,				0.0,			(0xCC9966),			(0xFFFFFF),			0.0,		0.0,		0.0,		2.4,			0.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				1,		LOOT_MEDICAL, 				"none", 				 "none",						"You found a Bandage!~n~Use it to stop bandage your wounds and stop your bleeding."},
	{2709,			"Painkillers",			10.0,					  0.0,					0.0,					00.0,			  	  0.0,			0.0,				0.0,			(0xFF6666),			(0xFFFFFF),			0.0,		0.0,		0.0,		2.4,			0.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				1,		LOOT_MEDICAL, 				"none", 				 "none",						"You found some Painkillers!~n~Using it, you'll no longer feel any pain homie!~n~This item cures injured bones."},
	{2891,			"Morphine Bag",			11.0,					  0.0,					0.0,					00.0,			  	  0.0,			0.0,				0.0,			(0xCCCCCC),			(0xFFFFFF),			0.0,		0.0,		0.0,		2.4,			0.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				1,		LOOT_MEDICAL, 				"none", 				 "none",						"You found a Morphine Bag!~n~Use it to cure schock.~n~Shock level average decrease: 150.0/s (+skill bonus)."},
	{11736,			"First Aid Kit",		6.0,					  0.0,					0.0,					00.0,			  	  0.0,			0.0,				0.0,			(0x336633),			(0xFFFFFF),			0.0,		0.0,		0.0,		2.4,			0.0,			0.0,		0.0,	 	(0xFFFFFF),			false,			0, 					0.0,			0.0,			1, 				1,		LOOT_MEDICAL, 				"none", 				 "none",						"You found a First Aid Kit!~n~It contains:~n~1x morphine + 1x bandage + 1x painkillers"},
	{11738,			"Medkit",				3.0,					  0.0,					0.0,					00.0,			  	  0.0,			0.0,				0.0,			(0xFF0000),			(0xFFFFFF),			0.0,		0.0,		0.0,		2.4,			0.0,			0.0,		0.0,		(0xFFFFFF),			false,			0, 					0.15,			0.0,			1, 				1,		LOOT_MEDICAL,				"none", 				 "none",						"You found a Medkit!~n~It contains:~n~1x blood bag + 1x morphine + 1x bandage~n~+ 1x painkillers + 1x Nausea Tablets"}
};




GetObjectName(modelid)
{
	new string[50];
	format(string, 50, "Empty");
	for(new o; o < sizeof(ObjectsInfo); o++)
	{
		if(ObjectsInfo[o][Object_Model] == modelid)
			format(string, 50, "%s", ObjectsInfo[o][Object_Name]);
	}	
	return string;
}

GetObjectColor(modelid)
{
	for(new o; o < sizeof(ObjectsInfo); o++)
		if(ObjectsInfo[o][Object_Model] == modelid) return ObjectsInfo[o][Object_Color];
	return 0xFFFFFF;
}

GetObjectEffects(modelid, &Float:ehunger, &Float:ethirst, &Float:edamage, &Float:eenergy, &Float:etemp, &Float:ehealth)
{
	for(new o; o < sizeof(ObjectsInfo); o++)
	{
		if(ObjectsInfo[o][Object_Model] == modelid)
		{
			ehunger = ObjectsInfo[o][Object_eHunger];
			ethirst = ObjectsInfo[o][Object_eThirst];
			edamage = ObjectsInfo[o][Object_eDamage];
			eenergy = ObjectsInfo[o][Object_eEnergy];
			etemp = ObjectsInfo[o][Object_eTemp];
			ehealth = ObjectsInfo[o][Object_eHealth];
			return 1;
		}
	}
	return 0;
}

GetObjectDescription(modelid)
{
	new string[128];
	for(new o; o < sizeof(ObjectsInfo); o++)
		if(ObjectsInfo[o][Object_Model] == modelid) format(string, 256, "%s", ObjectsInfo[o][Object_Description]);
	 
	return string;
}

GetObjectTXDInfo(modelid, &color, &Float:rx, &Float:ry, &Float:rz, &Float:zoom)
{
	for(new o; o < sizeof(ObjectsInfo); o++)
	{
		if(ObjectsInfo[o][Object_Model] == modelid)
		{
			color = ObjectsInfo[o][Object_TXD_Color];
			rx = ObjectsInfo[o][Object_TXD_rx];
			ry = ObjectsInfo[o][Object_TXD_ry];
			rz = ObjectsInfo[o][Object_TXD_rz];
			zoom = ObjectsInfo[o][Object_TXD_Zoom];
			return 1;
		}
	}
	return 0;
}

GetObjectTXRInfo(modelid, txrlib[], txrname[], &material_color)
{
	for(new o; o < sizeof(ObjectsInfo); o++)
	{
		if(ObjectsInfo[o][Object_Model] == modelid)
		{
			format(txrlib, 32, "%s", ObjectsInfo[o][Object_TXR_Lib]);
			format(txrname, 32, "%s",  ObjectsInfo[o][Object_TXR_Name]);
			material_color = ObjectsInfo[o][Object_material_color];
			return 1;
		}
	}
	return 0;
} 

stock GetItemModel(index) return ObjectsInfo[index][Object_Model];


stock bool:IsModelStackable(modelid)
{
	for(new i; i < sizeof ObjectsInfo; i++)
	{
		if(ObjectsInfo[i][Object_Model] == modelid)
			return ObjectsInfo[i][Stackable];
	}
	return false;
}

stock GetObjectMaxStack(modelid)
{
	for(new i; i < sizeof ObjectsInfo; i++)
	{
		if(ObjectsInfo[i][Object_Model] == modelid)
			return ObjectsInfo[i][Max_stack];
	}
	return 0;
}

GetObjectDropData(modelid, &Float:O_rx, &Float:O_ry, &Float:O_rz, &Float:label_height, &Float:zindex_height)
{
	for(new i; i < sizeof ObjectsInfo; i++)
	{
		if(ObjectsInfo[i][Object_Model] == modelid)
		{
			O_rx = ObjectsInfo[i][Object_rx];
			O_ry = ObjectsInfo[i][Object_ry];
			O_rz = ObjectsInfo[i][Object_rz];
			label_height = ObjectsInfo[i][Label_additional_height];
			zindex_height = ObjectsInfo[i][Object_zindex_height];
			return 1;
		}			
	}
	return 0;
}

GetObjectDropAmount(modelid, &min, &max)
{
	for(new i; i < sizeof ObjectsInfo; i++)
	{
		if(ObjectsInfo[i][Object_Model] == modelid)
		{
			min = ObjectsInfo[i][min_drop_amount];
			max = ObjectsInfo[i][max_drop_amount];
			return 1;
		}			
	}
	return 0;
}