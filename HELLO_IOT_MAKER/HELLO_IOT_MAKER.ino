#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#define LED  D1

const char* ssid = "nome_da_rede_wifi";
const char* password = "password_da_rede_wifi";

ESP8266WebServer server(80);

void turnOn() {
  server.send(200, "text/html; charset=utf-8", "Maker o Led está ligado!");
  digitalWrite(LED, HIGH);
}
void turnOff() {
  server.send(200, "text/html; charset=utf-8", "Maker o Led está desligado");
  digitalWrite(LED, LOW);
}

void handleRoot() {
  server.send(200, "text/html; charset=utf-8", "Bem Vindo Maker!");
}

void handleNotFound(){
  server.send(404, "text/html; charset=utf-8", "Comando Inválido.");
}


void setup(void){
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  WiFi.mode(WIFI_STA);
  Serial.println(".");
  // Aguarda até estar ligado ao Wi-Fi
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Ligado a ");
  Serial.println(ssid);
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());
  server.on("/", handleRoot);
  server.on("/on", turnOn);
  server.on("/off", turnOff);
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server iniciado.");
}

void loop(void){
  server.handleClient();
}
