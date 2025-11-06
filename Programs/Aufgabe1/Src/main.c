/**
  ******************************************************************************
  * @file    main.c
  * @author  Franz Korf
  * @brief   Kleines Testprogramm fuer neu erstelle Fonts.
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
 
#include "display.h"
#include "myError.h"
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
#include "myError.h"
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
    int erk1;
    int erk2;
 
 
    while(1) {
        //ddc
        T_token token = nextToken();
 
        switch(token.tok){
            //-----------------------------------
            case NUMBER:
            erk2 = stack_push(token.val);
            if (erk2 != EOK) {
                printStdout("Stackoverflow\n");
                break;
            }
                break;
                
            //-----------------------------------
            case PLUS:
            result = 0;
            erk1 = stack_pop(&val);
            if (erk1 == UNDERFLOW){
                printStdout("Stackunderflow\n");
                break;
            }           
            result += val;

            erk1 = stack_pop(&val);
            if (erk1 == UNDERFLOW){
                printStdout("Stackunderflow\n");
                break;
            }
            result += val;

            erk2 = stack_push(result);
            if (erk2 != EOK) {
                printStdout("Stackoverflow\n");
                break;
            }
                break;
            
            //-----------------------------------
            case MINUS:
            result = 0;
            
            erk1 = stack_pop(&val);
            if (erk1 == UNDERFLOW){
                printStdout("Stackunderflow\n");
                break;
            }
            result = -val;

            erk1 = stack_pop(&val);
            if (erk1 == UNDERFLOW){
                printStdout("Stackunderflow\n");
                break;
            }
            result += val;

            erk2 = stack_push(result);
            if (erk2 != EOK) {
                printStdout("Stackoverflow\n");
                break;
            }

                break;
 

            //-----------------------------------
            case MULT:
            result = 0;

            erk1 = stack_pop(&val);
            if (erk1 == UNDERFLOW){
                printStdout("Stackunderflow\n");
                break;
            }
            result = val;

            erk1 = stack_pop(&val);
            if (erk1 == UNDERFLOW){
                printStdout("Stackunderflow\n");
                break;
            }
            result *= val;

            erk2 = stack_push(result);
            if (erk2 != EOK) {
                printStdout("Stackoverflow\n");
                break;
            }
                break;
            
            //-----------------------------------
            case DIV:
            result = 0;
            erk1 = stack_pop(&val);
            if (erk1 == UNDERFLOW){
                printStdout("Stackunderflow\n");
                break;
            }

            if (val == 0) {
                printStdout("Division durch 0 unzulaessig!");
                break;
            
            }
            result = val;

            erk1 = stack_pop(&val);
            if (erk1 == UNDERFLOW){
                printStdout("Stackunderflow\n");
                break;
            }

            result = val / result;

            erk2 = stack_push(result);
            if (erk2 != EOK) {
                printStdout("Stackoverflow\n");
                break;
            }
                break;
 
            //-----------------------------------
            case PRT:
            p();
            /*if (erk1 == UNDERFLOW){
                printStdout("Stackunderflow\n");
                break;
            }
            if (erk2 == OVERFLOW) {
                printStdout("Stackoverflow");
            }
                */
            
                break;
 
            //-----------------------------------
            case PRT_ALL:
            P();
            /*
            if (erk1 == UNDERFLOW){
                printStdout("Stackunderflow\n");
                break;
            }

            if (erk2 == OVERFLOW) {
                printStdout("Stackoverflow");
                break;
            }
                */
                break;
 
            //-----------------------------------
            case SWAP:
            r();
            /* if (erk1 == UNDERFLOW){
                printStdout("Stackunderflow\n");
                break;
            }
                */
                break;
 
            //-----------------------------------
            case CLEAR:
            C();
                break;  
 
            //-----------------------------------
            case DOUBLE:
            d();
                break;
 
        }
 
    }
}
 
// EOF