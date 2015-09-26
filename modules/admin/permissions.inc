enum permissions
{
	admlevel,
	command[32],
	rule_description[64]
}

new AdminPermissions[][permissions] = 
{
	{4, "admins", "This command allow you to see all online admins"},
	{6, "adminlist", "This command allow you to see all server admins"},
	{6, "setlevel", "This command allow you to set admins"}
};

IsValidRule(duty, rule[])
{
	for(new c; c < sizeof AdminPermissions; c++)
		if(!strcmp(rule, AdminPermissions[c][command]) && duty >= AdminPermissions[c][admlevel]) return true;
	return false;
}