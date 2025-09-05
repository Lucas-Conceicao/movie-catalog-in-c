# Sistema de Catálogo de Filmes em C

![Linguagem C](https://img.shields.io/badge/Linguagem-C-blue.svg)
![Licença](https://img.shields.io/badge/Licen%C3%A7a-MIT-green.svg)

Um sistema simples de gerenciamento de catálogo de filmes desenvolvido em C puro. O projeto implementa funcionalidades de CRUD (Create, Read, Update, Delete) para um catálogo de filmes, com todos os dados persistidos em um arquivo binário. Este projeto foi criado como parte do meu portfólio de estudos em Análise e Desenvolvimento de Sistemas.

## 🚀 Funcionalidades

* **Cadastro de Filmes:** Adiciona novos filmes ao catálogo com nome, quantidade, preço e data de lançamento.
* **Listagem Completa:** Exibe todos os filmes cadastrados no catálogo.
* **Pesquisa por Nome:** Busca um filme específico pelo seu nome completo.
* **Pesquisa por Data:** Lista todos os filmes lançados em um determinado mês/ano.
* **Filtro por Preço:** Exibe filmes dentro de uma faixa de preço definida pelo usuário.
* **Atualização de Dados:** Permite alterar o estoque, o preço ou todos os dados de um filme.
* **Exclusão Lógica:** Remove filmes do catálogo (através de marcação, sem apagar o registro fisicamente).

## 🛠️ Tecnologias Utilizadas

* **Linguagem:** C
* **Compilador:** GCC
* **IDE:** Code::Blocks

## 📂 Estrutura de Pastas

O projeto está organizado da seguinte forma para manter o código-fonte separado de outros arquivos:

```
/
├── .gitignore
├── README.md
└── src/
    ├── catalogo.c
    ├── catalogo.h
    └── main.c
```

## ⚙️ Como Compilar e Executar

### Pré-requisitos
É necessário ter um compilador C (como o GCC) instalado e configurado no seu sistema.

### Passos para Compilação
1.  Clone o repositório:
    ```bash
    git clone [https://github.com/Lucas-Conceicao/movie-catalog-in-c.git](https://github.com/Lucas-Conceicao/movie-catalog-in-c.git)
    ```
2.  Navegue até a pasta do projeto:
    ```bash
    cd movie-catalog-in-c
    ```
3.  Compile os arquivos-fonte. O executável será criado na pasta raiz do projeto.
    ```bash
    gcc src/main.c src/catalogo.c -o catalogo_app
    ```
4.  Execute o programa:
    * No Windows:
        ```bash
        catalogo_app.exe
        ```
    * No Linux ou macOS:
        ```bash
        ./catalogo_app
        ```

O programa irá gerar automaticamente o arquivo `catalogo.txt` para armazenar os dados.

## 📝 Licença

Este projeto está sob a licença MIT. Veja o arquivo `LICENSE` para mais detalhes.
