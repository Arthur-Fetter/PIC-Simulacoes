#include<16F877A.h>
#fuses xt, nowdt, nobrownout
#use delay(clock=4000000)
#include<lcd.h>
#use fast_io(c)
#use fast_io(d)

#define BOTAO_BT0    PIN_C0
#define LED1         PIN_D0
#define ON           0
#define OFF          1
#define PRESS        0
#define SOLTO        1
#define NAO          0
#define SIM          1
#define FILTRO       1800

//variaveis globais:
int1 executouBT0=NAO;
unsigned int16 tempoPressBT0 = 0;
signed int16 contagem = 0;

//*********************************

//prototipo das funções
void atualizaLCD();
void limites();

//*********************************

void main()
{
   set_tris_c(0b00001111);
   set_tris_d(0b00000000);
   lcd_init();
   atualizaLCD();
   
   while(1)
   {
      if(input(BOTAO_BT0) == PRESS && executouBT0 == NAO)
      {
         tempoPressBT0++;
         
         if(tempoPressBT0 == FILTRO)
         {
            contagem++;
            executouBT0=SIM;
            atualizaLCD();
         }
      }
      if(input(BOTAO_BT0) == SOLTO)
      {
         tempoPressBT0 = 0;
         executouBT0 = NAO;
      }
   }
}

//**************************************

void atualizaLCD()
{
   lcd_gotoxy(1, 1);
   lcd_putc((contagem / 10) + 48);
   lcd_putc((contagem % 10) + 48);
}

//**************************************

void limites()
{
   if(contagem < 0) contagem = 99;
   if(contagem > 99) contagem = 0;
}
