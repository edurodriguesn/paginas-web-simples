#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <time.h>

int cadeia_asterisco(int controle, int i, char *cadeia)
{
    int valor = cadeia[i - 1];
    int aux = i;
    int j = 0;

    switch (controle)
    {
    case 0:
        cadeia[i] = ' ';
        cadeia[i - 1] = ' ';
        return i;
        break;

    case 1:
        cadeia[i] = ' ';
        return i;
        break;

    case 2:
        cadeia[i] = valor;
        return i;
        break;

    default:
    {

        for (j = 0; j < controle - 1; j++)
        {
            cadeia[aux] = valor;
            aux++;
        }
        i += j;
        return i;
    }
    break;
    }
}

int cadeia_mais(int controle, int i, char *cadeia)
{
    int valor = cadeia[i - 1];
    int aux = i;
    int j = 0;

    switch (controle)
    {
    case 1:
        cadeia[i] = ' ';
        return i;
        break;

    case 2:
        cadeia[i] = valor;
        return i;
        break;

    default:
    {

        for (j = 0; j < controle - 1; j++)
        {
            cadeia[aux] = valor;
            aux++;
        }
        i += j;
        return i;
    }
    break;
    }
}

void print_cadeia(char exp_reg[], char *cadeia)
{
    printf("\nEXPRESSAO REGULAR: \n");
    printf(exp_reg);
    printf("\nCADEIA: \n");

    int i = 0;
    while (cadeia)
    {
        if (cadeia[i] != ' ')
        {
            printf("%c", cadeia[i]);
            i++;
        }
    }
    printf("\n");
}

void ler_exp(char exp_reg[])
{

    int tam = strlen(exp_reg);
    char cadeia[10];
    int i;
    int j;
    int qntd;
    int aux = 0;
    int valor;
    int controle = 1;

    // for (controle = 0; controle < 5; controle++)
    //{
    for (i = 0; i < tam; i++)
    {
        switch (exp_reg[i])
        {
        case '*':
            i = cadeia_asterisco(controle, i, cadeia);
            break;

        case '^':
            if (controle != 0)
            {
                cadeia_mais(controle, i, cadeia);
            }
            break;

            // case '(':
            //     /* code */
            //     break;

        default:
            cadeia[i] = exp_reg[i];
            break;
        }
    }
    print_cadeia(exp_reg, cadeia);
    //}
}

void main(void)
{
    char exp_reg[80];
    gets(exp_reg);
    ler_exp(exp_reg);
}