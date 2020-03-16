/*
 * Auteur : G.Menez
 */
#include <WiFi.h>
#include "C:\Users\Alcor\Documents\Arduino/net_misc.h"
#include "ESPAsyncWebServer.h"

#include "OneWire.h"
#include "DallasTemperature.h"

void make_html_response_page(AsyncWebServerRequest* request, String mac, String temperature, String lumin);

void print_ip_status(){
  Serial.print("\nWiFi connected !\n");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("MAC address: ");
  Serial.println(WiFi.macAddress());
}

void connect_wifi(){
 // Access Point of the infrastructure
  const char* ssid = "TODO";
  const char *password= "TODO"; 
 
 
 Serial.println("\nConnecting Wifi to ");
 Serial.println(ssid);
 
 Serial.print("Attempting to connect ");
 WiFi.begin(ssid, password);
 while(WiFi.status() != WL_CONNECTED){
   delay(1000);
   Serial.print(".");
 }
 
 print_ip_status();
}

/* ---- LED ---- */
// LED will use GPIO pin 19
const int LEDpin = 18;
// Ces variables permettent d'avoir une reprÃ©sentation
// interne au programme du statut "electrique" de l'objet.
// Car on ne peut pas interroge une GPIO pour lui demander !
String LEDState = "off";
String couleur = "";


/* ---- TEMP ---- */
OneWire oneWire(23); // Pour utiliser une entite oneWire sur le port 23
DallasTemperature tempSensor(&oneWire) ; // Cette entite est utilisee par le capteur de temperature

/* ---- WEB ---- */
// Set web server port number to 80
AsyncWebServer server(80);

/*--------------------------------*/
String getTemperature() {
  /* Renvoie la String la valeur de temperature
   * Attention !!
   *    J'ai enleve le delay mais convertir prend du temps ! 
   *    moins que les requetes Http.
   */
  float t;
  tempSensor.requestTemperaturesByIndex(0);
  t = tempSensor.getTempCByIndex(0);
  Serial.print("Temperature : "); // for debug
  Serial.print(t);
  Serial.print(" C\n");
  return String(t);
}

String getLumin() {
  int sensorValue;
  sensorValue = analogRead(A0);
  Serial.print("Intensité lumineuse:");
  Serial.print(sensorValue, DEC);
  return String(sensorValue);
}


/*--------------------------------*/
void setup() {
  Serial.begin(9600);
  while (!Serial); // wait for a serial connection. Needed for native USB port only
  
  // Initialize the output variables as outputs
  pinMode(LEDpin, OUTPUT);
  // Set outputs to LOW
  digitalWrite(LEDpin, LOW);
  
  // Init temperature sensor 
  tempSensor.begin();
 
  connect_wifi(); // Connexion Wifi  
server.on(
  "/",
  HTTP_GET,
  [](AsyncWebServerRequest * request){
     String temperature = getTemperature();
          String lumin = getLumin();
          make_html_response_page(request, WiFi.macAddress(),temperature, lumin);  }
  
  );


 
server.on(
    "/led",
    HTTP_POST,
    [](AsyncWebServerRequest * request){
    int params = request->params();
    
    AsyncWebParameter* s = NULL;
        
            for(int i=0;i<params;i++){
              AsyncWebParameter* p = request->getParam(i);
              if(p->name() == "state") {
                s = p;
                break;
              }
              
            }
            
      if(s != NULL) {

        if(s->value() == "on") {
          
          String temperature = getTemperature();
          String lumin = getLumin();
          
          Serial.println("GET request to push LED on");
          LEDState = "Allumee";
          couleur = "red";
        
          digitalWrite(LEDpin, HIGH);
          make_html_response_page(request, WiFi.macAddress(),temperature, lumin);

      
        }
        else if(s->value() == "off") {
          
          String temperature = getTemperature();
          String lumin = getLumin();
          
          Serial.println("GET request to push LED off");
          LEDState = "Eteinte";
          couleur = "red";
              
          digitalWrite(LEDpin, LOW);
          make_html_response_page(request, WiFi.macAddress(),temperature, lumin);

        }
        else {
          Serial.println("on off error");
          Serial.println(s->value());
          request->send(404);
        }

      }
      else {
          Serial.println("param not found");
          request->send(404);

      }
    });
     server.begin(); // Lancement du serveur

}

/*--------------------------------*/
void make_html_response_page(AsyncWebServerRequest* request, String mac, String temperature, String lumin){
    /*
     * Cette fonction transmet au client la page Web qui forme la reponse 
     * Ã  sa requete.
     */
    // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
    // and a content-type so the client knows what's coming, then a blank line:

    AsyncWebServerResponse* response;
    

    String HTMLResponse = "<!DOCTYPE html><html><head><style>body{font-family: Helvetica; margin: 0px auto; text-align: center; background-color:lightGrey;}"
    "div{display: inline-block;}"
    ".buttong{padding: 16px 40px; font-size: 30px; color:green;}"
    ".buttonr{color: red;}"
    "p{text-align: left; font-size: 20px;font-weight : bold;}"
    "h1, h2{color: #00008b;}</style></head>"

    // Web Page Body
    "<body><h1>ESP32 Web Server</h1>"
    "<h2>Controler la LED, le photoresistor et la temperature via le web.</h2>"
    "<p>Objet Ref : " + mac + "</p>"
    "<p>Temperature : "+ temperature +" </p>"
    "<p>Luminosite : "+ lumin +" </p>"

            
    // Display current state, and ON/OFF buttons for LED
    "<p>Statut de la LED : <font color=" + couleur +">" + LEDState + "</font></p>"
    
    // Ctrl buttons
    "<div><form action=\"/led\" method=\"post\"><button name=\"state\" value=\"on\" class=\"buttong\">Push for LED ON</button></form></div>"
    "<div><form action=\"/led\" method=\"post\"><button name=\"state\" value=\"off\" class=\"buttong buttonr\">Push for LED OFF</button></form></div>"
    "<form action=\"/setValues\"><label for=\"fname\">Temperature min</label><br><input type=\"number\" id=\"fname\" name=\"fname\" value=\"24\"><br>"
    "<label for=\"lname\">Luminosite en fin de journee</label><br><input type=\"number\" id=\"lname\" name=\"lname\" value=\"28\"><br><br><input type=\"submit\" value=\"27\">"
    "</form></body></html>";
            
    // The HTTP response ends with another blank line
        request->send(200, "text/html", HTMLResponse);

}



/*--------------------------------*/
void loop(){}
