	
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
	{                                                            //put this in a sub block, so any unused memory can be freed as soon as possible, required to save mem while sending data
		char message_buff[length + 1];                        //need to copy over the payload so that we can add a /0 terminator, this can then be wrapped inside a string for easy manipulation.
		strncpy(message_buff, (char*)payload, length);        //copy over the data
		message_buff[length] = '\0';                      //make certain that it ends with a null           

		msgString = String(message_buff);
		msgString.toLowerCase();                  //to make certain that our comparison later on works ok (it could be that a 'True' or 'False' was sent)
	}
	char* idOut = NULL;
	{                                                       //put this in a sub block, so any unused memory can be freed as soon as possible, required to save mem while sending data
		int topicLength = strlen(topic);

		Serial.print("Payload: ");                            //show some debugging.
		Serial.println(msgString);
		Serial.print("topic: ");
		Serial.println(topic);

	}
	if (idOut != NULL)                //also let the iot platform know that the operation was succesful: give it some feedback. This also allows the iot to update the GUI's correctly & run scenarios.
		Device.Send(msgString, *idOut);
}
