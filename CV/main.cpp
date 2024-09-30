#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    // Load Haar Cascade for face detection
    CascadeClassifier face_cascade;
    if (!face_cascade.load("/Users/pparakala/Personal/Projects/CV/haarcascade_frontalface_default.xml")) {
        cout << "Error loading cascade file!" << endl;
        return -1;
    }

    // Open the default camera
    VideoCapture cap(1); 
    if (!cap.isOpened()) {
        cout << "Error opening video stream!" << endl;
        return -1;
    }

    // Main loop to capture frames from the camera
    while (cap.isOpened()) {
        Mat frame;
        cap >> frame; // Capture the frame
        if (frame.empty()) break;

        // Convert to grayscale
        Mat gray;
        cvtColor(frame, gray, COLOR_BGR2GRAY);
        equalizeHist(gray, gray);

        // Detect faces in the frame
        vector<Rect> faces;
        face_cascade.detectMultiScale(gray, faces);

        // Output message if a face is detected
        if (!faces.empty()) {
            cout << "Face detected!" << endl;
        }
        else {
            cout << "Face not detected!" << endl;
        }

        // Draw rectangle around faces
        for (size_t i = 0; i < faces.size(); i++) {
            rectangle(frame, faces[i], Scalar(255, 0, 0), 2);
        }

        // Display the resulting frame
        imshow("Camera Feed", frame);

        // Exit if 'q' is pressed
        if (waitKey(10) == 'q') {
            break;
        }
    }

    cap.release(); // Release the camera
    destroyAllWindows(); // Close all windows
    return 0;
}
