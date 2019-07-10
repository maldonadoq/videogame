#include "../inc/listen.h"

bool state;

bool TListener::checkFist(const Hand& hand){

    float sum = 0;
    int n = 0;
    bool r = false;
    
    const FingerList fingers = hand.fingers();
    Vector meta, proxi, inter;

    for (FingerList::const_iterator fl = fingers.begin(); fl != fingers.end(); ++fl){
        const Finger finger = *fl;
        
        meta  = finger.bone(static_cast<Bone::Type>(0)).direction();
        proxi = finger.bone(static_cast<Bone::Type>(1)).direction();
        inter = finger.bone(static_cast<Bone::Type>(2)).direction();
        // std::cout << std::string(6, ' ') << bone.direction() << std::endl;
        sum += meta.dot(proxi);
        sum += proxi.dot(inter);

        if(finger.isExtended())
            n++;
    }    

    sum = sum / 10;
    if (sum <= 0.5 && n == 0)
        r = true;

    return r;
}

int TListener::checkFingers(const Hand& hand){
    int n = 0;
    const FingerList fingers = hand.fingers();
    for (FingerList::const_iterator fl = fingers.begin(); fl != fingers.end(); ++fl){
        const Finger finger = *fl;
        if(finger.isExtended())
            n++;
    }

    return n;
}

void TListener::onInit(const Controller& controller) {
    std::cout << "Initialized" << std::endl;
}

void TListener::onConnect(const Controller& controller) {
    std::cout << "Connected" << std::endl;
    controller.enableGesture(Gesture::TYPE_CIRCLE);
    controller.enableGesture(Gesture::TYPE_KEY_TAP);
    controller.enableGesture(Gesture::TYPE_SCREEN_TAP);
    controller.enableGesture(Gesture::TYPE_SWIPE);
}

void TListener::onDisconnect(const Controller& controller) {
    // Note: not dispatched when running in a debugger.
    std::cout << "Disconnected" << std::endl;
}

void TListener::onExit(const Controller& controller) {
    std::cout << "Exited" << std::endl;
}

void TListener::onFrame(const Controller& controller) {
    const Frame frame = controller.frame();

    state = false;

    // Get gestures
    const GestureList gestures = frame.gestures();
    for (int g = 0; g < gestures.count() and !state; ++g) {
        Gesture gesture = gestures[g];

        // std::cout << gesture.duration() << " ms\n";
        switch (gesture.type()) {
            case Gesture::TYPE_CIRCLE:{
                CircleGesture circle = gesture;
                gesture_idx = 0;

                gesture_state = true;
                state = true;
                if (circle.pointable().direction().angleTo(circle.normal()) <= PI/2){
                    gesture_sentido = 1;
                }
                else{
                	gesture_sentido = -1;
                }

                break;
            }
            
            case Gesture::TYPE_SWIPE:{
                SwipeGesture swipe = gesture;
                gesture_idx = 1;
                gesture_state = true;
                state = true;
                
                if(swipe.direction().x < -0.7f)         gesture_sentido = 1;
                else if(swipe.direction().x > 0.6f)     gesture_sentido = 2;
                else if(swipe.direction().y < -0.7f)	gesture_sentido = 3;
                else if(swipe.direction().y > 0.6f)	    gesture_sentido = 4;
                break;
            }
            case Gesture::TYPE_KEY_TAP:{
                KeyTapGesture tap = gesture;
                gesture_idx = 2;
                gesture_state = true;
                state = true;
                break;
            }
            case Gesture::TYPE_SCREEN_TAP:{
                ScreenTapGesture screentap = gesture;
                gesture_idx = 3;
                gesture_state = true;
                state = true;
                break;
            }
            default:{            	
                // std::cout << std::string(2, ' ')  << "Unknown gesture type." << std::endl;
                break;
            }
        }
    }

    if(!state){
        HandList hands = frame.hands();
        Hand hand;
        if (hands.count() == 1) {
            hand = hands.frontmost();
            // std::cout << (hand.fingers()).count() << "\n";
            int fing = checkFingers(hand);
            if (checkFist(hand)) {
                gesture_idx = 4;
                gesture_state = true;
            }
            else if(fing == 1){
                gesture_idx = 5;
                gesture_state = true;
            }
            else if(fing == 2){
                gesture_idx = 6;
                gesture_state = true;
            }
            else if(fing == 3){
                gesture_idx = 7;
                gesture_state = true;
            }
        }
    }
}

void TListener::onFocusGained(const Controller& controller) {
  std::cout << "Focus Gained" << std::endl;
}

void TListener::onFocusLost(const Controller& controller) {
  std::cout << "Focus Lost" << std::endl;
}

void TListener::onDeviceChange(const Controller& controller) {
  std::cout << "Device Changed" << std::endl;
  const DeviceList devices = controller.devices();

  for (int i = 0; i < devices.count(); ++i) {
    std::cout << "id: " << devices[i].toString() << std::endl;
    std::cout << "  isStreaming: " << (devices[i].isStreaming() ? "true" : "false") << std::endl;
  }
}

void TListener::onServiceConnect(const Controller& controller) {
  std::cout << "Service Connected" << std::endl;
}

void TListener::onServiceDisconnect(const Controller& controller) {
  std::cout << "Service Disconnected" << std::endl;
}