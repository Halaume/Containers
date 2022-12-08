#! /bin/bash

VECTOR_LOC=""

echo "${VECTOR_LOC}"
source ../config.sh
echo "${VECTOR_LOC}"

if [ -z ${VECTOR_LOC} ]
then
	echo "Vector location not provided in config.sh"
	exit 1
elif [ ${VECTOR_LOC::1} == "." ]
then
	VECTOR_LOC="../${VECTOR_LOC}"
fi

FORMAT='%-15s %-15s %-15s\n'
FIELD_SIZE='%-15s'
RET=0

if [ $# -ne 0 ]
then
	if [ "$1" == "clean" ]
	then
		for f in srcs/*; \
		do
			f=${f:5}
			make --no-print-directory SRC="${f}" NAME="${f::-4}" clean
			make --no-print-directory SRC="${f}" NAME="${f::-4}" ISFT=1 clean
		done
	elif [ "$1" == "fclean" ]
	then
		for f in srcs/*; \
		do
			f=${f:5}
			make --no-print-directory SRC="${f}" NAME="${f::-4}" fclean
			make --no-print-directory SRC="${f}" NAME="${f::-4}" ISFT=1 fclean
		done
		rm -rf logs/*; rm -rf diff/*
	elif [ "$1" == "re" ]
	then
		rm -rf logs/*; rm -rf diff/*
		for f in srcs/*; \
		do
			f=${f:5}
			make --no-print-directory SRC="${f}" NAME="${f::-4}" re
			make --no-print-directory SRC="${f}" NAME="${f::-4}" ISFT=1 re
		done
		rm -rf logs/*; rm -rf diff/*
	elif [ "$1" == "build" ]
	then
		for f in srcs/*; \
		do
			f=${f:5}
			make --no-print-directory SRC="${f}" NAME="${f::-4}" VECTOR_LOCATION="${VECTOR_LOC}"
			make --no-print-directory SRC="${f}" NAME="${f::-4}" ISFT=1 VECTOR_LOCATION="${VECTOR_LOC}"
		done
		rm -rf logs/*; rm -rf diff/*
	else
		echo "Unrecognized argument";
	fi
	exit 0
fi

rm -rf logs/*; rm -rf diff/* ; \
mkdir -p bin; mkdir -p logs; mkdir -p diff; mkdir -p objs ; \
if ! test -f "${VECTOR_LOC}/vector.hpp" ;
then
	echo "vector.hpp not found at ${VECTOR_LOC}/vector.hpp";
	exit 1;
fi
printf "%-35s   ${FORMAT}" "TEST" "COMPILATION" "VALGRIND" "DIFF";
for f in srcs/*; \
do
	f=${f:5}
	printf '%-35s   ' $f;
	if ! make --no-print-directory SRC="${f}" NAME="${f::-4}" VECTOR_LOCATION="${VECTOR_LOC}" &>/dev/null;
	then
		if make --no-print-directory SRC="${f}" NAME="${f::-4}" ISFT=1 VECTOR_LOCATION="${VECTOR_LOC}" &>/dev/null;
		then
			printf "${FORMAT}" "Should not compile" "?" "KO"; continue;
		else
			printf "${FORMAT}" "OK" "OK" "OK"; continue;
		fi
	else
		if ! make --no-print-directory SRC="${f}" NAME="${f::-4}" ISFT=1 VECTOR_LOCATION="${VECTOR_LOC}" &>/dev/null ;
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
