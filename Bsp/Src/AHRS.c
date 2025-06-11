
#include "app.h"

mpu6500_t mpu6500;

/**************************************************************************************************/
u8 IMU_data[14];

/**************************************************************************
**************************************************************************/

u8 IMU_flag = 0;

void IMU_handle(void) // 姿态计算
{
	Get_mpu6500(IMU_data);	//获取mpu6500数据

	mpu6500.acc.data.x = ((IMU_data[0]<<8)|IMU_data[1]);
	mpu6500.acc.data.y = ((IMU_data[2]<<8)|IMU_data[3]);
	mpu6500.acc.data.z = ((IMU_data[4]<<8)|IMU_data[5]);

	mpu6500.gyro.data.x = ((IMU_data[8]<<8)|IMU_data[9]);
	mpu6500.gyro.data.y = ((IMU_data[10]<<8)|IMU_data[11]);
	mpu6500.gyro.data.z = ((IMU_data[12]<<8)|IMU_data[13]);

	if(mpu6500.Cali_Flag == 1) // 温补已经校准
	{
		if(mpu6500.Offset_Flag == 0)
		{
			mpu6500.Offset_Flag = 1;
			mpu6500.gyro.filter.x = mpu6500.gyro.Primitive.x;
			mpu6500.gyro.filter.y = mpu6500.gyro.Primitive.y;
			mpu6500.gyro.filter.z = mpu6500.gyro.Primitive.z;

			mpu6500.acc.Initial.x = mpu6500.acc.data.x;
			mpu6500.acc.Initial.y = mpu6500.acc.data.y;
			mpu6500.acc.Initial.z = mpu6500.acc.data.z;
		}

		mpu6500.gyro.Primitive.x = (float)mpu6500.gyro.data.x/16.4f - mpu6500.gyro.offset.x; // 换算成 度/秒
		mpu6500.gyro.Primitive.y = (float)mpu6500.gyro.data.y/16.4f - mpu6500.gyro.offset.y;
		mpu6500.gyro.Primitive.z = (float)mpu6500.gyro.data.z/16.4f - mpu6500.gyro.offset.z;

		mpu6500.gyro.filter.x += (mpu6500.gyro.Primitive.x - mpu6500.gyro.filter.x) * 0.5f; // 滤波
		mpu6500.gyro.filter.y += (mpu6500.gyro.Primitive.y - mpu6500.gyro.filter.y) * 0.5f;
		mpu6500.gyro.filter.z += (mpu6500.gyro.Primitive.z - mpu6500.gyro.filter.z) * 0.5f;

		mpu6500.acc.Primitive.x = (float)mpu6500.acc.data.x/4096.0f; // 换算成 度/秒
		mpu6500.acc.Primitive.y = (float)mpu6500.acc.data.y/4096.0f;
		mpu6500.acc.Primitive.z = (float)mpu6500.acc.data.z/4096.0f;

		mpu6500.acc.filter.x += (mpu6500.acc.Primitive.x - mpu6500.acc.filter.x) * 0.01f; // 滤波
		mpu6500.acc.filter.y += (mpu6500.acc.Primitive.y - mpu6500.acc.filter.y) * 0.01f;
		mpu6500.acc.filter.z += (mpu6500.acc.Primitive.z - mpu6500.acc.filter.z) * 0.01f;
	}
	else if(mpu6500.Cali_Flag == 0)
	{
		if(mpu6500.Offset_Flag == 0)
		{
			mpu6500.Offset_Flag = 1;
			mpu6500.gyro.filter.x = mpu6500.gyro.Primitive.x;
			mpu6500.gyro.filter.y = mpu6500.gyro.Primitive.y;
			mpu6500.gyro.filter.z = mpu6500.gyro.Primitive.z;

			mpu6500.acc.Initial.x = mpu6500.acc.data.x;
			mpu6500.acc.Initial.y = mpu6500.acc.data.y;
			mpu6500.acc.Initial.z = mpu6500.acc.data.z;
		}

		mpu6500.gyro.Primitive.x = (float)mpu6500.gyro.data.x/16.4f; // 换算成 度/秒
		mpu6500.gyro.Primitive.y = (float)mpu6500.gyro.data.y/16.4f;
		mpu6500.gyro.Primitive.z = (float)mpu6500.gyro.data.z/16.4f;

		mpu6500.gyro.filter.x += (mpu6500.gyro.Primitive.x - mpu6500.gyro.filter.x) * 0.05f; // 滤波
		mpu6500.gyro.filter.y += (mpu6500.gyro.Primitive.y - mpu6500.gyro.filter.y) * 0.05f;
		mpu6500.gyro.filter.z += (mpu6500.gyro.Primitive.z - mpu6500.gyro.filter.z) * 0.05f;

		mpu6500.acc.Primitive.x = (float)mpu6500.acc.data.x/4096.0f; // 换算成 度/秒
		mpu6500.acc.Primitive.y = (float)mpu6500.acc.data.y/4096.0f;
		mpu6500.acc.Primitive.z = (float)mpu6500.acc.data.z/4096.0f;

		mpu6500.acc.filter.x += (mpu6500.acc.Primitive.x - mpu6500.acc.filter.x) * 0.01f; // 滤波
		mpu6500.acc.filter.y += (mpu6500.acc.Primitive.y - mpu6500.acc.filter.y) * 0.01f;
		mpu6500.acc.filter.z += (mpu6500.acc.Primitive.z - mpu6500.acc.filter.z) * 0.01f;
	}

	mpu6500.accAngle.y = -atan2f(mpu6500.acc.filter.x,mpu6500.acc.filter.z) * 57.2957795f;  //计算加速度倾角

	if(IMU_flag == 0) // 使用加速度计算的姿态角赋初值
	{
		IMU_flag = 1;
		mpu6500.gyroAngle.y = mpu6500.accAngle.y;
	}

	if(fabsf(mpu6500.accAngle.y) > 90.0f)
	{
		mpu6500.gyroAngle.y = mpu6500.accAngle.y;
	}
	else
	{
		mpu6500.gyroAngle.y += mpu6500.gyro.Primitive.y * 0.001f; // 角速度积分
	  mpu6500.gyroAngle.y = mpu6500.gyroAngle.y * 0.999f + mpu6500.accAngle.y * 0.001f; // 陀螺积分角度与加速度倾角进行融合

		mpu6500.gyroAngle.z += mpu6500.gyro.Primitive.z * 0.001f; // 角速度积分，暂未使用
		if(mpu6500.gyroAngle.z > 180.0f)mpu6500.gyroAngle.z -= 360.0f;	
	  else if(mpu6500.gyroAngle.z < -180.0f)mpu6500.gyroAngle.z += 360.0f;	
	}
}


