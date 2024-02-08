import matplotlib.pyplot as plot
import seaborn as sns
import torch

def KernelPlot():
    return 0

# A=(A.numpy().flatten().tolist())
def f(x):
    if x==0:
        return 1000000000000000
    return (x/x)

# plot.plot([i for i in range(-9,10)],[f(i) for i in range(-9,10)])
# plot.show()
KernelPlot()
sns.kdeplot(torch.rand(130,1).flatten(),bw_adjust=3,fill=True)
plot.show(sns)
 