/* moistセンサーの動きを確認するためのシンプルなプログラムです
 * どのような値を表示するのか、最大値と最小値のあたりをつけます
*/


#define MOIST_PIN 32

void setup() {
  Serial.begin(115200);
  Serial.println("start");
  pinMode(MOIST_PIN, INPUT);
}

void loop() {
  int Measurevalue;
  Measurevalue = analogRead(MOIST_PIN); 
  
  Serial.print("Mesure value is : ");
  Serial.println(Measurevalue);
  
  delay(500);
}
