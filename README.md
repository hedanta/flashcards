# Flashcards
Курсовая работа по ООП - карточки для запоминания информации!
## Оглавление
1. [Установка](#установка-на-windows)
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
  cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=<Ваш путь до vcpkg>/scripts/buildsystems/vcpkg.cmake
```
```
  cmake --build build --config Release
```
```
  cmake --install ./build --prefix ./cards
```
По завершении сборки в папке `cards/bin` появится `cards.exe`, который можно запустить
## Использование
Имеется файл с готовыми карточками для тестирования.
Можно добавить свои вопросы в файл `cards.json`.
~когда-нибудь я добавлю функцию создания карточек :)~

Основное окно выглядит так: 

![main_window](/images/main_window.png)

Как можно заметить, есть три кнопки управления. Например, если получить случайный вопрос, нажав на кнопку `Случайный вопрос`, ввести ответ в поле `Ваш ответ` и проверить его с помощью кнопки `Проверить ответ`, то Вы увидите оценку `Верно` или `Неверно`:

![checker](/images/checker.png)

При этом важно, что для перехода к следующему вопросу необходимо написать и проверить свой ответ, иначе будет показано соответствующее предупреждение.
____
Имеется меню `Опции`, в котором есть следующие команды (все основные действия происходят с текущей колодой):

![optioins](/images/options.png)

При выборе опции `Переименовать колоду`, Вы увидите окно с полем ввода нового названия:

![rename](/images/rename.png)

При выборе опции `Редактор колоды`, Вы увидите окно со всеми карточками, которые можно добавить в колоду или удалить из неё, поставив или убрав галочку возле соответствующей карточки:

![editor](/images/editor.png)

Можно создать новую колоду, выбрав опцию `Создать колоду`:

![creator](/images/creator.png)

Также есть возможность удалить колоду (за исключением колоды `Все карточки` — это колода по умолчанию):

![remove](/images/remove.png)

## а всё)
ура у меня приняли курсач!!!!!!
