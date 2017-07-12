#!/bin/bash

file=$1
passfile=${file}_pwd
pubkey=keyfile.pub

openssl rand 256 > ${passfile}

tar cz $file | openssl enc -aes-256-cbc -salt -out ${file}.enc -pass file:./${passfile}
openssl rsautl -encrypt -pubin -inkey ${pubkey} -in ${passfile} -out ${passfile}.enc

rm ${file} ${passfile}
cp ${file}.enc ${passfile}.enc ../local
