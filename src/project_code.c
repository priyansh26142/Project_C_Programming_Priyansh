#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Contact Book
{
    char name[50];
    char phone[20];
} CB;

int FirstPage()
{
    printf("\n\n");
    printf("=====================================================\n");
    printf("\t\tWELCOME TO CONTACT BOOK\t\t\t\t\t\n");
    printf("=====================================================\n");
    printf("                \t\t Developed in C Language\n");
    printf("               \t\t  Save | Search | Delete\n");
    printf("-----------------------------------------------------\n");
    printf("                    Loading.......");

    for (int i = 0; i < 6; i++)
    {
        printf(".");
        fflush(stdout);
        for (int j = 0; j < 200000000; j++)
            ;
    }
    printf("\n\n");
    return 0;
}

void addContact()
{
    struct CB;
    FILE *fp = fopen("contact/contact_list.txt", "a");

    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter Name: ");
    scanf("%s", c.name);
    while (1)
    {

        printf("Enter Phone Number: ");
        scanf("%s", c.phone);
        printf("\nInvalid Phone Number! Please enter a 10-digit number.\n");
        if (strlen(c.phone) != 10)
        {
        }
        else
        {
            break;
        }
    }

    fprintf(fp, "%s %s\n", c.name, c.phone);
    fclose(fp);

    printf("Contact Added Successfully!\n");
}

void viewContacts()
{
    struct CB;
    FILE *fp = fopen("contact/contacts_list.txt", "r");

    if (fp == NULL)
    {
        printf("No contacts found!\n");
        return;
    }

    printf("\t\t\t\n--- Contact List ---\n");
    while (fscanf(fp, "%s %s", c.name, c.phone) != EOF)
    {
        printf("Name: %-15s Phone Number: %-15s\n", c.name, c.phone);
    }
    fclose(fp);
}

void searchContact()
{
    struct CB;
    char searchName[50];
    int found = 0;

    FILE *fp = fopen("contact/contacts_list.txt", "r");

    if (fp == NULL)
    {
        printf("No contacts found!\n");
        return;
    }

    printf("Enter name to search: ");
    scanf("%s", searchName);

    while (fscanf(fp, "%s %s", c.name, c.phone) != EOF)
    {
        if (strcmp(c.name, searchName) == 0)
        {
            printf("\nContact Found!\n");
            printf("Name: %s\nPhone Number: %s\n", c.name, c.phone);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Contact Not Found!\n");

    fclose(fp);
}

void deleteContact()
{
    struct CB;
    char deleteName[50];
    int found = 0;

    FILE *fp = fopen("contact/contacts_list.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (fp == NULL)
    {
        printf("No contacts found!\n");
        return;
    }

    printf("Enter name to delete: ");
    scanf("%s", deleteName);

    while (fscanf(fp, "%s %s", c.name, c.phone) != EOF)
    {
        if (strcmp(c.name, deleteName) != 0)
        {
            fprintf(temp, "%s %s\n", c.name, c.phone);
        }
        else
        {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    remove("contact/contacts_list.txt");
    rename("contact/temp.txt", "contact/contacts_list.txt");

    if (found)
        printf("Contact Deleted Successfully!\n");
    else
        printf("Contact Not Found!\n");
}

int main()
{
    int choice;

    openingPage();

    while (1)
    {
        printf("\n--- CONTACT BOOK MENU ---\n");
        printf("1. Add Contact\n");
        printf("2. View Contacts\n");
        printf("3. Search Contact\n");
        printf("4. Delete Contact\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");

        scanf("%d ", &choice);
        

        switch (choice)
        {
        case 1:
            addContact();
            break;
        case 2:
            viewContacts();
            break;
        case 3:
            searchContact();
            break;
        case 4:
            deleteContact();
            break;
        case 5:
            printf("Thank you for using Contact Book!\n");
            return 0;
        default:
            printf("Invalid choice!\n");
        }
    }
}
