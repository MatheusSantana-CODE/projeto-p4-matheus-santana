# [P4-ETAPA-01] Proposta e especificação do problema

## Sistema de Gerenciamento de Irrigação Inteligente

## 1. Descrição do problema

A irrigação de jardins, hortas e pequenas áreas de cultivo pode desperdiçar água quando é realizada sem considerar a umidade real do solo. Também pode ocorrer falta de irrigação quando o solo está seco, prejudicando o desenvolvimento das plantas.

O problema proposto consiste em gerenciar a irrigação de uma área com base nas leituras de umidade do solo. O sistema deverá analisar a leitura recebida, comparar esse valor com limites previamente definidos e decidir se a irrigação deve ser iniciada, mantida ou interrompida.

O sistema também deverá considerar comandos de controle e possíveis falhas do sensor. Quando uma leitura for inválida ou o sensor estiver com defeito, o fornecimento de água deverá ser interrompido e a falha deverá ser informada. Dessa forma, a solução busca utilizar a água de maneira mais racional e proporcionar um comportamento seguro e previsível.

## 2. Objetivo

O objetivo é gerenciar o funcionamento de um sistema de irrigação a partir da umidade do solo e das regras definidas pelo usuário.

O sistema deverá ser capaz de:

- receber uma leitura de umidade do solo;
- verificar se a leitura é válida;
- comparar a umidade com os limites configurados;
- iniciar a irrigação quando o solo estiver seco;
- manter a irrigação enquanto a umidade permanecer abaixo do limite de desligamento;
- interromper a irrigação quando o solo atingir umidade suficiente;
- respeitar comandos de ativação e desligamento;
- identificar e informar falhas do sensor;
- indicar o estado atual da irrigação e da válvula;
- registrar o resultado de cada avaliação.

## 3. Entradas

O sistema receberá os seguintes dados:

1. **Umidade do solo:** valor percentual entre 0 e 100.
2. **Limite para iniciar a irrigação:** percentual abaixo do qual o solo será considerado seco.
3. **Limite para interromper a irrigação:** percentual a partir do qual a umidade será considerada suficiente.
4. **Estado do sensor:** indica se o sensor está funcionando normalmente ou se apresenta falha.
5. **Estado de habilitação:** indica se o sistema está habilitado ou desligado pelo usuário.
6. **Comando de reinicialização:** solicita a recuperação do sistema depois de uma falha.
7. **Estado anterior da irrigação:** informa se, antes da avaliação atual, a irrigação estava ativa ou parada.

## 4. Saídas

O sistema deverá produzir:

1. **Estado da irrigação:** parada, irrigando ou falha de sensor.
2. **Ação sobre a válvula:** abrir, manter aberta, fechar ou manter fechada.
3. **Mensagem de resultado:** explicação da decisão tomada.
4. **Alerta de erro:** aviso quando a entrada for inválida ou o sensor apresentar falha.
5. **Registro da avaliação:** um resumo contendo as entradas válidas e a decisão produzida.

## 5. Regras do problema

1. A umidade do solo deve estar entre 0% e 100%, inclusive.
2. Os dois limites de umidade também devem estar entre 0% e 100%.
3. O limite para iniciar a irrigação deve ser menor que o limite para interrompê-la.
4. Se o sistema estiver desligado pelo usuário, a irrigação deverá permanecer parada e a válvula fechada.
5. Se o sensor apresentar falha, o sistema deverá entrar no estado de falha e fechar a válvula.
6. Uma leitura inválida não poderá ser utilizada para decidir pela abertura da válvula.
7. Se o sistema estiver habilitado, o sensor estiver normal e a umidade for menor ou igual ao limite de início, a irrigação deverá ser iniciada.
8. Depois de iniciada, a irrigação deverá continuar enquanto a umidade permanecer abaixo do limite de interrupção.
9. Quando a umidade for maior ou igual ao limite de interrupção, a irrigação deverá ser interrompida.
10. Se a irrigação estiver parada e a umidade estiver entre os dois limites, ela deverá permanecer parada.
11. Se a irrigação já estiver ativa e a umidade estiver entre os dois limites, ela deverá permanecer ativa.
12. A diferença entre os limites evita que a válvula fique abrindo e fechando repetidamente quando a umidade estiver próxima de um único valor de referência.
13. O sistema somente poderá sair do estado de falha depois de receber um comando de reinicialização e confirmar que o sensor voltou ao funcionamento normal.
14. Toda avaliação válida deverá informar o estado resultante e a ação correspondente sobre a válvula.

## 6. Casos de exemplo

Para todos os exemplos abaixo, considere limite de início igual a 30% e limite de interrupção igual a 50%, exceto quando outro valor for informado.

| Caso | Entradas | Saída esperada |
|---|---|---|
| 1 | Umidade 20%; sensor normal; sistema habilitado; irrigação parada | Estado `IRRIGANDO`; abrir a válvula; informar que o solo está seco |
| 2 | Umidade 40%; sensor normal; sistema habilitado; irrigação ativa | Estado `IRRIGANDO`; manter a válvula aberta |
| 3 | Umidade 40%; sensor normal; sistema habilitado; irrigação parada | Estado `PARADO`; manter a válvula fechada |
| 4 | Umidade 55%; sensor normal; sistema habilitado; irrigação ativa | Estado `PARADO`; fechar a válvula; informar que a umidade é suficiente |
| 5 | Umidade 25%; sensor com falha; sistema habilitado; irrigação ativa | Estado `FALHA_SENSOR`; fechar a válvula e emitir alerta |
| 6 | Umidade 15%; sensor normal; sistema desligado; irrigação parada | Estado `PARADO`; manter a válvula fechada |
| 7 | Umidade 30%; sensor normal; sistema habilitado; irrigação parada | Estado `IRRIGANDO`; abrir a válvula |
| 8 | Umidade 50%; sensor normal; sistema habilitado; irrigação ativa | Estado `PARADO`; fechar a válvula |

## 7. Casos-limite

1. **Umidade exatamente igual ao limite de início:** a irrigação deverá ser iniciada quando estiver parada.
2. **Umidade exatamente igual ao limite de interrupção:** a irrigação deverá ser interrompida quando estiver ativa.
3. **Umidade fora do intervalo permitido:** valores menores que 0% ou maiores que 100% deverão gerar erro e manter a válvula fechada.
4. **Limites inconsistentes:** se o limite de início for maior ou igual ao limite de interrupção, a configuração deverá ser rejeitada.
5. **Falha durante a irrigação:** a válvula deverá ser fechada imediatamente e o sistema deverá assumir o estado de falha.
6. **Reinicialização com sensor ainda defeituoso:** o sistema deverá continuar no estado de falha.

## 8. Restrições

Estão fora do escopo desta versão do projeto:

- controlar equipamentos físicos reais;
- determinar automaticamente as necessidades específicas de cada espécie de planta;
- utilizar previsão meteorológica ou dados obtidos pela internet;
- controlar várias áreas independentes ao mesmo tempo;
- calcular consumo financeiro de água ou energia;
- cadastrar usuários, senhas ou permissões;
- desenvolver aplicativo para celular ou interface web;
- realizar manutenção física do sensor, da válvula ou da tubulação;
- garantir aplicação em ambientes agrícolas de grande escala.

As leituras e comandos poderão ser simulados durante as implementações acadêmicas.

## 9. Principais conceitos do domínio

- **Área irrigada:** local cujo solo será monitorado.
- **Umidade do solo:** quantidade percentual de umidade identificada.
- **Sensor de umidade:** origem da leitura utilizada na decisão.
- **Limite de início:** valor que caracteriza a necessidade de iniciar a irrigação.
- **Limite de interrupção:** valor que indica umidade suficiente.
- **Irrigação:** fornecimento controlado de água.
- **Válvula:** elemento cujo estado representa a liberação ou interrupção da água.
- **Estado do sistema:** situação atual, como parado, irrigando ou com falha.
- **Comando:** solicitação de habilitação, desligamento ou reinicialização.
- **Falha:** situação que impede o uso seguro da leitura do sensor.
- **Alerta:** informação produzida para comunicar uma falha ou entrada inválida.
- **Avaliação:** análise das entradas que produz uma decisão.
- **Registro:** resumo de uma avaliação e de seu resultado.

Nesta etapa, esses conceitos representam apenas elementos do problema. Eles ainda não são classes, estruturas ou objetos.

## 10. Adequação aos quatro paradigmas

### Programação imperativa

O problema pode ser expresso como uma sequência de verificações e comandos que alteram o estado da irrigação e da válvula. Essa abordagem permite observar claramente o fluxo de controle, as condições e as mudanças de estado.

### Programação orientada a objetos

O domínio possui conceitos com responsabilidades e comportamentos relacionados, como sensor, sistema de irrigação, configuração, avaliação e registro. Isso permite estudar organização, encapsulamento, comunicação entre objetos e separação de responsabilidades.

### Programação funcional

A decisão pode ser tratada como uma transformação de dados de entrada em um resultado, evitando alterações desnecessárias em dados existentes. Também será possível separar validação, decisão e produção das mensagens em funções independentes.

### Programação lógica

As condições de funcionamento podem ser representadas por fatos e regras. A partir de informações sobre umidade, sensor, configuração e estado anterior, uma consulta poderá determinar o estado esperado da irrigação.

Portanto, o problema permite reformular a solução segundo cada paradigma, em vez de apenas traduzir o mesmo programa entre linguagens.

## 11. Linguagens inicialmente consideradas

| Paradigma | Linguagem considerada | Justificativa inicial |
|---|---|---|
| Imperativo | C++ | Permite trabalhar diretamente com variáveis, decisões, repetições, funções e alterações de estado. Também é uma linguagem já conhecida pelo aluno. |
| Orientado a objetos | C++ | Possui suporte a classes, objetos, encapsulamento, composição e polimorfismo, permitindo reorganizar o problema conforme os princípios desse paradigma. |
| Funcional | Haskell | Favorece funções puras, imutabilidade, composição e declaração de transformações de dados. |
| Lógico | Prolog | Permite representar conhecimento por meio de fatos, regras e consultas, sendo adequado para expressar as condições de decisão do sistema. |

C++ é inicialmente considerada para duas etapas, mas as soluções imperativa e orientada a objetos deverão possuir modelagens próprias. A versão orientada a objetos não será apenas uma cópia da solução imperativa dentro de uma classe.

## Conclusão da Etapa 01

A especificação define o comportamento esperado do Sistema de Gerenciamento de Irrigação Inteligente sem determinar antecipadamente sua implementação. O problema possui entradas, saídas, regras, estados e situações de exceção suficientes para ser estudado nos quatro paradigmas durante o semestre.
