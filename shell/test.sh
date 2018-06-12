#!/bin/bash
#echo "hello world"
#str='world'
#str1=hello
#str2="right"
#echo  $str$str1$str2
#myint=100
#((myint++))
#进行算数
#res=$((myint + 2))
#echo $res

i=1
#echo ${i}
#从1到100求和
sum=0
echo $i
echoStr=''

 while [ $i -le 100 ]


do
  #echo $((i++))
  let sum+=i
  if [ -z "$echostr" ]; then
    echoStr=$i
  else
    echoStr=$echostr '+' $i
  fi
  let i++
done

echo $echoStr=$sum








