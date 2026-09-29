# [P4-ETAPA-02] Contrato semântico do sistema

## 1. Finalidade

Este contrato define o comportamento observável do Sistema de Gerenciamento de Irrigação Inteligente. Ele estabelece quais dados o sistema recebe, quais resultados deve produzir e qual regra prevalece quando mais de uma condição ocorre ao mesmo tempo.

O contrato não determina classes, funções, estruturas, bibliotecas ou algoritmos. Todas as implementações futuras deverão produzir os mesmos resultados para as mesmas entradas, independentemente da linguagem ou do paradigma utilizado.

## 2. Entradas do contrato

| Campo | Domínio permitido | Significado |
|---|---|---|
| `umidade` | Número entre 0 e 100, inclusive | Percentual de umidade do solo |
| `limite_inicio` | Número entre 0 e 100, inclusive | Valor em que a irrigação deve iniciar |
| `limite_interrupcao` | Número entre 0 e 100, inclusive | Valor em que a irrigação deve parar |
| `sensor` | `NORMAL` ou `FALHA` | Condição do sensor de umidade |
| `sistema_habilitado` | `SIM` ou `NAO` | Permissão do usuário para funcionamento |
| `estado_anterior` | `PARADO`, `IRRIGANDO` ou `FALHA_SENSOR` | Estado antes da avaliação atual |
| `reinicializar` | `SIM` ou `NAO` | Pedido de recuperação após falha |

## 3. Saídas do contrato

| Campo | Valores previstos | Significado |
|---|---|---|
| `resultado` | `SUCESSO`, `FALHA_SENSOR` ou `ENTRADA_INVALIDA` | Classificação da avaliação |
| `estado_resultante` | `PARADO`, `IRRIGANDO` ou `FALHA_SENSOR` | Estado depois da avaliação |
| `acao_valvula` | `ABRIR`, `MANTER_ABERTA`, `FECHAR` ou `MANTER_FECHADA` | Ação esperada sobre o fluxo de água |
| `mensagem` | Texto explicativo | Motivo do resultado produzido |

## 4. Pré-condições

Para uma avaliação operacional válida:

1. `umidade`, `limite_inicio` e `limite_interrupcao` devem pertencer ao intervalo de 0 a 100.
2. `limite_inicio` deve ser estritamente menor que `limite_interrupcao`.
3. Os campos enumerados devem possuir um dos valores previstos neste contrato.

Se alguma pré-condição não for atendida, o resultado será `ENTRADA_INVALIDA`, o estado resultante será `PARADO`, a ação será `FECHAR` e nenhuma regra operacional de irrigação será aplicada.

## 5. Ordem de prioridade

As regras deverão ser avaliadas nesta ordem conceitual:

1. validar as entradas e os limites;
2. verificar a existência de falha no sensor;
3. verificar se o sistema está habilitado;
4. tratar a permanência ou recuperação do estado de falha;
5. comparar a umidade com os limites;
6. considerar o estado anterior quando a umidade estiver entre os limites.

Essa prioridade faz parte do comportamento esperado. Uma implementação pode utilizar outra organização interna, desde que produza o mesmo resultado observável.

## 6. Regras de comportamento

### R01 Entrada inválida

Se qualquer entrada violar as pré-condições, o sistema deverá produzir `ENTRADA_INVALIDA`, assumir `PARADO`, ordenar `FECHAR` e informar o motivo da rejeição.

### R02 Falha do sensor

Se `sensor` for `FALHA`, o sistema deverá produzir `FALHA_SENSOR`, assumir `FALHA_SENSOR` e ordenar `FECHAR`, independentemente da umidade informada.

### R03 Sistema desabilitado

Se `sistema_habilitado` for `NAO` e as entradas forem válidas, o estado resultante será `PARADO`. Se a irrigação estava ativa, a ação será `FECHAR`; caso contrário, será `MANTER_FECHADA`.

### R04 Permanência em falha

Se `estado_anterior` for `FALHA_SENSOR` e `reinicializar` for `NAO`, o sistema deverá permanecer em `FALHA_SENSOR` e ordenar `FECHAR`, mesmo que o sensor já esteja normal.

### R05 Recuperação da falha

Se `estado_anterior` for `FALHA_SENSOR`, `reinicializar` for `SIM` e o sensor estiver normal, o sistema deverá voltar a avaliar a umidade conforme as regras operacionais.

### R06 Início da irrigação

Se o sistema estiver habilitado, sem falha, e `umidade` for menor ou igual a `limite_inicio`, o estado resultante será `IRRIGANDO`. A ação será `ABRIR` quando o estado anterior for `PARADO`, ou `MANTER_ABERTA` quando já estiver `IRRIGANDO`.

### R07 Interrupção da irrigação

Se o sistema estiver habilitado, sem falha, e `umidade` for maior ou igual a `limite_interrupcao`, o estado resultante será `PARADO`. A ação será `FECHAR` quando o estado anterior for `IRRIGANDO`, ou `MANTER_FECHADA` quando já estiver `PARADO`.

### R08 Faixa intermediária

Se a umidade estiver acima do limite de início e abaixo do limite de interrupção, o sistema preservará o estado operacional anterior:

- se estava `IRRIGANDO`, permanecerá `IRRIGANDO` e usará `MANTER_ABERTA`;
- se estava `PARADO`, permanecerá `PARADO` e usará `MANTER_FECHADA`.

## 7. Pós-condições

Depois de uma avaliação:

1. toda entrada válida produzirá exatamente um estado resultante e uma ação de válvula;
2. nenhuma falha ou entrada inválida poderá resultar em abertura da válvula;
3. `IRRIGANDO` somente poderá ser combinado com `ABRIR` ou `MANTER_ABERTA`;
4. `PARADO` somente poderá ser combinado com `FECHAR` ou `MANTER_FECHADA`;
5. `FALHA_SENSOR` sempre será combinado com `FECHAR`;
6. a mensagem deverá explicar a regra que determinou o resultado.

## 8. Independência de implementação

Os casos definidos em `testes/casos.md` constituem o critério comum de aceitação. As implementações imperativa, orientada a objetos, funcional e lógica poderão organizar os dados e o controle de maneiras diferentes, mas deverão respeitar este contrato e produzir as mesmas saídas esperadas.
