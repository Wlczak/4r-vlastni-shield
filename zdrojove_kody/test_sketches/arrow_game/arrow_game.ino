#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <LiquidCrystal_I2C.h>
#include <wifi_auth.h>
#include <LCDChars.h>

const char* ssid = STASSID;
const char* password = STAPSK;

ESP8266WebServer server(80);
LCDChars lcdChars;
LiquidCrystal_I2C lcd(0x27, 16, 2);


void setup() {

  Serial.begin(115200);
  Serial.println("");
  WiFi.begin(ssid, password);

  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);

  loadCharmap();
  /*lcd.setCursor(0, 0);
  for (int i = 0; i < 8; i++) {
    lcd.write(byte(i));
  }*/
  /*
  lcd.setCursor(6, 0);
  lcd.print("O");
  lcd.setCursor(7, 0);
  lcd.print("k");
  lcd.setCursor(8, 0);
  */
}


// loads all custom characters
void loadCharmap() {
  byte* tmp;
  byte charMap[8];
  for (int i = 0; i < 8; i++) {
    tmp = lcdChars.getChar(i);
    for (int j = 0; j < 8; j++) {
      charMap[j] = tmp[j];
    }
    lcd.createChar(i, charMap);
  }
}

void boot() {
}


int curCol = 0;
int curRow = 0;
bool curStat = false;
long mil = millis();

bool up, down, left, right = false;

void loop() {
  if (millis() - 500 > mil) {
    lcd.setCursor(curCol, curRow);
    if (curStat) {
      lcd.write(byte(2));
      curStat = false;
    } else {
      lcd.write(byte(3));
      curStat = true;
    }
    mil = millis();
  }
  if (Serial.available()) {
    int incomingByte = Serial.read();

    switch (incomingByte) {
      case 49:
        Serial.print("left ");
        player(-1, 0);
        break;
      case 50:
        Serial.print("down ");
        player(0, 1);
        break;
      case 51:
        Serial.print("right ");
        player(1, 0);
        break;
      case 53:
        Serial.print("up ");
        player(0, -1);
        break;
      default:
        Serial.print("undefined ");
        break;
    }
    Serial.print(" | ");
    Serial.println(incomingByte);
  }
}
void player(int x, int y) {
  if (0 <= (x + curCol) && (x + curCol) <= 15) {
    curCol += x;
  }
  if (0 <= (y + curRow) && (y + curRow) <= 1) {
    curRow += y;
  }

  Serial.print("cur col: ");
  Serial.print(curCol);
  Serial.print(" | cur row: ");
  Serial.print(curRow);
  lcd.clear();
}
