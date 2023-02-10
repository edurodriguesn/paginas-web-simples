#include <stdio.h>
#include <string.h>
int main()
{
  char Expressao[10]; //Variável que irá armazenar a expressão regular (Char para receber expressões alfanuméricas)
  int i; //Variável que será usada para repetições
  int ValidarExpressao=0; //Variavel que será usada para confirmar se a expressão dada é válida. 
  printf("Digite sua expressão regular: ");
  scanf("%s",Expressao); //Realiza a leitura da expressão e armazena na variavel criada
  
  return 0;
}
