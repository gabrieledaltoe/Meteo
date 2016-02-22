void Init_Syslog()
{	
#ifdef SYSLOG
	SyslogUdp.begin(SYSLOGLOCALPORT);
	#ifdef SERIAL
	Serial.println("Inizializzazione Syslog");
	#endif
#endif
}

void sendSyslogMessage(int severity, String message)
{
#ifdef SYSLOG
	/*
	0 Emergency: system is unusable
	1 Alert: action must be taken immediately
	2 Critical: critical conditions
	3 Error: error conditions
	4 Warning: warning conditions
	5 Notice: normal but significant condition
	6 Informational: informational messages

	Only severity levels 0, 1, and 2 will trigger an email alert
	*/

	byte pri = (32 + severity);
	String priString = String(pri, DEC);
	String buffer = "<" + priString + ">" + "Arduino Weather - " + message;
	int bufferLength = buffer.length();
	char char1[bufferLength + 1];
	for (int i = 0; i<bufferLength; i++)
	{
		char1[i] = buffer.charAt(i);
	}

	char1[bufferLength] = '\0';
	SyslogUdp.beginPacket(syslogServer, SYSLOGPORT);
	SyslogUdp.write(char1);
	SyslogUdp.endPacket(); //this is slow 
#endif
}
