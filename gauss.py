def gauss(mat, ans):
    n, m = len(mat), len(ans)    
    EPS = 10**(-4)
    where = [-1 for _ in range(m)]
    
    row = 0
    for col in range(m):
        if row >= n: break
        
        sel = row
        for i in range(row, n):
            if abs(mat[i][col]) > abs(mat[sel][col]):
                sel = i
        if abs(mat[sel][col]) < EPS:
            continue
        mat[sel], mat[row] = mat[row], mat[sel]
        where[col] = row
        
        for j in reversed(range(col, m + 1)):
            mat[row][j] = mat[row][j] / mat[row][col]
        for i in range(n):
            if i != row:
                for j in reversed(range(col, m + 1)):
                    mat[i][j] -= mat[i][col] * mat[row][j]
        row += 1
    
    for i in range(len(ans)):
        ans[i] = 0.
    for i in range(m):
        if where[i] != -1:
            ans[i] = mat[where[i]][m] / mat[where[i]][i]
            # print(mat[where[i]][m])
    
    for i in range(n):
        sum = 0.
        for j in range(m):
            sum += ans[j] * mat[i][j]
        if abs(sum - mat[i][m]) > EPS:
            return "NO"
    for i in range(m):
        if where[i] == -1:
            return "INF"
    return "YES"


def main():
    n, m = map(int, input().split())
    mat = [list(map(float, input().split())) for _ in range(n)]
    ans = [0 for _ in range(m)]
    answer = gauss(mat, ans)
    print(answer)
    if answer == "YES":
        print(*ans, sep=' ')

if __name__ == "__main__":
    main()