// gcc -Wall -o globalkeypress globalkeypress.c -framework ApplicationServices && ./globalkeypress

#include <ApplicationServices/ApplicationServices.h>
#include <pthread.h>

void delayCGEventPost(CGEventTapLocation tap, CGEventRef event){
    CGEventPost(tap, event);
    usleep(15000);
}

// 血岩碎片
void* xueyan(void* args){
    int i = 0;
    CGPoint point;
    CGEventRef ourEvent = CGEventCreate(NULL);
    point = CGEventGetLocation(ourEvent);
    CFRelease(ourEvent);

    CGEventRef theEvent = CGEventCreateMouseEvent(NULL, kCGEventRightMouseDown, point, kCGMouseButtonRight);  
    CGEventSetIntegerValueField(theEvent, kCGMouseEventClickState, 1);  
    delayCGEventPost(kCGHIDEventTap, theEvent);  
    CGEventSetType(theEvent, kCGEventRightMouseUp);  
    delayCGEventPost(kCGHIDEventTap, theEvent);  

    for(i=0; i!= 30; i++){
        CGEventSetType(theEvent, kCGEventRightMouseDown);  
        delayCGEventPost(kCGHIDEventTap, theEvent);  
        CGEventSetType(theEvent, kCGEventRightMouseUp); 
        delayCGEventPost(kCGHIDEventTap, theEvent); 
    }

    CFRelease(theEvent); 
    return NULL;
}

// 分解装备
void* fenjie(void* args){
    int i=0, j=0;
    int gridX = 1430, gridY = 585;
    CGPoint pointGrid;
    CGPoint pointYello = CGPointMake(385, 290);
    CGPoint pointBlue = CGPointMake(320, 290);
    CGPoint pointWhite = CGPointMake(255, 290);
    CGPoint pointOrange = CGPointMake(170, 295);

    CGEventRef enterDown = CGEventCreateKeyboardEvent (NULL, (CGKeyCode)36, true);  // Enter
    CGEventRef enterUp = CGEventCreateKeyboardEvent (NULL, (CGKeyCode)36, false);  // Enter
    CGEventRef theEvent;

    // 分解黄装
    theEvent = CGEventCreateMouseEvent(NULL, kCGEventLeftMouseDown, pointYello, kCGMouseButtonLeft);  
    CGEventSetIntegerValueField(theEvent, kCGMouseEventClickState, 1);  
    delayCGEventPost(kCGHIDEventTap, theEvent); 
    CGEventSetType(theEvent, kCGEventLeftMouseUp);  
    delayCGEventPost(kCGHIDEventTap, theEvent);
    
    delayCGEventPost(kCGHIDEventTap, enterDown);
    delayCGEventPost(kCGHIDEventTap, enterUp);
    delayCGEventPost(kCGHIDEventTap, enterDown);
    delayCGEventPost(kCGHIDEventTap, enterUp);

    // 分解蓝装
    CGEventSetLocation(theEvent, pointBlue);
    CGEventSetType(theEvent, kCGEventLeftMouseDown); 
    delayCGEventPost(kCGHIDEventTap, theEvent); 
    CGEventSetType(theEvent, kCGEventLeftMouseUp);  
    delayCGEventPost(kCGHIDEventTap, theEvent);
    
    delayCGEventPost(kCGHIDEventTap, enterDown);
    delayCGEventPost(kCGHIDEventTap, enterUp);
    delayCGEventPost(kCGHIDEventTap, enterDown);
    delayCGEventPost(kCGHIDEventTap, enterUp);

    // 分解白装
    CGEventSetLocation(theEvent, pointWhite);
    CGEventSetType(theEvent, kCGEventLeftMouseDown); 
    delayCGEventPost(kCGHIDEventTap, theEvent); 
    CGEventSetType(theEvent, kCGEventLeftMouseUp);  
    delayCGEventPost(kCGHIDEventTap, theEvent);
    
    delayCGEventPost(kCGHIDEventTap, enterDown);
    delayCGEventPost(kCGHIDEventTap, enterUp);
    delayCGEventPost(kCGHIDEventTap, enterDown);
    delayCGEventPost(kCGHIDEventTap, enterUp);

    // 分解硫磺
    CGEventSetLocation(theEvent, pointOrange);
    CGEventSetType(theEvent, kCGEventLeftMouseDown); 
    delayCGEventPost(kCGHIDEventTap, theEvent); 
    CGEventSetType(theEvent, kCGEventLeftMouseUp);  
    delayCGEventPost(kCGHIDEventTap, theEvent); 

    for (i=0; i!=10; i++){
        gridX = 1430 + i*50;

        for(j=0; j!=6; j++){
            gridY = 585 + j*50;

            if (!(j >= 4 && i >= 5)){
                // printf("gridX = %d, gridY = %d \n", gridX, gridY);

                pointGrid = CGPointMake(gridX, gridY);
                CGEventSetLocation(theEvent, pointGrid);
                CGEventSetType(theEvent, kCGEventLeftMouseDown); 
                delayCGEventPost(kCGHIDEventTap, theEvent); 
                CGEventSetType(theEvent, kCGEventLeftMouseUp);  
                delayCGEventPost(kCGHIDEventTap, theEvent);

                // usleep(100000);

                delayCGEventPost(kCGHIDEventTap, enterDown);
                delayCGEventPost(kCGHIDEventTap, enterUp);
                delayCGEventPost(kCGHIDEventTap, enterDown);
                delayCGEventPost(kCGHIDEventTap, enterUp);
            }

        }
    }

    CFRelease(theEvent); 
    CFRelease(enterDown); 
    CFRelease(enterUp); 

    return NULL;
}

// 辅助猎魔
const int FUZHU_TYPE_DH  = 7;   // 猎魔
const int FUZHU_TYPE_DJ  = 8;   // 豆角
const int FUZHU_TYPE_MZ  = 9;   // 蛮子
const int FUZHU_TYPE_FS  = 5;   // 蛮子
const int FUZHU_TYPE_SL  = 4;   // 死灵

int gFuzhuType = 0;
void* fuzhuDH(void* args){
    gFuzhuType = FUZHU_TYPE_DH;
    CGEventRef qDown = CGEventCreateKeyboardEvent (NULL, (CGKeyCode)12, true);  // q
    CGEventRef qUp = CGEventCreateKeyboardEvent (NULL, (CGKeyCode)12, false);  // q
    delayCGEventPost(kCGHIDEventTap, qUp);
    delayCGEventPost(kCGHIDEventTap, qDown);
    CFRelease(qDown); 
    CFRelease(qUp); 
    return NULL;
}

int gFuzhuMZTag = 0;
void* fuzhuManziLoop(void* args){
    int tag = gFuzhuMZTag;
    CGEventRef qDown = CGEventCreateKeyboardEvent (NULL, (CGKeyCode)12, true);  // q
    CGEventRef qUp = CGEventCreateKeyboardEvent (NULL, (CGKeyCode)12, false);  // q
    CGEventRef wDown = CGEventCreateKeyboardEvent (NULL, (CGKeyCode)13, true);  // w
    CGEventRef wUp = CGEventCreateKeyboardEvent (NULL, (CGKeyCode)13, false);  // w
    // CGEventRef eDown = CGEventCreateKeyboardEvent (NULL, (CGKeyCode)14, true);  // e
    // CGEventRef eUp = CGEventCreateKeyboardEvent (NULL, (CGKeyCode)14, false);  // e
    CGEventRef rDown = CGEventCreateKeyboardEvent (NULL, (CGKeyCode)15, true);  // r
    CGEventRef rUp = CGEventCreateKeyboardEvent (NULL, (CGKeyCode)15, false);  // r

    while(tag == gFuzhuMZTag){
        delayCGEventPost(kCGHIDEventTap, qUp);
        delayCGEventPost(kCGHIDEventTap, qDown);
        delayCGEventPost(kCGHIDEventTap, wUp);
        delayCGEventPost(kCGHIDEventTap, wDown);
        delayCGEventPost(kCGHIDEventTap, rUp);
        delayCGEventPost(kCGHIDEventTap, rDown);
        usleep(150000);
    }

    delayCGEventPost(kCGHIDEventTap, qUp);
    delayCGEventPost(kCGHIDEventTap, wUp);
    delayCGEventPost(kCGHIDEventTap, rUp);
    CFRelease(qDown); 
    CFRelease(qUp); 
    CFRelease(wDown); 
    CFRelease(wUp); 
    CFRelease(rDown); 
    CFRelease(rUp); 
    return NULL;
}

int gFaShiTag = 0;
void* fashiLoop(void* args){
    int tag = gFaShiTag;
    CGPoint point;

    CGEventRef qDown = CGEventCreateKeyboardEvent (NULL, (CGKeyCode)12, true);  // q
    CGEventRef qUp = CGEventCreateKeyboardEvent (NULL, (CGKeyCode)12, false);  // q
    CGEventRef wDown = CGEventCreateKeyboardEvent (NULL, (CGKeyCode)13, true);  // w
    CGEventRef wUp = CGEventCreateKeyboardEvent (NULL, (CGKeyCode)13, false);  // w
    // CGEventRef eDown = CGEventCreateKeyboardEvent (NULL, (CGKeyCode)14, true);  // e
    // CGEventRef eUp = CGEventCreateKeyboardEvent (NULL, (CGKeyCode)14, false);  // e
    CGEventRef rDown = CGEventCreateKeyboardEvent (NULL, (CGKeyCode)15, true);  // r
    CGEventRef rUp = CGEventCreateKeyboardEvent (NULL, (CGKeyCode)15, false);  // r

    // 右键按下
    CGEventRef ourEvent = CGEventCreate(NULL);
    point = CGEventGetLocation(ourEvent);
    CFRelease(ourEvent);
    CGEventRef theEvent = CGEventCreateMouseEvent(NULL, kCGEventRightMouseDown, point, kCGMouseButtonRight);  
    CGEventSetIntegerValueField(theEvent, kCGMouseEventClickState, 1);  
    delayCGEventPost(kCGHIDEventTap, theEvent);  

    delayCGEventPost(kCGHIDEventTap, wDown);
    delayCGEventPost(kCGHIDEventTap, wUp);
    delayCGEventPost(kCGHIDEventTap, rDown);
    delayCGEventPost(kCGHIDEventTap, rUp);

    while(tag == gFaShiTag){
        delayCGEventPost(kCGHIDEventTap, qUp);
        delayCGEventPost(kCGHIDEventTap, qDown);
        // delayCGEventPost(kCGHIDEventTap, wUp);
        // delayCGEventPost(kCGHIDEventTap, wDown);
        // delayCGEventPost(kCGHIDEventTap, rUp);
        // delayCGEventPost(kCGHIDEventTap, rDown);
        usleep(150000);
    }
    delayCGEventPost(kCGHIDEventTap, qUp);

    CGEventSetType(theEvent, kCGEventRightMouseUp); 
    delayCGEventPost(kCGHIDEventTap, theEvent); 

    CFRelease(qDown); 
    CFRelease(qUp); 
    CFRelease(wDown); 
    CFRelease(wUp); 
    CFRelease(rDown); 
    CFRelease(rUp); 
    CFRelease(theEvent); 
    return NULL;
}

int gFuzhuSLTag = 0;
void* fuzhuSLLoop(void* args){
    int tag = gFuzhuSLTag;
    CGEventRef qDown = CGEventCreateKeyboardEvent (NULL, (CGKeyCode)12, true);  // q
    CGEventRef qUp = CGEventCreateKeyboardEvent (NULL, (CGKeyCode)12, false);  // q
    CGEventRef wDown = CGEventCreateKeyboardEvent (NULL, (CGKeyCode)13, true);  // w
    CGEventRef wUp = CGEventCreateKeyboardEvent (NULL, (CGKeyCode)13, false);  // w
    // CGEventRef eDown = CGEventCreateKeyboardEvent (NULL, (CGKeyCode)14, true);  // e
    // CGEventRef eUp = CGEventCreateKeyboardEvent (NULL, (CGKeyCode)14, false);  // e
    CGEventRef rDown = CGEventCreateKeyboardEvent (NULL, (CGKeyCode)15, true);  // r
    CGEventRef rUp = CGEventCreateKeyboardEvent (NULL, (CGKeyCode)15, false);  // r

    while(tag == gFuzhuSLTag){
        delayCGEventPost(kCGHIDEventTap, qDown);
        delayCGEventPost(kCGHIDEventTap, qUp);
        delayCGEventPost(kCGHIDEventTap, wDown);
        usleep(200000);
        delayCGEventPost(kCGHIDEventTap, wUp);
        delayCGEventPost(kCGHIDEventTap, rDown);
        delayCGEventPost(kCGHIDEventTap, rUp);
    }

    delayCGEventPost(kCGHIDEventTap, qDown);
    delayCGEventPost(kCGHIDEventTap, wUp);
    delayCGEventPost(kCGHIDEventTap, rUp);
    CFRelease(qDown); 
    CFRelease(qUp); 
    CFRelease(wDown); 
    CFRelease(wUp); 
    CFRelease(rDown); 
    CFRelease(rUp); 
    return NULL;
}


int gFuzhuDHTag = 0;
void* fuzhuDHLoop2(void* args){
    CGPoint point;
    CGEventRef ourEvent = CGEventCreate(NULL);
    point = CGEventGetLocation(ourEvent);
    CFRelease(ourEvent);

    CGEventRef theEvent = CGEventCreateMouseEvent(NULL, kCGEventRightMouseDown, point, kCGMouseButtonRight);  
    CGEventSetIntegerValueField(theEvent, kCGMouseEventClickState, 1);  
    if(gFuzhuDHTag%2 == 0){
        CGEventSetType(theEvent, kCGEventRightMouseUp);  
    }
    delayCGEventPost(kCGHIDEventTap, theEvent);  
    return NULL;
}

void* fuzhuDHLoop3(void* args){
    int tag = gFuzhuDHTag;
    // CGEventRef qDown = CGEventCreateKeyboardEvent (NULL, (CGKeyCode)12, true);  // q
    // CGEventRef qUp = CGEventCreateKeyboardEvent (NULL, (CGKeyCode)12, false);  // q
    CGEventRef wDown = CGEventCreateKeyboardEvent (NULL, (CGKeyCode)13, true);  // w
    CGEventRef wUp = CGEventCreateKeyboardEvent (NULL, (CGKeyCode)13, false);  // w
    CGEventRef eDown = CGEventCreateKeyboardEvent (NULL, (CGKeyCode)14, true);  // e
    CGEventRef eUp = CGEventCreateKeyboardEvent (NULL, (CGKeyCode)14, false);  // e
    // CGEventRef rDown = CGEventCreateKeyboardEvent (NULL, (CGKeyCode)15, true);  // r
    // CGEventRef rUp = CGEventCreateKeyboardEvent (NULL, (CGKeyCode)15, false);  // r
    CGEventRef key5Down = CGEventCreateKeyboardEvent (NULL, (CGKeyCode)23, true);  // 5
    CGEventRef key5Up = CGEventCreateKeyboardEvent (NULL, (CGKeyCode)23, false);  // 5
    CGEventRef key6Down = CGEventCreateKeyboardEvent (NULL, (CGKeyCode)22, true);  // 6
    CGEventRef key6Up = CGEventCreateKeyboardEvent (NULL, (CGKeyCode)22, false);  // 6

    delayCGEventPost(kCGHIDEventTap, key5Down);
    delayCGEventPost(kCGHIDEventTap, key5Up);


    while(tag == gFuzhuDHTag){
        // printf("tag = %d\n", tag);
        delayCGEventPost(kCGHIDEventTap, eUp);
        delayCGEventPost(kCGHIDEventTap, wDown);
        usleep(500000);
        delayCGEventPost(kCGHIDEventTap, wUp);
        delayCGEventPost(kCGHIDEventTap, eDown);
        usleep(2000000);
    }

    // delayCGEventPost(kCGHIDEventTap, qUp);
    delayCGEventPost(kCGHIDEventTap, wUp);
    delayCGEventPost(kCGHIDEventTap, eUp);

    delayCGEventPost(kCGHIDEventTap, key6Down);
    delayCGEventPost(kCGHIDEventTap, key6Up);

    // CFRelease(qDown); 
    // CFRelease(qUp); 
    CFRelease(wDown); 
    CFRelease(wUp); 
    CFRelease(eDown); 
    CFRelease(eUp); 
    // CFRelease(rDown); 
    // CFRelease(rUp); 

    return NULL;
}

// 翻滚辅助dh
void* fuzhuDHLoop(void* args){
    int tag = gFuzhuDHTag;
    
    CGEventRef qDown = CGEventCreateKeyboardEvent (NULL, (CGKeyCode)12, true);  // q
    CGEventRef qUp = CGEventCreateKeyboardEvent (NULL, (CGKeyCode)12, false);  // q
    CGEventRef wDown = CGEventCreateKeyboardEvent (NULL, (CGKeyCode)13, true);  // w
    CGEventRef wUp = CGEventCreateKeyboardEvent (NULL, (CGKeyCode)13, false);  // w
    // CGEventRef eDown = CGEventCreateKeyboardEvent (NULL, (CGKeyCode)14, true);  // e
    // CGEventRef eUp = CGEventCreateKeyboardEvent (NULL, (CGKeyCode)14, false);  // e
    // CGEventRef rDown = CGEventCreateKeyboardEvent (NULL, (CGKeyCode)15, true);  // r
    // CGEventRef rUp = CGEventCreateKeyboardEvent (NULL, (CGKeyCode)15, false);  // r
    CGEventRef spaceDown = CGEventCreateKeyboardEvent (NULL, (CGKeyCode)49, true);  // space
    CGEventRef spaceUp = CGEventCreateKeyboardEvent (NULL, (CGKeyCode)49, false);  // space
    // CGEventRef key5Down = CGEventCreateKeyboardEvent (NULL, (CGKeyCode)23, true);  // 5
    // CGEventRef key5Up = CGEventCreateKeyboardEvent (NULL, (CGKeyCode)23, false);  // 5
    // CGEventRef key6Down = CGEventCreateKeyboardEvent (NULL, (CGKeyCode)22, true);  // 6
    // CGEventRef key6Up = CGEventCreateKeyboardEvent (NULL, (CGKeyCode)22, false);  // 6

    // delayCGEventPost(kCGHIDEventTap, key5Down);
    // delayCGEventPost(kCGHIDEventTap, key5Up);

    delayCGEventPost(kCGHIDEventTap, wDown);
    delayCGEventPost(kCGHIDEventTap, qDown);

    while(tag == gFuzhuDHTag){
        // printf("tag = %d\n", tag);
        delayCGEventPost(kCGHIDEventTap, wDown);

        // 强制站立 + 左键射击
        delayCGEventPost(kCGHIDEventTap, spaceDown);

        CGEventRef ourEvent = CGEventCreate(NULL);
        CGPoint point = CGEventGetLocation(ourEvent);
        CFRelease(ourEvent);
        // 左键
        CGEventRef theEvent = CGEventCreateMouseEvent(NULL, kCGEventLeftMouseDown, point, kCGMouseButtonLeft);  
        CGEventSetIntegerValueField(theEvent, kCGMouseEventClickState, 1);  
        delayCGEventPost(kCGHIDEventTap, theEvent);  
        CGEventSetType(theEvent, kCGEventLeftMouseUp);  
        delayCGEventPost(kCGHIDEventTap, theEvent);
        CFRelease(theEvent); 

        // 右键
        // usleep(500000);
        // CGEventRef theEvent2 = CGEventCreateMouseEvent(NULL, kCGEventRightMouseDown, point, kCGMouseButtonRight);  
        // CGEventSetIntegerValueField(theEvent2, kCGMouseEventClickState, 1);  
        // delayCGEventPost(kCGHIDEventTap, theEvent2);  
        // CGEventSetType(theEvent2, kCGEventRightMouseUp);  
        // delayCGEventPost(kCGHIDEventTap, theEvent2);
        // CFRelease(theEvent2); 

        delayCGEventPost(kCGHIDEventTap, spaceUp);

        usleep(2000000);
    }

    delayCGEventPost(kCGHIDEventTap, qUp);
    delayCGEventPost(kCGHIDEventTap, wUp);
    delayCGEventPost(kCGHIDEventTap, spaceUp);

    // delayCGEventPost(kCGHIDEventTap, key6Down);
    // delayCGEventPost(kCGHIDEventTap, key6Up);

    CFRelease(qDown); 
    CFRelease(qUp); 
    CFRelease(wDown); 
    CFRelease(wUp); 
    // CFRelease(eDown); 
    // CFRelease(eUp); 
    // CFRelease(rDown); 
    // CFRelease(rUp); 
    CFRelease(spaceDown); 
    CFRelease(spaceUp); 

    return NULL;
}


void* DJsushua(void* args){
    gFuzhuType = FUZHU_TYPE_DJ;
    CGEventRef qDown = CGEventCreateKeyboardEvent (NULL, (CGKeyCode)12, true);  // q
    CGEventRef qUp = CGEventCreateKeyboardEvent (NULL, (CGKeyCode)12, false);  // q
    delayCGEventPost(kCGHIDEventTap, qUp);
    delayCGEventPost(kCGHIDEventTap, qDown);
    CFRelease(qDown); 
    CFRelease(qUp); 
    return NULL;
}

void* chongzhu(void* args){
    int gridX = 1430, gridY = 615;
    CGPoint pointGrid;
    CGPoint pointLeft = CGPointMake(580, 840);
    CGPoint pointCenter = CGPointMake(730, 840);
    CGPoint pointRight = CGPointMake(850, 840);
    CGPoint pointOK = CGPointMake(240, 830);

    CGEventRef theEvent;
    CGEventRef rightEvent;

    theEvent = CGEventCreateMouseEvent(NULL, kCGEventLeftMouseDown, pointRight, kCGMouseButtonLeft);  
    CGEventSetIntegerValueField(theEvent, kCGMouseEventClickState, 1);  

    rightEvent = CGEventCreateMouseEvent(NULL, kCGEventRightMouseDown, pointRight, kCGMouseButtonRight);  
    CGEventSetIntegerValueField(rightEvent, kCGMouseEventClickState, 1);  


    pointGrid = CGPointMake(gridX, gridY);

    CGEventSetLocation(theEvent, pointRight);
    CGEventSetType(theEvent, kCGEventLeftMouseDown); 
    delayCGEventPost(kCGHIDEventTap, theEvent); 
    CGEventSetType(theEvent, kCGEventLeftMouseUp);  
    delayCGEventPost(kCGHIDEventTap, theEvent);

    usleep(100000);

    CGEventSetLocation(theEvent, pointLeft);
    CGEventSetType(theEvent, kCGEventLeftMouseDown); 
    delayCGEventPost(kCGHIDEventTap, theEvent); 
    CGEventSetType(theEvent, kCGEventLeftMouseUp);  
    delayCGEventPost(kCGHIDEventTap, theEvent);

    usleep(100000);

    CGEventSetLocation(theEvent, pointCenter);
    CGEventSetType(theEvent, kCGEventLeftMouseDown); 
    delayCGEventPost(kCGHIDEventTap, theEvent); 
    CGEventSetType(theEvent, kCGEventLeftMouseUp);  
    delayCGEventPost(kCGHIDEventTap, theEvent);

    usleep(100000);

    CGEventSetLocation(rightEvent, pointGrid);
    CGEventSetType(rightEvent, kCGEventRightMouseDown); 
    delayCGEventPost(kCGHIDEventTap, rightEvent); 
    CGEventSetType(rightEvent, kCGEventRightMouseUp);  
    delayCGEventPost(kCGHIDEventTap, rightEvent);

    usleep(100000);

    CGEventSetLocation(theEvent, pointOK);
    CGEventSetType(theEvent, kCGEventLeftMouseDown); 
    delayCGEventPost(kCGHIDEventTap, theEvent); 
    CGEventSetType(theEvent, kCGEventLeftMouseUp);  
    delayCGEventPost(kCGHIDEventTap, theEvent);

    usleep(100000);

    CGEventSetLocation(theEvent, pointGrid);
    CGEventSetType(theEvent, kCGEventMouseMoved); 
    delayCGEventPost(kCGHIDEventTap, theEvent); 


    CFRelease(theEvent); 
    CFRelease(rightEvent); 

    return NULL;
}

int gShengJiTag = 0;
void* shengjiChuanqi(void* args){
    int i=0, j=0;
    int gridX = 1430, gridY = 615;
    CGPoint pointGrid;
    CGPoint pointLeft = CGPointMake(580, 840);
    CGPoint pointCenter = CGPointMake(730, 840);
    CGPoint pointRight = CGPointMake(850, 840);
    CGPoint pointOK = CGPointMake(240, 830);

    CGEventRef theEvent;
    CGEventRef rightEvent;

    theEvent = CGEventCreateMouseEvent(NULL, kCGEventLeftMouseDown, pointRight, kCGMouseButtonLeft);  
    CGEventSetIntegerValueField(theEvent, kCGMouseEventClickState, 1);  

    rightEvent = CGEventCreateMouseEvent(NULL, kCGEventRightMouseDown, pointRight, kCGMouseButtonRight);  
    CGEventSetIntegerValueField(rightEvent, kCGMouseEventClickState, 1);  

    for (i=0; i!=10; i++){
        if (gShengJiTag == 0) break;

        gridX = 1430 + i*50;

        for(j=0; j!=3; j++){
            if (gShengJiTag == 0) break;

            gridY = 615 + j*50*2;
            pointGrid = CGPointMake(gridX, gridY);

            CGEventSetLocation(theEvent, pointRight);
            CGEventSetType(theEvent, kCGEventLeftMouseDown); 
            delayCGEventPost(kCGHIDEventTap, theEvent); 
            CGEventSetType(theEvent, kCGEventLeftMouseUp);  
            delayCGEventPost(kCGHIDEventTap, theEvent);

            usleep(100000);

            CGEventSetLocation(theEvent, pointLeft);
            CGEventSetType(theEvent, kCGEventLeftMouseDown); 
            delayCGEventPost(kCGHIDEventTap, theEvent); 
            CGEventSetType(theEvent, kCGEventLeftMouseUp);  
            delayCGEventPost(kCGHIDEventTap, theEvent);

            usleep(100000);

            CGEventSetLocation(theEvent, pointCenter);
            CGEventSetType(theEvent, kCGEventLeftMouseDown); 
            delayCGEventPost(kCGHIDEventTap, theEvent); 
            CGEventSetType(theEvent, kCGEventLeftMouseUp);  
            delayCGEventPost(kCGHIDEventTap, theEvent);

            usleep(100000);

            CGEventSetLocation(rightEvent, pointGrid);
            CGEventSetType(rightEvent, kCGEventRightMouseDown); 
            delayCGEventPost(kCGHIDEventTap, rightEvent); 
            CGEventSetType(rightEvent, kCGEventRightMouseUp);  
            delayCGEventPost(kCGHIDEventTap, rightEvent);

            usleep(100000);

            CGEventSetLocation(theEvent, pointOK);
            CGEventSetType(theEvent, kCGEventLeftMouseDown); 
            delayCGEventPost(kCGHIDEventTap, theEvent); 
            CGEventSetType(theEvent, kCGEventLeftMouseUp);  
            delayCGEventPost(kCGHIDEventTap, theEvent);
            usleep(100000);

            // usleep(2000000);
        }

        if (gShengJiTag == 0) break;
    }
    CFRelease(theEvent); 
    CFRelease(rightEvent); 

    gShengJiTag = 0;
    return NULL;
}

int gPickUpTag = 0;
void* pickUp(void* args){
    int tag = gPickUpTag;
    CGPoint point;

    while(tag == gPickUpTag){
        CGEventRef ourEvent = CGEventCreate(NULL);
        point = CGEventGetLocation(ourEvent);
        CFRelease(ourEvent);

        CGEventRef theEvent = CGEventCreateMouseEvent(NULL, kCGEventLeftMouseDown, point, kCGMouseButtonLeft);  
        CGEventSetIntegerValueField(theEvent, kCGMouseEventClickState, 1);  
        delayCGEventPost(kCGHIDEventTap, theEvent);  
        CGEventSetType(theEvent, kCGEventLeftMouseUp);  
        delayCGEventPost(kCGHIDEventTap, theEvent);
        CFRelease(theEvent); 

        usleep(100000);
    }

    return NULL;
}

int gLeftMouseDotTag = 0;
void* leftMouseDots(void* args){
    CGPoint point;

    while(gLeftMouseDotTag == 1 ){
        CGEventRef ourEvent = CGEventCreate(NULL);
        point = CGEventGetLocation(ourEvent);
        CFRelease(ourEvent);

        CGEventRef theEvent = CGEventCreateMouseEvent(NULL, kCGEventLeftMouseDown, point, kCGMouseButtonLeft);  
        CGEventSetIntegerValueField(theEvent, kCGMouseEventClickState, 1);  
        delayCGEventPost(kCGHIDEventTap, theEvent);  
        CGEventSetType(theEvent, kCGEventLeftMouseUp);  
        delayCGEventPost(kCGHIDEventTap, theEvent);
        CFRelease(theEvent); 

        usleep(100000);
    }

    return NULL;
}

int gRightMouseDotTag = 0;
void* rightMouseDots(void* args){
    CGPoint point;

    while(gRightMouseDotTag == 1 ){
        CGEventRef ourEvent = CGEventCreate(NULL);
        point = CGEventGetLocation(ourEvent);
        CFRelease(ourEvent);

        CGEventRef theEvent = CGEventCreateMouseEvent(NULL, kCGEventRightMouseDown, point, kCGMouseButtonRight);  
        CGEventSetIntegerValueField(theEvent, kCGMouseEventClickState, 1);  
        delayCGEventPost(kCGHIDEventTap, theEvent);  
        CGEventSetType(theEvent, kCGEventRightMouseUp);  
        delayCGEventPost(kCGHIDEventTap, theEvent);
        CFRelease(theEvent); 

        usleep(100000);
    }

    return NULL;
}

void runTask( void *(*task)(void*) ){
    pthread_t p;
    pthread_create(&p, NULL, task, NULL);
}

CGEventRef
myCGEventCallback(CGEventTapProxy proxy, CGEventType type,
                  CGEventRef event, void *refcon)
{
    
    // Paranoid sanity check.
    if ((type != kCGEventKeyDown) && (type != kCGEventKeyUp) 
        // && (type != kCGEventLeftMouseUp) && (type != kCGEventRightMouseUp) 
        && type != 26 && type != 22)
        return event;

    // The incoming keycode.
    CGKeyCode keycode = (CGKeyCode)CGEventGetIntegerValueField(
                                       event, kCGKeyboardEventKeycode);

    //Keypress code goes here.
    // printf("key type is %d, keycode = %d\n", type, keycode);
    // printf("kCGEventScrollWheel=%d\n", kCGEventScrollWheel);
    // printf("kCGEventOtherMouseDown=%d\n", kCGEventOtherMouseDown);
    // printf("kCGEventOtherMouseUp=%d\n", kCGEventOtherMouseUp);

    if ( type == kCGEventKeyUp ) {
        if ( keycode == 82 ) { // Num 0 
            runTask(xueyan);
        } if ( keycode == 65 ){ // Num del
            runTask(fenjie);
        } if ( keycode == 69 ){ // Num +
            if(gShengJiTag == 1){
                gShengJiTag = 0;
            }else{
                gShengJiTag = 1;
                runTask(shengjiChuanqi);
            }
        } else if ( keycode == 89 ) {// Num 7
            runTask(fuzhuDH);
        } else if ( keycode == 91 ) {// Num 8
            runTask(DJsushua);
        } else if ( keycode == 92 ) {// Num 9
            gFuzhuType = FUZHU_TYPE_MZ;
        } else if ( keycode == 87 ) {// Num 5
            gFuzhuType = FUZHU_TYPE_FS;
        } else if ( keycode == 78 ) {// Num -
            runTask(chongzhu);
        } else if ( keycode == 86 ) {// 4
            gFuzhuType = FUZHU_TYPE_SL;
        }
    }
    
    // if (type == kCGEventLeftMouseUp){
    //     gLeftMouseDotTag = 0;
    //     printf("kCGEventLeftMouseUp\n");
    // }
    
    // if (type == kCGEventRightMouseUp){
    //     gRightMouseDotTag = 0;
    // }
    
    if (type == kCGEventOtherMouseUp){    // 鼠标功能键弹起
        CGKeyCode number = (CGKeyCode)CGEventGetIntegerValueField(event, kCGMouseEventButtonNumber);
        // printf("number=%d\n", number);
        
        if (number == 2) {        // 鼠标滚轮按下

        }else if (number == 3) {        // 鼠标左侧面后面那个键
            if (gFuzhuType == FUZHU_TYPE_DH){  // DH
                gFuzhuDHTag++;
                if(gFuzhuDHTag%2 !=0){
                    runTask(fuzhuDHLoop);
                }
            }else if (gFuzhuType == FUZHU_TYPE_DJ){ // 豆角
            }else if (gFuzhuType == FUZHU_TYPE_SL){ // 死灵
                gFuzhuSLTag++;
                if(gFuzhuSLTag%2 !=0){
                    runTask(fuzhuSLLoop);
                }
            }else if (gFuzhuType == FUZHU_TYPE_MZ){ // 蛮子
                gFuzhuMZTag++;
                if(gFuzhuMZTag%2 !=0){
                    runTask(fuzhuManziLoop);
                }
            }else if (gFuzhuType == FUZHU_TYPE_FS){ // 法师
                gFaShiTag++;
                if(gFaShiTag%2 !=0){
                    runTask(fashiLoop);
                }
            }
        }else if( number == 4) {  // 鼠标左侧面前面那个键
            gPickUpTag++;
            if(gPickUpTag%2 !=0){
                runTask(pickUp);
            }
        }
    }
    
    // if (type == kCGEventScrollWheel){    // 鼠标滚轮上下
    //     int number1 = (int)CGEventGetIntegerValueField(event, kCGScrollWheelEventDeltaAxis1);

    //     if (number1 > 0){   // 向上滚轮
    //         gRightMouseDotTag = 0;
    //     }else if(number1 < 0){  // 向下滚轮
    //         if(gRightMouseDotTag ==0 ){
    //             gRightMouseDotTag = 1;
    //             runTask(rightMouseDots);
    //         }
    //     }
    // }

    // We must return the event for it to be useful.
    return event;
}

int
main(void)
{
    CFMachPortRef      eventTap;
    CGEventMask        eventMask;
    CFRunLoopSourceRef runLoopSource;

    // Create an event tap. We are interested in key presses.
    // eventMask = ((1 << kCGEventKeyDown) | (1 << kCGEventKeyUp) | (1 << kCGEventLeftMouseDown));
    eventMask = kCGEventMaskForAllEvents;
    eventTap = CGEventTapCreate( kCGAnnotatedSessionEventTap, kCGHeadInsertEventTap, 0,
                                eventMask, myCGEventCallback, NULL);
    if (!eventTap) {
        fprintf(stderr, "failed to create event tap\n");
        exit(1);
    }   

    // Create a run loop source.
    runLoopSource = CFMachPortCreateRunLoopSource(
                        kCFAllocatorDefault, eventTap, 0);

    // Add to the current run loop.
    CFRunLoopAddSource(CFRunLoopGetCurrent(), runLoopSource,
                       kCFRunLoopCommonModes);

    // Enable the event tap.
    CGEventTapEnable(eventTap, true);

    // Set it all running.
    CFRunLoopRun();

    exit(0);
}