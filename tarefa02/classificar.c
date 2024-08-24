#include <stdio.h>
#include <string.h>

int main(){
    int n; // Número de pacientes
    scanf("%d", &n);

    //Construir lista de nomes_sobrenomes
    char name_list[100][30]; //30 => Número máximo de caractéres por nome & 100 => Número máximo de nomes
    //char name[30];

    //Atribuindo todos os elementos igual a 0 na lista de pacientes
    for (int i = 0; i<100; i++){
        for (int j = 0; j<30; j++){
            name_list[i][j] = '\0';
        }
    }

    for (int i = 0; i<n; i++){
        scanf("%s", name_list[i]);
    }

    //Entrada do comando
    char comando[20], palavra_chave[20];
    scanf("%s %s", comando, palavra_chave);



    //Fazer tarefa
    if (strcmp(comando,"homonimos") == 0){
        for (int i = 0; i<n; i++){
            //Encontrar o local da memória da primeira aparição de "_"
            char *position_;
            position_ = strchr(name_list[i],'_');

            int index_name;
           //int index_surname;

            //Determinar a posição da primeira aparição do "_"
            if (position_ != NULL){
                index_name = position_ - name_list[i];
                //index_surname = strlen(name_list[i]) - index_name;
            }


            char name[20];
            //char surname[20];

            strncpy(name, name_list[i], index_name);
            name[index_name] = '\0';

            if (strcmp(name, palavra_chave) == 0){
                printf("%s\n", name_list[i]);
            }

        }
    }

    else if((strcmp(comando,"parentes") == 0)){
        for (int i = 0; i<n; i++){
            //Encontrar o local da memória da primeira aparição de "_"
            char *position_;
            position_ = strchr(name_list[i],'_');

            int index_name;
            int index_surname;

            //Determinar a posição da primeira aparição do "_"
            if (position_ != NULL){
                index_name = position_ - name_list[i];
                index_surname = strlen(name_list[i]) - index_name -1;
            }
           
            char surname[20];

            strncpy(surname, name_list[i] + index_name + 1, index_surname);
            surname[index_surname] = '\0';

            if (strcmp(surname, palavra_chave) == 0){
                printf("%s\n", name_list[i]);
            }
        }
    }

    return 0;

}