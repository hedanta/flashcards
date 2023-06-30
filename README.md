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

![image](https://github.com/hedanta/flashcards/assets/95635887/2a3584ff-bcba-4cc4-b2d2-ac3e0e47ba86)

Как можно заметить, есть три кнопки управления. Например, если получить случайный вопрос, нажав на кнопку `Случайный вопрос`, ввести ответ в поле `Ваш ответ` и проверить его с помощью кнопки `Проверить ответ`, то Вы увидите оценку `Верно` или `Неверно`:

![image](https://github.com/hedanta/flashcards/assets/95635887/498466bc-d5c3-4fdf-9bb0-e7da1cc1a3cf)

При этом важно, что для перехода к следующему вопросу необходимо написать и проверить свой ответ, иначе будтет показано соответствущее предупреждение.
____
Имеется меню `Опции`, в котором есть следующие команды (все основные действия происходят с текущей колодой):

![image](https://github.com/hedanta/flashcards/assets/95635887/4827df7f-fcd9-4342-9189-2819fe0f21fc)

При выборе опции `Переименовать колоду`, Вы увидите окно с полем ввода нового названия:

![image](https://github.com/hedanta/flashcards/assets/95635887/0c576f9f-d993-476d-93d6-fbb0c4cdf29e)

При выборе опции `Редактор колоды`, Вы увидите окно со всеми карточками, которые можно добавить в колоду или удалить из неё, поставив или убрав галочку возле соответствующей карточки:

![image](https://github.com/hedanta/flashcards/assets/95635887/6387c1d5-1425-4830-80fd-e35cacd695ad)

Можно создать новую колоду, выбрав опцию `Создать колоду`:

![image](https://github.com/hedanta/flashcards/assets/95635887/bccfaf5f-6f81-47be-ab1d-b9586a67a961)

Также есть возможность удалить колоду (за исключением колоды `Все карточки` — это колода по умолчанию):

![image](https://github.com/hedanta/flashcards/assets/95635887/551faf09-c331-4fbc-a940-3321aa7d74f5)

## а всё)
ура у меня приняли курсач!!!!!!