#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


struct Student {
    int id;
    char name[50];
    float grade;
};


struct Student *students = NULL;
int count = 0;
int capacity = 0;

/*add a student*/
void add_student() {
    if (count == capacity) {
        capacity += 5;
        students = realloc(students, capacity * sizeof(struct Student));
        if (students == NULL) {
            printf("Memory error!\n");
            return;
        }
    }

    struct Student *s = students + count;
    printf("Enter ID: ");
    scanf("%d", &s->id);
    printf("Enter Name: ");
    scanf("%s", s->name);
    printf("Enter Grade (0-100): ");
    scanf("%f", &s->grade);
    count++;
    printf("Student added!\n");
}

/*  display all students  */
void display_students() {
    if (count == 0) {
        printf("No students found.\n");
        return;
    }
    printf("\n%-5s %-20s %-10s\n", "ID", "Name", "Grade");
    printf("---------------------------\n");
    int i;
    for (i = 0; i < count; i++) {
        struct Student *s = students + i;
        printf("%-5d %-20s %.2f\n", s->id, s->name, s->grade);
    }
}

/* Sort students by grade */
void sort_students() {
    int i, j;
    struct Student temp;
    for (i = 0; i < count - 1; i++) {
        for (j = 0; j < count - 1 - i; j++) {
            if ((students + j)->grade < (students + j + 1)->grade) {
                temp = *(students + j);
                *(students + j) = *(students + j + 1);
                *(students + j + 1) = temp;
            }
        }
    }
    printf("Students sorted by grade.\n");
}

/* Calculate average grade */
void calculate_average() {
    if (count == 0) {
        printf("No students.\n");
        return;
    }
    float total = 0;
    int i;
    for (i = 0; i < count; i++) {
        total += (students + i)->grade;
    }
    printf("Average Grade: %.2f\n", total / count);
}

/*Find the top student */
void find_top_student() {
    if (count == 0) {
        printf("No students.\n");
        return;
    }
    struct Student *top = students;
    int i;
    for (i = 1; i < count; i++) {
        if ((students + i)->grade > top->grade) {
            top = students + i;
        }
    }
    printf("Top Student: %s with grade %.2f\n", top->name, top->grade);
}


/* calculates how stable the grades are across students */
void grade_stability_score() {
    if (count < 2) {
        printf("Need at least 2 students.\n");
        return;
    }

    float total = 0;
    int i;
    for (i = 0; i < count; i++) {
        total += (students + i)->grade;
    }
    float mean = total / count;

    float variance = 0;
    for (i = 0; i < count; i++) {
        float diff = (students + i)->grade - mean;
        variance += diff * diff;
    }
    variance = variance / count;
    float std_dev = sqrt(variance);

    float score = 100 - std_dev;
    if (score < 0) score = 0;

    printf("\n--- Grade Stability Score ---\n");
    printf("Mean Grade: %.2f\n", mean);
    printf("Standard Deviation: %.2f\n", std_dev);
    printf("Stability Score: %.2f / 100\n", score);
    if (score >= 80)
        printf("Result: Class performance is very stable\n");
    else if (score >= 50)
        printf("Result: Moderate variation in grades\n");
    else
        printf("Result: High variation - grades are spread out\n");
}

void load_demo_data() {
    capacity = 10;
    students = malloc(capacity * sizeof(struct Student));

    struct Student demo[10] = {
        {1,  "Alice",   88.5},
        {2,  "Brian",   72.0},
        {3,  "Clara",   95.0},
        {4,  "David",   60.5},
        {5,  "Eva",     78.0},
        {6,  "Frank",   85.5},
        {7,  "Grace",   91.0},
        {8,  "Henry",   55.0},
        {9,  "Irene",   83.0},
        {10, "James",   67.5}
    };

    int i;
    for (i = 0; i < 10; i++) {
        *(students + i) = demo[i];
    }
    count = 10;
    printf("Demo data loaded (%d students)\n", count);
}


typedef void (*MenuFunction)();

int main() {
 
    printf("  Dynamic Student Record Engine \n");
    printf("  Student ID: 1005698443 \n");
    printf("  Analysis: Grade Stability Score\n");
   

    load_demo_data();

    /*pointers for menu */
    MenuFunction options[6] = {
        add_student,
        display_students,
        sort_students,
        calculate_average,
        find_top_student,
        grade_stability_score
    };

    char *labels[6] = {
        "Add Student",
        "Display Students",
        "Sort Students",
        "Calculate Average",
        "Find Top Student",
        "Grade Stability Score"
    };

    int choice;
    do {
        printf("\n--- Menu ---\n");
        int i;
        for (i = 0; i < 6; i++) {
            printf("%d. %s\n", i + 1, labels[i]);
        }
        printf("7. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);

        if (choice >= 1 && choice <= 6) {
            options[choice - 1]();
        } else if (choice != 7) {
            printf("Invalid choice.\n");
        }

    } while (choice != 7);

    printf("Goodbye!\n");
    free(students);
    return 0;
}
