
 #include "lib/include.h"

 // modulo 0, generado 0, 1, 2 
 // gen 0 - PB7 (PMW1)
 // gen 1 - PB4 (PMW2)
 // gen 2 - PE4 (PWM4)  pág. 1233 

extern void Configura_Reg_PWM0(uint16_t freq)
{
    //Se habilita modulo PWM0 pag 354
    SYSCTL->RCGCPWM |= (1<<0);
    //Habilitar GPIO Puerto B y E pag 340 y pag. 1233 
    SYSCTL->RCGCGPIO |= (1<<1)|(1<<4);
    //Habilitar el divisor del reloj PWM pag 254 Nota *Se usa otra frecuencia                                                              
    SYSCTL->RCC &=~(1<<20);                                    
    // Habilitar función alternativa  Control de registros ya sea por GPIO o Otros Pag 672
    GPIOB->AFSEL |= (1<<4) | (1<<7); //PB4 PB7
    GPIOE->AFSEL |= (1<<4); //PE4
    //Combinado con la tabla Pag 1351 y el registro PCTL le digo que es pwm Pag 689
    // 4 indica que es PWM 
    GPIOB->PCTL |= (GPIOB->PCTL&0x0FF0FFFF) | 0x40040000; //PB7 y PB4
    GPIOE->PCTL |= (GPIOE->PCTL&0xFFF0FFFF) | 0x00040000; //PE4
    //Para decirle si es digital o no Pag 682
    GPIOB->DEN |= (1<<4)|(1<<7); 
    GPIOE->DEN |= (1<<4); 
    // Salida de PWM 
    GPIOB->DIR |= (1<<4)|(1<<7); 
    GPIOE->DIR |= (1<<4); 
    //Bloqueo y desbloqueo pag 1266, pag 1233 generadores de PWM 
    PWM0->_0_CTL = (0<<0);
    PWM0->_1_CTL = (0<<0);
    PWM0->_2_CTL = (0<<0);
    //Pag 1248  
    PWM0->_0_GENB = 0x0000080C; //PWM1 trabaja con comparador B
    PWM0->_1_GENA = 0x0000008C; //PWM2 trabaja con comparador A 
    PWM0->_2_GENA = 0x0000008C; //PWM4 trabaja con comparador A 
    //cuentas=fclk/fpwm  (20,000,000/2000)=10000 
    PWM0->_0_LOAD = 10000; 
    PWM0->_1_LOAD = 10000;  
    PWM0->_2_LOAD = 10000; 
    PWM0->_0_CMPB = 1500; //Ciclo de trabajo Nota *Regla de 3
    PWM0->_1_CMPA = 1500; 
    PWM0->_2_CMPA = 1500;
    // Se activa el generador 0,1,2
    PWM0->_0_CTL = (1<<0);
    PWM0->_1_CTL = (1<<0);
    PWM0->_2_CTL = (1<<0);
    // habilitar el PWM3,PWM2,PWM4 pag 1248
    PWM0->ENABLE = (1<<1)|(1<<2)|(1<<4); 
}