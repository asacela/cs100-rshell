INPUTS=("(echo hello && (echo hell nah || (git status && ls -a)))" "(echo making && (ls -j || git status))" "((echo hello || ls -a) && (ls -j))")

for input in "${INPUTS[@]}"
do
	echo "---------Precedence Command Test ${@}:----------"
	echo " ${input}"
	${input}

	sleep 1

	
	echo "-----------------Completed------------------"
	echo "\n\n\n\n"

done
