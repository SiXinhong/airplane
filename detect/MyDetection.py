from imageai.Detection import ObjectDetection
import os
import json
from PIL import ImageFile
ImageFile.LOAD_TRUNCATED_IMAGES = True
class MyDetection:
    def __init__(self):
        pass
    def setDetection(self):
        execution_path = os.getcwd()
        self.detector = ObjectDetection()
        self.detector.setModelTypeAsYOLOv3()
        self.detector.setModelPath( os.path.join(execution_path , "yolo.h5"))
        self.detector.loadModel(detection_speed="normal")
        self.detector.detectObjectsFromImage(input_image=os.path.join(execution_path , "t.jpg"), output_image_path=os.path.join(execution_path , "image3new.jpg"), minimum_percentage_probability=30)
    def detectionImage(self,imageName):
        res=self.detector.detectObjectsFromImage(input_image=imageName,
                                             minimum_percentage_probability=30)
        a = list()
        for i in res:
            t = dict()
            t['name'] = i['name']
            t['box_points'] = list()
            t['box_points'].append(int(i['box_points'][0]))
            t['box_points'].append(int(i['box_points'][1]))
            t['box_points'].append(int(i['box_points'][2]))
            t['box_points'].append(int(i['box_points'][3]))
            a.append(t)
        ret = dict()
        ret['filename']= imageName
        ret['data'] = a
        print(ret)
        return json.dumps(ret)
