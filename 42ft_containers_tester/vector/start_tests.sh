#! /bin/bash

VECTOR_LOCATION="../inc"

FORMAT='%-15s %-15s %-15s\n'
FIELD_SIZE='%-15s'
RET=0
LINE=1

rm -rf logs/*; rm -rf diff/* ; \
mkdir -p bin; mkdir -p logs; mkdir -p diff; mkdir -p objs ; \
if ! test -f "../${VECTOR_LOCATION}/vector.hpp" ;
then
	echo "vector.hpp not found";
	exit 1;
fi
printf "%-35s   ${FORMAT}" "TEST" "COMPILES" "VALGRIND" "DIFF";
for f in srcs/*; \
do
	f=${f:5}
	printf '%-35s   ' $f;
	if ! make SRC="${f}" NAME="${f::-4}" &>/dev/null;
	then
		if make SRC="${f}" NAME="${f::-4}" ISFT=1 &>/dev/null;
		then
			printf "${FORMAT}" "Should not compile" "?" "KO"; continue;
		else
			printf "${FORMAT}" "OK" "OK" "OK"; continue;
		fi
	else
		if ! make SRC="${f}" NAME="${f::-4}" ISFT=1 &>/dev/null;
		then
			printf "${FORMAT}" "Does not compile" "?" "KO"; continue;
		else
			printf "${FIELD_SIZE} "	"OK";
		fi
	fi
	"bin/${f::-4}_std" 2>/dev/null >"logs/${f::-4}_std.log" | :
	(trap 'RET=1;' CHLD;
	if ! valgrind --leak-check=full --error-exitcode=1 "bin/${f::-4}_ft" &>/dev/null >"logs/${f::-4}_ft.log"  ;
	then
		if [ $RET -eq 1 ]
		then
			printf "${FIELD_SIZE} "	"KO"; RET=0;
		else
			printf "${FIELD_SIZE} "	"KO";
		fi
	else
		printf "${FIELD_SIZE} "	"OK";
	fi) 2>/dev/null
	if ! diff "logs/${f::-4}_std.log" "logs/${f::-4}_ft.log" >"diff/${f::-4}.log";
	then
		printf "${FIELD_SIZE}\n"	"KO";
	else
		printf "${FIELD_SIZE}\n"	"OK";
	fi
done;
