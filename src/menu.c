typedef struct
{
   BYTE hour,min;
}Hour;

typedef struct
{
   Hour on;
   Hour off;
}Day;

typedef struct
{
   Day monday, tuesday, wednesday;
   Day thursday, friday, saturday, sunday;
}Week;

void clean(int a)
{
   if(a == 1 || a ==2)
   {
      lcd_gotoxy(1,1);
      printf(lcd_putc,"                "); 
   }
   if(a ==2)
   {
      lcd_gotoxy(1,2);
      printf(lcd_putc,"                ");
   }
}

void eepromLoad(BYTE addr,Week* schedule)
{
   BYTE *ptr = (BYTE*) schedule;
   BYTE i;
   for (i = 0; i < sizeof(schedule); i++)
      write_eeprom (addr++, *(ptr++));
}

void dataLoad (Byte addr,Week* schedule)
{
   BYTE *ptr = (BYTE*) schedule;
   BYTE i;
   for (i = 0; i < sizeof(schedule); i++)
      *(ptr++) = read_eeprom(addr++);
}


int concatenateAtoi(char& a, char& b)
{
   int aI, bI, r, pow=10;
   aI = a-'0';
   bI = b-'0';
   while(bI >= pow)
      pow *= 10;
   r = aI*pow+bI;
   return (r);
}

void showHour(BYTE hr, BYTE min, BYTE sec)
{
   printf(lcd_putc, "%02d:%02d:%02d",hr,min,sec);
}

void showDate (BYTE day, BYTE month, BYTE year, BYTE dow)
{
   switch (dow)
   {
      case 1:
         printf(lcd_putc, "%02d/%02d/%02d DOM",day,month,year);
         break;
      case 2:
         printf(lcd_putc, "%02d/%02d/%02d LUN",day,month,year);
         break;
      case 3:
         printf(lcd_putc, "%02d/%02d/%02d MAR",day,month,year);
         break;
      case 4:
         printf(lcd_putc, "%02d/%02d/%02d MIE",day,month,year);
         break;
      case 5:
         printf(lcd_putc, "%02d/%02d/%02d JUE",day,month,year);
         break;
      case 6:
         printf(lcd_putc, "%02d/%02d/%02d VIE",day,month,year);
         break;
      case 7:
         printf(lcd_putc, "%02d/%02d/%02d SAB",day,month,year);
         break;
   }
}

void getHour(char message[],BYTE& hr, BYTE& min)
{
   char h[2];
   char m[2]; 
   char con = '\0';
   clean(2);
   printf (lcd_putc,"\a%s",message);
   lcd_gotoxy (5,2);
   if(hr==0 && min == 0)printf (lcd_putc,"HH:MM");
   else printf (lcd_putc,"%02d:%02d",hr,min);
   do
   {
      con = kbd_getc();
      ((con >= '0') && (con <= '2'))? (h[0]=con) :(con='\0'); 
   }while(con == '\0');
   lcd_gotoxy (5,2);
   printf (lcd_putc,"%cH:MM",h[0]);
   do
   {
      con = kbd_getc();
      if(h[0]=='0'||h[0]=='1') ( (con >= '0') && (con <= '9') )?(h[1]=con):(con='\0');
      if(h[0]=='2') ( (con >= '0') && (con <= '4') )?(h[1]=con):(con='\0'); 
   }while(con == '\0');
   lcd_gotoxy (5,2);
   printf (lcd_putc,"%c%c:MM",h[0],h[1]);
   do
   {
      con = kbd_getc();
      ((con >= '0') && (con <= '5'))? (m[0]=con) :(con='\0'); 
   }while(con == '\0');
   lcd_gotoxy (5,2);
   printf (lcd_putc,"%c%c:%cM",h[0],h[1],m[0]);
   do
   {
      con = kbd_getc();
      ((con >= '0') && (con <= '5'))? (m[1]=con) :(con='\0'); 
   }while(con == '\0');
   lcd_gotoxy (5,2);
   printf (lcd_putc,"%c%c:%c%c",h[0],h[1],m[0],m[1]);
   delay_ms(500);
   hr = concatenateAtoi (h[0],h[1]);
   min = concatenateAtoi (m[0],m[1]);
}

void getDate(char message[],BYTE& day, BYTE& month, BYTE& year, BYTE& dow)
{
   char d[2];
   
   char con = '\0';
   clean(2);
   printf (lcd_putc,"\a%s",message);
   lcd_gotoxy (3,2);
   printf (lcd_putc,"DD/MM/YY D");
   
   do
   {
      con = kbd_getc();
      ((con >= '0') && (con <= '3'))? (d[0]=con) :(con='\0'); 
   }while(con == '\0');
   lcd_gotoxy (3,2);
   printf (lcd_putc,"%cD/MM/YY D",d[0]);
   
   do
   {
      con = kbd_getc();
      if(d[0] == '0')( (con >= '1') && (con <= '9') )?(d[1]=con):(con='\0');
      if(d[0]>'0' && d[0]<='2') ( (con >= '0') && (con <= '9') )?(d[1]=con):(con='\0');
      if(d[0]=='3') ( (con == '0') || (con == '1') )?(d[1]=con):(con='\0'); 
   }while(con == '\0');
   lcd_gotoxy (3,2);
   printf (lcd_putc,"%c%c/MM/YY D",d[0],d[1]);
   day = concatenateAtoi(d[0],d[1]);
   
   do
   {
      con = kbd_getc();
      ((con == '0') || (con == '1'))? (d[0]=con) :(con='\0'); 
   }while(con == '\0');
   lcd_gotoxy (3,2);
   printf (lcd_putc,"%02d/%cM/YY D",day,d[0]);
   
   do
   {
      con = kbd_getc();
      if(d[0]=='0') ( (con >= '1') && (con <= '9') )?(d[1]=con):(con='\0');
      if(d[0]=='1') ( (con >= '0') && (con <= '2') )?(d[1]=con):(con='\0');
   }while(con == '\0');
   lcd_gotoxy (3,2);
   month = concatenateAtoi(d[0],d[1]);
   switch(month)
   {
   case 2:{if(day > 28)day=28; break;}
   case 4:{if(day > 30)day=30; break;}
   case 6:{if(day > 28)day=28; break;}
   case 9:{if(day > 28)day=28; break;}
   case 12:{if(day > 28)day=28; break;}
   }
   printf (lcd_putc,"%02d/%02d/YY D",day,month);
   
   do
   {
      con = kbd_getc();
      ((con >= '0') && (con <= '9'))? (d[0]=con) :(con='\0'); 
   }while(con == '\0');
   lcd_gotoxy (3,2);
   printf (lcd_putc,"%02d/%02d/%cY D",day,month,d[0]);
   
   do
   {
      con = kbd_getc();
      ((con >= '0') && (con <= '9'))? (d[1]=con) :(con='\0'); 
   }while(con == '\0');
   lcd_gotoxy (3,2);
   year=concatenateAtoi(d[0],d[1]);
   printf (lcd_putc,"%02d/%02d/%02d D",day,month,year);
   
   do
   {
      con = kbd_getc();
      ((con >= '1') && (con <= '9'))? (d[0]=con) :(con='\0'); 
   }while(con == '\0');
   lcd_gotoxy (3,2);
   dow =(int)(d[0]-'0');
   printf (lcd_putc,"%02d/%02d/%02d %02d",day,month,year,dow);
   delay_ms(1000);
}

void configClock()
{
   BYTE hour,min,day,month,year,dow;
   clean(2);
   int a = 1;
   lcd_gotoxy (2,2); 
   printf(lcd_putc "<   enter   >");
   while (a!=0)
   {
      char c;
      switch (a)
      {
      case 1:
      {
         char message[]={"-NUEVA HORA-"};
         clean(1);
         printf(lcd_putc,"\a-CONFIG HOUR-");
         c = kbd_getc();
         if (c == '1') a=3;
         if (c == '2') {getHour(message,hour,min); rtc_set_time(hour,min);}
         if (c == '3') ++a;
         
         break;
      }
      case 2:
      {
         char message[]={"-NUEVA FECHA-"};
         clean(1);
         printf(lcd_putc,"\a-CONFIG DATE-");
         c = kbd_getc();
         if (c == '1') --a;
         if (c == '2') {getDate(message,day,month,year,dow); rtc_set_date(day,month,year,dow);}
         if (c == '3') ++a;
         break;
      }
      case 3:
      {
         clean(1);
         printf(lcd_putc,"\a-EXIT-");
         c = kbd_getc();
         if (c == '1') --a;
         if (c == '2') a = 0;
         if (c == '3') a = 1;
         break;
      }
      }
   }  
}

void configOnOff(Week& schedule)
{
   char message1[]={"-HORA ON-"};
   char message2[]={"-HORA OFF-"};
   clean(2);
   int a = 1;
   lcd_gotoxy (2,2); 
   printf(lcd_putc "<   enter   >");
   while (a!=0)
   {
      char c;
      switch (a)
      {
      case 1:
      {
         clean(1);
         printf(lcd_putc,"\a-LUNES-");
         c = kbd_getc();
         if (c == '1') a=8;
         if (c == '2') 
         {
            getHour(message1, schedule.monday.on.hour, schedule.monday.on.min);
            getHour(message2, schedule.monday.off.hour, schedule.monday.off.min);
         }
         if (c == '3') ++a;
         break;
      }
      case 2:
      {
         clean(1);
         printf(lcd_putc,"\a-MARTES-");
         c = kbd_getc();
         if (c == '1') --a;
         if (c == '2')
         {
            getHour(message1, schedule.tuesday.on.hour, schedule.tuesday.on.min);
            getHour(message2, schedule.tuesday.off.hour, schedule.tuesday.off.min);
         }
         if (c == '3') ++a;
         break;
      }  
      case 3:
      {
         clean(1);
         printf(lcd_putc,"\a-MIERCOLES-");
         c = kbd_getc();
         if (c == '1') --a;
         if (c == '2')
         {
            getHour(message1, schedule.wednesday.on.hour, schedule.wednesday.on.min);
            getHour(message2, schedule.wednesday.off.hour, schedule.wednesday.off.min);
         }
         if (c == '3') ++a;
         break;
      }
      case 4:
      {
         clean(1);
         printf(lcd_putc,"\a-JUEVES-");
         c = kbd_getc();
         if (c == '1') --a;
         if (c == '2')
         {
            getHour(message1, schedule.thursday.on.hour, schedule.thursday.on.min);
            getHour(message2, schedule.thursday.off.hour, schedule.thursday.off.min);
         }
         if (c == '3') ++a;
         break;
      }
      case 5:
      {
         clean(1);
         printf(lcd_putc,"\a-VIERNES-");
         c = kbd_getc();
         if (c == '1') --a;
         if (c == '2')
         {
            getHour(message1, schedule.friday.on.hour, schedule.friday.on.min);
            getHour(message2, schedule.friday.off.hour, schedule.friday.off.min);
         }
         if (c == '3') ++a;
         break;
      }
      case 6:
      {
         clean(1);
         printf(lcd_putc,"\a-SABADO-");
         c = kbd_getc();
         if (c == '1') --a;
         if (c == '2')
         {
            getHour(message1, schedule.saturday.on.hour, schedule.saturday.on.min);
            getHour(message2, schedule.saturday.off.hour, schedule.saturday.off.min);
         }
         if (c == '3') ++a;
         break;
      }
      case 7:
      {
         clean(1);
         printf(lcd_putc,"\a-DOMINGO-");
         c = kbd_getc();
         if (c == '1') --a;
         if (c == '2')
         {
            getHour(message1, schedule.sunday.on.hour, schedule.sunday.on.min);
            getHour(message2, schedule.sunday.off.hour, schedule.sunday.off.min);
         }
         if (c == '3') ++a;
         break;
      }
      case 8:
      {
         clean(1);
         printf(lcd_putc,"\a-EXIT CONFIG-");
         c = kbd_getc();
         if (c == '1') --a;
         if (c == '2') a = 0;
         if (c == '3') a = 1;
         break;
      }
      }
   }
   eepromLoad(1,&schedule);
}

void menu(Week& schedule)
{
   clean(2);
   int a = 1;
   lcd_gotoxy (2,2); 
   printf(lcd_putc "<   enter   >");
   while (a!=0)
   {
      char c;
      switch (a)
      {
      case 1:
         clean(1);
         printf(lcd_putc,"\a-CONFIG RELOJ-");
         c = kbd_getc();
         if (c == '1') a=3;
         if (c == '2') configClock();
         if (c == '3') ++a;
         break;
      
      case 2:
         clean(1);
         printf(lcd_putc,"\a-CONFIG ON/OFF-");
         c = kbd_getc();
         if (c == '1') --a;
         if (c == '2') configOnOff(schedule);
         if (c == '3') ++a;
         break;
         
      case 3:
         clean(1);
         printf(lcd_putc,"\a-EXIT-");
         c = kbd_getc();
         if (c == '1') --a;
         if (c == '2') a = 0;
         if (c == '3') a = 1;
         break;         
      }
   }  
}

