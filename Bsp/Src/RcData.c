
#include "app.h"

s16 CH0 = 1024;//352 - 1024 - 1696
s16 CH1 = 1024;//352 - 1024 - 1696 
s16 CH2 = 0;
s16 CH3 = 0;

RC_t Rc;

u16 BLE_Cnt = 0;
uint8_t Rc_flag = 0;

void RcData(void)
{
	if(U1_IDLE_Flag == 1)
	{
		U1_IDLE_Flag = 0;
		BLE_Cnt = 0;
		if(GET_USART1_Data[0] == 0x20 && GET_USART1_Data[1] == 0x0f && GET_USART1_Data[14] == 0x02) // 游戏手柄控制数据
		{
			if(GET_USART1_Data[10] > 250) // ZL
			{
				Car.Protect_flag = 1;
				Car.AutoStandUp = 0;// 终止一键起立
			}

			if(GET_USART1_Data[11] > 250 && Rc_flag == 0)
			{
				Rc_flag = 1;
				if(Car.Rc_Mode == 0)
				{
					Car.Rc_Mode = 1;
				}
				else if(Car.Rc_Mode == 1)
				{
					Car.Rc_Mode = 0;
				}
			}
			else if(GET_USART1_Data[11] < 10)Rc_flag = 0;

			Rc.ch0 = (GET_USART1_Data[4] - 128); // = +- 128 -前 +后

			if(Car.Rc_Mode == 1)Rc.ch1 = (GET_USART1_Data[3] - 128);
			else Rc.ch1 = (GET_USART1_Data[5] - 128);

			if(GET_USART1_Data[8] == 2 && CH2 == 0)
			{
				CH2 = 3;
			}
			else if(GET_USART1_Data[8] != 2 && CH2 == 3)
			{
				CH2 = 0;
				if(Rc.ch2 == 0)Rc.ch2 = 1; else if(Rc.ch2 == 1)Rc.ch2 = 0;
			}
			else if(GET_USART1_Data[8] == 4 && CH3 == 0)  // 左 0x04 右 0x08
			{
				CH3 = 3;
			}
			else if(GET_USART1_Data[8] != 4 && CH3 == 3)
			{
				CH3 = 0;
				if(Car.Sensitivity < 25.0f)
				{
					Car.Sensitivity = 35.0f;

				}
				else if(Car.Sensitivity > 25.0f)
				{
					Car.Sensitivity = 20.0f;

				}
			}
			else if(GET_USART1_Data[8] == 1)
			{
				TMR10->c1dt = 200;
				if(Car.AutoStandUp == 0)Car.AutoStandUp = 1;

//				if(Car.Protect_flag > 0)
//				{
//					Car.Protect_flag = 0;
//					M1_Foc.Cali_Status = 0;
//					M2_Foc.Cali_Status = 0;
//				}
			}
			else TMR10->c1dt = 0;

			if(abs(Rc.ch0) < 8)
			{
				Rc.ch0 = 0;
				Rc.x += (Rc.ch0 - Rc.x) * 0.5f;
				if(fabs(Rc.x) < 0.0001f)
				{
					Rc.x = 0.0f;
					Rc.x_flag = 0;
				}
			}
			else if(Rc.ch0 > 8)
			{
				Rc.ch0 -= 8;
				Rc.x += (Rc.ch0 - Rc.x) * 0.25f;
				Rc.x_flag = 1;
			}
			else if(Rc.ch0 < -8)
			{
				Rc.ch0 += 8;
				Rc.x += (Rc.ch0 - Rc.x) * 0.25f;
				Rc.x_flag = 1;
			}

			if(abs(Rc.ch1) < 8)
			{
				Rc.ch1 = 0;
				Rc.z += (Rc.ch1 - Rc.z) * 0.8f;
				if(fabs(Rc.z) < 0.0001f)
				{
					Rc.z = 0.0f;
					Rc.z_flag = 0;
				}
			}
			else if(Rc.ch1 > 8)
			{
				Rc.ch1 -= 8;
				Rc.z += (Rc.ch1 - Rc.z) * 0.1f;
				Rc.z_flag = 1;
			}
			else if(Rc.ch1 < -8)
			{
				Rc.ch1 += 8;
				Rc.z += (Rc.ch1 - Rc.z) * 0.1f;
				Rc.z_flag = 1;
			}
		}
		else if(GET_USART1_Data[0] == 0x20 && GET_USART1_Data[1] == 0x0f && GET_USART1_Data[14] == 0x66) // 小程序控制数据
		{
			Rc.ch0 = GET_USART1_Data[5]; // = +- 100 
			Rc.ch1 = GET_USART1_Data[4];
			Rc.ch2 = GET_USART1_Data[2];
			
			if(GET_USART1_Data[8] == 2 && CH2 == 0)
			{
				CH2 = 3;
			}
			else if(GET_USART1_Data[8] != 2 && CH2 == 3)
			{
				CH2 = 0;
			}
			else if(GET_USART1_Data[8] == 4 && CH3 == 0)
			{
				CH3 = 3;
			}
			else if(GET_USART1_Data[8] != 4 && CH3 == 3)
			{
				CH3 = 0;
				if(Car.Sensitivity < 10.0f) 
				{
					Car.Sensitivity = 12.0f; 

				}
				else if(Car.Sensitivity > 10.0f)
				{
					Car.Sensitivity = 8.0f;

				}
			}
			else if(GET_USART1_Data[8] == 1)
			{
				TMR10->c1dt = 200;
				if(Car.Protect_flag > 0)
				{
					Car.Protect_flag = 0;
					M1_Foc.Cali_Status = 0;
					M2_Foc.Cali_Status = 0;
				}
			}
			else TMR10->c1dt = 0;
			
			if(abs(Rc.ch0) < 5)
			{
				Rc.ch0 = 0; 
				Rc.x += (Rc.ch0 - Rc.x) * 0.1f;
				if(fabs(Rc.x) < 0.001f)
				{
					Rc.x = 0.0f;
					Rc.x_flag = 0;
				}
			}
			else if(Rc.ch0 > 5)
			{
				Rc.ch0 -= 5;
				Rc.x += (Rc.ch0 - Rc.x) * 0.5f;
				Rc.x_flag = 1;
			}
			else if(Rc.ch0 < -5)
			{
				Rc.ch0 += 5;
				Rc.x += (Rc.ch0 - Rc.x) * 0.5f;
				Rc.x_flag = 1;
			}
			
			if(abs(Rc.ch1) < 25)
			{
				Rc.ch1 = 0; 
				Rc.z += (Rc.ch1 - Rc.z) * 0.1f;
				if(fabs(Rc.z) < 0.001f)
				{
					Rc.z = 0.0f;
					Rc.z_flag = 0;
				}
			}
			else if(Rc.ch1 > 25)
			{
				Rc.ch1 -= 25;
				Rc.z += (Rc.ch1 - Rc.z) * 0.5f;
				Rc.z_flag = 1;
			}
			else if(Rc.ch1 < -25)
			{
				Rc.ch1 += 25;
				Rc.z += (Rc.ch1 - Rc.z) * 0.5f;
				Rc.z_flag = 1;
			}
		}
		GET_USART1_Data[0] = GET_USART1_Data[1] = 0;
	}
	else
	{
		if(++BLE_Cnt >= 150)
		{
			BLE_Cnt = 500;
			if(Rc.ch0 > 0)
			{
				Rc.ch0--;
			  if(Rc.ch0 < 0)Rc.ch0 = 0; 
			}
			else if(Rc.ch0 < 0)
			{
				Rc.ch0++;
			  if(Rc.ch0 > 0)Rc.ch0 = 0; 
			}
			
			Rc.x += (Rc.ch0 - Rc.x) * 0.01f;
			if(fabs(Rc.x) < 0.0001f)
			{
				Rc.x = 0.0f;
				Rc.x_flag = 0;
			}
			
			if(Rc.ch1 > 0)
			{
				Rc.ch1--;
			  if(Rc.ch0 < 0)Rc.ch1 = 0; 
			}
			else if(Rc.ch1 < 0)
			{
				Rc.ch1++;
			  if(Rc.ch1 > 0)Rc.ch1 = 0; 
			}
			Rc.z += (Rc.ch1 - Rc.z) * 0.1f;
			if(fabs(Rc.z) < 0.0001f)
			{
				Rc.z = 0.0f;
				Rc.z_flag = 0;
			}
		}
	}
}

