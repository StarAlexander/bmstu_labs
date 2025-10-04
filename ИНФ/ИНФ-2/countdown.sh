#!/bin/bash

echo "Введите число для обратного отсчёта:"
read num

if ! [[ "$num" =~ ^[0-9]+$ ]]; then
    echo "Ошибка: введите корректное положительное число."
    exit 1
fi

for (( i=num; i>=1; i-- )); do
    echo "$i"
done
echo "Готово!"