#include "Graphics.h"
#include <algorithm>

using namespace cv;
using namespace std;

//////////////////////////////////////////////////

SingleAnimationGraphics::SingleAnimationGraphics(AnimationPtr animPtr, bool isCyclic)
    :_animation(animPtr), _currFrameIdx(0)
    , _isCyclic(isCyclic)
{    
}


cv::Mat SingleAnimationGraphics::getCollisionMask()
{
    return _animation->getFrame(_currFrameIdx).mask;
}

void SingleAnimationGraphics::draw(cv::Mat& canvas, cv::Point const& topLeft)
{
    drawFrame(_animation->getFrame(_currFrameIdx), canvas, topLeft);
}

void SingleAnimationGraphics::reset(int code)
{
    _currFrameIdx = 0;
}

bool SingleAnimationGraphics::update()
{
    bool hasFinished = (_currFrameIdx == _animation->numFrames() - 1);
    if (_isCyclic)
        _currFrameIdx = (_currFrameIdx + 1) % _animation->numFrames();
    else 
        _currFrameIdx = min<int>(_currFrameIdx + 1, (int)_animation->numFrames() - 1);

    return hasFinished;
}
///////////////////LivesGraphics///////////////////////////////
LivesGraphics::LivesGraphics(Frame _singleLife, int _livesCount):_singleLife(_singleLife), _livesCount(_livesCount)
{  
}
Mat LivesGraphics::getCollisionMask()
{
    return cv::Mat();
}
void LivesGraphics::draw(cv::Mat& canvas, cv::Point const& topLeft)
{
    drawFrame(Frame (_singleLife), canvas, topLeft);
}
void LivesGraphics::reset(int code)
{
    _livesCount = code;
}
bool LivesGraphics::update()
{
    return false;
}

//////////////ScoresGraphics////////
ScoresGraphics::ScoresGraphics(float _fontScale, int _score, int _fontFace):_fontScale(_fontScale),_score(_score),_fontFace(_fontFace)
{
}
Mat ScoresGraphics::getCollisionMask()
{
    return cv::Mat();
}
void ScoresGraphics::draw(cv::Mat& canvas, cv::Point const& topLeft)
{
    string text = "score: ";
    string moreText = to_string(_score);
    text = text + moreText;
    Scalar color(0, 0, 255);
    int thickness = 2;
    int lineType = FILLED;
    putText(canvas, text, topLeft, _fontFace, _fontScale, color, thickness, lineType);
    imshow("test", canvas);
    waitKey();//waiting forever till some key is hit.
}
void ScoresGraphics::reset(int code)
{
   this->_score = code;
}
bool ScoresGraphics::update()
{
    return false;
}
void exampleOfPutText()
{
    Mat image = imread(R"(../Animations/background.png)", IMREAD_UNCHANGED);
    string text = "score: ";
    int score = 465;
    string moreText = to_string(score);
    text = text + moreText;
    Point topLeft(50, 50);
    int fontFace = FONT_HERSHEY_SIMPLEX; // normal size sans - serif font
    // other options for fontFace:
    FONT_HERSHEY_PLAIN;// small size sans - serif font
    FONT_HERSHEY_DUPLEX;// normal size sans - serif font(more complex than FONT_HERSHEY_SIMPLEX)
    FONT_HERSHEY_COMPLEX; // normal size serif font
    FONT_HERSHEY_TRIPLEX; //normal size serif font(more complex than FONT_HERSHEY_COMPLEX)
    FONT_HERSHEY_COMPLEX_SMALL; //smaller version of FONT_HERSHEY_COMPLEX
    FONT_HERSHEY_SCRIPT_SIMPLEX; //hand - writing style font
    FONT_HERSHEY_SCRIPT_COMPLEX;// more complex variant of FONT_HERSHEY_SCRIPT_SIMPLEX
    double fontScale = 2; // Font scale factor that is multiplied by the font-specific base size.
    Scalar color(/*Blue between 0...255 =*/0,/*Green between 0...255 =*/0,/*Red between 0...255 =*/255); 
    int thickness = 2;
    int lineType = FILLED;
    // other options for line type:
    LINE_4; LINE_8; LINE_AA;

    // finally:
    putText(image, text, topLeft, fontFace, fontScale, color, thickness, lineType);
    
    imshow("test", image);
    waitKey();//waiting forever till some key is hit.
}

