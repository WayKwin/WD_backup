# ----------------------------
# df(磁盘信息) 0表示全部, 1表示第一行... 
# NF表示每一行分别有几列,$NF表示最后一行(注意区别)
#df | awk '{print $NF}'
# ----------------------------
# print 言外之意是按格式打印
# 所以可以按格式打印每行 例如对每一行进行: 拼接,替换
# 注意print只是打印,不影响源文件 (不支持中文)
#awk '{print "name:"$1,"sex:"$2,"age:"$3}' file
#awk '{print "name:"$1" note:happy ","sex:"$2,"age:"$3}' file
#awk '{print '33',$2}' file
# ----------------------------
# awk  pattern模式 BEGIN和END
# 注意书写格式, awk和 '之间有空格, ' 和file 之间有空格
# 其他地方没有空格要求
#awk 'BEGIN{print"name","age","sex"}{print $1,$2,$3} END{print "this", "is","end"}' file
# 建议书写格式
#awk '
#BEGIN{print"name","age","sex"}
#{print $1,$2,$3} 
#END{print "this", "is","end"}
#' file
# ----------------------------
# awk 输入输出分割符号
  # 1.输入分割符号
  #   通过该[options] -F#来分割
#awk -F# '{print $1,$2,$3}' file2
  #   通过[-v FS="#"] 来分割 其中-v 表示内部变量 FS为filed separator(输入分隔符)
#awk -v FS='#' '{print $1,$2,$3}' file2
  #2.输出分隔符号\
#awk -v OFS="__" -F# '{print $1,$2,$3}' file2
# ----------------------------
# AWK内置变量
  # NF 显示有多少列 $NF最后一列
  #  区分:NR 显示行号, FNR 分别显示所有文件的行号
#awk '{print NR,$0}' file  file2
#awk '{print FNR,$0}' file file2
# ----------------------------
  # awk 行输入输出 符号设定
#awk -v RS=' ' '{print NR,$0}' file
#awk -v ORS='{}' '{print NR,$0}' file2
# ----------------------------
  # awk FILENAME
#awk '{print FILENAME,FNR,$0}' file file2
# ----------------------------
  # awk 参数 ARGC,ARGV(注意是大写的) ARGV[0]是awk
#awk 'BEGIN{print "aaa",ARGC,ARGV[0],ARGV[1],ARGV[2]}' file file2
#awk '{print ARGC,ARGV[0],ARGV[1],ARGV[2]}' file file2
# ----------------------------
# AWK自定义变量
  #在没有输入源的时候,打印变量要在之前加上BEGIN (也就是在处理输入源之前打印变量)
  # 注意引用bash变量之间不能有空格 why??
#mystring="helloworld"
#awk -v myvar=${mystring} 'BEGIN{print myvar}' 
  # 自定义变量可以
#awk -v myvar="hello world" 'BEGIN{print myvar}' 
  #另一种定义方式 注意定义完了使用分号结束;
#awk 'BEGIN{myvar="hello world"; print myvar}'






