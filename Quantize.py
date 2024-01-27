import torch

A=torch.nn.Linear(4,4)
S=A.state_dict()

def quantize(tensor):
    return 0