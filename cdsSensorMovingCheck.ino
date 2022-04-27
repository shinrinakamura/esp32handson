#define LIGHT_PIN 35    //ピン番号を指定

void setup() {
  Serial.begin(115200);
  Serial.println("CdS start");
  pinMode(LIGHT_PIN, INPUT);    //センサーピンのセット
}

void loop() {
  int Measurevalue;   //センサーの値を読み取るための変数を用意
  Measurevalue = analogRead(LIGHT_PIN);   //測定値を読みとる
  
  Serial.print("Mesure value is : ");   //表示して確認
  Serial.println(Measurevalue);
  
  delay(500);                           //遅延を入れて読み取り頻度を調整
}
