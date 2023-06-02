//-----------------------------------------------------------------------------
/*

Pulse Width Modulation Driver

*/
//-----------------------------------------------------------------------------

#ifndef PWM_H
#define PWM_H

//-----------------------------------------------------------------------------

#ifndef STM32F4_SOC_H
#warning "please include this file using the toplevel stm32f4_soc.h"
#endif

//-----------------------------------------------------------------------------

enum {
	PWM_CH1,		// == 0
	PWM_CH2,
	PWM_CH3,
	PWM_CH4,
};

struct pwm_cfg {
	uint32_t base;		// base address of TIM2/3/4/5 peripheral
	int freq;		// frequency of PWM pulse
	int bits;		// bits of PWM resolution (1..16)
};

struct pwm_drv {
	TIM_TypeDef *regs;
	uint32_t mask;		// mask for 16/32 bit registers writes
	int shift;		// duty cycle bit shift
};

int pwm_init(struct pwm_drv *drv, struct pwm_cfg *cfg);
void pwm_set_duty_cycle(struct pwm_drv *pwm, int ch, uint16_t duty);
void pwm_enable(struct pwm_drv *pwm, int ch);
void pwm_disable(struct pwm_drv *pwm, int ch);
float pwm_get_frequency(struct pwm_drv *pwm);

//-----------------------------------------------------------------------------

#endif				// PWM_H

//-----------------------------------------------------------------------------
