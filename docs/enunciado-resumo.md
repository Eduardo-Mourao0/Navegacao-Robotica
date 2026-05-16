# TP02 - Navegacao Robotica: resumo do enunciado

## Objetivo

Implementar, em linguagem C, um sistema para armazenar, processar, analisar e calcular metricas de trajetorias de um robo em plano cartesiano usando listas encadeadas com ponteiros.

O robo comeca em uma posicao inicial `(xInicial, yInicial)` e executa uma sequencia de comandos unitarios:

- `N`: move de `(x, y)` para `(x, y + 1)`.
- `S`: move de `(x, y)` para `(x, y - 1)`.
- `L`: move de `(x, y)` para `(x + 1, y)`.
- `O`: move de `(x, y)` para `(x - 1, y)`.

## Estruturas obrigatorias

O trabalho define tres estruturas principais no arquivo `caminho.h`, que nao pode ser modificado:

```c
typedef struct Comando {
    char Direcao;
    struct Comando* Proximo;
} Comando;

typedef struct Posicao {
    int X;
    int Y;
    struct Posicao* Proximo;
} Posicao;

typedef struct Caminho {
    Posicao* Inicio;
    Posicao* Fim;
    Posicao* Historico;
    Comando* Instrucoes;
    int N;
} Caminho;
```

## Funcoes obrigatorias

```c
Caminho* InicializarCaminho(const char* Sequencia, int xInicial, int yInicial);
void DestruirCaminho(Caminho* C);
Posicao* DeterminarFim(Caminho* C);
Posicao* HistoricoPosicoes(Caminho* C);
int CalcularDistanciaTotal(Caminho* C);
double CalcularDistanciaGeometrica(Caminho* C);
int CalcularDistanciaManhattan(Caminho* C);
int ContarInstrucoes(Caminho* C);
```

## Regras de erro

- Comandos invalidos devem ser tratados dentro de `InicializarCaminho`.
- Se houver comando invalido, `InicializarCaminho` deve retornar `NULL`.
- Funcoes que retornam ponteiro devem retornar `NULL` em caso de problema.
- Funcoes que retornam `int` devem retornar `-1` em caso de problema.
- Funcoes que retornam `double` devem retornar `-1.0` em caso de problema.

## Restricoes

- Nao usar vetores para armazenar comandos ou historico de posicoes.
- Usar listas encadeadas e alocacao dinamica.
- O codigo deve compilar com GCC em Windows.
- O arquivo `caminho.h` deve ser usado sem modificacoes.
- A entrega deve ser um unico arquivo `.c`, nao compactado.
- O nome do arquivo entregue deve ser formado pelos digitos da matricula. Exemplo: `26209999.c`.
- A correcao automatica usara algo no formato:

```powershell
gcc 26209999.c main.c -o robo.exe
```

## Exemplo do enunciado

Entrada:

```c
InicializarCaminho("LLLLLLLNNNNN", 2, 2);
```

Resultado esperado:

- Inicio: `(2, 2)`
- Fim: `(9, 7)`
- Historico: `(2, 2) -> (3, 2) -> ... -> (9, 7)`
- Distancia total: `12`
- Distancia geometrica: `sqrt((9 - 2)^2 + (7 - 2)^2) = 8.60`
- Distancia de Manhattan: `|9 - 2| + |7 - 2| = 12`
- Quantidade de instrucoes: `12`

## Criterios de avaliacao

- Funcionamento correto de todas as funcoes.
- Uso correto de alocacao dinamica.
- Manipulacao correta de ponteiros e encadeamentos.
- Compatibilidade com `caminho.h`.
- Uso adequado de listas encadeadas.
- Ausencia de vazamentos de memoria e liberacoes indevidas.
- Tratamento de erros e comandos invalidos.
- Organizacao, legibilidade e indentacao.
- Compatibilidade com GCC.
- Respeito as restricoes do enunciado.

## Decisoes de implementacao propostas

- Construir a lista de comandos e a lista de historico dentro de `InicializarCaminho`.
- Fazer `Inicio` apontar para o primeiro no da lista `Historico`.
- Fazer `Fim` apontar para o ultimo no da lista `Historico`.
- Fazer `DeterminarFim` retornar `C->Fim`.
- Fazer `HistoricoPosicoes` retornar `C->Historico`.
- Fazer `ContarInstrucoes` retornar `C->N`.
- Fazer `CalcularDistanciaTotal` retornar `C->N`, pois cada comando valido tem deslocamento unitario.
- Em `DestruirCaminho`, liberar a lista `Historico`, a lista `Instrucoes` e depois a struct `C`.
- Evitar liberar `Inicio` e `Fim` separadamente, pois eles devem ser apenas referencias para nos dentro de `Historico`.

## Casos de teste importantes

- Sequencia valida simples: `"N"`, `"S"`, `"L"`, `"O"`.
- Exemplo do enunciado: `"LLLLLLLNNNNN"` a partir de `(2, 2)`.
- Sequencia com movimentos que se cancelam: `"NSLO"` a partir de `(0, 0)`.
- Sequencia vazia: `""`, se aceitarmos como caminho sem deslocamento.
- Sequencia invalida: `"NLX"` deve retornar `NULL`.
- Ponteiro de caminho `NULL` passado para funcoes auxiliares.
- Coordenadas iniciais negativas.
