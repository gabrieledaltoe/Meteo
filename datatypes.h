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

typedef struct 
{
	// Esempio: Att1[0]=1 significa che c'è stato un cambio di stato; (Att1[0]=0 no cambio stato).
	//	        Att[1]=1 significa che l'attuatore è ON, Att[1]=0 significa che l'attuatore è OFF
	bool Att1[2];   
	bool Att2[2];
	bool Att3[2];
} Attuatori;