#include <LCDI2C_Katakana_Symbols.h>

#include <LiquidCrystal_I2C.h>

//LiquidCrystal_I2C lcd(0x27, 16, 2);
LCDI2C_Katakana_Symbols lcd2(0x27, 16, 2);
char array1[] = "デモネエニホンゴガデキル　";      // první řádek displeje (26 znaků!)
char array2[] = "ﾃﾞﾓ ﾈｴ ﾆﾎﾝｺﾞ ｶﾞ ﾃﾞｷﾙ          ";  // druhý řádek displeje (26 znaků!)
int tim = 500;                                     //délka pauzy
// inicializace knihovny displej

unsigned long etime;
unsigned long etime2;
int counter;
int counter2;
byte smiley[8] = {
  B00000,
  B01010,
  B00000,
  B00000,
  B10001,
  B01110,
  B00000
};
byte test[8] = {
  B00000,
  B11111,
  B00100,
  B00100,
  B00100,
  B00100,
  B00100
};
byte test2[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B11111,
  B00000
};
void setup() {
  lcd2.init();
  etime = millis();
  etime2 = millis();
  counter = 0;
  counter2 = 0;
  lcd2.backlight();
  lcd2.clear();
  lcd2.createChar(0, smiley);
  lcd2.createChar(1, test);
  lcd2.createChar(2, test2);

  // Display the custom character
  lcd2.setCursor(0, 0);
  lcd2.print("Smiley: ");

  lcd2.write(byte(1));
  lcd2.write(byte(2));
  lcd2.write(byte(1));
}

void loop() {
  /*if (millis() - etime > 1000) {
    etime = millis();
    lcd2.setCursor(0, 0);
    lcd2.print("カウター:");
    lcd2.setCursor(6, 0);
    String str = String(counter);
    lcd2.print(str + "セカンド");
    counter++;
  }*/
  if (millis() - etime2 > 30) {
    etime2 = millis();
    lcd2.setCursor(counter2, 1);
    lcd2.print("-");
    lcd2.setCursor(15 - counter2, 1);
    lcd2.print("+");
    if (counter2 == 15) {
      counter2 = 0;
    } else {
      counter2++;
    }
  }
}
