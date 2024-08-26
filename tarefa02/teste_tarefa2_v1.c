#include <stdio.h>
#include "consultas.h"
#include <string.h>

int catalago_de_doenças(Disease doencas[]){
    /* Essa função irá ler o arquivo com todas as n doenças e cataogá-las (guardar em uma variável)*/
    
    //doencas é um array cujo cada elemento é uma variável do tipo "Disease"

    //Abrindo
    FILE *file_disease = fopen("dados/doencas.txt", "r");
    //Se a abertura do arquivo der errado: saia do programa
    if (file_disease == NULL) {
        return 1;
    }

    //Catalogando
    int num_diseases; //Em que n<= 150
    fscanf(file_disease, "%d", &num_diseases);

    for (int i = 0; i<num_diseases; i++){
        fscanf(file_disease,"%s %s", doencas[i].CID, doencas[i].nameDisease);
    }

    //Fechando
    fclose(file_disease);

    return num_diseases;
}

int catalogo_de_medicos(Doctor medicos[]){
    /* Essa função irá ler o arquivo com todas os médicos e cataogá-los (guardar em uma variável)*/
    
    //medicos é um array cujo cada elemento é uma variável do tipo "Doctor"

    //Abrindo
    FILE *file_doctor = fopen("dados/medicos.txt","r");
    //Se a abertura do arquivo der errado: saia do programa
    if (file_doctor == NULL){
        return 1;
    }

    //Catalogando
    int num_doctors; //Em que n<= 50
    fscanf(file_doctor, "%d", &num_doctors);

    for (int i = 0; i<num_doctors; i++){
        fscanf(file_doctor, "%s %s", medicos[i].CRM, medicos[i].nameDoctor);
    }

    //Fechando
    fclose(file_doctor);

    return num_doctors;
}

void open_medical_clinic(ManagementMedicalAppointment *g, int max_consultas){
    /*Essa função inicializa/"Abre" um dia da clínica*/
    g->num_consultas = 0; //Inicializando o dia com 0 consultas registradas no início do dia
    g->max_consultas = max_consultas;
}

void registrar(ManagementMedicalAppointment *gerenciamento, char *ponteiroNamePacient, char *CID, char *CRM, Disease doencas[], int num_diseases, Doctor medicos[], int num_doctors){
    //Acessando variáveis da struct que g aponta
    if (gerenciamento->num_consultas >= gerenciamento->max_consultas){
        printf("Não há mais vagas para consultar no dia de hoje.\n");
        return;
    }

    //Inicialização dos ponteiros
    Disease *doenca = NULL;
    Doctor *medico = NULL;

    //Encontrando a doença do paciente no catálogo de doenças
    for (int i = 0; i< num_diseases; i++){
        if (strcmp(doencas[i].CID,CID) == 0){
            doenca = &doencas[i]; //Aguardando qual doença é a do paciente
            break; //Doença achada
        }
    } 

    //Encontrando o médico que atenderá o paciente no catálogo de médicos
    for (int i = 0; i<num_doctors; i++){
        if (strcmp(medicos[i].CRM, CRM) == 0){
            medico = &medicos[i];//Aguardando qual médico atenderá o paciente
            break; //Médico achado
        }
    }

    /*Registrando o atendimento médico*/

    //Registrando o nome do paciete:

    //gerenciamento é um ponteiro que aponta para um struct do tipo "ManagementMedicalAppointment"
    //Dentro de "ManagementMedicalAppointment" há o array cujos elemntos são do tipo do tipo "consultas"
    //Para definir bem uma "consultas[i]" é necessário saber o nome do pacente
    //ponteiroNamePacient aponta para o local da memório onde será guardado o nome do paciente
    strcpy(gerenciamento->consultas[gerenciamento->num_consultas].namePacient, ponteiroNamePacient);

    //Registrando o tipo de doença:
    gerenciamento->consultas[gerenciamento->num_consultas].doenca = *doenca;

    //Registando o médico que irá atender:
    gerenciamento->consultas[gerenciamento->num_consultas].medico = *medico;

    //Ajustando num_consultas para receber o próximo registro
    gerenciamento->num_consultas++;
}

void remover(ManagementMedicalAppointment *gerenciamento, char *ponteiroNamePacient){
    
    for (int i = 0; i< gerenciamento->num_consultas; i++){
        if (strcmp(gerenciamento->consultas[i].namePacient, ponteiroNamePacient) == 0){
            
            //Eliminando a consulta a ser removida sem deixar "buracos" no array consultas
            for (int j = i; j< (gerenciamento->num_consultas-1); j++){
                gerenciamento->consultas[j] = gerenciamento->consultas[j+1];
            }

            //A cada remoção o número de consultas diminui um
            gerenciamento->num_consultas--;
            break; //Consulta a ser removida já achada e removida
        }
    }
}

void alterar(ManagementMedicalAppointment *gerenciamento, char *ponteiroNamePacient, char *newCID, Disease doencas[], int num_diseases){

    Disease *doencaCorretaPonteiro = NULL;

    //Encontrando o endereço da doença correta por meio do novo CID
    for (int i = 0; i < num_diseases; i++){
        if (strcmp(doencas[i].CID,newCID) == 0){
            doencaCorretaPonteiro = &doencas[i];
        }
    }

    //Atualizando o CID da doença correta do paciente:
    for (int i = 0; i < gerenciamento->num_consultas; i++){
        if (strcmp(gerenciamento->consultas[i].namePacient,ponteiroNamePacient) == 0){

            gerenciamento->consultas[i].doenca = *doencaCorretaPonteiro;
            break; //Doença correta foi atualizada na lista de consultas do dia
        }
    }
}

void close_medical_clinic(ManagementMedicalAppointment *gerenciamento){

    for (int i = 0; i<gerenciamento->num_consultas; i++){
        printf("%s atendido por %s: %s\n", gerenciamento->consultas[i].namePacient, gerenciamento->consultas[i].medico.nameDoctor, gerenciamento->consultas[i].doenca.nameDisease);
    }
}

int main(){
    ManagementMedicalAppointment gerenciamento;
    Disease doencas[150]; //Há no máximo 150 tipos de doenças
    Doctor medicos[50]; //Há no máximo 50 médicos na clínica

    int num_diseases = catalago_de_doenças(doencas);
    int num_doctors = catalogo_de_medicos(medicos);

    char tarefa[50];
    while (scanf("%s", tarefa) != EOF){
        if (strcmp(tarefa, "abrir") == 0){
            int max_consultas;
            scanf("%d", &max_consultas);
            open_medical_clinic(&gerenciamento, max_consultas);
        }
        else if (strcmp(tarefa, "registrar") == 0){
            char namePacient[100];
            char CID[5]; //CID: 1 letra + 2 dígitos + \0
            char CRM[7]; //CRM: 6 letra + \0
            scanf("%s %s %s", namePacient, CID, CRM);
            registrar(&gerenciamento, namePacient, CID, CRM, doencas, num_diseases, medicos, num_doctors);
        }
        else if (strcmp(tarefa, "remover") == 0){
            char namePacient[100];
            scanf("%s", namePacient);
            remover(&gerenciamento, namePacient);
        }
        else if (strcmp(tarefa, "alterar") == 0){
            char namePacient[100];
            char newCID[5];
            scanf("%s %s", namePacient, newCID);
            alterar(&gerenciamento, namePacient, newCID, doencas, num_diseases);
        }
        else if (strcmp(tarefa, "fechar") == 0){
            close_medical_clinic(&gerenciamento);
            break;
        }
    }

    return 0;
}