import pandas as pd
import os

# 递归获取.csv文件存入到list_csv列表中，方便遍历
# 将所有文件的路径放入到listcsv列表中
def list_dir(file_dir):
    # list_csv = []
    dir_list = os.listdir(file_dir)
    for cur_file in dir_list:
        path = os.path.join(file_dir, cur_file)
        # 判断是文件夹还是文件
        if os.path.isfile(path):
            # print("{0} : is file!".format(cur_file))
            dir_files = os.path.join(file_dir, cur_file)
        # 判断是否存在.csv文件，如果存在则获取路径信息写入到list_csv列表中
        if os.path.splitext(path)[1] == '.csv':
            csv_file = os.path.join(file_dir, cur_file)
            # print(os.path.join(file_dir, cur_file))
            # print(csv_file)
            list_csv.append(csv_file)
        if os.path.isdir(path):
            # print("{0} : is dir".format(cur_file))
            # print(os.path.join(file_dir, cur_file))
            list_dir(path)
    return list_csv

paths = r'D:\citysome'
list_csv = []
list_dir(file_dir=paths)  # 获取文件

#遍历文件
for citycsv in list_csv:
    df = pd.read_csv(citycsv)
    
    # 删除重复项
    df.drop_duplicates(['楼盘名字'], keep='last', inplace=True)
    # 删除含范围价格和价格待定的项（不符合要求）
    for i, line in df.iterrows():
        try:
            int(df.loc[i, '平米均价'])#如果无法转换为int，则表明是我们不需要的数据，这时直接处理异常即可
        except:
            df.drop(i, axis=0, inplace=True)  # 删除指定行

    df.to_csv(citycsv, sep=',', index=False, header=True)  # 数据清洗后，覆盖原csv文件
