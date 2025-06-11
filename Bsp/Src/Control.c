
#include "app.h"

PID_Structure_t SpeedPID;
PID_Structure TurnPID;

PID_Structure UprightPID;
PID_Structure GyroAnglePID;

PID_Structure M1SpeedPID;
PID_Structure M2SpeedPID;

PID_Structure M1CurrentIdPID;
PID_Structure M1CurrentIqPID;

PID_Structure M2CurrentIdPID;
PID_Structure M2CurrentIqPID;

Encoder_t M1_Encoder;
Encoder_t M2_Encoder;

Car_t Car;

volatile union sFaultBitTypeDef FaultBit;


u8 GET_USART1_Data[128];
u8 GET_USART2_Data[128];

#define CurrentLimit  1.0f

#define IqId 1.0f // 最大为1.0

#define UprightLimit 6000.0f // 直立最大输出 2500 度/秒
#define TurnLimit    3000.0f // 旋转最大输出 1500 度/秒
#define SpeedLimit   5000.0f // 速度最大输出 1500 度/秒

void parameters_Init(void) //
{
/*************************************************************/
	SpeedPID.Kp = 1.25f; // 1.25
	SpeedPID.Ki = 0.0015f; // 0.002
	SpeedPID.Kd = 0.0f;

	SpeedPID.Ki_Out = 0.0f;

	SpeedPID.Kp_Min = -SpeedLimit;
	SpeedPID.Kp_Max =  SpeedLimit;

	SpeedPID.Kd_Min = 0.0f;
	SpeedPID.Kd_Max = 0.0f;

	SpeedPID.Ki_Min = -SpeedLimit / SpeedPID.Ki;
	SpeedPID.Ki_Max =  SpeedLimit / SpeedPID.Ki;

	SpeedPID.outMin = -SpeedLimit / SpeedPID.Ki;
	SpeedPID.outMax =  SpeedLimit / SpeedPID.Ki;

	SpeedPID.PID_Out = 0.0f;
	SpeedPID.OutLimit = SpeedLimit;

/*************************************************************/

/*************************************************************/
	TurnPID.Kp = 1.0f; // 0.1
	TurnPID.Ki = 0.0f; //
	TurnPID.Kd = 5.0f;//50.0

	TurnPID.Ki_Out = 0.0f; //

	TurnPID.Kp_Min = -TurnLimit;
	TurnPID.Kp_Max =  TurnLimit;

	TurnPID.Kd_Min = -TurnLimit;
	TurnPID.Kd_Max =  TurnLimit;

	TurnPID.Ki_Min = -TurnLimit; //
	TurnPID.Ki_Max =  TurnLimit;

	TurnPID.outMin = -TurnLimit;
	TurnPID.outMax =  TurnLimit;

	TurnPID.PID_Out = 0.0f;
/*************************************************************/

/*************************************************************/
	UprightPID.Kp = 100.0f; // 100
	UprightPID.Ki = 0.0f;   //
	UprightPID.Kd = 10.0f;  //

	UprightPID.Ki_Out = 0.0f; //

	UprightPID.Kp_Min = -UprightLimit;
	UprightPID.Kp_Max =  UprightLimit;

	UprightPID.Kd_Min = -UprightLimit;
	UprightPID.Kd_Max =  UprightLimit;

	UprightPID.Ki_Min = -UprightLimit; //
	UprightPID.Ki_Max =  UprightLimit;

	UprightPID.outMin = -UprightLimit;
	UprightPID.outMax =  UprightLimit;

	UprightPID.PID_Out = 0.0f;
/*************************************************************/

/*************************************************************/
	M1SpeedPID.Kp = 0.001f; // 0.005f
	M1SpeedPID.Ki = M1SpeedPID.Kp / 50.0f; // 0.00005f
	M1SpeedPID.Kd = 0.0f;

	M1SpeedPID.Ki_Out = 0.0f;

	M1SpeedPID.Kp_Min = -CurrentLimit;
	M1SpeedPID.Kp_Max =  CurrentLimit;

	M1SpeedPID.Kd_Min = -CurrentLimit;
	M1SpeedPID.Kd_Max =  CurrentLimit;

	M1SpeedPID.Ki_Min = -CurrentLimit; //
	M1SpeedPID.Ki_Max =  CurrentLimit;

	M1SpeedPID.outMin = -CurrentLimit;
	M1SpeedPID.outMax =  CurrentLimit;

	M1SpeedPID.PID_Out = 0.0f;
/*************************************************************/
	M2SpeedPID.Kp = 0.001f; // 0.1
	M2SpeedPID.Ki = M2SpeedPID.Kp / 50.0f; //
	M2SpeedPID.Kd = 0.0f;//50.0

	M2SpeedPID.Ki_Out = 0.0f; //

	M2SpeedPID.Kp_Min = -CurrentLimit;
	M2SpeedPID.Kp_Max =  CurrentLimit;

	M2SpeedPID.Kd_Min = -CurrentLimit;
	M2SpeedPID.Kd_Max =  CurrentLimit;

	M2SpeedPID.Ki_Min = -CurrentLimit; //
	M2SpeedPID.Ki_Max =  CurrentLimit;

	M2SpeedPID.outMin = -CurrentLimit;
	M2SpeedPID.outMax =  CurrentLimit;

	M2SpeedPID.PID_Out = 0.0f;
/*************************************************************/

/*************************************************************/
	M1CurrentIdPID.Kp = 0.1f;
	M1CurrentIdPID.Ki = M1CurrentIdPID.Kp / 10.0f;
	M1CurrentIdPID.Kd = 0.0f;

	M1CurrentIdPID.Ki_Out = 0.0f; //

	M1CurrentIdPID.Kp_Min = -IqId/2.0f;
	M1CurrentIdPID.Kp_Max =  IqId/2.0f;

	M1CurrentIdPID.Kd_Min = -IqId/2.0f;
	M1CurrentIdPID.Kd_Max =  IqId/2.0f;

	M1CurrentIdPID.Ki_Min = -IqId/2.0f; //
	M1CurrentIdPID.Ki_Max =  IqId/2.0f;

	M1CurrentIdPID.outMin = -IqId/2.0f;
	M1CurrentIdPID.outMax =  IqId/2.0f;

	M1CurrentIdPID.PID_Out = 0.0f;
/*************************************************************/
	M1CurrentIqPID.Kp = 0.5f;
	M1CurrentIqPID.Ki = M1CurrentIqPID.Kp / 10.0f;
	M1CurrentIqPID.Kd = 0.0f;

	M1CurrentIqPID.Ki_Out = 0.0f; //

	M1CurrentIqPID.Kp_Min = -IqId;
	M1CurrentIqPID.Kp_Max =  IqId;

	M1CurrentIqPID.Kd_Min = -IqId;
	M1CurrentIqPID.Kd_Max =  IqId;

	M1CurrentIqPID.Ki_Min = -IqId; //
	M1CurrentIqPID.Ki_Max =  IqId;

	M1CurrentIqPID.outMin = -IqId;
	M1CurrentIqPID.outMax =  IqId;

	M1CurrentIqPID.PID_Out = 0.0f;
/*************************************************************/

/*************************************************************/
	M2CurrentIdPID.Kp = 0.1f;
	M2CurrentIdPID.Ki = M2CurrentIdPID.Kp / 10.0f;
	M2CurrentIdPID.Kd = 0.0f;

	M2CurrentIdPID.Ki_Out = 0.0f; //

	M2CurrentIdPID.Kp_Min = -IqId/2.0f;
	M2CurrentIdPID.Kp_Max =  IqId/2.0f;

	M2CurrentIdPID.Kd_Min = -IqId/2.0f;
	M2CurrentIdPID.Kd_Max =  IqId/2.0f;

	M2CurrentIdPID.Ki_Min = -IqId/2.0f; //
	M2CurrentIdPID.Ki_Max =  IqId/2.0f;

	M2CurrentIdPID.outMin = -IqId/2.0f;
	M2CurrentIdPID.outMax =  IqId/2.0f;

	M2CurrentIdPID.PID_Out = 0.0f;
/*************************************************************/
	M2CurrentIqPID.Kp = 0.5f;
	M2CurrentIqPID.Ki = M2CurrentIqPID.Kp / 10.0f;
	M2CurrentIqPID.Kd = 0.0f;

	M2CurrentIqPID.Ki_Out = 0.0f; //

	M2CurrentIqPID.Kp_Min = -IqId;
	M2CurrentIqPID.Kp_Max =  IqId;

	M2CurrentIqPID.Kd_Min = -IqId;
	M2CurrentIqPID.Kd_Max =  IqId;

	M2CurrentIqPID.Ki_Min = -IqId; //
	M2CurrentIqPID.Ki_Max =  IqId;

	M2CurrentIqPID.outMin = -IqId;
	M2CurrentIqPID.outMax =  IqId;

	M2CurrentIqPID.PID_Out = 0.0f;
/*************************************************************/

  Car.Sensitivity = 20.0f;
	Car.Protect_flag = 1;
	Car.BatVin_filter = 8.2f;
}

float ControlOut_L = 0.0f,ControlOut_R = 0.0f;

u8 CarSpeedCnt = 0;

u16 Stall_cnt;

void MotorControl(void) //直接控制电机转速进行起立后闭环
{
	if(fabs(mpu6500.gyroAngle.y) < 5.0f)
	{
		Car.Protect = 1;

		if(Car.Protect_flag == 1)
		{
			if(fabsf(mpu6500.gyro.filter.x) < 1.5f && fabsf(mpu6500.gyro.filter.y) < 1.5f && fabsf(mpu6500.gyro.filter.z) < 5.0f)
			{
				if(++Car.ProtectCnt >= 100)
				{
					Car.ProtectCnt = 0;
					Car.Protect_flag = 0;
					M1_Foc.Cali_Status = 0;
					M2_Foc.Cali_Status = 0;
				}
			}
			else Car.ProtectCnt = 0;
		}
	}

	if(Car.Protect_flag == 0 && Car.PowerFlag == 1 && fabs(mpu6500.gyroAngle.y) < 70.0f)
	{
		if(++CarSpeedCnt >= 2) // 2ms
		{
			CarSpeedCnt = 0;
			if(Car.Protect == 1)
			{
				Car.Speed = (M1_Encoder.Speed_filterA - M2_Encoder.Speed_filterA);

				if(Rc.z_flag == 0) // 增强手感
				{
					TurnPID.Kd = 10.0f;
				}
				else if(Rc.z_flag == 1) // 默认手感
				{
					TurnPID.Kd = 5.0f;
				}

				Car.ControlY = Rc.x*Car.Sensitivity;
				Car.ControlZ = Rc.z*Car.Sensitivity;

				if(fabsf(M1_Encoder.Speed_filterA) > 3600.0f || fabsf(M2_Encoder.Speed_filterA) > 3600.0f) //
				{
					if(Rc.x_flag == 0 && Rc.z_flag == 0)
					{
						if(mpu6500.acc.filter.z > 1.025f)Car.Protect_flag = 1;
					}
				}

				PID_Adjust_S(&SpeedPID,0.0f,-Car.Speed,Car.ControlY);
				PID_Adjust_T(&TurnPID,Car.ControlZ,0.0f,mpu6500.gyro.Primitive.z);
			}
		}
		PID_Adjust_T(&UprightPID,0.0f,-mpu6500.gyroAngle.y,mpu6500.gyro.Primitive.y);
		ControlOut_L = UprightPID.PID_Out + SpeedPID.PID_Out + TurnPID.PID_Out;
		ControlOut_R = UprightPID.PID_Out + SpeedPID.PID_Out - TurnPID.PID_Out;

		if(fabsf(M1_Foc.Iq) > 0.95f || fabsf(M2_Foc.Iq) > 0.95f)
		{
			if(++Stall_cnt >= 1000) //堵转1秒关闭
			{
				Stall_cnt = 0;
				Car.Protect_flag = 1;
			}
		}
		else Stall_cnt = 0;
	}
	else if(Car.Protect_flag == 1 || fabs(mpu6500.gyroAngle.y) > 75.0f)
	{
		Car.Protect_flag = 1;
		ControlOut_L = 0.0f;
		ControlOut_R = 0.0f;

		if(fabsf(M1_Encoder.Speed_filter) < 5.0f && fabsf(M2_Encoder.Speed_filter) < 5.0f) // 转速小于5
		{
			M1_Foc.Cali_Status = 2;
			M2_Foc.Cali_Status = 2;
		}

		Car.Speed = 0.0f;
		Car.Protect = 0;

		M1_Encoder.Spd_Offset_Flag = 0;
		M2_Encoder.Spd_Offset_Flag = 0;

		UprightPID.Ki_Out = 0.0f;
		UprightPID.PID_Out = 0.0f;

		SpeedPID.Ki_Out = 0.0f;
		SpeedPID.PID_Out = 0.0f;

		TurnPID.Ki_Out =  0.0f;
		TurnPID.PID_Out = 0.0f;

		M1_Encoder.Speed_filterA = 0.0f;
		M2_Encoder.Speed_filterA = 0.0f;
	}

	if(FaultBit.bit.IMU == 1)
	{
		ControlOut_L = 0.0f;
		ControlOut_R = 0.0f;
	}
}

u8 M1SpeedCnt = 0;
u8 M2SpeedCnt = 0;

void M1_Control(void)
{
	if(M1_Foc.Cali_Status == 0)
	{
		M1SpeedControl(ControlOut_L);
		M1Current_ClosedLoop(M1SpeedPID.PID_Out);
	}
	else if(M1_Foc.Cali_Status == 2)
	{
		M1_Foc.Vd = 0.0f;
		M1_Foc.Vq = 0.0f;
	}
	else if(M1_Foc.Cali_Status == 1)
	{
		M1SpeedControl(1800.0f);
		M1Current_ClosedLoop(M1SpeedPID.PID_Out);
	}
	else if(M1_Foc.Cali_Status == 3)
	{
		if(++M1SpeedCnt >= 2)
		{
			M1SpeedCnt = 0;
			SpeedCompute(&M1_Encoder,M1_Foc.Encoder_data);
		}
	}
}

void M2_Control(void)
{
	if(M2_Foc.Cali_Status == 0)
	{
		M2SpeedControl(-ControlOut_R);
		M2Current_ClosedLoop(M2SpeedPID.PID_Out);
	}
	else if(M2_Foc.Cali_Status == 2)
	{
		M2_Foc.Vd = 0.0f;
		M2_Foc.Vq = 0.0f;
	}
	else if(M2_Foc.Cali_Status == 1)
	{
		M2SpeedControl(1800.0f);
		M2Current_ClosedLoop(M2SpeedPID.PID_Out);
	}
	else if(M2_Foc.Cali_Status == 3)
	{
		if(++M2SpeedCnt >= 2)
		{
			M2SpeedCnt = 0;
			SpeedCompute(&M2_Encoder,M2_Foc.Encoder_data);
		}
	}
}

void SpeedCompute(Encoder_t* Speed, uint16_t Encoder_data)
{
	Speed->data = Encoder_data;
	if(Speed->Spd_Offset_Flag == 0)
	{
		Speed->Spd_Offset_Flag = 1;
		Speed->UpData = Speed->data;
	}
	if(Speed->UpData > 32000 && Speed->data < 768)
	{
		Speed->DiffeData = (int32_t)(32768  + Speed->data) - Speed->UpData;
	}
	else if(Speed->UpData < 768 && Speed->data > 32000)
	{
		Speed->DiffeData = - ((int32_t)(32768  - Speed->data) + Speed->UpData);
	}
	else
	{
		Speed->DiffeData = Speed->data - Speed->UpData;
	}
	Speed->UpData = Speed->data;

	Speed->Speed = (Speed->DiffeData * 0.010986328125f)/0.0002f;
	Speed->Speed_filter += (Speed->Speed - Speed->Speed_filter) * 0.25f;
	Speed->Speed_filterA += (Speed->Speed_filter - Speed->Speed_filterA) * 0.01f;
}

void M1SpeedControl(float speed)
{
	if(++M1SpeedCnt >= 2)
	{
		M1SpeedCnt = 0;
		SpeedCompute(&M1_Encoder,M1_Foc.Encoder_data);
		PID_Adjust(&M1SpeedPID,speed,M1_Encoder.Speed_filter);
	}
}

void M1Current_ClosedLoop(float Current)
{
	PID_Adjust(&M1CurrentIdPID,0.0f,M1_Foc.Id);
	M1_Foc.Vd = M1CurrentIdPID.PID_Out;

	PID_Adjust(&M1CurrentIqPID,Current,M1_Foc.Iq);
	M1_Foc.Vq = M1CurrentIqPID.PID_Out;
}

void M2SpeedControl(float speed)
{
	if(++M2SpeedCnt >= 2) // 速度环 200us
	{
		M2SpeedCnt = 0;
		SpeedCompute(&M2_Encoder,M2_Foc.Encoder_data);
		PID_Adjust(&M2SpeedPID,speed,M2_Encoder.Speed_filter);
	}
}

void M2Current_ClosedLoop(float Current) // 电流环 100us
{
	PID_Adjust(&M2CurrentIdPID,0.0f,M2_Foc.Id);
	M2_Foc.Vd = M2CurrentIdPID.PID_Out;	
	
	PID_Adjust(&M2CurrentIqPID,Current,M2_Foc.Iq);
	M2_Foc.Vq = M2CurrentIqPID.PID_Out;
}

float PID_Adjust_T(PID_Structure* handle,float Given,float Feedback,float Gyro)
{
	float Error_value;

	float P_Out;
	float D_Out;
	
	Error_value = Given - Feedback;
	
	P_Out = Error_value * handle->Kp;
	handle->Ki_Out += Error_value * handle->Ki;
	D_Out = Gyro * handle->Kd; 
	
	if(P_Out < handle->Kp_Min)P_Out = handle->Kp_Min; 
	else if(P_Out > handle->Kp_Max)P_Out = handle->Kp_Max;
	
	if(handle->Ki_Out < handle->Ki_Min)handle->Ki_Out = handle->Ki_Min;
	else if(handle->Ki_Out > handle->Ki_Max)handle->Ki_Out = handle->Ki_Max;
  
	if(D_Out < handle->Kd_Min)D_Out = handle->Kd_Min; 
	else if(D_Out > handle->Kd_Max)D_Out = handle->Kd_Max;
	
	handle->PID_Out = P_Out + handle->Ki_Out + D_Out;
	
	if(handle->PID_Out > handle->outMax)
	{
    handle->PID_Out = handle->outMax;
	}
  else if(handle->PID_Out < handle->outMin)
	{
    handle->PID_Out = handle->outMin;
	}
	return handle->PID_Out;
}

float PID_Adjust(PID_Structure* handle,float Given,float Feedback)
{
	float Error_value;

	float P_Out;
	
	Error_value = Given - Feedback;
	
	P_Out = Error_value * handle->Kp;
	handle->Ki_Out += Error_value * handle->Ki;

	if(P_Out < handle->Kp_Min)P_Out = handle->Kp_Min; 
	else if(P_Out > handle->Kp_Max)P_Out = handle->Kp_Max;
	
	if(handle->Ki_Out < handle->Ki_Min)handle->Ki_Out = handle->Ki_Min;
	else if(handle->Ki_Out > handle->Ki_Max)handle->Ki_Out = handle->Ki_Max;
	
	handle->PID_Out = P_Out + handle->Ki_Out;
	
	if(handle->PID_Out > handle->outMax)
	{
    handle->PID_Out = handle->outMax;
	}
  else if(handle->PID_Out < handle->outMin)
	{
    handle->PID_Out = handle->outMin;
	}
	return handle->PID_Out;
}


