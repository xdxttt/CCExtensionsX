#pragma once
class UMFeedbackWrapper{
public:
    UMFeedbackWrapper();
    ~UMFeedbackWrapper();
    static UMFeedbackWrapper *getInstance();
    static void destroyInstance();
    void showFeedback(std::string appKey);
};