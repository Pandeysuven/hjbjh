import sys
def strCompare(a, b):
    if (len(a) > len(b)):
        return 1
    if (len(b) > len(a)):
        return -1
    if (a > b):
        return 1
    if (b > a):
        return -1
    if (a == b):
        return 0
def findChar(a, b, n):
    f = []
    f.append(dict({"a": True, "len": len(a)}))
    f.append(dict( {"b": True, "len": len(b)} ))
    i = 0
    while(1):
        f.append({"one": f[i], "two": f[i+1], "len": str(int(f[i]["len"]) + int(f[i+1]["len"]) ) } )
        if (  strCompare(f[len(f)-1]["len"], n)  >= 0 ):
            break
        i += 1
    soln = f[(len(f) - 1)]
    answer = ''
    while (1):
        if ('a' in soln): 
            answer = a[int(n)-1]
            break
        if ('b' in soln):
            answer = b[int(n) - 1]
            break
        if ( strCompare( str(soln["one"]['len']),n) >= 0):
            soln = soln["one"]
        else:
            n = str( int(n) - int(soln["one"]["len"]) )
            soln = soln["two"]
    return answer
num_line = int(input(""))
for num_line in range(num_line):
    line = input("")
    strings = line.split()
    first = strings[0]
    second = strings[1]
    n = strings[2]
    answer = findChar(first, second, n)
    print(answer)
