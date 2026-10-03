# Car Factory Idle - C++17 + Raylib 3D Oyunu

## DOSYA YAPISI

```
CarFactoryIdle/
├── Main.cpp
├── Game.h
├── Game.cpp
├── Factory.h
├── Factory.cpp
├── Car.h
├── Car.cpp
├── ProductionLine.h
├── ProductionLine.cpp
├── Employee.h
├── Employee.cpp
├── Machine.h
├── Machine.cpp
├── Economy.h
├── Economy.cpp
├── UI.h
├── UI.cpp
├── SaveSystem.h
├── SaveSystem.cpp
└── CMakeLists.txt (veya Makefile)
```

## DERLEME KOMUTU (MSYS2 UCRT64)

```bash
g++ -std=c++17 -O2 Main.cpp Game.cpp Factory.cpp Car.cpp ProductionLine.cpp Employee.cpp Machine.cpp Economy.cpp UI.cpp SaveSystem.cpp -o CarFactoryIdle.exe -lraylib -lopengl32 -lgdi32 -lwinmm
```

## BAŞLAMA

1. Her dosya adını aşağıdaki listeden al
2. Sırasıyla kodu VS Code'a kopyala
3. Derleme komutunu çalıştır

