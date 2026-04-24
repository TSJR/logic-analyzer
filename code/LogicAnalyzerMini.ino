// ATtiny85 + 74HC165 logic analyzer

#include <TinyWireM.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const uint8_t dataPin = 1   // phys pin 6
const uint8_t clockPin = 3; // phys pin 2
const uint8_t latchPin = 4; // phys pin 3

uint16_t addr; // hex address (4 digits)
uint8_t dat; // hex data (2 digits)

void printHexFixed(uint16_t num, uint8_t digits) { // print hex to lcd
  for (int i = (digits - 1) * 4; i >= 0; i -= 4) {
    lcd.print((num >> i) & 0xF, HEX);
  }
}

void setup() {
  TinyWireM.begin();
  lcd.init();
  lcd.backlight();

  pinMode(dataPin, INPUT_PULLUP);
  pinMode(clockPin, OUTPUT);
  pinMode(latchPin, OUTPUT);

  digitalWrite(clockPin, LOW);
  digitalWrite(latchPin, HIGH);

  lcd.setCursor(0, 0);
  lcd.print("ADDR:0000");
  lcd.setCursor(0, 1);
  lcd.print("DATA:00");
}

void loop() { // DAISY-CHAINED TO READ LSB FIRST
  addr = 0;
  dat = 0;

  // load parallel inputs into 74HC165
  digitalWrite(latchPin, LOW);
  delayMicroseconds(5);
  digitalWrite(latchPin, HIGH);
  delayMicroseconds(5);

  // read first 8 bits (data)
  for (int i = 0; i < 8; i++) {
    dat |= ((uint16_t) digitalRead(dataPin) << i);
    digitalWrite(clockPin, HIGH);
    delayMicroseconds(2);
    digitalWrite(clockPin, LOW);
    delayMicroseconds(2);
  }

  // read next 16 bits (address)
  for (int i = 0; i < 16; i++) {
    addr |= ((uint16_t) digitalRead(dataPin) << i);
    digitalWrite(clockPin, HIGH);
    delayMicroseconds(2);
    digitalWrite(clockPin, LOW);
    delayMicroseconds(2);
  }

  lcd.setCursor(5, 0);
  printHexFixed(addr, 4);
  lcd.setCursor(5, 1);
  printHexFixed(dat, 2);
  delay(150);
}
