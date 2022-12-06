
def checkWord(arg):
  arg = arg.strip()
  if(arg.isalpha() and len(arg)<15):
    arg = arg.lower()
    return True
  else:
    return False
def changeWord(arg):
  if checkWord(arg):
    out = arg.lower();
    return out;
  
input = open("input/english3.txt", 'r')
output = open("output/my_words2.txt", 'w')
count = 0
for line in input:
  curString = line
  if(checkWord(curString)):
    curString = changeWord(curString)
    output.write(curString)
    count+=1
    print(count)
  else:
    print("fail")
