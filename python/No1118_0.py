# 読み込むファイル名
Files = ['nozomi.txt', 'hayabusa.txt', 'yokosukasobu.txt']

# 隣駅を格納する辞書
Neighbors = {}

# 各ファイルを開いて1行ずつ処理
for Filename in Files:
    MyFile = open(Filename, 'r')
    Lines = MyFile.readlines()
    Lines = [line.strip() for line in Lines]

    # 隣駅を登録（両方向）
    for i in range(len(Lines)):
        station = Lines[i]

        if station not in Neighbors:
            Neighbors[station] = set()

        # 前の駅
        if i > 0:
            Neighbors[station].add(Lines[i-1])

        # 次の駅
        if i < len(Lines) - 1:
            Neighbors[station].add(Lines[i+1])

# 出力ファイルへ書き込み
OutFile = open('stations.txt', 'w')

for station, adj in Neighbors.items():
    # set をカンマ区切り文字列へ
    nexts = ", ".join(adj)
    OutFile.write(f"{station}：{nexts}\n")

OutFile.close()
