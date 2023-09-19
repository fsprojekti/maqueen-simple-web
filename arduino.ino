#include <WiFi.h>
#include <WebSocketsServer.h>
#include <DFRobot_MaqueenPlus.h>

DFRobot_MaqueenPlus maqueenPlus(22, 21);

const char* ssid = "mr. Corn";
const char* password = "9d0e8ace";

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
        maqueenPlus.motorControl(maqueenPlus.eRIGHT, maqueenPlus.eCCW, 30);
        maqueenPlus.motorControl(maqueenPlus.eLEFT, maqueenPlus.eCW, 30);
        // Implement logic here
    } else if (command == "right") {
        // Turn right at the specified speed
        Serial.println("Executing right command.");
        maqueenPlus.motorControl(maqueenPlus.eRIGHT, maqueenPlus.eCW, 30);
        maqueenPlus.motorControl(maqueenPlus.eLEFT, maqueenPlus.eCCW, 30);
        // Implement logic here
    } else if (command == "back") {
        // Move back at the specified speed
        Serial.println("Executing back command.");
         maqueenPlus.motorControl(maqueenPlus.eALL, maqueenPlus.eCW, 50);
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



// #include <LiteLED.h>

// #define LED_TYPE LED_STRIP_WS2812
// #define LED_GPIO 23
// #define

// LiteLED ledUnder(LED_TYPE, 0);



// static const crgb_t L_RED = 0xff0000;
// static const crgb_t L_GREEN = 0x00ff00;
// static const crgb_t L_BLUE = 0x0000ff;
// static const crgb_t L_WHITE = 0xe0e0e0;

// int sensorSum = 0;
// int sensorSumMax = 1000;


// void setup() {
//   // initialize serial print
//   Serial.begin(115200);

//   Serial.println("initialize MaqueenPlus I2C communication");
//   while (maqueenPlus.begin() != 0) {
//     Serial.println("I2C initialization failed");
//   }
//   Serial.println("I2C initialization success");

//   //Turn on lights under the robot
//   ledUnder.begin(LED_GPIO, 4);  // initialze the myLED object. Here we have 1 LED attached to the LED_GPIO pin
//   ledUnder.brightness(100);     // set the LED photon intensity level
//   ledUnder.setPixel(0, L_WHITE, 1);
//   delay(200);
//   ledUnder.setPixel(1, L_WHITE, 1);
//   delay(200);
//   ledUnder.setPixel(2, L_WHITE, 1);
//   delay(200);
//   ledUnder.setPixel(3, L_WHITE, 1);
//   delay(200);
// }

// int counterA = 0;
// int counterB = 0;
// void loop() {
//   if (counterA > 10) {
//     counterA = 0;
//     uint16_t* state = maqueenPlus.getGrayscale();
//     sensorSum = state[0] + state[1] + state[2];
//     if (sensorSumMax<sensorSum) sensorSumMax=sensorSum;
//   }
//   if (counterB > 200) {
//     counterB = 0;
//     Serial.print(sensorSum);
//     Serial.print(" : ");
//     Serial.println(sensorSumMax);
//   }
//   delay(1);
//   counterA++;
//   counterB++;


//   //Move robot
//   // Serial.print(maqueenPlus.eALL);
//   // Serial.print(" ");
//   // Serial.print(maqueenPlus.eCW);
//   // Serial.println();

//   // Serial.print("Max sensor: ");
//   // Serial.print(sensorSumMax);
//   // Serial.print(" current sum: ");
//   // Serial.println(sensorSum);
//   // delay(100);
//   // Serial.println("test");
//   // maqueenPlus.getGrayscale();

//   // uint8_t dataOn[] = { 1 };
//   // uint8_t dataOff[] = { 0 };
//   // maqueenPlus.writeReg(0x0B, dataOn, 1);
//   // delay(1000);
//   // maqueenPlus.writeReg(0x0B, dataOff, 1);
//   // delay(1000);

//   // uint8_t dataOn[] = {1,50};
//   // uint8_t dataOff[] = {2, 50};
//   // maqueenPlus.writeReg(0x00, &dataOn[0], 2);
//   // delay(1000);
//   // maqueenPlus.writeReg(0x00, &dataOff[0], 2);
//   // delay(1000);
// }
