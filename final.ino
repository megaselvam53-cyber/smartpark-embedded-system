#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);

Servo myservo;

#define ir_enter 3
#define ir_back 2

#define ir_car1 8
#define ir_car2 9
#define ir_car3 10
#define ir_car4 11
#define ir_car5 12
#define ir_car6 13

int S1, S2, S3, S4, S5, S6;
int slot = 0;

void setup() {
  Serial.begin(9600);

  pinMode(ir_car1, INPUT);
  pinMode(ir_car2, INPUT);
  pinMode(ir_car3, INPUT);
  pinMode(ir_car4, INPUT);
  pinMode(ir_car5, INPUT);
  pinMode(ir_car6, INPUT);

  pinMode(ir_enter, INPUT);
  pinMode(ir_back, INPUT);

  myservo.attach(7);
  myservo.write(90);   // gate closed

  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print(" Car Parking ");
  delay(2000);
  lcd.clear();
}

void loop() {

  Read_Sensor();
  slot = S1 + S2 + S3 + S4 + S5 + S6;

  // LCD Update
  lcd.setCursor(0, 0);
  lcd.print("Filled Slot: ");
  lcd.print(slot);
  lcd.print("/6 ");

  lcd.setCursor(0, 1); lcd.print(S1 ? "S1:Fill " : "S1:Empty");
  lcd.setCursor(10, 1); lcd.print(S2 ? "S2:Fill " : "S2:Empty");

  lcd.setCursor(0, 2); lcd.print(S3 ? "S3:Fill " : "S3:Empty");
  lcd.setCursor(10, 2); lcd.print(S4 ? "S4:Fill " : "S4:Empty");

  lcd.setCursor(0, 3); lcd.print(S5 ? "S5:Fill " : "S5:Empty");
  lcd.setCursor(10, 3); lcd.print(S6 ? "S6:Fill " : "S6:Empty");

  // ENTRY GATE
  if (digitalRead(ir_enter) == LOW && slot < 6) {
    Serial.println("Car Entered");
    myservo.write(0);          // OPEN GATE
    delay(3000);
    myservo.write(90);         // CLOSE GATE
  }

  if (slot == 6) {
    lcd.setCursor(0, 0);
    lcd.print("Parking Full      ");
    delay(1000);
  }

  // EXIT GATE
  if (digitalRead(ir_back) == LOW) {
    Serial.println("Car Exited");
    myservo.write(0);          // OPEN GATE
    delay(3000);
    myservo.write(90);         // CLOSE GATE
  }

  delay(200);
}

void Read_Sensor() {
  S1 = !digitalRead(ir_car1);
  S2 = !digitalRead(ir_car2);
  S3 = !digitalRead(ir_car3);
  S4 = !digitalRead(ir_car4);
  S5 = !digitalRead(ir_car5);
  S6 = !digitalRead(ir_car6);
}
