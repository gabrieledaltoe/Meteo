typedef struct				// Definisce un tipo di dati dove memorizzare i valori rilevati dai sensori
							// Attenzione che sono memorizzati in int non in float
{
  float TempExt;			// Temperatura Esterna
  float HumExt;				// Umidita Esterna
  float HumExtMIN;			// Umidita Esterna Minima
  float Wind;				// Velocita Vento Istantanea  ogni 5 secondi
  float WindMax;			// Memorizzo il vento massimo
  float WindDir;			// Direzione Vento Istantanea ogni 5 secondi
  float Rain_rate;			// mm Pioggia Istantanea calcolata ogni 60 sec 
  int Lux;					// Intensita' di Luce istantanea (in Percentuale)
  float Vasca;				// Litri presenti nella Vasca
} Meteo;

