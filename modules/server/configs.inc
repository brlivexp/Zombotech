//////////////////////////////////////////
#define		mysql_host		"127.0.0.1"//Não usar "localhost" para conexão!
#define		mysql_user		"root"
#define		mysql_pass		""
#define		mysql_data		"dayz"
#define		mysql_port		3306
//////////////////////////////////////////
#define		DEFAULT_OBJECT_MODEL		19475
#define 	INVALID_ITEM_ID		-1
#define 	MAX_ITEMS			50000
//////////////////////////////////////////
new MySQL;

MySQLStartConnection()
{
	MySQL = mysql_connect(mysql_host, mysql_user, mysql_data, mysql_pass, mysql_port);
	if(mysql_errno() != 0) 
	{
		print("MySQL could not connect to database, check your database and configs!");
		return SendRconCommand("exit");
	}
	else print("MySQL connection sucefully executed!");
	return 1;
}

MySQLCloseConnection()
{
	mysql_close();
	return 1;
}


