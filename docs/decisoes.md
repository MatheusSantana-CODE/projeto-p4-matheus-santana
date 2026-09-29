# Decisões do projeto

## [P4-ETAPA-01]

1. O projeto tratará apenas uma área irrigada por vez para manter o escopo adequado à disciplina.
2. Serão utilizados dois limites de umidade para impedir alternâncias frequentes da válvula.
3. Em qualquer falha de sensor ou entrada inválida, a decisão segura será manter a válvula fechada.
4. C++ foi considerada para as abordagens imperativa e orientada a objetos, mas cada solução deverá respeitar as características do paradigma correspondente.
5. A Etapa 01 não incluirá código-fonte, pois seu objetivo é especificar o comportamento esperado.

## [P4-ETAPA-02]

1. O contrato utiliza os mesmos dados e limites definidos na Etapa 01.
2. A validação das entradas possui prioridade sobre as regras operacionais.
3. Falha de sensor, sistema desabilitado e recuperação de falha possuem comportamentos explícitos para impedir resultados ambíguos.
4. As saídas observáveis foram padronizadas em resultado, estado resultante, ação da válvula e mensagem.
5. Foram criados 10 casos normais, 4 casos-limite e 3 casos de entrada inválida.
6. Os mesmos casos deverão ser utilizados nas quatro implementações futuras.

## [P4-ETAPA-03]

1. A implementação imperativa utiliza C++17, linguagem considerada desde a Etapa 01.
2. Foram utilizadas estruturas simples e enumerações, sem classes, herança ou polimorfismo.
3. O fluxo do contrato aparece explicitamente em atribuições, condicionais e retornos antecipados.
4. O estado atual da irrigação é mantido em uma variável mutável no programa principal.
5. As operações de entrada e saída são efeitos colaterais concentrados no programa principal.
6. A função de avaliação recebe parâmetros e devolve o próximo estado e a ação da válvula.
7. Os 17 casos da Etapa 02 foram transformados em testes automatizados.
