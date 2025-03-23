def main():
    numVar = int(input())
    numClauses = int(input())
    condList = []
    for m in range(0,numClauses):
        a,b,c = input().split()
        condList.append([int(a),int(b),int(c)])
    assignVar = input().split()
    for n in range(0,numVar):
        assignVar[n] = int(assignVar[n])
    for m in range(0,numClauses):
        localFlag = False
        for n in range(0,3):
            pos = condList[m][n]
            if pos > 0 and assignVar[pos-1]==1:
                localFlag = True
                break
            if pos < 0 and assignVar[-pos-1]==0:
                localFlag = True
                break
        if not localFlag:
            print("BAD")
            return
    print("GOOD")    
    
    
    
if __name__ == '__main__':
    main()
