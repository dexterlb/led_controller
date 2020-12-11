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

read v1 v2 < <(perl -E '($r, $v) = @ARGV; say $v * $r, " ", $v * (1 - $r)' "${2}" "${3}")

echo -e "set ch1 val ${v1}\nset ch2 val ${v2}" | tee "${1}"
