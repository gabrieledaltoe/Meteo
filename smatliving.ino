	
void SmartLivingSendData(void)
{
#ifdef SMARTLIVING
		Device.Send(String(StazioneMeteo.Wind), IDWind);
		Device.Send(String(StazioneMeteo.Lux), IDLuce);
		Device.Send(String(StazioneMeteo.TempExt), IDTemp);
		Device.Send(String(StazioneMeteo.HumExt), IDHum);
			
#endif
}

void SmartLiving_Wind()
{
#ifdef SMARTLIVING
	Device.Send(String(StazioneMeteo.Wind),IDWind );
	StazioneMeteo.WindMax = 0;	// Ripristino il valore nullo di WindMax
#endif
}

void SmartLiving_Run()
{
#ifdef SMARTLIVING
	if (millis() - DeviceCloud_Last > DeviceCloud_Update_Interval) {
		SmartLivingSendData();
		DeviceCloud_Last = millis();
		}
	Device.Process();
#endif
}

void Init_SmartLiving()
{
	String MSGSL;
	MSGSL = "Inizio Connessione con Smartliving...";
	debug_sl_message(MSGSL, 2);
	
	if (Device.Connect(&ethClient, httpServer)) {    

		Device.AddAsset(IDLuce, "LUX", "Intensita' di luce in %", false, "integer");
		Device.AddAsset(IDTemp, "Temperatura", "Temperatura Esterna", false, "number");
		Device.AddAsset(IDHum, "Umidita", "Umidita' Esterna", false, "number");
		Device.AddAsset(IDWind, "Vento", "Velocita' Vento", false, "number");
		Device.AddAsset(11, "Sala Pranzo", "Luce della Sala da Pranzo", true, "boolean");
		Device.AddAsset(12, "Binario Sogg", "Luce Binario Soggiorno", true, "boolean");
		Device.AddAsset(13, "Soppalco Ovest", "Luce del Soppalco Ovest", true, "boolean");
			
		// Ci assicuriamo che possiamo ricevere i messaggi da IOT 
		
		while (!Device.Subscribe(mqttclient))	{
			
			MSGSL = "Ritento....";
			debug_sl_message(MSGSL, 2);
		}
	}
	else {
		MSGSL = "Problemi di connessione a Smartliving....";
		debug_sl_message(MSGSL, 1);
	}

}

void callback(char* topic, byte* payload, unsigned int length)
{
	String MSGSL;
	String msgString;
	{                                                           //put this in a sub block, so any unused memory can be freed as soon as possible, required to save mem while sending data
		char message_buff[length + 1];                        //need to copy over the payload so that we can add a /0 terminator, this can then be wrapped inside a string for easy manipulation
		strncpy(message_buff, (char*)payload, length);        //copy over the data
		message_buff[length] = '\0';                      //make certain that it ends with a null           

		msgString = String(message_buff);
		msgString.toLowerCase();                  //to make certain that our comparison later on works ok (it could be that a 'True' or 'False' was sent)
	}
	int* idOut = NULL;
	{                                                       //put this in a sub block, so any unused memory can be freed as soon as possible, required to save mem while sending data
		int pinNr = Device.GetPinNr(topic, strlen(topic));

		MSGSL = "Payload: " + String(msgString) + " topic: " + String(topic) + " Pin: " + String(pinNr);
		debug_sl_message(MSGSL, 1);

		switch (pinNr)
		{
		case 11:
			if (msgString == "false") {
				OWN_SendData(OWN_Att1_OFF);
			}
			else
				if (msgString == "true") {
					OWN_SendData(OWN_Att1_OFF);
				}
			idOut = &attuatore_SmatLiving;
			break;

		case 12:
			if (msgString == "false") {
				OWN_SendData(OWN_Att2_OFF);
			}
			else
				if (msgString == "true") {
					OWN_SendData(OWN_Att2_ON);
				}
			idOut = &attuatore_SmatLiving;
			break;

		case 13:
			if (msgString == "false") {
				OWN_SendData(OWN_Att3_OFF);
			}
			else
				if (msgString == "true") {
					OWN_SendData(OWN_Att3_ON);
				}
			idOut = &attuatore_SmatLiving;
			break;
		default:
			break;
		}
	}

	// void ElaboraAttuatori();

	if (idOut != NULL)                                           //Let the iot platform know that the operation was succesful
		Device.Send(msgString, *idOut);
}

void ElaboraAttuatori()
{
	if (Att_SmartLiving.Att1[0]) {
		// C'è un cambio di stato
		if (Att_SmartLiving.Att1[1]) {
			OWN_SendData(OWN_Att1_ON);
		}
		else
		{
			OWN_SendData(OWN_Att1_OFF);
		}
		Att_SmartLiving.Att1[0] = false;
	}

	if (Att_SmartLiving.Att2[0]) {
		// C'è un cambio di stato
		if (Att_SmartLiving.Att2[1]){
		OWN_SendData(OWN_Att2_ON);
		}
		else
		{
			OWN_SendData(OWN_Att2_OFF);
		}
		Att_SmartLiving.Att2[0] = false; 
	}
	
	if (Att_SmartLiving.Att3[0]) {
		// C'è un cambio di stato
		if (Att_SmartLiving.Att3[1]) {
			OWN_SendData(OWN_Att3_ON);
		}
		else
		{
			OWN_SendData(OWN_Att3_OFF);
		}
		Att_SmartLiving.Att3[0] = false;
	}
		
}

void debug_sl_message(String MSG, int Syslogfacility)
{
#ifdef DEBUGSMARTLIVING
	Serial.println(MSG);
#endif

#ifdef SYSLOGSMARTLIVING
	sendSyslogMessage(Syslogfacility, MSG);
#endif
}