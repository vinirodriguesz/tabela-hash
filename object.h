#define new(Type) new_##Type()

typedef struct Node {
    void* dado;
    int tipo;
    struct Node* proximo;
    struct Node* anterior;
    void (*set)();
    void (*print)();
    void (*destroy)();
} Node;

typedef Node* Object;

void destruir_objeto(Object obj) {
    if (obj) {
        if (obj->dado) {
            free(obj->dado);
        }
        free(obj);
    }
}

Object new_Object() {
    Object obj = (Object)malloc(sizeof(Node));
    obj->proximo = NULL;
    obj->anterior = NULL;
    obj->dado = NULL;
    obj->tipo = 0;
    obj->destroy = destruir_objeto;
    return obj;
}

void imprimir_objeto(Object obj) {
    if (obj && obj->print) {
        obj->print(obj);
    }
}

