# [P4-ETAPA-02] Contrato semantico e casos de teste

## 1. Finalidade

Este documento define casos de teste independentes de linguagem e paradigma para o Sistema de Gerenciamento de Irrigacao Inteligente. Os mesmos casos deverao ser aplicados as implementacoes imperativa, orientada a objetos, funcional e logica.

Salvo quando indicado de outra forma, os casos utilizam:

- `limite_inicio = 30`;
- `limite_interrupcao = 50`;
- `sensor = NORMAL`;
- `sistema_habilitado = SIM`;
- `reinicializar = NAO`.

Cada teste apresenta identificador, entrada, saida esperada e descricao, conforme solicitado na Etapa 02.

## 2. Casos normais

### CN01 Iniciar irrigacao com solo seco

- **Entrada:** umidade 20; estado anterior `PARADO`.
- **Saida esperada:** resultado `SUCESSO`; estado `IRRIGANDO`; acao `ABRIR`; mensagem informando que a umidade atingiu a faixa de inicio.
- **Descricao:** verifica se um solo abaixo do limite provoca o inicio da irrigacao.

### CN02 Manter irrigacao com solo ainda seco

- **Entrada:** umidade 25; estado anterior `IRRIGANDO`.
- **Saida esperada:** resultado `SUCESSO`; estado `IRRIGANDO`; acao `MANTER_ABERTA`; mensagem informando que a irrigacao deve continuar.
- **Descricao:** verifica se a valvula permanece aberta quando o solo ainda esta abaixo do limite de inicio.

### CN03 Permanecer parado na faixa intermediaria

- **Entrada:** umidade 40; estado anterior `PARADO`.
- **Saida esperada:** resultado `SUCESSO`; estado `PARADO`; acao `MANTER_FECHADA`; mensagem informando que o estado anterior foi preservado.
- **Descricao:** verifica a histerese quando a umidade esta entre os dois limites e o sistema estava parado.

### CN04 Continuar irrigando na faixa intermediaria

- **Entrada:** umidade 40; estado anterior `IRRIGANDO`.
- **Saida esperada:** resultado `SUCESSO`; estado `IRRIGANDO`; acao `MANTER_ABERTA`; mensagem informando que o estado anterior foi preservado.
- **Descricao:** verifica a histerese quando a umidade esta entre os limites e o sistema ja estava irrigando.

### CN05 Interromper irrigacao com umidade suficiente

- **Entrada:** umidade 60; estado anterior `IRRIGANDO`.
- **Saida esperada:** resultado `SUCESSO`; estado `PARADO`; acao `FECHAR`; mensagem informando que a umidade atingiu a faixa de interrupcao.
- **Descricao:** verifica se a irrigacao e interrompida quando o solo possui umidade suficiente.

### CN06 Manter valvula fechada com umidade suficiente

- **Entrada:** umidade 70; estado anterior `PARADO`.
- **Saida esperada:** resultado `SUCESSO`; estado `PARADO`; acao `MANTER_FECHADA`; mensagem informando que nao ha necessidade de irrigacao.
- **Descricao:** verifica se o sistema permanece parado quando o solo ja esta suficientemente umido.

### CN07 Desabilitar o sistema durante a irrigacao

- **Entrada:** umidade 20; estado anterior `IRRIGANDO`; sistema habilitado `NAO`.
- **Saida esperada:** resultado `SUCESSO`; estado `PARADO`; acao `FECHAR`; mensagem informando que o sistema foi desabilitado.
- **Descricao:** verifica se o comando do usuario prevalece sobre a necessidade de irrigar.

### CN08 Detectar falha durante a irrigacao

- **Entrada:** umidade 20; estado anterior `IRRIGANDO`; sensor `FALHA`.
- **Saida esperada:** resultado `FALHA_SENSOR`; estado `FALHA_SENSOR`; acao `FECHAR`; mensagem de falha do sensor.
- **Descricao:** verifica o comportamento seguro quando o sensor falha enquanto a valvula esta aberta.

### CN09 Recuperar falha e voltar a irrigar

- **Entrada:** umidade 20; estado anterior `FALHA_SENSOR`; sensor `NORMAL`; reinicializar `SIM`.
- **Saida esperada:** resultado `SUCESSO`; estado `IRRIGANDO`; acao `ABRIR`; mensagem informando que a falha foi encerrada e o solo requer irrigacao.
- **Descricao:** verifica a recuperacao de uma falha quando o sensor voltou ao normal e houve reinicializacao.

### CN10 Permanecer em falha sem reinicializacao

- **Entrada:** umidade 60; estado anterior `FALHA_SENSOR`; sensor `NORMAL`; reinicializar `NAO`.
- **Saida esperada:** resultado `FALHA_SENSOR`; estado `FALHA_SENSOR`; acao `FECHAR`; mensagem solicitando reinicializacao.
- **Descricao:** verifica se o sistema impede a retomada automatica depois de uma falha.

## 3. Casos-limite

### CL01 Umidade exatamente no limite de inicio

- **Entrada:** umidade 30; estado anterior `PARADO`.
- **Saida esperada:** resultado `SUCESSO`; estado `IRRIGANDO`; acao `ABRIR`; mensagem informando o inicio da irrigacao.
- **Descricao:** confirma que o limite de inicio e inclusivo.

### CL02 Umidade exatamente no limite de interrupcao

- **Entrada:** umidade 50; estado anterior `IRRIGANDO`.
- **Saida esperada:** resultado `SUCESSO`; estado `PARADO`; acao `FECHAR`; mensagem informando a interrupcao da irrigacao.
- **Descricao:** confirma que o limite de interrupcao e inclusivo.

### CL03 Menor umidade valida

- **Entrada:** umidade 0; limite de inicio 30; limite de interrupcao 50; estado anterior `PARADO`.
- **Saida esperada:** resultado `SUCESSO`; estado `IRRIGANDO`; acao `ABRIR`; mensagem informando que o solo requer irrigacao.
- **Descricao:** verifica o menor valor permitido para a leitura de umidade.

### CL04 Maior umidade valida

- **Entrada:** umidade 100; limite de inicio 30; limite de interrupcao 50; estado anterior `IRRIGANDO`.
- **Saida esperada:** resultado `SUCESSO`; estado `PARADO`; acao `FECHAR`; mensagem informando que a umidade e suficiente.
- **Descricao:** verifica o maior valor permitido para a leitura de umidade.

## 4. Casos de entrada invalida

### CI01 Umidade abaixo do dominio permitido

- **Entrada:** umidade -1; estado anterior `PARADO`.
- **Saida esperada:** resultado `ENTRADA_INVALIDA`; estado `PARADO`; acao `FECHAR`; mensagem informando que a umidade deve estar entre 0 e 100.
- **Descricao:** verifica a rejeicao de uma leitura menor que o valor minimo permitido.

### CI02 Umidade acima do dominio permitido

- **Entrada:** umidade 101; estado anterior `IRRIGANDO`.
- **Saida esperada:** resultado `ENTRADA_INVALIDA`; estado `PARADO`; acao `FECHAR`; mensagem informando que a umidade deve estar entre 0 e 100.
- **Descricao:** verifica a rejeicao de uma leitura maior que o valor maximo permitido.

### CI03 Limites inconsistentes

- **Entrada:** umidade 40; limite de inicio 50; limite de interrupcao 30; estado anterior `PARADO`.
- **Saida esperada:** resultado `ENTRADA_INVALIDA`; estado `PARADO`; acao `FECHAR`; mensagem informando que o limite de inicio deve ser menor que o limite de interrupcao.
- **Descricao:** verifica a rejeicao de uma configuracao cuja faixa de controle e impossivel.

## 5. Criterio geral de aprovacao

Uma implementacao sera considerada compativel com o contrato quando produzir, para todos os casos, o mesmo `resultado`, `estado_resultante` e `acao_valvula` definidos neste documento. O texto da mensagem pode variar, desde que comunique corretamente o motivo da decisao.
