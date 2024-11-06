import sys
import shutil
import os


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


# ディレクトリのパス
path = f"./tessoku-book"

# ディレクトリ作成
os.mkdir(path)

# 問題名用リスト
problem_name_list = list("ABCDEFGHIJKLMNOPQRSTUVWXYZ")

for i in range(1, 78):
    problem_path = f"{path}/A{i}"
    os.mkdir(problem_path)

    copy_directory_contents(".template/code", problem_path)

for i in list(range(1, 46)) + list(range(51, 70)):
    problem_path = f"{path}/B{i}"
    os.mkdir(problem_path)

    copy_directory_contents(".template/code", problem_path)

for i in range(1, 21):
    problem_path = f"{path}/C{i}"
    os.mkdir(problem_path)

    copy_directory_contents(".template/code", problem_path)
