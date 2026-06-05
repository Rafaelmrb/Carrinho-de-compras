#include <stdio.h>
#include <locale.h>
#include <string.h>

typedef struct {
    int codigo;
    char nome[50];
    float preco;
} produto;

typedef struct {
    produto p;
    int quantidade;
} itemCarrinho;

typedef struct {
    itemCarrinho itens[100];
    int qtdItens;
} carrinho;

void exibirProdutos(produto catalogo[], int tamanho) {
    printf("---- CATÁLOGO ----\n");
    for (int i = 0; i < tamanho; i++) {
        printf("Código %d - %s - R$ %.2f\n", catalogo[i].codigo, catalogo[i].nome, catalogo[i].preco);
    }
}

void adicionarCarrinho(produto catalogo[], int tamanhoCatalogo, carrinho *compras) {
    int codigo;
    int quantidade;
    int encontrado = 0;

    printf("Digite o código do produto: ");
    scanf("%d", &codigo);

    for (int i = 0; i < tamanhoCatalogo; i++) {
        if (catalogo[i].codigo == codigo) {
            encontrado = 1;

            printf("Digite a quantidade desejada: ");
            scanf("%d", &quantidade);

            if (quantidade <= 0) {
                printf("Quantidade inválida!\n");
                return;
            }

            for (int j = 0; j < compras->qtdItens; j++) {
                if (compras->itens[j].p.codigo == codigo) {
                    compras->itens[j].quantidade += quantidade;
                    printf("%d unidade(s) de %s adicionada(s) ao carrinho!\n",
                           quantidade, catalogo[i].nome);
                    return;
                }
            }

            compras->itens[compras->qtdItens].p = catalogo[i];
            compras->itens[compras->qtdItens].quantidade = quantidade;
            compras->qtdItens++;

            printf("%d unidade(s) de %s adicionada(s) ao carrinho!\n",
                   quantidade, catalogo[i].nome);
            return;
        }
    }

    if (!encontrado) {
        printf("Produto não encontrado!\n");
    }
}

void exibirCarrinho(carrinho compras) {

    if (compras.qtdItens == 0) {
        printf("Carrinho vazio!\n");
        return;
    }

    printf("--- CARRINHO ---\n");
    for (int i = 0; i < compras.qtdItens; i++) {
        printf("%s | Quantidade: %d | Subtotal: R$ %.2f\n", compras.itens[i].p.nome, compras.itens[i].quantidade, compras.itens[i].quantidade *compras.itens[i].p.preco);
    }
}

void salvarCompra(carrinho compras, float totalFinal) {
    FILE *arquivo = fopen("compras.txt", "a"); // "a" = append (não sobrescreve)

    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo!\n");
        return;
    }

    fprintf(arquivo, "---- NOVA COMPRA ----\n");

    for (int i = 0; i < compras.qtdItens; i++) {
        fprintf(arquivo, "%s | Qtd: %d | Preço: %.2f | Subtotal: %.2f\n",
                compras.itens[i].p.nome,
                compras.itens[i].quantidade,
                compras.itens[i].p.preco,
                compras.itens[i].quantidade * compras.itens[i].p.preco);
    }

    fprintf(arquivo, "TOTAL FINAL: R$ %.2f\n", totalFinal);
    fprintf(arquivo, "---------------------\n\n");

    fclose(arquivo);

    printf("Compra salva com sucesso!\n");
}

void finalizarCompra(carrinho compras) {
    float total = 0;
    float descontoPercentual = 10.0;
    float impostoPercentual = 5.0; 

    if (compras.qtdItens == 0) {
        printf("Carrinho vazio!\n");
        return;
    }

    printf("---- RESUMO DA COMPRA ----\n");
    for (int i = 0; i < compras.qtdItens; i++) {
        float subtotal = compras.itens[i].quantidade * compras.itens[i].p.preco;
        total += subtotal;
        printf("%s | Qtd: %d | R$ %.2f\n", compras.itens[i].p.nome, compras.itens[i].quantidade, subtotal);
    }
    
    printf("\nTOTAL BRUTO: R$ %.2f\n", total);

    float valorDesconto = total * (descontoPercentual / 100.0);
    float totalComDesconto = total - valorDesconto;

    float valorImposto = totalComDesconto * (impostoPercentual / 100.0);
    float totalFinal = totalComDesconto + valorImposto;


    printf("\n---- CÁLCULOS FINAIS ----\n");
    printf("Desconto: -R$ %.2f\n", valorDesconto);
    printf("Imposto: +R$ %.2f\n", valorImposto);
    printf("TOTAL FINAL: R$ %.2f\n", totalFinal);
    
    salvarCompra(compras, totalFinal);
}

int main() {
    setlocale(LC_ALL, "");
    int opcaoMenu;

    produto catalogo[6] = {
        {1, "Arroz", 12.50},
        {2, "Feijão", 8.00},
        {3, "Batata", 6.50},
        {4, "Frango", 20.60},
        {5, "Cerveja", 4.70},
        {6, "Refrigerante", 7.99}
    };

    carrinho compras;
    compras.qtdItens = 0;

    do {

        printf("\n---- CARRINHO DE COMPRAS ----\n");
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
                exibirProdutos(catalogo, 6);
                break;

            case 2:
                adicionarCarrinho(catalogo, 6, &compras);
                break;

            case 3:
                exibirCarrinho(compras);
                break;

            case 4:
                finalizarCompra(compras);
                break;

            case 5:
                break;

            default:
                printf("Opção inválida!\n");
        }

    } while (opcaoMenu != 5);

    printf("Sistema encerrado.\n");

    return 0;
}
