#include <stdio.h>
#include <stdlib.h> // atof
#include <ctype.h>  // isdigit, toupper etc.

typedef char* string;
typedef enum {FALSE, TRUE} bool;

#define MaxStackSize 100
double stk[MaxStackSize];
int stkcount;

void Push(double element) {
    if (stkcount == MaxStackSize)  {
        printf( "Stack size exceeded.\n");
        exit( EXIT_FAILURE);
    }

    stk[stkcount++] = element;
}

double Pop(void) {
    if (stkcount == 0) {
        printf( "Pop of an empty stack.\n");
        exit( EXIT_FAILURE);
    }

    return stk[--stkcount];
}

void ApplyOperator(char op);
void DisplayStack(void);
string getLine(void);


// EXEMPLO:
// Função Aritmetica: (5 + 3) * 2 / (4 - 6)
// RPN: 5 3 + 2 * 4 6 - /

// Resultado = -8


int main(void) {
    string line;
    char ch;

    printf( "----RPN Calculator Simulation----\n");
    printf("\n--VALID OPTIONS--\n");
    printf("Any Number\n");
    printf("Operators: (+, -, *, /)\n");
    printf("Q: (Quit)\n");
    printf("C: (Clear)\n");
    printf("P: (Print)\n\n");
   
    stkcount = 0;
   
    while (TRUE) {
        printf("> ");
      
        line = getLine();
        ch = toupper(line[0]);
        
        switch (ch) {
            case 'Q': {
                return 0;
            }
            case 'C': {
                stkcount = 0; break;
            }
            case 'P': {
                DisplayStack(); break;
            }
            default: {
                if (isdigit(ch)) 
                    Push(atof(line));
                else
                    ApplyOperator(ch);
                break;
            }
        }
    }
}

void ApplyOperator(char op) {
   double lhs, rhs, result;
   
   rhs = Pop(); // operando direito
   lhs = Pop(); // operando esquerdo
   
   switch (op) {
      case '+': result = lhs + rhs; break;
      case '-': result = lhs - rhs; break;
      case '*': result = lhs * rhs; break;
      case '/': result = lhs / rhs; break;
      default : printf("Illegal operator\n"); 
                exit(EXIT_FAILURE);
   }
   
   printf( "Result: %g\n", result);
   Push( result);
}

void DisplayStack(void) {
    int i;
   
    printf( "Stack: ");
   
    if (stkcount == 0) {
        printf( "empty\n");
    } else {
        for (i = 0; i < stkcount; i++) {
            if (i > 0) printf( ", ");
            printf( "%g", stk[i]);
        }
        
        printf( "\n");
    }
}

string getLine( void) {
    string line;
    int n, ch;
   
    n = 0;
    line = malloc( 100+1);
   
    if (line == NULL){
        exit( EXIT_FAILURE);
    }
   
    while ((ch = getc( stdin)) != '\n') {
        if (n >= 100) {
            free( line);
            exit( EXIT_FAILURE);
        }
        
        line[n++] = ch;
    }
   
   line[n] = '\0';
   
   return line;
}