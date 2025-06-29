# 👔 Sistema de Recrutamento e Seleção - C++

[![C++ Standard](https://img.shields.io/badge/C%2B%2B-11%2B-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B11)
[![Multiplatform](https://img.shields.io/badge/platform-Windows%20%7C%20Linux%20%7C%20macOS-lightgrey.svg)](https://en.wikipedia.org/wiki/Cross-platform)

## 📌 Visão Geral

Sistema de terminal para **gestão de candidatos** com foco em Recrutamento e Seleção. Permite o cadastro, visualização, ordenação, busca (por nome ou CPF), importação/exportação de dados em CSV e **persistência binária eficiente e automática**.

Desenvolvido em C++11 com foco em **modularidade, segurança de memória, tratamento robusto de erros e interface interativa**.

---

## 📸 Interface (modo terminal)

> ![Exemplo visual do sistema](https://github.com/user-attachments/assets/8c6d896e-70d9-4ab0-8ec0-5bb3411f321d)

---

## 🧩 Principais Funcionalidades

* ✅ Adicionar e remover candidatos
* 🔍 Buscar candidatos por **nome** ou **CPF**
* 🧮 Ordenação ascendente/descendente por qualquer campo
* 📁 Exportação e importação de CSV
* 💾 Persistência binária automática com salvamento explícito
* 📃 Visualização paginada ou completa
* 🎨 Interface colorida, limpa e responsiva no terminal

---

## ⚙️ Robustez e Tratamento de Erros

* ✨ **Validação de entrada de dados**:

  * Proteção contra inserção de letras em campos numéricos
  * Reentrada automática em caso de erro
* 📋 **Validação de opções no menu**:

  * Impede seleção inválida sem travar o programa
  * Mensagens claras e amigáveis ao usuário
* 🧭 **Controle contextual de interface**:

  * Não exibe "próxima página" se já estiver na última
  * "Página anterior" só aparece se houver anterior
  * Paginação e listagem só são exibidas no modo paginado

> ⚠️ *Observação: o sistema **não impede duplicidade de CPFs nem valida estruturalmente CPF** (mas essa é uma funcionalidade que pode ser adicionada posteriormente).*

---

## 📚 Arquitetura das Bibliotecas

As bibliotecas utilitárias contidas na pasta `/libs/util` possuem uma **implementação mais robusta e genérica**, projetadas para serem reutilizáveis em diversos projetos e casos de uso. Elas incluem estruturas genéricas, como `ArrayList<T>`, e funcionalidades de manipulação de arquivos e strings com tratamento cuidadoso de memória e tipos.

Já o código principal do sistema (na pasta `/main` e `/src`) é implementado com foco na **robustez adequada para o projeto específico**, evitando overengineering e mantendo a simplicidade para facilitar manutenção e extensão. Assim, o sistema é sólido, porém direto ao ponto para atender o escopo de Recrutamento e Seleção.

---

## 📁 Estrutura do Projeto

libs/
  util/include/util/
    ArrayList, ArrayUtils, FileManager, StringUtils # Bibliotecas utilitárias genéricas e robustas
  binary_data/include/binary/data/
    BinaryEntity, BinaryFileRepository # Manipulação genérica de arquivos binários

main/
  include/
    model/
      Candidate.hpp
    repository/
      CandidateRepository.hpp
    menu/
      Menu.hpp
      enum/
        HrMenuFieldEnum.hpp
        MenuListModeEnum.hpp

---

## 🔧 Compilação

O projeto inclui um `Makefile`. Para compilar:

```bash
make
```

Para executar

```bash
./rh_system
```

Caso deseje compilar manualmente

```bash
g++ -std=c++11 \\
  main/src/main.cpp \\
  main/src/model/Candidate.cpp \\
  main/src/Menu.cpp \\
  libs/util/src/StringUtils.cpp \\
  libs/util/src/FileManager.cpp \\
  -o rh_syste
```

---

## 🧪 Exemplo de Uso

👥 Candidatos:  1. Adicionar   2. Remover
📄 Arquivo:     3. Importar    4. Exportar
👁 Visualizar:  5. Ordenar     6. Buscar     7. Listar Tudo
📏 Página:      8. Definir Itens/Página
💾 Sistema:     s. Salvar      0. Sair

---

## 🔒 Qualidade do Código

* 🧠 `ArrayList<T>` gerencia internamente a memória (construtor, cópia, movimento, destrutor, resize)

* 🛡️ Tipos seguros e operações genéricas (`sort`, `filter`, `findBy`)

* ♻️ Total separação de camadas (Menu, Model, Repository)

* 📁 Arquivos binários organizados em `/data/*.bin`

---

## ✨ Tecnologias e Conceitos

* C++11

* STL (`<string>`, `<fstream>`, `<algorithm>`, etc)

* Templates, RAII e Smart Separation

* Serialização binária segura

* Design Modular e orientado a objetos
