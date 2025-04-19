# Final Project for 5092

**Grupo Dmytro e Rui**

## Objetivo
Elaborar um programa em C++ com o intuito de gestão de um pequeno comércio local, concretizando os pontos abaixo.
Tema: Loja de Maquinas Fotograficas
---

## Funcionalidades

### Ações

- **Efetuar Venda:**
  1. Apresentar os produtos no ecrã.
  2. Selecionar produto e indicar a quantidade a comprar.
  3. Checkout (apresentar resumo da compra e efetuar pagamento).
  4. Imprimir talão no ecrã.

- **Criação de Compra para Stock:**
  1. Criação de artigo novo.
  2. Eliminar produto.

---

## Estruturas

- **Stock:**
  - ID do produto
  - Quantidade
  - Nome do produto
  - Preço de custo  
    *(preço de venda = preço de custo + 30%)*

- **Talão:**
  1. Número da fatura
  2. Número do cliente
  3. Nome do produto
  4. Quantidade
  5. Preço sem IVA
  6. IVA
  7. Total com IVA
  8. Valor entregue
  9. Troco

---

## Outros Requisitos

- Data do talão inserida automaticamente pelo sistema.
- O programa, ao iniciar, deve já conter valores para todas as estruturas.
- **Extra:** De tempos em tempos, uma das vendas deve ser sorteada e o cliente não paga.
- O programa deve conter todas as validações necessárias para evitar ações indevidas.
- O stock deve ser atualizado automaticamente nas compras e vendas.

---

## Requisitos Técnicos

O programa a ser elaborado em C++ deve utilizar:

- Funções
- Vetores
- Matrizes
- Ponteiros
- Estruturas de decisão
- Estruturas de repetição
