/*cdsセンサーの動きと湿度センサーで測定した値をmqttで送信するシンプルなプログラムです
 * 
 * @author S.Nakamura 2022-04-23
 */

//使用するライブラリの読み込み
#include <WiFi.h>
#include <PubSubClient.h>

//Wi-Fiのアクセスポイントの接続情報
const char ssid[] = "your_ssid";
const char passwd[] = "your_pass";

//brokerサーバーの接続情報
const char* mqttHost = "######"; // MQTTのIPかホスト名
const int mqttPort = 1883;       // MQTTのポート

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

const char* topic_pub = "handson0429";                         // 送信するトピック名

//センサーで使用するピンを指定
#define MOIST_PIN 35
#define CDS_PIN 32

//プロトタイプ宣言
bool connectWiFi();
//espのMacアドレスを取得する
String getMacAddr();
//サーバーとの接続の確認をする
void connectMqtt();
//Mqttを送信する
//第一引数；水分センサーの測定値
//第二引数：cdsセンサーの測定値
void MqttPublish(int moist, int cds);


void setup() {
  Serial.begin(115200);
  Serial.println("CdS Moist sensor moving check start");
  pinMode(MOIST_PIN, INPUT);
  pinMode(CDS_PIN, INPUT);
  connectWiFi();      //接続確認
//   connectMqtt();
}

void loop() {
//   connectMqtt();
  int MeasureMoist;                     //読み取った値を入れておく領域を確保
  int MeasureCds;
  MeasureMoist = analogRead(MOIST_PIN); //水分センサーの値を読み取る
  MeasureCds = analogRead(CDS_PIN);     //cdsセンサーの値を読み取る
  
  Serial.print("Mesure Moist is : ");   //表示して確認
  Serial.println(MeasureMoist);
  Serial.print("Mesure Cds is : ");
  Serial.println(MeasureCds);

  MqttPublish(MeasureMoist, MeasureCds);  //mqttを送信
  delay(1000);      //送信頻度を調整するために遅延を入れる
}


//Wi-Fiの接続確認
bool connectWiFi(){
        
  WiFi.begin(ssid, passwd);
  Serial.print("WiFi connecting...");
  //10秒たっても接続されていないときはリセットする
  int i = 0 ;   //接続確認のリセット用
  while(WiFi.status() != WL_CONNECTED) {
  i += 1;
  Serial.print("...");
  delay(1000);
  if (i == 10){
    Serial.println("wi-fi reset");
    connectWiFi();
      }
  }
        
  Serial.print(" connected. ");
  Serial.println(WiFi.localIP());

  return true;
}


//mqttサーバーに接続
void connectMqtt(){
  
  //Wi-Fiの接続確認
  while(WiFi.status() != WL_CONNECTED) {
    
  Serial.print("WiFi is not connect");
  connectWiFi();

  }
  
  //brokerサーバーに接続する
  //第一引数：ブローカーサーバーのドメインもしくはipアドレス
  //第二引数：接続するポート（通常は1883か8883）
  mqttClient.setServer(mqttHost, mqttPort);
  

  //clientIDを作成してサーバーに接続する
  while( ! mqttClient.connected() ) {

    Serial.println("Connecting to MQTT...");
    
    //MacアドレスからクライアントIDを作成する
    String clientId = "ESP32-" +  getMacAddr();
    //確認用の表示
    Serial.print("clientID : "); 
    Serial.println(clientId.c_str()); 
    
    //接続の確認
    //if ( mqttClient.connect(clientId.c_str(),mqtt_username, mqtt_password) ) {  //ユーザー認証を行う時はこちらを利用する
    if ( mqttClient.connect(clientId.c_str())) { 
      Serial.println("connected"); 

    }
  }
}





//mqttを送信する関数
//引数：なし
//ステータスを返すようにしたい
void MqttPublish(int moist, int cds){
  

  //第一引数：トピック名
  //第二引数：送信するデータ
  char payload[125];    //大きめに確保
  sprintf(payload,"{\"deviceId\":\"01\",\"moist\":%d,\"light\":%d}", moist, cds);
  mqttClient.publish(topic_pub, payload);
  Serial.println("published Message is ");
  Serial.println(payload);

}

// Macアドレスを文字列で取得する
String getMacAddr()
{
  byte mac[6];
  char buf[50];
  WiFi.macAddress(mac);
  sprintf(buf, "%02x%02x%02x%02x%02x%02x", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
  return String(buf);
}
