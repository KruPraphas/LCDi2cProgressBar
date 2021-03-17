// LCD i2c Library https://github.com/johnrickman/LiquidCrystal_I2C

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2);
byte zero[] = {
  B11111,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B11111
};
byte one[] = {
  B11111,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B11111
};

byte two[] = {
  B11111,
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
  B11111
};

byte three[] = {
  B11111,
  B11100,
  B11100,
  B11100,
  B11100,
  B11100,
  B11100,
  B11111
};

byte four[] = {
  B11111,
  B11110,
  B11110,
  B11110,
  B11110,
  B11110,
  B11110,
  B11111
};

byte five[] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};
int randNumber;
void setup() {

  // initialize the LCD and allocate the 5 arrays to a number.
  lcd.init();
  lcd.createChar(0, zero);
  lcd.createChar(1, one);
  lcd.createChar(2, two);
  lcd.createChar(3, three);
  lcd.createChar(4, four);
  lcd.createChar(5, five);
  lcd.backlight();
}

void loop() {
  for (int i = 0; i < 100; i += 2)
  {
    lcd.setCursor(0, 0);
    lcd.print(i);
    lcd.print("   ");
    updateProgressBar(i, 100, 1);
    delay(50);
  }
  delay(1000);
  for (int i = 100; i > 0; i -= 2)
  {
    lcd.setCursor(0, 0);
    lcd.print(i);
    lcd.print("   ");
    updateProgressBar(i, 100, 1);
    delay(50);
  }
  delay(1000);
  for (int i = 0; i < 5; i++)
  {
    randNumber = random(1000);
    lcd.setCursor(0, 0);
    lcd.print(randNumber);
    lcd.print("   ");
    updateProgressBar(randNumber, 1000, 1);
    delay(250);
  }
  delay(1000);
}
/*
   This is the method that does all the work on the progress bar.
   Please feel free to use this in your own code.
   @param count = the current number in the count progress
   @param totalCount = the total number to count to
   @param lineToPrintOn = the line of the LCD to print on.

   Because I am using a 16 x 2 display, I have 16 characters.  
   Each character has 5 sections.  Therefore, I need to declare the number 80.0.
   If you had a 20 x 4 display, you would have 25 x 5 = 100 columns.  Therefore you would change the 80.0 to 100.0
   You MUST have the .0 in the number.  If not, it will be treated as an int and will not calculate correctly

   The factor is the totalCount/divided by the number of columns.
   The percentage is the count divided by the factor (so for 80 columns, this will give you a number between 0 and 80)
   the number gives you the character number (so for a 16 x 2 display, this will be between 0 and 16)
   the remainder gives you the part character number, so returns a number between 0 and 4

   Based on the number and remainder values, the appropriate character is drawn on the screen to show progress.
   This will work with fluctuating values!
*/
void updateProgressBar(unsigned long count, unsigned long totalCount, int lineToPrintOn)
{
  double factor = totalCount / 80.0;        //See note above!
  int percent = (count + 1) / factor;
  int number = percent / 5;
  int remainder = percent % 5;
  if (number > 0)
  {
    for (int j = 0; j < number; j++)
    {
      lcd.setCursor(j, lineToPrintOn);
      lcd.write(5);
    }
  }
  lcd.setCursor(number, lineToPrintOn);
  lcd.write(remainder);
  if (number < 16)
  {
    for (int j = number + 1; j <= 16; j++)
    {
      lcd.setCursor(j, lineToPrintOn);
      lcd.write(0);
    }
  }
}
