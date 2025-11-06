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
#include "myError.h"
#include <stdint.h>
 
#define STACK_SIZE 10


 
static int Stack[STACK_SIZE];
 

static int count = 0;
 
/**
* @brief Methode pusht die gegebene Nummer auf den Stack
* @param val Der Wert, der gepushed werden soll
* @return 0, falls der Push erfolgreich war, sonst -1 für falsch
*  
*/
 


int stack_push(int val){
    if (count >= STACK_SIZE){
        
        return OVERFLOW;
 
    }
 
    Stack[count] = val;
    count++;
    return EOK;
}
 
/**
* @brief Methode poppt die gegebene Nummer vom Stack
* @param val Die Adresse auf die wir den Wert, der gepopped wurde reinschreiben
* @return 0, falls der Pop erfolgreich war, sonst -1 für falsch
*/
 
int stack_pop(int *val){
 
    if (count <= 0){
       
        return UNDERFLOW;
    }
 
    count--;
    *val = Stack[count];
    return EOK;
 
}
 
 
/**
* @brief Methode druckt den obersten Wert des Stack aus
*/
 
int p(){
    if(count <= 0 ){
        
        return UNDERFLOW;
    }
    else if (count > 10){
        
        return OVERFLOW;
    }
    else{
        int val = Stack[count - 1]; //oberster Wert
        char number_str[16]; 
        int len = 0;
 
        if (val < 0) {
            printStdout("-");
        }
 
        // Solange den Val nehmen, modulo 10 verrechnen und mit char '0' addieren.
        /*
        Z.B.: 
        val = 1230
        digit = 1230 % 10 = 0 + '0'
        val / 10 = 123
        digit = 123 % 10 = 3 + '0'
        val / 10 = 12,3
        digit = 12 % 10 = 2 + '0' 
        val / 10 = 1,2
        digit = 1 % 10 = 1 + '0'

        number_str = '0' '3' '2' '1'
        */
        do {
            int digit = (val % 10);
            if(digit < 0) {
                digit = -digit;
            }

            number_str[len++] = digit + '0';
            val /= 10;
        } while(val != 0);

        // Signalisieren, dass hier das Ende vom String ist
        number_str[len] = '\0';
 
        int start = 0;
        int ende = len - 1;
 
        //String umdrehen
        while( start < ende){
            int temp = number_str[start];
            number_str[start] = number_str[ende];
            number_str[ende] = temp;
            start++; ende--;
        }
 
        printStdout(number_str);
        printStdout("\n");

        return EOK;
 
    }
 
}
 
/**
* @brief Methode druckt den gesamten Stack aus
* @return EOK
*/
 
int P(){
    int temp = count;
    for (int i = 0; i < count; count--){
        p();
 
    }
    count = temp;

    return EOK;
 
}
 
 
/**
* @brief Methode löscht alle Einträge des Stack
*/
 
int C(){
    clearStdout();
    count = 0;
    return EOK;
}
 
/**
* @brief Methode dupliziert den obersten Wert
*/
 
int d(){
    int val = Stack[count - 1];
    stack_push(val);
    return EOK;
}
 
 
/**
* @brief Methode vertauscht die Reihenfolge der oberen beiden Zahlen
*/
int r(){
    if (count <= 1){
       
        return UNDERFLOW;
    }


    int wert1 = Stack[count - 1];
    int wert2 = Stack[count - 2];
 
    Stack[count - 1] = wert2;
    Stack[count - 2] = wert1;
    return EOK;
}

