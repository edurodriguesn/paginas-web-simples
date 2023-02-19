#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdbool.h>

int main()
{

    int i;
    int parentesis1 = -1;
    int parentesis2;
    int mais = 0;
    int amais;
    int dmais;
    int asterisco = 0;
    int acento = 0;
    int controle = 0;
    int j;

    char exp_reg[10];
    char cadeia[10];

    printf("EXPRESSAO REGULAR\n");
    gets(exp_reg);
    int tam = strlen(exp_reg);

    // VERIFICA OCORRENCIAS DOS SIMBOLOS
    for (i = 0; i < tam; i++)
    {
        if (exp_reg[i] == '(')
        {
            parentesis1 = i;
        }
        else if (exp_reg[i] == ')')
        {
            parentesis2 = i;
        }
        else if (exp_reg[i] == '+')
        {
            mais = i;
        }
        else if (exp_reg[i] == '*')
        {
            if ((exp_reg[i - 1] != ')') && (parentesis1 == -1))
            {
                asterisco = i;
            }
        }
        else if (exp_reg[i] == '^')
        {
            if ((exp_reg[i - 1] != ')') && (parentesis1 == -1))
            {
                acento = i;
            }
        }
    }

    if (asterisco != 0) // sem parentesis mas com asterisco
    {

        for (i = 0; i < 10; i++)
        {
            cadeia[i] = ' ';
        }
        cadeia[0] = '\0';

        strncat(cadeia, exp_reg, tam - 2); // não podia o elemento antes do simbolo OKKKKKK

        int aux = 1;
        printf("CADEIAS\n");
        for (i = 0; i < 5; i++)
        {
            for (j = 0; j < aux; j++)
            {
                printf(cadeia);
                printf("\n");
                strncat(cadeia, &exp_reg[tam - 2], 1);
            }
        }
    }

    else if ((parentesis1 == -1) && (acento != 0)) // sem parentesis mas com acento OKKKKK
    {
        for (i = 0; i < 10; i++)
        {
            cadeia[i] = ' ';
        }
        cadeia[0] = '\0';

        strncat(cadeia, exp_reg, tam - 2); // não podia o elemento antes do simbolo

        int aux = 1;
        printf("CADEIAS\n");
        for (i = 0; i < 5; i++)
        {
            for (j = 0; j < aux; j++)
            {
                strncat(cadeia, &exp_reg[tam - 2], 1);
                printf(cadeia);
                printf("\n");
            }
        }
    }
    else if ((parentesis1 != -1) && (mais == 0)) // tiver parentesis e não o mais OKKKKKK
    {

        char parte[10];
        i = 0;
        for (i = 0; i < 10; i++)
        {
            parte[i] = ' ';
        }
        parte[0] = '\0';

        if ((exp_reg[parentesis2 + 1] == '*') || (exp_reg[parentesis2 + 1] == '^()'))
        {
            parentesis2 = parentesis2 - parentesis1 - 1;
            int aux = 1;
            printf("CADEIAS\n");
            for (i = 0; i < 5; i++)
            {
                for (j = 0; j < aux; j++)
                {
                    strncat(parte, &exp_reg[parentesis1 + 1], parentesis2);
                }
                printf(parte);
                printf("\n");
            }
        }
    }

    // TESTAR E IMPLEMENTAR A LEITURA DEPOIS DO FECHAMENTO DOS PARENTESIS
    else if ((parentesis1 != -1) && (mais != 0)) // tiver parentesis e o mais
    {
        char metade[10];
        i = 0;
        for (i = 0; i < 10; i++)
        {
            metade[i] = ' ';
        }
        metade[0] = '\0';

        for (i = 0; i < 10; i++)
        {
            cadeia[i] = ' ';
        }
        cadeia[0] = '\0';

        if ((controle == 0) && (controle < 3))
        {
            amais = mais - parentesis1 - 1;
            strncat(metade, &exp_reg[parentesis1 + 1], amais);
        }
        else
        {
            dmais = parentesis2 - mais - 1;
            strncat(metade, &exp_reg[mais + 1], dmais);
        }

        char parte[10];
        i = 0;
        for (i = 0; i < 10; i++)
        {
            parte[i] = ' ';
        }
        parte[0] = '\0';

        strcat(parte, metade);
    }
}
