# 导入docx库
import docx

# 参数sslist是一个列表存着课程信息，file是一个文件，已经打开
def printToFile(sslist, file):
    if len(sslist) < 2:
        file.write("?")
    else:
        file.write(sslist[1])
        file.write("\n")

# 入口函数
if __name__ == '__main__':
    document = docx.Document(r"D:\2021版计算机科学与技术专业教学大纲.docx")
    # 打开文件
    file = open(r"C:\Users\Wanxi\Desktop\test (2).cms", "w", encoding='utf-8')
    count = 0
    summ = 0
    flag = False

    # doc文档里面的段落
    for p in document.paragraphs:
        if p.text == "一、课程基本信息":
            flag = True

        # 截取课程信息
        elif p.text != "一、课程基本信息" and flag:
            count += 1
            if count != 2:
                sstr = p.text
                slist = sstr.split("：")
                printToFile(slist, file)
                # print(slist)
                if count == 9:
                    summ += 1
                    flag = False
                    count = 0
    # 关闭文件
    file.close()