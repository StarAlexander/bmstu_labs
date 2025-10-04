#!/bin/bash

touch notes.txt
echo "Введите текст (введите 'exit' для завершения):"
while true; do
    read line
    if [[ "$line" == "exit" ]]; then
        break
    else
        echo "$line" >> notes.txt
    fi
done
echo -e "\nСодержимое файла notes.txt:"
cat notes.txt
rm notes.txt