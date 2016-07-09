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
		debug_light_message("INIT Light: Appuro che e' buio e lo segnalo",6);
		}
	else {
		OWN_SendData(OWN_CrepuscolareOFF);
		CrepuscolareON = 0;
		debug_light_message("INIT Light: Appuro che e' chiaro e lo segnalo",6);
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
	String msg;
	int luce = (int)((1023.0 - (float)analogRead(LIGHT_PIN)) / 10.23);
	if (luce != StazioneMeteo.Lux) { // Considero solo i cambiamenti di luce, altrimenti non faccio nulla
		#ifdef DEBUGLIGHT
		msg = "Luce Attuale: " + String(luce) + " Luce Precedente: " + String(StazioneMeteo.Lux);
		Serial.println(msg);
		#endif	
		StazioneMeteo.Lux = luce;         // Luce in percentuale (0-100) percento
		msg = msg = "Luce " + String(StazioneMeteo.Lux);
		debug_light_message(msg, 6);
	}
}

void check_light()
{
	if ((StazioneMeteo.Lux <= BUIO) && (!CrepuscolareON)) {
		OWN_SendData(OWN_CrepuscolareON);
		CrepuscolareON = true;
		String msg = "Passaggio da Luce a Buio";
		debug_light_message("Passaggio da Luce a Buio",6);
		}

	if ((StazioneMeteo.Lux > BUIO) && (CrepuscolareON)) {
		OWN_SendData(OWN_CrepuscolareOFF);
		CrepuscolareON = 0;
		String msg = "Passaggio da Buio a Luce";
		debug_light_message("Passaggio da Luce a Buio", 6);
		}
}

void debug_light_message(String MSG, int Syslogfacility)
{
#ifdef DEBUG_LIGHT
	Serial.println(MSG);
#endif

#ifdef SYSLOGLIGHT
	sendSyslogMessage(Syslogfacility, MSG);
#endif

#ifdef MAIL_LIGHT
	SendMail("Crepuscolare", MSG);
#endif
}