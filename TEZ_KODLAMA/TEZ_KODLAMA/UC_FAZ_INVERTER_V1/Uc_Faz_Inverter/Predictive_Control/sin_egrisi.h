/*
 * sin_egrisi.h
 *
 *  Created on: 26 Eyl 2020
 *      Author: ASUS
 */

#ifndef UC_FAZ_INVERTER_PREDICTIVE_CONTROL_SIN_EGRISI_H_
#define UC_FAZ_INVERTER_PREDICTIVE_CONTROL_SIN_EGRISI_H_

#define M_PI            3.14159265358979323846

#define Seri_Uzunlugu  400

#include "pin_tanimlamalari.h"
#include "math.h"

typedef struct{

    UINT16  faz1[Seri_Uzunlugu];
    UINT16  faz2[Seri_Uzunlugu];
    UINT16  faz3[Seri_Uzunlugu];

    float Faz_Farki_120;
    float Faz_Farki_240;

    float fRadians;
    float radians;
    float hypotenuse;

    float faz_1_amplitude;
    float faz_2_amplitude;
    float faz_3_amplitude;

}Sin_egrisi_t;


void sin_egrisi_oluþturma(void);


extern Sin_egrisi_t sin_egrisi;



#endif /* UC_FAZ_INVERTER_PREDICTIVE_CONTROL_SIN_EGRISI_H_ */
