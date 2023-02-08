#ifndef LIB_SysTick_H_
#define LIB_SysTick_H_

extern void SysTick_Init(void);
extern void SysTick_Wait(uint32_t delay);
extern void SysTick_Wait100ms(uint32_t delay);

#endif 