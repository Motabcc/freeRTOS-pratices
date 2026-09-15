# 🚁 Controle de Quadricóptero com FreeRTOS - Fase I

> Projeto desenvolvido para a disciplina de **Sistemas Operacionais Ciberfísicos** (Bacharelado em Ciência da Computação).

![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![FreeRTOS](https://img.shields.io/badge/FreeRTOS-20232A?style=for-the-badge&logo=freertos&logoColor=green)

## 📖 Sobre o Projeto

O objetivo desta primeira fase do projeto é simular o comportamento das manobras de voo de um quadricóptero utilizando conceitos de **Sistemas de Tempo Real (RTOS)** através do kernel **FreeRTOS**. 

Para que a aeronave voe e estabilize corretamente, é necessário controlar de forma concorrente a velocidade de rotação de quatro motores independentes, manipulando o empuxo para realizar três manobras básicas: Guinada, Arfagem e Rolagem.

## ⚙️ Manobras e Tarefas (Tasks)

O sistema conta com uma memória global compartilhada que representa as velocidades dos **4 Motores** (`m0, m1, m2, m3`). Três tarefas (*tasks*) rodam de forma concorrente, acessando e modificando essas velocidades de acordo com a manobra solicitada:

| Manobra | Movimento (Eixo) | Tarefa RTOS | Incremento/Decremento | Frequência de Controle |
| :--- | :--- | :--- | :--- | :--- |
| 🔄 **Guinada** (*Yaw*) | Rotação (Eixo Vertical) | `vTaskGuinada` | ± 100 | 100 Hz (10 ms) |
| ↕️ **Arfagem** (*Pitch*) | Frente/Trás (Eixo Lateral) | `vTaskArfagem` | ± 25 | 25 Hz (40 ms) |
| ↔️ **Rolagem** (*Roll*) | Esquerda/Direita (Longitudinal)| `vTaskRolagem` | ± 50 | 50 Hz (20 ms) |

## 🚀 Arquitetura e Implementação

1. **Estado Compartilhado:** Utilização de uma variável global contendo um `struct` para simular o estado atual do quadricóptero.
2. **Criação das Tasks:** As tarefas são iniciadas através da API `xTaskCreate`, todas com prioridade `1` no escalonador.
3. **Execução e Delay:** Cada task calcula a nova velocidade dos motores baseada em regras físicas de cancelamento de torque, formata a saída de texto via `sprintf` e imprime o log no console via `vPrintString`. Em seguida, utiliza `vTaskDelay` para respeitar as temporizações estritas do sistema embarcado.

## 💻 Como Executar

Este código foi desenvolvido para rodar no ambiente de desenvolvimento integrado do FreeRTOS.
1. Clone este repositório.
2. Adicione o arquivo fonte principal na sua configuração de projeto do FreeRTOS (Windows/Simulador ou Microcontrolador).
3. Certifique-se de que a biblioteca auxiliar `basic_io.h` (para impressões no console) está vinculada corretamente no *build*.
4. Compile, execute e acompanhe o comportamento dos motores pelo terminal.

---
👨‍💻 **Desenvolvido por:** Gabriel Mota
