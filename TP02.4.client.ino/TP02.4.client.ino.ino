/*
 * Auteur : G.Menez
 */
#include <WiFi.h>
#include "net_misc.h"

/* For loop delay */
unsigned long lastConnectionTime = 0;                  // last time you connected to the server, in milliseconds
unsigned long delayinseconds = 10L;
const unsigned long postingInterval = delayinseconds * 1000L; // delay between updates, in milliseconds

/* Configure targeted serveraddress */
char serv_name[] = "httpbin.org";
//IPAddress server(64,131,82,241);

/* Instanciation of a WifiClient aka a socket : the WEB server */
WiFiClient serv;

/*--------------------------------*/
void setup() {
  Serial.begin(9600);
  while (!Serial) ; // wait for serial port to connect. Needed for native USB port only

  connect_wifi(); 
}

void httpRequest(WiFiClient serv) {
  /*
   * This method makes a HTTP connection to the server
   */
  // First, close any connection before send a new request.
  // This will free the socket on the WiFi shield
  serv.stop();

  // If there's a successful connection:
  if (serv.connect(serv_name, 80)) {
    Serial.println("connecting...");

    /* Write the request to the server */
    serv.println("GET /ip HTTP/1.1");  // url
    serv.println("Host: httpbin.org"); // host name 
    serv.println("User-Agent: ArduinoWiFi/1.1");
    serv.println("Connection: close");
    serv.println();

    // note the time that the connection was made:
    lastConnectionTime = millis();
  } else {
    // if you couldn't make a connection:
    Serial.println("connection failed");
  }
}

void loop() {
  
  // if there's incoming data from the net connection.
  // send it out the serial port.  
  // This is for debugging purposes only :
  while (serv.available()) {
    char c = serv.read();
    Serial.write(c);
  }

  // if ten seconds have passed since your last connection,
  // then connect again and send data:
  if (millis() - lastConnectionTime > postingInterval) {
    httpRequest(serv);
  }
}
