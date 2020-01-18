echo " Compiling ... "
gcc bst.c -o my_bst
ec=$?
if [[ $ec == 0 ]]
then
	echo " Compiled Successfully ! "
	echo " use ./my_bst to run the program"
else
	echo " an error occured "
	echo " with an exit code = $ec "
fi
