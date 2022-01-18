#include <projj.h>
#define LCD_ENABLE_PIN PIN_B0
#define LCD_RS_PIN PIN_B1
#define LCD_RW_PIN PIN_B2
#define LCD_DATA4 PIN_B4
#define LCD_DATA5 PIN_B5
#define LCD_DATA6 PIN_B6
#define LCD_DATA7 PIN_B7
   unsigned long int bilgi;
   float sicaklik,voltaj;
#include <lcd.c>
void fan_calis( );
void main()
{
  

   setup_spi(SPI_SS_DISABLED);
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_1);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DIV_BY_16,255,1);
   setup_comparator(NC_NC_NC_NC);
   setup_vref(FALSE);
   set_tris_a(0b00000001);
   set_tris_c(0x00);
   setup_CCP1(CCP_OFF);
   setup_CCP2(CCP_OFF);
  // set_pwm1_duty(0);
   setup_adc(adc_clock_div_32);
   setup_adc_ports(AN0); 
   lcd_init();
   set_adc_channel(0);
   delay_us(20);
   printf(lcd_putc,"\fSicaklik=");

   while(TRUE)
   {
   bilgi=read_adc();
   voltaj=(0.004882812*bilgi);
   sicaklik=(voltaj*100)-0.2;
if(sicaklik<30){
   fan_calis( );
  // set_pwm1_duty(0);
   }
if(sicaklik>=30&&sicaklik<35){
   fan_calis( );
   // set_pwm1_duty(35);
   }
if(sicaklik>=35&&sicaklik<40){
   fan_calis( );
   // set_pwm1_duty(50);
   }
if(sicaklik>=40&&sicaklik<45){
   fan_calis( );
   // set_pwm1_duty(75);
   }
if(sicaklik>=45&&sicaklik<50){
   fan_calis( );
   // set_pwm1_duty(90);
   }
if(sicaklik>50){
   fan_calis( );
   // set_pwm1_duty(100);
   
   }
   lcd_gotoxy(10,1);
   printf(lcd_putc,"%5.1f'C",sicaklik);
   delay_ms(100);
   }
}
void fan_calis( ){
   output_high(pin_c3);
   output_low(pin_c1);

   }
