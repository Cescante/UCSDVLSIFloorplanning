#!/usr/bin/python
from ast import literal_eval
import sys
import csv
import FPVisVTK as fvvtk


def parse_data(fname):
    for line in open(fname):
        yield eval(line)


def parse_csv(fname, delim=','):
    with open(fname, 'r') as csvfile:
        csvreader = csv.reader(csvfile, delimiter=delim)
        for line in csvreader:
            yield [literal_eval(x) for x in line]

if __name__ == '__main__':
    filename = sys.argv[1]

    plotter = fvvtk.BlockPlotter(list(parse_csv(filename, delim=' ')), spacing=0.1, alpha=0.8)

    plotter.set_alpha(1.0)
    plotter.set_colors(fvvtk.c_palette)
    plotter.set_lcolors(fvvtk.lc_palette)

    plotter.render()
