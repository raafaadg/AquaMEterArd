// Programa: Web Server com modulo ESP8266
// Alteracoes e adaptacoes: FILIPEFLOP
 
#include <SoftwareSerial.h>
 
//RX pino 2, TX pino 3
SoftwareSerial esp8266(2, 3);
 
#define DEBUG true
 
void setup()
{
  pinMode(7,OUTPUT);
  digitalWrite(7,1);
  Serial.begin(115200);
  esp8266.begin(115200);
 
//  sendData("AT+RST", 2000, DEBUG); // rst
//  // Conecta a rede wireless
//  sendData("AT+CWMODE=2", 1000, DEBUG);
//  delay(3000);
////  sendData("AT+CWJAP=\"Leutner\",\"engenharia12\"", 2000, DEBUG);
////  delay(3000);
//  // Mostra o endereco IP
//  sendData("AT+CIFSR", 1000, DEBUG);
//  // Configura para multiplas conexoes
//  sendData("AT+CIPMUX=0", 1000, DEBUG);
//  // Inicia o web server na porta 80
//  sendData("AT+CIPSERVER=1,80", 1000, DEBUG);
}
 
void loop()
{
  // Verifica se o ESP8266 esta enviando dados
  if (esp8266.available())
  {
    if (esp8266.find("+IPD,"))
    {
      delay(300);
//      int connectionId = esp8266.read() - 48;
      Serial.print("VALOR RECEBIDO");
      Serial.print(esp8266.read());
      if(esp8266.find("LIGA"))
        digitalWrite(7,0);
      else
        digitalWrite(7,1);

      String asw = "recebeu";
      String cipSend = "AT+CIPSEND=";
      cipSend += 0;
//      cipSend += connectionId;
      cipSend += ",";
      cipSend += asw.length();
//      cipSend += "rn";
 
      sendData(cipSend, 1000, DEBUG);
      sendData(asw, 1000, DEBUG);
 
      String closeCommand = "AT+CIPCLOSE=";
      closeCommand += 0; // append connection id
//      closeCommand += connectionId; // append connection id
//      closeCommand += "rn";
 
      sendData(closeCommand, 3000, DEBUG);
    }
  }
}
 
String sendData(String command, const int timeout, boolean debug)
{
  // Envio dos comandos AT para o modulo
  String response = "";
  esp8266.print(command);
  long int time = millis();
  while ( (time + timeout) > millis())
  {
    while (esp8266.available())
    {
      // The esp has data so display its output to the serial window
      char c = esp8266.read(); // read the next character.
      response += c;
    }
  }
  if (debug)
  {
    Serial.print(response);
  }
  return response;
}
