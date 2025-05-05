// all of these ints that will never hold > 255 should be byte variables.

int IR_SensorR=2;
int IR_SensorL=4;

int ENA_LeftMotorSpeed=7;
int IN1_LeftMotorBkwd=9;    //Left Bkwd Clockwise
int IN2_LeftMotorFwd=10;    //Left Fwd Anti-Clockwise
int IN3_RightMotorBkwd=11;    //Right Bkwd Clockwise
int IN4_RightMotorFwd=5;    //Right Fwd Anti-Clockwise
int ENB_LeftMotorSpeed=6;

// declare once, not inside of loop()
    int RunSpeed = 120;
    int TurnSpeed = 140;
    int StopSpeed = 0;
//    int dtime = 5000;    // 5 seconds? Ignore sensors for 5 whole seconds??
//    int dtimer = 2000;   // is this ever used?
    int dtime = 10;    // why is there any delay anyway?


unsigned long startWait, waitWait;  // these are replacing those delay() calls


void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);  //  better to use 115200 or faster to clear the serial output buffer quicker

pinMode(IR_SensorL,INPUT);
pinMode(IR_SensorR,INPUT);


pinMode(ENA_LeftMotorSpeed,OUTPUT);
pinMode(IN1_LeftMotorBkwd,OUTPUT);
pinMode(IN2_LeftMotorFwd,OUTPUT);
pinMode(IN3_RightMotorBkwd,OUTPUT);
pinMode(IN4_RightMotorFwd,OUTPUT);
pinMode(ENB_LeftMotorSpeed,OUTPUT);


  digitalWrite(IN1_LeftMotorBkwd,0);
  digitalWrite(IN2_LeftMotorFwd,0);
  digitalWrite(IN3_RightMotorBkwd,0);
  digitalWrite(IN4_RightMotorFwd,0);
 
}

void loop() {
  //1 means IR light OFF, On Black Tape, o/p=1 - LED is OFF in Code
  //0 means IR light ON, NOT on Black Tape, o/p=0 - LED is ON in code
  //RED LED is LEFT IR
  //GREEN LED RIGHT IR
 
  // put your main code here, to run repeatedly:
Serial.println("IR_SensorL:");
Serial.println(digitalRead(IR_SensorL));
Serial.println("IR_SensorR:");
Serial.println(+digitalRead(IR_SensorR));
Serial.println("...............");

    RunSpeed = 120;
    TurnSpeed = 140;
    StopSpeed = 0;
   
if ( waitWait > 0 )
{
  if ( millis() - startWait >= waitWait )
  {
    waitWait = 0; // next time through, read the sensors, etc
  }
}
else
{
  if(digitalRead(IR_SensorL) == 1 & digitalRead(IR_SensorR) == 1)  //STOP
  {
    Serial.println("BOTH Left and Right Side ON Black Line, Red and Green LED OFF : STOP");
   
    //STOP all Motors
    analogWrite(ENA_LeftMotorSpeed,StopSpeed);
    analogWrite(ENB_LeftMotorSpeed,StopSpeed);
   
    digitalWrite(IN1_LeftMotorBkwd,0);
    digitalWrite(IN2_LeftMotorFwd,0);    //Left STOP
    digitalWrite(IN3_RightMotorBkwd,0);
    digitalWrite(IN4_RightMotorFwd,0);    //Right STOP

//    delay(dtime);
    startWait = millis();
    waitWait = dtime; // next bunch of times through, wait
   }
  else if(digitalRead(IR_SensorL) == 0 & digitalRead(IR_SensorR) == 1 )  //Turn Right
  {
    Serial.println("Right Side ON Black Line, Green LED OFF : Turn Left Wheel");

   
    analogWrite(ENA_LeftMotorSpeed,TurnSpeed);
    analogWrite(ENB_LeftMotorSpeed,RunSpeed);
   
    digitalWrite(IN1_LeftMotorBkwd,0);
    digitalWrite(IN2_LeftMotorFwd,1);    //Left Fwd Clockwise
    digitalWrite(IN3_RightMotorBkwd,1);    //Right Bkwd AntiClockwise   
    digitalWrite(IN4_RightMotorFwd,0);
//    delay(dtime);
    startWait = millis();
    waitWait = dtime; // next bunch of times through, wait
  }
  else if(digitalRead(IR_SensorL) == 1 & digitalRead(IR_SensorR) == 0 )  //Turn Left
  {
    Serial.println("Left Side ON Black Line, Red LED OFF : Turn Right Wheel");


    analogWrite(ENA_LeftMotorSpeed,RunSpeed);
    analogWrite(ENB_LeftMotorSpeed,TurnSpeed);
   
    digitalWrite(IN1_LeftMotorBkwd,1);    //Left Bkwd AntiClockwise
    digitalWrite(IN2_LeftMotorFwd,0);
    digitalWrite(IN3_RightMotorBkwd,0);
    digitalWrite(IN4_RightMotorFwd,1);    //Right Fwd Clockwise   
//    delay(dtime);
    startWait = millis();
    waitWait = dtime; // next bunch of times through, wait
  }
 else //Go Straight
  {
    Serial.println("BOTH Left and Right Side NOT on Black Line, Red and Green LED ON : Go Straight");

    analogWrite(ENA_LeftMotorSpeed,RunSpeed);
   
    analogWrite(ENB_LeftMotorSpeed,RunSpeed);
    //RUN All Motors
    digitalWrite(IN1_LeftMotorBkwd,0);
    digitalWrite(IN2_LeftMotorFwd,1);    //Left Fwd Clockwise
    digitalWrite(IN3_RightMotorBkwd,0);
    digitalWrite(IN4_RightMotorFwd,1);    //Right Fwd Clockwise 
//    delay(dtimer);
    startWait = millis();
    waitWait = dtime; // next bunch of times through, wait
  }
 }
}

