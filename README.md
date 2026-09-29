# Projeto P4 - Um Problema, Quatro Paradigmas

## [P4-ETAPA-01] Proposta e especificacao do problema

**Aluno:** Matheus Santana Silva  
**Problema escolhido:** Sistema de Gerenciamento de Irrigacao Inteligente

Este projeto tem como objetivo estudar diferentes formas de resolver um mesmo problema por meio dos paradigmas imperativo, orientado a objetos, funcional e logico.

O problema escolhido consiste em decidir quando um sistema de irrigacao deve iniciar, continuar ou interromper o fornecimento de agua, considerando a umidade do solo, os limites configurados, o estado do sensor e os comandos de controle.

Nesta primeira etapa, o projeto apresenta somente a especificacao do problema. Ainda nao ha implementacao em codigo.

## [P4-ETAPA-02] Contrato semantico e testes

A segunda etapa transforma a especificacao inicial em um contrato de comportamento independente de linguagem e paradigma. Esse contrato define entradas, saidas, prioridades e resultados esperados para que as quatro implementacoes futuras possam ser avaliadas pelos mesmos criterios.

Foram definidos:

- 10 casos normais;
- 4 casos-limite;
- 3 casos de entrada invalida.

## [P4-ETAPA-03] Implementacao imperativa

A terceira etapa implementa o contrato semantico em C++ utilizando predominantemente o paradigma imperativo. O fluxo de decisao e explicito, o estado do sistema e mutavel e a solucao e organizada em subprogramas, sem classes ou hierarquias orientadas a objetos.

A pasta `imperativo/` contem:

- programa interativo;
- regras de avaliacao;
- tipos e subprogramas;
- testes automatizados dos 17 casos da Etapa 02;
- documentacao das decisoes de implementacao.

## Documentos da Etapa 01

- `docs/especificacao.md`: especificacao completa do problema;
- `docs/contrato-semantico.md`: contrato de comportamento da Etapa 02;
- `testes/casos.md`: exemplos de execucao e casos-limite.
- `imperativo/`: implementacao imperativa em C++ e validacao automatizada.

## Paradigmas previstos

1. Programacao imperativa;
2. Programacao orientada a objetos;
3. Programacao funcional;
4. Programacao logica.

## Linguagens inicialmente consideradas

- Imperativo: C++;
- Orientado a objetos: C++;
- Funcional: Haskell;
- Logico: Prolog.
