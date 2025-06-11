#include "app.h"

Print_data_t Print_data;
u8 get_decode_data[]=
{	
	0x23,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00
};

u16 test_cnt = 0;

u8 debug_buff[72];

void UsartPrint(void) // 支持ni名助手V1.0.1上位机打印数据，一共16通道，可自行修改其它上位机 Read_MT6701()
{
	uint8_t i;

	if(Tx2_Flag == 0)
	{
		Tx2_Flag = 1;

		Print_data.data0  = 0; // 把“0”替换成所需要查看的变量
		Print_data.data1  = 0;
		Print_data.data2  = 0;
		Print_data.data3  = 0;
		Print_data.data4  = 0;
		Print_data.data5  = 0;
		Print_data.data6  = 0;
		Print_data.data7  = 0;
		Print_data.data8  = 0;
		Print_data.data9  = 0;
		Print_data.data10 = 0;
		Print_data.data11 = 0;
		Print_data.data12 = 0;
		Print_data.data13 = 0;
		Print_data.data14 = 0;
		Print_data.data15 = test_cnt++;

	  debug_buff[0] = 0xAB;
		debug_buff[1] = 0;
		debug_buff[2] = 0;
		debug_buff[3] = 0xFA;
		debug_buff[4] = 64;
		debug_buff[5] = 0;

		memcpy(debug_buff+6,&Print_data,sizeof(Print_data));

		debug_buff[70]=0;
		debug_buff[71]=0;

		for(i=0;i<70;i++)
		{
			debug_buff[70] += debug_buff[i];
			debug_buff[71] += debug_buff[70];
		}
		UART2_SendDataDMA(debug_buff,72);
	}
}

void Oscilloscope(void)
{
	uint8_t i;
	if(Tx2_Flag == 0)
	{
		Tx2_Flag = 1;
		Print_data.data0  = M1_Foc.Id; // 把“0”替换成所需要查看的变量
		Print_data.data1  = M1_Foc.Iq;
		Print_data.data2  = M2_Foc.Id;
		Print_data.data3  = M2_Foc.Iq;
		Print_data.data4  = 0;
		Print_data.data5  = 0;
		Print_data.data6  = 0;
		Print_data.data7  = 0;
		Print_data.data8  = 0;
		Print_data.data9  = 0;
		Print_data.data10 = 0;
		Print_data.data11 = 0;
		Print_data.data12 = 0;
		Print_data.data13 = 0;
		Print_data.data14 = 0;
		Print_data.data15 = test_cnt++;	
		
	  get_decode_data[0] = 0x23;
		memcpy(get_decode_data+1,&Print_data,sizeof(Print_data));
		
		get_decode_data[65]=0;
		for(i=1;i<65;i++)
		{	  				    
			get_decode_data[65] += get_decode_data[i];
		}	
		UART2_SendDataDMA(get_decode_data,66);
	}
}
