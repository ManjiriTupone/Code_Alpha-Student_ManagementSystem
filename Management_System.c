#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define DATA_FILE "students.dat"
#define TEMP_FILE "students_temp.dat"

#define NAME_SIZE 50
#define GENDER_SIZE 15
#define COURSE_SIZE 50
#define CONTACT_SIZE 20
#define EMAIL_SIZE 60

typedef struct
{
    int studentID;
    char name[NAME_SIZE];
    int age;
    char gender[GENDER_SIZE];
    char course[COURSE_SIZE];
    int semester;
    char contact[CONTACT_SIZE];
    char email[EMAIL_SIZE];
} Student;


/* Function Prototypes */
void displayMenu(void);
void addStudent(void);
void displayAllStudents(void);
void searchStudent(void);
void updateStudent(void);
void deleteStudent(void);

int studentIDExists(int id);

int readInt(const char *prompt, int min, int max);
void readString(const char *prompt, char *buffer, int size);
void readContact(char *contact);
void readEmail(char *email);

void displayStudent(const Student *student);
void clearInputBuffer(void);
void pauseScreen(void);

void printHeader(const char *title);
void printLine(void);


/* ==================== MAIN ==================== */

int main(void)
{
    int choice;

    do
    {
        displayMenu();

        choice = readInt("Enter your choice: ", 1, 6);

        switch (choice)
        {
            case 1:
                addStudent();
                break;

            case 2:
                displayAllStudents();
                break;

            case 3:
                searchStudent();
                break;

            case 4:
                updateStudent();
                break;

            case 5:
                deleteStudent();
                break;

            case 6:
                printf("\n");
                printLine();
                printf("        THANK YOU FOR USING THE SYSTEM\n");
                printf("              END OF PROGRAM\n");
                printLine();
                break;
        }

        if (choice != 6)
        {
            pauseScreen();
        }

    } while (choice != 6);

    return 0;
}


/* ==================== MENU ==================== */

void displayMenu(void)
{
    printf("\n\n");
    printf("+--------------------------------------------------+\n");
    printf("|           STUDENT MANAGEMENT SYSTEM              |\n");
    printf("+--------------------------------------------------+\n");
    printf("|                                                  |\n");
    printf("|   [1]  Add New Student                           |\n");
    printf("|   [2]  Display All Students                      |\n");
    printf("|   [3]  Search Student                            |\n");
    printf("|   [4]  Update Student                            |\n");
    printf("|   [5]  Delete Student                            |\n");
    printf("|   [6]  Exit                                      |\n");
    printf("|                                                  |\n");
    printf("+--------------------------------------------------+\n");
}


/* ==================== ADD STUDENT ==================== */

void addStudent(void)
{
    Student student;
    FILE *file;

    printHeader("ADD NEW STUDENT");

    while (1)
    {
        student.studentID =
            readInt("Student ID / Roll Number: ", 1, 999999);

        if (studentIDExists(student.studentID))
        {
            printf("\n[ERROR] Student ID already exists.\n");
            printf("Please enter a different ID.\n\n");
        }
        else
        {
            break;
        }
    }

    readString("Student Name: ",
               student.name, NAME_SIZE);

    student.age =
        readInt("Age: ", 1, 100);

    readString("Gender: ",
               student.gender, GENDER_SIZE);

    readString("Course: ",
               student.course, COURSE_SIZE);

    student.semester =
        readInt("Semester: ", 1, 12);

    readContact(student.contact);
    readEmail(student.email);

    file = fopen(DATA_FILE, "ab");

    if (file == NULL)
    {
        printf("\n[ERROR] Unable to open data file.\n");
        return;
    }

    if (fwrite(&student, sizeof(Student), 1, file) != 1)
    {
        printf("\n[ERROR] Unable to save student record.\n");
        fclose(file);
        return;
    }

    fclose(file);

    printf("\n");
    printLine();
    printf("Student added successfully!\n");
    printf("Student ID: %d\n", student.studentID);
    printLine();
}


/* ==================== DISPLAY ALL ==================== */

void displayAllStudents(void)
{
    FILE *file;
    Student student;
    int count = 0;

    printHeader("ALL STUDENT RECORDS");

    file = fopen(DATA_FILE, "rb");

    if (file == NULL)
    {
        printf("No student records found.\n");
        printf("Add a student first.\n");
        return;
    }

    while (fread(&student, sizeof(Student), 1, file) == 1)
    {
        count++;

        printf("\n");
        printf("+--------------------------------------------------+\n");
        printf("|                 STUDENT #%d                      |\n", count);
        printf("+--------------------------------------------------+\n");

        printf("| ID       : %-35d |\n", student.studentID);
        printf("| Name     : %-35s |\n", student.name);
        printf("| Age      : %-35d |\n", student.age);
        printf("| Gender   : %-35s |\n", student.gender);
        printf("| Course   : %-35s |\n", student.course);
        printf("| Semester : %-35d |\n", student.semester);
        printf("| Contact  : %-35s |\n", student.contact);
        printf("| Email    : %-35s |\n", student.email);

        printf("+--------------------------------------------------+\n");
    }

    fclose(file);

    if (count == 0)
    {
        printf("\nNo student records available.\n");
    }
    else
    {
        printf("\n");
        printLine();
        printf("Total Students: %d\n", count);
        printLine();
    }
}


/* ==================== SEARCH ==================== */

void searchStudent(void)
{
    FILE *file;
    Student student;

    int choice;
    int id;
    int found = 0;

    char searchName[NAME_SIZE];

    printHeader("SEARCH STUDENT");

    printf("[1] Search by Student ID\n");
    printf("[2] Search by Name\n\n");

    choice = readInt("Select search method: ", 1, 2);

    file = fopen(DATA_FILE, "rb");

    if (file == NULL)
    {
        printf("\nNo student records found.\n");
        return;
    }

    if (choice == 1)
    {
        id = readInt("Enter Student ID: ", 1, 999999);

        while (fread(&student, sizeof(Student), 1, file) == 1)
        {
            if (student.studentID == id)
            {
                printf("\nSTUDENT FOUND\n");
                printLine();

                displayStudent(&student);

                found = 1;
                break;
            }
        }
    }
    else
    {
        readString("Enter Name: ",
                   searchName, NAME_SIZE);

        while (fread(&student, sizeof(Student), 1, file) == 1)
        {
            if (strstr(student.name, searchName) != NULL)
            {
                printf("\nSTUDENT FOUND\n");
                printLine();

                displayStudent(&student);

                found = 1;
            }
        }
    }

    fclose(file);

    if (!found)
    {
        printf("\n[INFO] No matching student found.\n");
    }
}


/* ==================== UPDATE ==================== */

void updateStudent(void)
{
    FILE *file;
    Student student;

    int id;
    int found = 0;
    int choice;

    long position;

    printHeader("UPDATE STUDENT");

    id = readInt("Enter Student ID: ", 1, 999999);

    file = fopen(DATA_FILE, "r+b");

    if (file == NULL)
    {
        printf("\nNo student records found.\n");
        return;
    }

    while (1)
    {
        position = ftell(file);

        if (fread(&student, sizeof(Student), 1, file) != 1)
        {
            break;
        }

        if (student.studentID == id)
        {
            found = 1;

            printf("\nCURRENT DETAILS\n");
            printLine();
            displayStudent(&student);

            printf("\nUPDATE OPTIONS\n");
            printf("------------------------------\n");
            printf("[1] Name\n");
            printf("[2] Age\n");
            printf("[3] Gender\n");
            printf("[4] Course\n");
            printf("[5] Semester\n");
            printf("[6] Contact\n");
            printf("[7] Email\n");
            printf("[8] All Details\n");
            printf("[9] Cancel\n");
            printf("------------------------------\n");

            choice = readInt("Enter your choice: ", 1, 9);

            if (choice == 9)
            {
                fclose(file);
                printf("\nUpdate cancelled.\n");
                return;
            }

            switch (choice)
            {
                case 1:
                    readString("New Name: ",
                               student.name, NAME_SIZE);
                    break;

                case 2:
                    student.age =
                        readInt("New Age: ", 1, 100);
                    break;

                case 3:
                    readString("New Gender: ",
                               student.gender, GENDER_SIZE);
                    break;

                case 4:
                    readString("New Course: ",
                               student.course, COURSE_SIZE);
                    break;

                case 5:
                    student.semester =
                        readInt("New Semester: ", 1, 12);
                    break;

                case 6:
                    readContact(student.contact);
                    break;

                case 7:
                    readEmail(student.email);
                    break;

                case 8:
                    readString("New Name: ",
                               student.name, NAME_SIZE);

                    student.age =
                        readInt("New Age: ", 1, 100);

                    readString("New Gender: ",
                               student.gender, GENDER_SIZE);

                    readString("New Course: ",
                               student.course, COURSE_SIZE);

                    student.semester =
                        readInt("New Semester: ", 1, 12);

                    readContact(student.contact);
                    readEmail(student.email);

                    break;
            }

            if (fseek(file, position, SEEK_SET) != 0)
            {
                printf("\n[ERROR] Unable to update record.\n");
                fclose(file);
                return;
            }

            if (fwrite(&student, sizeof(Student), 1, file) != 1)
            {
                printf("\n[ERROR] Unable to save updated record.\n");
                fclose(file);
                return;
            }

            fflush(file);

            printf("\n");
            printLine();
            printf("Student record updated successfully!\n");
            printLine();

            break;
        }
    }

    fclose(file);

    if (!found)
    {
        printf("\n[INFO] Student ID %d was not found.\n", id);
    }
}


/* ==================== DELETE ==================== */

void deleteStudent(void)
{
    FILE *file;
    FILE *tempFile;

    Student student;

    int id;
    int found = 0;

    printHeader("DELETE STUDENT");

    id = readInt("Enter Student ID: ", 1, 999999);

    file = fopen(DATA_FILE, "rb");

    if (file == NULL)
    {
        printf("\nNo student records found.\n");
        return;
    }

    tempFile = fopen(TEMP_FILE, "wb");

    if (tempFile == NULL)
    {
        printf("\n[ERROR] Unable to create temporary file.\n");
        fclose(file);
        return;
    }

    while (fread(&student, sizeof(Student), 1, file) == 1)
    {
        if (student.studentID == id)
        {
            found = 1;
            continue;
        }

        if (fwrite(&student, sizeof(Student), 1, tempFile) != 1)
        {
            printf("\n[ERROR] Unable to write temporary file.\n");

            fclose(file);
            fclose(tempFile);

            remove(TEMP_FILE);
            return;
        }
    }

    fclose(file);
    fclose(tempFile);

    if (!found)
    {
        remove(TEMP_FILE);

        printf("\n[INFO] Student ID %d was not found.\n", id);
        return;
    }

    if (remove(DATA_FILE) != 0)
    {
        printf("\n[ERROR] Unable to remove old data file.\n");
        remove(TEMP_FILE);
        return;
    }

    if (rename(TEMP_FILE, DATA_FILE) != 0)
    {
        printf("\n[ERROR] Unable to replace data file.\n");
        return;
    }

    printf("\n");
    printLine();
    printf("Student deleted successfully!\n");
    printf("Student ID %d has been removed.\n", id);
    printLine();
}


/* ==================== DUPLICATE ID CHECK ==================== */

int studentIDExists(int id)
{
    FILE *file;
    Student student;

    file = fopen(DATA_FILE, "rb");

    if (file == NULL)
    {
        return 0;
    }

    while (fread(&student, sizeof(Student), 1, file) == 1)
    {
        if (student.studentID == id)
        {
            fclose(file);
            return 1;
        }
    }

    fclose(file);

    return 0;
}


/* ==================== INTEGER INPUT ==================== */

int readInt(const char *prompt, int min, int max)
{
    int value;
    char line[100];
    char extra;

    while (1)
    {
        printf("%s", prompt);

        if (fgets(line, sizeof(line), stdin) == NULL)
        {
            continue;
        }

        if (sscanf(line, " %d %c", &value, &extra) == 1)
        {
            if (value >= min && value <= max)
            {
                return value;
            }
        }

        printf("[ERROR] Enter a number between %d and %d.\n",
               min, max);
    }
}


/* ==================== STRING INPUT ==================== */

void readString(const char *prompt, char *buffer, int size)
{
    size_t length;

    while (1)
    {
        printf("%s", prompt);

        if (fgets(buffer, size, stdin) == NULL)
        {
            continue;
        }

        length = strlen(buffer);

        if (length > 0 && buffer[length - 1] == '\n')
        {
            buffer[length - 1] = '\0';
        }
        else
        {
            clearInputBuffer();
        }

        if (strlen(buffer) == 0)
        {
            printf("[ERROR] Input cannot be empty.\n");
            continue;
        }

        return;
    }
}


/* ==================== CONTACT VALIDATION ==================== */

void readContact(char *contact)
{
    int i;
    int valid;

    while (1)
    {
        readString("Contact Number: ",
                   contact, CONTACT_SIZE);

        if (strlen(contact) < 7 ||
            strlen(contact) > 15)
        {
            printf("[ERROR] Contact number must contain 7-15 digits.\n");
            continue;
        }

        valid = 1;

        for (i = 0; contact[i] != '\0'; i++)
        {
            if (!isdigit((unsigned char)contact[i]) &&
                !(i == 0 && contact[i] == '+'))
            {
                valid = 0;
                break;
            }
        }

        if (!valid)
        {
            printf("[ERROR] Invalid contact number.\n");
            continue;
        }

        return;
    }
}


/* ==================== EMAIL VALIDATION ==================== */

void readEmail(char *email)
{
    while (1)
    {
        readString("Email: ",
                   email, EMAIL_SIZE);

        if (strchr(email, '@') == NULL ||
            strchr(email, '.') == NULL)
        {
            printf("[ERROR] Invalid email format.\n");
            continue;
        }

        return;
    }
}


/* ==================== DISPLAY STUDENT ==================== */

void displayStudent(const Student *student)
{
    printf("\n");
    printf("+--------------------------------------------------+\n");
    printf("|                 STUDENT DETAILS                  |\n");
    printf("+--------------------------------------------------+\n");

    printf("| Student ID : %-34d |\n",
           student->studentID);

    printf("| Name       : %-34s |\n",
           student->name);

    printf("| Age        : %-34d |\n",
           student->age);

    printf("| Gender     : %-34s |\n",
           student->gender);

    printf("| Course     : %-34s |\n",
           student->course);

    printf("| Semester   : %-34d |\n",
           student->semester);

    printf("| Contact    : %-34s |\n",
           student->contact);

    printf("| Email      : %-34s |\n",
           student->email);

    printf("+--------------------------------------------------+\n");
}


/* ==================== INPUT BUFFER ==================== */

void clearInputBuffer(void)
{
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF)
    {
        /* Clear remaining input */
    }
}


/* ==================== PAUSE ==================== */

void pauseScreen(void)
{
    char line[10];

    printf("\n");
    printf("+--------------------------------------------------+\n");
    printf("|              END OF OPERATION                   |\n");
    printf("+--------------------------------------------------+\n");

    printf("Press Enter to return to the main menu...");

    fgets(line, sizeof(line), stdin);
}


/* ==================== HEADER ==================== */

void printHeader(const char *title)
{
    printf("\n");
    printf("+--------------------------------------------------+\n");
    printf("| %-48s |\n", title);
    printf("+--------------------------------------------------+\n\n");
}


/* ==================== LINE ==================== */

void printLine(void)
{
    printf("----------------------------------------------------\n");
}