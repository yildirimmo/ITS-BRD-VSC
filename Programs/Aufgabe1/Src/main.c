/**
  ******************************************************************************
  * @file    main.c
  * @author  Franz Korf
  * @brief   Kleines Testprogramm fuer neu erstelle Fonts.
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
 
#include "display.h"
#include "scanner.h"
#include "stack.h"
#include "stm32f4xx_hal.h"
#include "init.h"
#include "LCD_GUI.h"
#include "LCD_Touch.h"
#include "lcd.h"
#include "keypad.h"
#include "fontsFLASH.h"
#include "additionalFonts.h"
#include "error.h"
#include "token.h"
 
 
 
 
 
int main(void) {
    initITSboard();    // Initialisierung des ITS Boards
    initDisplay();      // Initialisierung des Displays
    
    GUI_init(DEFAULT_BRIGHTNESS);   // Initialisierung des LCD Boards mit Touch
    TP_Init(false);                 // Initialisierung des LCD Boards mit Touch
 
 
    makeKeyPad(); //Basic Keypad wird ausgegeben
    
    /**
     * hier sollen die zurückgegebenen Tokens bzw die Tastatureingaben gelesen werden
     *
     * */
 
    int val = 0;
    int result = 0;
 
 
    while(1) {
        //ddc
        T_token token = nextToken();
 
        switch(token.tok){
            case NUMBER:
            stack_push(token.val);
                break;
 
            case PLUS:
            stack_pop(&val);
            result += val;
            stack_pop(&val);
            result += val;
            stack_push(result);
                break;
            
            case MINUS:
            stack_pop(&val);
            result = -val;
            stack_pop(&val);
            result += val;
            stack_push(result);
                break;
 
            case MULT:
            stack_pop(&val);
            result = val;
            stack_pop(&val);
            result *= val;
            stack_push(result);
                break;
            
            case DIV:
            stack_pop(&val);
            if (val == 0) {
                printStdout("Division durch 0 unzulaessig!");
                break;
            
            }
            result = val;
            stack_pop(&val);
            result = val / result;
            stack_push(result);
                break;
 
            case PRT:
            p();
                break;
 
            case PRT_ALL:
            P();
                break;
 
            case SWAP:
            r();
                break;
 
            case CLEAR:
            C();
                break;  
 
            case DOUBLE:
            d();
                break;
 
        }
 
    }
}
 
// EOF