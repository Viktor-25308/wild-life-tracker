#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Дефиниция на структурата
typedef struct {
    char species[50];
    int count;
    char region[50];
} WildlifeRecord;

// Прототипи на функциите
void addRecord(WildlifeRecord db[], int *size);
void displayAll(WildlifeRecord db[], int size);
void searchSpecies(WildlifeRecord db[], int size);
void saveToFile(WildlifeRecord db[], int size);
int loadFromFile(WildlifeRecord db[]);

int main() {
    WildlifeRecord database[100]; 
    int count = loadFromFile(database); 
    int choice;

    do {
        printf("\n--- Wildlife Population Tracker ---\n");
        printf("1. Добави нов запис\n");
        printf("2. Покажи всички записи\n");
        printf("3. Търсене по вид\n");
        printf("4. Запиши и Изход\n");
        printf("Избор: ");
        if (scanf("%d", &choice) != 1) break;
        getchar(); 

        switch (choice) {
            case 1: addRecord(database, &count); break;
            case 2: displayAll(database, count); break;
            case 3: searchSpecies(database, count); break;
            case 4: saveToFile(database, count); printf("Данните са записани!\n"); break;
            default: printf("Невалиден избор!\n");
        }
    } while (choice != 4);

    return 0;
}

void addRecord(WildlifeRecord db[], int *size) {
    if (*size >= 100) {
        printf("Базата данни е пълна!\n");
        return;
    }
    printf("Вид животно: ");
    fgets(db[*size].species, 50, stdin);
    db[*size].species[strcspn(db[*size].species, "\n")] = 0;

    printf("Брой: ");
    scanf("%d", &db[*size].count);
    getchar();

    printf("Регион: ");
    fgets(db[*size].region, 50, stdin);
    db[*size].region[strcspn(db[*size].region, "\n")] = 0;

    (*size)++;
    printf("Успешно добавен запис.\n");
}

void displayAll(WildlifeRecord db[], int size) {
    if (size == 0) { printf("\nНяма данни.\n"); return; }
    printf("\n%-20s %-10s %-20s\n", "Вид", "Брой", "Регион");
    printf("--------------------------------------------------\n");
    for (int i = 0; i < size; i++) {
        printf("%-20s %-10d %-20s\n", db[i].species, db[i].count, db[i].region);
    }
}

void searchSpecies(WildlifeRecord db[], int size) {
    char query[50];
    printf("Търсене на вид: ");
    fgets(query, 50, stdin);
    query[strcspn(query, "\n")] = 0;
    
    int found = 0;
    for (int i = 0; i < size; i++) {
        if (strstr(db[i].species, query)) {
            printf("Намерено: %s | Брой: %d | Регион: %s\n", db[i].species, db[i].count, db[i].region);
            found = 1;
        }
    }
    if (!found) printf("Няма съвпадения.\n");
}

void saveToFile(WildlifeRecord db[], int size) {
    FILE *file = fopen("data.txt", "w");
    if (!file) return;
    for (int i = 0; i < size; i++) {
        fprintf(file, "%s|%d|%s\n", db[i].species, db[i].count, db[i].region);
    }
    fclose(file);
}

int loadFromFile(WildlifeRecord db[]) {
    FILE *file = fopen("data.txt", "r");
    if (!file) return 0;
    int i = 0;
    while (i < 100 && fscanf(file, " %[^|]|%d|%[^\n]\n", db[i].species, &db[i].count, db[i].region) == 3) {
        i++;
    }
    fclose(file);
    return i;
}