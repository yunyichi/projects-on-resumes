# Yunyi Chi
# CS 5330 Computer Vision Project 5

# This file includes all helper function of this project



from configparser import Interpolation
from random import shuffle
import torchvision.transforms as transforms
import torchvision
import torch
import matplotlib.pyplot as plt
from torchvision import datasets
import cv2
import numpy as np

# greek data set transform
class GreekTransform:
    def __init__(self):
        pass

    def __call__(self, x):
        x = torchvision.transforms.functional.rgb_to_grayscale( x )
        x = torchvision.transforms.functional.affine( x, 0, (0,0), 36/128, 0 )
        x = torchvision.transforms.functional.center_crop( x, (28, 28) )
        return torchvision.transforms.functional.invert( x )

# get train_loader and test_loader
def load_data(batch_size=64):
    transform = transforms.Compose([transforms.ToTensor(),
                                   transforms.Normalize((0.1307,), (0.3081,))])
    train_set = torchvision.datasets.MNIST(root='./data', train=True, download=True, transform=transform)
    test_set = torchvision.datasets.MNIST(root='./data', train=False, download=True, transform=transform)
    train_loader = torch.utils.data.DataLoader(train_set, batch_size=batch_size, shuffle=False)
    test_loader = torch.utils.data.DataLoader(test_set, batch_size=batch_size, shuffle=False)
    return train_loader, test_loader

# get test_loader
def load_testset():
    transform = transforms.Compose([transforms.ToTensor(),
                                   transforms.Normalize((0.1307,), (0.3081,))])
    test_set = torchvision.datasets.MNIST(root='./data', train=False, download=True, transform=transform)
    test_loader = torch.utils.data.DataLoader(test_set)                                   
    return test_loader

# get train_loader
def load_trainset():
    transform = transforms.Compose([transforms.ToTensor(),
                                   transforms.Normalize((0.1307,), (0.3081,))])
    train_set = torchvision.datasets.MNIST(root='./data', train=True, download=True, transform=transform)
    train_loader = torch.utils.data.DataLoader(train_set)                                   
    return train_loader

# get handwriting inputs as test_loader
def load_custumed_set(url):
    transform = transforms.Compose([
        transforms.Resize((28, 28)),
        transforms.Grayscale(),
        transforms.functional.invert,
        transforms.ToTensor(),
        transforms.Normalize((0.1307,), (0.3081,))
    ])
    test_loader = torch.utils.data.DataLoader(datasets.ImageFolder(url, transform))
    return test_loader

# get greek images as train_loader
def load_greek_trainset(url):
    greek_train = torch.utils.data.DataLoader(
        torchvision.datasets.ImageFolder( url,
                                          transform = torchvision.transforms.Compose( [torchvision.transforms.ToTensor(),
                                                                                       GreekTransform(),
                                                                                       torchvision.transforms.Normalize(
                                                                                           (0.1307,), (0.3081,) ) ] ) ),
        batch_size = 5,
        shuffle = True )
    return greek_train

# plot a graph which includes train loss and test loss
def plot_loss_graph(train_losses, num_trained, test_losses, num_tested):
    plt.plot(num_trained, train_losses, color='blue')
    plt.scatter(num_tested, test_losses, color='red')
    plt.xlabel('number of training examples seen')
    plt.ylabel('negative log likelihood loss')
    plt.legend(['Train Loss', 'Test Loss'], loc='upper right')
    plt.show()


# plot a graph which only includes train loss
def plot_train_loss(train_losses, num_trained):
    plt.plot(num_trained, train_losses, color='blue')
    plt.xlabel('number of training examples seen')
    plt.ylabel('negative log likelihood loss')
    plt.legend(['Train Loss', 'Test Loss'], loc='upper right')
    plt.show()


# visualze data of ground truth in a graph
def visualize_data(train_loader, row, col):
    data, targets = next(iter(train_loader))
    fig, axes = plt.subplots(row, col)
    fig.tight_layout()
    for i, ax in enumerate(axes.flat):
        ax.imshow(data[i][0], cmap='gray', interpolation='none')
        ax.set_title(f'Ground Truth: {targets[i]}')
        ax.set_xticks([])
        ax.set_yticks([])
    plt.show()


# visual predicted result in a graph
def visualize_result(data_list, label_list, row, col):
    num_results = row*col
    fig, axes = plt.subplots(row, col)
    fig.tight_layout()
    for i, ax in enumerate(axes.flat):
        if i < len(data_list):
            ax.imshow(data_list[i], cmap='gray', interpolation='none')
            ax.set_title(f'Prediction: {label_list[i]}')
            ax.set_xticks([])
            ax.set_yticks([])
        else:
            ax.axis('off')
    plt.show()


# get the filters in the first layer of a DNN
def get_filters(model):
    conv_layer = model.conv1
    num_filter = len(conv_layer.weight)
    filters = []
    with torch.no_grad():
        for filter_index in range(num_filter):
            filter = conv_layer.weight[filter_index, 0]
            filters.append(filter)
            print(f'This is filter {filter_index+1}')
            print(filter)
            print(filter.shape)
            print()
    return filters

# visualize the filters of DNN in a graph
def plot_filters(filters, row, col):
    fig, axes = plt.subplots(row, col)
    fig.tight_layout()
    with torch.no_grad():
        for i, ax in enumerate(axes.flat):
            if i < len(filters):
                ax.imshow(filters[i])
                ax.set_title(f'Filter {i+1}')
                ax.set_xticks([])
                ax.set_yticks([])
            else:
                ax.axis('off')
    plt.show()


# visualize the filters and processed images in a graph
def filter_applied_to_image(filters, image, row, col):
    filtered_image_list = []
    fig, axes = plt.subplots(row, col)
    fig.tight_layout()
    with torch.no_grad():
        for i in range(len(filters)):
            filtered_image = cv2.filter2D(np.array(image), ddepth=-1, kernel=np.array(filters[i]))
            filtered_image_list.append(filtered_image)
        for i, ax in enumerate(axes.flat):
            if i < 2*len(filters):
                if i%2 == 0:
                    ax.imshow(filters[i//2], cmap='gray', interpolation='none')
                    ax.set_xticks([])
                    ax.set_yticks([])
                else:
                    ax.imshow(filtered_image_list[i//2], cmap='gray', interpolation='none')
                    ax.set_xticks([])
                    ax.set_yticks([])
            else:
                ax.axis('off')
    plt.show()






