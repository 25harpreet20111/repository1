#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Contact {
    char name[50];
    char phone[15];
    char email[50];
    struct Contact *next;
};

struct Contact *head = NULL;

void addContact();
void listContacts();
void searchContact();
void editContact();
void deleteContact();

// Helper function to safely get string input
void getInput(char *prompt, char *str, int size) {
    printf("%s", prompt);
    fgets(str, size, stdin);
    str[strcspn(str, "\n")] = '\0'; // remove newline
}

int main() {
    int choice;
    while (1) {
        printf("\n=== Contact Management System ===\n");
        printf("1. Add Contact\n");
        printf("2. List All Contacts\n");
        printf("3. Search Contact\n");
        printf("4. Edit Contact\n");
        printf("5. Delete Contact\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();  // clear input buffer

        switch (choice) {
            case 1: addContact(); break;
            case 2: listContacts(); break;
            case 3: searchContact(); break;
            case 4: editContact(); break;
            case 5: deleteContact(); break;
            case 6:
                printf("Exit the program...\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again!\n");
        }
    }
    return 0;
}

void addContact() {
    struct Contact *newContact = (struct Contact *)malloc(sizeof(struct Contact));
    if (newContact == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    getInput("Enter name: ", newContact->name, sizeof(newContact->name));
    getInput("Enter phone: ", newContact->phone, sizeof(newContact->phone));
    getInput("Enter email: ", newContact->email, sizeof(newContact->email));
    newContact->next = NULL;

    if (head == NULL) {
        head = newContact;
    } else {
        struct Contact *temp = head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newContact;
    }

    printf("Contact added successfully!\n");
}

void listContacts() {
    struct Contact *temp = head;
    if (temp == NULL) {
        printf("No contacts found!\n");
        return;
    }

    printf("\n=== Contact List ===\n");
    while (temp != NULL) {
        printf("\nName : %s\nPhone: %s\nEmail: %s\n", temp->name, temp->phone, temp->email);
        temp = temp->next;
    }
}

void searchContact() {
    char name[50];
    int found = 0;
    getInput("Enter name to search: ", name, sizeof(name));

    struct Contact *temp = head;
    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0) {
            printf("\nContact found!\n");
            printf("Name : %s\nPhone: %s\nEmail: %s\n", temp->name, temp->phone, temp->email);
            found = 1;
            break;
        }
        temp = temp->next;
    }

    if (!found)
        printf("Contact not found!\n");
}

void editContact() {
    char name[50];
    int found = 0;
    getInput("Enter name of contact to edit: ", name, sizeof(name));

    struct Contact *temp = head;
    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0) {
            printf("Editing contact for %s\n", name);
            getInput("Enter new phone: ", temp->phone, sizeof(temp->phone));
            getInput("Enter new email: ", temp->email, sizeof(temp->email));
            printf("Contact updated successfully!\n");
            found = 1;
            break;
        }
        temp = temp->next;
    }

    if (!found)
        printf("Contact not found!\n");
}

void deleteContact() {
    char name[50];
    getInput("Enter name of contact to delete: ", name, sizeof(name));

    struct Contact *temp = head;
    struct Contact *prev = NULL;
    int found = 0;

    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0) {
            if (prev == NULL)
                head = temp->next;
            else
                prev->next = temp->next;

            free(temp);
            printf("Contact deleted successfully!\n");
            found = 1;
            break;
        }
        prev = temp;
        temp = temp->next;
    }

    if (!found)
        printf("Contact not found!\n");
}
