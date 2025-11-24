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
    printf("                    Loading....");
    fflush(stdout);
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

// adding contact in book
void addContact()
{
    CB c;
    const char *path = "contact/contacts_list.txt";
    FILE *fp = fopen(path, "a");

    if (fp == NULL)
    {
        printf("Error opening file '%s'!\n", path);
        return;
    }

    printf("Enter Name: ");
    scanf("%49s", c.name);

    while (1)
    {
        printf("Enter Phone Number: ");
        scanf("%10s", c.phone); // allow only 10 characters

        if (strlen(c.phone) == 10)
        {
            
            // continue;
            break;
        }
        printf("\nInvalid Phone Number! Please enter a 10-digit number.\n");
    }

    fprintf(fp, "%s %s\n", c.name, c.phone);
    fclose(fp);

    printf("Contact Added Successfully!\n");
}

// viewing contacts in book
void viewContacts()
{
    CB c;
    const char *path = "contact/contacts_list.txt";
    FILE *fp = fopen(path, "r");

    if (fp == NULL)
    {
        printf("No contacts found!\n");
        return;
    }
    // displaying contact list
    printf("\n--- Contact List ---\n");
    while (fscanf(fp, "%49s %19s", c.name, c.phone) == 2)
    {
        printf("Name: %-15s Phone Number: %-15s\n", c.name, c.phone);
    }
    fclose(fp);
}

// searching contact in book
void searchContact()
{
    CB c;
    char searchName[50];
    int found = 0;
    const char *path = "contact/contacts_list.txt";

    FILE *fp = fopen(path, "r");
    if (fp == NULL)
    {
        printf("No contacts found!\n");
        return;
    }
    // getting name to search
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

// deleting contact from book
void deleteContact()
{
    CB c;
    char deleteName[50];
    int found = 0;

    const char *path = "contact/contacts_list.txt";
    const char *tempPath = "contact/temp.txt";

    FILE *fp = fopen(path, "r");
    FILE *temp = fopen(tempPath, "w");

    if (fp == NULL)
    {
        printf("No contacts found!\n");
        if (temp)
            fclose(temp);
        return;
    }
    if (temp == NULL)
    {
        printf("Error creating temporary file!\n");
        fclose(fp);
        return;
    }

    // getting name to delete
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
        }
    }
    // closing files
    fclose(fp);
    fclose(temp);

    if (remove(path) != 0)
    {
        printf("Warning: could not remove original file.\n");
    }
    if (rename(tempPath, path) != 0)
    {
        printf("Warning: could not rename temporary file.\n");
    }

    if (found)
        printf("Contact Deleted Successfully!\n");
    else
        printf("Contact Not Found!\n");
}

// main function
int main()
{
    int choice;

    FirstPage();
    // menu display
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
            // invalid input: clear stdin and continue
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF)
                ;
            printf("Invalid input. Try again.\n");
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
