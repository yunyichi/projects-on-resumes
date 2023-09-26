"""
Yunyi Chi CS5330
This file represents a symmetry detector
"""


import numpy as np
import cv2
import sys
import matplotlib.pyplot as plt
import Symmetry_Drawer


# This class represents a Symmetry detector
# it uses the SIFT features to get matches pairs
# then draw a hexbin diagram to find the dominate symmetry
class Symmetry_Detector:
    # constructor of Symmetry_Detector class
    # should specify the original image, flip image, mode and title
    def __init__(self, original_image, flip_image, mode, title='image'):
        self.sift = cv2.xfeatures2d.SIFT_create()
        self.bfMatcher = bf = cv2.BFMatcher()
        self.original_image = original_image
        self.flip_image = flip_image
        self.mode = mode
        self.title = title
    # a method to get the symmetry for the original image in the Symmetry_Detector class
    def get_potential_symmetry(self):
        # Step 1: extract sift features from both images
        original_feature_points, original_descriptors = self.extract_sift_features(self.original_image)
        flip_feature_points, flip_descriptors = self.extract_sift_features(self.flip_image)
        # if the mode is analyse_mode, try to draw feature points in both images
        if self.mode == 'analyse_mode':
            Symmetry_Drawer.draw_feature_points(self.original_image, original_feature_points)
            Symmetry_Drawer.draw_feature_points(self.flip_image, flip_feature_points)
            
        # defines potential matched pairs
        matched_features = self.find_matches_by_knn(original_descriptors, flip_descriptors)
        # if the mode is analyse_mode, try to draw feature matches in both images
        if self.mode == 'analyse_mode':
            Symmetry_Drawer.draw_potential_matches(self.original_image, self.flip_image, original_feature_points, flip_feature_points, matched_features)
        symmetries_r, symmetries_theta = self.find_symmetries(matched_features, original_feature_points, flip_feature_points)
        # if self.mode == 'analyse_mode':
        #     Symmetry_Drawer.draw_symmetries(self.original_image, symmetries_r, symmetries_theta)
        max_r, max_theta = self.get_max_symmetry_by_hexbin(symmetries_r, symmetries_theta)
        modified_image = Symmetry_Drawer.draw_mirror_symmetry(self.original_image, max_r, max_theta, self.mode, self.title)
        return modified_image


    # extract SIFT features from an image
    def extract_sift_features(self, image):
        return self.sift.detectAndCompute(image, None)

    # use knn algorithm to match the pairs between original and mirror image
    # sort the return list based on distance
    def find_matches_by_knn(self, original_descriptors, flip_descriptors):
        potential_matches = self.bfMatcher.knnMatch(original_descriptors, flip_descriptors, 2)
        matched_features = []
        for i in potential_matches:
            matched_features.append(i[0])
        matched_features.sort(key=lambda x:x.distance)
        return matched_features
    
    # find all potential symmetries for matched pairs, represented by polar coordinates
    def find_symmetries(self, matched_features, original_feature_points, flip_feature_points):
        symmetry_polor_coordinates_r, symmetry_polor_coordinates_theta = [], []
        for m in matched_features:
            original_point = original_feature_points[m.queryIdx]
            flip_point = flip_feature_points[m.trainIdx]
            flip_point.angle = np.pi - np.deg2rad(flip_point.angle)
            flip_point.pt = (self.flip_image.shape[1] - flip_point.pt[0], flip_point.pt[1])
            x_difference = original_point.pt[0] - flip_point.pt[0]
            y_difference = original_point.pt[1] - flip_point.pt[1]
            mid_x = (original_point.pt[0] + flip_point.pt[0])/2
            mid_y = (original_point.pt[1] + flip_point.pt[1])/2
            if x_difference == 0:
                theta = np.pi/2
            else:
                theta = np.arctan(y_difference/x_difference)
                if theta < 0:
                    theta += np.pi
            r = mid_x*np.cos(theta) + mid_y*np.sin(theta)
            symmetry_polor_coordinates_r.append(r)
            symmetry_polor_coordinates_theta.append(theta)
        return symmetry_polor_coordinates_r, symmetry_polor_coordinates_theta
    
    # draw the hexbin diagram by the symmetries polar coordinates list.
    # only return the coordinate of bin which has the largest vote
    def get_max_symmetry_by_hexbin(self, symmetries_r, symmetries_theta):
        hexbin = plt.hexbin(symmetries_r, symmetries_theta, bins=200, cmap=plt.cm.Spectral_r)
        if self.mode == 'analyse_mode':
            plt.colorbar()
            plt.title("Hexbin")
            plt.show()
        values = hexbin.get_array()
        coors = hexbin.get_offsets()
        max_r, max_theta, max_value = 0, 0, 0
        for c in range(coors.shape[0]):
            r, theta = coors[c][0], coors[c][1]
            if values[c] and values[c] > max_value and theta != 0 and theta != np.pi:
                max_value = values[c]
                max_r = r
                max_theta = theta
        return max_r, max_theta                
                

    