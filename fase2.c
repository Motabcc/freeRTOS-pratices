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
#include "semphr.h"
#include "basic_io.h"
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

//Parametros Motores
volatile long velocidadeMotor0 = 0;
volatile long velocidadeMotor1 = 0;
volatile long velocidadeMotor2 = 0;
volatile long velocidadeMotor3 = 0;

//Parametros de controle
volatile char sentido[15];
volatile char direcao[15];
volatile char orientacao[15];

SemaphoreHandle_t xSemaphore;

void print_status(const char* manobra, const char* status) {
    //tamanho do espaço
    char buffer[120];
    sprintf(buffer, "[%s] Acao: %s | M0: %ld, M1: %ld, M2: %ld, M3: %ld\r\n", 
            manobra, status, velocidadeMotor0, velocidadeMotor1, velocidadeMotor2, velocidadeMotor3);
    vPrintString(buffer);
}

void vTaskGuinada(void * pvParameters);
void vTaskArfagem(void* pvParameters);
void vTaskRolagem(void* pvParameters);
void vTaskRadioFrequencia(void* pvParameters);

void vTaskGuinada(void *pvParameters)
{   
    // parâmetro inicial enviado na xTaskCreate
    if (pvParameters != NULL) {
        xSemaphoreTake(xSemaphore, portMAX_DELAY);
        sprintf((char*)sentido, "%s", (char*)pvParameters);
        xSemaphoreGive(xSemaphore);
    }

    char* status;
    for (;; )
    {
        // uso exclusivo dos motores e variáveis de controle
        xSemaphoreTake(xSemaphore, portMAX_DELAY);

        //se sentido horario
        if(strcmp((char*)sentido, "Sentido Horario") == 0){
            status = "Sentido Horario";
            velocidadeMotor0 += 100;
            velocidadeMotor2 += 100;
            velocidadeMotor1 -= 100;
            velocidadeMotor3 -= 100;
        }
        else{
            status = "SENTIDO ANTI-HORÁRIO"; 

            velocidadeMotor0 -= 100;
            velocidadeMotor1 += 100;
            velocidadeMotor2 -= 100;
            velocidadeMotor3 += 100;
        };

        print_status("Guinada", status);
        xSemaphoreGive(xSemaphore);

        vTaskDelay(portTICK_RATE_MS * 10);
    }

    vTaskDelete(NULL);
}

void vTaskArfagem(void* pvParameters)
{  
    // Recebe o parâmetro inicial enviado na xTaskCreate
    if (pvParameters != NULL) {
        xSemaphoreTake(xSemaphore, portMAX_DELAY);
        sprintf((char*)direcao, "%s", (char*)pvParameters);
        xSemaphoreGive(xSemaphore);
    }

    char* status;

    for (;; )
    {
        // Garante uso exclusivo dos motores e variáveis de controle
        xSemaphoreTake(xSemaphore, portMAX_DELAY);

        if(strcmp((char*)direcao, "Frente") == 0){
            status = "FRENTE";
            
            velocidadeMotor0 -= 25;
            velocidadeMotor1 -= 25;
            velocidadeMotor2 += 25;
            velocidadeMotor3 += 25;
        }
        else{
            status = "TRÁS";

            velocidadeMotor0 += 25;
            velocidadeMotor1 += 25;
            velocidadeMotor2 -= 25;
            velocidadeMotor3 -= 25;
        };

        print_status("Arfagem", status);
        xSemaphoreGive(xSemaphore);

        vTaskDelay(portTICK_RATE_MS * 40);
    }

    vTaskDelete(NULL);
}

void vTaskRolagem(void * pvParameters)
{   
    // Recebe o parâmetro inicial enviado na xTaskCreate
    if (pvParameters != NULL) {
        xSemaphoreTake(xSemaphore, portMAX_DELAY);
        sprintf((char*)orientacao, "%s", (char*)pvParameters);
        xSemaphoreGive(xSemaphore);
    }

    char *status;
    
    for(;;){
        // Garante uso exclusivo dos motores e variáveis de controle
        xSemaphoreTake(xSemaphore, portMAX_DELAY);

        if(strcmp((char*)orientacao, "Direita") == 0){
            status = "DIREITA";
            
            velocidadeMotor0 += 50;
            velocidadeMotor1 -= 50;
            velocidadeMotor2 -= 50;
            velocidadeMotor3 += 50;
        }
        else{
            status = "ESQUERDA";

            velocidadeMotor0 -= 50;
            velocidadeMotor1 += 50;
            velocidadeMotor2 += 50;
            velocidadeMotor3 -= 50;
        };

        print_status("Rolagem", status);
        xSemaphoreGive(xSemaphore);

        vTaskDelay(portTICK_RATE_MS * 20); 
    }
    vTaskDelete(NULL);
}

void vTaskRadioFrequencia(void * pvParameters)         
{   
    int num_rand;
    for (;;)
    {   
        // Garante acesso exclusivo para modificar as variáveis globais
        xSemaphoreTake(xSemaphore, portMAX_DELAY);

        // Sortear número de 0 a 100 e verificar par ou ímpar
        num_rand = rand() % 100;
        if(num_rand % 2 == 0){
            sprintf((char*)sentido, "Sentido Horario");
        }
        else{
            sprintf((char*)sentido, "Sentido Anti-Horário");
        }

        num_rand = rand() % 100;
        if(num_rand % 2 == 0){
            sprintf((char*)direcao, "Frente");
        }
        else{
            sprintf((char*)direcao, "Trás");
        }

        num_rand = rand() % 100;
        if(num_rand % 2 == 0){
            sprintf((char*)orientacao, "Direita");
        }
        else{
            sprintf((char*)orientacao, "Esquerda");
        }

        xSemaphoreGive(xSemaphore);

        vTaskDelay(portTICK_RATE_MS * 100);
    }
    vTaskDelete(NULL);
}

void main_(void)
{
    // Criação do semáforo binário
    vSemaphoreCreateBinary(xSemaphore);

    if (xSemaphore != NULL)
    {
        // Criação das tarefas passando o parâmetro inicial e prioridades (manobras = 2, radio = 1)
        xTaskCreate(vTaskGuinada, "Task Guinada", 1000, (void*)"Sentido Horario", 2, NULL);
        xTaskCreate(vTaskArfagem, "Task Arfagem", 1000, (void*)"Frente", 2, NULL);
        xTaskCreate(vTaskRolagem, "Task Rolagem", 1000, (void*)"Direita", 2, NULL);
        xTaskCreate(vTaskRadioFrequencia, "Task RadioFrequencia", 1000, NULL, 1, NULL);

        // Inicia o escalonador de tarefas
        vTaskStartScheduler();
    }

    for (;; );
}