#!/usr/bin/python
from ast import literal_eval
import sys
import csv
import FPVisVTK as fvvtk


def eval_help(str):
    try:
        return literal_eval(str)
    except ValueError:
        return str

def parse_data(fname):
    for line in open(fname):
        yield eval(line)


def parse_csv(fname, delim=','):
    with open(fname, 'r') as csvfile:
        csvreader = csv.reader(csvfile, delimiter=delim)
        for line in csvreader:
            if line[0] == '#':
                continue
            yield [eval_help(x) for x in line]

if __name__ == '__main__':
    filename = sys.argv[1]
    # filename = 'proofblocks.txt'

    plotter = fvvtk.BlockPlotter(list(parse_csv(filename, delim=' ')), spacing=0.05, alpha=0.8)

    plotter.set_alpha(1.0)
    plotter.set_colors(fvvtk.c_palette)
    plotter.set_lcolors(fvvtk.lc_palette)

    plotter.render()
    plotter.plot_color_legend()
