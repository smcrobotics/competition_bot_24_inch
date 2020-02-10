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
        command = " ".join(command_list).lower()
        button = line[1].split(";", 1)[0]
        bindings[button] = command
        # print(command)
        # print(button)
        # bindings.append(line)

source.close()

with open('./docs/24in_key_bindings.md', 'a') as output_file:
    output_file.write("# Key bindings for SMC 2019-2020 24in robot\n")
    output_file.write("![Controller](https://raw.githubusercontent.com/smcrobotics/competition_bot_15_inch/master/docs/controller.png)\n")
    output_file.write("\n## Button mappings\n")
    output_file.write("### Bumpers (1-4), Joysticks (5-6), Arrows (7-10), Letters (11-14)\n")

    for button in bumpers:
        output_file.write("1. {}: ".format(button))
        if button in bindings:
            output_file.write("{}".format(bindings[button]))
        else:
            output_file.write("N/A")
        output_file.write("\n")

    output_file.write("1. Left Joystick: Left side drive motors\n")
    output_file.write("1. Right Joystick: Right side drive motors\n")

    for button in arrows:
        output_file.write("1. {}: ".format(button))
        if button in bindings:
            output_file.write("{}".format(bindings[button]))
        else:
            output_file.write("N/A")
        output_file.write("\n")
    
    for button in letters:
        output_file.write("1. {}: ".format(button))
        if button in bindings:
            output_file.write("{}".format(bindings[button]))
        else:
            output_file.write("N/A")
        output_file.write("\n")