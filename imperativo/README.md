# [P4-ETAPA-03] Implementacao imperativa

## 1. Visao geral

Esta pasta apresenta a implementacao imperativa, em C++17, do Sistema de Gerenciamento de Irrigacao Inteligente. A solucao segue o contrato semantico definido na Etapa 02 e utiliza os mesmos 17 casos para validacao.

A implementacao evita classes, heranca, polimorfismo e outras abstracoes orientadas a objetos. O comportamento e expresso por variaveis, atribuicoes, condicionais, repeticao, subprogramas e modificacao explicita do estado.

## 2. Arquivos

| Arquivo | Finalidade |
|---|---|
| `irrigacao.h` | Tipos simples e declaracoes dos subprogramas |
| `irrigacao.cpp` | Validacao, regras do contrato e conversoes para texto |
| `main.cpp` | Programa interativo e manutencao do estado mutavel |
| `testes.cpp` | Execucao automatizada dos casos da Etapa 02 |
| `Makefile` | Comandos de compilacao e teste |

## 3. Estados mantidos

O programa principal mantem as seguintes variaveis durante a execucao:

- `estadoAtual`: situacao atual da irrigacao;
- `sistemaHabilitado`: permissao para funcionamento;
- `limiteInicio`: valor para iniciar a irrigacao;
- `limiteInterrupcao`: valor para parar a irrigacao;
- `executando`: controla a repeticao do menu.

Esses valores podem mudar ao longo da execucao. Por isso, representam o estado mutavel do programa.

## 4. Operacoes que modificam estado

- O processamento de uma leitura atribui `saida.estadoResultante` a `estadoAtual`.
- A opcao de configuracao atribui novos valores aos limites.
- A opcao de habilitacao inverte o valor de `sistemaHabilitado`.
- A opcao de encerramento modifica `executando` para terminar o laco principal.

## 5. Efeitos colaterais

Os efeitos colaterais aparecem principalmente em `main.cpp`:

- leitura de valores com `std::cin`;
- exibicao de mensagens com `std::cout`;
- alteracao das variaveis que representam o estado atual.

A funcao `avaliarIrrigacao` nao realiza entrada ou saida. Ela recebe os dados por parametro e devolve uma estrutura com o resultado.

## 6. Estruturas de controle

- `while` mantem o programa ativo e valida respostas do usuario;
- `switch` seleciona a operacao do menu e converte enumeracoes em texto;
- `if` e `else` aplicam a prioridade das regras do contrato;
- `for` percorre os casos de teste;
- retornos antecipados encerram a avaliacao assim que uma regra prioritaria e satisfeita.

## 7. Organizacao dos subprogramas

- `entradaValida`: verifica o dominio dos dados e a coerencia dos limites;
- `avaliarIrrigacao`: aplica as regras na ordem de prioridade;
- `lerInteiro` e `lerSimNao`: tratam a entrada interativa;
- `exibirSaida` e `exibirMenu`: concentram a saida para o usuario;
- funcoes `...ParaTexto`: convertem valores enumerados em texto;
- `executarCaso`: compara uma saida obtida com o resultado esperado.

Os parametros evitam dependencias desnecessarias de variaveis globais e tornam explicitos os dados utilizados por cada subprograma.

## 8. Por que a solucao e imperativa

A solucao descreve uma sequencia de comandos que modifica variaveis ao longo do tempo. O fluxo e determinado por condicionais, repeticoes e atribuicoes, e o programa principal conserva um estado mutavel entre as leituras. As regras sao executadas em ordem explicita e os efeitos colaterais de entrada, saida e atualizacao de estado sao visiveis.

Embora a linguagem C++ suporte orientacao a objetos, essa implementacao usa apenas recursos adequados ao modelo imperativo. As `structs` agrupam dados e nao possuem metodos ou encapsulamento de comportamento.

## 9. Compilacao

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

Tambem e possivel compilar manualmente:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp irrigacao.cpp -o irrigacao
g++ -std=c++17 -Wall -Wextra -pedantic testes.cpp irrigacao.cpp -o testes
./testes
```

## 10. Criterio de validacao

A implementacao e considerada valida quando os 17 casos definidos em `testes/casos.md` forem aprovados. O executavel de testes retorna codigo zero quando todos os casos passam e codigo diferente de zero quando algum resultado diverge do contrato.

