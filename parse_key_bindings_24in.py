import os

os.system("rm -rf ./docs/24in_key_bindings.md")
os.system("touch ./docs/24in_key_bindings.md")
source = open("./include/smc/util/constants.h")


arrows = ["down", "left", "up", "right"]
bumpers = ["R1", "L1", "R2", "L2"]
letters = ["Y", "X", "A", "B"]


bindings = {}

for line in source.readlines():
    if "ControllerDigital" in line:
        line = line.strip().replace("const auto ", "").split(" = okapi::ControllerDigital::", 1)
        command = line[0]
        command_list = command.split("_")
        command = " ".join(command_list)
        button = line[1].split(";", 1)[0]
        bindings[button] = command
        # print(command)
        # print(button)
        # bindings.append(line)

source.close()

with open('./docs/24in_key_bindings.md', 'a') as output_file:
    output_file.write("# Key bindings for SMC 2019-2020 24in robot\n")
    output_file.write("![Controller](https://raw.githubusercontent.com/smcrobotics/competition_bot_15_inch/master/docs/controller.JPG)\n")
    output_file.write("\nDirection Arrows | Letters          | Bumpers    |\n")
    output_file.write("---------------- | ---------------- | ---------- |\n")
    for i in range(4):
        j = i + 1
        arrow = bindings[arrows[i]] if arrows[i] in bindings else "N/A"
        output_file.write("{}. {} | ".format(str(j), arrow))
        bumper = bindings[bumpers[i]] if bumpers[i] in bindings else "N/A"
        output_file.write("{}. {} | ".format(str(j+4), bumper))
        letter = bindings[letters[i]] if letters[i] in bindings else "N/A"
        output_file.write("{}. {} | ".format(str(j+8), letter))
        output_file.write("\n")
