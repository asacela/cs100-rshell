INPUTS=("exit")

for input in "${INPUTS[@]}"
do
	echo "-----------Exit Command Test ${@}:----------"
	echo " ${input}"
	${input}

	sleep 1

	
	echo "-----------------Completed------------------"
	echo "\n\n\n\n"

done