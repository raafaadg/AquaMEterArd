#define DEBUG true
 
void setup()
{
  pinMode(7,OUTPUT);
  digitalWrite(7,1);
  Serial.begin(115200);
}
 
void loop()
{
  // Verifica se o ESP8266 esta enviando dados

  String conteudo = "";
  char caractere;
  if(Serial.available()>0){
    while(Serial.available() > 0) {
      // read the incoming byte:
      caractere = Serial.read();
    
      // Ignora caractere de quebra de linha
      if (caractere != '\n'){
        // Concatena valores
        conteudo.concat(caractere);
      }
      delay(10);       
    }
      //Serial.print("Recebi: ");
      //Serial.println(conteudo);
      if(conteudo == "liga")
        digitalWrite(7,0);
      if(conteudo == "des"){
        digitalWrite(7,1);
        Serial.write("1,2,3,4,5,6,7,8,9,4,7,8,5,2,1,4,7,8,5,6,9,8,5,47");
      }
  } 
}
