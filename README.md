# Periodic-Table-Management-System
This Periodic Table Management System in C language implements using a doubly linked list. Users can add, display, search, and delete elements based on atomic number. It demonstrates dynamic memory allocation, linked list operations, and basic input validation. Perfect for learning C data structures.

**Key Features**

*Add Elements:* Allows the user to input a new element's atomic number, symbol, name, and atomic mass into the periodic table.

*Delete Elements:* Deletes an element based on its atomic number, with automatic re-linking of neighboring elements.

*Search Elements:* Search for an element by its atomic number and display its details.

*Display All Elements:* Lists all elements currently stored in the periodic table, displaying their atomic number, symbol, name, and atomic mass.

*Memory Management:* Dynamically allocates memory for each element and ensures proper cleanup when the program exits.

**Usages**

*Add Elements:* Users can input new elements by specifying their properties.

*Delete Elements:* Remove any element from the table by its atomic number.

*Search Elements:* Look up any element by atomic number to find its name, symbol, and atomic mass.

*Display Table:* Display all currently stored elements with their properties.

**Data Structures Used**

Doubly Linked List: The periodic table is implemented using a doubly linked list (Element structure). Each Element node contains the following:

atomic_number: The unique identifier for each element.

symbol: A string holding the chemical symbol of the element.

name: The element's name.

atomic_mass: The atomic mass of the element.

next and prev: Pointers to the next and previous elements in the list, allowing bi-directional traversal.
How to Run

**Compile the program using a C compiler:**

```bash
gcc periodic_table.c -o periodic_table

Run the compiled program:
bash

./periodic_table
