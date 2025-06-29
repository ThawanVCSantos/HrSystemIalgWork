
# 📦 Binary Data - Biblioteca C++ para Persistência em Arquivos Binários

[![C++ Standard](https://img.shields.io/badge/C%2B%2B-11%2B-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B#Standardization)
[![Multiplatform](https://img.shields.io/badge/platform-Windows%20%7C%20Linux%20%7C%20macOS-lightgrey.svg)](https://en.wikipedia.org/wiki/Cross-platform)

## 📌 Visão Geral

**Binary Data** é uma biblioteca leve e multiplataforma escrita em C++11+ que auxilia na persistência de dados em arquivos binários. Inspirada no padrão *Repository* do Spring Data, ela foi projetada para facilitar o armazenamento e recuperação de objetos serializáveis de forma simples, organizada e eficiente.

### Principais Recursos:
- **Persistência automática em arquivos binários**
- **CRUD básico com operações atômicas**
- **Validações em tempo de compilação**
- **Gerenciamento automático de diretórios**
- **Suporte consistente a Windows, Linux e macOS**

---

## 🧩 Estrutura da Biblioteca

### `BinaryEntity<T>`

Classe abstrata base que todas as entidades devem herdar. Garante que as entidades sejam serializáveis.

```cpp
namespace binary {
  namespace data {

    template <typename T>
    class BinaryEntity {
      static_assert(std::is_trivially_copyable<T>::value,
                    "T must be trivially copyable");

      public:
        static const char* entityName();

      private:
        BinaryEntity();
        friend T;
    };
  }
}
```

### `BinaryFileRepository<T>`

Classe base para repositórios com suporte a operações CRUD sobre arquivos binários.

```cpp
namespace binary {
  namespace data {
    template <typename T>
    class BinaryFileRepository {
      static_assert(
        std::is_base_of<BinaryEntity<T>, T>::value,
        "T precisa herdar BinaryEntity<T>"
      );

      protected:
        char filename[50];
        std::string path();

        BinaryFileRepository();

      public:
        ArrayList<T> readAll();
        void write(T entity, bool enableTruncate = false);
        void writeAll(ArrayList<T>& entities, bool enableTruncate = false);
    };
  }
}
```

---

## 🚀 Como Usar

### 1. Defina uma Entidade

```cpp
#include "BinaryEntity.hpp"

class Aluno : public binary::data::BinaryEntity<Aluno> {
public:
  int id;
  char nome[100];
  double nota;
  bool ativo;

  Aluno() : id(0), nota(0.0), ativo(false) {
    memset(nome, 0, sizeof(nome));
  }

  static const char* entityName() {
    return "Aluno";
  }
};
```

### 2. Crie um Repositório Personalizado

```cpp
#include "BinaryFileRepository.hpp"

class AlunoRepository : public binary::data::BinaryFileRepository<Aluno> {
  public:
    //Metodo Personalizado não obrigatório
    std::vector<Aluno> buscarAprovados() {
      auto todos = readAll();
      std::vector<Aluno> resultado;

      for (const auto& aluno : todos) {
        if (aluno.nota >= 6.0 && aluno.ativo) {
          resultado.push_back(aluno);
        }
      }
      return resultado;
    }
};
```

### 3. Exemplo de Uso

```cpp
int main() {
  AlunoRepository repo;

  Aluno a1;
  a1.id = 1;
  strncpy(a1.nome, "João Silva", sizeof(a1.nome) - 1);
  a1.nota = 8.5;
  a1.ativo = true;

  repo.write(a1);

  auto alunos = repo.readAll();
  for (const auto& aluno : alunos) {
    std::cout << aluno.nome << " - " << aluno.nota << std::endl;
  }

  return 0;
}
```

---

## 📁 Estrutura de Arquivos Gerada

A biblioteca cria automaticamente um diretório `./data/` na raiz do projeto com os seguintes arquivos:

```
./data/
  aluno.bin
  ...
```

---

## 🔧 API Completa

| Método             | Descrição                          | Complexidade |
|--------------------|------------------------------------|--------------|
| `write()`          | Escreve uma entidade               | O(n)         |
| `writeAll()`       | Substitui todas as entidades       | O(1)         |
| `readAll()`        | Lê todas as entidades              | O(n)         |

---

## ⚠️ Validações em Tempo de Compilação

- A entidade deve ser trivialmente copiável (`std::is_trivially_copyable`)
- A entidade deve definir `static const char* entityName()`
- O repositório só pode ser usado com tipos que herdam `BinaryEntity<T>`

---

## 📌 Boas Práticas

### Tipos Recomendados

| Finalidade           | Tipo Recomendado            |
|----------------------|-----------------------------|
| Inteiros             | `int`, `uint`, `long`       |
| Ponto Flutuante      | `float`, `double`           |
| Texto                | `char[N]`                   |
| Booleanos            | `bool`                      |

---
