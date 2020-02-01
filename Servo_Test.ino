

/*------ Arduino Fire Fighting Robot Code----- */

#include <Servo.h>
#include <AFMotor.h>
Servo myservo;
AF_DCMotor motor_r(3);
AF_DCMotor motor_l(4);

//AF_DCMotor pt(2);

int pos = 0;
int turn = 0;
boolean fire = false;

/*-------defining Inputs------*/
#define Left_S A1       // left sensor
#define Right_S A2      // right sensor
#define Forward_S A3    //forward sensor
#define L1 A4
#define L2 A5
#define pump A0



void setup()
{
  motor_l.setSpeed(200);
  motor_r.setSpeed(200);
  //pt.setSpeed(255);
  motor_l.run(RELEASE);
  motor_r.run(RELEASE);
  //pt.setSpeed(RELEASE);



  pinMode(Left_S, INPUT);
  pinMode(Right_S, INPUT);
  pinMode(Forward_S, INPUT);
  pinMode(pump, OUTPUT);

  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);



  myservo.attach(10);
  myservo.write(90);
}

void spin()
{
  int d;
  if (digitalRead(Left_S) == 1) {


    for (pos = 0; pos <= 180; pos += 10) {
      myservo.write(pos);
      delay(250);

      if (digitalRead(Forward_S) == 0  )
      {
        turn = pos;
        if (turn < 90)
        {
          d = (90 - pos) * 8;
          motor_r.run(BACKWARD);
          delay(d);
          motor_r.run(RELEASE);

        }
        else if (turn > 90)
        {
          d = (pos - 90) * 8;
          motor_l.run(BACKWARD);
          delay(d);
          motor_l.run(RELEASE);

        }

        myservo.write(90);
        fire = true;
        break;
      }

      if (digitalRead(Forward_S) == 0  )

      {
        fire = true;
        break;

      }

    }
    motor_r.run(BACKWARD);
    motor_l.run(BACKWARD);
    delay(160);
    motor_r.run(RELEASE);
    motor_l.run(RELEASE);

  }


  if (digitalRead(Left_S) == 1) {

    if (fire == false) {
      for (pos = 180; pos >= 0; pos = pos - 10) {
        myservo.write(pos);
        delay(250);

        if (digitalRead(Forward_S) == 0)
        {
          turn = pos;
          if (turn < 90)
          {
            d = (90 - pos) * 8;
            motor_r.run(BACKWARD);
            delay(d);
            motor_r.run(RELEASE);

          }
          else if (turn > 90)
          {
            d = (pos - 90) * 8;
            motor_l.run(BACKWARD);
            delay(d);
            motor_l.run(RELEASE);

          }

          myservo.write(90);

        }

        if (digitalRead(Forward_S) == 0) {

          fire = true;
          break;
        }

      }


      
      motor_l.run(BACKWARD);
      motor_r.run(BACKWARD);
      delay(160);
      motor_r.run(RELEASE);
      motor_l.run(RELEASE);



    }
  }
}





void put_off_fire()
{
  delay (150);
  motor_r.run(RELEASE);
  motor_l.run(RELEASE);

  digitalWrite(pump, HIGH);
  digitalWrite(L1, HIGH);
  digitalWrite(L2, HIGH);




  delay(500);



  digitalWrite(pump, LOW);
  if (digitalRead(Forward_S) == 1) {
    fire = false;
  }
}

void loop()
{
  //myservo.write(90); //Sweep_Servo();
  if (digitalRead(Left_S) == 1 && digitalRead(Forward_S) == 1) //If Fire not detected all sensors are zero
  {
    spin();

    //Do not move the robot
    //motor_r.run(RELEASE);
    //motor_l.run(RELEASE);

  }

  else if (digitalRead(Forward_S) == 0) //If Fire is straight ahead
  {
    //Move the robot forward
    motor_r.run(BACKWARD);
    motor_l.run(BACKWARD);
    delay(50);

    motor_l.run(RELEASE);

    motor_r.run(RELEASE);

    fire = true;
    put_off_fire();
    
  }

  else if (digitalRead(Left_S) == 0) //If Fire is to the left
  {
    //Move the robot left
    motor_r.run(BACKWARD);
    motor_l.run(BACKWARD);
    delay(200);

    motor_r.run(BACKWARD);
    motor_l.run(FORWARD);
    delay(1000);
    motor_r.run(RELEASE);
    motor_l.run(RELEASE);

  }

  /*else if (digitalRead(Forward_S) == 1)
  {

    //Do not move the robot
    motor_r.run(RELEASE);
    motor_l.run(RELEASE);
  }*/


  delay(300); //Slow down the speed of robot

  while (fire == true)
  {
    put_off_fire();
  }
}
