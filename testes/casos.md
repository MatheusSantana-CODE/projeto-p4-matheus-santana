# [P4-ETAPA-01] Casos de exemplo e casos-limite

Este documento organiza os cenarios que servirao como referencia para as implementacoes futuras.

## Configuracao padrao

- Limite para iniciar: 30%;
- Limite para interromper: 50%;
- Sistema habilitado;
- Sensor normal, exceto quando indicado de outra forma.

## Exemplos de comportamento

| ID | Umidade | Estado anterior | Condicao especial | Estado esperado | Valvula esperada |
|---|---:|---|---|---|---|
| CE01 | 20% | Parado | Nenhuma | Irrigando | Aberta |
| CE02 | 40% | Irrigando | Nenhuma | Irrigando | Aberta |
| CE03 | 40% | Parado | Nenhuma | Parado | Fechada |
| CE04 | 55% | Irrigando | Nenhuma | Parado | Fechada |
| CE05 | 25% | Irrigando | Falha do sensor | Falha do sensor | Fechada |
| CE06 | 15% | Parado | Sistema desligado | Parado | Fechada |
| CE07 | 30% | Parado | Igual ao limite de inicio | Irrigando | Aberta |
| CE08 | 50% | Irrigando | Igual ao limite de interrupcao | Parado | Fechada |

## Casos-limite e entradas invalidas

| ID | Situacao | Resultado esperado |
|---|---|---|
| CL01 | Umidade igual a 0% | Leitura valida; iniciar irrigacao se o sistema estiver habilitado |
| CL02 | Umidade igual a 100% | Leitura valida; irrigacao parada e valvula fechada |
| CL03 | Umidade menor que 0% | Rejeitar leitura, informar erro e manter valvula fechada |
| CL04 | Umidade maior que 100% | Rejeitar leitura, informar erro e manter valvula fechada |
| CL05 | Limite de inicio igual ao limite de interrupcao | Rejeitar configuracao |
| CL06 | Limite de inicio maior que o limite de interrupcao | Rejeitar configuracao |
| CL07 | Sensor falha durante a irrigacao | Entrar em falha e fechar a valvula |
| CL08 | Reinicializacao com sensor ainda defeituoso | Permanecer no estado de falha |
| CL09 | Reinicializacao com sensor normal | Liberar nova avaliacao conforme a umidade recebida |

