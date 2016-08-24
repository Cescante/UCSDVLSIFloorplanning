import matplotlib.pyplot as plt
import numpy as np
import ndap

subject = np.ones((5,5,5))
plotter = ndap.NDArrayPlotter(subject)
(fig, ax) = plotter.render()
plt.show()
