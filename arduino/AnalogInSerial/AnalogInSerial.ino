const int analogPin0 = A0;
const int analogPin1 = A1;


int sensor0 = 0;
int sensor1 = 0;
float voltage0 = 0;
float voltage1 = 0;
boolean state0 = false;
boolean state1 = false;

void setup() {
  Serial.begin(9600); 
}

void loop() {
  // read the analog in value:
  sensor0 = analogRead(analogPin0);
  sensor1 = analogRead(analogPin1);

  voltage0 = (float)(sensor0 * 5) / 1024;
  voltage1 = (float)(sensor1 * 5) / 1024;

  if(voltage0 >2.5)
  {
    state0=true;
  }
  else
  {
    state0=false;
  }
  if(voltage1 >2.5)
  {
    state1=true;
  }
  else
  {
    state1=false;
  }  

  // print the results to the serial monitor:                       
  Serial.print(state0);            
  Serial.println(state1);   

  delay(20);                     
}
