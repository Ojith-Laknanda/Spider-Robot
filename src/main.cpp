#include<Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <Arduino.h>

Adafruit_PWMServoDriver driver=Adafruit_PWMServoDriver();
int max =410;//410
int min=190;//205

int middle=310;
int middle_SP=200;
int count=0;

int state=-1;

void setup() {
  Wire.begin();
  driver.begin();
  Serial.begin(115200); 
  driver.setPWMFreq(50);  // Set PWM frequency to 50Hz (for servos)

  initPoint();
  delay(1000);
  justStand();
  delay(2000);
  walk();
  

}

void loop() {
//  justStand();
jump();
 
}

/*
 Serial.println("ready");
    if (Serial.available() > 0) {
    // read the incoming byte:
    
    String input = Serial.readStringUntil('\n');
    state=input.toInt();

    // say what you got:
    // Serial.print("I received: ");
    Serial.println(state);
  }

    switch(state){
      case 1:justStand();break;
      case 2:walk();break;
      case 3: byee_calibrate_right(2,max,middle,3,min,0,max);break;
      case 4: jump();
      default: initPoint();break;
    }
  
  delay(100);
*/

void initPoint(){
  for(int i=0;i<=5;i++){// right
    driver.setPWM(i, 0, min);//channel number, start pos ,pwm 
    // delay(200);
  }
  

  for(int i=6;i<=11;i++){//left
    driver.setPWM(i, 0, max);//channel number, start pos ,pwm 
    // delay(200);
  }
}

void justStand(){
  Serial.println("just stand");
  for(int i=2;i<5;i++){
    driver.setPWM(i, 0, middle);//channel number, start pos ,pwm 
    // delay(200);
  }
  driver.setPWM(5, 0, min);
  for(int i=0;i<2;i++){
    driver.setPWM(i, 0, middle_SP);//channel number, start pos ,pwm 
    // delay(200);
  }
  

  for(int i=6;i<=11;i++){
    if(i!=8){
      driver.setPWM(i, 0, middle);//channel number, start pos ,pwm 
    }else{continue;}
    // delay(200);
  }
  driver.setPWM(8, 0, max);
}


void walk() {
    Serial.println("walked");
    // Step 1: Move right back leg (hip 5, knee 4)
    moveLeg(5, middle, 4, min);  // Lift and extend
    // delay(1000);

    // Step 2: Move right front leg (hip 2, knee 3)
    moveLeg(2, max, 3, min);  // Lift and extend
    // delay(1000);

    // Step 3: Move left back leg (hip 8, knee 9)
    moveLeg(8, middle, 9, max);  // Lift and extend
    // delay(1000);
   
    // Step 4: Move left front leg (hip 7, knee 6)
    moveLeg(7, min, 6, max);  // Lift and extend
    // delay(300); 

    // Return to standing position
    justStand();
    delay(100);
    
}


void moveLeg(int hip,int hip_val,int knee, int knee_val) {
  driver.setPWM(knee, 0, knee_val);
  delay(150);
  driver.setPWM(hip, 0, hip_val);
  delay(150);
  driver.setPWM(knee, 0,middle);
  delay(150);
}

void byee_calibrate_right(int hip,int hip_val,int hip_val_end,int knee, int knee_val,int ankle, int ankle_val) {
  Serial.println("say bye");
  // justStand();
  //  delay(100);

  
  driver.setPWM(7, 0, min);//channel number, start pos ,pwm 
   delay(400);
  driver.setPWM(5, 0, middle);//channel number, start pos ,pwm 
  

  delay(100);
  
  driver.setPWM(knee, 0, knee_val);
  driver.setPWM(ankle, 0, ankle_val);
  delay(150);
  driver.setPWM(hip, 0,hip_val);
  delay(150);
  driver.setPWM(hip, 0,hip_val_end);
  delay(150);
    
}

void jump(){
  Serial.println("jump");
  Serial.println(" reading to jump pos");

  driver.setPWM(2, 0, max);
  for(int i=3;i<5;i++){
    driver.setPWM(i, 0, middle);//channel number, start pos ,pwm 
    // delay(200);
  }
  driver.setPWM(5, 0, min);
  for(int i=0;i<2;i++){
    driver.setPWM(i, 0, middle_SP);//channel number, start pos ,pwm 
    // delay(200);
  }
  

  
  for(int i=9;i<=11;i++){
      driver.setPWM(i, 0, middle);//channel number, start pos ,pwm 
  }
  
  driver.setPWM(7, 0, min);
  driver.setPWM(6, 0, middle);
  driver.setPWM(8, 0, max);

  delay(2000);
  // Serial.println("knees down");
  // driver.setPWM(3, 0, max);
  // driver.setPWM(4, 0, max);

  // driver.setPWM(6, 0, min);
  // driver.setPWM(9, 0, min);
  // delay(100);

  Serial.println("anckel ready");
  driver.setPWM(10, 0, max);
  driver.setPWM(11, 0, max);

  driver.setPWM(0, 0, min);
  driver.setPWM(1, 0, min);
  delay(100);

  // driver.setPWM(10, 0, min);
  // driver.setPWM(11, 0, min);

  // driver.setPWM(0, 0, max);
  // driver.setPWM(1, 0, max);
  delay(100);

}
