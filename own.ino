boolean AckNack(void)
// Funzione che si mette in ascolto del messaggio di risposta dal server OWN
{
#ifdef OWN
	boolean stato = false;
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
	con = ClientOWN.connect(own_server, own_serverPort);
	delay(10);
	if (con ) {
		#ifdef DEBUGOWN
		Serial.println("Connesso al server OWN");
		#endif
		if (AckNack())	{
			stato = true;
			#ifdef DEBUGOWN
			Serial.println("Il server OWN e' pronto ci ha risposto ACK");
			#endif
		}
	}
	else
	{
		#ifdef DEBUGOWN
		Serial.println("Non sono riuscito a connettermi al server OWN");
		#endif
		OWN_Stop_Client(); // Chiudo la connessione 
	}
	return stato;
#endif
}

boolean OWN_Command_Client()
{
	#ifdef OWN
	boolean stato;
	ClientOWN.print(SOCKET_COMANDI);
	stato = AckNack();
	if (stato) {
			#ifdef DEBUGOWN
			Serial.println("Entrato in modalita' Comandi");
			// sendSyslogMessage(1, "Entrato in modalita' comandi");
			#endif
	}
	else {
			#ifdef DEBUGOWN
			Serial.println("Errore OWN ha dato NACK su comando");
			// sendSyslogMessage(1, "Errore entrando in modalita' comandi");
			#endif
		}

	return stato;
	#endif
}

void OWN_Stop_Client()
{
	ClientOWN.flush();
	ClientOWN.stop();
	#ifdef DEBUGOWN
	Serial.println("Chiudo la connessione");
	#endif
}

boolean OWN_SendData(char *OWN_Command)
//Funzione che spedisce il commando OWN
{
#ifdef OWN
	boolean ok = false;
	boolean stato = false;
	char c;
	
	if (OWN_Connect_Client()) {
	
		stato=OWN_Command_Client();
	 }
	
	if (stato) 	{
		ClientOWN.flush();
		ClientOWN.print(OWN_Command); 
		delay(100);
		if (AckNack()) {
			#ifdef DEBUGOWN
			Serial.print("Spedito correttamente il comando OWN: ");
			Serial.println(OWN_Command);
			#endif
			ok = true;
		}
		else {
			#ifdef DEBUGOWN
			Serial.println("Comando non accettato dal server OWN");
			sendSyslogMessage(1, "Comando non accettato dal server OWN");
			#endif
		}
	}
	OWN_Stop_Client();
	return ok;
#endif
}

