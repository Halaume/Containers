#!/bin/bash
./Containers_ft > ft_output
./Containers_std > std_output
diff ft_output std_output
