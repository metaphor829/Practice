#获取当前工作目录
import os
current_path = os.getcwd()
#获取当前目录下的.txt文件名保存在list中
file_list = [f for f in os.listdir(current_path) if f.endswith('.txt')]
#将文件名中的.txt替换成空字符
file_list = [f.replace('.txt','') for f in file_list]
name_list = [f.split(',')[0] for f in file_list]
length = len(file_list)
#截取文件名中的方向
direct_list = [f.split('(')[3].split('方')[0] for f in file_list]
for i in range(length):
    print(f"{name_list[i]}的方向为{direct_list[i]}")
#读取文件中的内容
for i in range(length):
    with open(f"{file_list[i]}.txt",'r') as f:
        content = f.read()
        #将文件中的前两行内容保存在list中
        tga_list = content.split('\n')[:2]
        tga_list =[f.split('\t')[1] for f in tga_list]
        #将tga_list中的第一个元素赋给tg_list,将第二个元素赋给ta_list
        tg_list = tga_list[0]
        ta_list = tga_list[1]
        #将文件中的前三行后内容保存在list中
        acc_list = content.split('\n')[3:]
        #取acc_list中的最大值
        acc_max = max(acc_list)
        print(f"{name_list[i]}的最大加速度为{acc_max}")
        #创建新文件.dat
        with open(f"{name_list[i]}.dat",'w') as f:
        #将tg_list和ta_list写入.dat文件中
            f.write(f"{tg_list}{','}{ta_list}\n")
        #将acc_list写入.dat文件中
            for acc in acc_list:
                f.write(acc+'\n')
                