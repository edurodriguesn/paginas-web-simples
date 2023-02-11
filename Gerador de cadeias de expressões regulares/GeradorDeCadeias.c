#include <stdio.h>
#include <string.h> //Para manipular strings
#include <stdio.h>  //Para utilizar a função de random
#include <time.h>   //Para resetar o valor aleatório gerado
char Expressao[10]; // Variável que irá armazenar a expressão regular (Char para receber expressões alfanuméricas)
char Cadeia[50];
char ParteDaExpressao[5];        // Se a expressão tiver entre parenteses ele irá tornar o que está dentro de parenteses como uma string unica
int i;                           // Variável que será usada para repetições
int QuantidadeGerada;            // Valor que será sorteado
int EntreParenteses = 0;         // Irá identificar se existe expressão entre parenteses, para agrupar os caracteres dentro dela como um só
int PossuiExpoente = 0;          // Para definir se repete ou não
void EscrevernaCadeia(int Vazio) // Função para ser chamada. Utiliza int vazio pois se * inclui o valor 0, se + começa a partir de 1 (sorteio de quantidade)
{
  // int Vazio=Vazio; //T
  if (PossuiExpoente == 1) // Para concatenar mais de uma vez na cadeia (Caso não possua ele vai basicamente concatenar o valor contido no indice da string)
  {
    QuantidadeGerada = rand() % 5;         // Sorteia Quantas vezes o valor será repetido
    for (i = 0; i < QuantidadeGerada; i++) // For para concatenar
    {
      strcat(Cadeia, ParteDaExpressao); // Função de concatenar
    }
    // Ta faltando o else, caso não tenha expoente, concatena uma unica vez (To com preguiça de fazer agora)
  }
}

int main()
{
  srand(time(NULL));
  printf("Digite sua expressão regular: ");
  scanf("%s", Expressao); // Realiza a leitura da expressão e armazena na variavel criada
  for (i = 1; i < 10; i++)
  {
    strcpy(ParteDaExpressao, Expressao[i]); // Se for com parenteses ParteDaExpressao,Juncao do que está entre parenteses
    switch (Expressao[i])                   // Vai analisar os casos (Se tiver parenteses, se for *, se tiver + ou ^+)
    {
    case '*':
      if (EntreParenteses == 0) // Esqueci oq eu queria fazer aqui
        break;
    default:
      printf("A"); // Só teste
      break;
    }
  }
  return 0;
}
