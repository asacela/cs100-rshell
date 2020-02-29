INPUTS1=(" test -e integration_tests " "test -e ../unit_tests" "test -e ../header")



for input1 in "${INPUTS1[@]}"
do
	echo "---------Test Literal Single Command Test ${@}:----------"
	echo "${input1}"
	${input1}
	sleep 1

	
	echo "-----------------Completed------------------"

done


INPUTS2=("(echo hello && (test -e integration_tests)) || ls -j" "(test -e ../unit_tests) && echo test" "ls -j || test -e ../header || ls -j")

for input2 in "${INPUTS2[@]}"
do
        echo "---------Test Literal Commpound Command Test ${@}:----------"
        echo "${input2}"
        ${input2}
        sleep 1


        echo "-----------------Completed------------------"

done
