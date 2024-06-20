#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

// definição da estrutura livro
typedef struct {
    int id;
    char titulo[100];
    char autor[100];
} Livro;

// definição da árvore de busca binária
typedef struct No {
    Livro livro;
    struct No* esquerda;
    struct No* direita;
} NoArvore;

// função que cria um novo nó na árvore
NoArvore* criarNo(Livro livro) {
    NoArvore* novoNo = (NoArvore*)malloc(sizeof(NoArvore));
    novoNo->livro = livro;
    novoNo->esquerda = NULL;
    novoNo->direita = NULL;
    return novoNo;
}

// função que insere um novo livro na árvore
NoArvore* inserirLivro(NoArvore* raiz, Livro livro) {
    if (raiz == NULL) {
        return criarNo(livro);
    }
    if (livro.id < raiz->livro.id) {
        raiz->esquerda = inserirLivro(raiz->esquerda, livro);
    } else if (livro.id > raiz->livro.id) {
        raiz->direita = inserirLivro(raiz->direita, livro);
    }
    return raiz;
}

// função para procurar um livro pelo id
NoArvore* buscarLivro(NoArvore* raiz, int id) {
    if (raiz == NULL || raiz->livro.id == id) {
        return raiz;
    }
    if (id < raiz->livro.id) {
        return buscarLivro(raiz->esquerda, id);
    }
    return buscarLivro(raiz->direita, id);
}

// função para listar os livros em ordem crescente
void listarLivros(NoArvore* raiz) {
    if (raiz != NULL) {
        listarLivros(raiz->esquerda);
        printf("ID: %d, Titulo: %s, Autor: %s\n", raiz->livro.id, raiz->livro.titulo, raiz->livro.autor);
        listarLivros(raiz->direita);
    }
}

// função para encontrar sucessor (nó com menor valor maior que o id)
NoArvore* encontrarSucessor(NoArvore* no) {
    NoArvore* atual = no->direita;
    while (atual && atual->esquerda) {
        atual = atual->esquerda;
    }
    return atual;
}

// função que remove um livro pelo id
NoArvore* removerLivro(NoArvore* raiz, int id) {
    if (raiz == NULL) {
        return raiz;
    }

    // achar o nó com id desejado
    if (id < raiz->livro.id) {
        raiz->esquerda = removerLivro(raiz->esquerda, id);
    } else if (id > raiz->livro.id) {
        raiz->direita = removerLivro(raiz->direita, id);
    } else {
        // nó com id não encontrado

        // caso 1: nó sem nenhum filho ou com apenas um
        if (raiz->esquerda == NULL) {
            NoArvore* temp = raiz->direita;
            free(raiz);
            return temp;
        } else if (raiz->direita == NULL) {
            NoArvore* temp = raiz->esquerda;
            free(raiz);
            return temp;
        }

        // caso 2: nó com dois filhos
        NoArvore* sucessor = encontrarSucessor(raiz);
        raiz->livro = sucessor->livro;
        raiz->direita = removerLivro(raiz->direita, sucessor->livro.id);
    }
    return raiz;
}

// função para checar se a árvore está vazia
int arvoreVazia(NoArvore* raiz) {
    return raiz == NULL;
}

int main() {
    
    NoArvore* raiz = NULL;
    int opcao;
    Livro novoLivro;
    int idBusca;
    char linha[100];
    setlocale(LC_ALL,"Portuguese");

    while (1) {
        printf("\nMenu de Opcoes:\n");
        printf("1. Inserir Livro\n");
        printf("2. Buscar Livro\n");
        printf("3. Remover Livro\n");
        printf("4. Listar Livros\n");
        printf("5. Verificar se a arvore esta Vazia\n");
        printf("6. Sair\n");
        printf("Digite a opcoes desejada: ");

        fgets(linha, sizeof(linha), stdin);
        sscanf(linha, "%d", &opcao);

        switch (opcao) {
            case 1:
                printf("\nInsira as informacoes do livro:\n");
                printf("ID: ");
                fgets(linha, sizeof(linha), stdin);
                sscanf(linha, "%d", &novoLivro.id);
                printf("Titulo: ");
                fgets(linha, sizeof(linha), stdin);
                strcpy(novoLivro.titulo, linha);  
                novoLivro.titulo[strlen(novoLivro.titulo) - 1] = '\0';
                printf("Autor: ");
                fgets(linha, sizeof(linha), stdin);
                strcpy(novoLivro.autor, linha);
                novoLivro.autor[strlen(novoLivro.autor) - 1] = '\0'; 
                raiz = inserirLivro(raiz, novoLivro);
                printf("Livro inserido com sucesso!\n");
                break;

            case 2:
                printf("\nDigite o ID do livro que deseja buscar: ");
                fgets(linha, sizeof(linha), stdin);
                sscanf(linha, "%d", &idBusca);
                NoArvore* livroEncontrado = buscarLivro(raiz, idBusca);
                if (livroEncontrado != NULL) {
                    printf("\nLivro encontrado:\n");
                    printf("ID: %d\n", livroEncontrado->livro.id);
                    printf("Titulo: %s\n", livroEncontrado->livro.titulo);
                    printf("Autor: %s\n", livroEncontrado->livro.autor);
                } else {
                    printf("Livro não encontrado!\n");
                }
                break;

            case 3:
                printf("\nDigite o ID do livro que deseja remover: ");
                fgets(linha, sizeof(linha), stdin);
                sscanf(linha, "%d", &idBusca);
                raiz = removerLivro(raiz, idBusca);
                if (raiz != NULL) {
                    printf("Livro removido com sucesso!\n");
                } else {
                    printf("Livro nao encontrado!\n");
                }
                break;

            case 4:
                if (arvoreVazia(raiz)) {
                    printf("\nArvore vazia!\n");
                } else {
                    printf("\nLivros:\n");
                    listarLivros(raiz);
                }
                break;

            case 5:
                if (arvoreVazia(raiz)) {
                    printf("\nArvore vazia!\n");
                } else {
                    printf("\nArvore nao esta vazia!\n");
                }
                break;

            case 6:
                printf("\nSaindo do programa...\n");
                exit(0);

            default:
                printf("\nOpcao invalida!\n");
        }
    }

    return 0;
}