import datetime
import subprocess

import selection

gh_version = subprocess.run(["gh", "version"], stdout=subprocess.PIPE, text=True)

if gh_version.returncode != 0:
    print("github cliはインストールされていますか?")
    exit()
else:
    print(gh_version.stdout)

contests = selection.select(int(input("使うコンテスト数は、いくつですか: ")))

with open("issue.md", "w") as f:
    f.writelines(
        [
            f"- [ ] [{contest_name}](https://atcoder.jp/contests/{contest_name.lower()}) \n"
            for contest_name in contests
        ]
    )

subprocess.run(
    [
        "gh",
        "issue",
        "create",
        "--title",
        datetime.datetime.now().strftime("%Y %m/%d") + "のバチャコン精進",
        "--body-file",
        "issue.md",
    ]
)
