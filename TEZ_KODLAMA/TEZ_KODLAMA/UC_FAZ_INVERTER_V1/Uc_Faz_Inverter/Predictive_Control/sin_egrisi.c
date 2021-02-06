/*
 * sin_egrisi.c
 *
 *  Created on: 26 Eyl 2020
 *      Author: ASUS
 */


#include "sin_egrisi.h"

Sin_egrisi_t sin_egrisi={0};

/*
 * Yazan	     :  BEYTULLAH ÇÝÇEKCÝ
 * Fonksiyon adý :	sin_egrisi_oluþturma
 * Dondurulen    :	void
 * Saat-Tarih	 :  19:59:06 - 26 Eyl 2020
 *
 * Versiyon      :
 * Aciklama	     :
 *
 */
void sin_egrisi_oluþturma(void)
{
    sin_egrisi.fRadians   = ( ( M_PI*2 )   / Seri_Uzunlugu );
    sin_egrisi.hypotenuse = ( ( 4096 - 1 ) / 2 ) ;



    sin_egrisi.Faz_Farki_120 = 2.0944   ;

    sin_egrisi.Faz_Farki_240 = 2.0944*2 ;

    UINT16 Veri_sayici_u16=0;

    while( Veri_sayici_u16 < Seri_Uzunlugu )
    {

        sin_egrisi.radians = Veri_sayici_u16 * sin_egrisi.fRadians;

        sin_egrisi.faz_1_amplitude = sin( sin_egrisi.radians ) * sin_egrisi.hypotenuse;

        sin_egrisi.faz_2_amplitude = sin( sin_egrisi.radians + sin_egrisi.Faz_Farki_120 ) * sin_egrisi.hypotenuse;

        sin_egrisi.faz_3_amplitude = sin( sin_egrisi.radians + sin_egrisi.Faz_Farki_240 ) * sin_egrisi.hypotenuse;


        sin_egrisi.faz_1_amplitude = ( sin_egrisi.faz_1_amplitude + sin_egrisi.hypotenuse ) ;

        sin_egrisi.faz_2_amplitude = ( sin_egrisi.faz_2_amplitude + sin_egrisi.hypotenuse ) ;

        sin_egrisi.faz_3_amplitude = ( sin_egrisi.faz_3_amplitude + sin_egrisi.hypotenuse ) ;

        sin_egrisi.faz1[Veri_sayici_u16] = ( INT )round( sin_egrisi.faz_1_amplitude );

        sin_egrisi.faz2[Veri_sayici_u16] = ( INT )round( sin_egrisi.faz_2_amplitude );

        sin_egrisi.faz3[Veri_sayici_u16] = ( INT )round( sin_egrisi.faz_3_amplitude );

        Veri_sayici_u16++;
    }

}

