# Implementação orientada a objetos

Esta pasta contém a Etapa 04 do Sistema de Gerenciamento de Irrigação
Inteligente. A solução preserva o contrato semântico das etapas anteriores,
mas remodela o problema como uma colaboração entre objetos.

## Classes e responsabilidades

- `ConfiguracaoLimites`: encapsula os limites e valida sua coerência;
- `SensorUmidade`: encapsula a leitura e a condição de funcionamento;
- `ValvulaIrrigacao`: recebe comandos e conserva a condição aberta ou fechada;
- `ControladorIrrigacao`: coordena sensor, válvula, configuração e estado;
- `ResultadoControle`: representa a resposta observável de uma avaliação.

## Conceitos utilizados

Esta implementação concentra-se em quatro conceitos solicitados para a Etapa
04:

- encapsulamento, com atributos privados e acesso por métodos públicos;
- classes, que modelam sensor, válvula, configuração e controlador;
- objetos, criados a partir dessas classes durante a execução;
- responsabilidades bem definidas para cada componente.

Herança e polimorfismo não foram utilizados porque não são necessários para o
escopo atual. A criação de uma hierarquia apenas para demonstrar esses conceitos
deixaria a solução mais complexa sem melhorar a representação do problema.

## Compilação e execução

```bash
cd poo
make
./irrigacao_poo
```

## Testes

```bash
make test
```

Os 17 casos da Etapa 02 devem ser aprovados. Para remover os executáveis:

```bash
make clean
```
