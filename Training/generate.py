import sys
import shutil
import os
import subprocess


# GPT製　ディレクトリの中身をシラミ潰しにコピー
def copy_directory_contents(src_dir, dest_dir):
    # コピー先のディレクトリが存在しない場合、作成
    if not os.path.exists(dest_dir):
        os.makedirs(dest_dir)

    # src_dir の中身を一つずつコピー
    for item in os.listdir(src_dir):
        src_item = os.path.join(src_dir, item)
        dest_item = os.path.join(dest_dir, item)

        # ディレクトリなら再帰的にコピー
        if os.path.isdir(src_item):
            shutil.copytree(src_item, dest_item)
        else:
            shutil.copy2(src_item, dest_item)


# ディレクトリ名を特定
contest_name = None
try:
    contest_name = sys.argv[1]
except:
    print("コンテスト名を指定してください")
    exit()
# 問題の数
problem_n = 0
try:
    problem_n = int(sys.argv[2])
except:
    problem_n = 7

# ディレクトリのパス
path = f"./{contest_name}"

# ディレクトリ作成
os.mkdir(path)

# 問題名用リスト
problem_name_list = list("ABCDEFGHIJKLMNOPQRSTUVWXYZ")

# ./templateの中身を一つずつコピー
if problem_n > 26:
    for i in range(problem_n):
        problem_path = f"{path}/{i+1}"
        os.mkdir(problem_path)

        copy_directory_contents(".template/code", problem_path)
else:
    for i in range(problem_n):
        problem_path = f"{path}/{problem_name_list[i]}"
        os.mkdir(problem_path)

        copy_directory_contents(".template/code", problem_path)
