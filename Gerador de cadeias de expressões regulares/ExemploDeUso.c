#include <stdio.h>
#include <string.h>
#include <stdlib.h>
char CPF[14];
char *Alfabeto[]={'0','1','2','3','4','5','6','7','8','9','.','-'};
char StatusPadraoCPF[16];
char StatusValidadeCPF[8];
void VerificaPadrao(char CPF[14])
{
    int Pertencente; //Se o caractere lido está incluso no alfabeto
    for(int IndiceCPF=0;IndiceCPF<14;IndiceCPF++)//Percorre todos os caracteres da String CPF
    {
        Pertencente=0; //Enquanto não for verificado se a string pertence ao alfabeto, a variável Pertencente é falsa
        if(IndiceCPF!=3&&IndiceCPF!=7&&IndiceCPF!=11) //Verifica caso o indicie não seja os destinados a '.' e '-'
        {
            for(int IndiceAlfabeto=0;IndiceAlfabeto<10;IndiceAlfabeto++)//Percorre somente os números do alfabeto
                if(CPF[IndiceCPF]==Alfabeto[IndiceAlfabeto])//Compara se o caractere analisado é reconhecido no alfabeto
                {
                    Pertencente=1; //Caso seja reconhecido no alfabeto, a variavel pertencente se torna verdadeira
                    break;//Encerra a verificação, pois já foi validado
                }
        }
        else if(IndiceCPF==3||IndiceCPF==7) //Verifica caso o indice esperado seja '.'
        {
            if(CPF[IndiceCPF]==Alfabeto[10])
            {
                Pertencente=1;
                break;
            }
        }
        else
            if(CPF[IndiceCPF]==Alfabeto[11]) //Verifica caso o indice esperado seja '-'
            {
                Pertencente=1;
                break;
            }
        //Após verificar o caractere, será analisada a variável 'Pertencente'
        if(Pertencente==0||strlen(CPF)!=14)//Se o caractere não pertence ao alfabeto ou se o tamanho da string CPF não é 14
        {
            strcpy(StatusPadraoCPF,"Fora do padrao");//Se a varivel 'Pertencente' for 0, o CPF possui um caractere invalido
            break;//Se um caractere for invalido, todo o CPF é invalido, logo, a repetição é encerrada de maneira forçada
        }
        else
            strcpy(StatusPadraoCPF,"Dentro do padrao"); //Se a variavel 'Pertencente' for 1, o CPF está dentro no padrão
        //Se em nenhum momento houver um caractere inválido, o status do padrão do CPF será retornado para a função principal como 'dentro do padrão', pois não será alterado
    }
}
void ValidaCPF(char CPF[14])
{
    int Multiplicador=10,Somatorio=0;//Variaveis utilizadas para a operação de validação do CPF
    int CPFValido;
    char CaractereCPF[1];//Essa string receberá o caractere do indice do CPF para ser transformada em int
    for(int IndiceCPF=0;IndiceCPF<11;IndiceCPF++)//Percorre os 10 primeiros digitos do CPF
    {
        if(IndiceCPF!=3&&IndiceCPF!=7)//Realiza a operação nos casos em que o caractere for um numero
        {
            CaractereCPF[0]=CPF[IndiceCPF];
            Somatorio+=atoi(CaractereCPF)*Multiplicador;//O somatorio soma todas as multiplicações. A função atoi converte o caractere do CPF em inteiro e multiplica pelo multiplicador
            Multiplicador--;//A cada multipliação o multiplicador diminui em 1
        }
    }
    CaractereCPF[0]=CPF[12];//A string recebe o primeiro digito verificador
    if((Somatorio*10)%11==atoi(CaractereCPF))//Verifica se ao multiplicar o somatorio por 10, e dividir por 11, sobra um valor igual ao primeiro digito verificador
        CPFValido=1; //Caso seja verdadeiro, a variavel CPFValido é dada como true
        else
            CPFValido=0; //Caso não seja igual, então retorna falso, logo o CPF não é válido
    //Foi realizada a validação do primeiro digito verificador (000.000.000-X0)
    Multiplicador=11; //Agora começa multiplicando a partir do 11
    Somatorio=0;//Zera o valor da soma de todos as multiplicações
    for(int IndiceCPF=0;IndiceCPF<13;IndiceCPF++)//Percorre os 11 primeiros digitos do CPF
    {
        if(IndiceCPF!=3&&IndiceCPF!=7&&IndiceCPF!=11)//Realiza a operação se o caractere for um numero
        {
            CaractereCPF[0]=CPF[IndiceCPF];
            Somatorio+=atoi(CaractereCPF)*Multiplicador;
            Multiplicador--;//A cada multipliação o multiplicador diminui em 1
        }
    }
    CaractereCPF[0]=CPF[13];//A string recebe o segundo digito verificador
    if((Somatorio*10)%11!=atoi(CaractereCPF))//Faz a operação comparando a sobra com o segundo digito verificador
        CPFValido=0;//Verifica apenas se é diferente do segundo digito, pois caso seja igual,o status da validação não muda, continua verdadeiro
    //Foi realizada a validação do segundo digito verificador (000.000.000-0X)
    if(CPFValido==1)
        strcpy(StatusValidadeCPF,"Valido");//Se a variável for 1, retorna o status de válido na string
        else
            strcpy(StatusValidadeCPF,"Invalido");//Se for 0, retorna o status de inválido
}
int main()
{
    printf("Informe seu CPF: ");
    scanf("%s",CPF);
    VerificaPadrao(CPF); //Chama a função que irá verificar se o CPF está no padrão correto, utilizando a string CPF como parametro
    printf("Status do do padrão do CPF: %s\n",StatusPadraoCPF); //Retorna com a mensagem informando o status do padrão do CPF
    if(strcmp(StatusPadraoCPF,"Dentro do padrao")==0)//Verifica se o CPF está dentro do padrão
    {
        ValidaCPF(CPF);//Se tiver, chama a função que verifica se o CPF é válido
        printf("Status de Validade do CPF: %s\n",StatusValidadeCPF);//Exibe o status da validade
    }
    return 0;
}