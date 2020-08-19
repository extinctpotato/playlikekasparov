#!/usr/bin/python3

import sys, os

def find_start_end(file_path):
    with open(file_path, "r") as fh:
        lines = fh.readlines()

    file_name = os.path.basename(file_path)

    arr_end = "};\n"

    vert_line = "float {}Verts [] = {{\n".format(file_name.split(".")[0])
    norm_line = "float {}Normals [] = {{\n".format(file_name.split(".")[0])

    vert_start = lines.index(vert_line)+2
    norm_start = lines.index(norm_line)+2

    data = {"vert":[vert_start, vert_start], "norm":[norm_start, norm_start]}

    for line_numbers in data.values():
        for l in lines[line_numbers[0]:]:
            if l == arr_end:
                break
            else:
                line_numbers[1] += 1

    return data

def call_sed(file_path, lr):
    cmd = [
            "sed -i '{},{}s/$/1.0f,/' {}".format(lr['vert'][0],lr['vert'][1],file_path),
            "sed -i '{},{}s/$/0.0f,/' {}".format(lr['norm'][0],lr['norm'][1],file_path),
    ]

    for c in cmd:
        os.system(c)

def main():
    for f in sys.argv[1:]:
        fs = f.split(".")
        if len(fs) != 2 or fs[1] != "h":
            print("Rejecting {}".format(f))
            continue
        line_ranges = find_start_end(f)
        print(f, line_ranges)
        call_sed(f, line_ranges)

main()
