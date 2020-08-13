#!/bin/bash
#./a.out $1 | sort | column -t -s,
A=3
if [ "${1::1}" == "b" ] || [ "${1::1}" == "B" ]; then  #Sjekker kommandolinjeargument
  A=1
elif [ $# == 0 ]; then                                 #Hvis ingen kommandolinjeargument, sjekk miljøvariabel
  if [ "${OBLIG::1}" == "b" ] || [ "${OBLIG::1}" == "B" ]; then
    A=1
  fi
fi

./a.out $1 | sort | while read -r LINJE ; do
    BRUKERNAVN=$(echo $LINJE | cut -f$A -d,)            #Hent brukernavn fra linje
    if [ -f /home/$BRUKERNAVN/public_html/pub_key.asc ]; then
       NOKKELPAR=J
    else
       NOKKELPAR=N
    fi
    echo "$LINJE,$NOKKELPAR" 
done

