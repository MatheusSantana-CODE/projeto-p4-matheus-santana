# [P4-ETAPA-01] Proposta e especificacao do problema

## Sistema de Gerenciamento de Irrigacao Inteligente

## 1. Descricao do problema

A irrigacao de jardins, hortas e pequenas areas de cultivo pode desperdiçar agua quando e realizada sem considerar a umidade real do solo. Tambem pode ocorrer falta de irrigacao quando o solo esta seco, prejudicando o desenvolvimento das plantas.

O problema proposto consiste em gerenciar a irrigacao de uma area com base nas leituras de umidade do solo. O sistema devera analisar a leitura recebida, comparar esse valor com limites previamente definidos e decidir se a irrigacao deve ser iniciada, mantida ou interrompida.

O sistema tambem devera considerar comandos de controle e possiveis falhas do sensor. Quando uma leitura for invalida ou o sensor estiver com defeito, o fornecimento de agua devera ser interrompido e a falha devera ser informada. Dessa forma, a solucao busca utilizar a agua de maneira mais racional e proporcionar um comportamento seguro e previsivel.

## 2. Objetivo

O objetivo e gerenciar o funcionamento de um sistema de irrigacao a partir da umidade do solo e das regras definidas pelo usuario.

O sistema devera ser capaz de:

- receber uma leitura de umidade do solo;
- verificar se a leitura e valida;
- comparar a umidade com os limites configurados;
- iniciar a irrigacao quando o solo estiver seco;
- manter a irrigacao enquanto a umidade permanecer abaixo do limite de desligamento;
- interromper a irrigacao quando o solo atingir umidade suficiente;
- respeitar comandos de ativacao e desligamento;
- identificar e informar falhas do sensor;
- indicar o estado atual da irrigacao e da valvula;
- registrar o resultado de cada avaliacao.

## 3. Entradas

O sistema recebera os seguintes dados:

1. **Umidade do solo:** valor percentual entre 0 e 100.
2. **Limite para iniciar a irrigacao:** percentual abaixo do qual o solo sera considerado seco.
3. **Limite para interromper a irrigacao:** percentual a partir do qual a umidade sera considerada suficiente.
4. **Estado do sensor:** indica se o sensor esta funcionando normalmente ou se apresenta falha.
5. **Estado de habilitacao:** indica se o sistema esta habilitado ou desligado pelo usuario.
6. **Comando de reinicializacao:** solicita a recuperacao do sistema depois de uma falha.
7. **Estado anterior da irrigacao:** informa se, antes da avaliacao atual, a irrigacao estava ativa ou parada.

## 4. Saidas

O sistema devera produzir:

1. **Estado da irrigacao:** parada, irrigando ou falha de sensor.
2. **Acao sobre a valvula:** abrir, manter aberta, fechar ou manter fechada.
3. **Mensagem de resultado:** explicacao da decisao tomada.
4. **Alerta de erro:** aviso quando a entrada for invalida ou o sensor apresentar falha.
5. **Registro da avaliacao:** um resumo contendo as entradas validas e a decisao produzida.

## 5. Regras do problema

1. A umidade do solo deve estar entre 0% e 100%, inclusive.
2. Os dois limites de umidade tambem devem estar entre 0% e 100%.
3. O limite para iniciar a irrigacao deve ser menor que o limite para interrompe-la.
4. Se o sistema estiver desligado pelo usuario, a irrigacao devera permanecer parada e a valvula fechada.
5. Se o sensor apresentar falha, o sistema devera entrar no estado de falha e fechar a valvula.
6. Uma leitura invalida nao podera ser utilizada para decidir pela abertura da valvula.
7. Se o sistema estiver habilitado, o sensor estiver normal e a umidade for menor ou igual ao limite de inicio, a irrigacao devera ser iniciada.
8. Depois de iniciada, a irrigacao devera continuar enquanto a umidade permanecer abaixo do limite de interrupcao.
9. Quando a umidade for maior ou igual ao limite de interrupcao, a irrigacao devera ser interrompida.
10. Se a irrigacao estiver parada e a umidade estiver entre os dois limites, ela devera permanecer parada.
11. Se a irrigacao ja estiver ativa e a umidade estiver entre os dois limites, ela devera permanecer ativa.
12. A diferenca entre os limites evita que a valvula fique abrindo e fechando repetidamente quando a umidade estiver proxima de um unico valor de referencia.
13. O sistema somente podera sair do estado de falha depois de receber um comando de reinicializacao e confirmar que o sensor voltou ao funcionamento normal.
14. Toda avaliacao valida devera informar o estado resultante e a acao correspondente sobre a valvula.

## 6. Casos de exemplo

Para todos os exemplos abaixo, considere limite de inicio igual a 30% e limite de interrupcao igual a 50%, exceto quando outro valor for informado.

| Caso | Entradas | Saida esperada |
|---|---|---|
| 1 | Umidade 20%; sensor normal; sistema habilitado; irrigacao parada | Estado `IRRIGANDO`; abrir a valvula; informar que o solo esta seco |
| 2 | Umidade 40%; sensor normal; sistema habilitado; irrigacao ativa | Estado `IRRIGANDO`; manter a valvula aberta |
| 3 | Umidade 40%; sensor normal; sistema habilitado; irrigacao parada | Estado `PARADO`; manter a valvula fechada |
| 4 | Umidade 55%; sensor normal; sistema habilitado; irrigacao ativa | Estado `PARADO`; fechar a valvula; informar que a umidade e suficiente |
| 5 | Umidade 25%; sensor com falha; sistema habilitado; irrigacao ativa | Estado `FALHA_SENSOR`; fechar a valvula e emitir alerta |
| 6 | Umidade 15%; sensor normal; sistema desligado; irrigacao parada | Estado `PARADO`; manter a valvula fechada |
| 7 | Umidade 30%; sensor normal; sistema habilitado; irrigacao parada | Estado `IRRIGANDO`; abrir a valvula |
| 8 | Umidade 50%; sensor normal; sistema habilitado; irrigacao ativa | Estado `PARADO`; fechar a valvula |

## 7. Casos-limite

1. **Umidade exatamente igual ao limite de inicio:** a irrigacao devera ser iniciada quando estiver parada.
2. **Umidade exatamente igual ao limite de interrupcao:** a irrigacao devera ser interrompida quando estiver ativa.
3. **Umidade fora do intervalo permitido:** valores menores que 0% ou maiores que 100% deverao gerar erro e manter a valvula fechada.
4. **Limites inconsistentes:** se o limite de inicio for maior ou igual ao limite de interrupcao, a configuracao devera ser rejeitada.
5. **Falha durante a irrigacao:** a valvula devera ser fechada imediatamente e o sistema devera assumir o estado de falha.
6. **Reinicializacao com sensor ainda defeituoso:** o sistema devera continuar no estado de falha.

## 8. Restricoes

Estao fora do escopo desta versao do projeto:

- controlar equipamentos fisicos reais;
- determinar automaticamente as necessidades especificas de cada especie de planta;
- utilizar previsao meteorologica ou dados obtidos pela internet;
- controlar varias areas independentes ao mesmo tempo;
- calcular consumo financeiro de agua ou energia;
- cadastrar usuarios, senhas ou permissoes;
- desenvolver aplicativo para celular ou interface web;
- realizar manutencao fisica do sensor, da valvula ou da tubulacao;
- garantir aplicacao em ambientes agricolas de grande escala.

As leituras e comandos poderao ser simulados durante as implementacoes academicas.

## 9. Principais conceitos do dominio

- **Area irrigada:** local cujo solo sera monitorado.
- **Umidade do solo:** quantidade percentual de umidade identificada.
- **Sensor de umidade:** origem da leitura utilizada na decisao.
- **Limite de inicio:** valor que caracteriza a necessidade de iniciar a irrigacao.
- **Limite de interrupcao:** valor que indica umidade suficiente.
- **Irrigacao:** fornecimento controlado de agua.
- **Valvula:** elemento cujo estado representa a liberacao ou interrupcao da agua.
- **Estado do sistema:** situacao atual, como parado, irrigando ou com falha.
- **Comando:** solicitacao de habilitacao, desligamento ou reinicializacao.
- **Falha:** situacao que impede o uso seguro da leitura do sensor.
- **Alerta:** informacao produzida para comunicar uma falha ou entrada invalida.
- **Avaliacao:** analise das entradas que produz uma decisao.
- **Registro:** resumo de uma avaliacao e de seu resultado.

Nesta etapa, esses conceitos representam apenas elementos do problema. Eles ainda nao sao classes, estruturas ou objetos.

## 10. Adequacao aos quatro paradigmas

### Programacao imperativa

O problema pode ser expresso como uma sequencia de verificacoes e comandos que alteram o estado da irrigacao e da valvula. Essa abordagem permite observar claramente o fluxo de controle, as condicoes e as mudancas de estado.

### Programacao orientada a objetos

O dominio possui conceitos com responsabilidades e comportamentos relacionados, como sensor, sistema de irrigacao, configuracao, avaliacao e registro. Isso permite estudar organizacao, encapsulamento, comunicacao entre objetos e separacao de responsabilidades.

### Programacao funcional

A decisao pode ser tratada como uma transformacao de dados de entrada em um resultado, evitando alteracoes desnecessarias em dados existentes. Tambem sera possivel separar validacao, decisao e producao das mensagens em funcoes independentes.

### Programacao logica

As condicoes de funcionamento podem ser representadas por fatos e regras. A partir de informacoes sobre umidade, sensor, configuracao e estado anterior, uma consulta podera determinar o estado esperado da irrigacao.

Portanto, o problema permite reformular a solucao segundo cada paradigma, em vez de apenas traduzir o mesmo programa entre linguagens.

## 11. Linguagens inicialmente consideradas

| Paradigma | Linguagem considerada | Justificativa inicial |
|---|---|---|
| Imperativo | C++ | Permite trabalhar diretamente com variaveis, decisoes, repeticoes, funcoes e alteracoes de estado. Tambem e uma linguagem ja conhecida pelo aluno. |
| Orientado a objetos | C++ | Possui suporte a classes, objetos, encapsulamento, composicao e polimorfismo, permitindo reorganizar o problema conforme os principios desse paradigma. |
| Funcional | Haskell | Favorece funcoes puras, imutabilidade, composicao e declaracao de transformacoes de dados. |
| Logico | Prolog | Permite representar conhecimento por meio de fatos, regras e consultas, sendo adequado para expressar as condicoes de decisao do sistema. |

C++ e inicialmente considerada para duas etapas, mas as solucoes imperativa e orientada a objetos deverao possuir modelagens proprias. A versao orientada a objetos nao sera apenas uma copia da solucao imperativa dentro de uma classe.

## Conclusao da Etapa 01

A especificacao define o comportamento esperado do Sistema de Gerenciamento de Irrigacao Inteligente sem determinar antecipadamente sua implementacao. O problema possui entradas, saidas, regras, estados e situacoes de excecao suficientes para ser estudado nos quatro paradigmas durante o semestre.

