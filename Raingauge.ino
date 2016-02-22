void rainIRQ()
{
#ifdef RAINGAUGE
	noInterrupts();
	unsigned long now = micros();
	if (now - rain_last > 600) {  // Escludo i Glitch
		rain_count++;
		rain_last = now;
	}
	interrupts();
#endif
}


float getUnitRain()
{
#ifdef RAINGAUGE
	unsigned long reading = rain_count;
	rain_count = 0;
	float unit_rain = 0;
	if (reading > 0) {
		unit_rain = reading*RAIN_FACTOR;
	}
	return unit_rain;
#endif
}

void get_Raingauge()
{
#ifdef RAINGAUGE
	if ((rain_count) > 1 && (rain_count<4) && (StazioneMeteo.Rain_rate = 0))   {		// Sta iniziando a gocciolare
		AllarmePioggia = true;															// Segnalo l'allarme
	}
	
	if ((millis() - rain_last) >= (RAINGAUGE_SAMPLERATE * 1000)) {  // Aspetto il tempo di campionatura
		StazioneMeteo.Rain_rate = getUnitRain();
		rain_last = millis();
	}
#endif
}

void EmailRain(void)
{
#ifdef RAINGAUGE
	String msg;
	String subject;
	subject = "Piove";
	msg = "Rilevati: ";
	msg += String(StazioneMeteo.Rain_rate);
	msg += " mm/q";
	SendMail(subject, msg);			// Mando una email
	sendSyslogMessage(1, msg);		// Segnalo al syslog la pioggia
#ifdef DEBUGSERIAL
	Serial.println("Piove..");
#endif
#endif 
}

