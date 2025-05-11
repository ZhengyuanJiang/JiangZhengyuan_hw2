// 任务1

/*#include <Arduino.h>

const int led = 2;

void setup()
{
  // 初始化串口通信
  Serial.begin(115200);
  pinMode(led, OUTPUT);

}

void loop()
{
  // 检查是否有串口数据可读
  if (Serial.available() > 0)
  {
    char command = Serial.read();

    switch (command)
    {
      case '1':
        digitalWrite(led, HIGH);
        Serial.println("LED on");
        break;
      case '2':
        digitalWrite(led, LOW);
        Serial.println("LED off");
        break;
      case '3':
      Serial.println("LED blink");
      for(int i = 0;i < 5;i++)
      {
        digitalWrite(led, HIGH);
        delay(100);
        digitalWrite(led, LOW);
        delay(100);
      }
      break;
      default:
        Serial.println("Invalid instruction.");
        break;
    }
  }
}
*/

// 任务2

#include <Arduino.h>

const String password[] = {"AA", "BB", "CC", "AA"};
const int len = 4;

int currentIndex = 0; // 当前接收到的是第几段密码
String myString = ""; // 暂存接收到的字符串

void setup()
{
  Serial.begin(115200); 
}

// 验证输入的字符串
void checkPassword(String input)
{
  if (input == password[currentIndex])
    {
    currentIndex++; // 逐个验证输入的密码
    if (currentIndex == len) 
    {
      Serial.println("The password is correct.");
      currentIndex = 0; // 重置
    }
    }
    else
    {
    Serial.println("The password is wrong.");
    currentIndex = 0; 
    }
}

void loop()
{
  while (Serial.available())
  {
    myString = Serial.readStringUntil('\n');
    checkPassword(myString);
  }
}