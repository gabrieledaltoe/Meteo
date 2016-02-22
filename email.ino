void GetResponse() {
	if (SmtpClient.available()) {
		char c = SmtpClient.read();
		while (SmtpClient.available()) { // memorizza il commando carattere per carattere.
			SMTPServerResponse += c;
			c = SmtpClient.read();
		}
		#ifdef DEBUGEMAIL
		Serial.println("<<<" + SMTPServerResponse);
		#endif
		SMTPServerResponse = "";
	}
}

void SendMsg(String m) {
	SmtpClient.println(m);
	#ifdef DEBUGEMAIL
	Serial.println(">>>" + m);
	delay(SMTP_Wait); // In attesa di responso
	#endif
	GetResponse();
}

void Stop_Email()
{
#ifdef EMAIL
	SmtpClient.flush();
	SmtpClient.stop();
	#ifdef DEBUGEMAIL
	Serial.println("Chiudo la connessione con SMTP Server.");
	#endif
#endif
}

void SendMail(String Subject, String Body) { // Invia le email usando i valori globali con un determinato Oggetto e Corpo Messaggio
#ifdef EMAIL

#ifdef DEBUGEMAIL
Serial.println("\nInizio Connessione con server SMTP...");
#endif 

if (SmtpClient.connect(SMTP_Server, 25)) {
	#ifdef DEBUGEMAIL
	Serial.println("Connesso al server di posta");
	#endif 
	SendMsg("EHLO " + ServerName); /* say hello*/
	SendMsg("AUTH LOGIN ");
	SendMsg(UserName64); /* Username*/
	SendMsg(Password64); /* Password */
	SendMsg("MAIL From:<" + Sender + ">");
	SendMsg("RCPT To:<" + Recipient + ">");
	SendMsg("DATA");
	SendMsg("To: " + Recipient);
	SendMsg("From: " + Sender);
	SendMsg("Subject: " + Subject);
	SendMsg(""); /* empty line */
	SendMsg(Body); /* insert body */
	SendMsg(""); /* empty line */
	SendMsg("."); /* end mail */
	SendMsg("QUIT"); /* terminate connection */
	SmtpClient.println();
	Stop_Email();
}
else {
	#ifdef DEBUGEMAIL
	Serial.println("connection failed");
	#endif
}
#endif 
 }
