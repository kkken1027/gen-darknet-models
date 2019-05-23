# Training model command
### 下載darknet https://pjreddie.com/darknet/yolo/
git clone https://github.com/pjreddie/darknet</BR>
cd darknet; make</BR>

### 資料收集生成錄像檔
cd tools/video_record; make</BR>
./VideoRecord -camera 0 -time 10</BR>

### 標籤錄像檔轉成image and xml file
cd tools/video_labeler</BR>
定義標籤類別</BR>
data/labels_name.txt</BR>
生成output/images 和 output/labels 資料夾與內容</BR>
python2 --save_type 1 --write_im track_labeler.py ../video_record/xxx.avi data/labels_name.txt outputs</BR>

### 生成資料與訓練
回到最上層目錄修改 train.py 內的 classList、cfgFolder、modelYOLO、testRatio</BR>
生成tools/video_labeler/output/yolo 資料夾與darknet 的訓練資料格式</BR>
權重與cfg 產生於cfgFolder</BR>
python3 train.py</BR>
