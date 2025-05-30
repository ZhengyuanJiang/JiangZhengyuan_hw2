/* #include <Arduino.h>
#include <U8g2lib.h>

// 自定义CLK和SDA引脚
#define OLED_CLK  18  
#define OLED_SDA  5
// 构造对象
U8G2_SSD1306_128X64_NONAME_F_SW_I2C OLED(U8G2_R0, OLED_CLK, OLED_SDA, U8X8_PIN_NONE);

void setup() {
  // 初始化OLED
  OLED.begin();
  // 开启中文字符集支持
  OLED.enableUTF8Print();
  // 设置字体
  OLED.setFont(u8g2_font_wqy12_t_gb2312);
}

void loop() {
 
  // 清除缓存区内容
  OLED.clearBuffer();
  // 绘制内容
  OLED.setCursor(0, 10);
  OLED.print("Hello, world!");

  OLED.setCursor(0, 30);
  OLED.print("你好,世界!");

  // 发送缓存区内容到OLED
  OLED.sendBuffer();

  delay(1000);
}
*/
#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

const unsigned char gImage[512] = {
  0X00,0X01,0X40,0X00,0X3A,0X00,
  0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
  0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
  0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
  0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
  0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
  0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
  0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
  0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
  0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
  0X00,0X00,0X00,0XC0,0X01,0XC0,0X00,0X00,0X00,0X00,0X00,0XE0,0X03,0XC0,0X00,0X00,
  0X00,0X00,0X00,0XF0,0X07,0XE0,0X00,0X00,0X00,0X00,0X00,0XF8,0X0F,0XE0,0X00,0X00,
  0X00,0X00,0X01,0XFD,0XFF,0XE0,0X00,0X00,0X00,0X00,0X01,0XF8,0X07,0XE0,0X00,0X00,
  0X00,0X00,0X03,0X04,0X05,0XE0,0X00,0X00,0X00,0X00,0X0E,0X10,0X01,0XE0,0X00,0X00,
  0X00,0X00,0X08,0X00,0X01,0XE0,0X00,0X00,0X00,0X00,0X0F,0XF3,0XFF,0XF0,0X00,0X00,
  0X00,0X00,0X00,0X7A,0X0F,0XF0,0X00,0X00,0X00,0X00,0X10,0X7E,0X0F,0XF0,0X00,0X00,
  0X00,0X00,0X0E,0XFF,0XFF,0XF0,0X00,0X00,0X00,0X00,0X0F,0XFB,0XFF,0XF0,0X00,0X00,
  0X00,0X00,0X08,0X7C,0X1F,0XF0,0X00,0X00,0X00,0X00,0X00,0X78,0X03,0XF0,0X00,0X00,
  0X00,0X00,0X10,0X30,0X00,0X10,0X00,0X00,0X00,0X00,0X00,0X30,0X00,0X00,0X00,0X00,
  0X00,0X00,0X08,0XFB,0X80,0X20,0X00,0X00,0X00,0X00,0X08,0X4F,0X00,0X60,0X00,0X00,
  0X00,0X00,0X04,0X00,0X00,0XC0,0X00,0X00,0X00,0X00,0X06,0X00,0X03,0XC0,0X00,0X00,
  0X00,0X00,0X03,0XC0,0X0F,0X00,0X00,0X00,0X00,0X00,0X00,0XFF,0XFE,0X00,0X00,0X00,
  0X00,0X00,0X00,0X3F,0XF0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
  0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
  0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
  0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
  0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
  0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
  0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
  0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
};

Adafruit_SSD1306 OLED(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1); // 使用 I2C 接口

void setup() {
    Serial.begin(115200);
    Wire.begin(26,25); // SDA和SCL 引脚
    OLED.begin(SSD1306_SWITCHCAPVCC, 0x3C); // I2C 地址为 0x3C
    OLED.clearDisplay();
    OLED.setCursor(1,1);// 光标位置
    OLED.setTextSize(1); // 字体大小
    OLED.setTextColor(SSD1306_WHITE); // 字体为白色
    delay(1000); // 延时 1 秒
    OLED.drawBitmap(0, 0, gImage, 128, 64, SSD1306_WHITE); // 显示图片
    OLED.display(); // 刷新显示
}
void loop()
{

}


