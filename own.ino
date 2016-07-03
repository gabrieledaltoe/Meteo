boolean AckNack(void)
// Funzione che si mette in ascolto del messaggio di risposta dal server OWN
{
#ifdef OWN
	boolean stato = false;
	String MSG_OWN;
	int i = 0;
	char msgOWN_Ricevuto[7];
	
	if (ClientOWN.connected())           // Controlla che il client sia ancora connesso
	{
		delay(10);						// Delay in quanto puo' succedere che CliebtOWN.available sia 0 anche se in effetti e' connesso (1).
		while (ClientOWN.available())
		{
			msgOWN_Ricevuto[i] = ClientOWN.read();   // Leggo la stringa che mi ritorna il Server OWN
			i++;
		}
		if (strcmp(msgOWN_Ricevuto, ACK) == 0)	stato = true; // Se è ACK lo segnalo
	}
	
	return stato;
#endif
}

boolean OWN_Connect_Client()
{
#ifdef OWN
	boolean stato = false;
	boolean con = false;
	String MSG_OWN;
	con = ClientOWN.connect(own_server, own_serverPort);
	delay(10);
	if (con ) {
		MSG_OWN = "Connesso al server OWN";
		debug_own_message(MSG_OWN, 2);
		if (AckNack())	{
			stato = true;
			MSG_OWN = "Il server OWN e' pronto ci ha risposto ACK";
			debug_own_message(MSG_OWN, 2);
		}
	}
	else {
		MSG_OWN = "Non sono riuscito a connettermi al server OWN";
		debug_own_message(MSG_OWN, 1);
		OWN_Stop_Client(); // Chiudo la connessione 
	}
	return stato;
#endif
}

boolean OWN_Command_Client()
{
	#ifdef OWN
	boolean stato;
	String MSG_OWN;
	ClientOWN.print(SOCKET_COMANDI);
	stato = AckNack();
	if (stato) {
		MSG_OWN = "Entrato in modalita' Comandi";
		debug_own_message(MSG_OWN, 2);
	}
	else {
		MSG_OWN = "Errore OWN ha dato NACK su comando";
		debug_own_message(MSG_OWN, 1);
		}

	return stato;
	#endif
}

void OWN_Stop_Client()
{
	String MSG_OWN;
	MSG_OWN = "Chiudo la connessione";
	ClientOWN.flush();
	ClientOWN.stop();
	debug_own_message(MSG_OWN, 2);
}

boolean OWN_SendData(char *OWN_Command)
//Funzione che spedisce il commando OWN
{
#ifdef OWN
	boolean ok = false;
	boolean stato = false;
	String MSG_OWN;
	char c;
	
	if (OWN_Connect_Client()) {
	
		stato=OWN_Command_Client();
	 }
	
	if (stato) 	{
		ClientOWN.flush();
		ClientOWN.print(OWN_Command); 
		delay(100);
		if (AckNack()) {
			MSG_OWN = "Spedito correttamente il comando OWN: " + String(OWN_Command);
			debug_own_message(MSG_OWN, 2);
			ok = true;
		}
		else {
			MSG_OWN = "Comando non accettato dal server OWN";
			debug_own_message(MSG_OWN, 1);
		}
	}
	OWN_Stop_Client();
	return ok;
#endif
}

void debug_own_message(String MSG, int Syslogfacility)
{
#ifdef DEBUGOWN
	Serial.println(MSG);
#endif

#ifdef SYSLOGOWN
	sendSyslogMessage(Syslogfacility, MSG);
#endif
}