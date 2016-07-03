void windIRQ() {
#ifdef WIND
	noInterrupts();
	unsigned long now = micros();
	if ((now - anem_last) > 500) { // Filtro per togliere i glitch
		anem_count++;
		anem_last = now;
	}
	interrupts();
#endif
}

float getUnitWind()
{
#ifdef WIND
	unsigned long reading = anem_count;
	anem_count = 0;
	return (WIND_FACTOR*reading) / (WIND_SAMPLERATE);
#endif
}

void get_WindSpeed()
{
	// SOGLIAVENTO2 > SOGLIAVENTO1 36Km e 30Km
#ifdef WIND
	boolean flag = true;
	if ((millis() - WindLast) >= (WIND_SAMPLERATE*1000)) {
		StazioneMeteo.Wind = getUnitWind();
		WindLast = millis();
		if (StazioneMeteo.Wind >= SOGLIAMAXVENTO2) {
			SmartLiving_Wind();							// Pubblico il valore in SmartLiving
			StazioneMeteo.WindMax = StazioneMeteo.Wind;	// Mi prendo nota del vento più forte (verrà resettato quando effettuerò la pubblicazione di tutti i valori in Devicehub)
			flag = false;								// Non faccio eseguire il blocco che arriva dopo
			AllarmeVento(2);							// Procedo a segnalare il vento forte
		}
		if ((StazioneMeteo.Wind >= SOGLIAMAXVENTO1) && flag) {
			AllarmeVento(1);				// Procedo a segnalare il vento forte per il tendone
			SmartLiving_Wind();				// Pubblico il valore in DeviceHUB
			}
	}
#endif
}

void AllarmeVento(int i)	// Funzione che segnala il vento all'impianto domotico e che manda email
{
#ifdef WIND
	if (!FlagVentoForte) {
		if (i == 2) {
			OWN_SendData(OWN_Vento2);		// Segnalo il vento forte all'impianto domotico
			AllarmeVentoForte = millis();   // Prendo nota quando succede
			FlagVentoForte = true;			// Flag per dire che è avvenuto vento forte
			EmailWind();					// Segnalo con Email il vento forte
		}
		if (i == 1) {
			OWN_SendData(OWN_Vento1);		// Faccio abbassare il tendone delle camere
		}
	}
#endif
}

void EmailWind(void)
{
#ifdef WIND
	String msg;
	String subject;
	subject = "Allarme Vento";
	msg = "Vento Forte Valore: ";
	msg += String(StazioneMeteo.Wind);
	msg += " Km/h";
	SendMail(subject, msg);			// Mando una email
	sendSyslogMessage(1, msg);		// Segnalo al syslog il fento forte
	#ifdef DEBUGSERIAL
	Serial.println("Vento Forte");
	#endif
#endif
}