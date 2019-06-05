//include the libary code:

#include <LiquidCrystal.h>
LiquidCrystal lcd(7,8,9,10,11,12);

int adc_id = 0;
int HistoryValue = 0;
char printBuffer[128];
int buzzer =  13;//pin of active buzzer
//initialize the library with the numbers of the interface pins

void setup() {
  Serial.begin(9600);
  pinMode(buzzer, OUTPUT);//initialize the buzzer pin as an output
  lcd.begin(16,2);        //set up the LCD's number of columns and rows
}

void loop() {
  //set the cursor to column 0, line 1
  //line 1 is the second row, since counting begins with 0

  int value = analogRead(adc_id);   //get adc value

  if(((HistoryValue >= value)&& ((HistoryValue - value) > 10)) || ((HistoryValue < value) && ((value - HistoryValue)>10)))
  {
    int i = 0;    //time counting
    lcd.setCursor(10,0);
    lcd.print(" ");
    delay(1000);

    if(value < 200)
    {
      lcd.setCursor(0,0);
      lcd.print("Water Low");       //print a message to the LCD

      delay(800);
      while(i <10 && value < 200){
        i++;
        int n = 10 - i;

        lcd.setCursor(10,0);
        lcd.print(n);
        value =  analogRead(adc_id);
        lcd.setCursor(0,1);
        lcd.print("ADC");
        lcd.print(adc_id);
        lcd.print(": ");
        lcd.print(value);
        digitalWrite(buzzer, HIGH);
        delay(600); //wait for 1s
        digitalWrite(buzzer, LOW);
        delay(400); //wait for 1s
      }
        if ((i == 10) && (value <200)){         //after 10s without being put at right place, loop forever
          lcd.setCursor(0,0);                   //set up the LCD's number of columns and rows
          lcd.print("System failure");          //print a message to LCD
          lcd.setCursor(0,1);
          lcd.print("Device: OFF");
          digitalWrite(buzzer, HIGH);
          while(1){}
          }
    }else{
      lcd.setCursor(0,0);
      lcd.print("System OK");
      lcd.setCursor(0,1);
      lcd.print("ADC");
      lcd.print(adc_id);
      lcd.print(": ");
      lcd.print(value);

      HistoryValue = value;
      }
    }
}
