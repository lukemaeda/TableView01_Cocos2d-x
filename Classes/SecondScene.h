//
//  SecondScene.h
//  TableView01
//
//  Created by MAEDAHAJIME on 2015/02/18.
//
//

#ifndef __TableView01__SecondScene__
#define __TableView01__SecondScene__

#include "cocos2d.h"

class SecondScene : public cocos2d::Layer
{
protected:

    
public:
    static cocos2d::Scene* createScene();
    
    //初期化のメソッド
    virtual bool init();
    
    // スタートボタン押下時の処理宣言 戻る Object →　Ref に変更
    void pushBack(cocos2d::Ref *pSender);
    
    // create()を使えるようにしている。
    CREATE_FUNC(SecondScene);
};

#endif /* defined(__TableView01__SecondScene__) */
