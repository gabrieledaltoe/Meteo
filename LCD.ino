// Scrittura su LCD dei valori rilevati

void show_lcd_values()
{
	#ifdef LCD
	lcd.setCursor(0, 0);
	lcd.print("V:");
	lcd.print(StazioneMeteo.Wind);
	lcd.setCursor(6, 0);
	lcd.print("km");
	lcd.setCursor(8, 0);
	lcd.print("T:");
	lcd.print(StazioneMeteo.TempExt);
	lcd.setCursor(15, 0);
	lcd.print("C");
	lcd.setCursor(0, 1);
	lcd.print("L:");
	lcd.print(StazioneMeteo.Lux);
	lcd.setCursor(8, 1);
	lcd.print("H:");
	lcd.print(StazioneMeteo.HumExt);
	lcd.setCursor(15, 1);
	lcd.print("%");
	#endif
}

void Init_LCD()
{
#ifdef LCD
	lcd.begin(16, 2);					// Impostiamo le colonne (16) e le righe (2) del LCD
	#ifdef DEBUGLCD
	Serial.println("Inizializzazione LCD");
	#endif
#endif
}
