#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct ContactBook
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
        for (volatile long j = 0; j < 20000000; j++)
            ; // smaller busy loop
    }
    printf("\n\n");
    return 0;
}

void addContact()
{
    CB c;
    FILE *fp = fopen("contact/contacts_list.txt", "a");
    if (fp == NULL)
    {
        printf("Error opening file! Make sure 'contact' directory exists.\n");
        return;
    }

    printf("Enter Name: ");
    scanf("%49s", c.name); // limit width

    while (1)
    {
        printf("Enter Phone Number (10 digits): ");
        scanf("%19s", c.phone);
        if (strlen(c.phone) != 10)
        {
            printf("Invalid Phone Number! Please enter a 10-digit number.\n");
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
    CB c;
    FILE *fp = fopen("contact/contacts_list.txt", "r");
    if (fp == NULL)
    {
        printf("No contacts found!\n");
        return;
    }

    printf("\n--- Contact List ---\n");
    while (fscanf(fp, "%49s %19s", c.name, c.phone) == 2)
    {
        printf("Name: %-15s Phone Number: %-15s\n", c.name, c.phone);
    }
    fclose(fp);
}

void searchContact()
{
    CB c;
    char searchName[50];
    int found = 0;

    FILE *fp = fopen("contact/contacts_list.txt", "r");
    if (fp == NULL)
    {
        printf("No contacts found!\n");
        return;
    }

    printf("Enter name to search: ");
    scanf("%49s", searchName);

    while (fscanf(fp, "%49s %19s", c.name, c.phone) == 2)
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
    CB c;
    char deleteName[50];
    int found = 0;

    FILE *fp = fopen("contact/contacts_list.txt", "r");
    if (fp == NULL)
    {
        printf("No contacts found!\n");
        return;
    }

    FILE *temp = fopen("contact/temp.txt", "w");
    if (temp == NULL)
    {
        printf("Error creating temporary file.\n");
        fclose(fp);
        return;
    }

    printf("Enter name to delete: ");
    scanf("%49s", deleteName);

    while (fscanf(fp, "%49s %19s", c.name, c.phone) == 2)
    {
        if (strcmp(c.name, deleteName) != 0)
        {
            fprintf(temp, "%s %s\n", c.name, c.phone);
        }
        else
        {
            found = 1;
            // skip writing this contact -> effectively deletes it
        }
    }

    fclose(fp);
    fclose(temp);

    if (found)
    {
        if (remove("contact/contacts_list.txt") != 0)
        {
            printf("Error removing original contacts file.\n");
            return;
        }
        if (rename("contact/temp.txt", "contact/contacts_list.txt") != 0)
        {
            printf("Error renaming temp file.\n");
            return;
        }
        printf("Contact Deleted Successfully!\n");
    }
    else
    {
        // No contact found -> remove temp and keep original
        remove("contact/temp.txt");
        printf("Contact Not Found!\n");
    }
}

int main()
{
    int choice;

    FirstPage();

    while (1)
    {
        printf("\n--- CONTACT BOOK MENU ---\n");
        printf("1. Add Contact\n");
        printf("2. View Contacts\n");
        printf("3. Search Contact\n");
        printf("4. Delete Contact\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1)
        {
            // clear invalid input
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF)
                ;
            printf("Invalid input. Please enter a number.\n");
            continue;
        }

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
