#!/bin/bash

# a very dumb script for testing crossfade

function msg {
    echo "${@}" 1>&2
}

function die {
    msg "${@}"
    exit 1
}

if [[ ! -c "${1}" ]]; then
    die "\$1 must be a char device"
fi

val="${3}"
ratio="${2}"
read b1 b2 < <(perl -E '($r, $v) = @ARGV; say $r, " ", (1 - $r)' "${2}" "${3}")

echo -e "set ch1 val ${val};set ch2 val ${val};set ch1 blend ${b1};set ch2 blend ${b2}" | tee "${1}"
