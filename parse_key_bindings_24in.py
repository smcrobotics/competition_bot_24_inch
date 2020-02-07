import os

os.system("rm -rf ./24in_key_bindings.md")
os.system("touch ./24in_key_bindings.md")
source = open("./include/smc/util/constants.h")


arrows = ["up", "down", "left", "right"]
bumpers = ["L1", "L2", "R1", "R2"]
letters = ["X", "B", "Y", "A"]

bindings = {}

for line in source.readlines():
    if "ControllerDigital" in line:
        line = line.strip().replace("const auto ", "").split(" = okapi::ControllerDigital::", 1)
        command = line[0]
        button = line[1].split(";", 1)[0]
        bindings[button] = command
        # print(command)
        # print(button)
        # bindings.append(line)

source.close()

with open('./24in_key_bindings.md', 'a') as output_file:
    output_file.write("# Key bindings for SMC 2019-2020 24in robot\n")
    output_file.write("## Buttons\n")
    output_file.write("### Bumpers\n")
    for button in bumpers:
        output_file.write("- {}: ".format(button))
        if button in bindings:
            output_file.write("{}".format(bindings[button]))
        else:
            output_file.write("N/A")
        output_file.write("\n")
    output_file.write("### Arrows\n")
    for button in arrows:
        output_file.write("- {}: ".format(button))
        if button in bindings:
            output_file.write("{}".format(bindings[button]))
        else:
            output_file.write("N/A")
        output_file.write("\n")
    output_file.write("### Letters\n")
    for button in letters:
        output_file.write("- {}: ".format(button))
        if button in bindings:
            output_file.write("{}".format(bindings[button]))
        else:
            output_file.write("N/A")
        output_file.write("\n")
