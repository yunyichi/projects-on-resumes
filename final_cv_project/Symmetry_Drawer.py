"""
Yunyi Chi CS5330
This file represents some functions which draw on original image
"""

import numpy as np
import cv2
import sys
import matplotlib.pyplot as plt


# draw feature points on the original image with circle
def draw_feature_points(image, points):
    img_with_feature_points = cv2.drawKeypoints(image, points, None, color=(0, 255, 0), flags=cv2.DRAW_MATCHES_FLAGS_DRAW_RICH_KEYPOINTS)
    plt.imshow(img_with_feature_points)
    plt.axis('off')
    plt.show()

# draw the first 20 matches between original and mirror images by straight line
def draw_potential_matches(original_image, flip_image, original_feature_points, flip_feature_points, matched_features):
    image = cv2.drawMatches(original_image, original_feature_points, flip_image, flip_feature_points, matched_features[:20], None, flags=2)
    plt.imshow(image)
    plt.axis('off')
    plt.show()

# draw all potential symmetries on the original image
def draw_symmetries(image, symmetries_r, symmetries_theta):
    for r, theta in zip(symmetries_r, symmetries_theta):
        for x in range(len(image)):
            try:
                y = int((r - x*np.sin(theta))/np.cos(theta))
                image[x][y] = 255
                image[x][y+1] = 255
                image[x][y-1] = 255
            except IndexError:
                continue
    plt.imshow(image)
    plt.show()


# draw the dominate symmetry line on the original image
def draw_mirror_symmetry(image, r, theta, mode, title):
    for x in range(len(image)):
        try:
            y = int((r - x*np.sin(theta))/np.cos(theta))
            image[x][y] = 255
            image[x][y+1] = 255
            image[x][y-1] = 255
        except IndexError:
            continue
    if mode != 'video_mode':
        plt.imshow(image)
        plt.title(title)
        plt.axis('off')
        plt.show()
    return image





