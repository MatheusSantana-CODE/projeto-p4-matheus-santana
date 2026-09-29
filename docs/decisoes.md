# Decisoes do projeto

## [P4-ETAPA-01]

1. O projeto tratara apenas uma area irrigada por vez para manter o escopo adequado a disciplina.
2. Serao utilizados dois limites de umidade para impedir alternancias frequentes da valvula.
3. Em qualquer falha de sensor ou entrada invalida, a decisao segura sera manter a valvula fechada.
4. C++ foi considerada para as abordagens imperativa e orientada a objetos, mas cada solucao devera respeitar as caracteristicas do paradigma correspondente.
5. A Etapa 01 nao incluira codigo-fonte, pois seu objetivo e especificar o comportamento esperado.

## [P4-ETAPA-02]

1. O contrato utiliza os mesmos dados e limites definidos na Etapa 01.
2. A validacao das entradas possui prioridade sobre as regras operacionais.
3. Falha de sensor, sistema desabilitado e recuperacao de falha possuem comportamentos explicitos para impedir resultados ambiguos.
4. As saidas observaveis foram padronizadas em resultado, estado resultante, acao da valvula e mensagem.
5. Foram criados 10 casos normais, 4 casos-limite e 3 casos de entrada invalida.
6. Os mesmos casos deverao ser utilizados nas quatro implementacoes futuras.

## [P4-ETAPA-03]

1. A implementacao imperativa utiliza C++17, linguagem considerada desde a Etapa 01.
2. Foram utilizadas estruturas simples e enumeracoes, sem classes, heranca ou polimorfismo.
3. O fluxo do contrato aparece explicitamente em atribuicoes, condicionais e retornos antecipados.
4. O estado atual da irrigacao e mantido em uma variavel mutavel no programa principal.
5. As operacoes de entrada e saida sao efeitos colaterais concentrados no programa principal.
6. A funcao de avaliacao recebe parametros e devolve o proximo estado e a acao da valvula.
7. Os 17 casos da Etapa 02 foram transformados em testes automatizados.
