def main():
    n = input()
    if len(n) % 2 == 0:
        cut = n[0:(len(n)//2)] 
        reversecut = cut[::-1]
        re = cut + reversecut
    
    else:
        cut = n[0:((len(n)-1)//2)]
        reversecut = n[0:(len(n)+1)//2]
        re = int(reversecut + cut)
    if int(n) < re:
        print(re)
    else:
        # n = 
        pass
if __name__ == '__main__':
    main();             