import cv2

# Initialize the video capture. Change the index (0, 1, etc.) if needed.
cap = cv2.VideoCapture(0)

if not cap.isOpened():
    print("Unable to access the camera")
    exit()

while True:
    ret, frame = cap.read()
    if not ret:
        print("Failed to grab frame")
        break

    # Display the live video stream
    cv2.imshow('Webcam', frame)

    key = cv2.waitKey(1) & 0xFF
    # Press 's' to save the current frame as an image file
    if key == ord('s'):
        filename = "saved_image.jpg"
        cv2.imwrite(filename, frame)
        print(f"Image saved as {filename}")
    # Press 'q' to exit the loop and close the program
    elif key == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
