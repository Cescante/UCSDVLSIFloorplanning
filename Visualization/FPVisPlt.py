import plotly as py
import plotly.graph_objs as go

c_palette = ['#ff4c4d', '#ce4c7d', '#ae559e', '#df866d', '#ffb66d', '#ffe7cf', '#cecece', '#6d6d6d', '#4c4c8e',
             '#4c4cef']
lc_palette = ['#ff2727', '#b90046', '#8b0b74', '#d1512e', '#ff972f', '#ffddba', '#b9b9b9', '#2e2e2e', '#00005d',
              '#0000e8']


def make_block(x, y, z, w, l, h, s):
    """ compute vertices for a block in 3 dimensions. """
    # x = [0, 0, 1, 1, 0, 0, 1, 1],
    # y = [0, 1, 1, 0, 0, 1, 1, 0],
    # z = [0, 0, 0, 0, 1, 1, 1, 1],

    x2 = x + w - s
    y2 = y + l - s
    z2 = z + h - s

    x = x + s
    y = y + s
    z = z + s

    xs = [x, x,  x2, x2, x,  x,  x2, x2]
    ys = [y, y2, y2, y,  y,  y2, y2, y]
    zs = [z, z,  z,  z,  z2, z2, z2, z2]

    return [xs, ys, zs]


def mesh3d_datum(xs, ys, zs, clr, alpha, label):
    datum = go.Mesh3d(
        x=xs,
        y=ys,
        z=zs,
        color=clr,
        i=[7, 0, 0, 0, 4, 4, 6, 6, 4, 0, 3, 2],
        j=[3, 4, 1, 2, 5, 6, 5, 2, 0, 1, 6, 3],
        k=[0, 7, 2, 3, 6, 7, 1, 1, 5, 5, 7, 6],
        name=label,
        opacity=1.0
    )
    return datum


class BlockPlotter(object):
    def __init__(
        self,
        blocks,
        color="lightgreen",
        lcolor="darkgreen",
        alpha="0.6",
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

    def render(self, blocks=None, text=None):
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

        mesh_data = []

        for idx, block in enumerate(blocks):
            label = block[0]
            x = block[1]
            y = block[2]
            z = block[3]
            w = block[4]
            l = block[5]
            h = block[6]
            c_idx = block[7]
            c = self.colors[c_idx]
            # lc = self.lcolors[c_idx] # TODO: borders
            a = self.alphas[0]

            [xs, ys, zs] = make_block(x, y, z, w, l, h, self.spacing)
            mesh_data.append(mesh3d_datum(xs, ys, zs, c, a, label))

        return go.Data(mesh_data)

if __name__ == '__main__':
    subject = [['a', 0, 0, 0, 1, 1, 1, 1], ['b', 1, 0, 0, 1, 3, 1, 2], ['c', 2, 0, 0, 1, 1, 1, 3],
               ['d', 0, 1, 0, 1, 1, 1, 4], ['e', 2, 1, 0, 1, 1, 1, 5], ['f', 0, 2, 0, 1, 1, 1, 6],
               ['g', 2, 2, 0, 1, 1, 1, 7]]

    plotter = BlockPlotter(subject, spacing=0.1, alpha=0.8)

    plotter.set_alpha(1.0)
    plotter.set_colors(c_palette)
    plotter.set_lcolors(lc_palette)

    data = plotter.render()

    layout = go.Layout(
        xaxis=go.XAxis(
            title='x'
        ),
        yaxis=go.YAxis(
            title='y'
        )
    )
    fig = go.Figure(data=data, layout=layout)
    py.offline.plot(fig, filename='Floorplan.html')
