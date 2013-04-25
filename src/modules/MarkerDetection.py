class CMarkerDetection(object):
    def __init__(self):
        #CMarkerDetection();
        self.__marker_db = []
        self.__marker_detect = []
    
    def marker_detection(self, img_src, img_dest):
        #void MarkerDetection(IplImage *src, IplImage *dest);
        print("aloo")
        
    def draw_result(self):
        #void DrawResult(IplImage *src, sMarkerAreaInfo &marker);
        print("aloo")
        
    def __is_quadrangle(self, box1, box2):
        #bool IsQuadrangle(CvSeq *box1, CvSeq *box2);
        print("aloo")
        
    def __find_quadrangle_region(self, contours, level):
        #void FindQuadrangleRegion (CvSeq *contours, int level);
        print("aloo")
        
    def __crete_marker_image(self, img, marker_area_info):
        #IplImage *CreateMarkerImage (IplImage *img, sMarkerAreaInfo &marker);
        print("aloo")
        
    def __find_marker(self, img_marker):
        #int FindMarker (IplImage *imgMarker);
        print("aloo")
        
    def __del__(self):
        #~CMarkerDetection();
        print("aloo")
