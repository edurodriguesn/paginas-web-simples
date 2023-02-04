#include <stdio.h>
#include <string.h>
int main()
{
  char Expressao[10]; //Variável que irá armazenar a expressão regular (Char para receber expressões alfanuméricas)
  int i; //Variável que será usada para repetições
  int ValidarExpressao=0; //Variavel que será usada para confirmar se a expressão dada é válida. 
  printf("Digite sua expressão regular: ");
  scanf("%s",Expressao); //Realiza a leitura da expressão e armazena na variavel criada
  for(i=0;i<10;i++) //Repeticao feita para validar se a entrada dada pelo usuario é um expressão
  {
    char temp=Expressao[i];//Variavel criada para receber o caractere contido na posicao i da Expressao
    if(!temp)
      break;//Caso não haja mais nada contido na expressão a repetição é interrompida
    if(temp=='*'||temp=='+') //Caso haja os operadores * ou + a expressão é valida
      ValidarExpressao=1; //Caso a condição se satisfaça a variavel muda do estado 0 para 1
  }
  if(ValidarExpressao==1)//Caso a expressao seja valida o código continua
  {
    
  }
  return 0;
}
