#define LED_PIN 12   //ピンの番号を指定する

void setup() {
  Serial.begin(115200);               //シリアル通信のスタート
  Serial.println("LED Brynk start");  //コンソールに表示する
  pinMode(LED_PIN, OUTPUT);           //ピンを出力モードにする
}

void loop() {     //この中に書いた指示が繰り返される
  
  digitalWrite(LED_PIN, HIGH);    //点灯
  Serial.println("light on");     //表示して確認
  delay(1000);                    //指定した時間待つ
  
  digitalWrite(LED_PIN, LOW);     //消灯
  Serial.println("light off");
  delay(1000);                      
}
