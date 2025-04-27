from ultralytics import solutions
solutions.ParkingPtsSelection()
import json
import numpy as np
from typing import List
import cv2

# def get_parking_spots_bboxes(connected_components):
#     (totalLabels, label_ids, values, centroid) = connected_components

#     slots = []
#     coef = 1
#     for i in range(1, totalLabels):

#         # Now extract the coordinate points
#         x1 = int(values[i, cv2.CC_STAT_LEFT] * coef)
#         y1 = int(values[i, cv2.CC_STAT_TOP] * coef)
#         w = int(values[i, cv2.CC_STAT_WIDTH] * coef)
#         h = int(values[i, cv2.CC_STAT_HEIGHT] * coef)

#         slots.append([x1, y1, w, h])

#     return slots
# def get_coordinates():
#     box_coordinates = []
#     all_points = []
#     with open('bounding_boxes.json', 'r') as f:
#         data = json.load(f)
#         for i in range(len(data)):    
#             points = data[i]['points']
#             points = np.array(points)
#             all_points.append(points)
#             x_coords = points[:, 0]
#             y_coords = points[:,1]
            
#             x1 = np.min(x_coords)
#             y1 = np.min(y_coords)
#             x2 = np.max(x_coords)
#             y2 = np.max(y_coords)

#             w = x2 - x1
#             h = y2 - y1
#             box_coordinates.append([x1,y1,w,h])
#         return all_points

# def draw_boxes(mask_path: str, img_path: str):
#     mask = cv2.imread(mask_path,0)
#     img = cv2.imread(img_path)
#     connected_components = cv2.connectedComponentsWithStats(mask, 4, cv2.CV_32S)

#     spots = get_parking_spots_bboxes(connected_components)
#     for spot in spots:
#         x1,y1,w,h = spot
#         cv2.rectangle(img, (x1,y1), (x1 + w , y1+h), (255,0,0), 1)
#         cv2.imwrite("masked_park.jpg", img)
        
            

# def create_mask_from_polygons(image_path, polygons, fill_value=255):
#     # Load the image to get size
#     image = cv2.imread(image_path)
#     height, width = image.shape[:2]

#     # Create a blank black mask
#     mask = np.zeros((height, width), dtype=np.uint8)

#     # Fill each polygon
#     for poly in polygons:
#         pts = poly.astype(np.int32)
#         cv2.fillPoly(mask, [pts], color=fill_value)
#     return mask
# # Example usage
# if __name__ == "__main__":
#     image_path = 'saved_image.jpg'
#     coor = get_coordinates()
#     mask = create_mask_from_polygons(image_path, coor)

#     # Save or show the result
#     cv2.imwrite('polygon_mask.png', mask)
#     draw_boxes("polygon_mask.png", image_path)
#     #print(coor)
#     #draw_boxes(coordinates=coor,img_path="saved_image.jpg")
