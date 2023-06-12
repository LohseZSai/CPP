import pandas as pd

def compare_words(word1, word2):
    #使用这个函数时，记得要加上list
    for i, (c1, c2) in enumerate(zip(word1, word2)):
        if c1 == c2:
            yield '绿'
        elif c2 in word1:
            yield '橙'
        else:
            yield '灰'

def leave(word):
    for i in word:
        if i in left:
            return False
    else:
        return True


answer = 'parer'
alist = list(answer)
#导出词库
path = r'C:\Users\Scott\Desktop\yes.txt'
with open(path,'r') as file:
    words = file.read()
    wordlist = words.split()
comparelist = [list(i) for i in wordlist]
#我的思路是运用filter函数进行过滤
newdf = pd.DataFrame({'单词':[],'p值':[]})
for i,word in enumerate(wordlist):
    result = list(compare_words(answer,word))
    #如果检验结果的某个位置上是灰色，那么使用filter函数过滤含有该字母的单词
    left = []
    #此处的思路是，如果显示灰色，回退索引，进行过滤
    for index,value in enumerate(result):
        if value == '灰':
            left.append(word[index])
    #如果该词中有显示灰色的字母，删去
    guesslist = list(filter(leave, wordlist))
    newdf = newdf.append({'单词':word, 'p值':len(wordlist) - len(guesslist)}, ignore_index=True)
    print(f'finish {i} for {len(wordlist)}')
    #此时仅剩下橙色和绿色的组合
newdf.to_excel(r'C:\Users\Scott\Desktop\nogrey.xlsx')


    
        

