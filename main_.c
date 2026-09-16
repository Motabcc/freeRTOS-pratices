/*
Curso: Bacharelado em Ciência da Computação
Disciplina: Sistemas Operacionais Ciberfísicos
Período: 4
Turma: A
Integrantes:
    -Gabriel Mota
*/
#include "FreeRTOS.h"
#include "task.h"
#include "basic_io.h"
#include <stdio.h>
#include <stdbool.h> 

//Parametros Motores
typedef struct{
    int m0;
    int m1;
    int m2;
    int m3;
} Motores;
Motores motores ={0,0,0,0};

//Parametros Guinada
typedef struct{
    //se for true horario senao antihorario
    bool sentido_horario;
} DadosGuinada;

//Parametros Arfagem
typedef struct{
    //se for true frente senao trás
    bool frente;
} DadosArfagem;

//Parametros Rolagem
typedef struct{
    //se for true direita senao esquerda
    bool direita;
}DadosRolagem;

void print_status(const char* manobra, const char* status) {
    //tamanho do espaço
    char buffer[120];
    sprintf(buffer, "[%s] Acao: %s | M0: %d, M1: %d, M2: %d, M3: %d\r\n", 
            manobra, status, motores.m0, motores.m1, motores.m2, motores.m3);
    vPrintString(buffer);
}


void vTaskGuinada(void * DadosGuinada);
void vTaskArfagem(void* DadosArfagem);
void vTaskRolagem(void* DadosRolagem);


void vTaskGuinada(void *pvParameters)
{   //faz o ponteiro do void apontar para struct
    DadosGuinada *pt_dados = (DadosGuinada *) pvParameters;
    char* status ;



    for (;; )
    {
    
    if(pt_dados->sentido_horario){
        status = "Sentido Horario";
            motores.m0 += 100;
            motores.m2 += 100;
            motores.m1 -= 100;
            motores.m3 -= 100;
    }
    else{
        status = "SENTIDO ANTI-HORÁRIO"; 

        motores.m0 -=100;
        motores.m1 +=100 ;
        motores.m2 -=100 ;
        motores.m3 +=100 ;

    };
        print_status("Guinada",status);
        vTaskDelay(pdMS_TO_TICKS(10));
    }

    vTaskDelete(NULL);
}

void vTaskArfagem(void* pvParameters)
{   DadosArfagem *pt_dados =(DadosArfagem*) pvParameters;

    char* status ;

    for (;; )
    {
        if(pt_dados->frente){
        
         status = "FRENTE" ;
        
        motores.m0 -=25;
        motores.m1 -=25 ;
        motores.m2 +=25 ;
        motores.m3 +=25 ;
    }
    else{
         status = "TRÁS";
        motores.m0 +=25;
        motores.m1 +=25 ;
        motores.m2 -=25 ;
        motores.m3 -=25;

    };
    

        print_status("Arfagem",status);
        vTaskDelay(pdMS_TO_TICKS(40));
    }

    vTaskDelete(NULL);
}

void vTaskRolagem(void * pvParameters)
{   DadosRolagem *pt_dados =(DadosRolagem*) pvParameters;

    char *status  ;


    
    for(;;){

    if(pt_dados->direita){
        status = "DIREITA" ;

        motores.m0 +=50;
        motores.m1 -=50 ;
        motores.m2 -=50 ;
        motores.m3 +=50;
    }
    else{
        status = "ESQUERDA" ;

        motores.m0 -=50;
        motores.m1 +=50;
        motores.m2 +=50 ;
        motores.m3 -=50 ;

    };

        print_status("Rolagem",status);
        vTaskDelay(pdMS_TO_TICKS(20)); 
    }
    vTaskDelete(NULL);
}


void main_(void)
{
    //Setando parametros inicias
    static DadosGuinada dadoG = {.sentido_horario =true};
    static DadosArfagem dadoA = {.frente =true};
    static DadosRolagem dadoR = {.direita =true};

    //Criação das tarefas
    xTaskCreate(vTaskGuinada, "Task Guinada", 1000, (void*)&dadoG, 1, NULL);
    xTaskCreate(vTaskArfagem, "Task Arfagem", 1000, (void*)&dadoA, 1, NULL);
    xTaskCreate(vTaskRolagem, "Task Rolagem", 1000, (void*)&dadoR, 1, NULL);

    // Inicia o escalonador de tarefas
    vTaskStartScheduler();

    for (;; );
}

