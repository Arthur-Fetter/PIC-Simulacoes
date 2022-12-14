#include<16F877A.h>
#fuses nowdt, nobrownout, xt, noput, noprotect
#use fast_io(C)
#use delay(clock=4000000)
#include<lcd.h>

#define SOMAR     PIN_C0
#define SUBTRAIR  PIN_C1
#define AVANCAR   PIN_C2
#define REGREDIR  PIN_C3

int1 b1,b2,b3,b4;
char pos, num[8]={5,1,9,9,6,0,2,6};
char nome[4]={'C','A','S','A'};

void atualizaLCD();
void atualizaCursor();
void leMemoria();

//******************************
void main(){
   leMemoria();
   lcd_init();
   atualizaLCD();
   atualizaCursor();
   
   while(1){
      if(input(SOMAR)==0 && b1==0) {
         b1=1;
         if(pos<8){
            num[pos]++;
            if (num[pos] < 0) {
               num[pos] = 9;
            }
            else if (num[pos] > 9) {
               num[pos] = 0;
            }
            
            write_eeprom(pos, num[pos]);
         }
         else{
            nome[pos-8]++;
            if(nome[pos-8]>'Z') nome[pos-8]='A';
            write_eeprom(pos, num[pos-8]);
         }
         
         atualizaLCD();
      }
      if(input(SOMAR)==1) b1=0;
      
      if(input(AVANCAR)==0 && b3==0){
         b3=1;
         pos++;
         if(pos>11) pos=0;
         atualizaCursor();
      }
      if(input(AVANCAR)==1) b3=0;
      
      if(input(REGREDIR)==0 && b4==0){
         b4=1;
         pos--;
         if(pos<0) pos=11;
         atualizaCursor();
      }
      if(input(REGREDIR)==1) b4=0;
   }
}

//******************************
void atualizaLCD(){
   char i;
   lcd_cursor(0);
   lcd_gotoxy(1,1);
   for(i=0;i<8;i++) lcd_putc(num[i]+48);
   lcd_gotoxy(2,1);
   for(i=0;i<4;i++) lcd_putc(nome[i]);
   atualizaCursor();
}

//******************************
void atualizaCursor(){
   if(pos<8)lcd_gotoxy(1,pos+1);
   else lcd_gotoxy(2,pos-7);
   lcd_cursor(1);
}

//******************************
void leMemoria(){
 //comandos para ler os dados da EEPROM nos
 //endereços 0 a 11
 num[0]=read_eeprom(0);
 num[1]=read_eeprom(1);
 num[2]=read_eeprom(2);
 num[3]=read_eeprom(3);
 num[4]=read_eeprom(4);
 num[5]=read_eeprom(5);
 num[6]=read_eeprom(6);
 num[7]=read_eeprom(7);
 nome[0]=read_eeprom(8);
 nome[1]=read_eeprom(9);
 nome[3]=read_eeprom(10);
}
