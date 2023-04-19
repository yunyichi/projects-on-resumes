# Yunyi Chi
# CS 5330 Computer Vision Project 5

# This file is for Task 2, Exam the pre-trained DNN model


import sys
import torch
import DeepLearningModel
import helper_function
import numpy as np
import cv2


# Exam a pre-trained DNN network, print its structure, get access to the first layer
def main(argv):
    torch.manual_seed(42)
    torch.backends.cudnn.enabled = False
    model = DeepLearningModel.MyNetwork()
    model .load_state_dict(torch.load('trained_model_state.pth'))
    print(model)
    filters = helper_function.get_filters(model)
    helper_function.plot_filters(filters, 3, 4)
    train_loader = helper_function.load_trainset()
    data, target = next(iter(train_loader))
    image = np.transpose(torch.squeeze(data, 1).numpy(), (1, 2, 0))
    helper_function.filter_applied_to_image(filters, image, 5, 4)


if __name__ == "__main__":
    main(sys.argv)
