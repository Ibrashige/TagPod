
float voltage = 3;

void setup() {
  // put your setup code here, to run once:
  pinMode(voltage, OUTPUT);
}

void loop() {
  
  analogWrite(voltage,150);

}
