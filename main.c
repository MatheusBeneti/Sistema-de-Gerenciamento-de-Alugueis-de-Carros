#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>
#define CUSTOMER_NAME_SIZE 30
#define CAR_MODEL_SIZE 30

typedef struct car
{
    char modelo[CUSTOMER_NAME_SIZE];
    int licensePlate;
    struct car* prox;
    struct car* prev;
} Cars;

typedef struct customer
{
    char name[CAR_MODEL_SIZE];
    int cpf;
    struct customer* prox;
    struct customer* prev;
} Customer;

typedef struct rentedCars
{
    Customer *customer;
    Cars *car;
    struct rentedCars* prox;
    struct rentedCars* prev;
} RentedCars;

int showMenu()
{
    int option;
    printf("-- Clientes --\n 1-Incluir\n 2-Alterar\n 3-Consultar\n 4-Deletar\n-- Veículo --\n 5-Incluir\n 6-Alterar\n 7-Consultar\n 8-Deletar\n-- Aluguéis--\n 9-Incluir\n 10-Alterar\n 11-Consultar\n 12-Deletar\n\n0-Encerrar Programa\n\n");
    scanf("%d", &option);
    system("cls");
    return option;
}

Customer* customerExistsByCPF(Customer* customerList, int targetCPF)
{
    Customer* currentCustomer = customerList;

    while (currentCustomer != NULL)
    {

        if (currentCustomer->cpf == targetCPF)
        {
            return currentCustomer;
        }
        currentCustomer = currentCustomer->prox;
    }

    return NULL;
}

Cars* carExistsByLicensePlate(Cars* carList, int targetLicensePlate)
{
    Cars* currentCar = carList;

    while (currentCar != NULL)
    {
        if (currentCar->licensePlate == targetLicensePlate)
        {
            return currentCar;
        }
        currentCar = currentCar->prox;
    }

    return NULL;
}

void getCustomerData(char *newName, int *newCpf)
{
    printf("\nInforme os dados do cliente:\n");
    printf("Nome: ");
    getchar();
    fgets(newName, CUSTOMER_NAME_SIZE, stdin);
    printf("CPF: ");
    scanf("%d", newCpf);
}

int addCustomer(Customer **head)
{
    char newName[CUSTOMER_NAME_SIZE];
    int newCpf;

    getCustomerData(newName, &newCpf);

    if (customerExistsByCPF(*head, newCpf) != NULL)
    {
        printf("\nCliente com o mesmo CPF já cadastrado. A adição não é permitida.\n");
        return 0;
    }

    Customer *newCustomer = (Customer*)malloc(sizeof(Customer));
    if (newCustomer == NULL)
    {
        return 0;
    }

    newCustomer->cpf = newCpf;
    strcpy(newCustomer->name, newName);
    newCustomer->prev = NULL;

    if (*head == NULL)
    {
        newCustomer->prox = NULL;
    }
    else
    {
        newCustomer->prox = *head;
        (*head)->prev = newCustomer;
    }
    *head = newCustomer;
    system("cls");
    return 1;
}

void printCustomerList(const Customer* head)
{
    const Customer* current = head;

    if (current == NULL)
    {
        printf("Lista de clientes vazia!\n\n");
        return;
    }

    printf("-- Lista de Clientes --\n");

    while (current != NULL)
    {
        printf("Nome: %s\n", current->name);
        printf("CPF: %d\n", current->cpf);
        printf("\n");

        current = current->prox;
    }
}

void getCarData(char *newModel, int *newLicensePlate)
{
    printf("\nInforme os dados do carro:\n");
    printf("Modelo: ");
    getchar();
    fgets(newModel, CAR_MODEL_SIZE, stdin);
    printf("Placa: ");
    scanf("%d", newLicensePlate);
}

int addCar(Cars **head)
{
    char newModel[CAR_MODEL_SIZE];
    int newLicensePlate;

    getCarData(newModel, &newLicensePlate);

    if (carExistsByLicensePlate(*head, newLicensePlate) != NULL)
    {
        printf("\nCarro com a mesma placa já cadastrado. A adição não é permitida.\n");
        return 0;
    }

    system("cls");

    Cars *newCar = (Cars*)malloc(sizeof(Cars));
    if (newCar == NULL)
    {
        return 0;
    }

    newCar->licensePlate = newLicensePlate;
    strcpy(newCar->modelo, newModel);
    newCar->prox = NULL;

    if (*head == NULL)
    {
        newCar->prev = NULL;
        *head = newCar;
    }
    else
    {
        newCar->prev = NULL;
        newCar->prox = *head;
        (*head)->prev = newCar;
        *head = newCar;
    }

    return 1;
}

void printCars(const Cars* head)
{
    const Cars* current = head;

    if (current == NULL)
    {
        printf("Lista de carros vazia!\n\n");
        return;
    }

    printf("-- Lista de Carros --\n");

    while (current != NULL)
    {
        printf("Modelo: %s\n", current->modelo);
        printf("Placa: %d\n", current->licensePlate);
        printf("\n");

        current = current->prox;
    }
}

void getRentedCarData(int *cpf, int *licencePlate)
{
    printf("\nInforme os dados do aluguel:\n");
    printf("CPF do cliente: ");
    scanf("%d", cpf);
    printf("Placa do carro: ");
    scanf("%d", licencePlate);
}

bool isExistData(Customer *customerHead, Cars *carsHead, int targetCPF, int targetLicensePlate)
{
    Customer* customerExists = customerExistsByCPF(customerHead, targetCPF);
    Cars* carExists = carExistsByLicensePlate(carsHead, targetLicensePlate);

    return customerExists != NULL && carExists != NULL;
}

Customer* allocateAndInitializeCustomerData(const char* name, int cpf)
{
    Customer* newCustomer = (Customer*)malloc(sizeof(Customer));
    if (newCustomer == NULL)
    {
        return NULL;
    }

    strncpy(newCustomer->name, name, CUSTOMER_NAME_SIZE);
    newCustomer->cpf = cpf;
    newCustomer->prox = NULL;
    newCustomer->prev = NULL;

    return newCustomer;
}

Cars* allocateAndInitializeCarData(const char* model, int licensePlate)
{
    Cars* newCar = (Cars*)malloc(sizeof(Cars));
    if (newCar == NULL)
    {
        return NULL;
    }

    strncpy(newCar->modelo, model, CAR_MODEL_SIZE);
    newCar->licensePlate = licensePlate;
    newCar->prox = NULL;
    newCar->prev = NULL;

    return newCar;
}

const char* findCustomerNameByCPF(const Customer* head, int cpfToFind)
{
    const Customer* current = head;

    while (current != NULL)
    {
        if (current->cpf == cpfToFind)
        {
            return current->name;
        }
        current = current->prox;
    }

    return NULL;
}

const char* findCarModelByLicensePlate(const Cars* head, int licensePlateToFind)
{
    const Cars* current = head;

    while (current != NULL)
    {
        if (current->licensePlate == licensePlateToFind)
        {
            return current->modelo;
        }
        current = current->prox;
    }

    return NULL;
}

void addRentedCar(RentedCars **rentedCarsHead, Cars *carsHead, Customer *customerHead)
{
    int cpf, licensePlate;

    getRentedCarData(&cpf, &licensePlate);

    bool dataExists = isExistData(customerHead, carsHead, cpf, licensePlate);

    if (dataExists)
    {
        RentedCars *info = (RentedCars*)malloc(sizeof(RentedCars));
        if (info == NULL)
        {
            printf("Falha na memória.\n");
            return;
        }

        info->prev = NULL;
        info->prox = NULL;

        info->customer = allocateAndInitializeCustomerData(findCustomerNameByCPF(customerHead, cpf), cpf);
        info->car = allocateAndInitializeCarData(findCarModelByLicensePlate(carsHead, licensePlate), licensePlate);

        if (*rentedCarsHead == NULL)
        {
            *rentedCarsHead = info;
        }
        else
        {
            RentedCars *current = *rentedCarsHead;
            while (current->prox != NULL)
            {
                current = current->prox;
            }
            current->prox = info;
            info->prev = current;
        }
        printf("Dado adicionado!\n");
    }
    else
    {
        printf("CPF ou Placa não existe, cadastre primeiro.\n");
    }
}

void printRentedCar(const RentedCars *rentedCar)
{
    if (rentedCar == NULL)
    {
        printf("Rented Car is NULL\n");
        return;
    }

    printf("Customer Name: %s\n", rentedCar->customer->name);
    printf("Customer CPF: %d\n", rentedCar->customer->cpf);
    printf("Car Model: %s\n", rentedCar->car->modelo);
    printf("Car License Plate: %d\n", rentedCar->car->licensePlate);
    printf("\n");
}

void printAllRentedCars(const RentedCars* head)
{
    const RentedCars* current = head;

    if (current == NULL)
    {
        printf("Lista de carros alugados vazia!\n\n");
        return;
    }

    printf("-- Lista de Carros Alugados --\n");

    while (current != NULL)
    {
        printf("Cliente: %s (CPF: %d)\n", current->customer->name, current->customer->cpf);
        printf("Carro: %s (Placa: %d)\n", current->car->modelo, current->car->licensePlate);
        printf("\n");

        current = current->prox;
    }
}

void deleteCustomer(Customer **head, int cpf)
{
    system("cls");
    Customer *current = *head;
    while (current != NULL)
    {
        if (current->cpf == cpf)
        {
            if (current->prev != NULL)
            {
                current->prev->prox = current->prox;
            }
            if (current->prox != NULL)
            {
                current->prox->prev = current->prev;
            }
            if (current == *head)
            {
                *head = current->prox;
            }
            free(current);
            printf("\nCliente removido com sucesso!\n");
            return;
        }
        current = current->prox;
    }
    printf("\nCPF não encontrado.\n");
}

void deleteCar(Cars **head, int licensePlate)
{
    system("cls");
    Cars *current = *head;
    while (current != NULL)
    {
        if (current->licensePlate == licensePlate)
        {
            if (current->prev != NULL)
            {
                current->prev->prox = current->prox;
            }
            if (current->prox != NULL)
            {
                current->prox->prev = current->prev;
            }
            if (current == *head)
            {
                *head = current->prox;
            }
            free(current);
            printf("\nCarro removido com sucesso!\n");
            return;
        }
        current = current->prox;
    }
    printf("\nPlaca do carro não encontrada!\n");
}

void deleteRentedCar(RentedCars **head, int cpf, int licensePlate)
{
    system("cls");
    RentedCars *current = *head;

    while (current != NULL)
    {
        if (current->customer->cpf == cpf && current->car->licensePlate == licensePlate)
        {
            if (current->prev != NULL)
            {
                current->prev->prox = current->prox;
            }
            if (current->prox != NULL)
            {
                current->prox->prev = current->prev;
            }
            if (current == *head)
            {
                *head = current->prox;
            }

            free(current->customer);
            free(current->car);
            free(current);

            printf("\nAluguel removido com sucesso!\n");
            return;
        }
        current = current->prox;
    }

    printf("\nAluguel não encontrado.\n");
}

bool isCustomerInRentedCars(const RentedCars *head, int targetCPF)
{
    const RentedCars *current = head;

    while (current != NULL)
    {
        if (current->customer->cpf == targetCPF)
        {
            return true;
        }
        current = current->prox;
    }

    return false;
}

bool isCarInRentedCars(const RentedCars* head, int targetLicensePlate)
{
    const RentedCars* current = head;

    while (current != NULL)
    {
        if (current->car->licensePlate == targetLicensePlate)
        {
            return true;
        }
        current = current->prox;
    }

    return false;
}

void changeCustomer(Customer **customerHead)
{
    char newName[CUSTOMER_NAME_SIZE];
    int newCPF, targetCPF;

    printf("\nDigite o CPF do cliente que deseja alterar\n");
    scanf("%d", &targetCPF);

    Customer *current = *customerHead;

    while (current)
    {
        if (current->cpf == targetCPF)
        {
            printf("\nDigite os novos dados\n");
            getCustomerData(newName, &newCPF);

            strcpy(current->name, newName);
            current->cpf = newCPF;

            return;
        }
        current = current->prox;
    }
    printf("\nCPF não encontrado\n\n");

    return;
}

void changeCar(Cars **carsHead)
{
    char newModel[CAR_MODEL_SIZE];
    int newLicensePlate, targetLicensePlate;

    printf("\nDigite a placa do carro que deseja alterar\n");
    scanf("%d", &targetLicensePlate);

    Cars *current = *carsHead;

    while (current)
    {
        if (current->licensePlate == targetLicensePlate)
        {
            printf("\nDigite os novos dados\n");
            getCarData(newModel, &newLicensePlate);

            strcpy(current->modelo, newModel);
            current->licensePlate = newLicensePlate;

            return;
        }
        current = current->prox;
    }
    printf("\nPlaca do carro não encontrada\n\n");

    return;
}

void removeAndShift(char *str) {
    int len = strlen(str);
    int i, j;

    for (i = 0; i < len; i++) {
        if (str[i] == '\n') {

            for (j = i; j < len; j++) {
                str[j] = str[j + 1];
            }
            len--;
            i--;
        }
    }
}

void changeRentedCar(RentedCars **rentedCarsHead, Cars **carsHead, Customer **customerHead)
{
    int newCPF, newLicensePlate, targetCPF, targetLicensePlate;

    printf("\nDigite o CPF do cliente do carro alugado que deseja alterar\n");
    scanf("%d", &targetCPF);
    printf("\nDigite a placa do carro alugado que deseja alterar\n");
    scanf("%d", &targetLicensePlate);

    RentedCars *current = *rentedCarsHead;

    while (current)
    {
        if (current->customer->cpf == targetCPF && current->car->licensePlate == targetLicensePlate)
        {
            printf("\nDigite os novos dados\n");
            getRentedCarData(&newCPF, &newLicensePlate);

            Customer *existingCustomer = customerExistsByCPF(customerHead, newCPF);
            Cars *existingCar = carExistsByLicensePlate(carsHead, newLicensePlate);

            if (existingCustomer != NULL && existingCar != NULL)
            {
                strcpy(current->customer->name, existingCustomer->name);
                current->customer->cpf = existingCustomer->cpf;

                strcpy(current->car->modelo, existingCar->modelo);
                current->car->licensePlate = existingCar->licensePlate;

                printf("Alteração realizada com sucesso!\n");
            }
            else
            {
                printf("A alteração não pode ser feita pois o cliente ou o carro não existe no banco.\n\n");
                return;
            }

            return;
        }
        current = current->prox;
    }
    printf("Aluguel não encontrado\n");
}

void salvarClientesEmArquivo(const Customer* lista, const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "w");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    const Customer* clienteAtual = lista;

    while (clienteAtual != NULL) {

        char sentence[100];


        snprintf(sentence, sizeof(sentence), "Nome: %s, CPF: %d", clienteAtual->name, clienteAtual->cpf);

        removeAndShift(sentence);


        fprintf(arquivo, "%s\n", sentence);

        clienteAtual = clienteAtual->prox;
    }

    fclose(arquivo);
}

void salvarListaEmArquivo(const Cars* lista, const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "w");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    const Cars* carroAtual = lista;

    while (carroAtual != NULL) {


        char sentence[100];

        snprintf(sentence, sizeof(sentence), "Modelo: %s, Placa: %d", carroAtual->modelo, carroAtual->licensePlate);

        removeAndShift(sentence);


        fprintf(arquivo, "%s\n", sentence);


        carroAtual = carroAtual->prox;
    }

    fclose(arquivo);
}

void salvarRentedCarsEmArquivo(const RentedCars* lista, const char* nomeArquivo)
{
    FILE* arquivo = fopen(nomeArquivo, "w");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    const RentedCars* aluguelAtual = lista;

    while (aluguelAtual != NULL)
    {
        // Crie uma string para armazenar a linha
        char sentence[100];

        // Use snprintf para formatar a linha
        snprintf(sentence, sizeof(sentence), "Cliente: Nome: %s, CPF: %d | Carro: Modelo: %s, Placa: %d",
                 aluguelAtual->customer->name, aluguelAtual->customer->cpf,
                 aluguelAtual->car->modelo, aluguelAtual->car->licensePlate);

        removeAndShift(sentence);

        // Escreva a linha no arquivo
        fprintf(arquivo, "%s\n", sentence);

        aluguelAtual = aluguelAtual->prox;
    }

    fclose(arquivo);
}

Customer* carregarClientesDeArquivo(const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        return NULL;
    }

    Customer* head = NULL;
    char buffer[200];

    while (fgets(buffer, sizeof(buffer), arquivo) != NULL) {
        Customer* novoCliente = (Customer*)malloc(sizeof(Customer));

        if (novoCliente == NULL) {
            printf("Erro de alocação de memória.\n");
            exit(EXIT_FAILURE);
        }

        // Leitura do nome e do CPF na mesma linha
        if (sscanf(buffer, "Nome: %29[^,], CPF: %d", novoCliente->name, &novoCliente->cpf) == 2) {
            // Configuração do novo cliente
            novoCliente->prox = head;
            novoCliente->prev = NULL;

            // Atualiza a lista encadeada
            if (head != NULL) {
                head->prev = novoCliente;
            }

            head = novoCliente;

            // Mensagem de depuração
            printf("Cliente carregado: Nome: %s, CPF: %d\n", novoCliente->name, novoCliente->cpf);
        } else {
            // Mensagem de depuração
            printf("Falha ao ler linha do arquivo: %s\n", buffer);
            free(novoCliente); // Libera a memória alocada se a leitura falhar
        }
    }

    fclose(arquivo);
    return head;
}

Cars* carregarCarrosDeArquivo(const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        return NULL;
    }

    Cars* head = NULL;
    char buffer[200];

    while (fgets(buffer, sizeof(buffer), arquivo) != NULL) {
        Cars* novoCarro = (Cars*)malloc(sizeof(Cars));

        if (novoCarro == NULL) {
            printf("Erro de alocação de memória.\n");
            exit(EXIT_FAILURE);
        }


        if (sscanf(buffer, "Modelo: %29[^,], Placa: %d", novoCarro->modelo, &novoCarro->licensePlate) == 2) {
            // Configuração do novo carro
            novoCarro->prox = head;
            novoCarro->prev = NULL;

            // Atualiza a lista encadeada
            if (head != NULL) {
                head->prev = novoCarro;
            }

            head = novoCarro;

            // Mensagem de depuração
            printf("Carro carregado: Modelo: %s, Placa: %d\n", novoCarro->modelo, novoCarro->licensePlate);
        } else {
            // Mensagem de depuração
            printf("Falha ao ler linha do arquivo: %s\n", buffer);
            free(novoCarro); // Libera a memória alocada se a leitura falhar
        }
    }

    fclose(arquivo);
    return head;
}

RentedCars* carregarAlugueisDeArquivo(const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        return NULL;
    }

    RentedCars* head = NULL;
    char buffer[200];

    while (fgets(buffer, sizeof(buffer), arquivo) != NULL) {
        RentedCars* novoAluguel = (RentedCars*)malloc(sizeof(RentedCars));

        if (novoAluguel == NULL) {
            printf("Erro de alocação de memória.\n");
            exit(EXIT_FAILURE);
        }


        novoAluguel->customer = (Customer*)malloc(sizeof(Customer));
        novoAluguel->car = (Cars*)malloc(sizeof(Cars));

        if (novoAluguel->customer == NULL || novoAluguel->car == NULL) {
            printf("Erro de alocação de memória para cliente ou carro.\n");
            exit(EXIT_FAILURE);
        }


        int result = sscanf(buffer, "Cliente: Nome: %29[^,], CPF: %d | Carro: Modelo: %29[^,], Placa: %d",
                            novoAluguel->customer->name, &novoAluguel->customer->cpf,
                            novoAluguel->car->modelo, &novoAluguel->car->licensePlate);

        if (result == 4) {

            novoAluguel->prox = head;
            novoAluguel->prev = NULL;


            if (head != NULL) {
                head->prev = novoAluguel;
            }

            head = novoAluguel;


            printf("Aluguel carregado: Cliente: Nome: %s, CPF: %d | Carro: Modelo: %s, Placa: %d\n",
                   novoAluguel->customer->name, novoAluguel->customer->cpf,
                   novoAluguel->car->modelo, novoAluguel->car->licensePlate);
        } else {
            printf("Falha ao ler linha do arquivo: %s\n", buffer);
            free(novoAluguel->customer);
            free(novoAluguel->car);
            free(novoAluguel);
        }
    }

    fclose(arquivo);
    return head;
}

int main()
{
    setlocale(LC_ALL, "pt-BR");
    Cars *carsHead = carregarCarrosDeArquivo("Cars.txt");
    Customer *customerHead = carregarClientesDeArquivo("clientes.txt");
    RentedCars *rentedCarsHead = carregarAlugueisDeArquivo("rentedCars.txt");
    int chosenOption = 0;
    int cpfToDelete;
    int licensePlateToDelete;


    do
    {
        chosenOption = showMenu();

        switch (chosenOption)
        {
        case 1:
            if(addCustomer(&customerHead))
            {
                printf("Novo cliente adicionado!\n\n");
                salvarClientesEmArquivo(customerHead, "clientes.txt");
            }
            else
            {
                printf("Erro ao adicionar novo cliente.\n\n");
            }
            break;
        case 2:
            changeCustomer(&customerHead);
            salvarClientesEmArquivo(customerHead, "clientes.txt");
            break;
        case 3:
            printCustomerList(customerHead);
            break;
        case 4:
            if (customerHead != NULL)
            {
                printf("Digite o CPF do cliente a ser deletado: ");
                scanf("%d", &cpfToDelete);

                if (isCustomerInRentedCars(rentedCarsHead, cpfToDelete))
                {
                    printf("Esse dado não pode ser deletado pois está vinculado a um aluguel.\n");
                }
                else
                {
                    deleteCustomer(&customerHead, cpfToDelete);
                    salvarClientesEmArquivo(customerHead, "clientes.txt");
                }
            }
            else
            {
                printf("Lista Vazia.\n\n");
            }
            break;
        case 5:
            if(addCar(&carsHead))
            {
                printf("Novo carro adicionado!\n\n");
                salvarListaEmArquivo(carsHead, "cars.txt");
            }
            else
            {
                printf("Erro ao adicionar novo carro.\n\n");
            }
            break;
        case 6:
            changeCar(&carsHead);
            salvarListaEmArquivo(carsHead, "cars.txt");
            break;
        case 7:
            if(carsHead != NULL)
            {
                printCars(carsHead);
            }
            else
            {
                printf("Lista Vazia!\n\n");
            }
            break;
        case 8:

            if(carsHead != NULL)
            {
                printf("Digite a placa do carro a ser deletado: ");
                scanf("%d", &licensePlateToDelete);

                if (isCarInRentedCars(rentedCarsHead, licensePlateToDelete))
                {
                    printf("Esse dado não pode ser deletado pois está vinculado a um aluguel.\n");
                }
                else
                {
                    deleteCar(&carsHead, licensePlateToDelete);
                    salvarListaEmArquivo(carsHead, "cars.txt");
                }
            }
            else
            {
                printf("A lista está vazia!\n\n");
            }
            break;
        case 9:
            addRentedCar(&rentedCarsHead, carsHead, customerHead);
            salvarRentedCarsEmArquivo(rentedCarsHead, "rentedCars.txt");
            break;
        case 10:
            changeRentedCar(&rentedCarsHead, carsHead, customerHead);
            salvarRentedCarsEmArquivo(rentedCarsHead, "rentedCars.txt");
            break;
        case 11:
            printAllRentedCars(rentedCarsHead);
            break;
        case 12:
            printf("Digite o CPF do cliente: ");
            scanf("%d", &cpfToDelete);
            printf("Digite a placa do carro: ");
            scanf("%d", &licensePlateToDelete);
            deleteRentedCar(&rentedCarsHead, cpfToDelete, licensePlateToDelete);
            salvarRentedCarsEmArquivo(rentedCarsHead, "rentedCars.txt");
            break;
        }
    }
    while (chosenOption != 0);

    return 0;
}
