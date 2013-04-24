'''
Created on 23/04/2013

@author: Pela
'''
import cv2
import sys
import numpy as np

img = cv2.imread('../img/3.jpg')
template = cv2.imread('../img/2.jpg')
(imgw, imgh, imgt) = img.shape
(templatew, templateh, templatet) = template.shape
 
if img == None or template == None:
    print("No pude abrir una imagen")
    sys.exit()
    
result = cv2.matchTemplate(img, template, cv2.TM_SQDIFF)
print(result)
#the get the best match fast use this:
(min_x, max_y, minloc, maxloc) = cv2.minMaxLoc(result)
(x, y) = minloc
print(minloc)
#get all the matches:
result2 = np.reshape(result, result.shape[0] * result.shape[1])
sort = np.argsort(result2)
for i in range(3):
    (y, x) = np.unravel_index(sort[i], result.shape) #best match
    print(y, x)    
    cv2.line(img, (x, y), (x + templatew, y), (255, 0, 255))
    cv2.line(img, (x, y), (x, y + templateh), (255, 0, 255))
    cv2.line(img, (x, y + templateh), (x + templatew, y + templateh), (255, 0, 255))
    cv2.line(img, (x + templatew, y), (x + templatew, y + templateh), (255, 0, 255))

cv2.namedWindow('Display Window')        ## create window for display
cv2.imshow('Display Window', img)
cv2.waitKey(0)                           ## Wait for keystroke
cv2.destroyAllWindows()