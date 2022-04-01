//////////////////////////////////////////////////////////////////////////
///          An Arduino script to receive the temperature &            ///
///    the glucose concentration values from the server (Server.py)    ///
//////////////////////////////////////////////////////////////////////////

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#ifndef STASSID
#define STASSID "PoleDeVinci_DVIC"       // Enter your network SSID
#define STAPSK  "8PfURsp!dvic"           // Enter your network password
#endif

const char* ssid     = STASSID;          // Replace STASSID by "your_WiFi_network_name"
const char* password = STAPSK;           // Replace STAPSK by "your_WiFi_network_password"

String host = "172.21.72.179";           // Enter your domain
const uint16_t port = 1235;

WiFiClient client;


void setup() {
  
  Serial.begin(115200);

  // We start by connecting to a WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  // Set the ESP8266 to be a WiFi-client
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);              // Start the communication

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  IPAddress ip = WiFi.localIP();

  if (client.connect(host, port)) {
    Serial.println("connection succeeded");
  } else {
    Serial.println("connection failed");
    delay(5000);
    return;
  }
}


void loop() {
  
  if (WiFi.status() == WL_CONNECTED) {     // Check WiFi connection status
 
    HTTPClient http;                       // Declare an object of class HTTPClient
    http.begin(client, "http://" + host +":" + port + "/get_data");        //Specify the request destination
    int httpCode = http.GET();             // Request payload from the server
 
    if (httpCode > 0) {                    // The server has new payload available
 
      String payload = http.getString();   // Get the request response payload
      const char* payloadCStr = payload.c_str();
//      Serial.print("payload: ");
//      Serial.println(payload);             // Print the response payload
      
      char* pch = strtok((char*)payloadCStr, ";");
      Serial.print("Temperature: ");
      Serial.println(pch);
      pch = strtok(NULL, ";");
      Serial.print("Glucose concentration: ");
      Serial.println(pch);
      
      // String token = payload.substring(0, payload.find(";"));
      // Serial.println(Temperature);
 
    }
    http.end();      //Close the connection
  }
  delay(5000);       // Send a request every 5 seconds
}
