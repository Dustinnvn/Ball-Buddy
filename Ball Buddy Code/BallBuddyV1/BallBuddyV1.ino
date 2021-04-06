const int stepPinT = 7; 
const int dirPinT = 8; 
const int stepPinX = 5; 
const int dirPinX = 6; 
const int stepPin = 3; 
const int dirPin = 4; 
 
 
int R_EN1 = 13; //Motor 1
int R_PWM1 = 9;
int L_EN1 = 12;
int L_PWM1 = 10;
 
//int R_EN2 = 12; //Motor 2
//nt R_PWM2 = 10;
//int L_EN2 = 13;
//int L_PWM2 = 9;
 
int RELAY = 11; //Relay for Solenoid
 
long inputValue = 0; // store read value
 
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
 
 
 pinMode(R_EN1, OUTPUT);
 pinMode(R_PWM1, OUTPUT);
 pinMode(L_EN1, OUTPUT);
 pinMode(L_PWM1, OUTPUT);
 digitalWrite(R_EN1, HIGH);
 digitalWrite(L_EN1, HIGH);
 
 //pinMode(R_EN2, OUTPUT);
 //pinMode(R_PWM2, OUTPUT);
 //pinMode(L_EN2, OUTPUT);
 //pinMode(L_PWM2, OUTPUT);
 //digitalWrite(R_EN2, HIGH);
 //digitalWrite(L_EN2, HIGH);
 
 pinMode(RELAY, OUTPUT);
}
 
void motors50PWM_ON() {
  int i;
  start=millis();
 
  for (i = 0; i <= 120; i++) {
 
    analogWrite(R_PWM1, i);
    analogWrite(L_PWM1, 0);
 
    //analogWrite(R_PWM2, i);
    //analogWrite(L_PWM2, 0);
 
    delay(100);
  }
 
  analogWrite(R_PWM1, 100);
  analogWrite(L_PWM1, 0);
//  
//  analogWrite(R_PWM2, 100);
//  analogWrite(L_PWM2, 0);
 
  //delay(5000);
    Serial.println("Done 1/2");
 
}
 
void motors50PWM_OFF() {
 
  analogWrite(R_PWM1, 100);
  analogWrite(L_PWM1, 0);
//  
//  analogWrite(R_PWM2, 100);
//  analogWrite(L_PWM2, 0);
 
  //delay(5000);
 
  analogWrite(R_PWM1, 0);
  analogWrite(L_PWM1, 0);
 
  //analogWrite(R_PWM2, 0);
  //analogWrite(L_PWM2, 0);
  finished=millis();
  elapsed=finished-start-1000; //last number needs to change with delay(#)
  //Serial.println("Finished");
  Serial.println(elapsed);
  Serial.println("Done 2/2");
 
 
}
 
void Yaxis() {
  Serial.println("Start Y..");
 
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
        //digitalWrite(ledB,HIGH); //when we reach the desired distance we change directing and give off signal
        Changed = 1; 
        delay(1000);
      }
    else if ((x == 5599) && (Changed == 1)) {
        //digitalWrite(ledR,HIGH);
        Changed = 0;
        delay(1000);
      }    
 
 
    digitalWrite(stepPin,HIGH); 
    delayMicroseconds(1500); 
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(1500);
  }
  finished=millis();
  elapsed=finished-start-1000; //last number needs to change with delay(#)
  //Serial.println("Finished");
  Serial.println(elapsed);
  //Serial.println();
 
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
void Xaxis() {
  Serial.println("Start X..");
 
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
        //digitalWrite(ledB,HIGH); //when we reach the desired distance we change directing and give off signal
        Changed1 = 1; 
      }
    else if ((x == 679) && (Changed == 1)) {
        //digitalWrite(ledR,HIGH);
        Changed1 = 0;
 
      }
 
 
    digitalWrite(stepPinX,HIGH); 
    delayMicroseconds(1500); 
    digitalWrite(stepPinX,LOW); 
    delayMicroseconds(1500);
  }
  finished=millis();
  elapsed=finished-start-1000; //last number needs to change with delay(#)
  //Serial.println("Finished");
  Serial.println(elapsed);
  //Serial.println();
  delay(1000);
}
 
///////////////////////////////////////////////////////////////////////////////////////////////////////
 
void XYaxis() {
 
 
  Serial.println("Start XY..");
 
  if (Changed2 == 0) {                            //////PART 1 LOADING POSITION
    //if in the down left position
    Upcycle();  // GO  UP
    Serial.println("Finished Y... (1/1)");
    Serial.println("Ball Ready to be launched");
    Changed2 = 1;         // Move to the next phase (launch)
  }
  else if (Changed2 == 1) {
 
    Launch();
 
    Changed2 = 2;
  }
  else  {                                       //////PART 2 RECOVER POSITION
    //if in the top left position and launched ball
    Rightcycle();
    Serial.println("Finished X... (1/4)");    
 
    Downcycle();   // GO right - down-left
    Serial.println("Finished Y... (2/4)");
 
    Leftcycle();
    Serial.println("Finished X... (3/4)");
 
    Spins();
    Serial.println("Finished Spin... (4/4)");
 
    Serial.println("Ball Ready to be loaded");
 
    Changed2 = 0;
  }
 
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
 
void Launch() {
 
 
  Serial.println("Start Launch...");
  motors50PWM_ON();
 
  Serial.println("Start Solenoid");
  digitalWrite(RELAY, HIGH);
  delay(500);
  digitalWrite(RELAY, LOW);
  delay(1500);
  motors50PWM_OFF();
}
void Cycle2() {
 
 
  Serial.println("Start XY..");
 
  Upcycle();  // GO  UP
  Serial.println("Finished Y... (1/1)");
  Serial.println("Ball Ready to be launched");
  delay(1000);       // Move to the next phase (launch)
  
  Launch();
 
  delay(1000);
  
  Rightcycle();
  Serial.println("Finished X... (1/4)");    
 
  Downcycle();   // GO right - down-left
  Serial.println("Finished Y... (2/4)");
 
  Leftcycle();
  Serial.println("Finished X... (3/4)");
 
  Spins();
  Serial.println("Finished Spin... (4/4)");
 
  Serial.println("Ball Ready to be loaded");
 
}
 
void Spins() {
  Serial.println("Start..");
  // Makes 200 pulses for making one full cycle rotation
  for(int x = 0; x < 51; x++) { //5600 is one cylce up/down
 
    if (x == 49) {
        //digitalWrite(ledB,HIGH); //when we reach the desired distance we change directing and give off signal
      }
 
 
    digitalWrite(stepPinT,HIGH); 
    delayMicroseconds(3500); 
    digitalWrite(stepPinT,LOW); 
    delayMicroseconds(3500);
  }
  //Serial.println("Finished");
  //Serial.println();
  delay(1000);
 
}
 
void loop() {
 
  if (Serial.available()){
    input = Serial.readStringUntil('\n');         //////////////////////////////////// START POSITION= BOTTOM LEFT ____ LAUNCH POSITION= TOP RIGHT
 
    if (input.equals("g")) {
      Serial.println("start motors");
      //motors50_ONPWM();
    }
    else if (input.equals("d")){           ////   DOWN   = d
      Serial.println("Going down");
      Downcycle();
    }
    else if (input.equals("u")){
      Serial.println("Going up");        ////   UP     = u
      Upcycle();
    }
    else if (input.equals("1")){      ////   RIGHT  = 1
      Serial.println("Going right");
      Rightcycle();
    }
    else if (input.equals("2")){     ////    LEFT   = 2
      Serial.println("Going left");
      Leftcycle();
    }
    else if (input.equals("3")){     ////    TRAY SPIN   = 3
      Serial.println("Spin");
      Spins();
    }
    else if (input.equals("4")){
      Serial.println("XY Cycle");      ////  UP-RIGHT/ DOWN-LEFT    = 4
       XYaxis();
    }
    else if (input.equals("l")){           ////   Launching Sequence   = L
      Serial.println("Launch Cycle");
      Launch();
    }
    
    else if (input.equals("s")){           ////   Launching Sequence   = L
      Serial.println("Launch Cycle");
      Cycle2();
    }
    Serial.println("Finished");
 
  }
 
}
 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
 
 
void XYcycle() {
  XYaxis();
 
  //Serial.println("XY Cylcle  Finished");
}
void Downcycle() {
  Changed = 1;
  Yaxis();
  Changed = 0;
  //Serial.println(" Down Cylcle Finished");
}
void Upcycle() {
  Changed = 0;
  Yaxis();
  Changed = 0;
  //Serial.println(" Up Cylcle Finished");
}
void Rightcycle() {
  Changed1 = 1;
  Xaxis();
  Changed1 = 0;
  //Serial.println(" Right Cylcle Finished");
}
void Leftcycle() {
  Changed1 = 0;
  Xaxis();
  Changed1 = 0;
  //Serial.println(" Left Cylcle Finished");
}