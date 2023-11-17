#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_QUEUE_SIZE 10
#define MAX_PATIENTS 100
#define FILE_PATH "C:\\Users\\chrom\\OneDrive\\Desktop\\patients.dat"

// Structure to represent a patient
typedef struct {
    char name[50];
    int priority; // 1 for emergency, 2 for urgent, 3 for routine
} Patient;

// Structure to represent a queue of patients
typedef struct {
    Patient data[MAX_QUEUE_SIZE];
    int front, rear;
} Queue;

// Structure to represent a patient in the priority queue
typedef struct {
    Patient patientData;
    int priority; // 1 for emergency, 2 for urgent, 3 for routine
} PriorityPatient;

// Structure to represent a priority queue of patients
typedef struct {
    PriorityPatient data[MAX_QUEUE_SIZE];
    int front, rear;
} PriorityQueue;

// Structure to represent patient data
struct PatientData {
    int id;
    char name[50];
    int age;
    char blood_group[5];
    char disease[50];
};

// Function to initialize a queue
void initializeQueue(Queue *q) {
    q->front = -1;
    q->rear = -1;
}

// Function to check if the queue is empty
int isEmpty(Queue *q) {
    return q->front == -1;
}

// Function to check if the queue is full
int isFull(Queue *q) {
    return (q->rear + 1) % MAX_QUEUE_SIZE == q->front;
}

// Function to enqueue a patient
void enqueue(Queue *q, Patient p) {
    if (isFull(q)) {
        printf("Queue is full. Cannot add more patients.\n");
    } else {
        if (isEmpty(q)) {
            q->front = 0;
        }
        q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
        q->data[q->rear] = p;
        printf("Patient %s added to the queue.\n", p.name);
    }
}

// Function to update the name of a patient
void update_name(char *name) {
    printf("Enter new name: ");
    scanf("%s", name);
}

// Function to update the age of a patient
void update_age(int *age) {
    printf("Enter new age: ");
    scanf("%d", age);
}

// Function to update the blood group of a patient
void update_blood_group(char *blood_group) {
    printf("Enter new blood group: ");
    scanf("%s", blood_group);
}

// Function to update the disease of a patient
void update_disease(char *disease) {
    printf("Enter new disease: ");
    scanf("%s", disease);
}

// Function to print patient data
void print_patient_data(const struct PatientData *patient) {
    printf("ID: %d\n", patient->id);
    printf("Name: %s\n", patient->name);
    printf("Age: %d\n", patient->age);
    printf("Blood Group: %s\n", patient->blood_group);
    printf("Disease: %s\n", patient->disease);
}

// Function to save patient data to a file
void save_patients_to_file(const struct PatientData patients[], int patientCount) {
    FILE *file = fopen(FILE_PATH, "wb");

    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    fwrite(patients, sizeof(struct PatientData), patientCount, file);

    fclose(file);
}

// Function to load patient data from a file
void load_patients_from_file(struct PatientData patients[], int *patientCount) {
    FILE *file = fopen(FILE_PATH, "rb");

    if (file == NULL) {
        printf("No saved patient data found.\n");
        return;
    }

    *patientCount = fread(patients, sizeof(struct PatientData), MAX_PATIENTS, file);

    fclose(file);
}

// Function to add a new patient to the data array
void add_patient(struct PatientData patients[], int *patientCount) {
    struct PatientData newPatient;

    printf("Enter ID: ");
    scanf("%d", &newPatient.id);

    // Check if the specified ID already exists
    for (int i = 0; i < *patientCount; i++) {
        if (patients[i].id == newPatient.id) {
            printf("Patient with ID %d already exists. Please choose a different ID.\n", newPatient.id);
            return;
        }
    }

    printf("Enter name: ");
    scanf("%s", newPatient.name);

    printf("Enter age: ");
    scanf("%d", &newPatient.age);

    printf("Enter blood group: ");
    scanf("%s", newPatient.blood_group);

    printf("Enter disease: ");
    scanf("%s", newPatient.disease);

    if (*patientCount < MAX_PATIENTS) {
        patients[*patientCount] = newPatient;
        (*patientCount)++;
        printf("Patient added successfully!\n");
    } else {
        printf("Maximum number of patients reached!\n");
    }
}

// Function to edit an existing patient's information
void edit_patient(struct PatientData patients[], int patientCount) {
    int patientId;
    printf("Enter the ID of the patient to edit: ");
    scanf("%d", &patientId);

    for (int i = 0; i < patientCount; i++) {
        if (patients[i].id == patientId) {
            printf("Editing patient with ID %d:\n", patientId);

            int updateChoice;
            do {
                printf("\nUpdate Menu:\n");
                printf("1. Update name\n");
                printf("2. Update age\n");
                printf("3. Update blood group\n");
                printf("4. Update disease\n");
                printf("5. Exit update menu\n");
                printf("Enter your choice: ");
                scanf("%d", &updateChoice);

                switch (updateChoice) {
                    case 1:
                        update_name(patients[i].name);
                        break;
                    case 2:
                        update_age(&patients[i].age);
                        break;
                    case 3:
                        update_blood_group(patients[i].blood_group);
                        break;
                    case 4:
                        update_disease(patients[i].disease);
                        break;
                    case 5:
                        printf("Exiting update menu.\n");
                        break;
                    default:
                        printf("Invalid choice. Please enter a number between 1 and 5.\n");
                }
            } while (updateChoice != 5);

            printf("Patient edited successfully!\n");
            return;
        }
    }

    printf("Patient not found!\n");
}

// Function to delete an existing patient from the patient data array
void delete_patient(struct PatientData patients[], int *patientCount) {
    int patientId;
    printf("Enter the ID of the patient to delete: ");
    scanf("%d", &patientId);

    for (int i = 0; i < *patientCount; i++) {
        if (patients[i].id == patientId) {
                        for (int j = i; j < *patientCount - 1; j++) {
                patients[j] = patients[j + 1];
            }
            (*patientCount)--;
            printf("Patient deleted successfully!\n");
            return;
        }
    }

    printf("Patient not found!\n");
}

// Function to display details of an existing patient
void display_patient_details(const struct PatientData patients[], int patientCount) {
    int patientId;
    printf("Enter the ID of the patient to display details: ");
    scanf("%d", &patientId);

    for (int i = 0; i < patientCount; i++) {
        if (patients[i].id == patientId) {
            printf("Details of patient with ID %d:\n", patientId);
            print_patient_data(&patients[i]);
            return;
        }
    }

    printf("Patient not found!\n");
}

// Function to initialize a priority queue
void initializePriorityQueue(PriorityQueue *pq) {
    pq->front = -1;
    pq->rear = -1;
}

// Function to display the patient queue
void displayQueue(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty.\n");
    } else {
        printf("Queue:\n");
        int i = q->front;
        do {
            Patient p = q->data[i];
            printf("%s (Priority: %d)\n", p.name, p.priority);
            i = (i + 1) % MAX_QUEUE_SIZE;
        } while (i != (q->rear + 1) % MAX_QUEUE_SIZE);
    }
}

// Function to dequeue a patient with the highest priority
void dequeue(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty. No patients to dequeue.\n");
    } else {
        // Find the patient with the highest priority without sorting
        int highestPriorityIndex = q->front;
        for (int i = (q->front + 1) % MAX_QUEUE_SIZE; i != (q->rear + 1) % MAX_QUEUE_SIZE; i = (i + 1) % MAX_QUEUE_SIZE) {
            if (q->data[i].priority < q->data[highestPriorityIndex].priority) {
                highestPriorityIndex = i;
            }
        }

        // Serve the patient with the highest priority
        Patient p = q->data[highestPriorityIndex];
        printf("Patient %s with priority %d is being treated.\n", p.name, p.priority);

        // Remove the served patient from the queue
        if (q->front == q->rear) {
            // Last patient served, reset the queue
            initializeQueue(q);
        } else {
            // Remove the treated patient from the queue
            for (int i = highestPriorityIndex; i != q->rear; i = (i + 1) % MAX_QUEUE_SIZE) {
                q->data[i] = q->data[(i + 1) % MAX_QUEUE_SIZE];
            }
            q->rear = (q->rear - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
        }
    }
}

// Function to simulate treating one patient
void simTreatment(Queue *q) {
    if (!isEmpty(q)) {
        // Dequeue and treat one patient
        dequeue(q);

        // Simulate treating time using sleep (replace with actual treatment logic)
        sleep(2); // Simulating 2 seconds of treating time

        // Display the remaining patients in the queue
        displayQueue(q);
    } else {
        printf("Queue is empty. No patients to treat.\n");
    }
}

void registerPatients(struct PatientData patients[], int *patientCount) {
    int registrationChoice;
    do {
        printf("\nRegistration Menu:\n");
        printf("1. Add new patient\n");
        printf("2. Edit patient\n");
        printf("3. Delete patient\n");
        printf("4. Display patient details\n");
        printf("5. Back to the main menu\n");
        printf("Enter your choice: ");
        scanf("%d", &registrationChoice);

        switch (registrationChoice) {
            case 1:
                add_patient(patients, patientCount);
                break;
            case 2:
                edit_patient(patients, *patientCount);
                break;
            case 3:
                delete_patient(patients, patientCount);
                break;
            case 4:
                display_patient_details(patients, *patientCount);
                break;
            case 5:
                printf("Exiting registration menu.\n");
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 5.\n");
        }
    } while (registrationChoice != 5);
}

int main() {
    // Initialize the patient queue
    Queue patientQueue;
    initializeQueue(&patientQueue);

    // Initialize the priority patient queue
    PriorityQueue priorityQueue;
    initializePriorityQueue(&priorityQueue);

    // Array to store patient data
    struct PatientData patients[MAX_PATIENTS];
    int patientCount = 0;

    // Load existing patient data from file
    load_patients_from_file(patients, &patientCount);

    int choice;
    do {
        // Display menu options
        printf("\nHospital Queue Management System\n");
        printf("1. Enqueue Patient\n");
        printf("2. Display Queue\n");
        printf("3. Simulate Treatment\n");
        printf("4. Register\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        // Process user choice
        switch (choice) {
            case 1: {
                // Enqueue a new patient
                Patient newPatient;
                printf("Enter patient name: ");
                scanf("%s", newPatient.name);
                printf("Enter priority (1 for emergency, 2 for urgent, 3 for routine): ");
                scanf("%d", &newPatient.priority);
                enqueue(&patientQueue, newPatient);
                break;
            }
            case 2:
                // Display the patient queue
                displayQueue(&patientQueue);
                break;
            case 3:
                // Simulate treating one patient
                simTreatment(&patientQueue);
                break;
            case 4:
                // Register patients
                registerPatients(patients, &patientCount);
                break;
            case 5:
                // Exit the program
                printf("Exiting the program.\n");
                break;
            default:
                // Invalid choice
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 5);

    // Save patient data to file before exiting
    save_patients_to_file(patients, patientCount);

    return 0;
}

