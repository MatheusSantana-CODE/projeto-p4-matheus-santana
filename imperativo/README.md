# [P4-ETAPA-03] Implementação imperativa

## 1. Visão geral

Esta pasta apresenta a implementação imperativa, em C++17, do Sistema de Gerenciamento de Irrigação Inteligente. A solução segue o contrato semântico definido na Etapa 02 e utiliza os mesmos 17 casos para validação.

A implementação evita classes, herança, polimorfismo e outras abstrações orientadas a objetos. O comportamento é expresso por variáveis, atribuições, condicionais, repetição, subprogramas e modificação explícita do estado.

## 2. Arquivos

| Arquivo | Finalidade |
|---|---|
| `irrigacao.h` | Tipos simples e declarações dos subprogramas |
| `irrigacao.cpp` | Validação, regras do contrato e conversões para texto |
| `main.cpp` | Programa interativo e manutenção do estado mutável |
| `testes.cpp` | Execução automatizada dos casos da Etapa 02 |
| `Makefile` | Comandos de compilação e teste |

## 3. Estados mantidos

O programa principal mantém as seguintes variáveis durante a execução:

- `estadoAtual`: situação atual da irrigação;
- `sistemaHabilitado`: permissão para funcionamento;
- `limiteInicio`: valor para iniciar a irrigação;
- `limiteInterrupcao`: valor para parar a irrigação;
- `executando`: controla a repetição do menu.

Esses valores podem mudar ao longo da execução. Por isso, representam o estado mutável do programa.

## 4. Operações que modificam estado

- O processamento de uma leitura atribui `saida.estadoResultante` a `estadoAtual`.
- A opção de configuração atribui novos valores aos limites.
- A opção de habilitação inverte o valor de `sistemaHabilitado`.
- A opção de encerramento modifica `executando` para terminar o laço principal.

## 5. Efeitos colaterais

Os efeitos colaterais aparecem principalmente em `main.cpp`:

- leitura de valores com `std::cin`;
- exibição de mensagens com `std::cout`;
- alteração das variáveis que representam o estado atual.

A função `avaliarIrrigacao` não realiza entrada ou saída. Ela recebe os dados por parâmetro e devolve uma estrutura com o resultado.

## 6. Estruturas de controle

- `while` mantém o programa ativo e valida respostas do usuário;
- `switch` seleciona a operação do menu e converte enumerações em texto;
- `if` e `else` aplicam a prioridade das regras do contrato;
- `for` percorre os casos de teste;
- retornos antecipados encerram a avaliação assim que uma regra prioritária é satisfeita.

## 7. Organização dos subprogramas

- `entradaValida`: verifica o domínio dos dados e a coerência dos limites;
- `avaliarIrrigacao`: aplica as regras na ordem de prioridade;
- `lerInteiro` e `lerSimNao`: tratam a entrada interativa;
- `exibirSaida` e `exibirMenu`: concentram a saída para o usuário;
- funções `...ParaTexto`: convertem valores enumerados em texto;
- `executarCaso`: compara uma saída obtida com o resultado esperado.

Os parâmetros evitam dependências desnecessárias de variáveis globais e tornam explícitos os dados utilizados por cada subprograma.

## 8. Por que a solução é imperativa

A solução descreve uma sequência de comandos que modifica variáveis ao longo do tempo. O fluxo é determinado por condicionais, repetições e atribuições, e o programa principal conserva um estado mutável entre as leituras. As regras são executadas em ordem explícita e os efeitos colaterais de entrada, saída e atualização de estado são visíveis.

Embora a linguagem C++ suporte orientação a objetos, essa implementação usa apenas recursos adequados ao modelo imperativo. As `structs` agrupam dados e não possuem métodos ou encapsulamento de comportamento.

## 9. Compilação

Dentro da pasta `imperativo`, execute:

```bash
make
```

Para abrir o programa interativo:

```bash
./irrigacao
```

Para executar os testes:

```bash
make test
```

Também é possível compilar manualmente:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp irrigacao.cpp -o irrigacao
g++ -std=c++17 -Wall -Wextra -pedantic testes.cpp irrigacao.cpp -o testes
./testes
```

## 10. Critério de validação

A implementação é considerada válida quando os 17 casos definidos em `testes/casos.md` forem aprovados. O executável de testes retorna código zero quando todos os casos passam e código diferente de zero quando algum resultado diverge do contrato.
