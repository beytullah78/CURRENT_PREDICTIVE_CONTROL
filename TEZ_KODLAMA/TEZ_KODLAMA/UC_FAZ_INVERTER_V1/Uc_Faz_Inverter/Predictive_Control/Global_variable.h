/*
 * Global_variable.h
 *
 *  Created on: 19 Eyl 2020
 *      Author: ASUS
 */

#ifndef UC_FAZ_INVERTER_PREDICTIVE_CONTROL_GLOBAL_VARIABLE_H_
#define UC_FAZ_INVERTER_PREDICTIVE_CONTROL_GLOBAL_VARIABLE_H_

#include "pin_tanimlamalari.h"

typedef enum
{
    Adc_Cevre_Birimi_Hatali,
    Adc_Cevre_Birimi_Calisiyor,
}Adc_durum_t;

typedef struct
{
    UINT8 adc_kontrol_u8;

    UINT32 ADC0Value[3];      // fifo derinliði 4

    float ADC0Value_float[3];

    UINT8 i;

    float voltage_donusturme_katsayisi;

    float analog_cevirme;

    float faz_1_voltage_degeri;     /* FAZ_1 ÝÇÝN; ADC ÝLE OKUNAN DEÐERÝN VOLTAJA ÇEVRÝLMESÝ */

    float faz_2_voltage_degeri;     /* FAZ_2 ÝÇÝN; ADC ÝLE OKUNAN DEÐERÝN VOLTAJA ÇEVRÝLMESÝ */

    float faz_3_voltage_degeri;     /* FAZ_3 ÝÇÝN; ADC ÝLE OKUNAN DEÐERÝN VOLTAJA ÇEVRÝLMESÝ */

    float FAZ_1_Akim_degeri;     /* FAZ_1 ÝÇÝN; ADC ÝLE OKUNAN DEÐERÝN AKIMA ÇEVRÝLMESÝ */

    float FAZ_2_Akim_degeri;     /* FAZ_2 ÝÇÝN; ADC ÝLE OKUNAN DEÐERÝN AKIMA ÇEVRÝLMESÝ */

    float FAZ_3_Akim_degeri;     /* FAZ_3 ÝÇÝN; ADC ÝLE OKUNAN DEÐERÝN AKIMA ÇEVRÝLMESÝ */

    UINT16 FAZ_CEVRIMI_u16;

    float SIN_OFFSET_u16;

    float Akim_genlik_u8;

    float VOLTAGE_OFFSET;

    float Hassasiyet;

    INT8 EKSI_AKIM;

}Adc_okuma_t;

typedef struct
{
    float g_opt;

    float Ts;         // Sampling time of the predictive algorithm [s]

    float L;        // Inductance [H]

    float f_e;      //% Back-EMF frequency [rad/s]

    float f_ref;     // Frequency [rad/s]

    UINT8 flag_u8;

    UINT8 R_u8;          //Resistance [R_u8]

    UINT8 e_u8;        // Back-EMF peak amplitude [V]

    UINT8 I_ref_peak_u8; // Peak amplitude [A]

//    UINT8 dongu_u8;  //algoritmanýn for döngüsü için   MISRA 13.5 için uyarý veriyor for döngüsünden hemen önce yazmamýz gerekiyor.

    UINT8 dizi_u8;

    UINT8 Sa1_u8;
    UINT8 Sb1_u8;
    UINT8 Sc1_u8;

    UINT8 Sa_u8;
    UINT8 Sb_u8;
    UINT8 Sc_u8;

    UINT8 x_opt_u8;
    float g;

    UINT16 Vdc_u16;         // DC-link voltage [V]
    UINT16 VaN_u16;
    UINT16 VbN_u16;
    UINT16 VcN_u16;


    float FAZ_1_Referans_Akim_degeri;        /* FAZ_1 REFERANS AKIM DEÐERÝ */

    float FAZ_2_Referans_Akim_degeri;        /* FAZ_2 REFERANS AKIM DEÐERÝ */

    float FAZ_3_Referans_Akim_degeri;        /* FAZ_3 REFERANS AKIM DEÐERÝ */

    float Vcm;

    float Va0;
    float Vb0;
    float Vc0;

    float I0ak;
    float I0bk;
    float I0ck;

    float elde;


}Algoritma_t;

typedef union{

    struct
    {
        UINT8  kalan_u8    : 2 ;
        UINT8  HZ_1        : 1 ;
        UINT8  HZ_10       : 1 ;
        UINT8  HZ_100      : 1 ;
        UINT8  KHZ_1       : 1 ;
        UINT8  KHZ_40      : 1 ;
        UINT8 zaman_asimi  : 1 ;
    }HZ;

    UINT8 u8;

}Tasklar_t;


typedef struct{

    Tasklar_t tasklar_t;

    UINT32 sistem_saati_u32;

    UINT16 period_u16;

    UINT8 zaman_asimi_u8;

    Adc_durum_t adc_durum_t;

    Adc_okuma_t adc_okuma_t;

    Algoritma_t algoritma_t;



}GL_t;


extern GL_t GL;

#endif /* UC_FAZ_INVERTER_PREDICTIVE_CONTROL_GLOBAL_VARIABLE_H_ */
