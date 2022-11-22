#!/bin/bash
make
./Containers_ft > ft_output
./Containers_std > std_output
diff ft_output std_output > diff
echo "Diff done"
valgrind ./Containers_ft > ft_output_val
valgrind ./Containers_std > std_output_val
diff ft_output_val std_output_val > diff_val
echo "Diff valgrind done"
