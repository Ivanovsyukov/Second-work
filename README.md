## Как запустить проект?
---
В каждой папке (Server, Client) есть exe файл, который и следует запускать.
Также, чтобы программа заработала, нужно чтобы вместе с exe файлом лежали конфигурационный файл konfig.txt и файл для логирования log.txt.
В конфигурационном файле нужно написать ip сервера, потом через enter указать сокет.
Для сервера в конфигурационном файле следует указать только сокет.

## Как играть?
---
1. Установите корректные данные в конфигурационных файлах как сервера, так и клиента
2. Запустите сервер
3. Запустите клиент
4. Далее вы попадете на регистрацию. Следуйте указаниям
5. После регистрации вы можете написать команды 

- online - посмотреть список игроков онлайн

- play NAME - запрос поиграть с игроком с именем NAME

6. Наслаждайтесь игрой 

## Для разработчика 
---
Все исходные файлы лежат в папке Sourse как в Server так и в Client 

## Что бы хотелось добавить в проект
---

- шифрование пароля

- таймер для хода в игре

- команду help

Доп изменения:
1. Путь к конфигу в аргументах при запуске программы.
2. В конфиге должны быть строки в порядке:
а)Для клиента:
 1)Путь к лог файлу, для создания лог файла.
 2)Ip сервера.
 3)Порт.
б)Сервер:
 1)Путь к лог файлу, для создания лог файла.
 2)Порт.
 3)Путь к файлу с базой зарегистрированных пользователей для чтения.(Если нет, то прочерк)
 4)Путь к файлу для записи базы. (Если нет то прочерк)