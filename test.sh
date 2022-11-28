#!/bin/bash

echo "----FT----"

./Containers_ft > ft.log

echo "----STD----"

./Containers_std > std.log

echo "---DIFF---"

sh diff.sh

echo "------------"

exit 0
