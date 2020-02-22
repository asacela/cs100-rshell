INPUTS=("git status && echo world" "ls -a || echo \"no way\";" "ls -a -l -j || ./single_command_tests")

for input in "${INPUTS[@]}"
do
	echo "--------Multiple Command Test ${@}:---------"
	echo " ${input}"
	${input}

	sleep 1

	
	echo "-----------------Completed------------------"
	echo "\n\n\n\n"

done