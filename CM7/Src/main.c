#include"main.h"


#define FRONT_LEFT_MOTOR 0
#define FRONT_RIGHT_MOTOR 1


float errorcheck ;
int32_t pidspeed;

#define LIM_MAX_INT 3375468.0f
#define LIM_MIN_INT -3375468.0f
#define MAX_VRPM 6800
#define MAX_PWM 65535

struct PIDControl {
  float kp;
  float ki;
  float kd;
  float integral;
  float previousError;
  uint8_t state;
};


struct PIDControl PIDControllers[] = {
  {1.0f, 0.005f, 2.08f,0.0f, 0.0f,0},// PID for Front Left Motor
  {1.0f, 0.005f, 2.08f,0.0f, 0.0f,0},// PID for Front Right Motor
};


int32_t PIDMOTOR(float setpoint, float rpm, float deltaTime,struct PIDControl *pid) {

// Reset integral for direction change
  if ((setpoint > 0 && pid->state == 1) || (setpoint < 0 && pid->state == 0)) {
	        pid->integral = 0;
	        pid->state = setpoint > 0 ? 0 : 1;
  }


  float error = setpoint - rpm;
  pid->integral += (error * deltaTime);
  // Anti-windup
  if (pid->integral > LIM_MAX_INT) {
    pid->integral = LIM_MAX_INT;
  } else if (pid->integral < LIM_MIN_INT) {
    pid->integral = LIM_MIN_INT;
  }
  errorcheck = pid->integral;

  float derivative = (error - pid->previousError) / deltaTime;

  float u = (pid->kp * error + pid->ki * pid->integral + pid->kd * derivative);
  pid->previousError = error;

  int32_t pwm = (int32_t)(u * 65535.0f) / MAX_VRPM;
  errorcheck = error;

  if (pwm > 65535) {
    pwm = 65535;
  } else if (pwm < -65535) {
    pwm = -65535;
  }
  pidspeed = pwm;

  return pwm;
}

struct Velocity {
  float Pulse;
  float PrevPulse;
  float Vrpm;
};

struct Velocity Count[] = {
  { 0, 0, 0 },
  { 0, 0, 0}
};

float ChangetoRPM(int32_t Pulse, uint8_t i) {
  float Vrpm = (((float)Pulse*1.0f) - Count[i].PrevPulse) * 4.6875f;// 1output/จำนวนcount*60s/ms*1/deltatime(100) = vrpm
  Count[i].PrevPulse = (float)(Pulse*1.0f);
  return Vrpm;
}

int main(){
	Clk_init();// use 400MHz
	Systick_init(400000000,1000);// set millis()

	 /* FPU settings ------------------------------------------------------------*/
	SCB->CPACR |= ((3UL << 20U)|(3UL << 22U));  /* set CP10 and CP11 Full Access */

	USART3_Init();
	Encoder_init();
	motor_init();
	char encoder[99999];
	uint32_t prevtime = 0;

	while(1){

		if(millis() - prevtime >= 100){
			for(uint8_t i = 0;i<2;i++){
				Count[i].Pulse = GetValueEncoder(i+1);
				Count[i].Vrpm = ChangetoRPM(Count[i].Pulse,i);
			}
			int32_t speedFL = PIDMOTOR(5000.0f,Count[0].Vrpm,100,&PIDControllers[0]);
			int32_t speedFR = PIDMOTOR(5000.0f,Count[1].Vrpm,100,&PIDControllers[1]);
			rotateMotor(FRONT_LEFT_MOTOR,speedFL);
			rotateMotor(FRONT_RIGHT_MOTOR,speedFR);
			prevtime = millis();

		}
			sprintf(encoder,"Vrpm1 : %.4f  Vrpm2 : = %.4f \r\n",Count[0].Vrpm,Count[1].Vrpm);
			USART3_SendString(encoder);
	}
}
