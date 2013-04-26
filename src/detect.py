'''
Created on 23/04/2013

@author: Pela
'''
import cv2
import sys
import numpy as np

img = cv2.imread('../img/markers.jpg')
img_gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
cv2.cv.Smooth(img_gray, img_gray, cv2.cv.CV_GAUSSIAN, 3, 3)
img_binary = cv2.cv.CreateImage(cv2.cv.GetSize(img_gray), cv2.cv.IPL_DEPTH_8U, 1)
cv2.adaptiveThreshold(img_binary, 255, cv2.ADAPTIVE_THRESH_MEAN_C, cv2.THRESH_BINARY_INV, 71, 15)
contours, hierarchy = cv2.findContours(img_binary, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
#approx_countours = cv2.approxPolyDP(contours, epsilon, closed)
