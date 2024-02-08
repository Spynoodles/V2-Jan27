import torch

A=torch.randn(4,4)

def quantize(tensor):
    Int8Arr=[]
    temp=[]
    for i in range(0,len(tensor)):
        list=tensor[i].tolist()
        minimum,maximum=min(list),max(list)
        for j in range(len(tensor[i])):
            temp.append(((tensor[i][j].item())-minimum)*(2**8-1)/(maximum-minimum)-128)

            # temp.append(round((float(tensor[i][j])-minimum)*(2**8-1)/(maximum-minimum),0)-128)
        Int8Arr.append(temp)
        temp=[]
    tensor=torch.tensor(Int8Arr,dtype=torch.int8)
    return(tensor)

print(A)
B=quantize(A)
print(B)