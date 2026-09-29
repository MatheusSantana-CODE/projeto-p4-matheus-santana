# Reflexão sobre a mudança para orientação a objetos

## Como meu modelo mudou

Na implementação imperativa, o problema era representado principalmente por
estruturas de dados, variáveis mutáveis e uma sequência explícita de decisões.
Na implementação orientada a objetos, o mesmo comportamento passou a ser
representado por componentes que possuem estado, comportamento e
responsabilidades próprias. A mudança não consistiu apenas em colocar as
funções anteriores dentro de uma classe: sensor, válvula, configuração e
controle passaram a ser conceitos independentes que colaboram entre si.

## Representação do estado

No modelo imperativo, o estado anterior precisava ser informado a cada chamada
da função de avaliação. No modelo orientado a objetos, o
`ControladorIrrigacao` encapsula o estado atual e o altera somente por meio de
suas operações públicas. O `SensorUmidade` conserva a leitura e sua condição de
funcionamento, enquanto a `ValvulaIrrigacao` conserva se está aberta ou
fechada. Dessa forma, o estado fica associado ao objeto responsável por ele.

## Responsabilidades

As responsabilidades foram distribuídas para evitar uma classe central que
fizesse tudo. O sensor fornece a leitura; a configuração protege os limites; a
válvula aplica o comando; e o controlador toma a decisão conforme o contrato.
O programa principal ficou responsável apenas pela comunicação com o usuário.

## Relacionamento entre componentes

O controlador recebe objetos das classes `SensorUmidade` e
`ValvulaIrrigacao` e coordena suas operações. A configuração de limites também
é representada por uma classe própria. Essa organização torna os
relacionamentos explícitos e permite testar as regras sem depender da interface
de terminal.

## Reutilização

As classes `SensorUmidade`, `ValvulaIrrigacao` e `ConfiguracaoLimites` podem ser
reutilizadas em diferentes execuções do controlador. Os métodos públicos
definem operações claras, evitando a repetição de regras de acesso e alteração
dos dados internos.

## Encapsulamento

Os atributos das classes são privados e só podem ser consultados ou alterados
pelas operações públicas previstas. Isso impede que outras partes do programa
coloquem diretamente o controlador, o sensor ou a válvula em uma condição
inconsistente. As regras de transição permanecem concentradas no controlador.

## Decisão sobre herança e polimorfismo

Herança e polimorfismo não foram utilizados nesta versão. O enunciado permite
aplicar esses recursos somente quando fizerem sentido, e o sistema atual possui
apenas um tipo de sensor e um tipo de válvula. Criar classes-base e hierarquias
sem uma necessidade concreta aumentaria a complexidade e seria apenas uma forma
artificial de cumprir requisitos opcionais.

## Extensão do sistema

O modelo pode ser ampliado com mecanismos de registro, novas operações de
controle e outras interfaces de usuário. Se futuramente surgirem vários tipos
de sensores ou válvulas com comportamentos diferentes, herança ou polimorfismo
poderão ser avaliados nesse novo contexto. A separação atual de
responsabilidades já reduz o impacto das mudanças em comparação com a versão
predominantemente imperativa.
