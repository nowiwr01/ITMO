#!/bin/bash

ps axo  pid,command | grep "/sbin/" | awk '{ print $1 }'

# по дефолту в ps можно указывать команды без "-"
# -x - все процессы, принадлежащие нам
# -o - задали формат вывода
# Мы нашли PID и имя команды. Далее запускаем наш любимый grep и ищем все такие команды, 
# в которых есть имя библиотеки, а потом выводим айдишник