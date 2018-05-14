a = []
n = input('enter size of matrix:')
print 'enter elements of matrix '
for i in range(n):
    a.append(map(int,raw_input().strip().split(' ')))
c = []
for i in range(n):
    c.append([])
    for j in range(n):
        c[i].append(a[i][j])

for i in range(n):
    for j in range(n):
        for k in range(n):
            if(c[i][j] > c[i][k] + c[k][j]):
                c[i][j] = c[i][k] + c[k][j]

print 'elements of duplicate matrix are'
for i in range(n):
    for j in range(n):
        print c[i][j],
    print