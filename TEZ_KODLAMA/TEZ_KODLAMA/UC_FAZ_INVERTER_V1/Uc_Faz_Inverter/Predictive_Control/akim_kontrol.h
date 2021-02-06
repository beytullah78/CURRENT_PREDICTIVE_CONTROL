/*
 * akim_kontrol.h
 *
 *  Created on: 19 Eyl 2020
 *      Author: ASUS
 */

#ifndef UC_FAZ_INVERTER_PREDICTIVE_CONTROL_AKIM_KONTROL_H_
#define UC_FAZ_INVERTER_PREDICTIVE_CONTROL_AKIM_KONTROL_H_

#define VEKTOR_SAYICI                   8
#define VEKTOR_CARP                     3


#include "Global_variable.h"
#include "sin_egrisi.h"

#include "inc/hw_memmap.h"
#include "inc/hw_ints.h"
#include "inc/hw_types.h"
#include "math.h"

#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"
#include "driverlib/adc.h"
#include "driverlib/fpu.h"

void mcu_frekansi_ayarlama(void);
void gate_sürücüler_pinler_init(void);
void adc_cevre_birimi_init(void);
void algoritma_init(void);
void gate_sürücüler_enable(void);
void timer_cevre_birimi_init(void);


void adc_okuma(void);
void kontrol_algoritma(void);
void gate_suruculer_pin_reset(void);
void gate_suruculer_vektorler_pinler(void);






#endif /* UC_FAZ_INVERTER_PREDICTIVE_CONTROL_AKIM_KONTROL_H_ */
