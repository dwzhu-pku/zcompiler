import os
from types import coroutine

PATH = "./all_opentest/function_test2021"
COMP_COMMAND = "./build/compiler -S {0}/{1}.sy -o {0}/{1}.S"
RISCV_COMMAND1 = "riscv32-unknown-linux-gnu-gcc {0}/{1}.S -o output.o -L/root -lsysy -static"
RISCV_COMMAND2_V1 = "qemu-riscv32-static output.o > {0}/{1}.myout"
RISCV_COMMAND2_V2 = "qemu-riscv32-static output.o < {0}/{1}.in > {0}/{1}.myout"
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


file_list = [ file for file in os.listdir(f"{PATH}") if  file.endswith("sy")  ]
correct_cnt = 0

for idx, file in enumerate(file_list):
    prefix = file[:-3]

    if prefix != "103_long_func":
        continue
    try:
        res1 = os.system(COMP_COMMAND.format(PATH, prefix))
        if res1 != 0:
            print(f"Case {prefix} ignored")
            continue
        tmp = os.system(RISCV_COMMAND1.format(PATH, prefix))
        if tmp != 0:
            print(f"Case {prefix} ignored")
            continue
        
        res2 = 0
        if(f"{prefix}.in" in os.listdir(f"{PATH}")):
            res2 = os.system(RISCV_COMMAND2_V2.format(PATH, prefix))
        else:
            res2 = os.system(RISCV_COMMAND2_V1.format(PATH, prefix))

        os.system(APPEND_COMMAND.format(PATH, prefix, str(int(res2//256))))

        if out_compare(prefix) is False:
            print(f"Case {prefix} failed!")
        else:
            correct_cnt += 1
            print(f"Case {prefix} passed!")

    except:
        continue

print(f"#Correct/#Total = {correct_cnt}/{len(file_list)}")

