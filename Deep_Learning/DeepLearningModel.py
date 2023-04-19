# Yunyi Chi
# CS 5330 Computer Vision Project 5

# This file is for Task 1, build and train a DNN



import torch.nn as nn
import torch.nn.functional as F
import torch
import sys
import torch.optim as optim
import helper_function

# The base network for this project
# includes the following layers:
# A convolution layer with 10 5x5 filters
# A max pooling layer with a 2x2 window and a ReLU function applied.
# A convolution layer with 20 5x5 filters
# A dropout layer with a 0.5 dropout rate (50%)
# A max pooling layer with a 2x2 window and a ReLU function applied
# A flattening operation followed by a fully connected Linear layer with 50 nodes and a ReLU function on the output
# A final fully connected Linear layer with 10 nodes and the log_softmax function applied to the output.
class MyNetwork(nn.Module):
    def __init__(self, size=5, drop_rate=0.5):
        super(MyNetwork, self).__init__()
        self.conv1 = nn.Conv2d(1, 10, kernel_size=size)
        self.conv2 = nn.Conv2d(10, 20, kernel_size=size)
        self.conv2_drop = nn.Dropout(drop_rate)
        self.fc1 = nn.Linear(320, 50)
        self.fc2 = nn.Linear(50, 10)

    # forward
    def forward(self, x):
        x = F.relu(F.max_pool2d(self.conv1(x), 2))
        x = F.relu(F.max_pool2d(self.conv2_drop(self.conv2(x)), 2))
        x = x.view(-1, 320)
        x = F.relu(self.fc1(x))
        x = self.fc2(x)
        return F.log_softmax(x, dim=1)

# The modified network for transfer learning
# includes the following layers:
# A convolution layer with 10 5x5 filters
# A max pooling layer with a 2x2 window and a ReLU function applied.
# A convolution layer with 20 5x5 filters
# A dropout layer with a 0.5 dropout rate (50%)
# A max pooling layer with a 2x2 window and a ReLU function applied
# A flattening operation followed by a fully connected Linear layer with 50 nodes and a ReLU function on the output
# A final fully connected Linear layer with 3 nodes and the log_softmax function applied to the output.
class TranferLearning_Network(MyNetwork):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
    
    def forward(self, x):
        x = F.relu(F.max_pool2d(self.conv1(x), 2))
        x = F.relu(F.max_pool2d(self.conv2_drop(self.conv(x)), 2))
        x = x.view(-1, 320)
        x = F.relu(self.fc1(x))
        return x

# train the network with train_loader
def train(model, device, train_loader, optimizer, epoch, train_losses, train_counter):
    model.train()
    for batch_index, (data, target) in enumerate(train_loader):
        data, traget = data.to(device), target.to(device)
        optimizer.zero_grad()
        output = model(data)
        loss = F.nll_loss(output, target)
        loss.backward()
        optimizer.step()
        if batch_index % 10 == 0:
            train_losses.append(loss.item())
            train_counter.append((batch_index * 64) + ((epoch - 1) * len(train_loader.dataset)))
            #  I don't save the partly trained model, I don't know if it effects


# test the network with test_loader
def test(model, device, test_loader, test_losses, epoch, test_counter, train_loader):
    model.eval()
    test_loss = 0
    correct = 0
    with torch.no_grad():
        for data, target in test_loader:
            data, target = data.to(device), target.to(device)
            output = model(data)
            test_loss += F.nll_loss(output, target, reduction='sum').item()
            pred = output.argmax(dim=1, keepdim=True)
            correct += pred.eq(target.view_as(pred)).sum().item()
    test_loss = test_loss / len(test_loader.dataset)    
    test_losses.append(test_loss)
    test_counter.append(epoch * len(train_loader.dataset))
    print(f'Test Result for {epoch} training process:\n'
            f'The test loss is {round(test_loss, 4)}\n'
            f'The Accuracy is {correct}/{len(test_loader.dataset)} = {"{:.2%}".format(round(correct/len(test_loader.dataset), 4))}')
    print()

# main function
# build and train a DNN
def main(argv):
    torch.manual_seed(42)
    torch.backends.cudnn.enabled = False
    device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
    model = MyNetwork().to(device)
    optimizer = optim.SGD(model.parameters(), lr = 0.01, momentum=0.5)
    train_loader, test_loader = helper_function.load_data()
    helper_function.visualize_data(train_loader, 2, 3)

    train_losses = []
    num_trained = []
    test_losses = []
    num_tested = []
    max_epochs = 5

    test(model, device, test_loader, test_losses, 0, num_tested, train_loader)
    for epoch in range(1, max_epochs+1):
        train(model, device, train_loader, optimizer, epoch, train_losses, num_trained)
        test(model, device, test_loader, test_losses, epoch, num_tested, train_loader)
    
    helper_function.plot_loss_graph(train_losses, num_trained, test_losses, num_tested)
    torch.save(model, 'trained_model.pth')
    torch.save(model.state_dict(), 'trained_model_state.pth')
    



if __name__ == "__main__":
    main(sys.argv)








