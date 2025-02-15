// ESP32 Touch Test
// Just test touch pin - Touch0 is T0 which is on GPIO 4.

void setup() {
  Serial.begin(115200);
  delay(1000);  // give me time to bring up serial monitor
  Serial.println("ESP32 Touch Test");
}

void loop() {
  Serial.printf("T1:%i\n", touchRead(T1));  // get value using T0
  Serial.printf("T2:%i\n", touchRead(T2));  // get value using T0
  Serial.printf("T3:%i\n", touchRead(T3));  // get value using T0
  Serial.printf("T4:%i\n", touchRead(T4));  // get value using T0
  Serial.printf("T5:%i\n", touchRead(T5));  // get value using T0
  Serial.printf("T6:%i\n", touchRead(T6));  // get value using T0
  Serial.printf("T7:%i\n", touchRead(T7));  // get value using T0
  Serial.printf("T8:%i\n", touchRead(T8));  // get value using T0
  Serial.printf("T9:%i\n", touchRead(T9));  // get value using T0
  delay(500);
}
