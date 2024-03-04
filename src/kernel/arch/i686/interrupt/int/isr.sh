#!/bin/bash

error_codes="8 10 11 12 13 14 17 21 29 30"
gen_asm="$1"

echo "; this file is auto-generated" > "$gen_asm"

for i in $error_codes; do
    echo "ISR_WITH_ERROR_CODE ${i}" >> "$gen_asm"
done

for i in {0..255}; do
    if [[ ! $error_codes =~ $i ]]; then
        echo "ISR_NO_ERROR_CODE ${i}" >> "$gen_asm"
    fi
done
