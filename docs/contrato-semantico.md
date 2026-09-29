# [P4-ETAPA-02] Contrato semantico do sistema

## 1. Finalidade

Este contrato define o comportamento observavel do Sistema de Gerenciamento de Irrigacao Inteligente. Ele estabelece quais dados o sistema recebe, quais resultados deve produzir e qual regra prevalece quando mais de uma condicao ocorre ao mesmo tempo.

O contrato nao determina classes, funcoes, estruturas, bibliotecas ou algoritmos. Todas as implementacoes futuras deverao produzir os mesmos resultados para as mesmas entradas, independentemente da linguagem ou do paradigma utilizado.

## 2. Entradas do contrato

| Campo | Dominio permitido | Significado |
|---|---|---|
| `umidade` | Numero entre 0 e 100, inclusive | Percentual de umidade do solo |
| `limite_inicio` | Numero entre 0 e 100, inclusive | Valor em que a irrigacao deve iniciar |
| `limite_interrupcao` | Numero entre 0 e 100, inclusive | Valor em que a irrigacao deve parar |
| `sensor` | `NORMAL` ou `FALHA` | Condicao do sensor de umidade |
| `sistema_habilitado` | `SIM` ou `NAO` | Permissao do usuario para funcionamento |
| `estado_anterior` | `PARADO`, `IRRIGANDO` ou `FALHA_SENSOR` | Estado antes da avaliacao atual |
| `reinicializar` | `SIM` ou `NAO` | Pedido de recuperacao apos falha |

## 3. Saidas do contrato

| Campo | Valores previstos | Significado |
|---|---|---|
| `resultado` | `SUCESSO`, `FALHA_SENSOR` ou `ENTRADA_INVALIDA` | Classificacao da avaliacao |
| `estado_resultante` | `PARADO`, `IRRIGANDO` ou `FALHA_SENSOR` | Estado depois da avaliacao |
| `acao_valvula` | `ABRIR`, `MANTER_ABERTA`, `FECHAR` ou `MANTER_FECHADA` | Acao esperada sobre o fluxo de agua |
| `mensagem` | Texto explicativo | Motivo do resultado produzido |

## 4. Precondicoes

Para uma avaliacao operacional valida:

1. `umidade`, `limite_inicio` e `limite_interrupcao` devem pertencer ao intervalo de 0 a 100.
2. `limite_inicio` deve ser estritamente menor que `limite_interrupcao`.
3. Os campos enumerados devem possuir um dos valores previstos neste contrato.

Se alguma precondicao nao for atendida, o resultado sera `ENTRADA_INVALIDA`, o estado resultante sera `PARADO`, a acao sera `FECHAR` e nenhuma regra operacional de irrigacao sera aplicada.

## 5. Ordem de prioridade

As regras deverao ser avaliadas nesta ordem conceitual:

1. validar as entradas e os limites;
2. verificar a existencia de falha no sensor;
3. verificar se o sistema esta habilitado;
4. tratar a permanencia ou recuperacao do estado de falha;
5. comparar a umidade com os limites;
6. considerar o estado anterior quando a umidade estiver entre os limites.

Essa prioridade faz parte do comportamento esperado. Uma implementacao pode utilizar outra organizacao interna, desde que produza o mesmo resultado observavel.

## 6. Regras de comportamento

### R01 Entrada invalida

Se qualquer entrada violar as precondicoes, o sistema devera produzir `ENTRADA_INVALIDA`, assumir `PARADO`, ordenar `FECHAR` e informar o motivo da rejeicao.

### R02 Falha do sensor

Se `sensor` for `FALHA`, o sistema devera produzir `FALHA_SENSOR`, assumir `FALHA_SENSOR` e ordenar `FECHAR`, independentemente da umidade informada.

### R03 Sistema desabilitado

Se `sistema_habilitado` for `NAO` e as entradas forem validas, o estado resultante sera `PARADO`. Se a irrigacao estava ativa, a acao sera `FECHAR`; caso contrario, sera `MANTER_FECHADA`.

### R04 Permanencia em falha

Se `estado_anterior` for `FALHA_SENSOR` e `reinicializar` for `NAO`, o sistema devera permanecer em `FALHA_SENSOR` e ordenar `FECHAR`, mesmo que o sensor ja esteja normal.

### R05 Recuperacao da falha

Se `estado_anterior` for `FALHA_SENSOR`, `reinicializar` for `SIM` e o sensor estiver normal, o sistema devera voltar a avaliar a umidade conforme as regras operacionais.

### R06 Inicio da irrigacao

Se o sistema estiver habilitado, sem falha, e `umidade` for menor ou igual a `limite_inicio`, o estado resultante sera `IRRIGANDO`. A acao sera `ABRIR` quando o estado anterior for `PARADO`, ou `MANTER_ABERTA` quando ja estiver `IRRIGANDO`.

### R07 Interrupcao da irrigacao

Se o sistema estiver habilitado, sem falha, e `umidade` for maior ou igual a `limite_interrupcao`, o estado resultante sera `PARADO`. A acao sera `FECHAR` quando o estado anterior for `IRRIGANDO`, ou `MANTER_FECHADA` quando ja estiver `PARADO`.

### R08 Faixa intermediaria

Se a umidade estiver acima do limite de inicio e abaixo do limite de interrupcao, o sistema preservara o estado operacional anterior:

- se estava `IRRIGANDO`, permanecera `IRRIGANDO` e usara `MANTER_ABERTA`;
- se estava `PARADO`, permanecera `PARADO` e usara `MANTER_FECHADA`.

## 7. Poscondicoes

Depois de uma avaliacao:

1. toda entrada valida produzira exatamente um estado resultante e uma acao de valvula;
2. nenhuma falha ou entrada invalida podera resultar em abertura da valvula;
3. `IRRIGANDO` somente podera ser combinado com `ABRIR` ou `MANTER_ABERTA`;
4. `PARADO` somente podera ser combinado com `FECHAR` ou `MANTER_FECHADA`;
5. `FALHA_SENSOR` sempre sera combinado com `FECHAR`;
6. a mensagem devera explicar a regra que determinou o resultado.

## 8. Independencia de implementacao

Os casos definidos em `testes/casos.md` constituem o criterio comum de aceitacao. As implementacoes imperativa, orientada a objetos, funcional e logica poderao organizar os dados e o controle de maneiras diferentes, mas deverao respeitar este contrato e produzir as mesmas saidas esperadas.
