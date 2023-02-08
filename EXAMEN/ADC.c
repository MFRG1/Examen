#include "lib/include.h"

extern void Configura_Reg_ADC0(void)
{
    
    //Pag 352 tiva ch, 396 tiva gde
    //Para inicializar el modulo de reloj del adc RCGCADC, se habilita el modulo que se usa
    SYSCTL->RCGCADC = (1<<0);  //Inicializar  del reloj del adc  (RCGCADC), pag. 352 se habilita el modulo 1 y 0
    
    //Pag 340 tiva ch, pag. 382 tiva gde  los puertos (RGCGPIO) Puertos base habilitación del reloj 
    //SE habilitan los puertos correspondientes a los canales del adc pg. 801 tiva ch y 1055 tiva gde para saber canales y puerto
    //                     F     E      D       C      B     A     
    SYSCTL->RCGCGPIO |= (1<<5)|(1<<4)|(1<<3)|(0<<2)|(0<<1)|(1<<0); //Port A -> UART, Port F -> leds, Port E y D para canales 
    
    //Pag 663 (GPIODIR) Habilta los pines como I/O un cero para entrada y un uno para salida.
    //Pag 801 tiva ch y 1055 tiva gde para pines correspondientes a canales
    GPIOE_AHB->DIR = (0<<1) | (0<<0) | (0<<5); //PE1 PE0 y PE5
    
    //(GPIOAFSEL) pag.672 Indicar que esos pines trabajan con función alternativa, por eso se pone 1
    GPIOE_AHB->AFSEL = (1<<1) | (1<<0) | (1<<5); //PE1 PE0 y PE5
    
    //(GPIODEN) pag.683 desabilita el modo digital de los pines porque son analogicos
    GPIOE_AHB->DEN = (0<<1) | (0<<0) | (0<<5); //PE1 PE0 y PE5
    
    //Pag 688 GPIOPCTL registro combinado con el GPIOAFSEL 
    // Se indica la función alternativa de los pines colocando el valor indicado en la tabla pag 1351 tiva ch y 1808 tiva gde
    GPIOE_AHB->PCTL = GPIOE_AHB->PCTL & (0xFF0FFF00); //Poner 0 en los bits de los pines 0, 1, 5
    
    //(GPIOAMSEL) pag.687 habilitar analogico los pines de los canales
    GPIOE_AHB->AMSEL = (1<<1) | (1<<0) | (1<<5); //PE1 PE0 y PE5
    
    //Pag 891 tiva ch y 1159 tiva gde El registro (ADCPC) establece la velocidad de conversión por segundo
    ADC0->PC = (0<<3)|(1<<2)|(1<<1)|(1<<0);//1Mms  SE pone 7 en binario porque trabaja con la max. velocidad que es 1 millon 
    
    
    //Pag 841 Este registro (ADCSSPRI) configura la prioridad de los secuenciadores 
    ADC0->SSPRI = 0x2103; //prioridad 0 (mayor) -> sec 1,  1 -> sec.2, 2-> sec. 3, 3 (menor) -> sec. 0
//Secuenciadores     3210

    //Pag 821 (ADCACTSS) Este registro controla la activación de los secuenciadores
    ADC0->ACTSS  =   (0<<3) | (0<<2) | (0<<1) | (0<<0);
    
    //Este registro (ADCEMUX) selecciona el evento que activa la conversión (trigger) (Si es por procesador o por otro) ***
    //Pag. 834 tiva ch, 1092 tiva gde para saber que valor poner para escoger el modo de activación del ADC
    ADC0->EMUX  = (0x0000); // 0x0 = Por procesador. 
   
    //Este registro (ADCSSMUX2) define las entradas analógicas con el canal y secuenciador seleccionado, Se establece que canal estará en cada mux por lo tanto en cada secuenciador y en cada modulo
    //Pag. 867 tiva ch y 1129 tiva gde, el sec. 1 y 2 pueden guardar 4 canales, el sec. 3 solo puede guardar 1 y el sec. 0 puede guardar 8 canales 
    ADC0->SSMUX1 = 0x0357; // Los canales 3,5, 7 se definen para el mux 1 del sec. 1 en el modulo 0 

    //pag 868 tiva ch, 1130 tiva gde Este registro (ADCSSCTL2), configura el bit de control de muestreo y la interrupción
    //    Sec. 1        mux 0            mux 1             mux 2      son donde se establecen los canales en la configuración del SSMUX1 -> linea 71, se ocupan 3 mux porque se colocan 3 canales en secuenciador 1 
    ADC0->SSCTL1 = (1<<2) | (1<<1)| (1<<6) | (1<<5) | (1<<10) | (1<<9); // Para establecer configuración de muestro y finalizar muestro acorde a la pag. 868
    //    Sec. 2        mux 0            mux 1       se pcupan 2 mux porque se colocan 2 canales en el sec. 2
  
    // Pag 825 Enable ADC Interrupt - Interrumpe la conversión del secuenciador a usar 
    ADC0->IM |= (1<<1); /* Unmask ADC0 sequence 2 interrupt*/  // Al sec. 1  se le asigna un 1 para indicar que manda la señal pura al controlador de interrupciones
   

    //Pag 821 (ADCACTSS) Este registro controla la activación de los secuenciadores utilizados, se activan los sec. a usar 
    ADC0->ACTSS = (0<<3) | (0<<2) | (1<<1) | (0<<0); // se habilita el sec. 1
   
    //Cuando el ADC es configurador por procesador 
    ADC0->PSSI |= (1<<1); //se inicializa el sec. 1  cuando se configura el adc en modo de procesador  ***
}





































































