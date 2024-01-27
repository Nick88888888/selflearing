
char c[20];
int i=0,openmv_speed1=0,openmv_heanding=100;
int change=1,a=0;//找負號change是用來變號的
int find_value=0;

#include <AFMotor.h>
#include <string.h>
#include <Servo.h> 
AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);
Servo servo1;//控制轉向

void setup() {
  Serial.begin(19200);           // set up Serial library at 9600 bps
  Serial.println("Motor test!");
  servo1.attach(9);
  
  // turn on motor
  motor1.setSpeed(200);
  motor1.run(RELEASE);
  motor2.setSpeed(200);
  motor2.run(RELEASE);
  motor3.setSpeed(200);
  motor3.run(RELEASE);
  motor4.setSpeed(200);
  motor4.run(RELEASE); 
  servo1.write(100);

 
}

void loop() {

   if (Serial.available()) 
   {   
       c[i] = Serial.read();
       if(c[i]==10)
       {
        openmv_speed1=0;openmv_heanding=0;
        i=0;
        change=1;

        for(int j=0;j<=strlen(c);j++)
        {
          if(c[j]=='-')
          {
            change=-1;
          }
          
          Serial.println(c[j]);
        }
   
        int w=0;
         while(c[w]!=',')//找逗號
         {
            w++;
         }
         for(int k=1;k<w;k++)//逗號前加
         {
            openmv_speed1 = openmv_speed1*10+(c[k]-48);
         } 
         int r=0;
         while(c[r]!='E')//找E
         {
            r++;
         }
         for(int k=w+1;k<r;k++)
         {
            openmv_heanding = openmv_heanding*10+(c[k]-48);
         }
       
         Serial.println(openmv_speed1*change);
         Serial.println(change);
         Serial.println(openmv_heanding);
         
        
       }
       else
       {
        i++;
        
       }
       Serial.write(c[i]);
    }
    if (change==1)
      {
        motor1.run(FORWARD);
        motor2.run(FORWARD);
        motor3.run(BACKWARD);
        motor4.run(BACKWARD);
      }
    else
      {
        motor1.run(BACKWARD);
        motor2.run(BACKWARD);
        motor3.run(FORWARD);
        motor4.run(FORWARD);
      }
      
      motor1.setSpeed(openmv_speed1);
      motor2.setSpeed(openmv_speed1);   
      motor3.setSpeed(openmv_speed1);
      motor4.setSpeed(openmv_speed1); 
      servo1.write(openmv_heanding);
   

   
}
void stop1()
{ 
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
  motor1.setSpeed(60);
  motor2.setSpeed(60);   
  motor3.setSpeed(60);
  motor4.setSpeed(60); 
 
}
