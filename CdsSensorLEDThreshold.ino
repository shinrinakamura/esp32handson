/*cdsセンサーの動きを確認するためのシンプルなプログラムです
 * 
 * CdSセンサーの読み取り値が閾値以下になったらLEDを点灯させます。
 * それ以外の時は消灯しています
*/

#define CDS_PIN 35      //センサーのピン番号
#define LED_PIN 12      //LEDのピン番号
#define LIGHT_TH 2000   //LEDを点灯させる閾値（CdSの測定値の半部くらいから始めてください）

void setup() {
  Serial.begin(115200);
  Serial.println("cds sensor start");
  pinMode(CDS_PIN, INPUT);        //使用するピンのセット
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  
  int Measurevalue;
  Measurevalue = analogRead(CDS_PIN); //明るさの測定
  
  if (Measurevalue < LIGHT_TH){       //閾値を下回ったら
    digitalWrite(LED_PIN, HIGH);      //LEDを点灯させる
  }else{
    digitalWrite(LED_PIN, LOW);       //それ以外のときは消灯
  }
  
  Serial.print("Mesure value is : "); //測定値の表示
  Serial.println(Measurevalue);
  
  delay(500);                         //測定頻度調整のために遅延を入れる
}
