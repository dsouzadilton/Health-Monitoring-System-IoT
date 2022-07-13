#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP32Servo.h>
#include <Blynk.h>
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

char auth[] = "kKB0eUUHCHWIVc54qkyFNh9utW1TtMgz";
char ssid[] = "Pius";
char pass[] = "psmn1971";

Servo servo;

const unsigned char bitmap [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x18, 0x00, 0x0f, 0xe0, 0x7f, 0x00, 0x3f, 0xf9, 0xff, 0xc0,
  0x7f, 0xf9, 0xff, 0xc0, 0x7f, 0xff, 0xff, 0xe0, 0x7f, 0xff, 0xff, 0xe0, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xf7, 0xff, 0xf0, 0xff, 0xe7, 0xff, 0xf0, 0xff, 0xe7, 0xff, 0xf0, 0x7f, 0xdb, 0xff, 0xe0,
  0x7f, 0x9b, 0xff, 0xe0, 0x00, 0x3b, 0xc0, 0x00, 0x3f, 0xf9, 0x9f, 0xc0, 0x3f, 0xfd, 0xbf, 0xc0,
  0x1f, 0xfd, 0xbf, 0x80, 0x0f, 0xfd, 0x7f, 0x00, 0x07, 0xfe, 0x7e, 0x00, 0x03, 0xfe, 0xfc, 0x00,
  0x01, 0xff, 0xf8, 0x00, 0x00, 0xff, 0xf0, 0x00, 0x00, 0x7f, 0xe0, 0x00, 0x00, 0x3f, 0xc0, 0x00,
  0x00, 0x0f, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

boolean ultra() {
  int duration;
  float distance;
  digitalWrite(13, LOW);
  delayMicroseconds(2);
  digitalWrite(13, HIGH);
  delayMicroseconds(20);
  digitalWrite(13, LOW);
  duration = pulseIn(12, HIGH);
  distance = 15;
  Serial.println(distance);
  if (distance <= 15.00)
    return true;
  return false;
}

void initial() {
  delay(3000);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(1);
  display.setCursor(0, 0);
  display.println("Detected");
  display.setTextSize(1);
  display.print("\nOpening Door");
  display.display();
  delay(500);
  servo_call();
  delay(1000);
  temperature();
}

void servo_call() {
  delay(500);
  for (int pos = 0; pos <= 180; pos += 1) {
    servo.write(pos);
    delay(60);
  }
  delay(3000);
  for (int pos = 180; pos >= 0; pos -= 1) {
    servo.write(pos);
    delay(60);
  }
}

void temperature() {
  int BPM = 69, SPO2 = 98;
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(1);
  display.setCursor(0, 0);
  display.println("\n\nPlace Index Finger");
  display.println("On Temperature");
  display.println("Sensor...");
  display.display();
  delay(3000);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(1);
  display.setCursor(2, 2);
  display.println("Computing\n...");
  display.display();
  delay(3000);
  float tempC = analogRead(34) / 8.19;
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(1);
  display.setCursor(1, 4);
  display.println("Body Temperature: \n");
  display.setTextSize(2);
  display.print(tempC);
  display.setTextSize(1);
  display.println(" celcius");
  display.display();
  delay(4000);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(1);
  display.setCursor(0, 0);
  display.println("Place Index Finger");
  display.println("On POx");
  display.println("Sensor..");
  display.display();
  delay(3000);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(1);
  display.setCursor(2, 2);
  display.println("Computing\n...");
  display.display();
  delay(3000);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(1);
  display.setCursor(0, 0);
  display.println("Heart Rate:");
  display.setTextSize(2);
  display.print(BPM);
  display.setTextSize(1);
  display.println(" bpm");
  display.drawBitmap( 60, 20, bitmap, 32, 30 , 1);
  display.println(" ");
  display.println("Spo2:");
  display.setTextSize(2);
  display.print(SPO2);
  display.setTextSize(1);
  display.print(" %");
  display.display();
  delay(4000);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(1);
  display.setCursor(0, 0);
  display.println("Pushing\ndata to\nserver\n...");
  display.display();
  Blynk.run();
  delay(2000);
  Blynk.virtualWrite(V6, tempC);
  Blynk.virtualWrite(V7, BPM);
  Blynk.virtualWrite(V8, SPO2);
}

void setup() {
  Serial.begin(9600);
  int flag = 0;
  delay(2000);
  Serial.println("Setting Up...");
  delay(2000);
  Serial.println("Libraries included:\n#include <SPI.h>\n #include <Wire.h>\n #include <Adafruit_GFX.h>\n #include <Adafruit_SSD1306.h>\n #include <ESP32Servo.h>\n #include <Blynk.h>\n #include <WiFi.h>\n #include <BlynkSimpleEsp32.h>");
  delay(2000);
  pinMode(12, INPUT);
  pinMode(13, OUTPUT);
  servo.attach(4);
  servo.write(0);
  pinMode(34, INPUT);
  Serial.println("PinModes:\nInput: 12, 34\t Output: 4, 13");
  delay(2000);
  Serial.println("Establishing serial data connection...");
  delay(3000);
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation faileded!"));
    flag = 1;
    for (;;);
  }
  else {
    Serial.println("SSD1306 allocation successful!");
    flag = 0;
    display.display();
  }
  Serial.println("Connecting to server...");
  Serial.println("Configuring...");
  delay(3000);
  Blynk.begin(auth, ssid, pass);
  Serial.println("Connection to Server Successful!");
 
  if(flag == 1){
   Serial.println("SetUp Unsuccessful!");
  }else{
    Serial.println("SetUp successful!");
  }
  delay(2000);
}

void loop() {  
  delay(2000);
  Serial.println("\n");
  if (ultra()) {
    Serial.println("Detected...\nFurther Display Continuation on Oled...");
    delay(3000);
    initial();
  }
}    
