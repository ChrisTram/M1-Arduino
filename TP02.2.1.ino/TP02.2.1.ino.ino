#include <ETH.h>
#include <WiFi.h>
#include <WiFiAP.h>
#include <WiFiClient.h>
#include <WiFiGeneric.h>
#include <WiFiMulti.h>
#include <WiFiScan.h>
#include <WiFiServer.h>
#include <WiFiSTA.h>
#include <WiFiType.h>
#include <WiFiUdp.h>

//BasicWificonnection
#include<WiFi.h>
void print_ip_status(){
  Serial.print("\nWiFi␣connected␣!\n");
  Serial.print("IP␣address:␣");
  Serial.println(WiFi.localIP());
  Serial.print("MAC␣address:␣");
  Serial.println(WiFi.macAddress());
}
void connect_wifi(){
  //AccessPointoftheinfrastructure
  const char* ssid="HUAWEI−6EC2";
  const char* password="FGY9MLBL";
  Serial.println("\nConnecting␣Wifi␣to␣");
  Serial.println(ssid);
  Serial.print("Attempting␣to␣connect␣");
  WiFi.begin(ssid,password);
  while(WiFi.status()!= WL_CONNECTED){
    delay(1000);
    Serial.print(".");
  }
  print_ip_status();
}
void setup(){
  Serial.begin(9600);
  while (!Serial);//waitforaserialconnection
  //SetWiFitostationmodeanddisconnectfromanAPif
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  connect_wifi();
}
void loop(){
  //nocode
  //WiFi.disconnect();
}
