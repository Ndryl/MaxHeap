#include "Metodos.h"
Aviao contructorAeronave(char identificador[100], double Combustivel, int tipo, int emergencia, int previsao){
    Aviao aeronave;
    strcpy(aeronave.identificador, identificador);
    aeronave.Combustivel = Combustivel;
    aeronave.tipo = tipo;
    aeronave.emergencia = emergencia;
    aeronave.previsao = previsao;
    aeronave.prioridade = ((1000 - Combustivel) + (1440 - previsao) + 500*tipo + 5000*emergencia);
    return aeronave;
}
void informacaoAeronave(Aviao aeronave){
    printf("Identificador: %s \n", aeronave.identificador);
    printf("Combustivel: %2.f \n", aeronave.Combustivel);
    printf("Tipo: %d \n", aeronave.tipo);
    printf("Emergencia: %d \n", aeronave.emergencia);
    printf("Previsao: %d \n", aeronave.previsao);
    printf("Prioridade: %2.f \n", aeronave.prioridade);
}
Aviao getAviao(Aviao* aeronaves, int indice){
    if(indice > sizeof(aeronaves)){
        printf("Este índice não existe\n");
    }
    for(int i = 0; i < sizeof(aeronaves); i++){
        if(indice == i){
            return aeronaves[i];
        }
    }
}
heap* criaHeap(int capacity, Aviao* aeronaves){
    heap* h = (heap*)malloc(sizeof(heap));
    if(h == NULL){
        printf("Erro ao alocar memória na heap");
        return NULL;
    }
    h->size = 0;
    h->capacity = capacity;

    h->data = (Aviao*)malloc(capacity * sizeof(Aviao));
    if(h->data == NULL){
        printf("Erro ao alocar memória no array data");
        return NULL;
    }
    int i;
    for(i = 0; i < capacity; i++){
        h->data[i] = aeronaves[i];
    }
    h->size = i;
    i = (h->size -2) / 2;
    while(i>=0){
        maxHeapify(h, i);
        i--;
    }
    return h;
}
//
void maxHeapify(heap* h, int index)
{
	int left = index * 2 + 1;
    int rigth = index*2 + 2;
    int max = index;

    if(left >= h->size || left < 0){
        left =  -1;
    }
    if(rigth >= h->size || left < 0){
        rigth =  -1;
    }
    if (left != -1 && h->data[left].prioridade > h->data[max].prioridade){
        max = left;
    }
    if (rigth != -1 && h->data[rigth].prioridade > h->data[max].prioridade){
        max = rigth;
    }
 
    // Swapping the nodes
    if (max != index) {
        Aviao temp = h->data[max];
        h->data[max] = h->data[index];
        h->data[index] = temp;
 
        // recursively calling for their child elements
        // to maintain max heap
        maxHeapify(h, max);
    }
    
}
// Defining maxHeapify_bottom_up function
void insertHelper(heap* h, int index)
{

	// Store parent of element at index
	// in parent variable
	int parent = (index - 1) / 2;

	if (h->data[parent].prioridade < h->data[index].prioridade) {
		// Swapping when child is smaller
		// than parent element
		Aviao temp = h->data[parent];
		h->data[parent] = h->data[index];
		h->data[index] = temp;

		// Recursively calling maxHeapify_bottom_up
		insertHelper(h, parent);
	}
}

void insert(heap* h, Aviao data) {
    if (h->size >= h->capacity) {
        // Dobra a capacidade
        h->capacity *= 2;
        Aviao* new_data = (Aviao*)realloc(h->data, h->capacity * sizeof(Aviao));
        if (new_data == NULL) {
            printf("Erro ao redimensionar a heap.\n");
            return;
        }
        h->data = new_data;
    }
    // Insere o novo dado e ajusta o heap
    h->data[h->size] = data;
    insertHelper(h, h->size); // Reajusta para manter a propriedade da heap
    h->size++;
}

void deleteNode(heap* h){
    Aviao deleteItem;
    if(h-> size == 0){
        printf("Heap vazia");
        return;
    }
    deleteItem = h->data[0];
    h->data[0] = h->data[h->size - 1];
    h->size--;

    maxHeapify(h, 0);
}
void atualizaPrioridade(heap*h, char identificador[100]){
    for(int i = 0; i < h->size; i++){
        if(strcmp(h->data[i].identificador, identificador)){
            switch ((int)h->data[i].prioridade)
            {
            case 0:
                h->data[i].prioridade = 1;
                break;
            case 1:
                h->data[i].prioridade = 0;
                break;

            
            default:
                break;
            }
        }
    }
    maxHeapify(h, 0);
}
void exibirHeap(heap* h) {
    printf("Mostrando tabela:\n");
    for (int i = 0; i < h->size; i++) {
        printf("####POSIÇÃO %d####\n", i);
        informacaoAeronave(h->data[i]);
    }
}

void remover_quebra_linha(char* str) {
    if (str == NULL) return;
    size_t len = strlen(str);
    if (len > 0 && (str[len - 1] == '\n' || str[len - 1] == '\r')) {
        str[len - 1] = '\0';
    }
}

void carregar_voos(heap* h, char nome_arquivo[500]) {
    FILE* file = fopen(nome_arquivo, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    char buffer[1030];
    while (fgets(buffer, sizeof(buffer), file)) {
        remover_quebra_linha(buffer);
        char* token = strtok(buffer, ",");
        if (token == NULL) continue;

        char identificador[100];
        strcpy(identificador, token);

        token = strtok(NULL, ",");
        double combustivel = token ? atof(token) : 0;

        token = strtok(NULL, ",");
        int previsao = token ? atoi(token) : 0;

        token = strtok(NULL, ",");
        int tipo = token ? atoi(token) : 0;

        token = strtok(NULL, ",");
        int emergencia = token ? atoi(token) : 0;

        Aviao aeronave = contructorAeronave(identificador, combustivel, tipo, emergencia, previsao);
        insert(h, aeronave);
    }
    fclose(file);
}

void removeAeronave(heap* h, char identificador[100]) {
    for (int i = 0; i < h->size; i++) {
        if (strcmp(h->data[i].identificador, identificador) == 0) {
            h->data[i] = h->data[h->size - 1]; // Substitui pelo último elemento
            h->size--;
            maxHeapify(h, i); // Reajusta a heap
            return;
        }
    }
    printf("Esta aeronave não existe na lista\n");
}

void findAeronave(heap* h, char identificador[100]) {
    for (int i = 0; i < h->size; i++) {
        if (strcmp(h->data[i].identificador, identificador) == 0) {
            printf("####Aeronave com identificador %s####\n", identificador);
            informacaoAeronave(h->data[i]);
            return;
        }
    }
    printf("Esta aeronave não existe na lista\n");
}


