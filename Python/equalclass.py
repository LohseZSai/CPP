# coding=gbk
#���Ȳ���warshall���ӳ��������󴫵ݱհ�
import numpy as np
#warshall���󴫵ݱհ��Ĵ���
def Warshall(A, n):
    for k in range(n):
        for i in range(n):
            for j in range(n):
                A[i][j] = A[i][j] or (A[i][k] and A[k][j])

    return A
#��һ�����������
#����ϵ�ȼۣ��������Է��ԡ��Գ��ԡ�������
def Equals(B,m):
    #��һ���ж��Է��ԣ��������Է��ԵĻ�����ϵ����Խ�����Ԫ��֮��Ӧ��Ϊ����
    if np.trace(B) == m:
       for i in range(B.shape[0]):
        for j in range(B.shape[1]):
            if B[i][j] == B[j][i]:
                if Warshall(B,m).all() == B.all():
                    return "�ù�ϵ�ǵȼ۹�ϵ"
                else:
                    return "�ù�ϵ���ǵȼ۹�ϵ"
            else:
                return "�ù�ϵ���ǵȼ۹�ϵ"

    else:
        return "�ù�ϵ���ǵȼ۹�ϵ"

#�ú�����������ȼ���
def output(A,x):
    B = set()
    a = []
    while len(B) != 6:
        for i in A:
            count = 0
            C = set()
            for j in i:
                count += 1
                if j == 1:
                    C.add(count)
                    
            a.append(C)
        b = [str(i) for i in a]
        return set(b)
        
       
                    
                        
        
         #������Ԫ�أ�ÿһ�ζ�����һ���ȼ��༯��
        
    


#�������Ľ�������ϵ����Ϣ
n = int(input())
x = {1,2,3,4,5,6}
amat = [[0]*n for k in range(n)]
R = [(1,1),(2,2),(3,3),(4,4),(5,5),(6,6),(1,4),(2,3),(2,6),(3,2),(3,6),(4,1),(6,2),(6,3)]
for i,j in R:
    amat[i-1][j-1] = 1
amat = np.array(amat)
print(Equals(amat,n))
print(amat)
print(f"�ȼ������Ϊ��{output(amat,x)}")
#if Equals(amat,n) == '�ù�ϵ�ǵȼ۹�ϵ':
    




