# Flashcards
Курсовая работа по ООП - карточки для запоминания информации!
## Оглавление
1. [Установка](#установка-на-Windows)
2. [Сборка](#сборка)
3. [Использование](#использование)
## Установка на Windows
Для корректной работы приложения необходимы:
- Пакетный менеджер `vcpkg`, который может быть загружен с [официального сайта](https://vcpkg.io/en/getting-started.html)
- Утилита `Doxygen`, которая может быть загружена с [официального сайта](https://www.doxygen.nl/)
- Библиотека `nlohmann_json`, установленная с помощью `vcpkg`:
```
  vcpkg install nlohmann-json:x64-windows
``` 
- Библиотека `wxWidgets`, также установленная с помощью `vcpkg`:
```
  vcpkg install wxwidgets:x64-windows
```
- После установки библиотек также необходимо написать:
```
  vcpkg integrate install
```
## Сборка
1. Склонировать репозиторий
```
  git clone https://github.com/hedanta/flashcards
```
2. В скачанной директории:
```
  >cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=<Ваш путь до vcpkg>/scripts/buildsystems/vcpkg.cmake
  >cmake --build build --config Release
  >cmake --install ./build --prefix ./cards
```
По завершении сборки в папке cards появится `cards.exe`, который можно запустить
## Использование
это я потом допишу)
