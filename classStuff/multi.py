a = []
b = []
n = input('enter size of matrix:')
print 'enter elements of matrix 1'
for i in range(n):
    a.append(map(int,raw_input().strip().split(' ')))
print 'enter elements of array 2'
for i in range(n):
    b.append(map(int,raw_input().strip().split(' ')))
c = []
for i in range(n):
    c.append([])
    for j in range(n):
        c[i].append(0)

for i in range(n):
    for j in range(n):
        for k in range(n):
            c[i][j] += a[i][k] + b[k][j]
print 'product matrix-'
for i in range(n):
    for j in range(n):
        print c[i][j],
    print
    