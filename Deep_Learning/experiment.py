# Yunyi Chi
# CS 5330 Computer Vision Project 5

# This file is for task 4, design an experiment to evaluate the effect of all dimensions

import torch
import helper_function
import DeepLearningModel
import torch.optim as optim


# build and train a DNN with specified parameters
def experiment(num_epochs, batch_size, dropout_rate, filter_size):
    device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
    model = DeepLearningModel.MyNetwork(filter_size, dropout_rate).to(device)
    optimizer = optim.SGD(model.parameters(), lr = 0.01, momentum=0.5)
    train_loader, test_loader = helper_function.load_data(batch_size)
    train_losses = []
    num_trained = []
    test_losses = []
    num_tested = []
    DeepLearningModel.test(model, device, test_loader, test_losses, 0, num_tested, train_loader)
    for epoch in range(1, num_epochs+1):
        DeepLearningModel.train(model, device, train_loader, optimizer, epoch, train_losses, num_trained)
        DeepLearningModel.test(model, device, test_loader, test_losses, epoch, num_tested, train_loader)



# Design an experiment to evaluate the effect of different dimensions in building and training a Network
def main():
    torch.manual_seed(42)
    torch.backends.cudnn.enabled = False
    print('We will all do 96 experiments')
    index_of_experiment = 0
    for num_epochs in [3, 5, 8, 11]:
        for batch_size in [32, 64, 128, 256]:
            for dropout_rate in [0.3, 0.4, 0.5]:
                for filter_size in [5, 7]:
                    index_of_experiment += 1
                    print('-----------------------------------')
                    print("This is the ", index_of_experiment, " experiment:")
                    print("set number of epochs: ", num_epochs)
                    print("set batch size: ", batch_size)
                    print("set dropout rate: ", dropout_rate)
                    print("set filter size: ", filter_size)
                    print()
                    experiment(num_epochs, batch_size, dropout_rate, filter_size)






if __name__ == "__main__":
    main()