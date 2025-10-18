#!/bin/bash

echo "Сервер слушает порт 12345..."
echo "Сообщения выводятся на экран и в файл messages.log"


nc -l -p 12345 | while read -r line; do
    if [ -n "$line" ]; then
            timestamp=$(date '+%Y-%m-%d %H:%M:%S')
            
            echo "[$timestamp] $line" | tee -a messages.log
            
            
            confirmation="Сообщение '$line' получено в $timestamp"
            echo "$confirmation" | nc localhost 12346  
    fi
done