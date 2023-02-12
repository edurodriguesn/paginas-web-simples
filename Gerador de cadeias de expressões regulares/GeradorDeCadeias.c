#include <stdio.h>
#include <string.h> //Para manipular strings
#include <stdlib.h> //Para utilizar a função de random
#include <time.h> //Para resetar o valor aleatório gerado
char Expressao[50]; //Variável que irá armazenar a expressão regular (Char para receber expressões alfanuméricas)
char Cadeia[50];
char ParteDaExpressao[10]; //Se a expressão tiver entre parenteses ele irá tornar o que está dentro de parenteses como uma string unica
int i,j,k,l,IndiceDaCadeia; //Variável que será usada para repetições
int QntGerada; //Valor que será sorteado
int EntreParenteses; //Irá identificar se existe expressão entre parenteses, para agrupar os caracteres dentro dela como um só
int PossuiExpoente=0; //Para definir se repete ou não
void EscrevernaCadeia(int Vazio) //Função para ser chamada. Utiliza int vazio pois se * inclui o valor 0, se + começa a partir de 1 (sorteio de quantidade)
{
  //printf("%s| %d Exp| %d Par| %d inc\n",ParteDaExpressao,PossuiExpoente,EntreParenteses,IndiceDaCadeia);
  if(PossuiExpoente==0)
    QntGerada=1; //Se nao houver expoente ira gerar apenas uma vez o valor na cadeia
    else
      QntGerada=(rand()%5)+Vazio; //Se houver expoente sorteia quantas vezes o valor será repetido, +vazio para somar com 0(caso seja *) ou com 1(caso seja +) 
  //printf("%d| ",QntGerada);
  for(l=0;l<QntGerada;l++) //For para concatenar
  {
    if(EntreParenteses==0)
    {
    //  printf("%d-",l);
      Cadeia[IndiceDaCadeia]=ParteDaExpressao[0];//Se for para concatenar apenas um caractere, ira utilizar os indices onde o caractere esta
      //printf("(%s) | %c %d > {%d}",Cadeia,ParteDaExpressao[0],IndiceDaCadeia,i);
      IndiceDaCadeia++;//Avança para a proxima posicao da strin para nao sobreescrever
    }
    else
    {
      strncat(Cadeia,ParteDaExpressao,strlen(ParteDaExpressao)); //Se for uma string com mais de um caractere(entre parenteses), irá usar a função strcat para juntar strings inteira na cadeia
      IndiceDaCadeia+=strlen(ParteDaExpressao); //Ira avançar para a posição que corresponde ao tamanho da string entre parenteses
    }      
  }
  //printf("\n");
  strcpy(ParteDaExpressao," ");
}
void Parenteses() //Função que junta os caracteres dentro da perenteses em uma unica string separada
{
  k=0;//Variável que será usada como índice da outra string
  EntreParenteses=1; //Torna verdadeira a existencia de parenteses
  j++;//Passa para o próximo caractere depois de (
  while(Expressao[j]!=')') //Realiza a operação enquanto o caractere em questão não for o fecha parenteses
  {
    ParteDaExpressao[k]=Expressao[j]; //Recebe parte da expressao que está entre parenteses
    k++;//Avança no índice da string ParteDaExpressao, para ir concatenando
    j++;//Continuando avançando para o próximo caractere da expressao
  }
  j++;//Avança para o próximo caractere depois do )
}
int main()
{
  srand(time(NULL));
  printf("Digite sua expressão regular: ");
  scanf("%s",Expressao); //Realiza a leitura da expressão e armazena na variavel criada
  int QntDeCadeias=(rand()%3)+3;//Variável que define aleatoriamente quantas cadeias o programa irá mostrar, começando com no minimo 3
  for(i=0;i<QntDeCadeias;i++)
  {
    strcpy(Cadeia,"");
    IndiceDaCadeia=0;
    for(j=0;j<10;j++) //Repetição para analisar os 10 caracteres da expressão regular
    {
      if(Expressao[j]=='(') //Irá identificar se existe expressao entre parenteses para juntar tudo em uma unica string
        Parenteses();//Chama a função que realiza a junção dos caracteres em uma string
      switch(Expressao[j]) //Vai analisar os casos (Se tiver parenteses, se for *, se tiver + ou ^+)
      {
        case '*':
          PossuiExpoente=1;
          EscrevernaCadeia(0);
          break;
        case '^':
          PossuiExpoente=1;
          if(Expressao[j+1]=='+')
          {
            EscrevernaCadeia(1);    
          }
          else if(Expressao[j+1]=='*')
          {
            EscrevernaCadeia(0);
          }
          else
          {
            j=QntDeCadeias;
            printf("Expressao invalida");
          }
          j++;//Avança mais uma posição pois a proxima ja é deduzida como + ou *
          break;  
        default:
          ParteDaExpressao[0]=Expressao[j];//Recebe o caractere que está no indicie j da expressão
          EntreParenteses=0;
          if(Expressao[j+1]!='*'&&Expressao[j+1]!='+'&&Expressao[j+1]!='^')
          {
            PossuiExpoente=0;
            EscrevernaCadeia(2);
          }
          break;
      }
      if(!Expressao[j+1])
        break;
    }
    printf("%s\n",Cadeia);
  }
  return 0;
}
