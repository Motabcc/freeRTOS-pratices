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
#include <stdlib.h> 


//Parametros Motores
volatile long velocidadeMotor0;
volatile long velocidadeMotor1;
volatile long velocidadeMotor2;
volatile long velocidadeMotor3;

//Parametros de controle
volatile char sentido[15];
volatile char direcao[15];
volatile char orientacao[15];

//Criação de semáforo binário utilizei o X pois o V estava dando conflito e causando Race conditions

xSemaphoreCreateBinary( xSemaphore);

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
{   
    char* status ;
    for (;; )
    {
    //se sentido horario
    if(sentido == "Sentido Horario"){
        status = "Sentido Horario";
            velocidadeMotor0 += 100;
            velocidadeMotor2 += 100;
            velocidadeMotor1 -= 100;
            velocidadeMotor3 -= 100;
    }
    else{
        status = "SENTIDO ANTI-HORÁRIO"; 

        velocidadeMotor0 -=100;
        velocidadeMotor1 +=100 ;
        velocidadeMotor2 -=100 ;
        velocidadeMotor3 +=100 ;

    };
        print_status("Guinada",status);
        vTaskDelay(pdMS_TO_TICKS(10));
    }

    vTaskDelete(NULL);
}

void vTaskArfagem(void* pvParameters)
{  

    char* status ;

    for (;; )
    {
        if(orientacao == "Frente"){
        
         status = "FRENTE" ;
        
        velocidadeMotor0 -=25;
        velocidadeMotor1 -=25 ;
        velocidadeMotor2 +=25 ;
        velocidadeMotor3 +=25 ;
    }
    else{
         status = "TRÁS";
        velocidadeMotor0 +=25;
        velocidadeMotor1 +=25 ;
        velocidadeMotor2 -=25 ;
        velocidadeMotor3 -=25;

    };
    

        print_status("Arfagem",status);
        vTaskDelay(pdMS_TO_TICKS(40));
    }

    vTaskDelete(NULL);
}

void vTaskRolagem(void * pvParameters)
{   
    char *status  ;
    
    for(;;){

    if(direcao == "Direita"){
        status = "DIREITA" ;

        velocidadeMotor0 +=50;
        velocidadeMotor1 -=50 ;
        velocidadeMotor2 -=50 ;
        velocidadeMotor3 +=50;
    }
    else{
        status = "ESQUERDA" ;

        velocidadeMotor0 -=50;
        velocidadeMotor1 +=50;
        velocidadeMotor2 +=50 ;
        velocidadeMotor3 -=50 ;

    };

        print_status("Rolagem",status);
        vTaskDelay(pdMS_TO_TICKS(20)); 
    }
    vTaskDelete(NULL);
}
vTaskRadioFrequencia(void * pvParameters)         
{   
    int num_rand;
    for (;;)
    {   //0 e 1
        num_rand = rand() % 2;
        if(num){
            sentido ="Sentido Horario";
        }
        else{
            sentido ="Sentido Anti-Horário";
        }
        num_rand = rand() % 2;
        if(num){
            direcao ="Direita";
        }
        else{
            direcao ="Esquerda";
        }
        num_rand = rand() % 2;
        if(num){
            orientacao ="Frente";
        }
        else{
            orientacao ="Trás";
        }

        vTaskDelay(pdMS_TO_TICKS(100));
    }
    vTaskDelete(NULL);
}


void main_(void)
{
    //Setando parametros inicias
    static sentido[15] = "Sentido Horario";
    static direcao[15] = "Direita";
    static orientacao[15] = "Frente";

    //Criação das tarefas
    xTaskCreate(vTaskGuinada, "Task Guinada", 1000, (void*)&dadoG, 1, NULL);
    xTaskCreate(vTaskArfagem, "Task Arfagem", 1000, (void*)&dadoA, 1, NULL);
    xTaskCreate(vTaskRolagem, "Task Rolagem", 1000, (void*)&dadoR, 1, NULL);
    xTaskCreate(vTaskRadioFrequencia, "Task RadioFrequencia", 1000, NULL, 2, NULL);

    // Inicia o escalonador de tarefas
    vTaskStartScheduler();

    for (;; );
}

