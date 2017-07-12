#!/bin/bash

file=$1
passfile=${file%.enc}_pwd.enc
privatekey=keyfile.key

openssl rsautl -decrypt -inkey ${privatekey} -in ${passfile} -out ${passfile%.enc}
openssl enc -d -aes-256-cbc -in ${file} -pass file:./${passfile%.enc} | tar xz

rm ${file} ${passfile} ${passfile%.enc}

