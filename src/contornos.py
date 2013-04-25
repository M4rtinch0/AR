import cv2
import numpy as np

img = cv2.imread('../img/markers.png')

cv2.namedWindow('input')
img_gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

ret, tresh = cv2.threshold(img_gray, 177, 255, 0)
contours, hierarchy = cv2.findContours(tresh, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
img2 = img.copy()
print(len(contours))
for i in range(len(contours)):
    print(i)
    cnt = contours[i]
    approx = cv2.approxPolyDP(cnt, 0.1 * cv2.arcLength(cnt, True), True)
    cv2.drawContours(img2, [cnt], 0, (255, 0, 0), 5)
    hull = cv2.convexHull(approx)
    x, y, w, h = cv2.boundingRect(hull)
    #cv2.rectangle(img2, (x,y), (x + w, y + h), (0, 255, 0), 4)
    #rect = cv2.minAreaRect(hull)
    #box = cv2.cv.BoxPoints(rect)
    #box = np.int0(box)
    #cv2.drawContours(img2, [box], 0, (0, 0, 255), 3) 
cv2.imshow('input', img2)
cv2.waitKey(0)
cv2.destroyAllWindows()