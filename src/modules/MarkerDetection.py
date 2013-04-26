import cv2
import math
import numpy as np
import Marker

class MarkerDetection(object):
    def __init__(self):
        #CMarkerDetection();
        self.__marker_db.append(Marker.MarkerImg('../../img/marker.bmp'))
        self.__marker_detect = []
    
    def marker_detection(self, img_src, img_dest):
        #void MarkerDetection(IplImage *src, IplImage *dest);
        print("aloo")
        
    def draw_result(self, img, marker):
        color = (255, 0, 0)
        cv2.line(img, marker.corner[0], marker.corner[1], color, 2)
        cv2.line(img, marker.corner[1], marker.corner[2], color, 2)
        cv2.line(img, marker.corner[2], marker.corner[3], color, 2)
        cv2.line(img, marker.corner[3], marker.corner[0], color, 2)
        cv2.line(img, marker.corner[0], marker.corner[2], color, 2)
        cv2.line(img, marker.corner[1], marker.corner[3], color, 2)
        return img
    
    def __perpendicular(self, l0, l1, p):
        vx = l1[0] - l0[0]
        vy = l1[1] - l0[1]
        px = p[0] - l0[0]
        py = p[1] - l0[1]
        vl = math.sqrt(vx * vx + vy * vy)
        return (px * vy - py * vx) / vl
        
    def __is_quadrangle(self, box1, box2):
        box1 = np.int0(box1)
        box2 = np.int0(box2)
        p1 = []
        p2 = []
        for i in range(4):
            p1[i] = box1[i]
            p2[i] = box2[i]
        
        d = [math.fabs(self.__perpendicular(p1[0], p1[2], p2[0])),
             math.fabs(self.__perpendicular(p1[0], p1[2], p2[1])),
             math.fabs(self.__perpendicular(p1[0], p1[2], p2[2])),
             math.fabs(self.__perpendicular(p1[0], p1[2], p2[3])),
             
             math.fabs(self.__perpendicular(p1[1], p1[3], p2[0])),
             math.fabs(self.__perpendicular(p1[1], p1[3], p2[1])),
             math.fabs(self.__perpendicular(p1[1], p1[3], p2[2])),
             math.fabs(self.__perpendicular(p1[1], p1[3], p2[3]))]
        
        threshold = 5
        if d[0] < threshold and d[2] < threshold and d[5] < threshold and d[7] < threshold:
            return True
        if d[1] < threshold and d[3] < threshold and d[4] < threshold and d[6] < threshold:
            return True
        return False
            
        
    def __find_quadrangle_region(self, contours, level):
        """ 
        for (CvSeq *s = contours; s; s = s->h_next){
            if (level%2 == 0 && s->v_next && s->total == 4 && s->v_next->total == 4) {
                if (IsQuadrangle(s, s->v_next)) {
                    sMarkerAreaInfo marker;
                    marker.corner[0] = *(CvPoint *)cvGetSeqElem(s->v_next, 0);
                    marker.corner[1] = *(CvPoint *)cvGetSeqElem(s->v_next, 1);
                    marker.corner[2] = *(CvPoint *)cvGetSeqElem(s->v_next, 2);
                    marker.corner[3] = *(CvPoint *)cvGetSeqElem(s->v_next, 3);
                    
                    marker.CalcSize ();
    
                    _markerDetect.push_back (marker);
                }
            }
    
            if (s->v_next) {
                FindQuadrangleRegion (s->v_next, level+1);
            }
        }
        """
        #void FindQuadrangleRegion (CvSeq *contours, int level);
        print("aloo")
        
    def __crete_marker_image(self, img, marker_area_info):
        #IplImage *CreateMarkerImage (IplImage *img, sMarkerAreaInfo &marker);
        print("aloo")
        
    def __find_marker(self, img_marker):
        #int FindMarker (IplImage *imgMarker);
        print("aloo")

