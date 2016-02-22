// #define RAGGIO 4						// Distanza Braccetto Anemometro dal suo asse in centimetri
// #define DVASCA 2						// Diametro Vasca in metri
// #define PI 3.141593						// Pi Greco
// #define NVASCHE	3						// Numero di Vasche
// #define AVASCHE	2						// Altezza di ogni Vasca in metri

void get_vasca()
{
// Misura la quantita' di acqua nelle cisterne
#ifdef CISTERNA
	// StazioneMeteo.Vasca = (AVASCHE * 100 - (int)(analogRead(VASCA_PIN)))*((DVASCA / 2) ^ 2 * PI)*NVASCHE;
	StazioneMeteo.Vasca = (float(analogRead(VASCA_PIN)*1024)/5);
#endif
}