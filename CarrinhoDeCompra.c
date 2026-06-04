#include <stdio.h>
#include <locale.h>

typedef struct Produtos{
    int codigo;
    char nome [50];
    float preco;
    
} produto;


typedef struct {
    int qtdProdutos;
    produto p;
    
} carrinho;


void exibirProdutos (produto catalogo[]) {
    for (int i = 0; i < 6; i++){
        printf("Código %d - %s - Valor: R$%.2f\n", catalogo[i].codigo, catalogo[i].nome, catalogo[i].preco);
    }
}

void adicionarCarrinho () {
    
}

void exibirCarrinho () {
    
}

void finalizarCompra () {
    
}
    

int main() {
    setlocale(LC_ALL, "");
    int opcaoMenu;
    
    produto catalogo [6] = {
        {1, "Arroz", 12.50},
        {2, "Feijão", 8.0},
        {3, "Batata", 6.50},
        {4, "Frango", 20.60},
        {5, "Cerveja", 4.70},
        {6, "Refrigerante", 7.99}
        
    };
    
    do {
        printf("\n----Carrinho De Compras----\n");
        printf("1 - Catálogo de produtos\n");
        printf("2 - Adicionar ao carrinho\n");
        printf("3 - Exibir carrinho\n");
        printf("4 - Finalizar compra\n");
        printf("5 - Sair\n");
        printf("Selecione a opção desejada: ");
        scanf("%d", &opcaoMenu);
        printf("\n");
        
        switch (opcaoMenu) {
            
            case 1:
                exibirProdutos(catalogo);
            break;
            
            case 2:
            
            break;
            
            case 3:
            
            break;
            
            case 4:
            
            break;
            
            case 5:
            break;
            
            default:
            printf("Opção inválida!");
            
        }
        
    } while (opcaoMenu != 5);
    
    printf("Sistema encerrado.");
    
    return 0;
}