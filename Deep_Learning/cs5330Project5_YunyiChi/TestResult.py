# Yunyi Chi
# CS 5330 Computer Vision Project 5

# This task file is for the later part of Task 1, test the model with MNIST test_loader and user handwriting input


import torch
import DeepLearningModel
import helper_function
import numpy as np
import sys

# use a model to predict the result for a test dataset, also print the results and plot a graph
def test_prediction(test_loader, model):
    num_predicted = 10
    data_index = 0
    model.eval()
    data_list = []
    label_list = []
    torch.set_printoptions(precision=2, sci_mode=True)
    for data, target in test_loader:
        if data_index < num_predicted:
            image_array = np.transpose(torch.squeeze(data, 1).numpy(), (1, 2, 0))
            data_list.append(image_array)
            with torch.no_grad():
                output = model(data)
                print(f'------------------Test Example {data_index+1}------------------------------------')
                print(f'Model output: {output}')
                print(f'Index of the maximum output value: {output.argmax().item()}')
                predicted_label = output.data.max(1, keepdim=True)[1].item()
                print(f'Correct label: {target[0]}')
                label_list.append(predicted_label)
                data_index += 1
        else:
            break
    return data_list, label_list




# main function
# load a pre-trained network, make a prediction for the test dataset
def main(argv):
    torch.manual_seed(42)
    torch.backends.cudnn.enabled = False
    model = DeepLearningModel.MyNetwork()
    model .load_state_dict(torch.load('trained_model_state.pth'))
    test_loader = helper_function.load_testset()
    data_list, label_list = test_prediction(test_loader, model)
    helper_function.visualize_result(data_list, label_list, 3, 3)
    url = '/Users/yunyichi/Desktop/cv/DeepLearning/handwrite_number'
    customed_test_loader = helper_function.load_custumed_set(url)
    customed_data_list, customed_label_list = test_prediction(customed_test_loader, model)
    helper_function.visualize_result(customed_data_list, customed_label_list, 3, 4)




if __name__ == "__main__":
    main(sys.argv)