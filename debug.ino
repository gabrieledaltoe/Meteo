void Debug_serial()
{
	if ((millis() - Debug_Last) >= Debug_Range)
	{
		Debug_refresh();
		Debug_Last = millis();
	}
}

// Serve a stampare sul monitor seriale i valori dei vari sensori
void Debug_refresh()
{
	#ifdef DEBUGSERIAL
	Serial.print("contatti: ");
	Serial.print(anem_count);
	Serial.print(" Velocita' Vento: ");
	Serial.print(StazioneMeteo.Wind);
	Serial.print(" Km/h");
	Serial.print(" LUX: ");
	Serial.print(StazioneMeteo.Lux);
	#ifdef TH
	if (am2315OK) {
		Serial.print(" Umidita' ");
		Serial.print(StazioneMeteo.HumExt);
		Serial.print(" Temp: ");
		Serial.print(StazioneMeteo.TempExt);
	}
	else {
		Serial.println("Sensor not found, check wiring & pullups!");
	}
	#endif
	#ifdef RAINGAUGE
	Serial.print(" Pioggia: ");
	Serial.print(StazioneMeteo.Rain_rate);
	Serial.print(" Raincount: ");
	Serial.print(rain_count);
	#endif
	#ifdef CISTERNA
	Serial.print(" Cisterna: ");
	Serial.print(StazioneMeteo.Vasca);
	#endif
	Serial.println(" ");
	#endif
}

