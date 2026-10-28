/******************************************************************************
 * Program to implement a multilevel telephone directory using	*
 * linked lists (index nodes A-Z and contact sub-lists)	*
 * Author: SOORAJ	*
 * Date: 1-10-26	*
 * Version: 1	*
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct contactNode
{
    char name[50];
    char phone[15];
    char email[50];
    struct contactNode *next;
};

struct indexNode
{
    char letter;
    struct contactNode *contacts;
    struct indexNode *next;
};

struct indexNode *head = NULL;

// function prototypes
int compareNames(char *a, char *b);                       // case-insensitive name comparison
int startsWith(char *str, char *prefix);                  // case-insensitive prefix check
struct indexNode *findIndex(char letter);                 // finds the index node of a letter
struct indexNode *createIndex(char letter);               // creates an index node in sorted order
int isDuplicatePhone(char *phone);                        // checks if phone exists anywhere
void insertContact(char *name, char *phone, char *email); // adds a new contact
void deleteContact(char *name);                           // deletes a contact by name
void searchContacts(char *prefix);                        // lists contacts starting with prefix
void displayDirectory(void);                              // prints the whole directory
void freeDirectory(void);                                 // frees all index and contact nodes

int main()
{
    int choice = -1;
    char name[50], phone[15], email[50];
    while (choice != 5)
    {
        printf("Menu for Telephone Directory\n");
        printf("1.Insert Contact\n2.Delete Contact\n3.Search by Prefix\n");
        printf("4.Display Directory\n5.Exit\n");
        printf("Enter Your choice:\n");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("Enter The name:\n");
            scanf(" %49[^\n]", name);
            printf("Enter The phone number:\n");
            scanf("%14s", phone);
            printf("Enter The email:\n");
            scanf("%49s", email);
            insertContact(name, phone, email);
            break;
        case 2:
            printf("Enter The name to delete:\n");
            scanf(" %49[^\n]", name);
            deleteContact(name);
            break;
        case 3:
            printf("Enter The search string:\n");
            scanf(" %49[^\n]", name);
            searchContacts(name);
            break;
        case 4:
            displayDirectory();
            break;
        case 5:
            freeDirectory();
            printf("Exiting Program\n");
            break;
        default:
            printf("Wrong choice\n");
        }
    }
    return 0;
}

int compareNames(char *a, char *b)
{
    while (*a != '\0' && tolower((unsigned char)*a) == tolower((unsigned char)*b))
    {
        a++;
        b++;
    }
    return tolower((unsigned char)*a) - tolower((unsigned char)*b);
}

int startsWith(char *str, char *prefix)
{
    while (*prefix != '\0')
    {
        if (tolower((unsigned char)*str) != tolower((unsigned char)*prefix))
            return 0;
        str++;
        prefix++;
    }
    return 1;
}

struct indexNode *findIndex(char letter)
{
    struct indexNode *current = head;
    while (current != NULL)
    {
        if (current->letter == letter)
            return current;
        current = current->next;
    }
    return NULL;
}

struct indexNode *createIndex(char letter)
{
    struct indexNode *newNode = (struct indexNode *)malloc(sizeof(struct indexNode));
    newNode->letter = letter;
    newNode->contacts = NULL;
    if (head == NULL || letter < head->letter)
    {
        newNode->next = head;
        head = newNode;
    }
    else
    {
        struct indexNode *current = head;
        while (current->next != NULL && current->next->letter < letter)
        {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
    return newNode;
}

int isDuplicatePhone(char *phone)
{
    struct indexNode *idx = head;
    while (idx != NULL)
    {
        struct contactNode *curr = idx->contacts;
        while (curr != NULL)
        {
            if (strcmp(curr->phone, phone) == 0)
                return 1;
            curr = curr->next;
        }
        idx = idx->next;
    }
    return 0;
}

void insertContact(char *name, char *phone, char *email)
{
    if (!isalpha((unsigned char)name[0]))
    {
        printf("Name must start with a letter A-Z\n");
        return;
    }
    if (isDuplicatePhone(phone))
    {
        printf("Phone number already exists, contact not added\n");
        return;
    }
    char letter = toupper((unsigned char)name[0]);
    struct indexNode *idx = findIndex(letter);
    if (idx == NULL)
        idx = createIndex(letter);
    struct contactNode *newNode = (struct contactNode *)malloc(sizeof(struct contactNode));
    strcpy(newNode->name, name);
    strcpy(newNode->phone, phone);
    strcpy(newNode->email, email);
    if (idx->contacts == NULL || compareNames(name, idx->contacts->name) < 0)
    {
        newNode->next = idx->contacts;
        idx->contacts = newNode;
    }
    else
    {
        struct contactNode *curr = idx->contacts;
        while (curr->next != NULL && compareNames(name, curr->next->name) >= 0)
        {
            curr = curr->next;
        }
        newNode->next = curr->next;
        curr->next = newNode;
    }
    printf("Contact added under index %c\n", letter);
}

void deleteContact(char *name)
{
    char letter = toupper((unsigned char)name[0]);
    struct indexNode *prevIdx = NULL;
    struct indexNode *idx = head;
    while (idx != NULL && idx->letter != letter)
    {
        prevIdx = idx;
        idx = idx->next;
    }
    if (idx == NULL)
    {
        printf("Contact not found\n");
        return;
    }
    struct contactNode *prev = NULL;
    struct contactNode *curr = idx->contacts;
    while (curr != NULL && compareNames(curr->name, name) != 0)
    {
        prev = curr;
        curr = curr->next;
    }
    if (curr == NULL)
    {
        printf("Contact not found\n");
        return;
    }
    if (prev == NULL)
        idx->contacts = curr->next;
    else
        prev->next = curr->next;
    free(curr);
    printf("Contact deleted\n");
    if (idx->contacts == NULL)
    {
        if (prevIdx == NULL)
            head = idx->next;
        else
            prevIdx->next = idx->next;
        free(idx);
        printf("Index node %c removed as it has no contacts\n", letter);
    }
}

void searchContacts(char *prefix)
{
    int found = 0;
    struct indexNode *idx = findIndex(toupper((unsigned char)prefix[0]));
    if (idx != NULL)
    {
        struct contactNode *curr = idx->contacts;
        while (curr != NULL)
        {
            if (startsWith(curr->name, prefix))
            {
                printf("%s | %s | %s\n", curr->name, curr->phone, curr->email);
                found++;
            }
            curr = curr->next;
        }
    }
    if (found == 0)
        printf("No contacts found for '%s'\n", prefix);
}

void displayDirectory(void)
{
    if (head == NULL)
    {
        printf("Directory is empty\n");
        return;
    }
    struct indexNode *idx = head;
    while (idx != NULL)
    {
        printf("[%c]\n", idx->letter);
        struct contactNode *curr = idx->contacts;
        while (curr != NULL)
        {
            printf("  %s | %s | %s\n", curr->name, curr->phone, curr->email);
            curr = curr->next;
        }
        idx = idx->next;
    }
}

void freeDirectory(void)
{
    while (head != NULL)
    {
        struct indexNode *idx = head;
        head = head->next;
        while (idx->contacts != NULL)
        {
            struct contactNode *temp = idx->contacts;
            idx->contacts = temp->next;
            free(temp);
        }
        free(idx);
    }
}
