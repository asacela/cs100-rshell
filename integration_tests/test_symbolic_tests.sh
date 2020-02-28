INPUTS=("git pull" "echo hello" "ls -a" 
	"git status" "ls -j")

for input in "${INPUTS[@]}"
do
	echo "---------Single Command Test ${@}:----------"
	echo " ${input}"
	${input}

	sleep 1

	
	echo "-----------------Completed------------------"
	echo "\n\n\n\n"

done