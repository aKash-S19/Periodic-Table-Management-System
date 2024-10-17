#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define SYMBOL_LENGTH 5
#define NAME_LENGTH 20
#define MAX_ELEMENTS 118

// Structure to represent an element
typedef struct Element {
    int atomic_number;
    char symbol[SYMBOL_LENGTH];
    char name[NAME_LENGTH];
    float atomic_mass;
    struct Element* next;
    struct Element* prev;
} Element;

// Structure to represent the periodic table
typedef struct {
    Element* head;
    int count;
} PeriodicTable;

// Function to create a new element
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

// Function to initialize the periodic table
void initializePeriodicTable(PeriodicTable* pt) {
    pt->head = NULL;
    pt->count = 0;
}

// Function to insert an element into the periodic table
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
    printf("Element added successfully.\n");
}

// Function to delete an element from the periodic table
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
            printf("Element deleted successfully.\n");
            return;
        }
        current = current->next;
    }
    printf("Element not found.\n");
}

// Function to display all elements in the periodic table
void displayPeriodicTable(const PeriodicTable* pt) {
    Element* current = pt->head;
    printf("\nPeriodic Table:\n");
    printf("Atomic Number\tSymbol\tName\t\tAtomic Mass\n");
    printf("-------------------------------------------------\n");
    while (current != NULL) {
        printf("%d\t\t%s\t%s\t%.2f\n", current->atomic_number, current->symbol, current->name, current->atomic_mass);
        current = current->next;
    }
    printf("\n");
}

// Function to search for an element by atomic number
Element* searchElement(const PeriodicTable* pt, int atomic_number) {
    Element* current = pt->head;
    while (current != NULL) {
        if (current->atomic_number == atomic_number) {
            return current; // Element found
        }
        current = current->next;
    }
    return NULL; // Element not found
}

// Function to free the memory allocated for the periodic table
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
                    printf("Invalid atomic number. Please enter a valid number between 1 and %d.\n", MAX_ELEMENTS);
                    while (getchar() != '\n'); // clear the input buffer
                    break;
                }
                printf("Enter symbol: ");
                scanf("%s", symbol);
                printf("Enter name: ");
                scanf("%s", name);
                printf("Enter atomic mass: ");
                if (scanf("%f", &atomic_mass) != 1) {
                    printf("Invalid atomic mass. Please enter a valid number.\n");
                    while (getchar() != '\n'); // clear the input buffer
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
                    printf("Invalid atomic number. Please enter a valid number.\n");
                    while (getchar() != '\n'); // clear the input buffer
                    break;
                }
                Element* foundElement = searchElement(&pt, atomic_number);
                if (foundElement != NULL) {
                    printf("Element found: %s (%s), Atomic Mass: %.2f\n", foundElement->name, foundElement->symbol, foundElement->atomic_mass);
                } else {
                    printf("Element not found.\n");
                }
                break;
            case 4:
                printf("Enter atomic number to delete: ");
                if (scanf("%d", &atomic_number) != 1) {
                    printf("Invalid atomic number. Please enter a valid number.\n");
                    while (getchar() != '\n'); // clear the input buffer
                    break;
                }
                deleteElement(&pt, atomic_number);
                break;
            case 5:
                printf("Exiting the program.\n");
                freePeriodicTable(&pt);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 5);

    return 0;
}
