#include "hid_device_for_handel.h"

#include "usbd_custom_hid_if.h"

#include "main.h"
#include "adc.h"

#if BORD_MAP == F103_TERNEL 
#define key_channle_number 29
uint16_t adc_value [4];
uint8_t hid_data [13];
#endif

extern USBD_HandleTypeDef hUsbDeviceFS;

unsigned char PIN_KEY_GET_DATA (GPIO_TypeDef *GPIO,uint16_t GPIO_Pin);
unsigned char UNIT_ADC_DATA_COMVERTER(uint16_t adc_value_tmp);
unsigned char PIN_KEY_COMPLET_DATA(unsigned char KEY1_tmp,unsigned char KEY2_tmp,unsigned char KEY3_tmp,unsigned char KEY4_tmp,unsigned char KEY5_tmp,unsigned char KEY6_tmp,unsigned char KEY7_tmp,unsigned char KEY8_tmp);

void HID_FLIGHT_SIMULATOR_SYS_START(void)
{
    #if BORD_MAP == F103_TERNEL 
    HAL_ADC_Start_DMA(&hadc1,(uint32_t *)adc_value,4);
    #endif
}
void HID_FLIGHT_SIMULATOR_SYS_LOOP(void)
{
    #if BORD_MAP == F103_TERNEL 
    uint8_t key_tmp[key_channle_number];
    key_tmp[0] = PIN_KEY_GET_DATA(KEY1);
    key_tmp[1] = PIN_KEY_GET_DATA(KEY2);
    key_tmp[2] = PIN_KEY_GET_DATA(KEY3);
    key_tmp[3] = PIN_KEY_GET_DATA(KEY4);
    key_tmp[4] = PIN_KEY_GET_DATA(KEY5);
    key_tmp[5] = PIN_KEY_GET_DATA(KEY6);
    key_tmp[6] = PIN_KEY_GET_DATA(KEY7);
    key_tmp[7] = PIN_KEY_GET_DATA(KEY8);
    key_tmp[8] = PIN_KEY_GET_DATA(KEY9);
    key_tmp[9] = PIN_KEY_GET_DATA(KEY10);
    key_tmp[10] = PIN_KEY_GET_DATA(KEY11);
    key_tmp[11] = PIN_KEY_GET_DATA(KEY12);
    key_tmp[12] = PIN_KEY_GET_DATA(KEY13);
    key_tmp[13] = PIN_KEY_GET_DATA(KEY14);
    key_tmp[14] = PIN_KEY_GET_DATA(KEY15);
    key_tmp[15] = PIN_KEY_GET_DATA(KEY16);
    key_tmp[16] = PIN_KEY_GET_DATA(KEY17);
    key_tmp[17] = PIN_KEY_GET_DATA(KEY18);
    key_tmp[18] = PIN_KEY_GET_DATA(KEY19);
    key_tmp[19] = PIN_KEY_GET_DATA(KEY20);
    key_tmp[20] = PIN_KEY_GET_DATA(KEY21);
    key_tmp[21] = PIN_KEY_GET_DATA(KEY22);
    key_tmp[22] = PIN_KEY_GET_DATA(KEY23);
    key_tmp[23] = PIN_KEY_GET_DATA(KEY24);
    key_tmp[24] = PIN_KEY_GET_DATA(KEY25);
    key_tmp[25] = PIN_KEY_GET_DATA(KEY26);
    key_tmp[26] = PIN_KEY_GET_DATA(KEY27);
    key_tmp[27] = PIN_KEY_GET_DATA(KEY28);
    key_tmp[28] = PIN_KEY_GET_DATA(KEY29);

    hid_data[0] = BORD_ID;
    hid_data[1] = adc_value[0] & 0xff;
    hid_data[2] = adc_value[0] >> 8;
    hid_data[3] = adc_value[1] & 0xff;
    hid_data[4] = adc_value[1] >> 8;
    hid_data[5] = adc_value[2] & 0xff;
    hid_data[6] = adc_value[2] >> 8;
    hid_data[7] = adc_value[3] & 0xff;
    hid_data[8] = adc_value[3] >> 8;

    hid_data[9] = PIN_KEY_COMPLET_DATA(key_tmp[7],key_tmp[6],key_tmp[5],key_tmp[4],key_tmp[3],key_tmp[2],key_tmp[1],0);
    hid_data[10] = PIN_KEY_COMPLET_DATA(key_tmp[15],key_tmp[14],key_tmp[13],key_tmp[12],key_tmp[11],key_tmp[10],key_tmp[9],key_tmp[8]);
    hid_data[11] = PIN_KEY_COMPLET_DATA(key_tmp[23],key_tmp[22],key_tmp[21],key_tmp[20],key_tmp[19],key_tmp[18],key_tmp[17],key_tmp[16]);
    hid_data[12] = PIN_KEY_COMPLET_DATA(0,0,key_tmp[28],key_tmp[27],key_tmp[0],key_tmp[26],key_tmp[25],key_tmp[24]);


    USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS,hid_data,sizeof(hid_data));
    HAL_Delay(10);

    #endif
}



unsigned char PIN_KEY_GET_DATA (GPIO_TypeDef *GPIO,uint16_t GPIO_Pin)
{
    unsigned char tmp = 0;
    tmp = HAL_GPIO_ReadPin(GPIO,GPIO_Pin);
    tmp = (!tmp) & 1;
    return (tmp);
}

unsigned char UNIT_ADC_DATA_COMVERTER(uint16_t adc_value_tmp)
{
    unsigned char tmp = 0;
    tmp = (unsigned char) ((float)adc_value_tmp * 256 / 4096 );
    return tmp;
}

unsigned char PIN_KEY_COMPLET_DATA(unsigned char KEY1_tmp,unsigned char KEY2_tmp,unsigned char KEY3_tmp,unsigned char KEY4_tmp,unsigned char KEY5_tmp,unsigned char KEY6_tmp,unsigned char KEY7_tmp,unsigned char KEY8_tmp)
{
    unsigned char tmp = 0;
    tmp = KEY1_tmp<<7;
    tmp |= KEY2_tmp<<6;
    tmp |= KEY3_tmp<<5;
    tmp |= KEY4_tmp<<4;
    tmp |= KEY5_tmp<<3;
    tmp |= KEY6_tmp<<2;
    tmp |= KEY7_tmp<<1;
    tmp |= KEY8_tmp;
    return tmp;
}