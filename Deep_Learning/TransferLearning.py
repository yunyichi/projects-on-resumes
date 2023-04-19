# Yunyi Chi
# CS 5330 Computer Vision Project 5

# This task is for task 3, use transfer learning to make it can recognize the greek letters


import torchvision
import torch
import DeepLearningModel
import sys
import helper_function
import torch.nn as nn
import torch.optim as optim
import TestResult


# main function
# load pretrained model, freeze the weights and replace the last layer
# train the modified model and test for the greek letters
def main(argv):
    torch.manual_seed(42)
    torch.backends.cudnn.enabled = False
    greek_number_url = '/Users/yunyichi/Desktop/cv/DeepLearning/greek_numbers'
    device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
    model = DeepLearningModel.MyNetwork().to(device)
    model.load_state_dict(torch.load('trained_model_state.pth'))
    for param in model.parameters():
        param.requires_grad = False
    train_loader = helper_function.load_greek_trainset(greek_number_url)
    test_loader = helper_function.load_greek_trainset(greek_number_url)
    model.fc2 = nn.Linear(50, 3)
    train_losses = []
    num_trained = []
    test_losses = []
    num_tested = []
    num_epochs = 6
    optimizer = optim.SGD(model.parameters(), lr = 0.01, momentum=0.5)
    DeepLearningModel.test(model, device, test_loader, test_losses, 0, num_tested, train_loader)
    for epoch in range(1, num_epochs+1):
        DeepLearningModel.train(model, device, train_loader, optimizer, epoch, train_losses, num_trained)
        DeepLearningModel.test(model, device, test_loader, test_losses, epoch, num_tested, train_loader)
    helper_function.plot_train_loss(train_losses, num_trained)
    print(model)
    handwriting_greek_number_url = '/Users/yunyichi/Desktop/cv/DeepLearning/handwriting_greek'
    handwriting_test_loader = helper_function.load_greek_trainset(handwriting_greek_number_url)
    DeepLearningModel.test(model, device, handwriting_test_loader, [], 0, [], train_loader)



if __name__ == "__main__":
    main(sys.argv)