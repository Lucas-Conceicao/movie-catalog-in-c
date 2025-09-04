#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Inclu�do para usar a fun��o strcmp() e strcspn()
#include "catalogo.h" // Inclui nosso pr�prio arquivo de cabe�alho

int Pesquisa(FILE *catalogo, struct Filme *filme, char *filmepesquisado) {
    int x, posicao = 0;
    catalogo = fopen("catalogo.txt", "r");

    if (catalogo == NULL) {
        printf("N�o foi poss�vel abrir o cat�logo\n");
        return -1;
    }

    while (fread(filme, sizeof(struct Filme), 1, catalogo) == 1) {
        for (x = 0; filmepesquisado[x] != '\0'; x++)
            if (filme->nome[x] != filmepesquisado[x])
                break;
        if (filme->nome[x] == '\0' && filmepesquisado[x] == '\0') {
            printf("Nome do filme: %s\n", filme->nome);
            printf("Quantidade dispon�vel: %d\n", filme->quantidade);
            printf("Pre�o: %.2f\n", filme->preco);
            printf("Data de lan�amento: %d/%d\n\n", filme->mes, filme->ano);
            fclose(catalogo);
            return posicao; // se tiver alguma igual
        }
        posicao++;
    }
    fclose(catalogo);
    return -1;
}

void Entrada(FILE *catalogo, struct Filme *filme, char *filmepesquisado) {
    int x, pesquisa;
    catalogo = fopen("catalogo.txt", "a+");

    if (catalogo == NULL) {
        printf("N�o foi poss�vel abrir o cat�logo\n");
        return;
    }
    printf("**--------------- Entrada de dados ---------------**\n\n");
    printf("Digite o nome do filme: ");
    do {
        gets(filmepesquisado);
        pesquisa = Pesquisa(catalogo, filme, filmepesquisado);
        if (pesquisa > -1) {
            printf("Esse filme j� est� cadastrado! Favor inserir outro: ");
        }
    } while (pesquisa > -1);

    for (x = 0; filmepesquisado[x] != '\0'; x++)
        filme->nome[x] = filmepesquisado[x];
    filme->nome[x] = '\0';

    printf("Digite a quantidade dispon�vel: ");
    do {
        scanf("%d", &filme->quantidade);
        getchar();
        if (filme->quantidade < 0)
            printf("A quantidade dispon�vel deve ser maior ou igual a 0: ");
    } while (filme->quantidade < 0);

    printf("Digite o pre�o do filme: ");
    do {
        scanf("%f", &filme->preco);
        getchar();
        if (filme->preco < 0)
            printf("O pre�o do filme deve ser maior que 0: ");
    } while (filme->preco < 0);

    printf("Digite o m�s de lan�amento: ");
    do {
        scanf("%d", &filme->mes);
        getchar();
        if (filme->mes > 12 || filme->mes < 1)
            printf("O m�s deve ser um n�mero entre 1 e 12: ");
    } while (filme->mes > 12 || filme->mes < 1);

    printf("Digite o ano de lan�amento: ");
    do {
        scanf("%d", &filme->ano);
        if (filme->ano < 1888 )
            printf("O ano deve ser igual ou superior a 1888 : "); // data do primeiro filme lan�ado
    } while (filme->ano < 1888 );
    printf("\nFilme cadastrado com sucesso!!!\n");

    fwrite(filme, sizeof(struct Filme), 1, catalogo);
    fclose(catalogo);
}

void Listagem(FILE *catalogo, struct Filme *filme) {
    catalogo = fopen("catalogo.txt", "r");

    if (catalogo == NULL) {
        printf("N�o foi poss�vel abrir o cat�logo\n");
        return;
    }
    printf("**--------------- Listagem ---------------**\n\n");
    while (fread(filme, sizeof(struct Filme), 1, catalogo) == 1) {
        if (filme->nome[0] != '*') {
            printf("Nome do filme: %s\n", filme->nome);
            printf("Quantidade dispon�vel: %d\n", filme->quantidade);
            printf("Pre�o: %.2f\n", filme->preco);
            printf("Data de lan�amento: %d/%d\n\n", filme->mes, filme->ano);
        }
    }
    fclose(catalogo);
}

void PesquisaData(FILE *catalogo, struct Filme *filme) {
    int ano, mes, cont = 0;

    catalogo = fopen("catalogo.txt", "r");

    if (catalogo == NULL) {
        printf("N�o foi poss�vel abrir o cat�logo\n");
        return;
    }

    printf("**--------------- Pesquisa Data ---------------**\n\n");
    printf("M�s de lan�amento: ");
    do {
        scanf("%d", &mes);
        getchar();
        if (mes > 12 || mes < 1)
            printf("O m�s deve ser um n�mero entre 1 e 12: ");
    } while (mes > 12 || mes < 1);

    printf("Ano de lan�amento: ");
    do {
        scanf("%d", &ano);
        getchar();
        if (ano < 1888 )
            printf("O ano deve ser igual ou superior a 1888 : ");
    } while (ano < 1888 );

    while (fread(filme, sizeof(struct Filme), 1, catalogo) == 1) {
        if (ano == filme->ano && mes == filme->mes && filme->nome[0] != '*') {
            printf("\nNome do filme: %s\n", filme->nome);
            printf("Quantidade dispon�vel: %d\n", filme->quantidade);
            printf("Pre�o: %.2f\n", filme->preco);
            printf("Data de lan�amento: %d/%d\n\n", filme->mes, filme->ano);
            cont++;
        }
    }

    if (cont == 0)
        printf("N�o h� filmes cadastrados com essa data de lan�amento\n\n");

    fclose(catalogo);
}

void FaixaPreco(FILE *catalogo, struct Filme *filme) {
    float min, max;
    int cont = 0;

    catalogo = fopen("catalogo.txt", "r");

    if (catalogo == NULL) {
        printf("N�o foi poss�vel abrir o cat�logo\n");
        return;
    }

    printf("**--------------- Faixa de Pre�o ---------------**\n\n");
    printf("Insira o pre�o m�nimo: ");
    do {
        scanf("%f", &min);
        getchar();
        if (min < 0)
            printf("O valor m�nimo deve ser igual ou superior a 0: ");
    } while (min < 0);

    printf("Insira o pre�o m�ximo: ");
    do {
        scanf("%f", &max);
        getchar();
        if (max < min)
            printf("O valor m�ximo deve ser maior ou igual ao valor m�nimo: ");
    } while (max < min);

    while (fread(filme, sizeof(struct Filme), 1, catalogo) == 1) {
        if (filme->preco >= min && filme->preco <= max && filme->nome[0] != '*') {
            printf("\nNome do filme: %s\n", filme->nome);
            printf("Quantidade dispon�vel: %d\n", filme->quantidade);
            printf("Pre�o: %.2f\n", filme->preco);
            printf("Data de lan�amento: %d/%d\n\n", filme->mes, filme->ano);
            cont++;
        }
    }

    if (cont == 0)
        printf("N�o h� filmes cadastrados nessa faixa de pre�o\n\n");

    fclose(catalogo);
}

void AlteraEstoque(FILE *catalogo, struct Filme *filme, char *filmepesquisado) {
    int Novaquant;
    printf("\n");
    long Consulta;
    Consulta = Pesquisa(catalogo, filme, filmepesquisado);

    if (Consulta == -1) {
        printf("Filme n�o cadastrado\n\n!!!");
        return;
    }

    catalogo = fopen("catalogo.txt", "r+");
    if (catalogo == NULL) {
        printf("N�o foi poss�vel abrir o cat�logo\n");
        return;
    }
    printf("**--------------- Atualizando o Estoque ---------------**\n\n");
    Consulta *= sizeof(struct Filme);
    fseek(catalogo, Consulta, SEEK_SET);
    fread(filme, sizeof(struct Filme), 1, catalogo);

    printf("Insira a nova quantidade: ");
    do {
        scanf("%d", &Novaquant);
        getchar();
        if (Novaquant < 0)
            printf("Digite um valor v�lido: ");
    } while (Novaquant < 0);
    filme->quantidade = Novaquant;

    fseek(catalogo, Consulta, SEEK_SET);
    fwrite(filme, sizeof(struct Filme), 1, catalogo);

    fclose(catalogo);
    printf("\nQuantidade atualizada com sucesso!!!\n\n");
}

void AlteraPreco(FILE *catalogo, struct Filme *filme, char *filmepesquisado) {
    float Novopreco;
    printf("\n");
    long Consulta;
    Consulta = Pesquisa(catalogo, filme, filmepesquisado);

    if (Consulta == -1) {
        printf("Filme n�o cadastrado!!!\n\n");
        return;
    }

    catalogo = fopen("catalogo.txt", "r+");
    if (catalogo == NULL) {
        printf("N�o foi poss�vel abrir o cat�logo\n");
        return;
    }
    printf("**--------------- Alterar Pre�o ---------------**\n\n");
    Consulta *= sizeof(struct Filme);
    fseek(catalogo, Consulta, SEEK_SET);
    fread(filme, sizeof(struct Filme), 1, catalogo);

    printf("Insira o novo pre�o: ");
    do {
        scanf("%f", &Novopreco);
        getchar();
        if (Novopreco < 0)
            printf("O pre�o deve ser maior que 0: ");
    } while (Novopreco < 0);
    filme->preco = Novopreco;

    fseek(catalogo, Consulta, SEEK_SET);
    fwrite(filme, sizeof(struct Filme), 1, catalogo);

    fclose(catalogo);
    printf("\nPre�o atualizado com sucesso!!!\n\n");
}

void AlteraTudo(FILE *catalogo, struct Filme *filme, char *filmepesquisado) {
    int x;
    float p;
    printf("\n");
    long Consulta;
    Consulta = Pesquisa(catalogo, filme, filmepesquisado);

    if (Consulta == -1) {
        printf("Filme n�o cadastrado!!!\n\n");
        return;
    }

    catalogo = fopen("catalogo.txt", "r+");
    if (catalogo == NULL) {
        printf("N�o foi poss�vel abrir o cat�logo\n");
        return;
    }
    printf("**--------------- Alterar todos os dados ---------------**\n\n");
    Consulta *= sizeof(struct Filme);
    fseek(catalogo, Consulta, SEEK_SET);
    fread(filme, sizeof(struct Filme), 1, catalogo);

    printf("Nome do Filme: ");
    do {
        gets(filmepesquisado);
        x = Pesquisa(catalogo, filme, filmepesquisado);
        if (x > -1)
            printf("Esse filme j� est� cadastrado. Favor inserir outro: ");
    } while (x > -1);
    for (x = 0; filmepesquisado[x] != '\0'; x++)
        filme->nome[x] = filmepesquisado[x];
    filme->nome[x] = '\0';

    printf("Quantidade: ");
    do {
        scanf("%d", &x);
        getchar();
        if (x < 0)
            printf("Digite um valor v�lido: ");
    } while (x < 0);
    filme->quantidade = x;

    printf("Pre�o: ");
    do {
        scanf("%f", &p);
        getchar();
        if (p < 0)
            printf("Digite um valor v�lido: ");
    } while (p < 0);
    filme->preco = p;

    printf("M�s de lan�amento: ");
    do {
        scanf("%d", &x);
        getchar();
        if (x > 12 || x < 1)
            printf("O m�s deve ser um n�mero entre 1 e 12: ");
    } while (x > 12 || x < 1);
    filme->mes = x;

    printf("Ano de lan�amento: ");
    do {
        scanf("%d", &x);
        getchar();
        if (x < 1888 )
            printf("O ano deve ser igual ou superior a 1888 : ");
    } while (x < 1888 );
    filme->ano = x;

    fseek(catalogo, Consulta, SEEK_SET);
    fwrite(filme, sizeof(struct Filme), 1, catalogo);

    fclose(catalogo);
    printf("\nDados alterados com sucesso!!!\n\n");
}

void ExcluirFilme(FILE *catalogo, struct Filme *filme, char *filmepesquisado) {
    printf("\n");
    char Resposta;
    long Consulta;
    Consulta = Pesquisa(catalogo, filme, filmepesquisado);

    if (Consulta == -1) {
        printf("Filme n�o cadastrado!!!\n\n");
        return;
    }

    catalogo = fopen("catalogo.txt", "r+");
    if (catalogo == NULL) {
        printf("N�o foi poss�vel abrir o cat�logo\n");
        return;
    }

    printf("**--------------- Excluir filme ---------------**\n\n");
    Consulta *= sizeof(struct Filme);
    fseek(catalogo, Consulta, SEEK_SET);
    fread(filme, sizeof(struct Filme), 1, catalogo);

    printf("Essa a��o n�o pode ser desfeita!\n");
    printf("Voc� tem certeza que deseja excluir esse registro? (S/N): ");
    Resposta = getchar();

    if (Resposta == 's' || Resposta == 'S') {
        filme->nome[0] = '*'; // excluindo logicamente
        fseek(catalogo, Consulta, SEEK_SET);
        fwrite(filme, sizeof(struct Filme), 1, catalogo);
        printf("\nFilme exclu�do com sucesso!!!\n\n");
    } else {
        printf("Retornando ao menu...\n\n");
    }
    fclose(catalogo);
}

void Saida() {
    printf("Fechando o menu...\n\n");
    exit(0);
}
