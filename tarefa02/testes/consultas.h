#ifndef CONSULTAS_H
#define CONSULTAS_H

//Criando a estrutura com as variáveis necessárias para definir o que é uma doença
typedef struct {
    char CID[5]; //CID: 1 letra + 2 dígitos + \0
    char nameDisease[100];
} Disease;

//Criando a estrutura com as variáveis necessárias para definir o que é um médico
typedef struct {
    char CRM[7]; //CRM: 6 letra + \0
    char nameDoctor[100];
} Doctor;

//Criando a estrutura com as variáveis necessárias para definir o que é uma consulta
typedef struct {
    char namePacient[100];
    Disease doenca;
    Doctor medico;
} MedicalAppointment;

//Criando a estrutura com as variáveis necessárias para gerenciar as consultas daquele dia
typedef struct {
    MedicalAppointment consultas[100];
    int num_consultas;
    int max_consultas;
} ManagementMedicalAppointment;

#endif