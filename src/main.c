#include <main.h>
#include "DS1302.C"
#include <Flex_KBD.c>

//LCD Module Connections
#define LCD_ENABLE_PIN PIN_B1
#define LCD_RS_PIN PIN_B2
#define LCD_RW_PIN PIN_B3
#define LCD_DATA4 PIN_B4
#define LCD_DATA5 PIN_B5
#define LCD_DATA6 PIN_B6
#define LCD_DATA7 PIN_B7
//End LCD Module Connections
#include <LCD.C>
#include <menu.c>
void main()
{

   setup_adc_ports(NO_ANALOGS|VSS_VDD);
   setup_adc(ADC_CLOCK_DIV_2);
   //setup_pp(PMP_DISABLED);
   setup_spi(SPI_SS_DISABLED);
   setup_wdt(WDT_OFF);
   setup_timer_0(RTCC_INTERNAL);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DISABLED,0,1);
   setup_timer_3(T3_DISABLED|T3_DIV_BY_1);
   setup_ccp1(CCP_OFF);
   setup_comparator(NC_NC_NC_NC);
   kbd_init();
   rtc_init();
   lcd_init();
   Week schedule;
   BYTE hour,min,sec;
   BYTE day,month,year,dow;
   dataLoad(1,&schedule);
    while(true)
    {
      /// Obtain time from ds1302
      rtc_get_time(hour, min, sec);  // Store time in hr, min, sec
      rtc_get_date(day,month,year,dow);
      
      /// Show time
      lcd_gotoxy(5,1);             // Change cursor position on lcd
      showHour (hour,min,sec);
      lcd_gotoxy(3,2);
      showDate (day, month, year, dow);     
      printf(lcd_putc, "\a");
      
      if (kbd_getc() !='\0') 
      {
         menu(schedule);
         clean(2);
      }
    }

}
