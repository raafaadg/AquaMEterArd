#include <SoftwareSerial.h>

SoftwareSerial esp(2, 3); // RX, TX
boolean cont = false;
void setup()
{
  pinMode(7,OUTPUT);
  digitalWrite(7,1);
  Serial.begin(115200);
  esp.begin(115200);
}
 
void loop()
{
  // Verifica se o ESP8266 esta enviando dados

  String conteudo = "";
  char caractere;
  if(cont){
    Serial.println("ENVIANDO DADO");
    esp.print(random(300));
    //esp.write(random(300));
    delay(500);
  }
  if(esp.available()>0){
    Serial.println("DADO RECEBIDO");
    while(esp.available() > 0) {
      // read the incoming byte:
      caractere = esp.read();
    
      // Ignora caractere de quebra de linha
      if (caractere != '\n'){
        // Concatena valores
        conteudo.concat(caractere);
      }
      delay(10);       
    }
    Serial.print("O CONTEUDO É: ");
    Serial.println(conteudo);
      //Serial.print("Recebi: ");
      //Serial.println(conteudo);
      if(conteudo == "f"){
        Serial.println("FREQUENCIA RECEBIDA!!");
        String freq = "";
        for(int i = 0; i < 40; i++){
          freq = freq + String(random(100));
          freq = freq + ",";
        }
        Serial.print("A FREQUENCIA É: ");
        Serial.println(freq);
        esp.print(freq);
      }
      if(conteudo == "l"){
        Serial.println("LIGA RECEBIDO!!");
        digitalWrite(7,0);
        cont = true;
      }
      if(conteudo == "d"){
        Serial.println("DESLIGA RECEBIDO!!");
        cont = false;
        digitalWrite(7,1);
        //Serial.write("1,2,3,4,5,6,7,8,9,4,7,8,5,2,1,4,7,8,5,6,9,8,5,47");
      }
  } 
}
