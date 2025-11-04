/**
  ******************************************************************************
  * @file    stack.c
  * @author  Yildirim Madanoglu, Ramin Nekzad
  * @brief   Stack Programm
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
 
#include "stack.h"
#include "display.h"
#include "lcd.h"
 
#define STACK_SIZE 10
#define ERNO -1
#define EOK 0
 
int Stack[STACK_SIZE];
 
int count = 0;
 
/**
* @brief Methode pusht die gegebene Nummer auf den Stack
*
* @return 0, falls der Push erfolgreich war, sonst -1 für falsch
*  
*/
 
int stack_push(int val){
    if (count >= STACK_SIZE){
        printStdout("Stackoverflow");
        return ERNO;
 
    }
 
    Stack[count] = val;
    count++;
    return EOK;
}
 
/**
* @brief Methode poppt die gegebene Nummer vom Stack
*
* @return 0, falls der Pop erfolgreich war, sonst -1 für falsch
*/
 
int stack_pop(int *val){
 
    if (count <= 0){
        printStdout("Stackunderflow\n");
        return ERNO;
    }
 
    count--;
    *val = Stack[count];
    return EOK;
 
}
 
 
/**
* @brief Methode druckt den obersten Wert des Stack aus
*/
 
void p(){
    if(count > 10 || count <= 0){
        printStdout("Stack ist leer\n");
    }
    else{
        int val = Stack[count - 1];
        char number_str[16];
        int len = 0;
 
        bool negativ = false;
        if (val < 0) {
            negativ = true;
            val = -val;
        }
        if (negativ){
            printStdout("-");
        }
 
 
 
        do {
            int digit = (val % 10 + '0');
            number_str[len++] = digit;
            val /= 10;
        } while(val > 0);
        number_str[len] = '\0';
 
        int start = 0;
        int ende = len - 1;
 
        while( start < ende){
            int temp = number_str[start];
            number_str[start] = number_str[ende];
            number_str[ende] = temp;
            start++; ende--;
        }
 
        printStdout(number_str);
        printStdout("\n");
 
    }
 
}
 
/**
* @brief Methode druckt den gesamten Stack aus
*/
 
void P(){
    int temp = count;
    for (int i = 0; i < count; count--){
        p();
 
    }
    count = temp;
 
}
 
 
/**
* @brief Methode löscht alle Einträge des Stack
*/
 
void C(){
    clearStdout();
    count = 0;
}
 
/**
* @brief Methode dupliziert den obersten Wert
*/
 
void d(){
    int val = Stack[count - 1];
    stack_push(val);
}
 
 
/**
* @brief Methode vertauscht die Reihenfolge der oberen beiden Zahlen
*/
void r(){
    int wert1 = Stack[count - 1];
    int wert2 = Stack[count - 2];
 
    Stack[count - 1] = wert2;
    Stack[count - 2] = wert1;
}