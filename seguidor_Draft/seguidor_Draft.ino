#define infrared_right set_Arduino_port // the infrared sensor need a PWM or analog port
#define infrared_left set_Arduino_port 

#define h_bridge_right set_Arduino_port// H bridge need a PWM port to control the power of motors 
#define h_bridge_left set_Arduino_port

#define motor_right_input_1 set_Arduino_port
#define motor_right_input_2 set_Arduino_port
#define motor_left_input_1 set_Arduino_port
#define motor_left_input_2 set_Arduino_port

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
  pinMode(h_bridge_right,OUTPUT);
  pinMode(h_bridge_left,OUTPUT);

}

void loop() {
  //read infrared sensors
  left_sensor = read_sensor(infrared_left);
  right_sensor = read_sensor(infrared_right);

  
  //conditions
  if (right_sensor < value_black && left_sensor < value_black)
  {
    motor_speed(250,250); // 250 a max power if connected in pwm port
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
  
  return analogRead(sensor_name);
  
  
  }

void motor_speed(int left_motor, int right_motor){ 
  // as this code is to Seguidor (follow ??? ) it has no re option

  // set power
  analogWrite(h_bridge_left,left_motor);
  analogWrite(h_bridge_right,right_motor);

  // set motor sense // Really need this ??? could set in start function (create) to optimize code ??
  digitalWrite(motor_left_input_1,HIGH);
  digitalWrite(motor_left_input_2,LOW);
  digitalWrite(motor_right_input_1,HIGH);
  digitalWrite(motor_right_input_2,LOW);
   
  
  }
