'''
Created on 23/04/2013

@author: Pela
'''
import cv2
import sys
import numpy as np

class MarkerAreaInfo(object):
    def __init__(self):
        self.corner = []
        self.min_x = 1000000
        self.min_y = 1000000
        self.max_x = -1000000
        self.max_y = -1000000

    def calc_size(self):
        for i in range(4):
            self.min_x = min(self.min_x, self.corner[i].x);
            self.max_x = max(self.max_x, self.corner[i].x);
            self.min_y = min(self.min_y, self.corner[i].y);
            self.max_y = max(self.max_y, self.corner[i].y);
        }
    } 
class MarkerImg(object):
    def __init__(self, file_name):
        self.matching = 0.0
        self.image = cv2.imread(file_name)
        self.img_gray = cv2.cv.CreateImage(cv2.cv.GetSize(self.image), cv2.cv.IPL_DEPTH_8U, 1) 
        cv2.cvtColor(self.image, cv2.COLOR_BGR2GRAY, self.img_gray)
        cv2.threshold(self.img_gray, 128, 255, cv2.THRESH_BINARY_INV)
        self.contours, hierarchy = cv2.findContours(self.img_gray, cv2.RETR_LIST, cv2.CHAIN_APPROX_SIMPLE)
        cv2.drawContours(self.image, self.contours, -1, (0, 255, 0), 2)

img = cv2.imread('../img/markers.jpg')
img_gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
cv2.cv.Smooth(img_gray, img_gray, cv2.cv.CV_GAUSSIAN, 3, 3)
img_binary = cv2.cv.CreateImage(cv2.cv.GetSize(img_gray), cv2.cv.IPL_DEPTH_8U, 1)
cv2.adaptiveThreshold(img_binary, 255, cv2.ADAPTIVE_THRESH_MEAN_C, cv2.THRESH_BINARY_INV, 71, 15)
contours, hierarchy = cv2.findContours(img_binary, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
#approx_countours = cv2.approxPolyDP(contours, epsilon, closed)
