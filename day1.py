test = {}
elfcalories = []

def ParseText(s):
    iterator = 0
    split = s.split("\n\n")
    for elf in split:
        sum = 0
        split2 = elf.split("\n")
        for x in split2:
            sum = int(x) + sum
        elfcalories.append(sum)
        iterator += 1

def FindMax(elves):
    max = 0
    max2 = 0
    max3 = 0
    iterator = 0
    for elf in elves:
        if elf > max:
            max3 = max2
            max2 = max
            max = elf
        elif elf > max2:
            max3 = max2
            max2 = elf
        elif elf > max3:
            max3 = elf
        iterator += 1
    sum = max + max2 + max3
    print(max)
    print(sum)
    
test = open("day1.txt")
ParseText(test.read())
FindMax(elfcalories)