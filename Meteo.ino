//-------------------------------------------------------------------------------------------------
// INCLUDE FILES
//-------------------------------------------------------------------------------------------------

#include <LiquidCrystal.h>
#include <Wire.h>
#include <SPI.h>
#include <Ethernet.h>
#include <Adafruit_AM2315.h>
#include "datatypes.h"
#include <Time.h>
#include <EthernetUdp.h>
#include <PubSubClient.h>
#include <ATT_IOT.h>
#include "definizioni.h"
#include "GlobalVar.h"

// -------------------------------------------------------------------------
// NOTA: ANDARE IN definizioni.h PER DEFINIRE IL COMPORTAMENTO DEL PROGRAMMA
// -------------------------------------------------------------------------

// --------------------------------
// SETUP
// --------------------------------
void setup() 
{
	#ifdef SERIAL
	Serial.begin(38400);
	#endif

	Init_LCD();			//Inizializzo LCD
		
	if (Init_Ethernet())  {  // Se la scheda di rete e' OK; 
		Init_Syslog();
	}
	sendSyslogMessage(1, "Boot Init");
	Init_Sensor();		// Imposto gli ingressi dei sensori Rain e Wind
	Init_Irq();		    // Imposto gli IRQ dei sensori
	Init_Millis();		// Inizilizzo la gestione delle schedulazioni
	Init_light();		// Inizializzo Light
	refresh_th();		// Recuperp i valori dalla sonda TH
	Init_SmartLiving();	// Inizializzo Smartliving
	sendSyslogMessage(1, "Boot complete");
}

// --------------------------------
// MAIN
// --------------------------------
void loop()
{
	get_WindSpeed();							// Legge la velocita' del vento e controlla il superamento del limite
	get_Raingauge();							// Legge i valori del pluviometro
	get_light();								// Legge l'intensita' di luce in %
	get_th();									// Legge la sonda TH
	get_vasca();								// Legge il volume di acqua nelle vasche
	show_lcd_values();							// Aggiorna i dati nel display LCD 
	SmartLiving_Run();							// Gestisce la pubblicazioni dei dati su Smartliving
	GestioneAllarmi();							// Gestione degli allarmi
	Debug_serial();								// Mando nella console seriale i valori
}




