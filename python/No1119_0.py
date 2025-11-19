# 読み込むファイル名
Filename = 'patients.txt'

infect_cd = {}
# cases day
infect_ca = {}
# cases age
infect_cg = {}
# cases gender

MyFile = open(Filename, 'r', encoding='utf-8', errors='replace')
Lines = MyFile.readlines()
Lines = [line.strip() for line in Lines]

# 日付別の感染者数を数える
for i in range(len(Lines)):
    rawdata = Lines[i]
    spritdata = rawdata.split('\t')
    day = spritdata[1]
    age_group = spritdata[2]
    sex = spritdata[3]

    if day in infect_cd:
        infect_cd[day]+=1
    else:
        infect_cd[day]=1

    if age_group in infect_ca:
        infect_ca[age_group]+=1
    else:
        infect_ca[age_group]=1

    if sex in infect_cg:
        infect_cg[sex]+=1
    else:
        infect_cg[sex]=1



# 出力ファイルへ書き込み
OutFile = open('cases_day.txt', 'w')

for day, count in infect_cd.items():
    OutFile.write(f"{day}：{count}\n")

OutFile.close()

print ("i)\nOutputing the results to \"cases_day.txt\" was success\n")

print ("ii)\n")
for age, count in infect_ca.items():
    print (f"{age}：{count}")
print ("\n")

print ("iii)\n")
for sex, count in infect_cg.items():
    print (f"{sex}：{count}")
print ("\n")
