#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "catalogo.h" // Inclui nosso próprio arquivo de cabeçalho

int Menu() {
    int Resposta;
    printf("**--------------- Bem vindo ao menu do nosso catálogo de filmes ---------------**\n\n");
    printf(" 1 - Entrada de dados do filme\n");
    printf(" 2 - Lista todos os filmes na tela\n");
    printf(" 3 - Pesquisa um filme pelo nome completo e mostra todos os dados na tela\n");
    printf(" 4 - Pesquisar data de lançamento do filme (mês/ano)\n");
    printf(" 5 - Listar filmes por faixa de preço\n");
    printf(" 6 - Altera quantidade em estoque (entrada e saída)\n");
    printf(" 7 - Altera preço de um filme pesquisado pelo nome completo\n");
    printf(" 8 - Altera todos os dados do filme pesquisado pelo nome completo\n");
    printf(" 9 - Exclui filme pesquisado pelo nome completo\n");
    printf("10 - Saída\n");
    printf("\nDigite a opção que deseja: ");
    scanf("%d", &Resposta);
    getchar();
    system("cls");
    return Resposta;
}

int main() {
    int Resposta;
    struct Filme filme;
    char filmepesquisado[21];
    FILE *catalogo;
    setlocale(LC_ALL, "");

    for (;;) {
        system("cls");
        switch (Menu()) {
            case 1:
                Entrada(catalogo, &filme, filmepesquisado);
                break;

            case 2:
                Listagem(catalogo, &filme);
                break;

            case 3:
                printf("**--------------- Pesquisa ---------------**\n\n");
                printf("Insira o nome do filme que deseja consultar: ");
                gets(filmepesquisado);
                Pesquisa(catalogo, &filme, filmepesquisado);
                break;

            case 4:
                PesquisaData(catalogo, &filme);
                break;

            case 5:
                FaixaPreco(catalogo, &filme);
                break;

            case 6:
                printf("Insira o nome do filme que deseja atualizar a quantidade em estoque: ");
                gets(filmepesquisado);
                AlteraEstoque(catalogo, &filme, filmepesquisado);
                break;

            case 7:
                printf("Insira o nome do filme que deseja atualizar o preço: ");
                gets(filmepesquisado);
                AlteraPreco(catalogo, &filme, filmepesquisado);
                break;

            case 8:
                printf("Insira o nome do filme que deseja alterar todos os dados: ");
                gets(filmepesquisado);
                AlteraTudo(catalogo, &filme, filmepesquisado);
                break;

            case 9:
                printf("Insira o nome do filme que deseja excluir: ");
                gets(filmepesquisado);
                ExcluirFilme(catalogo, &filme, filmepesquisado);
                break;

            case 10:
                Saida();
                break;
        }
        system("pause");
    }
    return 0;
}
