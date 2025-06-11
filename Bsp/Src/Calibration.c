
#include "app.h"

CaliData_t CaliData;

uint8_t u8_Cali_Data[256]; 
uint8_t Protection = 0;
// 下载程序后使用串口助手按照顺序1-5进行校准即可，亦可仿真赋值进行校准

// 0xA0 0xAA 0x01 0xB1 0x66 校准陀螺零偏，必须保证小车无受到任何震动
// 0xA0 0xAA 0x02 0xB2 0x66 校准左电机，必须保证车轮能顺滑用手转动不能有干涉，串口发送指令后电机会按照设定速度转动则为正常（不转为异常）
// 0xA0 0xAA 0x03 0xB3 0x66 校准右电机，必须保证车轮能顺滑用手转动不能有干涉，串口发送指令后电机会按照设定速度转动则为正常（不转为异常）
// 0xA0 0xAA 0x04 0xB4 0x66 关闭电机
// 0xA0 0xAA 0x05 0xB5 0x66 保存数据，保存数据前请先关闭电机
// 0xA0 0xAA 0x06 0xB6 0x66 清除数据
// 0xA0 0xAA 0x07 0xB7 0x66 开启串口打印

void Car_Cali(void)
{
	uint8_t crc = 0;

	if(U2_IDLE_Flag == 1)
	{
		U2_IDLE_Flag = 0;
		if(GET_USART2_Data[0] == 0xA0 && GET_USART2_Data[1] == 0xAA && GET_USART2_Data[4] == 0x66)
		{
			crc = GET_USART2_Data[0] + GET_USART2_Data[1] + GET_USART2_Data[2] + GET_USART2_Data[4];
			if(GET_USART2_Data[3] == crc)
			{
				UART2_SendDataDMA(GET_USART2_Data,5);
				Car.Cali_mode = GET_USART2_Data[2];
				switch (Car.Cali_mode)
				{
					case 1:
						Gyro_Cali();
						Car.Cali_mode = 0;
						Protection = 0;
						break;
					case 2:
						M1_Foc.Cali_flag = 2;
						Car.Cali_mode = 0;
						break;
					case 3:
						M2_Foc.Cali_flag = 2;
						Car.Cali_mode = 0;
						break;
					case 4:
						M1_Foc.Cali_flag = 0;
						M2_Foc.Cali_flag = 0;
						Car.Cali_mode = 0;
						break;
					case 5:
						if(Protection == 0)
						{
							Protection = 1;
							Car.Cali_mode = 0;
							CaliData.M1_offset = M1_Foc.ThetaOffset;
							CaliData.M2_offset = M2_Foc.ThetaOffset;

							CaliData.M1_Flag = M1_Foc.Cali_Status;
							CaliData.M2_Flag = M2_Foc.Cali_Status;

							CaliData.x[0] = mpu6500.gyro.offset.x;
							CaliData.y[0] = mpu6500.gyro.offset.y;
							CaliData.z[0] = mpu6500.gyro.offset.z;

							CaliData.IMU_Flag = mpu6500.Cali_Flag;
							Write_Cali_Data();
						}
						break;
					case 6:
						if(Protection == 0)
						{
							Protection = 1;
							Car.Cali_mode = 0;
							CaliData.M1_offset = 0;
							CaliData.M2_offset = 0;

							CaliData.M1_Flag = 0;
							CaliData.M2_Flag = 0;

							CaliData.x[0] = 0;
							CaliData.y[0] = 0;
							CaliData.z[0] = 0;

							CaliData.IMU_Flag = 0;

							M1_Foc.Cali_flag = 0;
						  M2_Foc.Cali_flag = 0;
							Write_Cali_Data();
						}
						break;
					case 7:
						Car.Print_flag = 1;
						Car.Cali_mode = 0;
						break;
				}
			}
			memset(GET_USART2_Data,0,sizeof(char)*5);
		}
	}
}

/***********************************************************************************************************
*原型: void Gyro_Cali(void)
*功能：陀螺仪零偏校准
*调用：
*输入：
*输出：
************************************************************************************************************/
void Gyro_Cali(void)
{
	mpu6500.gyro.offset.x = mpu6500.gyro.filter.x;
	mpu6500.gyro.offset.y = mpu6500.gyro.filter.y;
	mpu6500.gyro.offset.z = mpu6500.gyro.filter.z;
	mpu6500.Cali_Flag = 1;
}

/***********************************************************************************************************
*原型: void Write_Cali_Data(void)
*功能：保存数据到Flash
*调用：
*输入：
*输出：
************************************************************************************************************/
void Write_Cali_Data(void)
{
	uint16_t i,len = 0;
	uint8_t *CaliDataT = (uint8_t *)&CaliData;

	CaliData.sumcheck = 0;
	CaliData.addcheck = 0;
	len = sizeof(CaliData)-2;
	for(i=0;i<len;i++)
	{
		CaliData.sumcheck += CaliDataT[i];
		CaliData.addcheck += CaliData.sumcheck;
	}

	memcpy(u8_Cali_Data,&CaliData,sizeof(CaliData));
	flash_write(0X0803E800,(uint16_t *)u8_Cali_Data,sizeof(CaliData));
}

/***********************************************************************************************************
*原型: void Read_Cali_Data(void)
*功能：读取Flash数据
*调用：
*输入：
*输出：
************************************************************************************************************/
void Read_Cali_Data(void)
{
	uint16_t i,len = 0;
	uint8_t sumcheck = 0,addcheck = 0;
	
	memset(&M1_Foc,0,sizeof(M1_Foc));
	memset(&M2_Foc,0,sizeof(M2_Foc));
	memset(&mpu6500,0,sizeof(mpu6500));
	
	flash_read(0X0803E800,(uint16_t *)u8_Cali_Data,sizeof(CaliData));
	
	memset(&CaliData,0,sizeof(CaliData));
	
	len = sizeof(CaliData)-2;
	for(i=0;i<len;i++)
	{
		sumcheck += u8_Cali_Data[i];
		addcheck += sumcheck;
	}	
	memcpy(&CaliData,u8_Cali_Data,sizeof(CaliData));

	if(CaliData.sumcheck == sumcheck && CaliData.addcheck == addcheck)
	{
		if(CaliData.M1_Flag == 1 && CaliData.M2_Flag == 1 && CaliData.IMU_Flag == 1)
		{
			Car.Cali_flag = 1;
			M1_Foc.Cali_flag = 1;
			M2_Foc.Cali_flag = 1;
			Cubli_Cali_Status = 1;
			
			if(CaliData.M1_Flag == 1)
			{
				M1_Foc.ThetaOffset = CaliData.M1_offset;
			}
			
			if(CaliData.M2_Flag == 1)
			{
				M2_Foc.ThetaOffset = CaliData.M2_offset;
			}
			
			if(CaliData.IMU_Flag == 1)
			{
				mpu6500.Cali_Flag = CaliData.IMU_Flag;
				mpu6500.gyro.offset.x = CaliData.x[0];
				mpu6500.gyro.offset.y = CaliData.y[0];
				mpu6500.gyro.offset.z = CaliData.z[0];
			}
		}
	}
	else 
	{
		memset(&CaliData,0,sizeof(CaliData));
		Car.Cali_flag = 0;
	}
}

