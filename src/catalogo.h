#ifndef CATALOGO_H
#define CATALOGO_H

#include <stdio.h>

// Definição da estrutura para armazenar os dados de um filme.
// Renomeado de "dados" para "Filme" para maior clareza.
struct Filme {
    char nome[51]; // Aumentei um pouco para nomes de filmes mais longos
    int quantidade;
    float preco;
    int mes;
    int ano;
};

int Pesquisa(FILE *catalogo, struct Filme *filme, char *filmepesquisado);
void Entrada(FILE *catalogo, struct Filme *filme, char *filmepesquisado);
void Listagem(FILE *catalogo, struct Filme *filme);
void PesquisaData(FILE *catalogo, struct Filme *filme);
void FaixaPreco(FILE *catalogo, struct Filme *filme);
void AlteraEstoque(FILE *catalogo, struct Filme *filme, char *filmepesquisado);
void AlteraPreco(FILE *catalogo, struct Filme *filme, char *filmepesquisado);
void AlteraTudo(FILE *catalogo, struct Filme *filme, char *filmepesquisado);
void ExcluirFilme(FILE *catalogo, struct Filme *filme, char *filmepesquisado);
void Saida();

#endif // CATALOGO_H
