#define infrared_right number // the infrared sensor need a PWM or analog port
#define infrared_left number 

#define motor_right number // motors need a PWM port
#define motor_right number

#define value_black number // maximun value to black light refraction
#define value_white number // minimun value to white light refraction

//var's
int left_sensor=0;
int right_sensor=0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(infrared_right,INPUT);
  pinMode(infrared_left,INPUT);
  pinMode(motor_right,OUTPUT);
  pinMode(motor_left,OUTPUT);

}

void loop() {
  //read infrared sensors
  left_sensor = read_sensor(infrared_left);
  right_sensor = read_sensor(infrared_right);
  
  if (right_sensor < value_black && left_sensor < value_black)
  {
    motor_speed(250,250); // 250 a max power if connected a  pwm port
  }
  else {
        if (right_sensor > value_white && left_sensor > value_white)
        {
            motor_speed(250,250);
        }
          else 
          {
            if( left_sensor > value_white && right_sensor < value_black )
            {
            motor_speed(0,250); // curve to left // need a ideal value # left motor stop and right motor run
            } 
            else 
            {
             motor_speed(250,0); // curve to right // need a ideal value # left motor run and right motor stop
            }
          }
    } // need check othwewise cases ?????????
}

float read_sensor(int sensor_name){
  pass function
  
 
  
  return result
  }

void motor_speed(int left_motor, int right_motor){
  pass function
  }
