// Gabriel Mota

#include "FreeRTOS.h"
#include "task.h"
#include "basic_io.h"
#include <stdio.h>
#include <stdbool.h> 
#include <stdlib.h> 
#include <FreeRTOSConfig.h>

void vTaskTemperatura(void * pvParameters);
void vTaskSatSanguinea(void * pvParameters);
void vTaskFreqCardiaca(void * pvParameters);

void vTaskTemperatura(void * pvParameters){
    char * rotulo = (char *) pvParameters;
    char * status;
    for(;;){
        // Gera temperatura aleatória entre 34.0 e 40.0 °C
        float Temperatura = 34.0f + ((float)rand() / (float)RAND_MAX) * 6.0f;

        if(Temperatura > 37.0){
            status = "Febre";
        }
        else if(Temperatura < 35.5){
            status = "Hipotermia";
        }
        else{
            status = "Normal";
        }

        vPrintStringAndNumber(rotulo, (long)Temperatura);
        vPrintString(status);
        vTaskDelay(pdMS_TO_TICKS(1000));
    };
    vTaskDelete(NULL);
}

void vTaskSatSanguinea(void * pvParameters){
    char * status;
    char * rotulo = (char *) pvParameters;
    for(;;){
        int Saturacao = 85 + (rand() % 16);

        if(Saturacao >= 95){
            status = "Normal";
        }
        else if(Saturacao < 90){
            status = "Baixa";
        }
        else{
            status = "Atenção";
        }

        vPrintStringAndNumber(rotulo, Saturacao);
        vPrintString(status);
        vTaskDelay(pdMS_TO_TICKS(1000));
    };
    vTaskDelete(NULL);
}

void vTaskFreqCardiaca(void * pvParameters){
    char * status;
    char * rotulo = (char *) pvParameters;
    for(;;){
        // Batimentos aleatórios entre 40 e 130 bpm
        int Batimentos = 40 + (rand() % 91);

        if(Batimentos > 110){
            status = "Taquicardia";
        }
        else if(Batimentos <= 50){
            status = "Bradicardia";
        }
        else{
            status = "Normal";
        }

        vPrintStringAndNumber(rotulo, Batimentos);
        vPrintString(status);
        vTaskDelay(pdMS_TO_TICKS(1000));
    };
    vTaskDelete(NULL);
}

void main__(void){
    // Randomizar semente
    srand(1);

    xTaskCreate(vTaskTemperatura,"Temperatura",configMINIMAL_STACK_SIZE,(void*)"Temperatura:",1,NULL);
    xTaskCreate(vTaskSatSanguinea,"Saturação Sanguínea",configMINIMAL_STACK_SIZE,(void*)"Saturação:",1,NULL);
    xTaskCreate(vTaskFreqCardiaca,"Frequência Cardíaca",configMINIMAL_STACK_SIZE,(void*)"Batimentos:",1,NULL);

    vTaskStartScheduler();
    for(;;);
}