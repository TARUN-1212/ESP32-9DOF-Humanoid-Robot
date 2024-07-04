#include "MiniHashHumanoid.h"

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "XT_DAC_Audio.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
XT_DAC_Audio_Class DacAudio(25, 0);

#include "ExpressionBitmap.h"
#include "VoiceHexData.h"

#define min_pulse_width 100
#define max_pulse_width 550
#define frequency 50

/* Initializing servo drive and OLED display */
void MiniHashHumanoid::init_hash() {
  pwm.begin();
  pwm.setPWMFreq(frequency);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  initial_face();
}

/* Servo angle setting */
void MiniHashHumanoid::set_servo(int servo, int servo_pwm) {
  pwm.setPWM(servo, 0, servo_pwm);
}

/* Initial position */
void MiniHashHumanoid::initial_position() {
  int pwm_array[16] = {100, 100, 325, 325, 550, 550, 325, 325, 325, 325, 325, 325, 325, 325, 325, 325}; /* RH1,RH2,RL1,RL2,LH1,LH2,LL1,LL2,HEAD,DMY1,DMY2,DMY3,DMY4,DMY5,DMY6 */
  for (int i = 0; i < 16; i++) {
    servo_position[i] = pwm_array[i];
  }
  move_servo(1000, pwm_array);
}
/* Moving each servo at given time interval */
void MiniHashHumanoid::move_servo(int time, int  servo_target[]) {

  if (time > 10) {
    for (int i = 0; i < 16; i++) {
      increment[i] = ((servo_target[i]) - servo_position[i]) / (time / 10.0);
    }
    final_time =  millis() + time;

    for (int iteration = 1; millis() < final_time; iteration++) {
      partial_time = millis() + 10;

      for (int i = 0; i < 16; i++) {
        set_servo(i, (int)(servo_position[i] + (iteration * increment[i])));

      }
      while (millis() < partial_time);

      DacAudio.FillBuffer();
      //Serial.println("hehe");
    }
  }
  else {
    for (int i = 0; i < 16; i++) {
      set_servo(i, (int)servo_target[i]);
    }
  }
  for (int i = 0; i < 16; i++) {
    servo_position[i] = servo_target[i];
  }
}

/******************************************************************************************************/
void MiniHashHumanoid::initial_face() {
  display.clearDisplay();
  display.drawBitmap(0, 0, initialface, 128, 64, 1);
  display.display();
}
void MiniHashHumanoid::bink_eye(int bink_count) {

  for (int i = 1 ; i <= bink_count; i++) {
    display.clearDisplay();
    display.drawBitmap(0, 0, blinkeye, 128, 64, 1);
    display.display();
    delay(500);
    initial_face();
    delay(1000);
  }
}
void MiniHashHumanoid::talking_face() {
  display.clearDisplay();
  display.drawBitmap(0, 0, talkface, 128, 64, 1);
  display.display();
}
void MiniHashHumanoid::happy_face() {
  display.clearDisplay();
  display.drawBitmap(0, 0, happyface, 128, 64, 1);
  display.display();
}
void MiniHashHumanoid::angry_face() {
  display.clearDisplay();
  display.drawBitmap(0, 0, angryface, 128, 64, 1);
  display.display();
}

void MiniHashHumanoid::sad_face() {
  display.clearDisplay();
  display.drawBitmap(0, 0, sadface, 128, 64, 1);
  display.display();
}
void MiniHashHumanoid::crying_face() {
  display.clearDisplay();
  display.drawBitmap(0, 0, cryingface, 128, 64, 1);
  display.display();
}

/******************************************************************************************************/
void MiniHashHumanoid::say_hi(int count) {
  XT_Wav_Class PlayVoice(hellohumanoids);
  PlayVoice.RepeatForever = false;
  DacAudio.Play(&PlayVoice);
  talking_face();

  int pwm_array1[16] = {500, 250, 325, 325, 550, 550, 325, 325, 325, 325, 325, 325, 325, 325, 325, 325};
  move_servo(1500, pwm_array1);

  for (int i = 1; i <= count; i++) {
    int pwm_array2[16] = {500, 175, 325, 325, 550, 550, 325, 325, 325, 325, 325, 325, 325, 325, 325, 325};
    int pwm_array3[16] = {500, 250, 325, 325, 550, 550, 325, 325, 325, 325, 325, 325, 325, 325, 325, 325};
    move_servo(1000, pwm_array2);
    move_servo(1000, pwm_array3);
  }
  int pwm_array4[16] = {100, 100, 325, 325, 550, 550, 325, 325, 325, 325, 325, 325, 325, 325, 325, 325};
  move_servo(1500, pwm_array4);
  initial_face();
}

/******************************************************************************************************/
void MiniHashHumanoid::my_name_hash_jr() {

  XT_Wav_Class PlayVoice(mynamehashjr);
  PlayVoice.RepeatForever = false;
  DacAudio.Play(&PlayVoice);
  talking_face();

  int pwm_array1[16] = {300, 175, 325, 325, 550, 550, 325, 325, 325, 325, 325, 325, 325, 325, 325, 325};
  int pwm_array2[16] = {300, 100, 325, 325, 550, 550, 325, 325, 325, 325, 325, 325, 325, 325, 325, 325};
  int pwm_array3[16] = {300, 175, 325, 325, 550, 550, 325, 325, 325, 325, 325, 325, 325, 325, 325, 325};
  int pwm_array4[16] = {100, 100, 325, 325, 550, 550, 325, 325, 325, 325, 325, 325, 325, 325, 325, 325};
  move_servo(1500, pwm_array1);
  move_servo(1000, pwm_array2);
  move_servo(1000, pwm_array3);
  move_servo(1500, pwm_array4);
  initial_face();
}

/******************************************************************************************************/
void MiniHashHumanoid::i_am_mini_robot() {

  XT_Wav_Class PlayVoice(iamaminirobot);
  PlayVoice.RepeatForever = false;
  DacAudio.Play(&PlayVoice);
  talking_face();

  int pwm_array1[16] = {300, 175, 325, 325, 450, 550, 325, 325, 325, 325, 325, 325, 325, 325, 325, 325};
  int pwm_array2[16] = {300, 100, 325, 325, 450, 550, 325, 325, 325, 325, 325, 325, 325, 325, 325, 325};
  int pwm_array3[16] = {300, 175, 325, 325, 500, 550, 325, 325, 325, 325, 325, 325, 325, 325, 325, 325};
  int pwm_array4[16] = {100, 100, 325, 325, 550, 550, 325, 325, 325, 325, 325, 325, 325, 325, 325, 325};
  move_servo(1500, pwm_array1);
  move_servo(1000, pwm_array2);
  move_servo(1000, pwm_array3);
  move_servo(1500, pwm_array4);
  initial_face();
}

/******************************************************************************************************/
void MiniHashHumanoid::say_yes() {
  XT_Wav_Class PlayVoice(sayyes);
  PlayVoice.RepeatForever = false;
  DacAudio.Play(&PlayVoice);
  talking_face();

  int pwm_array1[16] = {225, 100, 325, 325, 550, 550, 325, 325, 325, 325, 325, 325, 325, 325, 325, 325};
  int pwm_array2[16] = {100, 100, 325, 325, 550, 550, 325, 325, 325, 325, 325, 325, 325, 325, 325, 325};
  move_servo(1000, pwm_array1);
  move_servo(1500, pwm_array2);
  initial_face();
}

/******************************************************************************************************/
void MiniHashHumanoid::say_no() {
  XT_Wav_Class PlayVoice(sayno);
  PlayVoice.RepeatForever = false;
  DacAudio.Play(&PlayVoice);
  talking_face();

  int pwm_array1[16] = {100, 100, 325, 325, 550, 550, 325, 325, 275, 325, 325, 325, 325, 325, 325, 325};
  int pwm_array2[16] = {100, 100, 325, 325, 550, 550, 325, 325, 375, 325, 325, 325, 325, 325, 325, 325};
  int pwm_array3[16] = {100, 100, 325, 325, 550, 550, 325, 325, 325, 325, 325, 325, 325, 325, 325, 325};
  move_servo(500, pwm_array1);
  move_servo(1000, pwm_array2);
  move_servo(500, pwm_array3);
  initial_face();
}

/******************************************************************************************************/
void MiniHashHumanoid::say_thank_you() {
  XT_Wav_Class PlayVoice(saythankyou);
  PlayVoice.RepeatForever = false;
  DacAudio.Play(&PlayVoice);
  talking_face();

  int pwm_array1[16] = {200, 150, 325, 325, 450, 500, 325, 325, 325, 325, 325, 325, 325, 325, 325, 325};
  int pwm_array2[16] = {100, 100, 325, 325, 550, 550, 325, 325, 325, 325, 325, 325, 325, 325, 325, 325};
  move_servo(1500, pwm_array1);
  move_servo(1500, pwm_array2);
  initial_face();
}

/******************************************************************************************************/
void MiniHashHumanoid::do_happy_face() {
  happy_face();
  XT_Wav_Class PlayVoice(happyfacevoice);
  PlayVoice.RepeatForever = false;
  DacAudio.Play(&PlayVoice);

  int pwm_array1[16] = {200, 100, 325, 325, 550, 550, 325, 325, 325, 325, 325, 325, 325, 325, 325, 325};
  int pwm_array2[16] = {100, 100, 325, 325, 550, 550, 325, 325, 325, 325, 325, 325, 325, 325, 325, 325};
  move_servo(1000, pwm_array1);
  move_servo(1000, pwm_array2);
  initial_face();
}

/******************************************************************************************************/
void MiniHashHumanoid::do_angry_face() {
  angry_face();
  XT_Wav_Class PlayVoice(angryfacevoice);
  PlayVoice.RepeatForever = false;
  DacAudio.Play(&PlayVoice);

  int pwm_array1[16] = {200, 100, 325, 325, 550, 550, 325, 325, 325, 325, 325, 325, 325, 325, 325, 325};
  int pwm_array2[16] = {100, 100, 325, 325, 550, 550, 325, 325, 325, 325, 325, 325, 325, 325, 325, 325};
  move_servo(1000, pwm_array1);
  move_servo(1000, pwm_array2);
  initial_face();
}

/******************************************************************************************************/
void MiniHashHumanoid::do_sad_face() {
  sad_face();
  XT_Wav_Class PlayVoice(sadfacevoice);
  PlayVoice.RepeatForever = false;
  DacAudio.Play(&PlayVoice);

  int pwm_array1[16] = {200, 100, 325, 325, 550, 550, 325, 325, 325, 325, 325, 325, 325, 325, 325, 325};
  int pwm_array2[16] = {100, 100, 325, 325, 550, 550, 325, 325, 325, 325, 325, 325, 325, 325, 325, 325};
  move_servo(1500, pwm_array1);
  move_servo(2000, pwm_array2);
  initial_face();
}

/******************************************************************************************************/
void MiniHashHumanoid::do_crying_face() {
  crying_face();
  XT_Wav_Class PlayVoice(cryingfacevoice);
  PlayVoice.RepeatForever = false;
  DacAudio.Play(&PlayVoice);

  int pwm_array1[16] = {200, 100, 325, 325, 550, 550, 325, 325, 325, 325, 325, 325, 325, 325, 325, 325};
  int pwm_array2[16] = {100, 100, 325, 325, 550, 550, 325, 325, 325, 325, 325, 325, 325, 325, 325, 325};
  move_servo(1500, pwm_array1);
  move_servo(1500, pwm_array2);
  initial_face();
}

/******************************************************************************************************/
void MiniHashHumanoid::hands_up() {

  int pwm_array1[16] = {525, 100, 325, 325, 125, 550, 325, 325, 325, 325, 325, 325, 325, 325, 325, 325};
  move_servo(3000, pwm_array1);
}

/******************************************************************************************************/
void MiniHashHumanoid::hands_down() {

  int pwm_array1[16] = {100, 100, 325, 325, 550, 550, 325, 325, 325, 325, 325, 325, 325, 325, 325, 325};
  move_servo(3000, pwm_array1);
}

/******************************************************************************************************/
void MiniHashHumanoid::hand_wave(int count) {

  int pwm_array1[16] = {100, 400, 325, 325, 550, 400, 325, 325, 325, 325, 325, 325, 325, 325, 325, 325};
  move_servo(1500, pwm_array1);
  for (int i = 1; i <= count; i++) {
    int pwm_array2[16] = {100, 250, 325, 325, 550, 250, 325, 325, 325, 325, 325, 325, 325, 325, 325, 325};
    int pwm_array3[16] = {100, 400, 325, 325, 550, 400, 325, 325, 325, 325, 325, 325, 325, 325, 325, 325};
    move_servo(1000, pwm_array2);
    move_servo(1000, pwm_array3);
  }
  int pwm_array4[16] = {100, 100, 325, 325, 550, 550, 325, 325, 325, 325, 325, 325, 325, 325, 325, 325};
  move_servo(1500, pwm_array4);
}

/******************************************************************************************************/
void MiniHashHumanoid::right_leg_wave(int count) {

  int pwm_array1[16] = {100, 100, 325, 375, 550, 550, 325, 325, 325, 325, 325, 325, 325, 325, 325, 325};
  int pwm_array2[16] = {100, 100, 325, 375, 550, 550, 325, 375, 325, 325, 325, 325, 325, 325, 325, 325};
  move_servo(1000, pwm_array1);
  move_servo(1000, pwm_array2);
  for (int i = 1; i <= count; i++) {
    int pwm_array3[16] = {100, 100, 325, 250, 550, 550, 325, 375, 325, 325, 325, 325, 325, 325, 325, 325};
    int pwm_array4[16] = {100, 100, 325, 400, 550, 550, 325, 375, 325, 325, 325, 325, 325, 325, 325, 325};
    move_servo(1000, pwm_array3);
    move_servo(1000, pwm_array4);
  }
  int pwm_array5[16] = {100, 100, 325, 375, 550, 550, 325, 375, 325, 325, 325, 325, 325, 325, 325, 325};
  int pwm_array6[16] = {100, 100, 325, 325, 550, 550, 325, 325, 325, 325, 325, 325, 325, 325, 325, 325};
  move_servo(1000, pwm_array5);
  move_servo(1000, pwm_array6);
}

/******************************************************************************************************/
void MiniHashHumanoid::left_leg_wave(int count) {

  int pwm_array1[16] = {100, 100, 325, 325, 550, 550, 325, 275, 325, 325, 325, 325, 325, 325, 325, 325};
  int pwm_array2[16] = {100, 100, 325, 275, 550, 550, 325, 275, 325, 325, 325, 325, 325, 325, 325, 325};
  move_servo(1000, pwm_array1);
  move_servo(1000, pwm_array2);
  for (int i = 1; i <= count; i++) {
    int pwm_array3[16] = {100, 100, 325, 275, 550, 550, 325, 400, 325, 325, 325, 325, 325, 325, 325, 325};
    int pwm_array4[16] = {100, 100, 325, 275, 550, 550, 325, 250, 325, 325, 325, 325, 325, 325, 325, 325};
    move_servo(1000, pwm_array3);
    move_servo(1000, pwm_array4);
  }
  int pwm_array5[16] = {100, 100, 325, 275, 550, 550, 325, 275, 325, 325, 325, 325, 325, 325, 325, 325};
  int pwm_array6[16] = {100, 100, 325, 325, 550, 550, 325, 325, 325, 325, 325, 325, 325, 325, 325, 325};
  move_servo(1000, pwm_array5);
  move_servo(1000, pwm_array6);
}

/******************************************************************************************************/
void MiniHashHumanoid::leg_hand_shake(int count) {

  int pwm_array1[16] = {100, 400, 325, 400, 550, 400, 325, 325, 325, 325, 325, 325, 325, 325, 325, 325};
  move_servo(1000, pwm_array1);
  for (int i = 1; i <= count; i++) {
    int pwm_array2[16] = {100, 250, 325, 325, 550, 250, 325, 250, 325, 325, 325, 325, 325, 325, 325, 325};
    int pwm_array3[16] = {100, 400, 325, 400, 550, 400, 325, 325, 325, 325, 325, 325, 325, 325, 325, 325};
    move_servo(1000, pwm_array2);
    move_servo(1000, pwm_array3);
  }
  int pwm_array4[16] = {100, 100, 325, 325, 550, 550, 325, 325, 325, 325, 325, 325, 325, 325, 325, 325};
  move_servo(1000, pwm_array4);
}

/******************************************************************************************************/
void MiniHashHumanoid::right_slide_wave(int count) {

  int pwm_array1[16] = {100, 100, 325, 325, 550, 550, 325, 250, 325, 325, 325, 325, 325, 325, 325, 325};
  int pwm_array2[16] = {100, 325, 325, 250, 550, 325, 325, 250, 325, 325, 325, 325, 325, 325, 325, 325};
  move_servo(2000, pwm_array1);
  move_servo(2000, pwm_array2);
  for (int i = 1; i <= count; i++) {
    int pwm_array3[16] = {100, 400, 325, 250, 550, 250, 325, 250, 400, 325, 325, 325, 325, 325, 325, 325};
    int pwm_array4[16] = {100, 250, 325, 250, 550, 400, 325, 250, 250, 325, 325, 325, 325, 325, 325, 325};
    move_servo(1000, pwm_array3);
    move_servo(1000, pwm_array4);
  }
  int pwm_array5[16] = {100, 100, 325, 325, 550, 550, 325, 250, 325, 325, 325, 325, 325, 325, 325, 325};
  int pwm_array6[16] = {100, 100, 325, 325, 550, 550, 325, 325, 325, 325, 325, 325, 325, 325, 325, 325};
  move_servo(2000, pwm_array5);
  move_servo(2000, pwm_array6);
}

/******************************************************************************************************/
void MiniHashHumanoid::left_slide_wave(int count) {

  int pwm_array1[16] = {100, 100, 325, 400, 550, 550, 325, 325, 325, 325, 325, 325, 325, 325, 325, 325};
  int pwm_array2[16] = {100, 325, 325, 400, 550, 325, 325, 400, 325, 325, 325, 325, 325, 325, 325, 325};
  move_servo(2000, pwm_array1);
  move_servo(2000, pwm_array2);
  for (int i = 1; i <= count; i++) {
    int pwm_array3[16] = {100, 400, 325, 400, 550, 250, 325, 400, 250, 325, 325, 325, 325, 325, 325, 325};
    int pwm_array4[16] = {100, 250, 325, 400, 550, 400, 325, 400, 400, 325, 325, 325, 325, 325, 325, 325};
    move_servo(1000, pwm_array3);
    move_servo(1000, pwm_array4);
  }
  int pwm_array5[16] = {100, 100, 325, 400, 550, 550, 325, 325, 325, 325, 325, 325, 325, 325, 325, 325};
  int pwm_array6[16] = {100, 100, 325, 325, 550, 550, 325, 325, 325, 325, 325, 325, 325, 325, 325, 325};
  move_servo(2000, pwm_array5);
  move_servo(2000, pwm_array6);
}

/******************************************************************************************************/
void MiniHashHumanoid::move_forward(int steps, int speed) {
  for (int i = 1; i <= steps; i++) {
    int pwm_array1[16] = {100, 100, 375, 350, 500, 550, 375, 350, 325, 325, 325, 325, 325, 325, 325, 325};
    int pwm_array2[16] = {100, 100, 375, 325, 550, 550, 375, 325, 325, 325, 325, 325, 325, 325, 325, 325};
    int pwm_array3[16] = {150, 100, 275, 300, 550, 550, 275, 300, 325, 325, 325, 325, 325, 325, 325, 325};
    int pwm_array4[16] = {100, 100, 275, 325, 550, 550, 275, 325, 325, 325, 325, 325, 325, 325, 325, 325};
    move_servo(speed, pwm_array1);
    move_servo(speed, pwm_array2);
    move_servo(speed, pwm_array3);
    move_servo(speed, pwm_array4);
  }
  int pwm_array5[16] = {100, 100, 325, 325, 550, 550, 325, 325, 325, 325, 325, 325, 325, 325, 325, 325};
  move_servo(speed, pwm_array5);
}

/******************************************************************************************************/
void MiniHashHumanoid::move_backward(int steps, int speed) {

  for (int i = 1; i <= steps; i++) {
    int pwm_array1[16] = {100, 100, 375, 300, 550, 550, 375, 300, 325, 325, 325, 325, 325, 325, 325, 325};
    int pwm_array2[16] = {100, 100, 375, 325, 550, 550, 375, 325, 325, 325, 325, 325, 325, 325, 325, 325};
    int pwm_array3[16] = {100, 100, 275, 350, 550, 550, 275, 350, 325, 325, 325, 325, 325, 325, 325, 325};
    int pwm_array4[16] = {100, 100, 275, 325, 550, 550, 275, 325, 325, 325, 325, 325, 325, 325, 325, 325};
    move_servo(speed, pwm_array1);
    move_servo(speed, pwm_array2);
    move_servo(speed, pwm_array3);
    move_servo(speed, pwm_array4);
  }
  int pwm_array5[16] = {100, 100, 325, 325, 550, 550, 325, 325, 325, 325, 325, 325, 325, 325, 325, 325};
  move_servo(speed, pwm_array5);
}

/******************************************************************************************************/
void MiniHashHumanoid::turn_left(int steps, int speed) {

  for (int i = 1; i <= steps; i++) {
    int pwm_array1[16] = {100, 100, 325, 325, 550, 550, 325, 300, 325, 325, 325, 325, 325, 325, 325, 325};
    int pwm_array2[16] = {100, 100, 325, 288, 550, 550, 325, 288, 325, 325, 325, 325, 325, 325, 325, 325};
    int pwm_array3[16] = {100, 100, 375, 288, 550, 550, 325, 288, 325, 325, 325, 325, 325, 325, 325, 325};
    int pwm_array4[16] = {100, 100, 375, 325, 550, 550, 325, 325, 325, 325, 325, 325, 325, 325, 325, 325};
    int pwm_array5[16] = {100, 100, 375, 350, 550, 550, 325, 325, 325, 325, 325, 325, 325, 325, 325, 325};
    int pwm_array6[16] = {100, 100, 375, 362, 550, 550, 325, 362, 325, 325, 325, 325, 325, 325, 325, 325};
    int pwm_array7[16] = {100, 100, 325, 362, 550, 550, 325, 362, 325, 325, 325, 325, 325, 325, 325, 325};
    int pwm_array8[16] = {100, 100, 325, 325, 550, 550, 325, 325, 325, 325, 325, 325, 325, 325, 325, 325};
    move_servo(500, pwm_array1);
    move_servo(500, pwm_array2);
    move_servo(500, pwm_array3);
    move_servo(500, pwm_array4);
    move_servo(500, pwm_array5);
    move_servo(500, pwm_array6);
    move_servo(500, pwm_array7);
    move_servo(500, pwm_array8);
  }
  int pwm_array9[16] = {100, 100, 325, 325, 550, 550, 325, 325, 325, 325, 325, 325, 325, 325, 325, 325};
  move_servo(speed, pwm_array9);
}

/******************************************************************************************************/
void MiniHashHumanoid::turn_right(int steps, int speed) {

  for (int i = 1; i <= steps; i++) {
    int pwm_array1[16] = {100, 100, 325, 350, 550, 550, 325, 325, 325, 325, 325, 325, 325, 325, 325, 325};
    int pwm_array2[16] = {100, 100, 325, 362, 550, 550, 325, 362, 325, 325, 325, 325, 325, 325, 325, 325};
    int pwm_array3[16] = {100, 100, 325, 362, 550, 550, 275, 362, 325, 325, 325, 325, 325, 325, 325, 325};
    int pwm_array4[16] = {100, 100, 325, 325, 550, 550, 275, 325, 325, 325, 325, 325, 325, 325, 325, 325};
    int pwm_array5[16] = {100, 100, 325, 325, 550, 550, 275, 300, 325, 325, 325, 325, 325, 325, 325, 325};
    int pwm_array6[16] = {100, 100, 325, 288, 550, 550, 275, 288, 325, 325, 325, 325, 325, 325, 325, 325};
    int pwm_array7[16] = {100, 100, 325, 288, 550, 550, 325, 288, 325, 325, 325, 325, 325, 325, 325, 325};
    int pwm_array8[16] = {100, 100, 325, 325, 550, 550, 325, 325, 325, 325, 325, 325, 325, 325, 325, 325};
    move_servo(500, pwm_array1);
    move_servo(500, pwm_array2);
    move_servo(500, pwm_array3);
    move_servo(500, pwm_array4);
    move_servo(500, pwm_array5);
    move_servo(500, pwm_array6);
    move_servo(500, pwm_array7);
    move_servo(500, pwm_array8);
  }
  int pwm_array9[16] = {100, 100, 325, 325, 550, 550, 325, 325, 325, 325, 325, 325, 325, 325, 325, 325};
  move_servo(speed, pwm_array9);
}

/******************************************************************************************************/
void MiniHashHumanoid::side_move_right(int steps) {

  for (int i = 1; i <= steps; i++) {
    int pwm_array1[16] = {100, 100, 325, 325, 550, 550, 325, 400, 325, 325, 325, 325, 325, 325, 325, 325};
    int pwm_array2[16] = {100, 100, 325, 325, 550, 550, 325, 325, 325, 325, 325, 325, 325, 325, 325, 325};
    move_servo(400, pwm_array1);
    move_servo(400, pwm_array2);
  }
}

/******************************************************************************************************/
void MiniHashHumanoid::side_move_left(int steps) {

  for (int i = 1; i <= steps; i++) {
    int pwm_array1[16] = {100, 100, 325, 250, 550, 550, 325, 325, 325, 325, 325, 325, 325, 325, 325, 325};
    int pwm_array2[16] = {100, 100, 325, 325, 550, 550, 325, 325, 325, 325, 325, 325, 325, 325, 325, 325};
    move_servo(400, pwm_array1);
    move_servo(400, pwm_array2);
  }
}

/******************************************************************************************************/
void MiniHashHumanoid::flying_hand_wave(int count) {

  int pwm_array1[16] = {100, 475, 325, 325, 550, 175, 325, 325, 325, 325, 325, 325, 325, 325, 325, 325};
  move_servo(2000, pwm_array1);

  for (int i = 1; i <= count; i++) {
    int pwm_array2[16] = {100, 175, 325, 325, 550, 475, 325, 325, 325, 325, 325, 325, 325, 325, 325, 325};
    int pwm_array3[16] = {100, 475, 325, 325, 550, 175, 325, 325, 325, 325, 325, 325, 325, 325, 325, 325};

    move_servo(1000, pwm_array2);
    move_servo(1000, pwm_array3);
  }
  int pwm_array4[16] = {100, 100, 325, 325, 550, 550, 325, 325, 325, 325, 325, 325, 325, 325, 325, 325};
  move_servo(2000, pwm_array4);
}

/******************************************************************************************************/
void MiniHashHumanoid::jump(int count, int height) {
  if (height > 30) {
    height = 30;
  }
  for (int i = 1; i <= count; i++) {
    int pwm_array1[16] = {100, 100, 325, 400, 550, 550, 325, 250, 325, 325, 325, 325, 325, 325, 325, 325};
    int pwm_array2[16] = {100, 100, 325, 325, 550, 550, 325, 325, 325, 325, 325, 325, 325, 325, 325, 325};

    move_servo(1000, pwm_array1);
    move_servo(1000, pwm_array2);
  }
}

/******************************************************************************************************/
void MiniHashHumanoid::leg_head_shake(int count) {

  for (int i = 1; i <= count; i++) {
    int pwm_array1[16] = {100, 100, 375, 325, 550, 550, 375, 325, 375, 325, 325, 325, 325, 325, 325, 325};
    int pwm_array2[16] = {100, 100, 275, 325, 550, 550, 275, 325, 275, 325, 325, 325, 325, 325, 325, 325};

    move_servo(1000, pwm_array1);
    move_servo(1000, pwm_array2);
  }
  int pwm_array3[16] = {100, 100, 325, 325, 550, 550, 325, 325, 325, 325, 325, 325, 325, 325, 325, 325};
  move_servo(1000, pwm_array3);
}

/******************************************************************************************************/
void MiniHashHumanoid::flying(int count) {

  int pwm_array1[16] = {100, 400, 325, 325, 550, 250, 325, 325, 325, 325, 325, 325, 325, 325, 325, 325};
  move_servo(2000, pwm_array1);
  for (int i = 1; i <= count; i++) {
    int pwm_array2[16] = {100, 250, 325, 400, 550, 400, 325, 250, 325, 325, 325, 325, 325, 325, 325, 325};
    int pwm_array3[16] = {100, 400, 325, 325, 550, 250, 325, 325, 325, 325, 325, 325, 325, 325, 325, 325};

    move_servo(1000, pwm_array2);
    move_servo(1000, pwm_array3);
  }
  int pwm_array4[16] = {100, 100, 325, 325, 550, 550, 325, 325, 325, 325, 325, 325, 325, 325, 325, 325};
  move_servo(1000, pwm_array4);
}

/******************************************************************************************************/
void MiniHashHumanoid::leg_shake(int count) {

  for (int i = 1; i <= count; i++) {
    int pwm_array1[16] = {100, 100, 325, 288, 550, 550, 325, 288, 325, 325, 325, 325, 325, 325, 325, 325};
    int pwm_array2[16] = {100, 100, 325, 362, 550, 550, 325, 362, 325, 325, 325, 325, 325, 325, 325, 325};

    move_servo(1000, pwm_array1);
    move_servo(1000, pwm_array2);
  }
  int pwm_array3[16] = {100, 100, 325, 325, 550, 550, 325, 325, 325, 325, 325, 325, 325, 325, 325, 325};
  move_servo(1000, pwm_array3);
}

/******************************************************************************************************/
void MiniHashHumanoid::hand_straight_shake(int count) {

  int pwm_array1[16] = {500, 100, 325, 325, 325, 550, 325, 325, 325, 325, 325, 325, 325, 325, 325, 325};
  move_servo(2000, pwm_array1);
  for (int i = 1; i <= count; i++) {
    int pwm_array2[16] = {325, 100, 325, 325, 150, 550, 325, 325, 325, 325, 325, 325, 325, 325, 325, 325};
    int pwm_array3[16] = {500, 100, 325, 325, 325, 550, 325, 325, 325, 325, 325, 325, 325, 325, 325, 325};

    move_servo(1000, pwm_array2);
    move_servo(1000, pwm_array3);
  }
  int pwm_array4[16] = {100, 100, 325, 325, 550, 550, 325, 325, 325, 325, 325, 325, 325, 325, 325, 325};
  move_servo(1000, pwm_array4);
}
/******************************************************************************************************/
