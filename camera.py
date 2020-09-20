import re
import sys
def output():
    '''print("V = {")'''
    cmt = 1
    for key in Vertices:
        '''print("  ",cmt,':'," ","(",key[0],",",key[1],")",sep='')'''
        cmt = cmt+1
    '''print("}")'''
    print("V",cmt-1)
    sys.stdout.flush()
    '''print("E = {")
    cmt = 1
    ind=len(Edges)
    for key in Edges:
        ind=ind-1
        if ind>0:
            print(" "," ","<",key[0],",",key[1],">",",",sep="")
        if ind==0:
            print(" "," ","<",key[0],",",key[1],">",sep="")

    print("}")'''

    a=[];
    b=[];
    for i in Edges.keys():
        a.append(i)
    '''print(a)'''
    for i in a:
        for j in range(len(i)):
            m=i[j]-1
            b.append(m)
    '''print(b)'''
    print("E {",end='')
    sys.stdout.flush()
    cnt = 0
    for i in b:
        if cnt<len(b)-2:
            print("<",b[cnt],",",b[cnt+1],">",",", sep='',end='')
            sys.stdout.flush()
            cnt = cnt + 2
            if cnt == len(b)-2:
                print("<",b[cnt],",",b[cnt+1],">",sep='',end='')
                sys.stdout.flush()
    print("}")
    sys.stdout.flush()

def seperate(targ):
    v = targ.split(',')
    int(v[0])
    int(v[1])
    return (int(v[0]), int(v[1]))

def check_command(x):
    check = re.match(r'^\s*([acrg])(.*)$', x)
    if check:
        command = check.group(1)
        return command
    else:
        return False

def check_streetname(x):
    check = re.match(r'(.*)(\"[a-zA-Z\s*]+\")(.*)$', x)
    if check:
        return check.group(2).lower()
    else:
        return False

def check_point(x):
    check = re.match(r'(.*)\"\s*((\(-?\d+\s*\,\s*-?\d+\s*\)\s*)+)', x)
    if check == None:
        return False
    box = check.group(2)
    if check == None:
        return False
    else:
        coor = box
        pattern = re.compile(r'\-?\d+\,-?\d+')
        coordinates = pattern.findall(coor)
        pointlist = tuple(map(seperate, coordinates))
        return pointlist

def add_street(x, stname):
    p = check_point(x)
    line = makeline(p)
    Street[stname] = line

def remove_street(x):
    del Street[check_streetname(x)]

def change_street(x, stname):
    remove_street(x)
    add_street(x, stname)

class Point():
    def __init__(self, x, y):
        self.x = x
        self.y = y

class Line():
    def __init__(self, head, end):
        self.head = head
        self.end = end

def makeline(x):
    linecollection = []
    for i in range(len(x)-1):
        point1 = Point(x[i][0], x[i][1])
        point2 = Point(x[i + 1][0], x[i + 1][1])
        ln = Line(point1, point2)
        linecollection.append(ln)
    return linecollection

def CheckExsit(x, y, Intersections):
    if (x, y) not in Intersections:
        if (x, y) not in Vertices:
            AddVertex((x,y))
        Intersections[(x,y)] = VerticesFda[(x,y)]

def subseg(Interrr, Intersections):
    for p in Interrr:
        if (p.x, p.y) not in Vertices:
            AddVertex((p.x, p.y))
        if (p.x, p.y) not in Intersections:
            Intersections[(p.x, p.y)] = VerticesFda[(p.x, p.y)]


def FindEdges(Intersections):
    if len(Intersections) < 2:
        return False
    ans = sorted(Intersections.items(), key=lambda item: item[0][0])
    ans = sorted(ans, key=lambda item: item[0][1])
    return ans

def Find_VerticesEdges(Street):
    Intersections = {}
    flag = 0
    for s1 in Street:
        for line1 in Street[s1]:
            for s2 in Street:
                if s1 == s2:
                    continue
                for line2 in Street[s2]:
                    if check_intersection(line1, line2) == False:
                        continue
                    flag = 1
                    Interrr = check_intersection(line1, line2)

                    CheckExsit(line1.head.x, line1.head.y, Intersections)
                    CheckExsit(line1.end.x, line1.end.y, Intersections)

                    if (line2.head.x, line2.head.y) not in Vertices:
                        AddVertex((line2.head.x, line2.head.y))
                    if (line2.end.x, line2.end.y) not in Vertices:
                        AddVertex((line2.end.x, line2.end.y))

                    subseg(Interrr, Intersections)

            Interrr = []
            if (flag == 1) :
                Interrr = FindEdges(Intersections)
                if (Interrr == False) :
                    continue
                for i in range(len(Interrr)-1):
                    Edges[(Interrr[i][1], Interrr[i+1][1])] = 1
            Intersections = {}
            flag = 0

def AddVertex(vertex):
    if vertex not in VerticesFda:
        l = len(VerticesFda) + 1
        VerticesFda[vertex] = l
        Vertices[vertex] = l
    else:
        Vertices[vertex] = VerticesFda[vertex]
def clean_dictionary(x):
    x.clear()
def check_intersection(line1, line2):
    ##(ca x cd)·(cb x cd) <= 0 & & (ad x ab)·(ac x ab) <= 0
    A = (line2.head.x - line1.head.x) * (line1.end.y - line1.head.y) - (line2.head.y - line1.head.y) * (
                line1.end.x - line1.head.x)
    B = (line2.end.x - line1.head.x) * (line1.end.y - line1.head.y) - (line2.end.y - line1.head.y) * (
                line1.end.x - line1.head.x)
    C = (line1.end.x - line2.head.x) * (line2.end.y - line2.head.y) - (line1.end.y - line2.head.y) * (
                line2.end.x - line2.head.x)
    D = (line1.head.x - line2.head.x) * (line2.end.y - line2.head.y) - (line1.head.y - line2.head.y) * (
                line2.end.x - line2.head.x)
    # yi shuzhi
    c = 10000
    d = 10000

    # chonghe1: shuzhi
    if (line1.head.x==line1.end.x == line2.head.x==line2.end.x) :
        if ((line1.head.y<=line2.head.y) and (line1.head.y>=line2.end.y)) \
                or ((line2.head.y<=line1.head.y and line2.head.y>=line1.end.y))\
                or (line2.head.y<=line1.head.y and line2.end.y>=line1.end.y)\
                or (line1.head.y<=line2.head.y and line1.end.y>=line2.end.y):
            pli = [line1.head, line1.end, line2.head, line2.end]
            res = sorted(pli, key=lambda item:item.y)
            return res[1:3]
    ##chonghe shuiping
    if (line1.head.y == line1.end.y == line2.head.y == line2.end.y):
        if (line1.head.x <= line2.head.x) and (line1.head.x >= line2.end.x) \
                or (line2.head.x <= line1.head.x and line2.head.x >= line1.end.y)\
                or (line2.head.x<=line1.head.x and line2.end.x>=line1.end.x)\
                or (line1.head.x<=line2.head.x and line1.end.x>=line2.end.x):
            pli = [line1.head, line1.end, line2.head, line2.end]
            res = sorted(pli, key=lambda item:item.x)
            return res[1:3]
    ##xielvpingxing
    elif (line1.head.x-line1.end.x)!=0 \
            and (line1.head.y-line1.end.y)!=0 \
            and (line2.head.x-line2.end.x)!=0 \
            and (line2.head.y-line2.end.y)!=0 \
            and ((line1.head.y-line1.end.y)/(line1.head.x-line1.end.x)==(line2.head.y-line2.end.y)/(line2.head.x-line2.end.x)):
        if (line2.head.y-line1.end.y)/(line1.head.y-line1.end.y)==(line2.head.x-line1.end.x)/(line1.head.x-line1.end.x) \
                or (line2.end.y - line1.end.y) / (line1.head.y - line1.end.y) == (line2.end.x - line1.end.x) / (line1.head.x - line1.end.x):
            c=line1.head.x
            d=line1.head.y

    elif (line1.end.x - line1.head.x) == 0 and (line2.end.x - line2.head.x) != 0:
        if A * B <= 0 and C * D <= 0:
            k_2 = (line2.end.y - line2.head.y) / (line2.end.x - line2.head.x)
            b_2 = line2.head.y - (line2.end.y - line2.head.y) / (line2.end.x - line2.head.x) * line2.head.x
            c = line1.head.x
            d = k_2 * c + b_2
        else:
            pass
    elif (line1.end.x - line1.head.x) != 0 and (line2.end.x - line2.head.x) == 0:
        if A * B <= 0 and C * D <= 0:
            k_1 = (line1.end.y - line1.head.y) / (line1.end.x - line1.head.x)
            b_1 = line1.head.y - (line1.end.y - line1.head.y) / (line1.end.x - line1.head.x) * line1.head.x
            c = line2.head.x
            d = k_1 * c + b_1
        else:
            pass
    ##yi shuiping
    elif (line1.end.y - line1.head.y) == 0 and (line2.end.y - line2.head.y) != 0:
        if A * B <= 0 and C * D <= 0:
            if (line2.end.x - line2.head.x) == 0:
                c = line2.head.x
                d = line1.head.y
        if A * B <= 0 and C * D <= 0 and (line2.end.x - line2.head.x) != 0:
            k_2 = (line2.end.y - line2.head.y) / (line2.end.x - line2.head.x)
            b_2 = line2.head.y - (line2.end.y - line2.head.y) / (line2.end.x - line2.head.x) * line2.head.x
            d = line2.head.y
            c = (d - b_2) / k_2
        else:
            pass
    elif (line1.end.x - line1.head.x) != 0 and (line2.end.x - line2.head.x) == 0:
        if A * B <= 0 and C * D <= 0:
            k_1 = (line1.end.y - line1.head.y) / (line1.end.x - line1.head.x)
            b_1 = line1.head.y - (line1.end.y - line1.head.y) / (line1.end.x - line1.head.x) * line1.head.x
            d = line1.head.y
            c = (d - b_1) / k_1
        else:
            pass
    ##liangshuiping
    elif (line2.end.y - line2.head.y) == 0 and (line1.end.y - line1.head.y) == 0:
        if A * B <= 0 and C * D <= 0:
            if line1.head.x == line2.head.x or line1.head.x == line2.end.x:
                c = line1.head.x
                d = line1.head.y
            elif line1.end.x == line2.head.x or line1.end.x == line2.end.x:
                c = line1.end.x
                d = line1.end.y
            elif line2.head.x == line1.head.x or line2.head.x == line1.end.x:
                c = line2.head.x
                d = line2.head.y
            elif line2.end.x == line1.head.x or line2.end.x == line1.end.x:
                c = line2.end.x
                d = line2.end.y
        else:
            pass
    ##liangshuzhi
    elif (line2.end.x - line2.head.x) == 0 and (line1.end.x - line1.head.x) == 0:
        if A * B <= 0 and C * D <= 0:
            if line1.head.y == line2.head.y or line1.head.y == line2.end.y:
                c = line1.head.x
                d = line1.head.y
            elif line1.end.y == line2.head.y or line1.end.y == line2.end.y:
                c = line1.end.x
                d = line1.end.y
            elif line2.head.y == line1.head.y or line2.head.y == line1.end.y:
                c = line2.head.x
                d = line2.head.y
            elif line2.end.y == line1.head.y or line2.end.y == line1.end.y:
                c = line2.end.x
                d = line2.end.y
        else:
            pass
    ##k!=0
    elif (A * B <= 0) and (C * D <= 0) and (line1.end.x - line1.head.x) != 0 and (line2.end.x - line2.head.x) != 0:
        k_1 = (line1.end.y - line1.head.y) / (line1.end.x - line1.head.x)
        k_2 = (line2.end.y - line2.head.y) / (line2.end.x - line2.head.x)
        b_1 = line1.head.y - (line1.end.y - line1.head.y) / (line1.end.x - line1.head.x) * line1.head.x
        b_2 = line2.head.y - (line2.end.y - line2.head.y) / (line2.end.x - line2.head.x) * line2.head.x
        c = (b_2 - b_1) / (k_1 - k_2)
        d = k_1 * c + b_1

    if (c == 10000 or d == 10000):
        return False

    c = round(c, 2)
    d = round(d, 2)
    '''
    c = Decimal(c).quantize(Decimal('0.00'))
    d = Decimal(d).quantize(Decimal('0.00'))
    '''
    pointArr = [Point(c, d)]
    return pointArr
Street = {}
Vertices = {}
VerticesFda = {}
Edges = {}
Graph = {}

while True:
    line = sys.stdin.readline()

    if line == '':
        sys.exit(0)

    cmd = check_command(line)
    stname = check_streetname(line)
    point = check_point(line)
    if cmd==False:
        '''print("Error:wrong format ")'''
        continue
    else:
        if cmd == "a":
            if stname == False or point == False:
                '''print("Error: wrong format")'''
                continue
            if stname in Street:
                '''print("Error:street already exist")'''
                continue
            else:
                add_street(line, stname)
        if cmd == "c":
            if stname == False or point == False:
                '''print("Error: wrong format")'''
                continue
            if stname not in Street:
                '''print("Error: 'c' or 'r' specified for a street that does not exist.")'''
                continue
            else:
                remove_street(line)
                add_street(line, stname)
        if cmd == "r":
            if stname == False:
                '''print("Error: wrong format")'''
                continue
            if stname not in Street:
                '''print("Error: 'c' or 'r' specified for a street that does not exist.")'''
                continue
            else:
                remove_street(line)
        if cmd == "g":
            Edges = {}
            Vertices = {}
            VerticesFda = {}
            Find_VerticesEdges(Street)
            output()
            clean_dictionary(Edges)
            clean_dictionary(Vertices)
            clean_dictionary(VerticesFda)
            clean_dictionary(Street)
