from PIL import Image
import numpy as np
import cv2

np_image = np.load('./keypoints/KEYP_IMG00.npy')

img = Image.fromarray(np_image)

cv2.namedWindow('Display Window')        ## create window for display
cv2.imshow('Display Window', np_image)
cv2.waitKey(0)                           ## Wait for keystroke
cv2.destroyAllWindows()
