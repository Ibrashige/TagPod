/**
 * Central class that operates the dispenser's data, sensors and actuators.
 * 
 * Relies on the tacuna systems knowledge base:
 https://tacunasystems.com/knowledge-base/load-cell-faq/
 *
 *
 */
 
const float offset = 4.1056; // offset for the load cell to indicate 0 load at 2.5 V
const float vpp = 0.00122070312; // 5V/4096 for ADC conversion
const float totalLoad = 22.68; // maximum load capacity 12.5 pounds
const float a = 1100; // Amplifier Gain
const float s = 0.0008998; // load cell sensitivity 
const float ve = 4.97; //Excitation voltage
float points;
float voltage;
float load;
float numerator; // numerator of load calculation
float voutmax; // denominator of load calculation

#define VOUT  32

void setup() {
  
  Serial.begin(115200);
  Serial.println("Weighing code");
  
}

void loop() {
  calculatevoltage();
  calculateweight();
}

float calculatevoltage(){
  
  points = (float)analogRead(VOUT); 
  voltage = (points / 4095 * 4.9995) ; 
  Serial.print("calculated voltage is:");
  Serial.println(voltage);

  delay(3000);
}

void calculateweight(){
  numerator = totalLoad * (voltage);
  voutmax = s * a * ve;              // raw output voltage to its maximum rated capacity
  load = numerator/voutmax ; // weight in kgs

 if(load >= 0 && load <= 0.05 )
 {
    load = 0;
 }
  Serial.print("calculated weight in kilograms is:");
  Serial.println(load);  

  delay(300);
}
