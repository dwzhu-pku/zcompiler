import os
from types import coroutine

PATH = "./part2_opentest/functional"
COMP_COMMAND = "./build/compiler -S -t {0}/{1}.eeyore -o {0}/{1}.tigger"
MINIVM_COMMAND = "../MiniVM/build/minivm -t {0}/{1}.tigger > {0}/{1}.myout"
MINIVM_COMMAND_V2 = "../MiniVM/build/minivm -t {0}/{1}.tigger < {0}/{1}.in > {0}/{1}.myout"
APPEND_COMMAND = " sed -i '$a\\' {0}/{1}.myout && echo {2} >> {0}/{1}.myout"

def out_compare(prefix):
    file1 = f"{PATH}/{prefix}.myout"
    file2 = f"{PATH}/{prefix}.out"

    with open(file1, "r", encoding="utf-8") as file1, open(file2, 'r', encoding="utf-8") as file2:
        line_list1 = file1.read().splitlines()
        line_list2 = file2.read().splitlines()
        if (len(line_list1) != len(line_list2)):
            print("#line not match")
            return False
        for i in range(len(line_list1)):
            if line_list1[i] != line_list2[i]:
                return False
    return True


file_list = [ file for file in os.listdir(f"{PATH}") if  file.endswith("eeyore")  ]
correct_cnt = 0

for idx, file in enumerate(file_list):
    prefix = file[:-7]

    # if prefix != "42_index_func_ret":
    #     continue
    try:
        res1 = os.system(COMP_COMMAND.format(PATH, prefix))
        if res1 != 0:
            print(f"Case {idx} ignored")
            continue

        res2 = 0
        if(f"{prefix}.in" in os.listdir(f"{PATH}")):
            res2 = os.system(MINIVM_COMMAND_V2.format(PATH, prefix))
        else:
            res2 = os.system(MINIVM_COMMAND.format(PATH, prefix))

        os.system(APPEND_COMMAND.format(PATH, prefix, str(int(res2//256))))

        if out_compare(prefix) is False:
            print(f"Case {prefix} failed!")
        else:
            correct_cnt += 1
            print(f"Case {prefix} passed!")

    except:
        continue

print(f"#Correct/#Total = {correct_cnt}/{len(file_list)}")

