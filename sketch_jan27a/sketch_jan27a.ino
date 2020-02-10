void setup ()  {
Serial.begin (9600) ;
Serial.println ( " ∗∗∗ ␣This ␣message ␣ w i l l ␣ onl y ␣be␣ di s pl a y e d ␣on␣ s t a r t ␣ o r ␣ r e s e t . ␣ ∗∗∗ " ) ;
delay (2000) ;
}

void loop () {
Serial.println("−−␣Arduino ␣now␣ a t ␣ top ␣ o f ␣main␣ l o o p . ␣−−" ) ;
Serial.println("−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−");
delay(2000);
Serial.println("Executing␣instructions␣in␣main␣loop.");
delay(2000);
Serial.println("Arduino␣now␣at␣bottom␣of␣main␣loop.\r\n");
}
