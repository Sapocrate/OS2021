#!/bin/bash

if [[ $# -ne 1 ]]; then
  echo "almeno un argomento" ;
  exit 1;
fi
IFS=: #cambio il separatore
for i in $PATH #path trasformando : in spazi
  do
  echo "cerco in $i"
  if test -e $i/$1 #se esiste
  then
    echo "esiste"
    if test -f $i/$1 #è un file
    then
      echo "è un file"
    fi
    exit 1; #se lo trovo esco
  fi
done
#exit
