import os
import cv2
import time

class BoxSaver():
    def __init__(self,save_dir,save_im=False,save_type=0):
        self.save_dir=save_dir
        self.save_im=save_im
        self.label_file='%s/labels.txt'%(self.save_dir)
        self.save_type=save_type

    def save(self,im,frame_id,boxes_iter):
        if self.save_type == 0:
            for idx,(box,label) in enumerate(boxes_iter):
                p0, p1 = box
                with open(self.label_file,'a') as f:
                    # write format frame_id label x0 y0 x1 y1
                    f.write("%d %s %d %d %d %d\n"%(frame_id,label,p0[0],p1[0],p0[1],p1[1]))
                if self.save_im:
                    filename = '%s/%s/%d_%d.jpg' % (self.save_dir,label, frame_id, idx)
                    dir=os.path.split(filename)[0]
                    if not os.path.exists(dir):
                        os.makedirs(dir)
                    filename=os.path.abspath(filename)
                    obj_im=im[p0[1]:p1[1],p0[0]:p1[0]]
                    cv2.imwrite(filename,obj_im)
        
        elif self.save_type == 1:
            labeltime = time.strftime("%Y_%m_%d_%H_%M_%S", time.localtime())
            for idx,(box,label) in enumerate(boxes_iter):
                filejpg = '%s/images/%s_%s.jpg' % (self.save_dir, label, labeltime)
                filexml = '%s/labels/%s_%s.xml' % (self.save_dir, label, labeltime)
                dir1=os.path.split(filejpg)[0]
                if not os.path.exists(dir1):
                    os.makedirs(dir1)
                dir2=os.path.split(filexml)[0]
                if not os.path.exists(dir2):
                    os.makedirs(dir2)
                
                p0, p1 = box
                with open(filexml,'w') as f:
                    # write format frame_id label x0 y0 x1 y1
                    # TODO
                    f.write("<annotation>\n")
                    f.write("    <folder>images</folder>\n")
                    f.write("    <filename>%s_%s.jpg</filename>\n"%(label, labeltime))
                    f.write("    <path>%s</path>\n"%(filejpg))
                    f.write("    <source>\n")
                    f.write("        <database>Unknown</database>\n")
                    f.write("    </source>\n")
                    
                    f.write("    <size>\n")
                    f.write("        <width>%d</width>\n"%(im.shape[1]))
                    f.write("        <height>%d</height>\n"%(im.shape[0]))
                    f.write("        <depth>%d</depth>\n"%(im.shape[2]))
                    f.write("    </size>\n")
                    f.write("    <segmented>0</segmented>\n")
                    f.write("    <object>\n")
                    f.write("        <name>%s</name>\n"%(label))
                    f.write("        <pose>Unspecified</pose>\n")
                    f.write("        <truncated>0</truncated>\n")
                    f.write("        <difficult>0</difficult>\n")
                    f.write("        <bndbox>\n")
                    f.write("            <xmin>%d</xmin>\n"%(p0[0]))
                    f.write("            <ymin>%d</ymin>\n"%(p0[1]))
                    f.write("            <xmax>%d</xmax>\n"%(p1[0]))
                    f.write("            <ymax>%d</ymax>\n"%(p1[1]))
                    f.write("        </bndbox>\n")
                    f.write("    </object>\n")
                    f.write("</annotation>\n")
                    
                    #f.write("%d %s %d %d %d %d\n"%(frame_id,label,p0[0],p1[0],p0[1],p1[1]))
                   
                    
                    
                if self.save_im:
                    filename=os.path.abspath(filejpg)
                    cv2.imwrite(filename,im)