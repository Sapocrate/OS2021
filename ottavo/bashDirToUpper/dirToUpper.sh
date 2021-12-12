#!/bin/bash
# passato come parametro una directory, i file in essa presenti verranno rinominati in caps
if [[ $# -ne 1 ]]; then
  echo "please pass only one directory"
fi
#itero su ogni elemento della ls --> ovvero tutti i files della directory
for fi in `ls $1`;
do
  #per ogni nome di file eseguo un cut per tenere l'estensione
  nome="$(cut -d'.' -f1 <<<$fi)"
  estensione="$(cut -d'.' -f2 <<<$fi)"
  mv "${1}/${fi}" "${1}/${nome^^}.${estensione}" #passo da file normale a file caps

done
#exit
