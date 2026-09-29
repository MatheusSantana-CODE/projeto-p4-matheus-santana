# [P4-ETAPA-05] Comparação entre as implementações imperativa e orientada a objetos

**Aluno:** Matheus Santana Silva  
**Projeto:** Sistema de Gerenciamento de Irrigação Inteligente  
**Linguagem:** C++

## 1. Introdução

Esta etapa compara as implementações imperativa e orientada a objetos do Sistema de Gerenciamento de Irrigação Inteligente. A análise foi realizada com base no código efetivamente produzido nas pastas `imperativo` e `poo`.

As duas implementações seguem o mesmo contrato semântico. Elas recebem a leitura de umidade, os limites de início e interrupção, a condição do sensor, a habilitação do sistema, o estado anterior e o comando de reinicialização. Como resultado, ambas informam o estado da irrigação, a ação da válvula, o tipo de resultado e uma mensagem explicativa.

Os mesmos 17 casos de teste foram executados nas duas versões, incluindo 10 casos normais, 4 casos-limite e 3 casos de entrada inválida. Todos foram aprovados em ambas as implementações. Portanto, a mudança de paradigma alterou a organização interna do programa, mas preservou o comportamento definido para o sistema.

## 2. Comparação dos aspectos solicitados

### 2.1 Representação do estado

Na versão imperativa, o estado necessário para uma avaliação é agrupado na estrutura `EntradaIrrigacao`. O campo `estadoAnterior` precisa ser informado em cada chamada da função `avaliarIrrigacao`. O estado resultante é devolvido por meio da estrutura `SaidaIrrigacao`, mas a própria função não conserva informações entre chamadas.

Na versão orientada a objetos, o estado foi distribuído entre objetos. O `SensorUmidade` armazena a leitura e a condição de funcionamento; a `ValvulaIrrigacao` armazena se está aberta; e o `ControladorIrrigacao` conserva o estado operacional e a informação de habilitação. Assim, cada informação fica associada ao componente responsável por ela.

### 2.2 Mutabilidade

Na implementação imperativa, os dados da entrada são recebidos como referência constante. Durante a avaliação, a função cria e preenche uma variável local do tipo `SaidaIrrigacao`. Para representar uma nova execução, o chamador precisa montar outra entrada com o estado anterior atualizado.

Na implementação POO, os objetos são mutáveis de maneira controlada. O método `SensorUmidade::atualizar` modifica a leitura do sensor, `ValvulaIrrigacao::executar` altera o estado da válvula e os métodos `habilitar` e `desabilitar` alteram a condição do controlador. Os atributos são privados, portanto essas mudanças só podem ocorrer pelas operações públicas definidas pelas classes.

### 2.3 Fluxo de controle

O fluxo de controle das duas versões permanece baseado em uma sequência de decisões com retornos antecipados. Primeiro são verificadas as entradas inválidas; depois, a falha do sensor, a desabilitação do sistema, a necessidade de reinicialização e os limites de umidade.

Na versão imperativa, todo o fluxo está visível diretamente em `avaliarIrrigacao`. Na versão POO, a sequência principal está em `ControladorIrrigacao::processar`, mas a conclusão de cada decisão passa pelo método privado `concluir`, que atualiza o estado do controlador, executa a ação na válvula e cria o resultado.

### 2.4 Decomposição do problema

Na versão imperativa, a decomposição é feita principalmente por estruturas e funções. `EntradaIrrigacao` e `SaidaIrrigacao` agrupam dados, `entradaValida` verifica a entrada, `avaliarIrrigacao` aplica as regras e as funções de conversão produzem textos.

Na versão POO, o domínio foi dividido em classes com responsabilidades específicas. `ConfiguracaoLimites` representa e valida os limites; `SensorUmidade` representa a leitura; `ValvulaIrrigacao` aplica comandos; e `ControladorIrrigacao` coordena as regras do sistema. Essa decomposição aproxima a estrutura do código dos componentes do problema real.

### 2.5 Reutilização

As funções da versão imperativa podem ser reutilizadas sempre que uma `EntradaIrrigacao` for construída corretamente. Essa solução é simples e adequada para uma avaliação isolada, pois `avaliarIrrigacao` não depende de variáveis globais.

Na versão POO, as classes podem ser reutilizadas separadamente. O mesmo objeto `SensorUmidade` pode receber novas leituras, a válvula pode executar diferentes ações e o controlador pode processar vários ciclos preservando seu estado. Essa organização favorece a reutilização dos componentes em outras interfaces ou simulações.

### 2.6 Manutenção

Na versão imperativa, as regras estão concentradas em uma função, o que facilita localizar o algoritmo quando o sistema é pequeno. Entretanto, se forem adicionadas muitas responsabilidades, `avaliarIrrigacao` poderá crescer e concentrar detalhes de diferentes componentes.

Na versão POO, alterações específicas tendem a ficar na classe correspondente. Uma mudança na validação dos limites pode ser feita em `ConfiguracaoLimites`, enquanto uma mudança no comportamento físico da válvula pode ser tratada em `ValvulaIrrigacao`. O controlador continua responsável pelas decisões gerais. Essa separação reduz o impacto de determinadas alterações.

### 2.7 Facilidade de extensão

A implementação imperativa é fácil de ampliar quando a nova regra consiste apenas em acrescentar uma condição ao algoritmo. Porém, adicionar novos componentes e estados persistentes exigiria ampliar as estruturas e modificar a função central.

A implementação POO oferece uma base mais organizada para acrescentar histórico, registro de eventos, novas formas de configuração ou uma interface diferente. O projeto não utiliza herança nem polimorfismo, porque existe apenas um tipo de sensor e um tipo de válvula. Criar uma hierarquia sem necessidade aumentaria a complexidade. Se surgirem diferentes dispositivos com comportamentos próprios, esses recursos poderão ser avaliados futuramente.

### 2.8 Tratamento de erros

Na versão imperativa, a função `entradaValida` verifica a faixa de umidade, a faixa dos limites e a relação entre eles. Quando ocorre uma entrada inválida, `avaliarIrrigacao` devolve `ENTRADA_INVALIDA`, coloca o sistema em `PARADO` e determina o fechamento da válvula. A falha do sensor também leva a um estado seguro.

Na versão POO, `ConfiguracaoLimites::valida` verifica os limites e `ControladorIrrigacao::processar` verifica a umidade e o funcionamento do sensor. Em caso de erro, o método `concluir` centraliza a atualização para o estado seguro e o comando de fechamento. As duas versões adotam resultados explícitos em vez de exceções e mantêm a mesma prioridade das verificações.

### 2.9 Efeitos colaterais

Na versão imperativa, `avaliarIrrigacao` tem poucos efeitos colaterais: recebe uma entrada constante e devolve uma nova saída. O estado de objetos externos não é alterado. Isso torna o comportamento da função previsível.

Na versão POO, `ControladorIrrigacao::processar` possui efeitos colaterais intencionais. Ele modifica `estado_` e chama `ValvulaIrrigacao::executar`, que altera `aberta_`. Esses efeitos representam a evolução real do sistema e ficam concentrados no método `concluir`. O encapsulamento reduz o risco de alterações arbitrárias, mas exige atenção ao estado atual dos objetos.

### 2.10 Facilidade para testar

A versão imperativa é direta para testes unitários porque cada caso fornece uma `EntradaIrrigacao` completa e compara a `SaidaIrrigacao` devolvida. Como a função não preserva estado interno, os casos são independentes.

Na versão POO, cada teste precisa criar sensor, válvula, configuração e controlador antes de executar `processar`. Isso aumenta a preparação do teste, mas permite verificar a colaboração entre os componentes e simular estados internos do sistema. As duas implementações executaram os mesmos casos `CN01` a `CN10`, `CL01` a `CL04` e `CI01` a `CI03`, com 17 aprovações em cada versão.

### 2.11 Organização do código

Na versão imperativa, `irrigacao.h` declara enumerações, estruturas e funções; `irrigacao.cpp` implementa o algoritmo; e `testes.cpp` contém os casos de teste. A organização é compacta e fácil de acompanhar.

Na versão POO, `modelo.h` declara quatro classes e os tipos do domínio; `modelo.cpp` implementa seus métodos; e `testes.cpp` cria os objetos necessários para cada cenário. Há mais elementos no modelo, mas as responsabilidades ficam nomeadas e separadas de forma explícita.

### 2.12 Complexidade

Para o tamanho atual do problema, a versão imperativa possui menor complexidade estrutural. Ela utiliza menos abstrações e expressa a decisão principal por uma função e duas estruturas de dados.

A versão POO acrescenta construtores, métodos, referências entre objetos e gerenciamento de estado. Esse custo é perceptível em um sistema pequeno. Em compensação, a estrutura se torna mais adequada ao crescimento do projeto. Nos dois casos, a complexidade lógica das regras é semelhante, pois as condições do contrato semântico são as mesmas.

## 3. Respostas às perguntas propostas

### 3.1 Qual problema ficou mais fácil de expressar de forma imperativa?

A avaliação isolada de uma combinação de entradas ficou mais fácil de expressar de forma imperativa. A função `avaliarIrrigacao` recebe todos os valores necessários, percorre as regras em ordem de prioridade e devolve uma saída. Para entender uma única decisão, basta acompanhar a sequência de condições e retornos da função.

### 3.2 Qual problema ficou mais fácil de expressar utilizando orientação a objetos?

A representação de um sistema que evolui ao longo de vários ciclos ficou mais fácil com orientação a objetos. O sensor mantém sua leitura, a válvula mantém sua condição e o controlador mantém o estado da irrigação e a habilitação. Dessa forma, o programa representa melhor componentes que possuem identidade, dados próprios e comportamento.

### 3.3 Onde a orientação a objetos realmente trouxe vantagem?

A principal vantagem apareceu na separação de responsabilidades e no encapsulamento. O sensor, a válvula, os limites e o controlador deixaram de ser apenas campos de uma entrada e passaram a possuir operações relacionadas ao próprio papel. Além disso, o estado entre ciclos não precisa ser reconstruído manualmente a cada chamada, pois permanece dentro dos objetos responsáveis.

### 3.4 Em quais situações a utilização de objetos acrescentou complexidade desnecessária?

Para validar apenas uma entrada e calcular uma saída, criar quatro objetos, chamar construtores e manter referências entre eles é mais trabalhoso do que chamar uma única função. Classes muito pequenas, compostas apenas por atributos simples e poucos métodos, também introduzem código adicional. Por esse motivo, herança e polimorfismo não foram utilizados: no modelo atual, esses recursos não resolveriam uma necessidade concreta.

### 3.5 Que partes do problema praticamente não mudaram entre as duas implementações?

As regras de decisão, a ordem de prioridade, os limites de umidade, os estados possíveis, as ações da válvula, as mensagens e os resultados esperados permaneceram praticamente iguais. A lógica continua verificando primeiro as entradas inválidas e a segurança do sistema; depois avalia habilitação, reinicialização e umidade. Os mesmos 17 casos de teste também foram preservados.

### 3.6 Que partes precisaram ser completamente remodeladas?

A representação e a atualização do estado foram remodeladas. Na versão imperativa, todos os dados chegam juntos em `EntradaIrrigacao` e o resultado é construído localmente. Na versão POO, os dados foram distribuídos entre objetos persistentes, e `ControladorIrrigacao::concluir` passou a atualizar o controlador e a válvula. A interface de uso também mudou: em vez de preparar uma estrutura e chamar uma função, o programa cria objetos que colaboram por meio de métodos.

## 4. Conclusão

As duas implementações atendem ao mesmo contrato e produzem os mesmos resultados. A versão imperativa é mais curta e direta para executar avaliações independentes, sendo adequada ao tamanho inicial do algoritmo. A versão orientada a objetos exige mais estrutura, mas representa melhor os componentes do sistema, controla a mutabilidade por encapsulamento e distribui responsabilidades de forma clara.

No projeto desenvolvido, a orientação a objetos trouxe vantagem principalmente para representar o estado contínuo, organizar os componentes e preparar o sistema para futuras extensões. Ao mesmo tempo, a comparação demonstra que objetos não devem ser criados apenas por obrigação: abstrações como herança e polimorfismo só devem ser utilizadas quando houver tipos diferentes e comportamentos que realmente justifiquem seu uso.
