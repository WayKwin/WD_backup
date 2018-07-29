#read mystring
#[ $mystring == "hello" ]
#echo $?
#[ -c /dev/tty ]
#echo $?
#[ -f learn1.sh ]
#echo $?
#read mystring
# 注意方括号 和等号之间有空格
#if [ $mystring == "hello" ]
#then
  #echo "get hello"
#fi
printf "please Enter number: "
read number

if [ $number -lt 100 ]; then
  if [ $number -eq 50 ]; then 
        echo "the number is 50"
  elif [ $number -lt 50 ];then
          echo " the number is less than 50"
  else
          echo "the number is between 50 and 100"
fi
else 
    echo "data is great than 100"
fi
