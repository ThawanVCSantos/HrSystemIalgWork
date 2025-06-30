
# 🛠️ Util - Biblioteca de Utilitários C++ para Projetos Genéricos

[![C++ Standard](https://img.shields.io/badge/C%2B%2B-11%2B-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B#Standardization)
[![Multiplatform](https://img.shields.io/badge/platform-Windows%20%7C%20Linux%20%7C%20macOS-lightgrey.svg)](https://en.wikipedia.org/wiki/Cross-platform)

## 📌 Visão Geral

**Util** é uma biblioteca leve e extensível de utilitários em C++11+, ideal para projetos acadêmicos e sistemas C++ modernos. Fornece uma coleção de classes auxiliares para manipulação de arrays, strings, arquivos e diretórios.

**Suporte consistente a Windows, Linux e macOS**

---

## 📚 Componentes Principais

### ✅ `ArrayList<T>`

Uma lista dinâmica genérica inspirada na `ArrayList` do Java. Suporta ordenação, filtros, buscas e funções de ordem superior.

#### Recursos:
- Controle total e seguro da memória: construtor, cópia, movimento, destrutor
- Redimensionamento automático (para cima e para baixo)
- Iteração com `forEach`
- Filtros, ordenações e buscas por campo (`findBy`)

#### Exemplo:
```cpp
util::ArrayList<int> lista;
lista.add(10);
lista.add(5);
lista.sort([](int a, int b) { return a < b; });
lista.forEach([](int el) { std::cout << el << std::endl; });
```

---

### 🔁 `ArrayUtils`

Utilitários para cópia e ordenação de arrays C-style.

#### Funções Disponíveis:
- `copyArrayElements`
- `insertionSort`
- `mergeSort`
- `sort` (interno)

---

### 📂 `FileManager`

Facilita verificações e criação de arquivos/diretórios.

#### Funções:
- `dirExists(path)`
- `createDir(path)`
- `fileExists(path)`

---

### 🔤 `StringUtils`

Funções auxiliares para manipulação de `char[]` e `std::string`.

#### Funções:
- `toLowerCase`, `toUpperCase`
- `getStrSize`
- `truncate`, `centralize`

---

## 🔧 API Completa

### 📄 `ArrayList<T>`

| Método                        | Descrição                                                      |
|-------------------------------|----------------------------------------------------------------|
| `add(element)`                | Adiciona um elemento à lista                                   |
| `remove(index)`               | Remove o elemento da posição especificada                      |
| `remove(&element)`            | Remove o primeiro elemento igual ao fornecido (por ponteiro)   |
| `get(index)`                  | Retorna o elemento no índice                                   |
| `clear()`                     | Remove todos os elementos                                      |
| `size()`                      | Retorna a quantidade de elementos                              |
| `isEmpty()`                   | Verifica se a lista está vazia                                 |
| `data()`                      | Retorna ponteiro bruto para o array interno                    |
| `forEach(func)`               | Executa uma função para cada elemento                          |
| `sort(comp)`                  | Retorna nova lista ordenada conforme comparador                |
| `filter(pred)`                | Retorna nova lista com os elementos que satisfazem o predicado |
| `findBy(valor, getField)`     | Busca elemento com campo igual ao valor especificado           |

---

### 🌀 `ArrayUtils`

| Método                                                                | Descrição                                                            |
|-----------------------------------------------------------------------|----------------------------------------------------------------------|
| `copyArrayElements(arraySrc, arrayDst, size)`                         | Copia elementos de um array para outro (exceto `char[]`)             |
| `copyArrayElements(charSrc, charDst, size, includeNullTerminator)`    | Copia `char[]`, com ou sem terminador nulo                           |
| `insertionSort(array, size, comp)`                                    | Ordena usando o algoritmo insertion sort                             |
| `mergeSort(array, size, comp)`                                        | Ordena usando merge sort (mais eficiente)                            |
| `sort(array, size, comp)`                                             | Escolhe o algoritmo de ordenação ideal (atualmente: mergeSort)       |

---

### 📁 `FileManager`

| Método                           | Descrição                                        |
|----------------------------------|--------------------------------------------------|
| `dirExists(path)`                | Verifica se o diretório existe                   |
| `createDir(path)`                | Cria o diretório, se não existir                 |
| `fileExists(path)`               | Verifica se o arquivo existe                     |

---

### 🔤 `StringUtils`

| Método                              | Descrição                                                |
|-------------------------------------|----------------------------------------------------------|
| `getStrSize(str)`                   | Retorna o comprimento real da string `char*` (sem `\0`)  |
| `toLowerCase(char)`                 | Converte um caractere para minúsculo                     |
| `toLowerCase(char*)`                | Converte um array de caracteres para minúsculo           |
| `toUpperCase(char)`                 | Converte um caractere para maiúsculo                     |
| `toUpperCase(char*)`                | Converte um array de caracteres para maiúsculo           |
| `truncate(str, size)`               | Trunca uma string para o tamanho especificado            |
| `centralize(str, size)`             | Centraliza visualmente a string em `size` caracteres     |

---

## ✅ Requisitos

- Compilador com suporte a C++11 ou superior
- Nenhuma dependência externa

---

## 📌 Boas Práticas

- Utilize `filter` e `sort` para manipulações funcionais
- Prefira `ArrayList` para controle total da memória
- Use `ArrayUtils` para operações sobre arrays primitivos
- Use `FileManager` para preparar ambiente de persistência

---

## 🚀 Exemplo Integrado

```cpp
util::ArrayList<std::string> nomes;
nomes.add("João");
nomes.add("ana");
nomes.add("Carlos");

auto filtrado = nomes.filter([](const std::string& nome) {
  return nome[0] == 'J';
});

int valores[] = {3, 2, 1};
util::ArrayUtils::mergeSort(valores, 3, [](int a, int b) { return a < b; });

if (!util::FileManager::dirExists("data")) {
  util::FileManager::createDir("data");
}

char nome[] = "Exemplo";
util::StringUtils::toLowerCase(nome);
```
