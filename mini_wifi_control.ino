
#include "MiniHashHumanoid.h"
#include <WiFi.h>
#include "ESPAsyncWebServer.h"
AsyncWebServer server(80);

MiniHashHumanoid minihash;

const char* ssid = "POCOM2"; /* Your SSID */
const char* password = "helloworld"; /* Your Password */
String data = ""; 

void setup() {

  Serial.begin(115200);
  Serial.println("GPIO test!");
  delay(1000);
  minihash.init_hash();
  minihash.initial_position();
  delay(1000);
  connectingToWiFi(); /* Connectinf to WiFi */

// to handle the incoming request we need a web server
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    Serial.println("");
    if (request->hasParam("data")) {
      data = request->getParam("data")->value(); /* Getting data value from request parameter */
      Serial.println(data);
    }
    else {
      data = "";
    }
    request->send(200, "text/plain", "OK"); /* Sending response */
  });
  server.begin(); /* Begining Server */

}
void connectingToWiFi() {
  delay(3000);
  WiFi.disconnect();
  delay(1000);
  Serial.println("Connecting to WiFi");
  WiFi.begin(ssid, password);
  while ((!(WiFi.status() == WL_CONNECTED))) {
    delay(1000);
    Serial.print("...");
  }
  Serial.println("Connected");
  Serial.println("Local IP is : ");
  Serial.print((WiFi.localIP().toString()));
  delay(5000);
}

void loop() {

  delay(1000);
  if (data != "") {
    if (data == "initialize")
      minihash.initial_position();
    else if (data == "forward")
      minihash.move_forward(4, 500);
    else if (data == "backward")
      minihash.move_backward(4, 500);
    else if (data == "turnleft")
      minihash.turn_left(2, 500);
    else if (data == "turnright")
      minihash.turn_right(2, 500);
    else if (data == "blinkeye")
      minihash.bink_eye(2);
    else if (data == "happyface")
      minihash.do_happy_face();
    else if (data == "angryface")
      minihash.do_angry_face();
    else if (data == "sadface")
      minihash.do_sad_face();
    else if (data == "cryingface")
      minihash.do_crying_face();
    else if (data == "sayhi")
      minihash.say_hi(2);
    else if (data == "handsup")
      minihash.hands_up();
    else if (data == "handsdown")
      minihash.hands_down();
    else if (data == "leftlegwave")
      minihash.left_leg_wave(2);
    else if (data == "handwave")
      minihash.hand_wave(3);
    else if (data == "rightlegwave")
      minihash.right_leg_wave(2);
    else if (data == "leftbendwave")
      minihash.left_slide_wave(2);
    else if (data == "handlegshake")
      minihash.leg_hand_shake(3);
    else if (data == "rightbendwave")
      minihash.right_slide_wave(2);
    else if (data == "moveleft")
      minihash.side_move_left(5);
    else if (data == "jump")
      minihash.jump(4, 30);
    else if (data == "moveright")
      minihash.side_move_right(5);
    else if (data == "sayyes")
      minihash.say_yes();
    else if (data == "sayno")
      minihash.say_no();
    else if (data == "saythankyou")
      minihash.say_thank_you();
  }
  data = "";
}
