#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ENTRY_LENGTH 1000
#define MAX_ENTRIES 1000

typedef struct {
    char description[MAX_ENTRY_LENGTH];
    float amount;
    char type; // 'e' for expense, 'i' for income
} Entry;

Entry entries[MAX_ENTRIES];
int entryCount = 0;

void addEntry() {
    if (entryCount >= MAX_ENTRIES) {
        printf("Cannot add more entries. Maximum limit reached.\n");
        return;
    }

    Entry newEntry;
    printf("Enter description: ");
    fgets(newEntry.description, MAX_ENTRY_LENGTH, stdin);
    newEntry.description[strcspn(newEntry.description, "\n")] = '\0'; // Remove newline character

    printf("Enter amount: ");
    scanf("%f", &newEntry.amount);
    getchar(); // Consume leftover newline

    printf("Enter type (e for expense, i for income): ");
    newEntry.type = getchar();
    getchar(); // Consume leftover newline

    entries[entryCount++] = newEntry;
    printf("Entry added successfully.\n");
}

void saveEntriesToFile() {
    FILE *file = fopen("finance_data.txt", "w");
    if (!file) {
        perror("Failed to open file");
        return;
    }

    for (int i = 0; i < entryCount; i++) {
        fprintf(file, "%s,%f,%c\n", entries[i].description, entries[i].amount, entries[i].type);
    }

    fclose(file);
    printf("Data saved to file.\n");
}

void loadEntriesFromFile() {
    FILE *file = fopen("finance_data.txt", "r");
    if (!file) {
        perror("Failed to open file");
        return;
    }

    while (fscanf(file, "%[^,],%f,%c\n", entries[entryCount].description, &entries[entryCount].amount, &entries[entryCount].type) != EOF) 
    {
        entryCount++;
        if (entryCount >= MAX_ENTRIES) {
            printf("Maximum entry limit reached while loading.\n");
            break;
        }
    }

    fclose(file);
}

void displaySummary() {
    float totalIncome = 0.0;
    float totalExpense = 0.0;

    for (int i = 0; i < entryCount; i++) {
        if (entries[i].type == 'i') {
            totalIncome += entries[i].amount;
        } else if (entries[i].type == 'e') {
            totalExpense += entries[i].amount;
        }
    }

    printf("Total Income: $%.2f\n", totalIncome);
    printf("Total Expenses: $%.2f\n", totalExpense);
    printf("Net Balance: $%.2f\n", totalIncome - totalExpense);
}

int main() {
    int choice;

    loadEntriesFromFile();

    while (1) {
        printf("\nPersonal Finance Tracker\n");
        printf("1. Add Entry\n");
        printf("2. Display Summary\n");
        printf("3. Save and Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume leftover newline

        switch (choice) {
            case 1:
                addEntry();
                break;
            case 2:
                displaySummary();
                break;
            case 3:
                saveEntriesToFile();
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
