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

#i=1
##echo ${i}
##从1到100求和
#sum=0
#echo $i
#echoStr=''

 #while [ $i -le 100 ]


#do
  ##echo $((i++))
  #let sum+=i
  #if [ -z "$echostr" ]; then
    #echoStr=$i
  #else
    #echoStr=$echostr '+' $i
  #fi
  #let i++
#done

#echo $echoStr=$sum

# 交集
#cat file1 file2 > file3 | sort -d
## 并集
#cat file1 file2 > file3 | sort | uniq 
## 补集
#cat file1 file2 > file3 | sort | uniq -c
# paste
#paste file1 file2
#paste file1 file2 -d# -s  #转至

## cut
# 必须指定 -b,-c,-f之一
# -b按照字节来划分
#echo "hello world" | cut -b 1-3
#echo "hello world" | cut -d' ' -f2 #自定义切割符, -f2 从哪开始取

# xargs
# echo 不输出换行 -n
    
##根据根目录内容,创建同名的.log文件
#ls / | xargs  -i touch {}.log 

## awk
#awk '/^product.*$/{print $0}' data.txt
#awk '{if($2>50) print $0}' data.txt

#awk 
#'{
  #if($2>50)
    #print $0
  #else
    #print "value too small";
  #}' data.txt

  #awk 数组下标可以是字符串(hash)
 awk '
 {
  for(i=1; i<=NF;++i) {
     ++array[$i]
    }
   }END{
   for(i in array){
     print i"\t" array[i]
 }
 }
  ' world.txt



