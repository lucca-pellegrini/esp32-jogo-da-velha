# Jogo da Velha com ESP32

Este repositório contém o código-fonte do microcontrolador (ESP32) para um
projeto de Jogo da Velha utilizando botões e LEDs. O projeto foi desenvolvido
como parte de um trabalho acadêmico e faz parte de um sistema maior, que inclui
um aplicativo para smartphone e uma apresentação detalhada.

## Sumário

- [Introdução](#introdução)
- [Instalação](#instalação)
- [Uso](#uso)
- [Estrutura do Código](#estrutura-do-código)
- [Referências](#referências)
- [Créditos](#créditos)

## Introdução

Este projeto implementa um Jogo da Velha que pode ser jogado em um tabuleiro de
LEDs controlado por um ESP32. O jogo suporta dois modos principais:

- **Jogador vs. Jogador**: onde dois jogadores humanos se alternam.
- **Jogador vs. Computador**: onde o jogador humano compete contra a IA do
  ESP32, que pode ser configurada em três níveis de dificuldade diferentes
  (fácil, normal, difícil).

O projeto foi desenvolvido como parte da disciplina Laboratório de Introdução à
Engenharia de Computação, do curso de Engenharia de Computação na PUC Minas
Unidade Lourdes no primeiro semestre de 2024, e inclui um aplicativo para
smartphone que pode ser usado para configurar o jogo via Bluetooth.

## Instalação

Para compilar e carregar o código no ESP32, recomendamos o uso do
[PlatformIO Core](https://docs.platformio.org/en/latest/core/). Siga os passos
abaixo:

1. Clone este repositório:

   ```bash
   git clone https://github.com/lucca-pellegrini/esp32-jogo-da-velha.git
   cd esp32-jogo-da-velha
   ```

2. Instale o PlatformIO Core:

   ```bash
   python -m venv venv
   source venv/bin/activate
   pip install platformio
   ```

3. Compile e, tendo o ESP32 conectado, faça o upload do código:
   ```bash
   pio run -t upload
   ```

## Uso

### Controles

- **Botão Esquerdo (BTN1)**: Move o cursor para a próxima posição vazia.
- **Botão Direito (BTN2)**: Confirma a jogada na posição do cursor.

### Configuração

Para configurar o jogo via Bluetooth, siga as instruções no
[manual](https://github.com/ICEI-PUC-Minas-EC-TI/ppl-ec-2024-1-p1-liec-t1-g2-jogo-da-velha/blob/master/Manual/README.md).

## Estrutura do Código

O código-fonte está organizado da seguinte maneira:

- **src/**: contém os arquivos de código-fonte em C/C++.
  - `io.c`: implementa as funções para controle dos LEDs e leitura dos botões.
  - `player.c`: implementa a lógica da IA para diferentes níveis de dificuldade.
- **include/**: contém os arquivos de cabeçalho.
  - `board.h`: define as funções básicas do tabuleiro.
  - `io.h`: define as funções de entrada/saída.
  - `player.h`: define as funções da IA.
  - `settings.h`: define as estruturas e funções de configuração do jogo.

## Referências

Para mais detalhes sobre o desenvolvimento do projeto, consulte a
[documentação completa](https://github.com/ICEI-PUC-Minas-EC-TI/ppl-ec-2024-1-p1-liec-t1-g2-jogo-da-velha/tree/master/Documentacao).

## Créditos

Este projeto foi desenvolvido por:

- Amanda Canizela Guimarães
- Antonella de Paula Menegaz
- Felipe de Faria Rios Coelho
- Lucas Alvarenga Fernandes
- Lucca Mendes Alves Pellegrini

Orientador:

- Felipe Augusto Lara Soares

Para mais informações, consulte o
[repositório principal](https://github.com/ICEI-PUC-Minas-EC-TI/ppl-ec-2024-1-p1-liec-t1-g2-jogo-da-velha).
