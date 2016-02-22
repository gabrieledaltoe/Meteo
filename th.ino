void get_th()

{
	if ((millis() - TH_Last) > TH_Range) {
		refresh_th();
		TH_Last = millis();
	}
}

void refresh_th()
{
// Misura i valori della sonda TH
#ifdef TH														
am2315OK = am2315.begin();
if (am2315OK) {
	StazioneMeteo.HumExt = am2315.readHumidity();
	delay(500);
	StazioneMeteo.TempExt = am2315.readTemperature();
	#ifdef DEBUGTH
	Serial.print("T = ");
	Serial.print(StazioneMeteo.TempExt);
	Serial.print(" Hum = ");
	Serial.println(StazioneMeteo.HumExt);
	#endif
}
else {
	#ifdef DEBUGTH
	Serial.println("Sensor not found, check wiring & pullups!");
	#endif
}

#endif
}