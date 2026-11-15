# 2d-cutting-exact

Implementação em **C++** do algoritmo exato DB-PB (Lastra-Díaz & Ortuño, 2025) para o problema de Corte de Estoque Bidimensional Irregular.
As peças são rasterizadas em uma grade; a heurística construtiva fornece o limite superior inicial.

## Requisitos

- CMake 3.10+
- Compilador com suporte a C++17

## Compilar

```bash
cmake -S . -B build
cmake --build build
```

## Executar

```bash
./build/dbpb [caminho_config]
```

## Estrutura

```
.
├── CMakeLists.txt
├── config/config.txt
├── dataset/
├── include/
│   ├── conflitos.h
│   ├── conversor.h
│   ├── dbpb.h
│   ├── dbpb_lb.h
│   ├── empacotador.h
│   ├── grid.h
│   ├── instancia_db.h
│   ├── io.h
│   ├── matriz.h
│   ├── molde.h
│   └── variaveis.h
└── src/
    ├── conflitos.cpp
    ├── conversor.cpp
    ├── dbpb.cpp
    ├── dbpb_lb.cpp
    ├── empacotador.cpp
    ├── grid.cpp
    ├── instancia_db.cpp
    ├── io.cpp
    ├── main_dbpb.cpp
    ├── matriz.cpp
    ├── molde.cpp
    └── variaveis.cpp
```
