#define DaysToSeconds(%0)	(%0 * 86400)

GetDateFromTime(timestamp, string[32])
{
	new	tm <tmStamp>;
	localtime(Time:timestamp, tmStamp);
		
	strftime(string, sizeof(string), "%d/%m/%y", tmStamp); 
	return 1;
}
