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

    // Função para manter a propriedade da heap máxima
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
    
        // Troca os nós
        if (max != index) {
            Aviao temp = h->data[max];
            h->data[max] = h->data[index];
            h->data[index] = temp;
    
            // Chamando recursivamente para os elementos filhos
            // para manter a propriedade da heap máxima
            maxHeapify(h, max);
        }
    }

    // Função auxiliar para ajustar a heap de baixo para cima
    void insertHelper(heap* h, int index)
    {
        // Armazena o pai do elemento no índice
        // na variável parent
        int parent = (index - 1) / 2;

        if (h->data[parent].prioridade < h->data[index].prioridade) {
            // Troca quando o filho tem prioridade maior
            // que o pai
            Aviao temp = h->data[parent];
            h->data[parent] = h->data[index];
            h->data[index] = temp;

            // Chamando recursivamente insertHelper
            insertHelper(h, parent);
        }
    }

    // Insere um novo elemento na heap
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

        // Verifica se já existe uma aeronave com o mesmo identificador
        for (int i = 0; i < h->size; i++) {
            if (strcmp(h->data[i].identificador, data.identificador) == 0) {
                printf("Já existe aeronave com o código de registro %s\n", data.identificador);
                return; 
            }
        }

        // Insere o novo dado e ajusta a heap
        h->data[h->size] = data;
        insertHelper(h, h->size); // Reajusta para manter a propriedade da heap
        h->size++;
    }


    // Remove o nó de maior prioridade da heap
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

    // Atualiza a prioridade de uma aeronave com base no identificador
void atualizaPrioridade(heap* h, char identificador[100]) {
    for (int i = 0; i < h->size; i++) {
        if (strcmp(h->data[i].identificador, identificador) == 0) {
            // Inverte o valor de emergência
            h->data[i].emergencia = (h->data[i].emergencia == 1) ? 0 : 1;

            // Recalcula a prioridade com base na fórmula original
            h->data[i].prioridade =
                (1000 - h->data[i].Combustivel) +
                (1440 - h->data[i].previsao) +
                (500 * h->data[i].tipo) +
                (5000 * h->data[i].emergencia);

            // Reorganiza a heap para manter a propriedade de max-heap
            maxHeapify(h, i);
            insertHelper(h, i);

            printf("Prioridade da aeronave %s atualizada para %.2f após mudança de emergência para %d.\n",
                   identificador, h->data[i].prioridade, h->data[i].emergencia);
            return;
        }
    }
    printf("Aeronave com identificador %s não encontrada.\n", identificador);
}



    // Remove a quebra de linha de uma string, se presente
    void remover_quebra_linha(char* str) {
        if (str == NULL) return;
        size_t len = strlen(str);
        if (len > 0 && (str[len - 1] == '\n' || str[len - 1] == '\r')) {
            str[len - 1] = '\0';
        }
    }

    // Carrega os voos a partir de um arquivo e insere na heap
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

    // Remove uma aeronave com base no identificador
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

    // Busca e exibe uma aeronave com base no identificador
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
