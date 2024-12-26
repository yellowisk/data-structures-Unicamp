#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 100
#define START_COMMAND_LENGTH 8

typedef struct s_doctor {
    char CRM[7];
    char name[100];
} doctor;

typedef struct s_disease {
    char CID[4];
    char name[100];
} disease;

typedef struct s_appointment {
    char name[100];
    char CID[4];
    char CRM[7];
} appointment;

void get_info(int *lengthDoc, int *lengthDis, FILE **fpDoc, FILE **fpDis) {
    *fpDoc = fopen("dados/medicos.txt", "r");
    if (*fpDoc == NULL) {
        perror("Nao foi possivel abrir o arquivo medicos.txt");
        exit(1);
    }

    *fpDis = fopen("dados/doencas.txt", "r");
    if (*fpDis == NULL) {
        perror("Nao foi possivel abrir o arquivo doencas.txt");
        exit(1);
    }
    
    fscanf(*fpDoc, "%d", lengthDoc);
    fscanf(*fpDis, "%d", lengthDis);
}

void read_doctors(doctor *doctors, FILE **fp, int lengthDoc) {
    for (int i = 0; i < lengthDoc; i++) {
        char CRM[7];
        char name[100];
        doctor docStruct;

        fscanf(*fp, " %[^ ] %[^\n]", CRM, name);
        strcpy(docStruct.CRM, CRM);
        strcpy(docStruct.name, name);
        
        doctors[i] = docStruct;
    }

    fclose(*fp);
}

void read_diseases(disease *diseases, FILE **fp, int lengthDis) {
    for (int i = 0; i < lengthDis; i++) {
        char CID[4];
        char name[100];
        disease disStruct;

        fscanf(*fp, " %[^ ] %[^\n]", CID, name);
        strcpy(disStruct.CID, CID);
        strcpy(disStruct.name, name);
        
        diseases[i] = disStruct;
    }

    fclose(*fp);
}

int process_command(appointment *appointments, int *vacancies, int *currNumAppointments) {
    char command[MAX_LENGTH];
    scanf(" %[^ \n]", command);
    int i, j;

    if (strcmp(command, "remover") == 0) {
        char name[MAX_LENGTH];
        scanf(" %[^\n]", name);

        for (i = 0; i < *currNumAppointments; i++) {
            if (strcmp(appointments[i].name, name) == 0) {
                for (j = i; j < *currNumAppointments - 1; j++) {
                    appointments[j] = appointments[j + 1];
                }
                (*currNumAppointments)--;
                return 1;
            }
        }
    } else if (strcmp(command, "alterar") == 0) {
        char name[MAX_LENGTH];
        char CID[4];
        scanf(" %[^ ] %s", name, CID);

        for (i = 0; i < *currNumAppointments; i++) {
            if (strcmp(appointments[i].name, name) == 0) {
                strcpy(appointments[i].CID, CID);
                return 1;
            }
        }
    } else if (strcmp(command, "registrar") == 0) {
        if (*currNumAppointments < *vacancies) {
            char name[MAX_LENGTH];
            char CID[4];
            char CRM[7];
            scanf(" %[^ ] %[^ ] %s", name, CID, CRM);

            appointment newAppointment;
            strcpy(newAppointment.name, name);
            strcpy(newAppointment.CID, CID);
            strcpy(newAppointment.CRM, CRM);
            appointments[*currNumAppointments] = newAppointment;
            (*currNumAppointments)++;
            return 1;
        } else {
            return 0;
        }
    } else {
        return 0;
    }
    return 1;
}


int main() {
    int lengthDoc, lengthDis;
    FILE *fpDoc, *fpDis;

    // Get the number of doctors and dieseases
    get_info(&lengthDoc, &lengthDis, &fpDoc, &fpDis);

    // Populate the doctors and diseases arrays
    doctor *doctors = malloc(lengthDoc * sizeof(doctor));
    read_doctors(doctors, &fpDoc, lengthDoc);
    disease *diseases = malloc(lengthDis * sizeof(disease));
    read_diseases(diseases, &fpDis, lengthDis);

    char command[START_COMMAND_LENGTH];
    int vacancies;
    scanf(" %[^ ] %d", command, &vacancies);

    appointment *appointments = malloc(sizeof(appointment) * vacancies);

    int exit = 1;
    int currNumAppointments = 0;
    while (exit != 0) {
        exit = process_command(appointments, &vacancies, &currNumAppointments);
    }

    for (int i = 0; i < currNumAppointments; i++) {
        char docName[50];
        char disName[150];

        for (int j = 0; j < lengthDoc; j++) {
            if (strcmp(appointments[i].CRM, doctors[j].CRM) == 0) {
                strcpy(docName, doctors[j].name);
                break;
            }
        }

        for (int j = 0; j < lengthDis; j++) {
            if (strcmp(appointments[i].CID, diseases[j].CID) == 0) {
                strcpy(disName, diseases[j].name);
                break;
            }
        }
        printf("%s atendido por %s: %s\n", appointments[i].name, docName, disName);
    }

    free(doctors);
    free(diseases);
    free(appointments);

    return 0;
}