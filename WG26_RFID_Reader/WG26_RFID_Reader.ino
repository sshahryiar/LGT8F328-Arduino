#include "I2C_LCD.h"


#define D0_Pin  4   // Pin 4 = PD4 = PCINT20
#define D1_Pin  5   // Pin 5 = PD5 = PCINT21


I2C_LCD display;


char buffer[20];
volatile uint8_t count = 0;
volatile uint32_t card_number = 0;
volatile uint32_t facility_code = 0;
volatile uint32_t raw_card_data = 0;


void setup(void) 
{
  pinMode(D0_Pin, INPUT_PULLUP);
  pinMode(D1_Pin, INPUT_PULLUP);
  pinMode(13, OUTPUT);
  // Enable PCINT for PD4 and PD5 (PCINT20 and PCINT21)
  PCICR  |= (1 << PCIE2); // Enable PORTD group (PCINT[23:16])
  PCMSK2 |= (1 << PCINT20) | (1 << PCINT21); // Enable PD4, PD5

  display.begin();
  display.clear_home();
  display.text(0, 0, "Facility:");
  display.text(0, 1, "Card I.D:");
}

void loop(void) 
{
  if(count >= 25) 
  {
    digitalWrite(13, HIGH);
    
    card_number = (raw_card_data & 0xFFFF);
    facility_code = (0xFF & (raw_card_data >> 0x10));

    sprintf(buffer, "%03lu ", facility_code);
    display.text(10, 0, buffer);

    sprintf(buffer, "%06lu ", card_number);
    display.text(10, 1, buffer);

    count = 0;
    raw_card_data = 0;
    delay(600);

    digitalWrite(13, LOW);
  }
}

// ISR for PCINT on PORTD (PCINT2_vect)
ISR(PCINT2_vect) 
{
  bool D0_state = digitalRead(D0_Pin);
  bool D1_state = digitalRead(D1_Pin);

  if((D0_state == LOW) && (D1_state == HIGH)) 
  {
    // D0 active
    digitalWrite(13, LOW);
    raw_card_data <<= 1;
    count++;
  } 
  
  else if((D0_state == HIGH) && (D1_state == LOW)) 
  {
    // D1 active
    digitalWrite(13, HIGH);
    raw_card_data <<= 1;
    raw_card_data |= 1;
    count++;
  }
}
