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
   printf (lcd_putc,"HH:MM");
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
   //hr = concatenateAtoi (h[0],h[1]);
   //min = concatenateAtoi (m[0],m[1]);
}

void configClock()
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
      {
         char message[]={"NUEVA HORA"};
         clean(1);
         printf(lcd_putc,"\a-CONFIG HOUR-");
         c = kbd_getc();
         if (c == '1') a=3;
         //if (c == '2') getHour(message,,);
         if (c == '3') ++a;
         
         break;
      }
      case 2:
      {
         clean(1);
         printf(lcd_putc,"\a-CONFIG DATE-");
         c = kbd_getc();
         if (c == '1') --a;
         //if (c == '2') configDate();
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

void configOnOff()
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
      {
         clean(1);
         printf(lcd_putc,"\a-LUNES-");
         c = kbd_getc();
         if (c == '1') a=8;
         //if (c == '2') configClock();
         if (c == '3') ++a;
         break;
      }
      case 2:
      {
         clean(1);
         printf(lcd_putc,"\a-MARTES-");
         c = kbd_getc();
         if (c == '1') --a;
         //if (c == '2') configOnOff();
         if (c == '3') ++a;
         break;
      }  
      case 3:
      {
         clean(1);
         printf(lcd_putc,"\a-MIERCOLES-");
         c = kbd_getc();
         if (c == '1') --a;
         //if (c == '2') configOnOff();
         if (c == '3') ++a;
         break;
      }
      case 4:
      {
         clean(1);
         printf(lcd_putc,"\a-JUEVES-");
         c = kbd_getc();
         if (c == '1') --a;
         //if (c == '2') configOnOff();
         if (c == '3') ++a;
         break;
      }
      case 5:
      {
         clean(1);
         printf(lcd_putc,"\a-VIERNES-");
         c = kbd_getc();
         if (c == '1') --a;
         //if (c == '2') configOnOff();
         if (c == '3') ++a;
         break;
      }
      case 6:
      {
         clean(1);
         printf(lcd_putc,"\a-SABADO-");
         c = kbd_getc();
         if (c == '1') --a;
         //if (c == '2') configOnOff();
         if (c == '3') ++a;
         break;
      }
      case 7:
      {
         clean(1);
         printf(lcd_putc,"\a-DOMINGO-");
         c = kbd_getc();
         if (c == '1') --a;
         //if (c == '2') configOnOff();
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
}

void menu()
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
         if (c == '2') configOnOff();
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

