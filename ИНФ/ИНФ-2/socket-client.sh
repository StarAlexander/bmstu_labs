#!/bin/bash

PORT=12345
HOST="localhost"

if [ $# -eq 0 ]; then
    echo "Использование: $0 \"ваше сообщение\""
    exit 1
fi

MESSAGE="$*"

nc -l -p 12346 &
LISTENER_PID=$!

echo "Отправка: $MESSAGE"
echo "$MESSAGE" | nc "$HOST" "$PORT"

sleep 2
kill $LISTENER_PID 2>/dev/null