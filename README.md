Student Management System in C
About the Project

This is a simple Student Management System made using C language. I created this project to manage student records in an easy way through a menu-driven program.

The program stores student details in a file, so the data does not get deleted when the program is closed.

Features

The project has the following options:

Add Student – Add a new student's details.
Delete Student – Delete a student using their ID.
Update Student – Update the details of an existing student.
Search Student – Search for a student using their ID.
Display All Students – Display all saved student records.
Exit – Close the program.
Student Details

The program stores:

Student ID / Roll Number
Name
Age
Gender
Course
Semester
Contact Number
Email
Concepts Used

While making this project, I used:

Structures (struct)
Functions
Arrays/records
File handling
fopen()
fread()
fwrite()
fseek()
rewind()
fclose()
Input validation
Menu-driven programming
File Handling

The student records are stored in a file named:

students.dat

The file is created automatically when the first student is added. The records remain saved even after closing the program.

How to Run

Make sure GCC is installed on your computer.

Open the project folder in VS Code and run it in terminal

Run the program on Windows:

student_management.exe
Example Menu
============================================
       STUDENT MANAGEMENT SYSTEM
============================================
1. Add Student
2. Delete Student
3. Update Student
4. Search Student
5. Display All Students
6. Exit
============================================
Enter your choice:
Validation

The program also checks for some common errors, such as:

Duplicate student ID
Invalid student ID
Invalid age
Empty student details
Invalid contact number
Invalid email
Invalid menu choice
Missing data file
Purpose

The main purpose of this project is to understand how C structures, functions, and file handling can be combined to create a practical application.

Language Used

C
