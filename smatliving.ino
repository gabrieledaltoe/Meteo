	
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
	#ifdef DEBUGSMARTLIVING		
	Serial.println("\nInizio Connessione con Smartliving...");
	#endif
	if (Device.Connect(&ethClient, httpServer)) {    //Mi connetto a Smartliving.
		#ifdef SMARTLIVING_FIRST_TIME			// Attivo solo se si deve creare gli asset la prima volta....
		Device.AddAsset(IDLuce, "LUX", "Intensita' di luce in %", false, "integer");
		Device.AddAsset(IDTemp, "Temperatura", "Temperatura Esterna", false, "number");
		Device.AddAsset(IDHum, "Umidita", "Umidita' Esterna", false, "number");
		Device.AddAsset(IDWind, "Vento", "Velocita' Vento", false, "number");
		Device.AddAsset(11, "Sala Pranzo", "Luce della Sala da Pranzo", true, "boolean");
		Device.AddAsset(12, "Binario Sogg", "Luce Binario Soggiorno", true, "boolean");
		Device.AddAsset(13, "Soppalco Ovest", "Luce del Soppalco Ovest", true, "boolean");
		while (!Device.Subscribe(mqttclient))	{// Ci assicuriamo che possiamo ricevere i messaggi da IOT 
		#ifdef DEBUGSMARTLIVING	
			Serial.println("retrying");
		#endif
		}
		#endif	
		}
	else {
		#ifdef DEBUGSMARTLIVING	
		Serial.println("Problemi di connessione a Smartliving....");
		#endif
	}

}

void callback(char* topic, byte* payload, unsigned int length)
{
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

		#ifdef DEBUGSMARTLIVING
		Serial.print("Payload: ");                            //show some debugging
		Serial.println(msgString);
		Serial.print("topic: ");
		Serial.println(topic);
		Serial.print("Pin: ");
		Serial.println(pinNr);
		#endif

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