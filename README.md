# 💻 Projetos FreeRTOS - Sistemas Operacionais Ciberfísicos

> Repositório com as atividades práticas e miniprojetos desenvolvidos para a disciplina de **Sistemas Operacionais Ciberfísicos** (Bacharelado em Ciência da Computação - PUCPR).

![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![FreeRTOS](https://img.shields.io/badge/FreeRTOS-20232A?style=for-the-badge&logo=freertos&logoColor=green)

Este repositório contém duas implementações focadas em Sistemas de Tempo Real (RTOS) utilizando o kernel FreeRTOS. Navegue pelos projetos abaixo:

* [1. Controle de Quadricóptero (Fase I)](#1--controle-de-quadricóptero---fase-i)
* [2. Monitoramento de Sinais Vitais em UTI](#2--monitoramento-de-sinais-vitais-em-uti)

---

## 1. 🚁 Controle de Quadricóptero - Fase I

### 📖 Sobre o Projeto
O objetivo desta primeira fase do projeto é simular o comportamento das manobras de voo de um quadricóptero. Para que a aeronave voe e estabilize corretamente, é necessário controlar de forma concorrente a velocidade de rotação de quatro motores independentes, manipulando o empuxo para realizar três manobras básicas: Guinada, Arfagem e Rolagem.

### ⚙️ Manobras e Tarefas (Tasks)
O sistema conta com uma memória global compartilhada que representa as velocidades dos **4 Motores** (`m0, m1, m2, m3`). Três tarefas (*tasks*) rodam de forma concorrente, acessando e modificando essas velocidades de acordo com a manobra solicitada:

| Manobra | Movimento (Eixo) | Tarefa RTOS | Incremento/Decremento | Frequência de Controle |
| :--- | :--- | :--- | :--- | :--- |
| 🔄 **Guinada** (*Yaw*) | Rotação (Eixo Vertical) | `vTaskGuinada` | ± 100 | 100 Hz (10 ms) |
| ↕️ **Arfagem** (*Pitch*) | Frente/Trás (Eixo Lateral) | `vTaskArfagem` | ± 25 | 25 Hz (40 ms) |
| ↔️ **Rolagem** (*Roll*) | Esquerda/Direita (Longitudinal)| `vTaskRolagem` | ± 50 | 50 Hz (20 ms) |

### 🚀 Arquitetura e Implementação
1. **Estado Compartilhado:** Utilização de uma variável global contendo um `struct` para simular o estado atual do quadricóptero.
2. **Criação das Tasks:** As tarefas são iniciadas através da API `xTaskCreate`, todas com prioridade `1` no escalonador.
3. **Execução e Delay:** Cada task calcula a nova velocidade dos motores baseada em regras físicas de cancelamento de torque, formata a saída de texto via `sprintf` e imprime o log no console via `vPrintString`. Em seguida, utiliza `vTaskDelay` para respeitar as temporizações estritas do sistema embarcado.

---

## 2. 🏥 Monitoramento de Sinais Vitais em UTI

### 📖 Sobre o Projeto
Este projeto implementa um sistema de tempo real crítico para o monitoramento de pacientes em Unidades de Terapia Intensiva (UTIs). O equipamento simula a coleta e análise de três sinais vitais essenciais através de tarefas concorrentes, gerando alertas automáticos no console caso os dados do paciente fujam dos limites de normalidade.

### ⚙️ Sinais Vitais e Regras de Alerta
O sistema é composto por três *tasks* independentes rodando com a mesma prioridade. Os dados de cada sinal biológico são gerados de maneira aleatória por sensores simulados a cada **1 segundo**.

| Sinal Vital | Parâmetro de Inicialização | Condições de Alerta |
| :--- | :--- | :--- |
| ❤️ **Frequência Cardíaca** | `"Batimentos:"` | **Bradicardia:** ≤ 50 bpm <br> **Normal:** 51 a 110 bpm <br> **Taquicardia:** > 110 bpm |
| 🩸 **Saturação Sanguínea** | `"Saturação:"` | **Baixa:** < 90% <br> **Atenção:** 90% a 94% <br> **Normal:** ≥ 95% |
| 🌡️ **Temperatura** | `"Temperatura:"` | **Hipotermia:** < 35.5 °C <br> **Normal:** 35.5 °C a 37.0 °C <br> **Febre:** > 37.0 °C |

### 🚀 Arquitetura e Implementação
1. **Geração de Dados:** Cada tarefa utiliza funções de geração de números aleatórios internamente em seu loop para simular a aferição contínua dos sinais vitais.
2. **Passagem de Parâmetros e Saída:** Os rótulos de leitura são passados para as tarefas através do ponteiro de inicialização. A impressão dos resultados consolidados e numéricos no terminal é feita via `vPrintStringAndNumber()`.
3. **Temporização:** Para satisfazer a restrição de tempo real, todas as medições ocorrem em uma janela fixa através do uso de `vTaskDelay(pdMS_TO_TICKS(1000))` no final do ciclo, garantindo leituras a cada 1 segundo exato. As tarefas também possuem configuração de exclusão explícita com `vTaskDelete()`.

---

## 💻 Como Executar

Estes códigos foram desenvolvidos para rodar no ambiente de desenvolvimento integrado do FreeRTOS.

1. Clone este repositório.
2. Adicione o arquivo fonte (`.c`) do projeto desejado na sua configuração principal do FreeRTOS (Windows/Simulador ou Microcontrolador).
3. Certifique-se de que a biblioteca auxiliar `basic_io.h` (para impressões no console) está vinculada corretamente no *build* do seu projeto.
4. Compile, execute e acompanhe o comportamento dos sistemas através das saídas no terminal.

---
👨‍💻 **Desenvolvido por:** Gabriel Mota (e integrantes de equipe, quando aplicável).
