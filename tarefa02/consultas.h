#ifndef CONSULTAS_H
#define CONSULTAS_H

//Criando a estrutura com as variáveis necessárias para definir o que é uma doença
typedef struct {
    char CID[4];
    char nameDisease[101];
} Disease;

//Criando a estrutura com as variáveis necessárias para definir o que é um médico
typedef struct {
    char CRM[7];
    char nameDoctor[101];
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