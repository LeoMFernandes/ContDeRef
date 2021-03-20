#include <stdio.h>
#include <stdlib.h>

typedef struct lista
{
    void* endereco;
    int cont;
    struct lista *prox;
}lista;

lista* t = NULL;

lista* Inserir(lista* t, void* x)
{
    if(t==NULL)
    {
        lista*aux=(lista*)malloc(sizeof(lista));
        aux->endereco=x;
        aux->prox=NULL;
        aux->cont=1;
        t=aux;
        return t;
    }
    else
    {
        t->prox=Inserir(t->prox,x);
        return t;
    }
}

lista* remover(lista* t, void* x){

    lista* aux;
    if(t==NULL)
    {
        return t;
    }
    else if(t->endereco!=x)
    {
        t->prox = remover(t->prox,x);
        return t;
    }
    else
    {
        aux = t;
        t = t->prox;
        free(aux);
        t = remover(t,x);
        return t;
    }
}

int buscaQuantidade(lista* t, void* x)
{
    if(t==NULL)
    {
        return -1;
    }
    else
    {
        if(t->endereco == x)
        {
            return t->cont;
        }
        else
        {
            return buscaQuantidade(t->prox,x);
        }
    }
}

void atualizarContador(lista* t, void* x, int valor)
{
    if(t==NULL)
    {
        return;
    }
    else
    {
        if(t->endereco == x)
        {
            t->cont = t->cont + valor;
        }
        else
        {
            atualizarContador(t->prox, x, valor);
        }
    }
}

void* malloc2(size_t size)
{
    void* x;

    x = malloc(size);
    t = Inserir(t, x);

    return x;
}

void* atribuir(void* x, void* y)
{
    atualizarContador(t, x, -1);
    atualizarContador(t, y, 1);

    if(buscaQuantidade(t, x) == 0)
    {
        t = remover(t, x);
        free(x);
    }
    return y;
}

void dump()
{
    lista* lista=t;
    if (t == NULL)
    {
        printf("A lista esta vazia!\n");
        return;
    }

    while (lista != NULL)
    {
        printf("Endereco:%d\t", lista->endereco);
        printf("Ponteiros:%d\n", lista->cont);
        lista = lista->prox;
    }
}

int main(int argc, const char * argv[])
{
    int *a;
    int *b;

    printf("Alocando primeiro inteiro:\n");
    b = (int*)malloc2(sizeof(int)); /*Chama uma void* que aloca um inteiro e retorna a lista com os endereços*/

    dump(); /*Funçao que printa a lista e o contador na tela*/

    printf("\nAlocando segundo inteiro:\n");

    a = (int*)malloc2(sizeof(int));

    dump();

    printf("\nAtribuindo segundo endereco no primeiro ponteiro:\n");

    b = atribuir(b, a);

    dump();

    printf("\nAtribuindo NULL para o primeiro ponteiro:\n");

    b = atribuir(b, NULL);

    dump();

    printf("\nAtribuindo NULL para o segundo ponteiro:\n");

    a= atribuir(a, NULL);

    dump();

    printf("\n");
}
