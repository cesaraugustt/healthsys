# Sistema de Gerenciamento de Dados de Pacientes (HealthSys)

Este sistema foi desenvolvido como parte do trabalho prático da disciplina de Estruturas de Dados do IFES - Campus Serra. O HealthSys é um sistema de gerenciamento de dados de pacientes que permite realizar operações básicas de cadastro, consulta, atualização e remoção de registros.

## Funcionalidades

- Consulta de pacientes por nome ou CPF
- Atualização de dados de pacientes
- Remoção de pacientes do sistema
- Inserção de novos pacientes
- Listagem paginada de todos os pacientes

## Estrutura do Projeto

```
.
├── src/
│   ├── main.c          # Programa principal
│   ├── menu.c          # Interface com usuário
│   ├── lista.c         # Implementação da lista encadeada
│   ├── paciente.c      # TAD Paciente
│   ├── arquivo.c       # Manipulação de arquivo CSV
│   └── validacao.c     # Validação de dados
├── include/
│   ├── menu.h
│   ├── lista.h
│   ├── paciente.h
│   ├── arquivo.h
│   └── validacao.h
├── Makefile
├── bd_paciente.csv     # Banco de dados
└── README.md
```

## Principais TADs

### TAD Paciente
Representa um paciente no sistema com seus atributos:
- ID (identificador único)
- CPF
- Nome
- Idade
- Data de Cadastro

### TAD Lista
Implementa uma lista duplamente encadeada para armazenar os pacientes, permitindo:
- Inserção no final
- Remoção por ID
- Busca por nome ou CPF
- Atualização de registros

## Decisões de Implementação

1. **Estrutura de Dados**: Optamos por uma lista duplamente encadeada para facilitar a navegação nos dois sentidos durante a paginação.

2. **Persistência**: Os dados são armazenados em arquivo CSV, carregados na inicialização e salvos ao finalizar o programa.

3. **Busca**: 
   - Implementamos busca case-insensitive por nome
   - Busca parcial que encontra substrings no nome
   - Busca exata por CPF

4. **Interface**:
   - Menu interativo em loop
   - Listagem paginada (5 registros por página)
   - Confirmação antes de operações críticas

5. **Validações**:
   - CPF (formato e dígitos verificadores)
   - Data (formato YYYY-MM-DD)
   - Idade (0-150 anos)

## Como Compilar e Executar

1. Clone o repositório:
```bash
git clone https://github.com/cesaraugustt/healthsys.git
cd healthsys
```

2. Compile o projeto:
```bash
make
```

3. Execute o programa:
```bash
./healthsys
```

## Requisitos

- GCC 11 ou superior
- Make
- Sistema operacional Linux (testado no Ubuntu 22.04)

## Limpeza

Para limpar os arquivos compilados:
```bash
make clean
```

## Autor

César Augusto
cesaraugustobispo@gmail.com

## Licença

Este projeto está sob a licença MIT.