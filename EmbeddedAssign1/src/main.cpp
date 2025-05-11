#include <Arduino.h>

void setup() {
  // 设定主角（程序里的变量对应硬件的引脚），引脚功能/作用（输入/输出）
    pinMode(27,OUTPUT);
    pinMode(26,OUTPUT);
    pinMode(25,OUTPUT);
    pinMode(33,OUTPUT);
    pinMode(32,OUTPUT);
}

void blink(int i,int t)
{
    digitalWrite(i , HIGH);
    delay(t);
    digitalWrite(i , LOW);
}

void loop() {
  //因为在esp32上连续的引脚编号不连续，所以采用手动枚举的方法
    blink(27, 100);
    blink(25, 100);
    blink(26, 100);
    blink(33, 100);
    blink(32, 500);
    blink(33, 500);
    blink(26, 500);
    blink(25, 500);
}