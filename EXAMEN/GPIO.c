#include "lib/include.h"
extern void Configurar_GPIO(void)
{
    //Se habilita el puerto a usar 
    SYSCTL->RCGCGPIO |=(1<<0);  //pueto A
    
    //Desabilita la función analogica del puerto, para funcionar como GPIO pag. 687
    GPIOA->AMSEL = 0x00; 
    //Indicar que los pines a trabajan como GPIO son PA7-0
    GPIOA->PCTL = 0x00000000;   
    //Para indicar que pines son entradas y cuales son salida 0 -> entrada, 1 -> salida 
    GPIOA->DIR = (0<<2) | (0<<3) | (0<<4) | (0<<5) | (0<<6) | (0<<7); // PA2 - PA7 son entradas 
    //Se desabilita la función alternativa  PA7-0
    GPIOA->AFSEL = 0x00;   
    // Para habilitar que el edo. inicial de los pines sea pull-up O pull-down pag. 678
    GPIOA->PUR = (1<<2) | (1<<3) | (1<<4) | (1<<5) | (1<<6) | (1<<7);// PA2 - PA7 CONFIGURADO PULL UP
    //Se habilitan los pines como digitales PA5-PA0
    GPIOA->DEN = (1<<2) | (1<<3) | (1<<4) | (1<<5) | (1<<6) | (1<<7);     
    //pag. 667 Se limpian los pines a los que se asocian las interrupciones para poderlas configurar 
    GPIOA -> IM |= (0<<2) | (0<<3) | (0<<4) | (0<<5) | (0<<6) | (0<<7);
    //pag. 664 Configurar que sea sensible al borde 
     GPIOA -> IS |= (0<<2) | (0<<3) | (0<<4) | (0<<5) | (0<<6) | (0<<7);
    //pag. 665 registro para indicar que el IEV va a configurar que flancos detectar
    GPIOA -> IBE |= (0<<2) | (0<<3) | (0<<4) | (0<<5) | (0<<6) | (0<<7);
    //pag. 666 Indicar con que flanco trabaja 
    GPIOA -> IEV |= (1<<2) | (1<<3) | (1<<4) | (1<<5) | (1<<6) | (1<<7); //es con flanco de subida
    //pag. 668 establecer que no ha ocurrido ninguna interrupción en esos pines (edo inicial)
    GPIOA -> RIS |= (0<<2) | (0<<3) | (0<<4) | (0<<5) | (0<<6) | (0<<7);
    //PAG. 667 La interrupción del pin es enviada al controlador de interrup.
    GPIOA -> IM |= (1<<2) | (1<<3) | (1<<4) | (1<<5) | (1<<6) | (1<<7);

 
    //INTERRUPCIÓN
    //pag. 104 
    //GPIO A -> INTERRUPCION 0
    //Pag. 153 tiva ch, 160 tiva gde para saber que se le suma: [4n+3] [4n+2] [4n+1] [4n]
    // bloque de int. 3       2      1    0      
    //              [4n+3] [4n+2] [4n+1] [4n] ---> [4n] = 0(valor de la int) : n=0  (n es el # de prioridad)
    //                FF    FF      FF    00    (los 00 indica lo que se le suma)
    NVIC -> IP[0] = (NVIC ->IP[0]&0xFFFFFF00) | 0x00000020; //0 es el numero de prioridad (n), el 2 es la jerarquía y se pone en la posición que cae la int. según pag. 153 tiva ch

    // Habilitar interrupción pag. 142 tiva ch 
    NVIC -> ISER[0] = (1<<0); //0x00000001; //Se pone 1 en la interrupción 0 
}

extern void Delay(void)
{
  unsigned long volatile time;
  time = 1600000;
  while(time)
  {
		time--;
  }
}
