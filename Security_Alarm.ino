 int led = 11;               
int sensor = 2;              
int state = LOW;             
int val = 0;   

void setup() {
  pinMode(led, OUTPUT);      
  pinMode(sensor, INPUT);
  Serial.begin(9600);
}

void loop(){
  val = digitalRead(sensor);  
   
  if (val == HIGH) {           
    digitalWrite(led, HIGH);   // turn LED ON to indicate alarm
    delay(100);                
    
    if (state == LOW) {
      Serial.println("Motion detected!"); 
      state = HIGH;       // update variable state to HIGH - this is for like an announcement on maybe the user's phone
    }
  } 
  else {
      digitalWrite(led, LOW); // turn LED OFF to indicate turning off the alarm
      delay(200);            
      
      if (state == HIGH){
        Serial.println("Motion stopped!");
        state = LOW;       // update variable state to LOW
    }
  }
}