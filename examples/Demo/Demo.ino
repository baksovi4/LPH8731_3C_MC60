#include <LPH8731_3C_MC60.h>
#include <SimpleTimer.h>

LPH8731_3C_MC60 lcd;

SimpleTimer timer;

void setup ()
{
  Serial.begin(115200);
  lcd.begin();
  lcd.white();
  delay(100);
  lcd.setSymbol(164, 40, 20, 0, 255, 6, 6, 0);
  delay(400);
  lcd.white();
  lcd.setSymbolShadow(164, 40, 20, 0, 6, 6, 90);
  delay(400);
  lcd.white();
  lcd.setChar(164, 40, 20, 0, 255, 6, 6, 180);
  delay(400);
  lcd.white();
  lcd.string("test", 0, 2, 0, 255, 1, 1, 0);
  lcd.string("test", 0, 10, 0, 255, 2, 2, 0);
  lcd.stringShadow("test", 0, 25, 0, 3, 3, 0);
  lcd.stringShadow("test", 0, 50, 0, 4, 4, 0);
  delay(1300);
  lcd.white();
  lcd.drawRect(20, 10, 60, 60, 3, 0);
  delay(700);
  lcd.fillScreen(161);
  lcd.drawLine(0, 0, 101, 80, 0);
  delay(1000);
  lcd.white();
  lcd.fillRect(20, 10, 60, 60, 2500);
  delay(500);
  lcd.fillScreen(2320);
  lcd.drawCircle(50, 40, 30, 0);
  delay(500);
  lcd.white();
  lcd.fillCircle(50, 40, 30, 2580);
  delay(500);
  lcd.white();
  lcd.drawTriangle(50, 5, 5, 70, 95, 70, 0);
  delay(500);
  lcd.black();
  lcd.string("THE", 30, 10, 1000, 3096, 2, 2, 0);
  lcd.stringShadow("END", 25, 45, 2000, 3, 3, 0);
  delay(2000);
  lcd.white();

  //lcd.fillTriangle(50, 5, 5, 70, 95, 70, 0);  //  - reset WatchDog (HW or SW ????)
  //delay(1000);

  timer.setInterval(1L, drawPixel);
}

void loop ()
{
  timer.run();
}

void drawPixel() {
  static byte x = 0;
  static byte y = 0;
  static int color = 0;
  if (y != 80) {
    for (x = 0; x != 101; x++) {
      lcd.setPixColor(x, y, color);
    }
    if (x >= 101) {
      y++;
      x = 0;
    }
  } else {
    color = color + 10;
    Serial.println(color);
    y = 0; x = 0;
  }
}
