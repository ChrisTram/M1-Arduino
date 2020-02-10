void setup(){
Serial.begin(9600);
Serial.println( "<Serial is ready>");
}

void loop(){
  // l'ESP transmet
  sensorValue = analogRead(A0);
  Serial.print(sensorValue, DEC);
  Serial.print('\n');

  if(Serial.avalaible() > 0) {
    receivedChar = Serial.read(); //Just one byte
    // say what you got:
    Serial.print('\nI received : ');
    Serial.print(receivedChar);
    if (receivedChar == '1')
      coeff = 0;
    else 
      coeff 1;
  }
  delay(1000);  
  }
  
