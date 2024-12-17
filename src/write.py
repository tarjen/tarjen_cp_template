import os

# 遍历文件夹
folder_path = "src/data_structure"  # 文件夹路径
for file_name in os.listdir(folder_path):
    if os.path.isfile(os.path.join(folder_path, file_name)):
        # 输出文件名对应的两句话
        print(f"== {file_name.split('.')[0]}")
        print(f"#import_code(\"{folder_path}/{file_name}\")")