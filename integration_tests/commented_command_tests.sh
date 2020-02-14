INPUTS=("git pull #comments")

for input in "${INPUTS[@]}"
do
	echo "--------Commented Command Test ${@}:--------"
	echo " ${input}"
	${input}

	sleep 1

	
	echo "-----------------Completed------------------"
	echo "\n\n\n\n"

done