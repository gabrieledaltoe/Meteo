//-------------------------------------------------------------------------------------------------
// PARAMETRI SCHEDA DI RETE
//-------------------------------------------------------------------------------------------------
boolean ipstatico = true;								// IP Arduino statico
byte mac[] = { MAC_ARDUINO };							// Mac Address
byte ip[] = { IP_ARDUINO };								// static ip of Arduino
byte gateway[] = { GW_ARDUINO };						// gateway address
byte subnet[] = { MASK_ARDUINO };						// subnet mask
byte dnsip[] = { DNS_ARDUINO };							// DNS IP

//-------------------------------------------------------------------------------------------------
// SMTP
//-------------------------------------------------------------------------------------------------
EthernetClient SmtpClient;
String SMTPServerResponse = "";
char SMTP_Server[] = SMTP_SERVER;
String ServerName = SMTP_SERVENNAME;
String UserName64 = SMTP_USERNAME;
String Password64 = SMTP_PASSWORD;
String Sender = SMTP_SENDER;
String Recipient = SMTP_RECIPIENT;
String Subject;
String Body;

//-------------------------------------------------------------------------------------------------
// Inizializzazione di SmartLiving
// 
//-------------------------------------------------------------------------------------------------
// Se SMARTLIVING_FIRST_TIME e' definito mi crea/aggiorna i vari asset in Smartliving, altrimenti aggiorna solo i valori ma non aggiorna gli asset
// #define SMARTLIVING_FIRST_TIME 
char mqttServer[] = MQTTSERVER;
char httpServer[] = HTTPSERVER;
boolean DeviceCloud_Conn = false;
EthernetClient ethClient;
void callback(char* topic, byte* payload, unsigned int length);
PubSubClient mqttclient(mqttServer, 1883, callback, ethClient);		// Istanzia un client Etherenet per SMARTLIVING
ATTDevice Device(DEVICEID, CLIENTID, CLIENTKEY);					// Crea l'oggettp per essere gestito da SMARTLIVING
unsigned long DeviceCloud_Last = 0;									// Ultima volta che abbiamo contattato il server SMARTLIVING in msec
int attuatore_SmatLiving;											// usato per capire che attuatore è stato premuto
Attuatori Att_SmartLiving;	

//-------------------------------------------------------------------------------------------------
// OWN
//-------------------------------------------------------------------------------------------------
char OWN_Vento2[] = "*1*15*0513##";			// Commando OWN per segnalare che c'e' vento forte (A=5 PL=13) per 5 Min
char OWN_Vento1[] = "*2*2*0713##";			// Comando OWN per far alzare la Tenda Sole delle Camere
char OWN_Pioggia[] = "*1*15*0514##";		// Commando OWN per segnalare che sta piovendo (A=5 PL=14) per 5 Min
#ifdef DEVELOP
char OWN_CrepuscolareON[] = "*1*1*61##";	// Commando OWN per segnalare che e' buio (A=5 PL=12)
char OWN_CrepuscolareOFF[] = "*1*0*61##";	// Commando OWN per segnalare che non e' buio
#else 
char OWN_CrepuscolareON[] = "*1*1*0512##";	// Commando OWN per segnalare che e' buio (A=5 PL=12)
char OWN_CrepuscolareOFF[] = "*1*0*0512##";	// Commando OWN per segnalare che non e' buio
#endif
char msgOWN[5];								// inizializza un array char che conterra' un msg OWN
EthernetClient ClientOWN;					// Istanzia un client Ethernet per OWN
byte own_server[] = { OWN_SERVER };			// Impostiamo l'IP del server OWN
int own_serverPort = OWN_PORT;				// Porta Server OWN
unsigned long OWN_Last;						// Ultima volta che e' stato contattato il server OWN
char ACK[] = "*#*1##";						// MSG ACK
char NACK[] = "*#*0##";						// MSG NACK

//-------------------------------------------------------------------------------------------------
// Inizializzazione Syslog
//-------------------------------------------------------------------------------------------------
IPAddress syslogServer(SYSLOGSERVER);
EthernetUDP SyslogUdp;

//-------------------------------------------------------------------------------------------------
// Inizializzazione LCD
//-------------------------------------------------------------------------------------------------
#ifdef LCD
LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_DB4, LCD_DB5, LCD_DB6, LCD_DB7);  //Inizializzazione dell'istanza lcd
#endif

//----------
// LIGHT
//----------
unsigned long Light_Last;
unsigned long Light_rate = LIGHT_SAMPLERATE * 1000;
// CrepuscolareON:  Tiene traccia dello stato del crepuscolare =0 significa che c'è luce  =1 significa che è buio
boolean CrepuscolareON;				

//----------
// WIND 
//----------
volatile unsigned long anem_count = 0;
volatile unsigned long anem_last = 0;
volatile unsigned long anem_min = 0xffffffff;
volatile unsigned long WindLast;
unsigned long AllarmeVentoForte;	// Per tenere traccia quando è stato l'ultimo allarme vento forte
boolean FlagVentoForte = false;		// Per tenere traccia se è attivo o meno un allarme vento

//----------
//RAINGAUGE 
//----------
volatile unsigned long rain_count = 0;		// Numero di bilanciate
volatile unsigned long rain_last = 0;		// Ultima volta che e' avvenuta la bilanciata
boolean AllarmePioggia = false;

//----------
//TH
//----------
boolean am2315OK;								// Per memorizzare lo stato del sensore T/H	
Adafruit_AM2315 am2315;							// faccio una istanza della sonda temperatura umidita'
unsigned long TH_Range = TH_SAMPLERATE * 1000;	// Ogni quanto vado a vedere la temperatura in msec
unsigned long TH_Last;							// Tiene l'ultima visita

Meteo StazioneMeteo;							// Istanzia un tipo di dato Meteo dove memorizzare i dati

//----------
// DEBUGGING										
//----------
unsigned long Debug_Last;
unsigned long Debug_Range = DEBUGDELAY * 1000;

