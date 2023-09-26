"""
Yunyi Chi CS5330
This file represents the start program of Symmetry Detector
run 'python starter test_mode' for test
run 'python starter video_mode' for video
run 'python starter analyse_mode' for analyse
"""

import sys
import Symmetry_Detector
import cv2
import numpy as np


NUM_TEST = 72

# This is the main program of symmetry detetor
# there are 3 modes
# test_mode: for test results in the testset
# video_mode: open the real-time camera, to detect symmetry in the camera
# analyse_mode: print and draw more details
def main(argv):
    # the url of test set
    base_url = '/Users/yunyichi/Desktop/cs5330/final_proj/testset/'
    testset_url = [base_url + 'data' + str(i) + '.jpg' for i in range(1, NUM_TEST+1)]
    index = 1
    # test_mode
    if argv[1] == 'test_mode':
        for url in testset_url:
            b, g, r = cv2.split(cv2.imread(url))
            original_image = cv2.merge([r, g, b])
            flip_image = np.fliplr(original_image)
            sd = Symmetry_Detector.Symmetry_Detector(original_image, flip_image, argv[1], str(index))
            sd.get_potential_symmetry()
            index += 1
    # video_mode
    elif argv[1] == 'video_mode':
        cap = cv2.VideoCapture(0)
        while True:
            ret, frame = cap.read()
            b, g, r = cv2.split(frame)
            original_frame = cv2.merge([r, g, b])
            flip_frame = np.fliplr(original_frame)
            sd = Symmetry_Detector.Symmetry_Detector(original_frame, flip_frame, argv[1])
            new_frame = sd.get_potential_symmetry()
            cv2.imshow('frame', new_frame)
            if cv2.waitKey(1) & 0xFF == ord('q'):
                break
        cap.release()
        cv2.destroyAllWindows()
    # analyse_mode
    elif argv[1] == 'analyse_mode':
        url = testset_url[19]
        b, g, r = cv2.split(cv2.imread(url))
        original_image = cv2.merge([r, g, b])
        flip_image = np.fliplr(original_image)
        sd = Symmetry_Detector.Symmetry_Detector(original_image, flip_image, argv[1])
        sd.get_potential_symmetry()

 
if __name__ == "__main__":
    main(sys.argv)