import cv2
import numpy as np

drawing = False  # true if mouse is pressed
mode = True  # if True, draw rectangle. Press 'm' to toggle to curve
ix, iy = -1, -1


# mouse callback function
def draw_circle(event, x, y, flags, param):
    global ix, iy, drawing, mode

    if event == cv2.EVENT_LBUTTONDOWN:
        drawing = True
        ix, iy = x, y

    elif event == cv2.EVENT_MOUSEMOVE:
        if drawing == True:
            if mode == True:
                cv2.circle(img, (x, y), 1, (0, 0, 0), -1)
            else:
                cv2.circle(img, (x, y), 1, (0, 0, 0), -1)

    elif event == cv2.EVENT_LBUTTONUP:
        drawing = False
        if mode == True:
            cv2.circle(img, (x, y), 1, (0, 0, 0), -1)
        else:
            cv2.circle(img, (x, y), 1, (0, 0, 0), -1)


img = np.full((600, 600, 3), 255, dtype=np.uint8)
cv2.namedWindow('image')
cv2.setMouseCallback('image', draw_circle)

while (1):
    cv2.imshow('image', img)
    k = cv2.waitKey(33)
    if k == 32:  # Esc key to stop
        break

cv2.imwrite("../example/input.jpg",img)
cv2.destroyAllWindows()
