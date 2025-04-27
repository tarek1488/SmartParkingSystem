import cv2

from ultralytics import solutions
from utils import upload_val_to_firebase
# Video capture
cap = cv2.VideoCapture(0)
assert cap.isOpened(), "Error reading video file"

# Video writer
w, h, fps = (int(cap.get(x)) for x in (cv2.CAP_PROP_FRAME_WIDTH, cv2.CAP_PROP_FRAME_HEIGHT, cv2.CAP_PROP_FPS))
video_writer = cv2.VideoWriter("parking management.avi", cv2.VideoWriter_fourcc(*"mp4v"), fps, (w, h))

# Initialize parking management object
nameees = {64:"Car",65:"Car",67:"Car",79:"Car"}
parkingmanager = solutions.ParkingManagement(
    model="yolo11l.pt",  # path to model file
    json_file="bounding_boxes.json",# path to parking annotations file,  
    classes =[64,65,67,79,2],   
)

while cap.isOpened():
    ret, im0 = cap.read()
    if not ret:
        break

    results = parkingmanager(im0)
    upload_val_to_firebase(available_slots= results.available_slots)

    # print(results)  # access the output

    video_writer.write(results.plot_im)  # write the processed frame.
    cv2.imshow("frame",results.plot_im )
    key = cv2.waitKey(1) & 0xFF
    if key == ord('q'):
        break

cap.release()
video_writer.release()
cv2.destroyAllWindows()  # destroy all opened windows