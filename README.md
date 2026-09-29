# Projeto P4 - Um Problema, Quatro Paradigmas

## [P4-ETAPA-01] Proposta e especificação do problema

**Aluno:** Matheus Santana Silva  
**Problema escolhido:** Sistema de Gerenciamento de Irrigação Inteligente

Este projeto tem como objetivo estudar diferentes formas de resolver um mesmo problema por meio dos paradigmas imperativo, orientado a objetos, funcional e lógico.

O problema escolhido consiste em decidir quando um sistema de irrigação deve iniciar, continuar ou interromper o fornecimento de água, considerando a umidade do solo, os limites configurados, o estado do sensor e os comandos de controle.

Nesta primeira etapa, o projeto apresenta somente a especificação do problema. Ainda não há implementação em código.

## [P4-ETAPA-02] Contrato semântico e testes

A segunda etapa transforma a especificação inicial em um contrato de comportamento independente de linguagem e paradigma. Esse contrato define entradas, saídas, prioridades e resultados esperados para que as quatro implementações futuras possam ser avaliadas pelos mesmos critérios.

Foram definidos:

- 10 casos normais;
- 4 casos-limite;
- 3 casos de entrada inválida.

## [P4-ETAPA-03] Implementação imperativa

A terceira etapa implementa o contrato semântico em C++ utilizando predominantemente o paradigma imperativo. O fluxo de decisão é explícito, o estado do sistema é mutável e a solução é organizada em subprogramas, sem classes ou hierarquias orientadas a objetos.

A pasta `imperativo/` contém:

- programa interativo;
- regras de avaliação;
- tipos e subprogramas;
- testes automatizados dos 17 casos da Etapa 02;
- documentação das decisões de implementação.

## Documentos da Etapa 01

- `docs/especificacao.md`: especificação completa do problema;
- `docs/contrato-semantico.md`: contrato de comportamento da Etapa 02;
- `testes/casos.md`: exemplos de execução e casos-limite.
- `imperativo/`: implementação imperativa em C++ e validação automatizada.

## Paradigmas previstos

1. Programação imperativa;
2. Programação orientada a objetos;
3. Programação funcional;
4. Programação lógica.

## Linguagens inicialmente consideradas

- Imperativo: C++;
- Orientado a objetos: C++;
- Funcional: Haskell;
- Lógico: Prolog.
