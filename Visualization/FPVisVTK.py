"""
Floorplan visualization using mayavi.

Author: Fang Qiao
Date: 8/23/2016

Note: hard coded to 3d.
"""

import numpy as np
from mayavi import mlab

_NUMERALS = '0123456789abcdefABCDEF'
_HEXDEC = {v: int(v, 16) for v in (x+y for x in _NUMERALS for y in _NUMERALS)}

c_palette = ['ff4c4d', 'ce4c7d', 'ae559e', 'df866d', 'ffb66d', 'ffe7cf', 'cecece', '6d6d6d', '4c4c8e', '4c4cef']
lc_palette = ['ff2727', 'b90046', '8b0b74', 'd1512e', 'ff972f', 'ffddba', 'b9b9b9', '2e2e2e', '00005d', '0000e8']


def int_rgb(triplet):
    return _HEXDEC[triplet[0:2]] / 255, _HEXDEC[triplet[2:4]] / 255, _HEXDEC[triplet[4:6]] / 255


def text_coords(l, m, n):
    return "[%d,%d,%d]" % (l, m, n)


def text_values(array, l, m, n):
    return str(array[l, m, n])


def make_surfaces(x, y, z, w, l, h, s):
    """ Create a set of surfaces for a block in 3 dimensions. """
    x2 = x + w - s
    y2 = y + l - s
    z2 = z + h - s

    x = x + s
    y = y + s
    z = z + s

    surfaces = {
        "top": np.asarray([[[x, x2], [x, x2]], [[y, y], [y2, y2]], [[z2, z2], [z2, z2]]]),
        "bottom": np.asarray([[[x, x2], [x, x2]], [[y, y], [y2, y2]], [[z, z], [z, z]]]),
        "back": np.asarray([[[x, x], [x, x]], [[y, y2], [y, y2]], [[z, z], [z2, z2]]]),
        "front": np.asarray([[[x2, x2], [x2, x2]], [[y, y2], [y, y2]], [[z, z], [z2, z2]]]),
        "left": np.asarray([[[x, x2], [x, x2]], [[y, y], [y, y]], [[z, z], [z2, z2]]]),
        "rg": np.asarray([[[x, x2], [x, x2]], [[y2, y2], [y2, y2]], [[z, z], [z2, z2]]])
    }

    return surfaces


class BlockPlotter(object):
    def __init__(
        self,
        blocks,
        color="lightgreen",
        lcolor="darkgreen",
        alpha=0.6,
        scale=(1, 1, 1),
        spacing=0.1
    ):
        self.defaults_ = {
            "color":    color,
            "lcolor":   lcolor,
            "alpha":    alpha,
            "scale":    scale,
            "spacing":  spacing
        }
        self.blocks_ = blocks
        self.colors = [color] * len(self.blocks_)
        self.lcolors = [lcolor] * len(self.blocks_)
        self.alphas = [alpha] * len(self.blocks_)
        self.scale = scale
        self.spacing = spacing

    def reset(self, blocks):
        self.blocks_ = blocks
        self.set_color(self.defaults_["color"])
        self.set_lcolor(self.defaults_["lcolor"])
        self.set_alpha(self.defaults_["alpha"])
        self.set_spacing(self.defaults_["spacing"])
        self.set_scale(self.defaults_["scale"])

    def set_color(self, color):
        self.colors = [color] * len(self.blocks_)
        return self.colors

    def set_colors(self, colors):
        self.colors = colors
        return self.colors

    def set_lcolor(self, lcolor):
        self.lcolors = [lcolor] * len(self.blocks_)
        return self.colors

    def set_lcolors(self, lcolors):
        self.lcolors = lcolors
        return self.lcolors

    def set_alpha(self, alpha):
        self.alphas = [alpha] * len(self.blocks_)
        return self.alphas

    def set_scale(self, scale):
        self.scale = scale
        return self.scale

    def set_spacing(self, spacing):
        self.spacing = spacing
        return self.spacing

    def render(self, blocks=None, text=None, azim=-15, elev=15):
        """
        Main routine for generating block plot using matplotlib.

        :param blocks:
        :param text:
        :param azim:
        :param elev:
        :return:
        """

        if not blocks:
            blocks = self.blocks_

        bn = len(blocks)

        if bn != len(self.blocks_):
            self.reset(blocks)

        mlab.figure(bgcolor=(1.0, 1.0, 1.0))
        """TODO: problem with mayavi axes in python3 vtk"""
        # fig = plt.figure(dpi=120)
        # ax = fig.add_subplot(111, projection='3d')

        for idx, block in enumerate(blocks):
            label = block[0]
            x = block[1]
            y = block[2]
            z = block[3]
            w = block[4]
            l = block[5]
            h = block[6]
            c_idx = block[7]
            surfaces = make_surfaces(x, y, z, w, l, h, self.spacing)
            c = int_rgb(self.colors[c_idx])
            lc = int_rgb(self.lcolors[c_idx])
            a = self.alphas[0]

            for side in surfaces:
                surface = surfaces[side]
                (xs, ys, zs) = (self.scale[0] * surface[0], self.scale[1] * surface[1], self.scale[2] * surface[2])
                mlab.mesh (xs, ys, zs,
                    opacity=a,
                    color=c )

        mlab.show()


if __name__ == '__main__':
    subject = [['a', 0, 0, 0, 1, 1, 1, 1], ['b', 1, 0, 0, 1, 3, 1, 2], ['c', 2, 0, 0, 1, 1, 1, 3],
               ['d', 0, 1, 0, 1, 1, 1, 4], ['e', 2, 1, 0, 1, 1, 1, 5], ['f', 0, 2, 0, 1, 1, 1, 6],
               ['g', 2, 2, 0, 1, 1, 1, 7]]

    plotter = BlockPlotter(subject, spacing=0.1, alpha=0.8)

    plotter.set_alpha(1.0)
    plotter.set_colors(c_palette)
    plotter.set_lcolors(lc_palette)
    plotter.render()
