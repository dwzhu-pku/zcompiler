import os
from types import coroutine

COMP_COMMAND = "./build/compiler -S -e ./part1_opentest/functional_test/{}.sy -o ./output/{}.ir"
MINIVM_COMMAND = "../MiniVM/build/minivm ./output/{}.ir > ./part1_opentest/functional_test_myout/{}.out"
MINIVM_COMMAND_V2 = "../MiniVM/build/minivm ./output/{}.ir < ./part1_opentest/functional_test/{}.in > ./part1_opentest/functional_test_myout/{}.out"
APPEND_COMMAND = "echo {} >> ./part1_opentest/functional_test_myout/{}.out"

def out_compare(prefix):
    file1 = f"./part1_opentest/functional_test_myout/{prefix}.out"
    file2 = f"./part1_opentest/functional_test/{prefix}.out"

    with open(file1, "r", encoding="utf-8") as file1, open(file2, 'r', encoding="utf-8") as file2:
        line_list1 = file1.readlines()
        line_list2 = file2.readlines()
        if (len(line_list1) != len(line_list2)):
            return False
        for i in range(len(line_list1)):
            if line_list1[i] != line_list2[i]:
                return False
    return True


file_list = [ file for file in os.listdir("./part1_opentest/functional_test") if  file.endswith("sy")  ]
correct_cnt = 0

for idx, file in enumerate(file_list):
    prefix = file[:-3]
    try:
        print(f"Case {idx}")
        res1 = os.system(COMP_COMMAND.format(prefix, prefix))
        if res1 != 0:
            print(f"Case {idx} ignored")
            continue

        res2 = 0
        if(f"{prefix}.in" in os.listdir("./part1_opentest/functional_test")):
            res2 = os.system(MINIVM_COMMAND_V2.format(prefix, prefix, prefix))
        else:
            res2 = os.system(MINIVM_COMMAND.format(prefix, prefix))

        os.system(APPEND_COMMAND.format(str(int(res2//256)), prefix))

        if out_compare(prefix) is False:
            print(f"Case {prefix} failed!")
        else:
            correct_cnt += 1
            print(f"Case {prefix} passed!")

    except:
        continue

print(f"#Correct/#Total = {correct_cnt}/{len(file_list)}")

