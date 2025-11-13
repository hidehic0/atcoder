#!/bin/sh

CMD=$1
PROGRAM_FILE=$2
OUTPUT_FILE=$3

echo "CMD: " $CMD

if [ ! -e $OUTPUT_FILE ] || [ $OUTPUT_FILE -ot $PROGRAM_FILE ]; then
	$CMD
else
	echo "INFO: build skipped"
fi
