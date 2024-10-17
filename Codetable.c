#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SYMBOL_LENGTH 5
#define NAME_LENGTH 20
#define MAX_ELEMENTS 118

typedef struct Element {
    int atomic_number;
    char symbol[SYMBOL_LENGTH];
    char name[NAME_LENGTH];
    float atomic_mass;
    struct Element* next;
    struct Element* prev;
} Element;

typedef struct {
    Element* head;
    int count;
} PeriodicTable;

Element* createElement(int atomic_number, const char* symbol, const char* name, float atomic_mass) {
    Element* newElement = (Element*)malloc(sizeof(Element));
    if (newElement != NULL) {
        newElement->atomic_number = atomic_number;
        strncpy(newElement->symbol, symbol, SYMBOL_LENGTH - 1);
        newElement->symbol[SYMBOL_LENGTH - 1] = '\0';
        strncpy(newElement->name, name, NAME_LENGTH - 1);
        newElement->name[NAME_LENGTH - 1] = '\0';
        newElement->atomic_mass = atomic_mass;
        newElement->next = NULL;
        newElement->prev = NULL;
    }
    return newElement;
}

void initializePeriodicTable(PeriodicTable* pt) {
    pt->head = NULL;
    pt->count = 0;
}

void insertElement(PeriodicTable* pt, int atomic_number, const char* symbol, const char* name, float atomic_mass) {
    Element* newElement = createElement(atomic_number, symbol, name, atomic_mass);
    if (newElement == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }
    if (pt->head == NULL) {
        pt->head = newElement;
    } else {
        Element* temp = pt->head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newElement;
        newElement->prev = temp;
    }
    pt->count++;
    printf("Element '%s' added successfully.\n", name);
}

void deleteElement(PeriodicTable* pt, int atomic_number) {
    Element* current = pt->head;
    while (current != NULL) {
        if (current->atomic_number == atomic_number) {
            if (current->prev != NULL) {
                current->prev->next = current->next;
            } else {
                pt->head = current->next;
            }
            if (current->next != NULL) {
                current->next->prev = current->prev;
            }
            free(current);
            pt->count--;
            printf("Element with atomic number %d deleted successfully.\n", atomic_number);
            return;
        }
        current = current->next;
    }
    printf("Element with atomic number %d not found.\n", atomic_number);
}

void displayPeriodicTable(const PeriodicTable* pt) {
    if (pt->head == NULL) {
        printf("The periodic table is currently empty.\n");
        return;
    }
    
    Element* current = pt->head;
    printf("Periodic Table:\n");
    printf("Atomic Number\tSymbol\tName\t\tAtomic Mass\n");
    printf("-------------------------------------------------\n");
    while (current != NULL) {
        printf("%d\t\t%s\t%s\t\t%.2f\n", current->atomic_number, current->symbol, current->name, current->atomic_mass);
        current = current->next;
    }
    printf("\n");
}

Element* searchElement(const PeriodicTable* pt, int atomic_number) {
    Element* current = pt->head;
    while (current != NULL) {
        if (current->atomic_number == atomic_number) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void freePeriodicTable(PeriodicTable* pt) {
    Element* current = pt->head;
    while (current != NULL) {
        Element* temp = current;
        current = current->next;
        free(temp);
    }
    pt->head = NULL;
    pt->count = 0;
}

int main() {
    PeriodicTable pt;
    initializePeriodicTable(&pt);
    int choice;
    int atomic_number;
    char symbol[SYMBOL_LENGTH];
    char name[NAME_LENGTH];
    float atomic_mass;

    do {
        printf("Periodic Table Management System\n");
        printf("1. Add Element\n");
        printf("2. Display Elements\n");
        printf("3. Search Element\n");
        printf("4. Delete Element\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter atomic number: ");
                if (scanf("%d", &atomic_number) != 1 || atomic_number <= 0 || atomic_number > MAX_ELEMENTS) {
                    printf("Invalid input. Enter a valid atomic number between 1 and %d.\n", MAX_ELEMENTS);
                    while (getchar() != '\n');
                    break;
                }
                printf("Enter element symbol: ");
                scanf("%s", symbol);
                printf("Enter element name: ");
                scanf("%s", name);
                printf("Enter atomic mass: ");
                if (scanf("%f", &atomic_mass) != 1) {
                    printf("Invalid input. Enter a valid atomic mass.\n");
                    while (getchar() != '\n');
                    break;
                }
                insertElement(&pt, atomic_number, symbol, name, atomic_mass);
                break;
            case 2:
                displayPeriodicTable(&pt);
                break;
            case 3:
                printf("Enter atomic number to search: ");
                if (scanf("%d", &atomic_number) != 1) {
                    printf("Invalid input. Enter a valid atomic number.\n");
                    while (getchar() != '\n');
                    break;
                }
                Element* foundElement = searchElement(&pt, atomic_number);
                if (foundElement != NULL) {
                    printf("Element found: %s (%s), Atomic Mass: %.2f\n", foundElement->name, foundElement->symbol, foundElement->atomic_mass);
                } else {
                    printf("Element with atomic number %d not found.\n", atomic_number);
                }
                break;
            case 4:
                printf("Enter atomic number to delete: ");
                if (scanf("%d", &atomic_number) != 1) {
                    printf("Invalid input. Enter a valid atomic number.\n");
                    while (getchar() != '\n');
                    break;
                }
                deleteElement(&pt, atomic_number);
                break;
            case 5:
                freePeriodicTable(&pt);
                printf("Program terminated.\n");
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 5.\n");
                break;
        }
    } while (choice != 5);

    return 0;
}
