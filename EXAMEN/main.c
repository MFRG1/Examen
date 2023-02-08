#include "lib/include.h"
int bandera=0;

extern void IntGPIOA(void)
{
  bandera = 1;

}

int main(void)
{
    uint16_t valor = 0;
    char c='5';
    //char b='a';
    //int tamstring=100;
    //char PAL[tamstring]; 



    Configurar_PLL(_50MHZ);  //Confiuracion de velocidad de reloj ----SE CAMBIO A 50MHz
    Configurar_UART7();

    Configurar_GPIO();
   // Homogeneidad();
    //printString("Holis Bolis");
    printChar(c);
    //printChar(b);
    printString("\n");
   // char *arr = readString(',');
   // printString(&arr[0]);
    while(1)
    {
         c = readChar();
         switch(c)
         {
             case 'r':
                 //GPIODATA port F 662
                 printChar('a');
                 GPIOF->DATA = (1<<1);
                 break;
             case 'b':
                 //GPIODATA port F 662
                 printChar('b');
                 GPIOF->DATA = (1<<2);
                 break;
             case 'g':
                 //GPIODATA port F 662
                 printChar('c');
                 GPIOF->DATA = (1<<3);
                 break;
             case 'y':
                 //GPIODATA port F 662
                 printChar('d');
                 GPIOF->DATA = (1<<3) | (1<<2);
                 break;
             default:
                 printChar((char)valor);
                 GPIOF->DATA = (0<<1) | (0<<2) | (0<<3);
                 break;
         }
    }
}
