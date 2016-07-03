void Init_light()
{
	StazioneMeteo.Lux = (int)((1023.0 - (float)(analogRead(LIGHT_PIN))) / 10.23);         // Luce in percentuale (0-100) percento

	#ifdef DEBUGLIGHT
	Serial.print("INIT - Luce : ");
	Serial.println(StazioneMeteo.Lux);
	#endif

	if (StazioneMeteo.Lux <= BUIO) 	{
		OWN_SendData(OWN_CrepuscolareON);
		CrepuscolareON = true;
		#ifdef DEBUGLIGHT
		Serial.println("INIT Light: Imposto il crepuscolare a 1");
		#endif
		sendSyslogMessage(1, "INIT Light: Appuro che e' buio e lo segnalo");
		}
	else {
		OWN_SendData(OWN_CrepuscolareOFF);
		CrepuscolareON = 0;
		#ifdef DEBUGLIGHT
		Serial.println("INIT Light: Imposto il crepuscolare a 0");
		#endif
		sendSyslogMessage(1, "INIT Light: Appuro che e' chiaro e lo segnalo");
		}
}

void get_light()
{
	if ((millis() - Light_Last) >= Light_rate)
	{
		light_refresh();
		Light_Last = millis();
		check_light();				// Verifica lo stato della luce
	}
}

void light_refresh()
{
int luce = (int)((1023.0 - (float)analogRead(LIGHT_PIN)) / 10.23);
if (luce != StazioneMeteo.Lux) { // Considero solo i cambiamenti di luce, altrimenti non faccio nulla
	#ifdef DEBUGLIGHT
	Serial.print("Luce Attuale: ");
	Serial.print(luce);
	Serial.print(" Luce Precedente: ");
	Serial.println(StazioneMeteo.Lux);
	#endif	
	StazioneMeteo.Lux = luce;         // Luce in percentuale (0-100) percento
	#ifdef SYSLOGLIGHT
	String syslogstring;
	char logluce[5];
	dtostrf(StazioneMeteo.Lux, 2, 1, logluce);
	syslogstring = "Luce ";
	syslogstring += logluce;
	sendSyslogMessage(1, syslogstring);
	#endif
	}
}

void check_light()
{
	if ((StazioneMeteo.Lux <= BUIO) && (!CrepuscolareON)) {
		OWN_SendData(OWN_CrepuscolareON);
		CrepuscolareON = true;
		sendSyslogMessage(1, "Passaggio da Luce a Buio");
		#ifdef MAILLIGHT
		SendMail("Crepuscolare", "Crepuscolare ON");
		#endif
		#ifdef DEBUGLIGHT
		Serial.println("Dico che e' Buio");
		#endif
		}

	if ((StazioneMeteo.Lux > BUIO) && (CrepuscolareON)) {
		OWN_SendData(OWN_CrepuscolareOFF);
		CrepuscolareON = 0;
		sendSyslogMessage(1, "Passaggio da Buio a Luce");
		#ifdef MAILLIGHT
		SendMail("Crepuscolare", "Crepuscolare OFF");
		#endif
		#ifdef DEBUGLIGHT
		Serial.println("Dico che c'e' Luce");
		#endif
		}
}

