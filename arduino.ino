#include <WiFi.h>
#include <WebSocketsServer.h>
#include <DFRobot_MaqueenPlus.h>

DFRobot_MaqueenPlus maqueenPlus(22, 21);

const char* ssid = "TP-LINK_0B69";
const char* password = "29205820";

WebSocketsServer webSocket(81);

void handleCommand(const String& command, int speed) {
    Serial.printf("Command: %s, Speed: %d\n", command.c_str(), speed);

    if (command == "forward") {
        // Move forward at the specified speed
        Serial.println("Executing forward command.");
        maqueenPlus.motorControl(maqueenPlus.eALL, maqueenPlus.eCCW, speed);
        // Implement logic here
    } else if (command == "left") {
        // Turn left at the specified speed
        Serial.println("Executing left command.");
        maqueenPlus.motorControl(maqueenPlus.eRIGHT, maqueenPlus.eCCW, 50);
        maqueenPlus.motorControl(maqueenPlus.eLEFT, maqueenPlus.eCW, 50);
        // Implement logic here
    } else if (command == "right") {
        // Turn right at the specified speed
        Serial.println("Executing right command.");
        maqueenPlus.motorControl(maqueenPlus.eRIGHT, maqueenPlus.eCW, 50);
        maqueenPlus.motorControl(maqueenPlus.eLEFT, maqueenPlus.eCCW, 50);
        // Implement logic here
    } else if (command == "back") {
        // Move back at the specified speed
        Serial.println("Executing back command.");
         maqueenPlus.motorControl(maqueenPlus.eALL, maqueenPlus.eCW, speed);
        // Implement logic here
    } else if (command == "stop") {
        // Stop
        Serial.println("Executing stop command.");
        maqueenPlus.motorControl(maqueenPlus.eALL, maqueenPlus.eCCW, 0);
        // Implement logic here
    } else {
        Serial.println("Unknown command received.");
    }
}

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
    switch (type) {
        case WStype_DISCONNECTED:
            Serial.printf("[%u] Disconnected!\n", num);
            break;
        case WStype_TEXT:
            Serial.printf("[%u] Received text: %s\n", num, payload);
            
            // Split command and speed
            String data = String((char *)payload);
            int commaIndex = data.indexOf(',');
            String command = data.substring(0, commaIndex);
            int speed = data.substring(commaIndex + 1).toInt();

            handleCommand(command, speed);
            break;
    }
}

void setup() {
  Serial.begin(115200);

  Serial.println("Starting WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
  Serial.println("WebSocket server started.");

  Serial.println("initialize MaqueenPlus I2C communication");
  while (maqueenPlus.begin() != 0) {
    Serial.println("I2C initialization failed");
  }
  Serial.println("I2C initialization success");
}

void loop() {
  webSocket.loop();
}