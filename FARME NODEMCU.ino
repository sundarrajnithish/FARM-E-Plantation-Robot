#include <SoftwareSerial.h>
#include<ESP8266WebServer.h> //ESP WebServer library
ESP8266WebServer server; //Declaring ESP8266 as server
#include "dht.h"

//Access point Credentials
const char username[]="FARM-E";
const char password[]="7338899824";

SoftwareSerial NodeMCU(D5,D6);

int i;
#define dht_apin 4
dht DHT;
int hum;
int temp;

void setup(){
  Serial.begin(9600);
  NodeMCU.begin(4800);
  pinMode(D3,OUTPUT);
  pinMode(D4,OUTPUT);

  WiFi.softAP(username,password); // set upp acess point and username password

 IPAddress myIP=WiFi.softAPIP(); // getting ip address in variable name myIP
 Serial.print("AP IP address:");  // Printing my Ip address
 Serial.println(myIP); //Print Ip Addess

 server.begin(); //Starts the server
 server.on("/plant",Mode); //Calling the led function
 server.on("/dht",sensor);
 

}

void loop(){
  
  server.handleClient(); //Checks for requests from clients continuosly
  
  
  if(i>0){
  NodeMCU.print(i);
  NodeMCU.println("\n");
  Serial.println(i);
  delay(1000);
  }
}
void temperature()
{
    DHT.read11(dht_apin);
    hum=DHT.humidity;
    temp=DHT.temperature;
    delay(3000);
}
void sensor()
{
  String d="<!DOCTYPE html><html><h1><center><head><title>FARM-E</title></head><body>Humidity= hum Temperature= temp<br><form></body></form></center></h1></html>";
  temperature();
  d.replace("temp",String(temp));
  d.replace("hum",String(hum));
  server.send(200,"text/html",d);  
  
}
void Mode()

{
String m="<!DOCTYPE html><html><h1><center><head><title>FARM-E</title></head><body>Plantation Robot<br><button type=\"submit\" name =\"state\" value=\"0\">FARME</button><form><br><button type=\"submit\" name =\"state\" value=\"1\">AUTO</button><br><br><button type=\"submit\" name =\"state\" value=\"2\">FORWARD</button><button type=\"submit\" name =\"state\" value=\"3\">REVERSE</button><br><br><button type=\"submit\" name =\"state\" value=\"4\">LEFT</button><button type=\"submit\" name =\"state\" value=\"5\">RIGHT</button><br><br><button type=\"submit\" name =\"state\" value=\"6\">SUMP</button><br><br><button type=\"submit\" name =\"state\" value=\"7\">FUNNEL</button><br><br><button type=\"submit\" name =\"state\" value=\"8\">SWEEP1</button><button type=\"submit\" name =\"state\" value=\"9\">SWEEP2</button><br><br><button type=\"submit\" name =\"state\" value=\"10\">MANUAL</button><br><br><button type=\"submit\" name=\"state\" value=\"11\">STOP</button><form></body></form></center></h1></html>";

server.send(404,"text/html",m); //send my html
if (server.arg("state")=="1") //If state=1
{
 i=1;
}
if (server.arg("state")=="10")
{
 i=10;
}
if (server.arg("state")=="2")
{
 i=2;
}
if (server.arg("state")=="3")
{
 i=3;
}
if (server.arg("state")=="4")
{
 i=5;
}
if (server.arg("state")=="5")
{
 i=4;
}
if (server.arg("state")=="6")
{
 i=6;
}
if (server.arg("state")=="7")
{
 i=7;
}
if (server.arg("state")=="8")
{
 i=8;
}
if (server.arg("state")=="9")
{
 i=9;
}
if (server.arg("state")=="10")
{
 i=10;
}
}
