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

1. **Estrutura de Dados**: 
   - Lista duplamente encadeada para facilitar a navegação nos dois sentidos durante a paginação

2. **Persistência**: 
   - Dados armazenados em arquivo CSV
   - Carregamento na inicialização
   - Salvamento automático ao finalizar

3. **Busca**: 
   - Case-insensitive por nome
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

## Dependências

- GCC 11+
- Make

## Como Instalar

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
make run
```

## Exemplos de Uso

### Cadastro de Paciente
1. Selecione opção 4 no menu principal
2. Digite o CPF (somente números): 12345678909
3. Digite o nome: João da Silva
4. Digite a idade: 45
5. Digite a data: 20240208

### Consulta de Paciente
1. Selecione opção 1 no menu principal
2. Escolha o modo de busca (1 - Nome, 2 - CPF)
3. Digite o termo de busca

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
