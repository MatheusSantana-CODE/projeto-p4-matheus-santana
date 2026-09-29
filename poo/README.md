# Implementacao orientada a objetos

Esta pasta contem a Etapa 04 do Sistema de Gerenciamento de Irrigacao
Inteligente. A solucao preserva o contrato semantico das etapas anteriores,
mas remodela o problema como uma colaboracao entre objetos.

## Classes e responsabilidades

- `ConfiguracaoLimites`: encapsula os limites e valida sua coerencia;
- `SensorUmidade`: encapsula a leitura e a condicao de funcionamento;
- `ValvulaIrrigacao`: recebe comandos e conserva a condicao aberta ou fechada;
- `ControladorIrrigacao`: coordena sensor, valvula, configuracao e estado;
- `ResultadoControle`: representa a resposta observavel de uma avaliacao.

## Conceitos utilizados

Esta implementacao concentra-se em quatro conceitos solicitados para a Etapa
04:

- encapsulamento, com atributos privados e acesso por metodos publicos;
- classes, que modelam sensor, valvula, configuracao e controlador;
- objetos, criados a partir dessas classes durante a execucao;
- responsabilidades bem definidas para cada componente.

Heranca e polimorfismo nao foram utilizados porque nao sao necessarios para o
escopo atual. A criacao de uma hierarquia apenas para demonstrar esses conceitos
deixaria a solucao mais complexa sem melhorar a representacao do problema.

## Compilacao e execucao

```bash
cd poo
make
./irrigacao_poo
```

## Testes

```bash
make test
```

Os 17 casos da Etapa 02 devem ser aprovados. Para remover os executaveis:

```bash
make clean
```
