#!/bin/sh

set -x
./lexer ">>>>>>>"
./lexer "> > > >"
./lexer ">> >> >> >>"
./lexer "| || | ||"
./lexer "&&&"
./lexer ";;;;;"
./lexer "()"
./lexer "((((()))))"
./lexer "*"
./lexer '$hello $ $12!34'
