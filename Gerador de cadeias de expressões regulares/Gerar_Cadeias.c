#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <time.h>

int exc_simbolo(int i, char *c)
{
    int valor = c[i - 1]; // Guarda o valor antes do simbolo
    int j = i - 1;        // Posição antes do simbolo
    c[j] = c[i];
    while (j < 50)
    {
        c[j] = c[j + 1];
        j++;
    }

    return valor;
}

void print_cadeia(char exp_reg[], char cadeia[])
{
    printf("\nEXPRESSAO REGULAR: \n");
    printf(exp_reg);
    printf("\nCADEIA: \n");
    printf(cadeia); // Mudar para impressao no arquivo
}

void ler_exp(char exp_reg[])
{
    srand((unsigned)time(NULL)); /////
    int tam = strlen(exp_reg);
    char cadeia[50];
    int i;
    int j;
    int qntd;
    int aux = 0;
    int valor;

    for (i = 0; i < tam; i++)
    {
        switch (exp_reg[i])
        {
        case '*':
            valor = exc_simbolo(i, cadeia);
            qntd = rand() % 5;
            printf("%d", qntd);
            j = i - 1;
            while (aux < 1)
            {
                cadeia[j] = valor;
                aux++;
                j++;
            }
            i = j;
            aux = 0;
            break;

            // case '^+':
            //     /* code */
            //     break;

            // case '(':
            //     /* code */
            //     break;

        default:
            break;
        }

        cadeia[i] = exp_reg[i];
    }

    print_cadeia(exp_reg, cadeia);
}

void main(void)
{
    char exp_reg[80];
    gets(exp_reg);
    ler_exp(exp_reg);
}