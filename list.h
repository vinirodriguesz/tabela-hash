typedef struct StructLista {
    Object inicio;
    Object fim;
    int tamanho;
    void (*enqueue)();
    void (*push)();
    Object (*pop)();
    void (*print)();
    void (*clear)();
    void (*del)();
    Object (*get)();
} StructLista;
//Vini Rodriguesz
typedef StructLista* List;

void lista_print(List lista, void (*funcao_print)()) {
    if (!lista->inicio) return;
    Object atual = lista->inicio;
    int pos = 0;
    while (atual) {
        funcao_print(atual, pos);
        atual = atual->proximo;
        pos++;
    }
}

void lista_enqueue(List lista, Object novo) {
    if (!lista->inicio) {
        lista->inicio = novo;
        lista->fim = novo;
    } else {
        lista->fim->proximo = novo;
        novo->anterior = lista->fim;
        lista->fim = novo;
    }
    lista->tamanho++;
}

void lista_push(List lista, Object novo) {
    if (!lista->inicio) {
        lista->inicio = novo;
        lista->fim = novo;
    } else {
        lista->inicio->anterior = novo;
        novo->proximo = lista->inicio;
        lista->inicio = novo;
    }
    lista->tamanho++;
}

Object lista_pop(List lista) {
    if (!lista->inicio) return NULL;
    Object atual = lista->inicio;
    lista->inicio = atual->proximo;
    
    if (atual->proximo) {
        atual->proximo = NULL;
    }
    
    if (!lista->inicio) {
        lista->fim = NULL;
    } else {
        lista->inicio->anterior = NULL;
    }
    lista->tamanho--;
    return atual;
}

void lista_clear(List lista) {
    Object atual = lista->inicio;
    while (atual) {
        Object proximo_no = atual->proximo;
        if (atual->destroy) {
            atual->destroy(atual);
        }
        atual = proximo_no;
    }
    lista->inicio = NULL;
    lista->fim = NULL;
    lista->tamanho = 0;
}

Object lista_get(List lista, int pos) {
    if (!lista->inicio || pos < 0 || pos >= lista->tamanho) return NULL;
    Object atual = lista->inicio;
    for (int i = 0; i < pos; i++) {
        atual = atual->proximo;
    }
    return atual;
}

void lista_delete(List lista, int pos) {
    if (!lista->inicio || pos < 0 || pos >= lista->tamanho) return;
    Object atual = lista->inicio;
    
    for (int i = 0; i < pos; i++) {
        atual = atual->proximo;
    }
    
    if (lista->inicio == atual) {
        lista->inicio = atual->proximo;
        if (lista->inicio) {
            lista->inicio->anterior = NULL;
        } else {
            lista->fim = NULL;
        }
    } else if (lista->fim == atual) {
        lista->fim = atual->anterior;
        if (lista->fim) {
            lista->fim->proximo = NULL;
        } else {
            lista->inicio = NULL;
        }
    } else {
        atual->anterior->proximo = atual->proximo;
        atual->proximo->anterior = atual->anterior;
    }
    
    if (atual->destroy) {
        atual->destroy(atual);
    }
    lista->tamanho--;
}

List new_List() {
    List lista = (List)malloc(sizeof(StructLista));
    lista->inicio = NULL;
    lista->fim = NULL;
    lista->tamanho = 0;
    lista->enqueue = lista_enqueue;
    lista->push = lista_push;
    lista->print = lista_print;
    lista->pop = lista_pop;
    lista->clear = lista_clear;
    lista->get = lista_get;
    lista->del = lista_delete;
    return lista;
}
