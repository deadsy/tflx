//-----------------------------------------------------------------------------
/*

Pulse Width Modulation Driver

Use the general purpose timers (TIM2/3/4/5) to implement 4 channels of PWM per timer.

These timers have either 16 or 32 bit counters.
This driver uses only 16 bit counters, so all timers are functionally equivalent.

The duty cycle in the API ranges from 0..65535 (16 bits).
The ARR value is selected to be n-1 bits, where n is the PWM resolution.
The desired duty cycle is right shifted to match the ARR range.

Given an ARR value (resolution) it may not be possible to derive the exact PWM
frequency requested. The generated PWM frequency is available as a float so
the duty cycle can be calculated for accurate pulse timing.

*/
//-----------------------------------------------------------------------------

#include <string.h>

#include "stm32f4_soc.h"
#include "utils.h"

#define DEBUG
#include "logging.h"

//-----------------------------------------------------------------------------

#define CK_PSC 84000000.f	// 84 MHz

static uint32_t arr_val(int bits) {
	return (uint32_t) ((1 << bits) - 1);
}

static uint32_t psc_val(int freq, uint32_t arr) {
	float x = (float)arr + 1.f;
	float psc = (CK_PSC / (x * (float)freq)) - 1.f;
	return (uint32_t) psc;
}

float pwm_get_frequency(struct pwm_drv *pwm) {
	float arr = (float)pwm->regs->ARR;
	float psc = (float)pwm->regs->PSC;
	return CK_PSC / ((arr + 1.f) * (psc + 1.f));
}

//-----------------------------------------------------------------------------

// enable pwm on a channel
void pwm_enable(struct pwm_drv *pwm, int ch) {
	ch &= 3;
	DBG("pwm_enable ch %d\r\n", ch);
	uint32_t bits = 1 << (ch << 2);	// bits 0,4,8,12
	reg_set(&pwm->regs->CCER, bits);
}

// disable pwm on a channel
void pwm_disable(struct pwm_drv *pwm, int ch) {
	ch &= 3;
	DBG("pwm_disable ch %d\r\n", ch);
	uint32_t bits = 1 << (ch << 2);	// bits 0,4,8,12
	reg_clr(&pwm->regs->CCER, bits);
}

// set the pwm duty cycle for the channel
void pwm_set_duty_cycle(struct pwm_drv *pwm, int ch, uint16_t duty) {
	ch &= 3;
	duty >>= pwm->shift;
	DBG("pwm_duty_cycle ch %d 0x%04x\r\n", ch, duty);
	volatile uint32_t *ccr = &pwm->regs->CCR1;
	reg_rmw(&ccr[ch], pwm->mask, duty);
}

//-----------------------------------------------------------------------------

#define TIM_CR1_MASK (0x03ff)
#define TIM_CR2_MASK (0x00f8)
#define TIM_SMCR_MASK (0xfff7)
#define TIM_DIER_MASK (0x5f5f)
#define TIM_CCER_MASK (0xbbbb)
#define TIM_DCR_MASK (0x1f1f)
#define TIM_DMAR_MASK (0xffff)
#define TIM_PSC_MASK (0xffff)
#define TIM_CCMR_MASK (0xffff)
#define TIM2_OR_MASK (0x0c00)
#define TIM5_OR_MASK (0x00c0)
#define TIM_SR_MASK (0x1e5f)

#define PWM_16BIT 0xffff
#define PWM_32BIT 0xffffffff

int pwm_init(struct pwm_drv *pwm, struct pwm_cfg *cfg) {

	if (cfg->freq < 0) {
		DBG("bad pwm frequency\r\n");
		return -1;
	}

	if ((cfg->bits <= 0) || (cfg->bits > 16)) {
		DBG("bad pwm resolution\r\n");
		return -1;
	}

	memset(pwm, 0, sizeof(struct pwm_drv));

	// enable the clock to the timer
	if (cfg->base == TIM2_BASE) {
		RCC->APB1ENR |= (1 << 0 /*TIM2EN */ );
		pwm->mask = PWM_32BIT;
	} else if (cfg->base == TIM3_BASE) {
		RCC->APB1ENR |= (1 << 1 /*TIM3EN */ );
		pwm->mask = PWM_16BIT;
	} else if (cfg->base == TIM4_BASE) {
		RCC->APB1ENR |= (1 << 2 /*TIM4EN */ );
		pwm->mask = PWM_16BIT;
	} else if (cfg->base == TIM5_BASE) {
		RCC->APB1ENR |= (1 << 3 /*TIM5EN */ );
		pwm->mask = PWM_32BIT;
	} else {
		DBG("bad pwm base address\r\n");
		return -1;
	}

	pwm->regs = (TIM_TypeDef *) cfg->base;

	// TIM control registers
	reg_rmw(&pwm->regs->CR1, TIM_CR1_MASK, 0);
	reg_rmw(&pwm->regs->CR2, TIM_CR2_MASK, 0);

	// TIM slave mode control register
	reg_rmw(&pwm->regs->SMCR, TIM_SMCR_MASK, 0);

	// TIM DMA/interrupt enable register
	reg_rmw(&pwm->regs->DIER, TIM_DIER_MASK, 0);

	// TIM status register
	reg_rmw(&pwm->regs->SR, TIM_SR_MASK, 0);

	// TIM capture/compare mode register 1
	uint32_t val = 0;
	val |= (0 << 15 /*OC2CE */ );
	val |= (6 << 12 /*OC2M */ );	// pwm mode 1
	val |= (1 << 11 /*OC2PE */ );	// enable preload
	val |= (0 << 10 /*OC2FE */ );
	val |= (0 << 8 /*CC2S */ );
	val |= (0 << 7 /*OC1CE */ );
	val |= (6 << 4 /*OC1M */ );	// pwm mode 1
	val |= (1 << 3 /*OC1PE */ );	// enable preload
	val |= (0 << 2 /*OC1FE */ );
	val |= (0 << 0 /*CC1S */ );
	reg_rmw(&pwm->regs->CCMR1, TIM_CCMR_MASK, val);

	// TIM capture/compare mode register 2
	val = 0;
	val |= (0 << 15 /*OC4CE */ );
	val |= (6 << 12 /*OC4M */ );	// pwm mode 1
	val |= (1 << 11 /*OC4PE */ );	// enable preload
	val |= (0 << 10 /*OC4FE */ );
	val |= (0 << 8 /*CC4S */ );
	val |= (0 << 7 /*OC3CE */ );
	val |= (6 << 4 /*OC3M */ );	// pwm mode 1
	val |= (1 << 3 /*OC3PE */ );	// enable preload
	val |= (0 << 2 /*OC3FE */ );
	val |= (0 << 0 /*CC3S */ );
	reg_rmw(&pwm->regs->CCMR2, TIM_CCMR_MASK, val);

	// TIM capture/compare enable register
	reg_rmw(&pwm->regs->CCER, TIM_CCER_MASK, 0);

	// TIM counter register
	reg_rmw(&pwm->regs->CNT, pwm->mask, 0);

	// TIM auto-reload register
	uint32_t arr = arr_val(cfg->bits);
	reg_rmw(&pwm->regs->ARR, pwm->mask, arr);
	pwm->shift = 16 - cfg->bits;

	// TIM prescaler
	reg_rmw(&pwm->regs->PSC, TIM_PSC_MASK, psc_val(cfg->freq, arr));

	// TIM capture/compare register 1..4
	reg_rmw(&pwm->regs->CCR1, pwm->mask, 0);
	reg_rmw(&pwm->regs->CCR2, pwm->mask, 0);
	reg_rmw(&pwm->regs->CCR3, pwm->mask, 0);
	reg_rmw(&pwm->regs->CCR4, pwm->mask, 0);

	// TIM DMA control register
	reg_rmw(&pwm->regs->DCR, TIM_DCR_MASK, 0);

	// TIM DMA address for full transfer
	reg_rmw(&pwm->regs->DMAR, TIM_DMAR_MASK, 0);

	// TIM option register
	if (cfg->base == TIM2_BASE) {
		reg_rmw(&pwm->regs->OR, TIM2_OR_MASK, 0);
	}
	if (cfg->base == TIM5_BASE) {
		reg_rmw(&pwm->regs->OR, TIM5_OR_MASK, 0);
	}
	// TIM control register 1
	val = 0;
	val |= (0 << 8 /*CKD*/);	// Clock division
	val |= (1 << 7 /*ARPE*/);	// Auto-reload preload enable
	val |= (0 << 5 /*CMS*/);	// Center-aligned mode selection
	val |= (0 << 4 /*DIR*/);	// Direction
	val |= (0 << 3 /*OPM*/);	// One-pulse mode
	val |= (0 << 2 /*URS*/);	// Update request source
	val |= (0 << 1 /*UDIS*/);	// Update disable
	val |= (1 << 0 /*CEN*/);	// Counter enable
	reg_rmw(&pwm->regs->CR1, TIM_CR1_MASK, val);

	// TIM event generation register
	reg_set(&pwm->regs->EGR, 1 << 0 /*UG*/);

	return 0;
}

//-----------------------------------------------------------------------------
