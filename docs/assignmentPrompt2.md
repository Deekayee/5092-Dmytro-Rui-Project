# Final Project for 5092

**Grupo Dmytro e Rui**

## Objetivo
Elaborar um programa em C++ com o intuito de gestão de um pequeno comércio local, concretizando os pontos abaixo.

### Tema
Loja de Maquinas Fotograficas

---

## Funcionalidades

### Ações

- **Efetuar venda**
    1. Apresentar os produtos no ecrã.
    2. Selecionar produto(s) e indicar a quantidade do(s) produto(s) que vai
    comprar.
    3. Checkout (apresentar o resumo da compra e efetuar o pagamento)
    4. Imprimir talão no ecrã.

- **Criação de compra para stock**
    1. Criação de produto novo
    2. Adicionar stock a produto existente
    3. Eliminar Produto.

- **Criação de Relatórios:**
    1. Relatório de stock com stock total
    2. Relatório de vendas por produto (recebe por parâmetro o nome do
    produto)
    3. Relatório de total de vendas com
        - a. Produto mais vendido,
        - b. Produto menos vendido
        - c. Valor do lucro do produto mais vendido.
        - d. Cliente que mais comprou em valor.

- **Clientes**
    1. Criar cliente
    2. Eliminar cliente (Não deixar espaços vazios na estrutura)
    3. Alterar o nome do cliente

---

## Estruturas

- **Stock:**
    - Id do produto 
    - Quantidade
    - Nome do produto
    - Preço
    - Custo (O preço de venda é + 30%)

- **Cliente**
    - Id do cliente
    - Nome
    - Número de telefone
    - Morada

- **Talão:**
    - Número da fatura
    - Número do cliente
    - Número de linha (indicação incremental da quantidade de artigos no
    mesmo talão, esta indicação aparece antes do nome do produto)
    - Nome do produto
    - Quantidade
    - Preço s/IVA
    - IVA
    - Total C/iva
    - Valor entregue
    - Troco

- Todas as vendas devem ser armazenadas numa estrutura até ao **limite de 100**. Quando atinge o limite, **escrever na posição mais antiga**

---

## Outros Requisitos

- Data do talão inserida automaticamente pelo sistema.
- O programa ao arrancar deve já ter valores para todas as estruturas.
- O talão deve ser branco com as letras a preto.
- **Extra**: De tempos em tempos, uma das vendas deve ser **sorteada** e o cliente não paga.
- O programa deve fazer todas as **validações necessárias** de modo a não efetuar ações
indevidas.
- Deve existir as classes **Loja, Venda, Produto e Cliente**.
- A loja deve conter vetores de armazenamento de **vendas, produtos e clientes**.
- Os *Ids* de vendas, produtos e clientes devem ser diferentes e automáticos.
- O stock deve ser **atualizado** na compra e na venda, automaticamente.
- Após cada venda, o programa deve voltar ao menu inicial.

---

## Requisitos Técnicos

O programa a ser elaborado em C++ deve utilizar:

- Funções
- Ponteiros
- Estruturas de decisão
- Estruturas de repetição
- Classes


# Entregar os ficheiros .*cpp* e .*h*
## **Data de entrega**: terça-feira, 8 de julho de 2025 às 18:50 