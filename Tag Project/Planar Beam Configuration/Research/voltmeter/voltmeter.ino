#include <SPI.h>
#include <stdlib.h>

// pin definition for the Uno
#define cs   10
#define dc   9
#define rst  8

const float offset = 4.1056; // offset for the load cell to indicate 0 load at 2.5 V
const float vpp = 0.0048828125; // 5V/1024 for ADC conversion
const float totalLoad = 22.68; // maximum load capacity 12.5 pounds
const float a = 1100; // Amplifier Gain
const float s = 0.0008998; // load cell sensitivity 
const float ve = 4.97; //Excitation voltage
float points;
float voltage;
float load;
float numerator; // numerator of load calculation
float voutmax; // denominator of load calculation

char buff[10];


void setup() {
  Serial.begin(115200);
  pinMode(A0, INPUT);
}

void loop() {

  // read normal Arduino value

  int in0 = analogRead(A0);
  float val0 = in0 * 5.0 / 1024.0;

  // read correct supply voltage

  float supply = readVcc() / 1000.0;
  float val0Corrected = supply / 5 * val0;

  float weight = calculateweight(val0Corrected);

 Serial.print("normal arduino value is: ");
 Serial.println(in0);

 Serial.print("correct supply voltage is: ");
 Serial.println(supply);

 Serial.print("corrected arduino value is ");
 Serial.println(val0Corrected);

 Serial.print("calculated weight in kilograms is:");
 Serial.println(load);  

  delay(5000);
}

long readVcc() {
  long result;
  // Read 1.1V reference against AVcc
#if defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
  ADMUX = _BV(REFS0) | _BV(MUX4) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
#elif defined (__AVR_ATtiny24__) || defined(__AVR_ATtiny44__) || defined(__AVR_ATtiny84__)
  ADMUX = _BV(MUX5) | _BV(MUX0);
#elif defined (__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__)
  ADMUX = _BV(MUX3) | _BV(MUX2);
#else
  ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
#endif
  delay(2); // Wait for Vref to settle
  ADCSRA |= _BV(ADSC); // Convert
  while (bit_is_set(ADCSRA, ADSC));
  result = ADCL;
  result |= ADCH << 8;
  result = 1126400L / result; // Calculate Vcc (in mV); 1126400 = 1.1*1024*1000
  return result;
}

float calculateweight(float val0Corrected){
  numerator = totalLoad * (val0Corrected);
  voutmax = s * a * ve;              // raw output voltage to its maximum rated capacity
  load = numerator/voutmax - 4.15; // weight in kgs

 if(load >= 0 && load <= 0.05 )
 {
    load = 0;
 }
  return load;
}
