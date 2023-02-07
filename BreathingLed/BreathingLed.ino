/**
 * 功能描述：ESP8266 PWM演示例程
 * @author 单片机菜鸟
 * @date 2018/10/25
 */
 
#define PIN_LED D6
 
void setup() {
  // 这里开始写初始化代码，只会执行一次
  pinMode(PIN_LED,OUTPUT);
  analogWrite(PIN_LED,0);
}

void loop() {
  //这里写运行代码，重复执行
  for(int val=0;val<1024;val++){
     //占空比不断增大  亮度渐亮
   analogWrite(PIN_LED,val);
   delay(2);
  }
  
  for(int val=1023;val>=0;val--){
     //占空比不断变小  亮度渐暗
   analogWrite(PIN_LED,1023);
   delay(2);
  }
}
