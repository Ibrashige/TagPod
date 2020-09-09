double output;
double load = 26;

void setup() {
  Serial.begin(115200);
  pinMode(load,INPUT);

}

void loop() {
  output = analogRead(load);
  Serial.println(output);

delay(3000);
}
