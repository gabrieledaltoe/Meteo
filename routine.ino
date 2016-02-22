// --------------------------------
// Impostazion degli ingressi
// --------------------------------
void Init_Sensor()
{	
	#ifdef WIND
	pinMode(ANEMOMETER_PIN, INPUT);
	digitalWrite(ANEMOMETER_PIN, HIGH);  // Abilita le resistenze interne di pullup
	#endif

	#ifdef RAINGAUGE
	pinMode(RAIN_GAUGE_PIN, INPUT);
	digitalWrite(RAIN_GAUGE_PIN, HIGH);  // Abilita le resistenze interne di pullup
	#endif
}

// --------------------------------
//Definizione degli Interrupt wind e RAINGAUGE
// --------------------------------
void Init_Irq()
{

#ifdef RAINGAUGE
attachInterrupt(RAIN_GAUGE_INT, rainIRQ, RISING);		// Quando si attiva l'interrupts del sensore pioggia viene richiamata la funzione rainIRQ
#endif

#ifdef WIND
attachInterrupt(ANEMOMETER_INT, windIRQ, FALLING);		// Quando si attiva l'interrupts dell'anemometro viene richiamata la funzione windIRQ
#endif

// abilitazione degli interrupts
interrupts();

}

void Init_Millis()
{
WindLast = millis();
rain_last = millis();
OWN_Last = millis();
DeviceCloud_Last = millis();
TH_Last = millis();
Debug_Last = millis();
}

void GestioneAllarmi()
{
	if (AllarmePioggia) {
		OWN_SendData(OWN_Pioggia);		// Segnalo l'inizio di pioggia
		sendSyslogMessage(1, "Inizia a Piovere");
		#ifdef DEBUGSERIAL
		Serial.println("Inizia a Piovere");
		#endif
		AllarmePioggia = false;			// Reimposto l'allarme pioggia
	}
	if ((millis() - AllarmeVentoForte) >= (WIND_FINEALLARMEVENTO * 1000 * 60)) {
		if (FlagVentoForte) {
			FlagVentoForte = false;  // Ora non c'è più vento forte
		}
	}
}
	

