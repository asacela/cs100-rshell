INPUTS=("[ -e ../integration_tests ]" " [ -f ../integration_tests ]" " [ -d ../integration_tests ]")

for input in "${INPUTS[@]}"
do
	echo "---------Test Symbolic Single Command Test ${@}:----------"
	echo " ${input}"
	${input}

	sleep 1

	
	echo "-----------------Completed------------------"
	echo "\n\n\n\n"

done

INPUTS2=("(echo hello && ( [ -e integration_tests ])) || ls -j" "( [ -d ../unit_tests ]) && echo test" "ls -j || [ -f ../header ] || ls -j")

for input2 in "${INPUTS2[@]}"
do
        echo "---------Test Symbolic Commpound Command Test ${@}:----------"
        echo "${input2}"
        ${input2}
        sleep 1


        echo "-----------------Completed------------------"

done
     
