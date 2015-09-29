#define sprintf(%1) \
		(format(szStrsPrintf, 1024, %1),szStrsPrintf)

#define db_get_field_float(%0,%1) \
        (db_get_field_assoc(%0,%1,szStrsPrintf,1024),floatstr(szStrsPrintf))


#define db_get_field_val(%0,%1) \
        (db_get_field_assoc(%0,%1,szStrsPrintf,1024),strval(szStrsPrintf))


stock token_by_delim(const string[], return_str[], delim, start_index)
{
	new x=0;
	while(string[start_index] != EOS && string[start_index] != delim) {
	    return_str[x] = string[start_index];
	    x++;
	    start_index++;
	}
	return_str[x] = EOS;
	if(string[start_index] == EOS) start_index = (-1);
	return start_index;
}


#define MAX_INI_ENTRY_TEXT 80

stock DB_Escape(text[])
{
	new
		ret[MAX_INI_ENTRY_TEXT * 2],
		ch,
		i,
		j;
	while ((ch = text[i++]) && j < sizeof (ret))
	{
		if (ch == '\'')
		{
			if (j < sizeof (ret) - 2)
			{
				ret[j++] = '\'';
				ret[j++] = '\'';
			}
		}
		else if (j < sizeof (ret))
		{
			ret[j++] = ch;
		}
		else
		{
			j++;
		}
	}
	ret[sizeof (ret) - 1] = '\0';
	return ret;
}
