Semáforo com Temporizador no Raspberry Pi Pico W

link para o video: https://drive.google.com/file/d/1hdOqYet4HdC4O0jyTZuc2V4fvUa9MyR3/view?usp=drive_link

Este projeto implementa um sistema de semáforo utilizando um Raspberry Pi Pico W e LEDs para simular as cores vermelho, amarelo e verde. A troca das cores ocorre automaticamente em um intervalo fixo de 3 segundos, seguindo a sequência convencional de um semáforo de trânsito.

Funcionamento do Código

O código controla três LEDs representando as cores do semáforo. Um temporizador de repetição (Repeating Timer) alterna entre as cores a cada 3 segundos, seguindo a sequência:
	
 1.	Vermelho aceso – Indica “Pare”
	
 2.	Amarelo aceso – Indica “Atenção”

 3.	Verde aceso – Indica “Siga”

Cada vez que o temporizador ativa, ele apaga todos os LEDs e acende o próximo da sequência. Esse ciclo se repete indefinidamente.

Além disso, mensagens são enviadas via porta serial a cada segundo, indicando o estado atual do semáforo.

Componentes Utilizados

 •	Raspberry Pi Pico W

 •	3 LEDs:

 •	Vermelho conectado ao GPIO 11

 •	Amarelo conectado ao GPIO 12

 •	Verde conectado ao GPIO 13

 •	3 Resistores de 330Ω (limitadores de corrente para os LEDs)

Desenvolvimento do Código

O código é estruturado em três partes principais:


1. Configuração dos Pinos

Os LEDs são configurados como saídas, permitindo que sejam ligados e desligados pelo programa. Cada LED é inicializado com o estado desligado.


2. Controle do Semáforo com Temporizador

Um temporizador de repetição (repeating timer) é configurado para acionar a função de troca do semáforo a cada 3 segundos. Essa função desliga todos os LEDs e acende o próximo conforme a sequência correta.


3. Loop Principal

O loop principal mantém o sistema em execução, exibindo mensagens na saída serial a cada 1 segundo, informando que o sistema está ativo e aguardando a próxima troca do semáforo.

Execução do Programa

Após carregar o código no Raspberry Pi Pico W, o sistema começa com o LED vermelho aceso. A cada 3 segundos, ele alterna para o amarelo e, em seguida, para o verde, antes de voltar ao vermelho, repetindo esse ciclo continuamente. As mensagens na porta serial indicam o estado atual do semáforo.
