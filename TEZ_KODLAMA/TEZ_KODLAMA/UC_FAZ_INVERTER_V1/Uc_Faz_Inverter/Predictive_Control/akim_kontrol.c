/*
 * akim_kontrol.c
 *
 *  Created on: 19 Eyl 2020
 *      Author: ASUS
 */

#include "akim_kontrol.h"


/*
 * Yazan	     :  Mustafa Uður KEBÝR, BEYTULLAH ÇÝÇEKCÝ
 * Fonksiyon adý :	mcu_frekansi_ayarlama
 * Dondurulen    :	void
 * Saat-Tarih	 :  16:23:53 - 19 Eyl 2020
 *
 * Versiyon      :
 * Aciklama	     :
 *
 */
void mcu_frekansi_ayarlama(void)
{

    SysCtlClockSet( SYSCTL_SYSDIV_2_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN );

}

/** Yazan        :  BEYTULLAH ÇÝÇEKCÝ
 * Fonksiyon adý :  gate_sürücüler_pinler_init
 * Dondurulen    :  void
 * Saat-Tarih    :  02:41:44 - 26 Eyl 2020
 *
 * Versiyon      :
 * Aciklama      :
 *
 */
void gate_sürücüler_pinler_init(void)
{

    SysCtlPeripheralEnable( SYSCTL_PERIPH_GPIOA );

    SysCtlPeripheralEnable( SYSCTL_PERIPH_GPIOB );

    SysCtlPeripheralEnable( SYSCTL_PERIPH_GPIOE );

    SysCtlPeripheralEnable( SYSCTL_PERIPH_GPIOC ); // OSÝ


    GPIOPinTypeGPIOOutput( GPIO_PORTA_BASE, GPIO_PIN_5 |  GPIO_PIN_6 );

    GPIOPinTypeGPIOOutput( GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_4 );

    GPIOPinTypeGPIOOutput( GPIO_PORTE_BASE, GPIO_PIN_4);

    GPIOPinTypeGPIOOutput( GPIO_PORTC_BASE, GPIO_PIN_4 | GPIO_PIN_5); // OSÝ


    GPIOPinWrite( GPIO_PORTA_BASE, GPIO_PIN_5, 0 );

    GPIOPinWrite( GPIO_PORTA_BASE, GPIO_PIN_6, 0 );

    GPIOPinWrite( GPIO_PORTB_BASE, GPIO_PIN_0, 0 );

    GPIOPinWrite( GPIO_PORTB_BASE, GPIO_PIN_1, 0 );

    GPIOPinWrite( GPIO_PORTB_BASE, GPIO_PIN_4, 0 );

    GPIOPinWrite( GPIO_PORTE_BASE, GPIO_PIN_4, 0 );

}

/*
 * Yazan         :  MUSTAFA UGUR KEBÝR,BEYTULLAH ÇÝÇEKCÝ
 * Fonksiyon adý :  adc_cevre_birimi_init
 * Dondurulen    :  void
 * Saat-Tarih    :  01:26:44 - 26 Eyl 2020
 *
 * Versiyon      :
 * Aciklama      :
 *
 */
void adc_cevre_birimi_init(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);

    GPIOPinTypeGPIOInput(GPIO_PORTE_BASE, GPIO_PIN_3 | GPIO_PIN_2 |  GPIO_PIN_1 );

    GPIOPinTypeADC( GPIO_PORTE_BASE, GPIO_PIN_3 );

    GPIOPinTypeADC( GPIO_PORTE_BASE, GPIO_PIN_2 );

    GPIOPinTypeADC( GPIO_PORTE_BASE, GPIO_PIN_1 );

    ADCHardwareOversampleConfigure(ADC0_BASE, 2);

    ADCSequenceDisable(ADC0_BASE,0);

    while(!SysCtlPeripheralReady ( SYSCTL_PERIPH_ADC0 ) )
    {
      GL.adc_okuma_t.adc_kontrol_u8=Adc_Cevre_Birimi_Hatali;
    }

    GL.adc_okuma_t.adc_kontrol_u8=Adc_Cevre_Birimi_Calisiyor;

    ADCSequenceConfigure( ADC0_BASE, 0, ADC_TRIGGER_PROCESSOR, 0 );

    ADCSequenceStepConfigure( ADC0_BASE, 0,  0, ADC_CTL_CH0 );

    ADCSequenceStepConfigure( ADC0_BASE, 0,  1, ADC_CTL_CH1 );

    ADCSequenceStepConfigure( ADC0_BASE, 0,  2, ADC_CTL_IE | ADC_CTL_END | ADC_CTL_CH2 );

    ADCSequenceEnable( ADC0_BASE,0 );

    GL.adc_okuma_t.voltage_donusturme_katsayisi = 0.0008700;

    GL.adc_okuma_t.Hassasiyet         =  0.185;

    GL.adc_okuma_t.VOLTAGE_OFFSET     =  2.48;

    GL.adc_okuma_t.FAZ_CEVRIMI_u16    =  0;

    GL.adc_okuma_t.SIN_OFFSET_u16     =  2047;

    GL.adc_okuma_t.Akim_genlik_u8     =  1;

    GL.adc_okuma_t.EKSI_AKIM          = -1;
}

/*
 * Yazan         :  BEYTULLAH ÇÝÇEKCÝ
 * Fonksiyon adý :  algoritma_init
 * Dondurulen    :  void
 * Saat-Tarih    :  19:58:24 - 26 Eyl 2020
 *
 * Versiyon      :
 * Aciklama      :
 *
 */
void algoritma_init(void)
{

   GL.algoritma_t.g_opt = 1*powf(10,10);

   GL.algoritma_t.Ts = 50*powf(10,-6);  // ELLE HESAPLANAN DEÐERLER

   GL.algoritma_t.L = 0.92857;          // ELLE HESAPLANAN DEÐERLER


   //AYARLANACAK OLAN DEÐERLERÝN GÝRÝLMESÝ

   GL.algoritma_t.R_u8 = 5;

 //  GL.algoritma_t.e_u8 = 100;

 // GL.algoritma_t.f_e = 50*(2*M_PI);

   GL.algoritma_t.Vdc_u16 = 30;

   // Current reference

 //  GL.algoritma_t.I_ref_peak_u8 = 1;

   //GL.algoritma_t.f_ref = 50*(2*M_PI);

}

/*
 * Yazan         :  MUSTAFA UGUR KEBÝR,BEYTULLAH ÇÝÇEKCÝ
 * Fonksiyon adý :  gate_sürücüler_enable
 * Dondurulen    :  void
 * Saat-Tarih    :  02:13:45 - 26 Eyl 2020
 *
 * Versiyon      :
 * Aciklama      :
 *
 */
void gate_sürücüler_enable(void)
{
    SysCtlPeripheralEnable( SYSCTL_PERIPH_GPIOB );

    SysCtlPeripheralEnable( SYSCTL_PERIPH_GPIOE );

    GPIOPinTypeGPIOOutput( GPIO_PORTB_BASE , GPIO_PIN_5 );

    GPIOPinTypeGPIOOutput( GPIO_PORTE_BASE , GPIO_PIN_5 );

    GPIOPinWrite( GPIO_PORTB_BASE, GPIO_PIN_5, GPIO_PIN_5 );

    GPIOPinWrite( GPIO_PORTE_BASE, GPIO_PIN_5, GPIO_PIN_5 );
}

/*
 * Yazan	     :  MUSTAFA UGUR KEBÝR,BEYTULLAH ÇÝÇEKCÝ
 * Fonksiyon adý :	timer_cevre_birimleri_init
 * Dondurulen    :	void
 * Saat-Tarih	 :  01:26:12 - 26 Eyl 2020
 *
 * Versiyon      :
 * Aciklama	     :
 *
 */
void timer_cevre_birimi_init(void)
{
    SysCtlPeripheralEnable( SYSCTL_PERIPH_TIMER0 );

    TimerConfigure( TIMER0_BASE, TIMER_CFG_PERIODIC );

    GL.period_u16=SysCtlClockGet()/200000;             //SysCtlClockGet()/30000= 15 KHZ

    TimerLoadSet( TIMER0_BASE, TIMER_A, GL.period_u16 );

    IntEnable( INT_TIMER0A );

    TimerIntEnable( TIMER0_BASE, TIMER_TIMA_TIMEOUT );

    IntMasterEnable();

    TimerEnable( TIMER0_BASE, TIMER_A );

    TimerIntClear( TIMER0_BASE, TIMER_TIMA_TIMEOUT );
}


void adc_okuma(void)
{

    ADCProcessorTrigger(ADC0_BASE, 0); //  tetikleyici açýldý

    while(!ADCIntStatus(ADC0_BASE, 0, false));  // SAMPLE SEQUENCE TAMAMLANANA KADAR BEKLE

    ADCSequenceDataGet(ADC0_BASE, 0, GL.adc_okuma_t.ADC0Value);

    ADCIntClear(ADC0_BASE, 0);

    GL.adc_okuma_t.ADC0Value_float[0] = (float)GL.adc_okuma_t.ADC0Value[0];

    GL.adc_okuma_t.ADC0Value_float[1] = (float)GL.adc_okuma_t.ADC0Value[1];

    GL.adc_okuma_t.ADC0Value_float[2] = (float)GL.adc_okuma_t.ADC0Value[2];

    /* ADC ÝLE OKUNAN DEÐERLERÝN VOLTAJA ÇEVRÝLMESÝ BAÞLADI */

    GL.adc_okuma_t.voltage_donusturme_katsayisi = 0.0008700;

    GL.adc_okuma_t.faz_1_voltage_degeri =  GL.adc_okuma_t.voltage_donusturme_katsayisi * GL.adc_okuma_t.ADC0Value_float[0];      // *1.09 direnç bölücü sebebiyle çarpmaa ile ters iþlem yaparak sensörün direkt output'a eþit oldu

    GL.adc_okuma_t.faz_2_voltage_degeri =  GL.adc_okuma_t.voltage_donusturme_katsayisi * GL.adc_okuma_t.ADC0Value_float[1];

    GL.adc_okuma_t.faz_3_voltage_degeri =  GL.adc_okuma_t.voltage_donusturme_katsayisi * GL.adc_okuma_t.ADC0Value_float[2];

    /* ADC ÝLE OKUNAN DEÐERLERÝN VOLTAJA ÇEVRÝLMESÝ BÝTTÝ */


    /* ADC_VOLTAJI ----------> AKIMA ÇEVRÝLMESÝ BAÞLADI */

    //FAZ 3

      if(GL.adc_okuma_t.faz_3_voltage_degeri>2.48)
       {
          GL.adc_okuma_t.FAZ_3_Akim_degeri=  (GL.adc_okuma_t.faz_3_voltage_degeri - GL.adc_okuma_t.VOLTAGE_OFFSET)/GL.adc_okuma_t.Hassasiyet;// 0.000 is a value to make voltage zero when there is no current
       }
      else if(1.62<GL.adc_okuma_t.faz_3_voltage_degeri && GL.adc_okuma_t.faz_3_voltage_degeri< 2.48)  // -5 amper 1.62 ye denk geliyor daha küçük olamazz o yüzden sýnýrlandýrdýk.
       {
          GL.adc_okuma_t.FAZ_3_Akim_degeri=  (((GL.adc_okuma_t.VOLTAGE_OFFSET - GL.adc_okuma_t.faz_3_voltage_degeri)/GL.adc_okuma_t.Hassasiyet)*GL.adc_okuma_t.EKSI_AKIM);// 0.000 is a value to make voltage zero when there is no current
       }
       else
       {
           GL.adc_okuma_t.FAZ_3_Akim_degeri=0;
       }

      //FAZ 2

      if(GL.adc_okuma_t.faz_2_voltage_degeri>2.48)
       {
          GL.adc_okuma_t.FAZ_2_Akim_degeri=  (GL.adc_okuma_t.faz_2_voltage_degeri - GL.adc_okuma_t.VOLTAGE_OFFSET)/GL.adc_okuma_t.Hassasiyet;// 0.000 is a value to make voltage zero when there is no current
       }
      else if(1.62<GL.adc_okuma_t.faz_2_voltage_degeri && GL.adc_okuma_t.faz_2_voltage_degeri< 2.48)  // -5 amper 1.62 ye denk geliyor daha küçük olamazz o yüzden sýnýrlandýrdýk.
       {
          GL.adc_okuma_t.FAZ_2_Akim_degeri=  (((GL.adc_okuma_t.VOLTAGE_OFFSET - GL.adc_okuma_t.faz_2_voltage_degeri)/GL.adc_okuma_t.Hassasiyet)*GL.adc_okuma_t.EKSI_AKIM);// 0.000 is a value to make voltage zero when there is no current
       }
       else
       {
          GL.adc_okuma_t.FAZ_2_Akim_degeri=0;
       }

     //FAZ 1
      if(GL.adc_okuma_t.faz_1_voltage_degeri>2.48)
       {
          GL.adc_okuma_t.FAZ_1_Akim_degeri=  (GL.adc_okuma_t.faz_1_voltage_degeri - GL.adc_okuma_t.VOLTAGE_OFFSET)/GL.adc_okuma_t.Hassasiyet;// 0.000 is a value to make voltage zero when there is no current
       }
      else if(1.62<GL.adc_okuma_t.faz_1_voltage_degeri && GL.adc_okuma_t.faz_1_voltage_degeri< 2.48)  // -5 amper 1.62 ye denk geliyor daha küçük olamazz o yüzden sýnýrlandýrdýk.
       {
          GL.adc_okuma_t.FAZ_1_Akim_degeri=  (((GL.adc_okuma_t.VOLTAGE_OFFSET - GL.adc_okuma_t.faz_1_voltage_degeri)/GL.adc_okuma_t.Hassasiyet)*GL.adc_okuma_t.EKSI_AKIM);// 0.000 is a value to make voltage zero when there is no current
       }
       else
       {
           GL.adc_okuma_t.FAZ_1_Akim_degeri=0;
       }

      /* ADC_VOLTAJI ----------> AKIMA ÇEVRÝLMESÝ BITTI */


 /*  REFERANS AKIMLARININ SÝNÜS SÝNYALÝNE GÖRE ÜRETÝRMESÝ BAÞLADI  */

    GL.adc_okuma_t.FAZ_CEVRIMI_u16++;

    GL.algoritma_t.FAZ_1_Referans_Akim_degeri = ( ( sin_egrisi.faz1[ GL.adc_okuma_t.FAZ_CEVRIMI_u16]- GL.adc_okuma_t.SIN_OFFSET_u16  ) / GL.adc_okuma_t.SIN_OFFSET_u16) * GL.adc_okuma_t.Akim_genlik_u8 ;

    GL.algoritma_t.FAZ_2_Referans_Akim_degeri = ( ( sin_egrisi.faz2[ GL.adc_okuma_t.FAZ_CEVRIMI_u16]- GL.adc_okuma_t.SIN_OFFSET_u16  ) / GL.adc_okuma_t.SIN_OFFSET_u16) * GL.adc_okuma_t.Akim_genlik_u8 ;

    GL.algoritma_t.FAZ_3_Referans_Akim_degeri = ( ( sin_egrisi.faz3[ GL.adc_okuma_t.FAZ_CEVRIMI_u16]- GL.adc_okuma_t.SIN_OFFSET_u16  ) / GL.adc_okuma_t.SIN_OFFSET_u16) * GL.adc_okuma_t.Akim_genlik_u8 ;


    if( GL.adc_okuma_t.FAZ_CEVRIMI_u16 > 399)
    {

        GL.adc_okuma_t.FAZ_CEVRIMI_u16=0;

    }

 /*  REFERANS AKIMLARININ SÝNÜS SÝNYALÝNE GÖRE ÜRETÝRMESÝ BÝTTÝ  */



}

void kontrol_algoritma(void)
{

    float a= 0.285;
    float b= 0.143;

            GL.algoritma_t.I0ak =  ( GL.adc_okuma_t.FAZ_1_Akim_degeri * GL.algoritma_t.L ) ;           // FAZ_1_u16 deðiþkenine bak
            GL.algoritma_t.I0bk =  ( GL.adc_okuma_t.FAZ_2_Akim_degeri * GL.algoritma_t.L ) ;
            GL.algoritma_t.I0ck =  ( GL.adc_okuma_t.FAZ_3_Akim_degeri * GL.algoritma_t.L ) ;

            GL.algoritma_t.g =  fabsf( GL.algoritma_t.FAZ_1_Referans_Akim_degeri - GL.algoritma_t.I0ak ) + fabsf( GL.algoritma_t.FAZ_2_Referans_Akim_degeri - GL.algoritma_t.I0bk ) + fabsf( GL.algoritma_t.FAZ_3_Referans_Akim_degeri - GL.algoritma_t.I0ck );

            if ( GL.algoritma_t.g  < GL.algoritma_t.g_opt )
            {
                GL.algoritma_t.g_opt = GL.algoritma_t.g;

                GL.algoritma_t.Sa_u8 = 0;
                GL.algoritma_t.Sb_u8 = 0;
                GL.algoritma_t.Sc_u8 = 0;
            }

            GL.algoritma_t.I0ak =  a  +  ( GL.adc_okuma_t.FAZ_1_Akim_degeri * GL.algoritma_t.L ) ;
            GL.algoritma_t.I0bk = ( GL.adc_okuma_t.FAZ_2_Akim_degeri * GL.algoritma_t.L ) - b ;
            GL.algoritma_t.I0ck = ( GL.adc_okuma_t.FAZ_3_Akim_degeri * GL.algoritma_t.L ) - b ;

            GL.algoritma_t.g =  fabsf( GL.algoritma_t.FAZ_1_Referans_Akim_degeri - GL.algoritma_t.I0ak ) + fabsf( GL.algoritma_t.FAZ_2_Referans_Akim_degeri - GL.algoritma_t.I0bk ) + fabsf( GL.algoritma_t.FAZ_3_Referans_Akim_degeri - GL.algoritma_t.I0ck );

            if ( GL.algoritma_t.g  < GL.algoritma_t.g_opt )
            {
                GL.algoritma_t.g_opt = GL.algoritma_t.g;

                GL.algoritma_t.Sa_u8 = 1;
                GL.algoritma_t.Sb_u8 = 0;
                GL.algoritma_t.Sc_u8 = 0;
            }


            GL.algoritma_t.I0ak =  b  + ( GL.adc_okuma_t.FAZ_1_Akim_degeri * GL.algoritma_t.L ) ;           // FAZ_1_u16 deðiþkenine bak
            GL.algoritma_t.I0bk =  b  + ( GL.adc_okuma_t.FAZ_2_Akim_degeri * GL.algoritma_t.L ) ;
            GL.algoritma_t.I0ck =  ( GL.adc_okuma_t.FAZ_3_Akim_degeri * GL.algoritma_t.L ) - a  ;

            GL.algoritma_t.g =  fabsf( GL.algoritma_t.FAZ_1_Referans_Akim_degeri - GL.algoritma_t.I0ak ) + fabsf( GL.algoritma_t.FAZ_2_Referans_Akim_degeri - GL.algoritma_t.I0bk ) + fabsf( GL.algoritma_t.FAZ_3_Referans_Akim_degeri - GL.algoritma_t.I0ck );

            if ( GL.algoritma_t.g  < GL.algoritma_t.g_opt )
            {
                GL.algoritma_t.g_opt = GL.algoritma_t.g;

                GL.algoritma_t.Sa_u8 = 1;
                GL.algoritma_t.Sb_u8 = 1;
                GL.algoritma_t.Sc_u8 = 0;
            }


            GL.algoritma_t.I0ak =  ( GL.adc_okuma_t.FAZ_1_Akim_degeri * GL.algoritma_t.L ) - b ;           // FAZ_1_u16 deðiþkenine bak
            GL.algoritma_t.I0bk =  a + ( GL.adc_okuma_t.FAZ_2_Akim_degeri * GL.algoritma_t.L ) ;
            GL.algoritma_t.I0ck =  ( GL.adc_okuma_t.FAZ_3_Akim_degeri * GL.algoritma_t.L ) - b ;

            GL.algoritma_t.g =  fabsf( GL.algoritma_t.FAZ_1_Referans_Akim_degeri - GL.algoritma_t.I0ak ) + fabsf( GL.algoritma_t.FAZ_2_Referans_Akim_degeri - GL.algoritma_t.I0bk ) + fabsf( GL.algoritma_t.FAZ_3_Referans_Akim_degeri - GL.algoritma_t.I0ck );

            if ( GL.algoritma_t.g  < GL.algoritma_t.g_opt )
            {
                GL.algoritma_t.g_opt = GL.algoritma_t.g;

                GL.algoritma_t.Sa_u8 = 0;
                GL.algoritma_t.Sb_u8 = 1;
                GL.algoritma_t.Sc_u8 = 0;
            }

            GL.algoritma_t.I0ak =  ( GL.adc_okuma_t.FAZ_1_Akim_degeri * GL.algoritma_t.L ) - a;
            GL.algoritma_t.I0bk =  b +  ( GL.adc_okuma_t.FAZ_2_Akim_degeri * GL.algoritma_t.L ) ;
            GL.algoritma_t.I0ck =  b +  ( GL.adc_okuma_t.FAZ_3_Akim_degeri * GL.algoritma_t.L ) ;

            GL.algoritma_t.g =  fabsf( GL.algoritma_t.FAZ_1_Referans_Akim_degeri - GL.algoritma_t.I0ak ) + fabsf( GL.algoritma_t.FAZ_2_Referans_Akim_degeri - GL.algoritma_t.I0bk ) + fabsf( GL.algoritma_t.FAZ_3_Referans_Akim_degeri - GL.algoritma_t.I0ck );

            if ( GL.algoritma_t.g  < GL.algoritma_t.g_opt )
            {
                GL.algoritma_t.g_opt = GL.algoritma_t.g;

                GL.algoritma_t.Sa_u8 = 0;
                GL.algoritma_t.Sb_u8 = 1;
                GL.algoritma_t.Sc_u8 = 1;
            }


            GL.algoritma_t.I0ak =  ( GL.adc_okuma_t.FAZ_1_Akim_degeri * GL.algoritma_t.L ) - b ;           // FAZ_1_u16 deðiþkenine bak
            GL.algoritma_t.I0bk =  ( GL.adc_okuma_t.FAZ_2_Akim_degeri * GL.algoritma_t.L ) - b ;
            GL.algoritma_t.I0ck =  a + ( GL.adc_okuma_t.FAZ_3_Akim_degeri * GL.algoritma_t.L ) ;

            GL.algoritma_t.g =  fabsf( GL.algoritma_t.FAZ_1_Referans_Akim_degeri - GL.algoritma_t.I0ak ) + fabsf( GL.algoritma_t.FAZ_2_Referans_Akim_degeri - GL.algoritma_t.I0bk ) + fabsf( GL.algoritma_t.FAZ_3_Referans_Akim_degeri - GL.algoritma_t.I0ck );

            if ( GL.algoritma_t.g  < GL.algoritma_t.g_opt )
            {
                GL.algoritma_t.g_opt = GL.algoritma_t.g;

                GL.algoritma_t.Sa_u8 = 0;
                GL.algoritma_t.Sb_u8 = 0;
                GL.algoritma_t.Sc_u8 = 1;
            }


            GL.algoritma_t.I0ak =  b  + ( GL.adc_okuma_t.FAZ_1_Akim_degeri * GL.algoritma_t.L ) ;           // FAZ_1_u16 deðiþkenine bak
            GL.algoritma_t.I0bk =  ( GL.adc_okuma_t.FAZ_2_Akim_degeri * GL.algoritma_t.L ) - a ;
            GL.algoritma_t.I0ck =  b + ( GL.adc_okuma_t.FAZ_3_Akim_degeri * GL.algoritma_t.L ) ;

            GL.algoritma_t.g =  fabsf( GL.algoritma_t.FAZ_1_Referans_Akim_degeri - GL.algoritma_t.I0ak ) + fabsf( GL.algoritma_t.FAZ_2_Referans_Akim_degeri - GL.algoritma_t.I0bk ) + fabsf( GL.algoritma_t.FAZ_3_Referans_Akim_degeri - GL.algoritma_t.I0ck );

            if ( GL.algoritma_t.g  < GL.algoritma_t.g_opt )
            {
                GL.algoritma_t.g_opt = GL.algoritma_t.g;

                GL.algoritma_t.Sa_u8 = 1;
                GL.algoritma_t.Sb_u8 = 0;
                GL.algoritma_t.Sc_u8 = 1;
            }


            GL.algoritma_t.I0ak =  ( GL.adc_okuma_t.FAZ_1_Akim_degeri * GL.algoritma_t.L ) ;           // FAZ_1_u16 deðiþkenine bak
            GL.algoritma_t.I0bk =  ( GL.adc_okuma_t.FAZ_2_Akim_degeri * GL.algoritma_t.L ) ;
            GL.algoritma_t.I0ck =  ( GL.adc_okuma_t.FAZ_3_Akim_degeri * GL.algoritma_t.L ) ;

            GL.algoritma_t.g =  fabsf( GL.algoritma_t.FAZ_1_Referans_Akim_degeri - GL.algoritma_t.I0ak ) + fabsf( GL.algoritma_t.FAZ_2_Referans_Akim_degeri - GL.algoritma_t.I0bk ) + fabsf( GL.algoritma_t.FAZ_3_Referans_Akim_degeri - GL.algoritma_t.I0ck );

            if ( GL.algoritma_t.g  < GL.algoritma_t.g_opt )
            {
                GL.algoritma_t.g_opt = GL.algoritma_t.g;

                GL.algoritma_t.Sa_u8 = 1;
                GL.algoritma_t.Sb_u8 = 1;
                GL.algoritma_t.Sc_u8 = 1;
            }

}
/*
INT dongu_u8 * Yazan	     :  BEYTULLAH ÇÝÇEKCÝ
 * Fonksiyon adý :	gate_sürücüler_pin_reset
 * Dondurulen    :	void
 * Saat-Tarih	 :  00:58:55 - 1 Eki 2020
 *
 * Versiyon      :
 * Aciklama	     :
 *
 */
void gate_suruculer_pin_reset(void)
{

    GPIOPinWrite( GPIO_PORTA_BASE, GPIO_PIN_5, 0 );

    GPIOPinWrite( GPIO_PORTA_BASE, GPIO_PIN_6, 0 );

    GPIOPinWrite( GPIO_PORTB_BASE, GPIO_PIN_0, 0 );

    GPIOPinWrite( GPIO_PORTB_BASE, GPIO_PIN_1, 0 );

    GPIOPinWrite( GPIO_PORTB_BASE, GPIO_PIN_4, 0 );

    GPIOPinWrite( GPIO_PORTE_BASE, GPIO_PIN_4, 0 );

}

/*
 * Yazan	     :  BEYTULLAH ÇÝÇEKCÝ
 * Fonksiyon adý :	gate_sürücüler_vektörler_pinler
 * Dondurulen    :	void
 * Saat-Tarih	 :  18:12:54 - 1 Eki 2020
 *
 * Versiyon      :
 * Aciklama	     :
 *
 */
void gate_suruculer_vektorler_pinler(void)
{

     GPIOPinWrite( GPIO_PORTB_BASE, GPIO_PIN_5, GPIO_PIN_5 );

     GPIOPinWrite( GPIO_PORTE_BASE, GPIO_PIN_5, GPIO_PIN_5 );

    if( GL.algoritma_t.Sa_u8 == 1 )
    {
        GPIOPinWrite( GPIO_PORTE_BASE, GPIO_PIN_4 , GPIO_PIN_4 );

        GPIOPinWrite( GPIO_PORTA_BASE, GPIO_PIN_6 , 0 );
    }
    else
    {
       GPIOPinWrite( GPIO_PORTE_BASE, GPIO_PIN_4 , 0 );

       GPIOPinWrite( GPIO_PORTA_BASE, GPIO_PIN_6 ,  GPIO_PIN_6 );  // gerçekte olan
    }


    if( GL.algoritma_t.Sb_u8 == 1 )
    {
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_1, GPIO_PIN_1);

        GPIOPinWrite( GPIO_PORTA_BASE, GPIO_PIN_5 , 0 );
    }
    else
    {
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_1, 0);

       GPIOPinWrite( GPIO_PORTA_BASE, GPIO_PIN_5 , GPIO_PIN_5 ); // gerçekte olan
    }


    if( GL.algoritma_t.Sc_u8 == 1 )
    {
        GPIOPinWrite( GPIO_PORTB_BASE, GPIO_PIN_0 , GPIO_PIN_0 );

        GPIOPinWrite( GPIO_PORTB_BASE, GPIO_PIN_4 , 0 );
    }
    else
    {
        GPIOPinWrite( GPIO_PORTB_BASE, GPIO_PIN_0 , 0 );

        GPIOPinWrite( GPIO_PORTB_BASE, GPIO_PIN_4 , GPIO_PIN_4 ); //gerçekte bu olacak

    }

}

