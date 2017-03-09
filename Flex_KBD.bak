/////////////////////////////////////////////////////////////////////////// 
////                             Flex_KBD.C                            //// 
////                  Generic keypad scan driver                       //// 
////                                                                   //// 
////  kbd_init()   Must be called before any other function.           //// 
////                                                                   //// 
////  c = kbd_getc(c)  Will return a key value if pressed or /0 if not //// 
////                   This function should be called frequently so as //// 
////                   not to miss a key press.                        //// 
////                                                                   //// 
/////////////////////////////////////////////////////////////////////////// 



//Keypad connection:  

#define col0 PIN_D4 
#define col1 PIN_D5 
#define col2 PIN_D6 
#define row0 PIN_D0 
#define row1 PIN_D1 
#define row2 PIN_D2 
#define row3 PIN_D3 

// Keypad layout: 
char const KEYS[4][3] = {{'1','2','3'}, 
                         {'4','5','6'}, 
                         {'7','8','9'}, 
                         {'*','0','#'}}; 

#define KBD_DEBOUNCE_FACTOR 33    // Set this number to apx n/333 where 
                                  // n is the number of times you expect 
                                  // to call kbd_getc each second 



void kbd_init() { 
} 


short int ALL_ROWS (void) 
{ 
   if (input (row0) & input (row1) & input (row2) & input (row3)) 
      return (0); 
   else 
      return (1); 
} 



char kbd_getc( ) { 
   static byte kbd_call_count; 
   static short int kbd_down; 
   static char last_key; 
   static byte col; 

   byte kchar; 
   byte row; 

   kchar='\0'; 
   if(++kbd_call_count>KBD_DEBOUNCE_FACTOR) { 
       switch (col) { 
         case 0   : output_low(col0); 
               output_high(col1); 
               output_high(col2); 
                    break; 
         case 1   : output_high(col0); 
               output_low(col1); 
               output_high(col2); 
                    break; 
         case 2   : output_high(col0); 
               output_high(col1); 
               output_low(col2); 
                    break; 
       } 

       if(kbd_down) { 
         if(!ALL_ROWS()) { 
           kbd_down=false; 
           kchar=last_key; 
           last_key='\0'; 
         } 
       } else { 
          if(ALL_ROWS()) { 
             if(!input (row0)) 
               row=0; 
             else if(!input (row1)) 
               row=1; 
             else if(!input (row2)) 
               row=2; 
             else if(!input (row3)) 
               row=3; 
             last_key =KEYS[row][col]; 
             kbd_down = true; 
          } else { 
             ++col; 
             if(col==3) 
               col=0; 
          } 
       } 
      kbd_call_count=0; 
   } 
  return(kchar); 
}
