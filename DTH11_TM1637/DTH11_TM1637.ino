#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include "TM1637.h"
#include <DHT11.h>
#define CLK 12        //D6
#define DIO 14        //D5
#define DHT11PIN 4    //D2

TM1637 tm1637(CLK,DIO);                           //结构体
dht11 DHT11;                                      //结构体
const char *ssid     = "makabaka";                //wifi名称86
const char *password = "wulala.huhaha.1.2.3";     //wifi密码
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "ntp1.aliyun.com",60*60*8, 30*60*1000);

void setup()
{
  tm1637.init();                    //清屏
  tm1637.point(1);                  //小数点开关，1为打开，0为关闭
  Serial.begin(115200);             //串口波特率
  WiFi.begin(ssid, password);
  
  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
    digitalWrite(LED_BUILTIN, HIGH);
  }
  timeClient.begin();
}

String time1="";
bool dian=false;
void loop()
{
  int chk = DHT11.read(DHT11PIN);
  
  Serial.print("\n");
  Serial.println("ok");    //串口打印ok
  timeClient.update();     //从服务器获取时间
  time1=timeClient.getFormattedTime();
  Serial.println(time1);     //串口打印从服务器获取的时间
  Serial.print("Temperature: ");
  Serial.println((float)DHT11.temperature);  
  Serial.print("Humidity: ");
  Serial.println((float)DHT11.humidity);
  
  
  //获取实时时间
  String part01 = getValue(time1,':',0);  //小时
  String part02 = getValue(time1,':',1);  //分钟
  
  //亮度，pm17:00-24:00亮度降低
  if(part01.toInt() >= 17)
  tm1637.set(2);//BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;
  else
  tm1637.set(BRIGHTEST);
  
  //TM1637显示
  tm1637.display(0,(part01.toInt()/10));
  tm1637.display(1,(part01.toInt()%10)); 
  tm1637.display(2,(part02.toInt()/10));
  tm1637.display(3,(part02.toInt()%10)); 
  dian=!dian;
  tm1637.point(dian);
    delay(1000); 
    
}
// 切割字符串
String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;

  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }
  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}
