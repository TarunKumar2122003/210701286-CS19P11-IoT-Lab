#define FLOW_SENSOR_PIN 2
#define ALERT_PIN 11

volatile int flowPulseCount = 0;
unsigned long oldTime = 0;
float flowRate = 0.0;

void flowSensorISR() {
  flowPulseCount++;
}

void setup() {
  pinMode(FLOW_SENSOR_PIN, INPUT);
  pinMode(ALERT_PIN, OUTPUT);
  
  attachInterrupt(digitalPinToInterrupt(FLOW_SENSOR_PIN), flowSensorISR, RISING);
  
  Serial.begin(9600);
  oldTime = millis();
}

void loop() {
  unsigned long currentTime = millis();
  
  
  if (currentTime - oldTime >= 1000) {
    detachInterrupt(digitalPinToInterrupt(FLOW_SENSOR_PIN));
    
    
    flowRate = (float)flowPulseCount / 7.5; 
    Serial.print("Flow Rate: ");
    Serial.print(flowRate);
    Serial.println(" L/min");
    
   
    if (flowRate > 0.5) {
      Serial.println("Possible Leak Detected!");
      digitalWrite(ALERT_PIN, HIGH); 
    } else {
      digitalWrite(ALERT_PIN, LOW); 
    }
     
    
    flowPulseCount = 0;
    oldTime = currentTime;
    
    attachInterrupt(digitalPinToInterrupt(FLOW_SENSOR_PIN), flowSensorISR, RISING);
  }
}