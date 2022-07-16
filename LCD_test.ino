#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()
{
  lcd.init();                      // initialize the lcd 
  lcd.backlight();
}


void loop()
{
    Scrolling_text("I Am Shovan Sundar Paul ");
}


void Scrolling_text(String IC_name){
    int i,j=0;
    for( i=0; i<IC_name.length(); i++){
        if(i<15){
            lcd.print(IC_name.charAt[i]);
            delay(150);
        }
        else{
            for(i=16;i<IC_name.length(); i++){
                j++;
                lcd.setCursor(0,0);
                lcd.print(IC_name.substring(j, j+16));
                delay(250);
            }
        }
    }
    delay(3000);

}