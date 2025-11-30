#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#ifdef _WIN32
  #include <windows.h>
  #include <direct.h>
  #define mkdir_dir(path) _mkdir(path)
  #define sleep_ms(ms) Sleep(ms)
#else
  #include <unistd.h>
  #include <sys/stat.h>
  #define mkdir_dir(path) mkdir(path, 0755)
  #define sleep_ms(ms) usleep((ms) * 1000)
#endif

typedef struct ContactBook {
    char name[100];
    char phone[20];
} CB;

static void ensure_contact_dir(void) {
    mkdir_dir("contact");
}

static void trim_newline(char *s) {
    size_t n = strlen(s);
    if (n == 0) return;
    if (s[n-1] == '\n') s[n-1] = '\0';
}

static int is_valid_phone(const char *p) {
    if (strlen(p) != 10) return 0;
    for (size_t i = 0; i < 10; ++i)
        if (!isdigit((unsigned char)p[i])) return 0;
    return 1;
}

int firstPage(void)
{
    printf("\n\n");
    printf("=====================================================\n");
    printf("\t\tWELCOME TO CONTACT BOOK\t\t\t\t\t\n");
    printf("=====================================================\n");
    printf("                \t\t Developed in C Language\n");
    printf("               \t\t  Save | Search | Delete\n");
    printf("-----------------------------------------------------\n");
    printf("                    Loading");
    fflush(stdout);
    for (int i = 0; i < 6; ++i) {
        printf(".");
        fflush(stdout);
        sleep_ms(300);
    }
    printf("\n\n");
    return 0;
}

void addContact(void)
{
    CB c;
    const char *path = "contact/sample_input.txt";

    ensure_contact_dir();

    FILE *fp = fopen(path, "a");
    if (fp == NULL) {
        printf("Error opening file '%s' for append!\n", path);
        return;
    }

    printf("Enter Name: ");
    if (!fgets(c.name, sizeof c.name, stdin)) {
        printf("Input error.\n");
        fclose(fp);
        return;
    }
    trim_newline(c.name);
    if (c.name[0] == '\0') {
        printf("Empty name not allowed.\n");
        fclose(fp);
        return;
    }

    while (1) {
        printf("Enter Phone Number (10 digits): ");
        if (!fgets(c.phone, sizeof c.phone, stdin)) {
            printf("Input error.\n");
            fclose(fp);
            return;
        }
        trim_newline(c.phone);

        if (is_valid_phone(c.phone)) {
            break;
        }
        printf("Invalid Phone Number! Please enter exactly 10 digits (0-9).\n");
    }

    fprintf(fp, "%s\t%s\n", c.name, c.phone);
    fclose(fp);

    printf("Contact Added Successfully!\n");
}

void viewContacts(void)
{
    CB c;
    const char *path = "contact/sample_input.txt";
    FILE *fp = fopen(path, "r");

    if (fp == NULL) {
        printf("No contacts found!\n");
        return;
    }
    printf("\n--- Contact List ---\n");
    while (fscanf(fp, " %99[^\t\n]\t%19s", c.name, c.phone) == 2) {
        printf("Name: %-25s Phone Number: %-15s\n", c.name, c.phone);
    }
    fclose(fp);
}

void searchContact(void)
{
    CB c;
    char searchName[100];
    int found = 0;
    const char *path = "contact/sample_input.txt";

    FILE *fp = fopen(path, "r");
    if (fp == NULL) {
        printf("No contacts found!\n");
        return;
    }

    printf("Enter name to search: ");
    if (!fgets(searchName, sizeof searchName, stdin)) {
        fclose(fp);
        return;
    }
    trim_newline(searchName);

    while (fscanf(fp, " %99[^\t\n]\t%19s", c.name, c.phone) == 2) {
        if (strcmp(c.name, searchName) == 0) {
            printf("\nContact Found!\n");
            printf("Name: %s\nPhone Number: %s\n", c.name, c.phone);
            found = 1;
            break;
        }
    }

    if (!found) printf("Contact Not Found!\n");
    fclose(fp);
}

void deleteContact(void)
{
    CB c;
    char deleteName[100];
    int found = 0;

    const char *path = "contact/sample_input.txt";
    const char *tempPath = "contact/temp.txt";

    FILE *fp = fopen(path, "r");
    FILE *temp = fopen(tempPath, "w");

    if (fp == NULL) {
        printf("No contacts found!\n");
        if (temp) fclose(temp);
        return;
    }
    if (temp == NULL) {
        printf("Error creating temporary file!\n");
        fclose(fp);
        return;
    }

    printf("Enter name to delete: ");
    if (!fgets(deleteName, sizeof deleteName, stdin)) {
        fclose(fp);
        fclose(temp);
        return;
    }
    trim_newline(deleteName);

    while (fscanf(fp, " %99[^\t\n]\t%19s", c.name, c.phone) == 2) {
        if (strcmp(c.name, deleteName) != 0) {
            fprintf(temp, "%s\t%s\n", c.name, c.phone);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    if (found) {
        if (remove(path) != 0) {
            printf("Warning: could not remove original file. Check permissions.\n");
        }
        if (rename(tempPath, path) != 0) {
            printf("Warning: could not rename temporary file. Check permissions.\n");
        } else {
            printf("Contact Deleted Successfully!\n");
            return;
        }
    } else {
        remove(tempPath);
        printf("Contact Not Found!\n");
    }
}

int main(void)
{
    int choice;
    char line[32];

    firstPage();

    while (1) {
        printf("\n--- CONTACT BOOK MENU ---\n");
        printf("1. Add Contact\n");
        printf("2. View Contacts\n");
        printf("3. Search Contact\n");
        printf("4. Delete Contact\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");

        if (!fgets(line, sizeof line, stdin)) {
            printf("Input error.\n");
            continue;
        }
        if (sscanf(line, "%d", &choice) != 1) {
            printf("Invalid input. Try again.\n");
            continue;
        }

        switch (choice) {
            case 1: addContact(); break;
            case 2: viewContacts(); break;
            case 3: searchContact(); break;
            case 4: deleteContact(); break;
            case 5:
                printf("Thank you for using Contact Book!\n");
                return 0;
            default:
                printf("Invalid choice!\n");
        }
    }
}
