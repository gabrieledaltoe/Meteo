int Init_Ethernet() 
{
	int stato = 0; // Se sono qui vuol dire che ancora non c'è stata inizializzaione delle Ethernet
#ifdef ETHERNET

	#ifdef DEBUGETHERNET
	Serial.println("Arduino si sta connettendo alla rete");
	Serial.println();
	#endif

	if (ipstatico) {		// Vuol dire che e' specificato un IP 
		Ethernet.begin(mac, ip, dnsip, gateway, subnet);
		stato = 1;
	
	} else	{			// Connessione alla rete e recupero IP mediante DHCP
		stato = Ethernet.begin(mac);
		if ( stato == 0) 	{
			#ifdef DEBUGETHERNET
			Serial.println("DHCP Fallito");
			Serial.println();
			#endif
		}	
	}
	if (stato) {
		#ifdef DEBUGETHERNET
		Serial.print("Arduino ha il seguente IP: ");
		Serial.println(Ethernet.localIP());
		#endif
	}
	return stato;
#endif
}

