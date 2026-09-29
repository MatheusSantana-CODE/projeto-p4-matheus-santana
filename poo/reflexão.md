# Reflexao sobre a mudanca para orientacao a objetos

## Como meu modelo mudou

Na implementacao imperativa, o problema era representado principalmente por
estruturas de dados, variaveis mutaveis e uma sequencia explicita de decisoes.
Na implementacao orientada a objetos, o mesmo comportamento passou a ser
representado por componentes que possuem estado, comportamento e
responsabilidades proprias. A mudanca nao consistiu apenas em colocar as
funcoes anteriores dentro de uma classe: sensor, valvula, configuracao e
controle passaram a ser conceitos independentes que colaboram entre si.

## Representacao do estado

No modelo imperativo, o estado anterior precisava ser informado a cada chamada
da funcao de avaliacao. No modelo orientado a objetos, o
`ControladorIrrigacao` encapsula o estado atual e o altera somente por meio de
suas operacoes publicas. O `SensorUmidade` conserva a leitura e sua condicao de
funcionamento, enquanto a `ValvulaIrrigacao` conserva se esta aberta ou
fechada. Dessa forma, o estado fica associado ao objeto responsavel por ele.

## Responsabilidades

As responsabilidades foram distribuidas para evitar uma classe central que
fizesse tudo. O sensor fornece a leitura; a configuracao protege os limites; a
valvula aplica o comando; e o controlador toma a decisao conforme o contrato.
O programa principal ficou responsavel apenas pela comunicacao com o usuario.

## Relacionamento entre componentes

O controlador recebe objetos das classes `SensorUmidade` e
`ValvulaIrrigacao` e coordena suas operacoes. A configuracao de limites tambem
e representada por uma classe propria. Essa organizacao torna os
relacionamentos explicitos e permite testar as regras sem depender da interface
de terminal.

## Reutilizacao

As classes `SensorUmidade`, `ValvulaIrrigacao` e `ConfiguracaoLimites` podem ser
reutilizadas em diferentes execucoes do controlador. Os metodos publicos
definem operacoes claras, evitando a repeticao de regras de acesso e alteracao
dos dados internos.

## Encapsulamento

Os atributos das classes sao privados e so podem ser consultados ou alterados
pelas operacoes publicas previstas. Isso impede que outras partes do programa
coloquem diretamente o controlador, o sensor ou a valvula em uma condicao
inconsistente. As regras de transicao permanecem concentradas no controlador.

## Decisao sobre heranca e polimorfismo

Heranca e polimorfismo nao foram utilizados nesta versao. O enunciado permite
aplicar esses recursos somente quando fizerem sentido, e o sistema atual possui
apenas um tipo de sensor e um tipo de valvula. Criar classes-base e hierarquias
sem uma necessidade concreta aumentaria a complexidade e seria apenas uma forma
artificial de cumprir requisitos opcionais.

## Extensao do sistema

O modelo pode ser ampliado com mecanismos de registro, novas operacoes de
controle e outras interfaces de usuario. Se futuramente surgirem varios tipos
de sensores ou valvulas com comportamentos diferentes, heranca ou polimorfismo
poderao ser avaliados nesse novo contexto. A separacao atual de
responsabilidades ja reduz o impacto das mudancas em comparacao com a versao
predominantemente imperativa.
