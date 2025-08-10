#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct student {
    int id;          // Student ID
    char name[50];   // Student Name
    int age;         // Student Age
    float gpa;       // Student GPA
} Student;

typedef struct node {
    Student data;
    struct node *next;
} Node;

Node *head = NULL;

void addStudent() {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory allocation failed\n");
        return;
    }

    printf("Enter the student ID: ");
    scanf("%d", &newNode->data.id);

    Node *temp = head;
    while (temp) {
        if (temp->data.id == newNode->data.id) {
            printf("This ID already exists\n");
            free(newNode);
            return;
        }
        temp = temp->next;
    }

    getchar();
    printf("Please enter your name: ");
    fgets(newNode->data.name, sizeof(newNode->data.name), stdin);
    newNode->data.name[strcspn(newNode->data.name, "\n")] = '\0';

    printf("Please enter your age: ");
    scanf("%d", &newNode->data.age);

    printf("Please enter your GPA: ");
    scanf("%f", &newNode->data.gpa);

    newNode->next = NULL;

    if (head == NULL) {
        head = newNode;
    } else {
        temp = head;
        while (temp->next)
            temp = temp->next;
        temp->next = newNode;
    }
    printf("New student added successfully\n");
}

void displayStudents(void) {
    if (head == NULL) {
        printf("No students are present\n");
        return;
    }

    Node *temp = head;
    printf("\n--- All Students ---\n");
    while (temp) {
        printf("ID: %d | Name: %s | Age: %d | GPA: %.2f\n",
               temp->data.id, temp->data.name, temp->data.age, temp->data.gpa);
        temp = temp->next;
    }
}

void searchStudentByID(int id) {
    Node* temp = head;
    while (temp) {
        if (temp->data.id == id) {
            printf("Student Found: ID: %d | Name: %s | Age: %d | GPA: %.2f\n",
                   temp->data.id, temp->data.name, temp->data.age, temp->data.gpa);
            return;
        }
        temp = temp->next;
    }
    printf("Student with ID %d is not found\n", id);
}

void updateStudent(int id) {
    Node* temp = head;
    while (temp) {
        if (temp->data.id == id) {
            getchar();
            printf("Enter a new name: ");
            fgets(temp->data.name, sizeof(temp->data.name), stdin);
            temp->data.name[strcspn(temp->data.name, "\n")] = '\0';
            printf("Enter a new age: ");
            scanf("%d", &temp->data.age);
            printf("Enter a new GPA: ");
            scanf("%f", &temp->data.gpa);
            printf("Student updated successfully.\n");
            return;
        }
        temp = temp->next;
    }
    printf("Student with ID %d is not found.\n", id);
}

float calcAvgGPA(void) {
    if (head == NULL)
        return 0.0f;

    float sum = 0.0f;
    int c = 0;
    Node* temp = head;

    while (temp) {
        sum += temp->data.gpa;
        c++;
        temp = temp->next;
    }

    return (c > 0) ? (sum / c) : 0.0f;
}

void searchHighestGPA(void) {
    if (head == NULL) {
        printf("No students found.\n");
        return;
    }

    Node* temp = head;
    Node* top = head;

    while (temp) {
        if (temp->data.gpa > top->data.gpa) {
            top = temp;
        }
        temp = temp->next;
    }

    printf("Top Student: ID: %d | Name: %s | Age: %d | GPA: %.2f\n",
           top->data.id, top->data.name, top->data.age, top->data.gpa);
}

void deleteStudent(int id) {
    Node *temp = head, *prev = NULL;

    while (temp) {
        if (temp->data.id == id) {
            if (prev == NULL)
                head = temp->next;
            else
                prev->next = temp->next;

            free(temp);
            printf("Student with ID %d has been deleted successfully.\n", id);
            return;
        }
        prev = temp;
        temp = temp->next;
    }

    printf("Student with ID %d is not found.\n", id);
}

void menu() {
    printf("\n--- Student Management System ---\n");
    printf("1. Add a Student\n");
    printf("2. Display All Students\n");
    printf("3. Search for a Student by ID\n");
    printf("4. Update Student Information\n");
    printf("5. Delete a Student\n");
    printf("6. Calculate Average GPA\n");
    printf("7. Find Student with Highest GPA\n");
    printf("8. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    setvbuf(stdout, NULL , _IONBF , 0);
    setvbuf(stderr, NULL , _IONBF , 0);

    int ch, id;

    while (1) {
        menu();
        scanf("%d", &ch);

        switch (ch) {
            case 1:
                addStudent();
                break;
            case 2:
                displayStudents();
                break;
            case 3:
                printf("Enter ID to search: ");
                scanf("%d", &id);
                searchStudentByID(id);
                break;
            case 4:
                printf("Enter ID to update: ");
                scanf("%d", &id);
                updateStudent(id);
                break;
            case 5:
                printf("Enter ID to delete: ");
                scanf("%d", &id);
                deleteStudent(id);
                break;
            case 6:
                printf("Average GPA: %.2f\n", calcAvgGPA());
                break;
            case 7:
                searchHighestGPA();
                break;
            case 8:
                printf("Exiting program.\n");
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}
