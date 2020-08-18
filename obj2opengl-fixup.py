#!/usr/bin/python3

import sys, os

def find_start_end():
    with open(sys.argv[1], "r") as fh:
        lines = fh.readlines()

    arr_end = "};\n"

    vert_line = "float {}Verts [] = {{\n".format(sys.argv[1].split(".")[0])
    norm_line = "float {}Normals [] = {{\n".format(sys.argv[1].split(".")[0])

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

def call_sed(lr):
    cmd = [
            "sed -i '{},{}s/$/1.0f,/' {}".format(lr['vert'][0],lr['vert'][1],sys.argv[1]),
            "sed -i '{},{}s/$/0.0f,/' {}".format(lr['norm'][0],lr['norm'][1],sys.argv[1]),
    ]

    for c in cmd:
        os.system(c)

def main():
    line_ranges = find_start_end()
    print(line_ranges)
    call_sed(line_ranges)

main()
