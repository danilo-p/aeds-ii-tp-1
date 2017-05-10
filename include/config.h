#ifndef CONFIG_H
#define CONFIG_H

// Quantidade de filas de ficha
extern int CHECKOUT_QUEUE_AMOUNT;
// Quantidade máxima de pessoas nas filas de ficha (negativa significa sem
// limite)
extern int CHECKOUT_QUEUE_SIZE;
// Tempo gasto no caixa     
extern int CHECKOUT_DELAY;
// Quantidade de filas de bandeja
extern int TRAY_QUEUE_AMOUNT;
// Quantidade máxima de pessoas nas filas de bandeja (negativa significa sem
// limite)
extern int TRAY_QUEUE_SIZE;
// Quantidade de pilhas de bandeja
extern int TRAY_STACK_AMOUNT;
// Tamanho da pilha de bandeja
extern int TRAY_STACK_SIZE;
// Quantidade de bandejas repostas nas pilhas a cada intervalo
extern int TRAY_REFILL_AMOUNT;
// Intervalo de reposição de bandejas
extern int TRAY_REFILL_INTERVAL;
// Intervalo de chegada de novos usuários
extern int USER_ARRIVAL_INTERVAL;
// Quantidade de usuários que chegam a cada intervalo
extern int USER_REFILL_AMOUNT;
// Tempo gasto para pegar uma bandeja
extern int TRAY_DELAY;
// Tempo gasto para servir um tipo de comida
extern int FOOD_DELAY;
// Tempo da simulação
extern int DURATION;

#endif