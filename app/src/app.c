#include "app.h"


u8 seconds;
u16 Volt16;
u8 txdata[4];

u8  RGB_Flag = 0,LowBattery = 0,BatteryFlag = 0;
u8 LD1,LD2,LD3;
u32 RGB_LD;
u16 RGB_Cnt = 0;


void app_main(void)
{
    Read_Cali_Data();
    parameters_Init();
    Gpio_config();
    Key_Init();
    LED_Init();
    TLE5012B_Init();
    TIM2_Init();
    TIM5_Init();
    WS2812_init();

    USART1_init(115200*8); //ESP32通信口
    USART2_init(115200*2); //调试口
    IMU_Init();

    TIM1_Init();
    TIM8_Init();
    ADC_Config();
    delay_ms(10);

    while (1)
    {
        if(TIM_Flag == 1)
        {
            TIM_Flag = 0;
            //			Oscilloscope();
            Car_Cali();
            RcData();
            IMU_handle();
            if(mpu6500.Cali_Flag == 1)
            {
                G_LED(4);

                if(++Car.M1_M2_Cnt >= 300) // 等待电机初始化
                {
                    Car.M1_M2_Cnt = 300;
                    if(Car.Cali_flag == 1)MotorControl();
                }
            }

            Key_Scan();
            Get_InputVolt();

            //      if(fabsf(Car.BatVin_filter) < 6.5f)R_LED(5); else R_LED(0);
            if(++seconds >= 100) // 向ESP32发送电压数据
            {
                seconds = 0;
                Volt16 = (u16)(Car.BatVin_filter * 100.0f);
                txdata[0] = Volt16&0xff;
                txdata[1] = Volt16>>8;
                txdata[2]++;
                txdata[3]++;
                UART1_SendDataDMA(txdata,4);
            }

            if(Car.Print_flag == 1)UsartPrint();

            if(Car.BatVin_filter < 7.0f)LowBattery = 1; else LowBattery = 0;

            if(WS2812_SendFlag == 0)
            {
                WS2812_SendFlag = 1;
                if(Rc.ch2 == 1)
                {
                    RGB_Data[1] = 0x808080;
                    RGB_Data[2] = 0x808080;
                }
                else if(Rc.ch2 == 0)
                {
                    RGB_Data[1] = 0;
                    RGB_Data[2] = 0;
                }

                if(LowBattery == 1)
                {
                    if(++RGB_Cnt >= 200)
                    {
                        RGB_Cnt = 0;
                        if(BatteryFlag == 0)
                        {
                            BatteryFlag = 1;
                            RGB_Data[0] = 0x0a0000;
                            RGB_Data[3] = 0x0a0000;
                            RGB_Data[4] = 0x0a0000;
                            RGB_Data[7] = 0x0a0000;
                        }
                        else if(BatteryFlag == 1)
                        {
                            BatteryFlag = 0;
                            RGB_Data[0] = 0;
                            RGB_Data[3] = 0;
                            RGB_Data[4] = 0;
                            RGB_Data[7] = 0;
                        }
                    }
                }
                else
                {
                    RGB_Data[0] = 0;
                    RGB_Data[3] = 0;
                    RGB_Data[4] = 0;
                    RGB_Data[7] = 0;
                }
                //				RGB_Data[0] = 0x000000;
                //				RGB_Data[1] = 0x0a0a0a;
                //				RGB_Data[2] = 0x0a0a0a;
                //				RGB_Data[3] = 0x000000;
                //				RGB_Data[4] = 0x000000;
                //				RGB_Data[5] = 0x000000;
                //				RGB_Data[6] = 0x000000;
                //				RGB_Data[7] = 0x000000;
                send_Data(RGB_Data,8);
            }
        }
    }
}