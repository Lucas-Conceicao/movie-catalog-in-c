#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Incluído para usar a função strcmp() e strcspn()
#include "catalogo.h" // Inclui nosso próprio arquivo de cabeçalho

int Pesquisa(FILE *catalogo, struct Filme *filme, char *filmepesquisado) {
    int x, posicao = 0;
    catalogo = fopen("catalogo.txt", "r");

    if (catalogo == NULL) {
        printf("Não foi possível abrir o catálogo\n");
        return -1;
    }

    while (fread(filme, sizeof(struct Filme), 1, catalogo) == 1) {
        for (x = 0; filmepesquisado[x] != '\0'; x++)
            if (filme->nome[x] != filmepesquisado[x])
                break;
        if (filme->nome[x] == '\0' && filmepesquisado[x] == '\0') {
            printf("Nome do filme: %s\n", filme->nome);
            printf("Quantidade disponível: %d\n", filme->quantidade);
            printf("Preço: %.2f\n", filme->preco);
            printf("Data de lançamento: %d/%d\n\n", filme->mes, filme->ano);
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
        printf("Não foi possível abrir o catálogo\n");
        return;
    }
    printf("**--------------- Entrada de dados ---------------**\n\n");
    printf("Digite o nome do filme: ");
    do {
        gets(filmepesquisado);
        pesquisa = Pesquisa(catalogo, filme, filmepesquisado);
        if (pesquisa > -1) {
            printf("Esse filme já está cadastrado! Favor inserir outro: ");
        }
    } while (pesquisa > -1);

    for (x = 0; filmepesquisado[x] != '\0'; x++)
        filme->nome[x] = filmepesquisado[x];
    filme->nome[x] = '\0';

    printf("Digite a quantidade disponível: ");
    do {
        scanf("%d", &filme->quantidade);
        getchar();
        if (filme->quantidade < 0)
            printf("A quantidade disponível deve ser maior ou igual a 0: ");
    } while (filme->quantidade < 0);

    printf("Digite o preço do filme: ");
    do {
        scanf("%f", &filme->preco);
        getchar();
        if (filme->preco < 0)
            printf("O preço do filme deve ser maior que 0: ");
    } while (filme->preco < 0);

    printf("Digite o mês de lançamento: ");
    do {
        scanf("%d", &filme->mes);
        getchar();
        if (filme->mes > 12 || filme->mes < 1)
            printf("O mês deve ser um número entre 1 e 12: ");
    } while (filme->mes > 12 || filme->mes < 1);

    printf("Digite o ano de lançamento: ");
    do {
        scanf("%d", &filme->ano);
        if (filme->ano < 1888 )
            printf("O ano deve ser igual ou superior a 1888 : "); // data do primeiro filme lançado
    } while (filme->ano < 1888 );
    printf("\nFilme cadastrado com sucesso!!!\n");

    fwrite(filme, sizeof(struct Filme), 1, catalogo);
    fclose(catalogo);
}

void Listagem(FILE *catalogo, struct Filme *filme) {
    catalogo = fopen("catalogo.txt", "r");

    if (catalogo == NULL) {
        printf("Não foi possível abrir o catálogo\n");
        return;
    }
    printf("**--------------- Listagem ---------------**\n\n");
    while (fread(filme, sizeof(struct Filme), 1, catalogo) == 1) {
        if (filme->nome[0] != '*') {
            printf("Nome do filme: %s\n", filme->nome);
            printf("Quantidade disponível: %d\n", filme->quantidade);
            printf("Preço: %.2f\n", filme->preco);
            printf("Data de lançamento: %d/%d\n\n", filme->mes, filme->ano);
        }
    }
    fclose(catalogo);
}

void PesquisaData(FILE *catalogo, struct Filme *filme) {
    int ano, mes, cont = 0;

    catalogo = fopen("catalogo.txt", "r");

    if (catalogo == NULL) {
        printf("Não foi possível abrir o catálogo\n");
        return;
    }

    printf("**--------------- Pesquisa Data ---------------**\n\n");
    printf("Mês de lançamento: ");
    do {
        scanf("%d", &mes);
        getchar();
        if (mes > 12 || mes < 1)
            printf("O mês deve ser um número entre 1 e 12: ");
    } while (mes > 12 || mes < 1);

    printf("Ano de lançamento: ");
    do {
        scanf("%d", &ano);
        getchar();
        if (ano < 1888 )
            printf("O ano deve ser igual ou superior a 1888 : ");
    } while (ano < 1888 );

    while (fread(filme, sizeof(struct Filme), 1, catalogo) == 1) {
        if (ano == filme->ano && mes == filme->mes && filme->nome[0] != '*') {
            printf("\nNome do filme: %s\n", filme->nome);
            printf("Quantidade disponível: %d\n", filme->quantidade);
            printf("Preço: %.2f\n", filme->preco);
            printf("Data de lançamento: %d/%d\n\n", filme->mes, filme->ano);
            cont++;
        }
    }

    if (cont == 0)
        printf("Não há filmes cadastrados com essa data de lançamento\n\n");

    fclose(catalogo);
}

void FaixaPreco(FILE *catalogo, struct Filme *filme) {
    float min, max;
    int cont = 0;

    catalogo = fopen("catalogo.txt", "r");

    if (catalogo == NULL) {
        printf("Não foi possível abrir o catálogo\n");
        return;
    }

    printf("**--------------- Faixa de Preço ---------------**\n\n");
    printf("Insira o preço mínimo: ");
    do {
        scanf("%f", &min);
        getchar();
        if (min < 0)
            printf("O valor mínimo deve ser igual ou superior a 0: ");
    } while (min < 0);

    printf("Insira o preço máximo: ");
    do {
        scanf("%f", &max);
        getchar();
        if (max < min)
            printf("O valor máximo deve ser maior ou igual ao valor mínimo: ");
    } while (max < min);

    while (fread(filme, sizeof(struct Filme), 1, catalogo) == 1) {
        if (filme->preco >= min && filme->preco <= max && filme->nome[0] != '*') {
            printf("\nNome do filme: %s\n", filme->nome);
            printf("Quantidade disponível: %d\n", filme->quantidade);
            printf("Preço: %.2f\n", filme->preco);
            printf("Data de lançamento: %d/%d\n\n", filme->mes, filme->ano);
            cont++;
        }
    }

    if (cont == 0)
        printf("Não há filmes cadastrados nessa faixa de preço\n\n");

    fclose(catalogo);
}

void AlteraEstoque(FILE *catalogo, struct Filme *filme, char *filmepesquisado) {
    int Novaquant;
    printf("\n");
    long Consulta;
    Consulta = Pesquisa(catalogo, filme, filmepesquisado);

    if (Consulta == -1) {
        printf("Filme não cadastrado\n\n!!!");
        return;
    }

    catalogo = fopen("catalogo.txt", "r+");
    if (catalogo == NULL) {
        printf("Não foi possível abrir o catálogo\n");
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
            printf("Digite um valor válido: ");
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
        printf("Filme não cadastrado!!!\n\n");
        return;
    }

    catalogo = fopen("catalogo.txt", "r+");
    if (catalogo == NULL) {
        printf("Não foi possível abrir o catálogo\n");
        return;
    }
    printf("**--------------- Alterar Preço ---------------**\n\n");
    Consulta *= sizeof(struct Filme);
    fseek(catalogo, Consulta, SEEK_SET);
    fread(filme, sizeof(struct Filme), 1, catalogo);

    printf("Insira o novo preço: ");
    do {
        scanf("%f", &Novopreco);
        getchar();
        if (Novopreco < 0)
            printf("O preço deve ser maior que 0: ");
    } while (Novopreco < 0);
    filme->preco = Novopreco;

    fseek(catalogo, Consulta, SEEK_SET);
    fwrite(filme, sizeof(struct Filme), 1, catalogo);

    fclose(catalogo);
    printf("\nPreço atualizado com sucesso!!!\n\n");
}

void AlteraTudo(FILE *catalogo, struct Filme *filme, char *filmepesquisado) {
    int x;
    float p;
    printf("\n");
    long Consulta;
    Consulta = Pesquisa(catalogo, filme, filmepesquisado);

    if (Consulta == -1) {
        printf("Filme não cadastrado!!!\n\n");
        return;
    }

    catalogo = fopen("catalogo.txt", "r+");
    if (catalogo == NULL) {
        printf("Não foi possível abrir o catálogo\n");
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
            printf("Esse filme já está cadastrado. Favor inserir outro: ");
    } while (x > -1);
    for (x = 0; filmepesquisado[x] != '\0'; x++)
        filme->nome[x] = filmepesquisado[x];
    filme->nome[x] = '\0';

    printf("Quantidade: ");
    do {
        scanf("%d", &x);
        getchar();
        if (x < 0)
            printf("Digite um valor válido: ");
    } while (x < 0);
    filme->quantidade = x;

    printf("Preço: ");
    do {
        scanf("%f", &p);
        getchar();
        if (p < 0)
            printf("Digite um valor válido: ");
    } while (p < 0);
    filme->preco = p;

    printf("Mês de lançamento: ");
    do {
        scanf("%d", &x);
        getchar();
        if (x > 12 || x < 1)
            printf("O mês deve ser um número entre 1 e 12: ");
    } while (x > 12 || x < 1);
    filme->mes = x;

    printf("Ano de lançamento: ");
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
        printf("Filme não cadastrado!!!\n\n");
        return;
    }

    catalogo = fopen("catalogo.txt", "r+");
    if (catalogo == NULL) {
        printf("Não foi possível abrir o catálogo\n");
        return;
    }

    printf("**--------------- Excluir filme ---------------**\n\n");
    Consulta *= sizeof(struct Filme);
    fseek(catalogo, Consulta, SEEK_SET);
    fread(filme, sizeof(struct Filme), 1, catalogo);

    printf("Essa ação não pode ser desfeita!\n");
    printf("Você tem certeza que deseja excluir esse registro? (S/N): ");
    Resposta = getchar();

    if (Resposta == 's' || Resposta == 'S') {
        filme->nome[0] = '*'; // excluindo logicamente
        fseek(catalogo, Consulta, SEEK_SET);
        fwrite(filme, sizeof(struct Filme), 1, catalogo);
        printf("\nFilme excluído com sucesso!!!\n\n");
    } else {
        printf("Retornando ao menu...\n\n");
    }
    fclose(catalogo);
}

void Saida() {
    printf("Fechando o menu...\n\n");
    exit(0);
}
