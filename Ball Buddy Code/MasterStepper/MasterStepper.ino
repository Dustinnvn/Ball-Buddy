const int stepPinT = 7; 
const int dirPinT = 8; 
const int stepPinX = 5; 
const int dirPinX = 6; 
const int stepPin = 3; 
const int dirPin = 4; 
const int ledG = 13;
const int ledY = 12;
const int ledB = 11;
const int ledR = 10;
      
      int Changed = 0; //for decieding direction of Y axis
      int Changed1 = 0; //for decieding direction of X axis
      int Changed2 = 0; //for decieding direction of XY Cycle 
unsigned long start, finished, elapsed;
      String input;
/////////////////////////////////////////////////


void setup() {
  // Sets the two pins as Outputs
  Serial.begin(9600); //open the serial port at 9600 bps
  pinMode(stepPinT,OUTPUT); 
  pinMode(dirPinT,OUTPUT);
  pinMode(stepPinX,OUTPUT); 
  pinMode(dirPinX,OUTPUT);
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);
  pinMode(ledG,OUTPUT);
  pinMode(ledY,OUTPUT);
  pinMode(ledB,OUTPUT);
  pinMode(ledR,OUTPUT);
}
void loop() {

  if (Serial.available()){
    input = Serial.readStringUntil('\n');

    if (input.equals("d")){           ////   DOWN   = d
      Serial.println("go down");
      Downcycle();
    }
    else if (input.equals("u")){
      Serial.println("go up");        ////   UP     = u
      upcycle();
    }
    else if (input.equals("1")){      ////   RIGHT  = 1
      Serial.println("right");
      Rightcycle();
    }
    else if (input.equals("2")){     ////    LEFT   = 2
      Serial.println("left");
      Leftcycle();
    }
    else if (input.equals("3")){     ////    TRAY SPIN   = 3
      Serial.println("Spin");
      Spins();
    }
    else {
      Serial.println("XY Cycle");      ////  UP-RIGHT/ DOWN-LEFT    = entr
       XYaxis();
    }
  }

  
}
  //delay(1000); // One second delay

void Yaxis() {
  Serial.println("Start..");
  start=millis();
  if (Changed == 0) {
    digitalWrite(dirPin,HIGH);  //Enables the motor to move in a particular direction
  }
  if (Changed == 1) {
    digitalWrite(dirPin,LOW);
  }
  // Makes 200 pulses for making one full cycle rotation
  for(int x = 0; x < 5600; x++) { //5600 is one cylce up/down

    if ((x == 5599) && (Changed == 0)) {
        digitalWrite(ledB,HIGH); //when we reach the desired distance we change directing and give off signal
        Changed = 1; 
        delay(1000);
      }
    else if ((x == 5599) && (Changed == 1)) {
        digitalWrite(ledR,HIGH);
        Changed = 0;
        delay(1000);
      }    
    digitalWrite(ledB,LOW);
    digitalWrite(ledR,LOW);
    
    digitalWrite(stepPin,HIGH); 
    delayMicroseconds(1500); 
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(1500);
  }
  finished=millis();
  elapsed=finished-start-1000; //last number needs to change with delay(#)
  Serial.println("Finished");
  Serial.print(elapsed);
  Serial.println();
 
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
void Xaxis() {
  Serial.println("Start..");
  start=millis();
  if (Changed1 == 0) {
    digitalWrite(dirPinX,HIGH);  //Enables the motor to move in a particular direction
  }
  if (Changed1 == 1) {
    digitalWrite(dirPinX,LOW);
  }
  // Makes 200 pulses for making one full cycle rotation
  for(int x = 0; x < 710; x++) { //5600 is one cylce up/down

    if ((x == 679) && (Changed == 0)) {
        digitalWrite(ledB,HIGH); //when we reach the desired distance we change directing and give off signal
        Changed1 = 1; 
      }
    else if ((x == 679) && (Changed == 1)) {
        digitalWrite(ledR,HIGH);
        Changed1 = 0;
        
      }
      
    digitalWrite(ledB,LOW);
    digitalWrite(ledR,LOW);
    
    digitalWrite(stepPinX,HIGH); 
    delayMicroseconds(1500); 
    digitalWrite(stepPinX,LOW); 
    delayMicroseconds(1500);
  }
  finished=millis();
  elapsed=finished-start-1000; //last number needs to change with delay(#)
  Serial.println("Finished");
  Serial.print(elapsed);
  Serial.println();
  delay(1000);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////

void XYaxis() {
  int spn = 0;
  Serial.println("Start..");
  if (Changed2 == 0) {           //if in the down left position
    digitalWrite(dirPinX,LOW);  // GO Right - UP
    digitalWrite(dirPin,HIGH);
    Changed2 = 1;
  }
  else  {
    digitalWrite(dirPinX,HIGH);  //if in the top right position
    digitalWrite(dirPin,LOW);   // GO left  - down
    spn = 1;
    Changed2 = 0;
  }

/////////////////////////////////// Y MOVE 1st
  for(int y = 0; y < 5600; y++) { //5600 is one cylce up/down

    if ((y == 5599) && (Changed == 0)) {
        digitalWrite(ledB,HIGH); 
      }
    else if ((y == 5599) && (Changed == 1)) {
        digitalWrite(ledR,HIGH);
      }    
    digitalWrite(ledB,LOW);
    digitalWrite(ledR,LOW);
    
    digitalWrite(stepPin,HIGH); 
    delayMicroseconds(1500); 
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(1500);
  }
  delay(1000);
  Serial.println("Finished Y... (1/2)");
  Serial.println();



  /////////////////////////////////// Tray spin only if changed2 == 1
  if (spn == 1) {
    Spins();
    Serial.println("Finished Spin...(?/2)");
    Serial.println();
  }
  
  /////////////////////////////////// X MOVE 2nd
  for(int x = 0; x < 680; x++) { //650 is one cylce left/right

    if ((x == 679) && (Changed1 == 0)) {
        digitalWrite(ledB,HIGH); //when we reach the desired distance we change directing and give off signal 
      }
    else if ((x == 679) && (Changed1 == 1)) {
        digitalWrite(ledR,HIGH);
      }
      
    digitalWrite(ledB,LOW);
    digitalWrite(ledR,LOW);
    
    digitalWrite(stepPinX,HIGH); 
    delayMicroseconds(1500); 
    digitalWrite(stepPinX,LOW); 
    delayMicroseconds(1500);
  }
  
  Serial.println("Finished X... (2/2)!!");
  Serial.println();
   
  Changed == 0;
  Changed1 == 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Spins() {
  Serial.println("Start..");
  // Makes 200 pulses for making one full cycle rotation
  for(int x = 0; x < 51; x++) { //5600 is one cylce up/down

    if (x == 49) {
        digitalWrite(ledB,HIGH); //when we reach the desired distance we change directing and give off signal
      }
    
    digitalWrite(ledB,LOW);
    digitalWrite(ledR,LOW);
    
    digitalWrite(stepPinT,HIGH); 
    delayMicroseconds(3500); 
    digitalWrite(stepPinT,LOW); 
    delayMicroseconds(3500);
  }
  Serial.println("Finished Spin.");
  Serial.println();
  delay(1000);
 
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////


void XYcycle() {
  XYaxis();
  
  Serial.println("XY Cylcle Finished");
}
void Downcycle() {
  Changed = 1;
  Yaxis();
  Changed = 0;
  Serial.println(" D Cylcle Finished");
}
void upcycle() {
  Changed = 0;
  Yaxis();
  Changed = 0;
  Serial.println(" U Cylcle Finished");
}
void Rightcycle() {
  Changed1 = 1;
  Xaxis();
  Changed1 = 0;
  Serial.println(" R Cylcle Finished");
}
void Leftcycle() {
  Changed1 = 0;
  Xaxis();
  Changed1 = 0;
  Serial.println(" L Cylcle Finished");
}
