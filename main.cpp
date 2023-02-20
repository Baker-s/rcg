#include <opencv4/opencv2/opencv.hpp>

using namespace cv;

int main() {
    //Working person detection in laptop camera
    //VideoCapture cap(0);
    VideoCapture cap("rtsp://externaluser:1kL6H7sj06bbhD2@188.169.66.2:554/Streaming/Channels/2001/?transportmode=unicast"); //1
    //VideoCapture cap("rtsp://externaluser:1kL6H7sj06bbhD2@31.146.183.134:654/Streaming/Channels/801/?transportmode=unicast"); //2
    //VideoCapture cap("rtsp://externaluser:1kL6H7sj06bbhD2@31.146.131.74:554/Streaming/Channels/1401/?transportmode=unicast"); //3

    cv::dnn::Net net = cv::dnn::readNetFromDarknet("dnn_model/yolov4-tiny.cfg","dnn_model/yolov4-tiny.weights");
    cv::dnn::DetectionModel model(net);
    model.setInputParams((double)1/255, cv::Size(320, 320), Scalar());

    while (true) {
        Mat frame;
        cap.read(frame);

        std::vector<int> class_ids;
        std::vector<float> scores;
        std::vector<Rect> bboxes;

        model.detect(frame, class_ids, scores, bboxes);

        printf("Size: %ld\n", bboxes.size());
        for (size_t i = 0; i < bboxes.size(); i++) {
            Rect bbox = bboxes[i];
            int x = bbox.x;
            int y = bbox.y;
            int w = bbox.width;
            int h = bbox.height;
            printf("x: %d, y: %d, w: %d, h: %d box size: %ld\n", x, y, w, h, bboxes.size());
            cv::rectangle(frame, bbox, Scalar(200, 0, 50), 3);
        }

        imshow("Frame", frame);
        char key = waitKey(1);
        if (key == 27)
            break;
    }

    cap.release();
    return 0;
}
