//In questo file vado a definire dei parametri di come funzionerà il programma

//-------------------------------------------------------------------------------------------------
// MODALITA' DI ESECUZIONE / DEBUG / AMBIENETE PRODUZIONE O TEST
//-------------------------------------------------------------------------------------------------

#define DEVELOP			// Per cambiare DEVELOP = ARDUINO Sviluppo, altrimenti Produzione
// #define DEBUGRUN			// Predispone ambiente di test su arduinio di produzione con il Debug
//___________________________________________________________________________________________________________

#ifdef DEVELOP
#define DEBUGSERIAL		// Esegue il debug su seriale dei Dati
#define OWN				// Abilita la funzionalita OWN 
#define DEBUGOWN
#else 
#define UNDEBUG			// Disattiva le opzioni di debug
#define OWN
#endif

#ifdef DEBUGRUN
#undef UNDEBUG	
#define OWN
#define DEBUGSERIAL
#define DEBUGWIND		
#define DEBUGLIGHT
#define DEBUGOWN
#endif

//-------------------------------------------------------------------------------------------------
// SENSORI / FUNZIONI	ATTIVI
//-------------------------------------------------------------------------------------------------
#define SERIAL			// Attiva la seriale (per il debug su seriale)
#define LCD				// Attiva LCD a bordo dell'Arduino
#define LIGHT			// Attiva il sensore luce
// #define MAILLIGHT   // Usato per comuncare via mail il cambio di stato del crepuscolare
#define WIND			// Attiva il sensore velocita' e direzione Vento
#define RAINGAUGE	// Attiva il sensore pioggia a bilancere
// #define CISTERNA		// Attiva il sensore di profondità della Cisterna
#define TH				// Abilita la funzione Temperatura e Umidita
#define ETHERNET		// Abilita la Ethernet Shield di Arduino
#define SMARTLIVING		// Abilita la funzionalita SmartLiving
// #define SYSLOG			// Abilita il syslog
#ifdef DEVELOP
#undef EMAIL
#else 
#define EMAIL			// Abilita la funziona email su allarmi
#endif

#ifndef ETHERNET		// Se non c'e' la Ethernet non ci possono essere TIME, DEVICEHUB, TIME, OWN e Syslog
#undef DEVICEHUB
#undef TIME
#undef OWN
#undef SYSLOG
#undef EMAIL
#endif

// ------------------------------------------------------------------------------------------------ -
// OPZIONI DI DEBUG
//-------------------------------------------------------------------------------------------------

// Opzioni singole di DEBUG
#define DEBUGDELAY   2			// Ogni quanti secondi aggiorna i dati del debug su seriale
#define DEBUGLCD				// Mostra i msg di init dell'LCD
#define DEBUGLIGHT				// Mostra i dati relativi al sensore luce
#define DEBUGWIND				// Mostra i dati relativi al sensore velocita' e direzione Vento
#define DEBUGRAINGAUGE			// Mostra i dati relativi al sensore pioggia a bilancere
#define DEBUGCISTERNA			// Mostra i dati relativi alla profondità della Cisterna
#define DEBUGTH					// Mostra i dati relativi al sensore TH
#define DEBUGETHERNET			// Mostra i mssaggi relativi alla Ethernet Shield di Arduino
#define DEBUGSMARTLIVING		// Mostra i dati relativi alla pubblicazione dati su Smartliving
#define DEBUGTIME				// Mostra i mssaggi relativi a Time
#define DEBUGOWN				// Mostra i mssaggi relativi a OWN
#define DEBUGEMAIL				// Mostra i messaggi relativi a Email

#ifdef UNDEBUG
#undef DEBUGSERIAL	
#undef DEBUGLCD			
#undef DEBUGWIND		
#undef DEBUGRAINGAUGE	
#undef DEBUGLIGHT		
#undef DEBUGETHERNET
// #undef DEBUGDEVICEHUB	
#undef DEBUGOWN				
#undef DEBUGTIME	
#undef DEBUGEMAIL
#endif

#ifndef ETHERNET
#undef DEBUGETHERNET
#undef DEBUGTIME
#undef DEBUGOWN
#undef DEBUGDEVICEHUB
#undef DEBUGEMAIL
#endif

//--------------------------------------------------------------------------------------------------
// IMPOSTAZIONI INDIRIZZO IP
//--------------------------------------------------------------------------------------------------
#define IPSTATIC true								// Indica se si vuole usare l'IP Statico per Arduino altrimenti viene richiesto via DHCP

#ifdef DEVELOP
#define MAC_ARDUINO 0x90,0xA2,0xDA,0x0F,0xAC,0x6E	// MAC Address Arduino Mega Test
#define IP_ARDUINO 10,20,2,9						// IP Arduino
#else
#define MAC_ARDUINO 0x90,0xA2,0xDA,0x0F,0x66,0x79	// MAC Address Arduino Mega Produzione
#define IP_ARDUINO 10,20,2,8						// IP Arduino
#endif

//--------------------------------------------------------------------------------------------------
// ALTRE IMPOSTAZIONI COMUNI
//--------------------------------------------------------------------------------------------------
#define GW_ARDUINO 10,20,1,254			// GW Arduino
#define MASK_ARDUINO 255,255,0,0		// Subnetmask Arduino
#define DNS_ARDUINO 8,8,8,8				// DNS di Arduino
#define TIMESERVER 193,204,114,105		// Indirizzo IP del Time Server (ntp.ien.it)

//-------------------------------------------------------------------------------------------------
// OWN
//-------------------------------------------------------------------------------------------------
#define OWN_SERVER 10,20,9,2			// Indirizzo IP del gateway OWN - SCS -> Ora MH200N
#define OWN_PORT 20000					// Porta TCP di collegamento
#define SOCKET_COMANDI  "*99*0##"	
#define SOCKET_MONITOR  "*99*1##"
#define OWN_TIMEOUT 30						// Timeout in secondi dal OWN (passati i quali se non vengono impartiti commandi viene disconnessa la sessione)

//-------------------------------------------------------------------------------------------------
// LCD
//-------------------------------------------------------------------------------------------------
#define LCD_DB4 44						// collegamemto LCD DB4 (11)   -> D44 Arduino
#define LCD_DB5 45						// collegamemto LCD DB5 (12)   -> D45 Arduino
#define LCD_DB6 46						// collegamemto LCD DB6 (13)   -> D46 Arduino
#define LCD_DB7 47						// collegamemto LCD DB7 (14)   -> D47 Arduino
#define LCD_EN 48						// collegamemto LCD Enable (6) -> D48 Arduino
#define LCD_RS 49						// collegamento LCD RS (4)     -> D49 Arduino

//-------------------------------------------------------------------------------------------------
// SMARTLIVING
//-------------------------------------------------------------------------------------------------
// Se SMARTLIVING_FIRST_TIME e' definito mi crea/aggiorna i vari asset in Smartliving, altrimenti aggiorna solo i valori ma non aggiorna gli asset
#define SMARTLIVING_FIRST_TIME 
#define MQTTSERVER "broker.smartliving.io"	
#define HTTPSERVER "api.smartliving.io"
#ifdef DEVELOP
#define DEVICEID "ng5D4ukwKbiDJBzZca4V271"
#define CLIENTID "gabrieledaltoe"
#define CLIENTKEY "bdlpuwvqm5e"
#else
#define DEVICEID "9ZOjNEIWwDG8HEk51ONWTnH"
#define CLIENTID "gabrieledaltoe"
#define CLIENTKEY "bdlpuwvqm5e"
#endif

#define MQTTUPDATE 30		// Tempo di Aggiornameto dei valori verso smartliving espesso in secondi

#define IDLuce	0			// Primo Sensore in Smartliving
#define IDTemp	1			// Secondo Sensore in Smartliving
#define IDHum	2			// Terzo Sensore in Smartliving
#define IDWind  3			// Quarto Sensore in Smartliving

#define RAIN_FACTOR 0.2794				// Ogni "bilanciata" equivale a circa 0,3 mm di pioggia caduta  -> dopo 10 bilanciate si ha circa 3 mm caduti di pioggia
#define RAINGAUGE_SAMPLERATE 600 		// Secondi per la campionatura del pluviometro (10 minuti)

#define SOGLIAMAXVENTO2	36				// Soglia velocita' vento in Km/h oltre la quale le tende devono chiudersi
#define SOGLIAMAXVENTO1	30				// Soglia velocita' vento in Km/h oltre la quale il tendone deve chiudersi

#define WIND_FACTOR 5.4					// Dalle specifiche dell'anemometro: Se il vento in 1 secondo fa compiere all'anemometro 1 giro (1Hz) -> allora il vento soffia a 5.4 Km/h
#define WIND_SAMPLERATE 2				// Secondi per la campionatura della velocita' del Vento
#define WIND_FINEALLARMEVENTO 15		// Tempo in Minuti per resettare l'allarme Vento

#define TH_SAMPLERATE 30				// Ogni XX Secondi vado a misurare la sonda TH

#ifdef DEVELOP	
#define LIGHT_SAMPLERATE 10	
#else
#define LIGHT_SAMPLERATE 10				// Secondi per la campionatura dell'intensita di luce
#endif
#define BUIO 44							// Intensita' Luce che definisce il tramonto

#define TIMEZONEOFFSET 3600				// Offset Timezone in secondi (+1 GMT) in secondi
#define NTPSYNCTIME 3600				// Frequenza di aggiornamento dell'ora in secondi

#define SMTP_Wait 1000					// Tempo da aspettare per ricevere la risposta
#define SMTP_SERVER "smtp.sistemaict.com"		// Server di posta per l'invio dell'email (avviene sempre su porta 25)
#define SMTP_SERVENNAME "smtp.sistemaict.com"	// Nome server da passare nella comunicazione EHLO
#define SMTP_USERNAME "c3lzYWxlcnRAc2lzdGVtYWljdC5jb20="	// Username in base64 usato per autenticazione vedi http://www.motobit.com/util/base64-decoder-encoder.asp
#define SMTP_PASSWORD "aWN0c3lzYWxlcnQ="			// Password in base 64 usato per autenticazione vedi http://www.motobit.com/util/base64-decoder-encoder.asp
#define SMTP_SENDER "sysalert@sistemaict.com" // Mittente email
#define SMTP_RECIPIENT "sys@sistemaict.com"	 // Destianatrio email

#define SYSLOGSERVER 10,20,1,10			// Definisce il syslog server
#define SYSLOGPORT 514					// Porta del syslogserver
#define SYSLOGLOCALPORT 8889			// Porta locale di Arduino che comunica con il syslogserver

//-------------------------------------------------------------------------------------------------
// INTERRUPTS
//--------------------------------------------------------------------------------------------------
#define ANEMOMETER_INT 1			//Interrupt 1 assiciato all'anemometro
#define RAIN_GAUGE_INT 2			//Interrupt 2 associato al pluviometro

// -------------------------------------------------------------------------------------------------
// I/O DIGITALI
//--------------------------------------------------------------------------------------------------
#define RAIN_GAUGE_PIN 2			// Pin2 digitale connesso al pluviometro a bilancere
#define ANEMOMETER_PIN 3            // Pin3 digitale connesso all'anemometro

//-------------------------------------------------------------------------------------------------
// I/O ANALOGICI
//-------------------------------------------------------------------------------------------------
#define LIGHT_PIN 0					// PIN0 Analogico connesso al sensore luce
#define WIND_VANE 1					// PIN1 Analogico connesso al sensore direzione vento
#define VASCA_PIN 7					// Connesso al sensore ultrasuoni (uscita analogica)

#define AM235CLOCK  21	            // Connesso WHITE to i2c clock (SCL)
#define AM2315DATA  20	            // Connesso YELLOW to i2c data (SDA)
// Connesso RED of the AM2315 sensor to 5.0V
// Connesso BLACK of the AM2315 sensor to GND

