# Yunyi Chi
# CS 5330 Computer Vision Project 5

# This file is for extension, load a pre-trained ResNet model and exam it


from operator import mod
import torch
import numpy as np
import sys
import helper_function
import torchvision.models as models

# Exam a pre-trained ResNet network, print its structure, get access to the first layer
def main(args):
    torch.manual_seed(42)
    torch.backends.cudnn.enabled = False
    model = models.resnet18(pretrained=True)
    print(f'This is the model structure: {model}')
    filters = helper_function.get_filters(model)
    helper_function.plot_filters(filters, 3, 4)
    train_loader = helper_function.load_trainset()
    data, target = next(iter(train_loader))
    image = np.transpose(torch.squeeze(data, 1).numpy(), (1, 2, 0))
    helper_function.filter_applied_to_image(filters, image, 5, 4)


if __name__ == "__main__":
    main(sys.argv)
