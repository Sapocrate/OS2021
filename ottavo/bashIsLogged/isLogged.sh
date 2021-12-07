#!/bin/bash
if [[ $# -ne 2 ]]; then
  echo "please insert seconds and username"
  exit 1;
fi
let continue=0
while [[ $continue -eq 0 ]]; do
sleep $1
  for i in $USER; do
    if [[ $i = $2 ]]; then
      echo "user $2 actually logged in"
    else
      let continue=1
    fi
  done
done
echo "user $2 not logged..."
#exit
