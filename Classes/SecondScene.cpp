//
//  SecondScene.cpp
//  TableView01
//
//  Created by MAEDAHAJIME on 2015/02/18.
//
//

#include "SecondScene.h"
#include "Overview.h"

//音をならすためにinclude
#include "SimpleAudioEngine.h"

// 名前空間 #define USING_NS_CC using namespace cocos2d
USING_NS_CC;

using namespace std; // String*

/// 行数格納用のキー
const char* ROW_KEY1 = "row";

Scene* SecondScene::createScene()
{
    // 「シーン」は自動解放オブジェクトです
    auto scene = Scene::create();
    
    // 「レイアウト」は自動解放オブジェクトです
    auto layer = SecondScene::create();
    
    // シーンに子としてレイヤーを追加
    scene->addChild(layer);
    
    // シーンを返す
    return scene;
}

// 「INIT」初期化
bool SecondScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    //画面の座標関係の詳しい説明はここ http://www.cocos2d-x.org/wiki/Coordinate_System
    //画面サイズを取得
    Size winSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();  //マルチレゾリューション対応がどうとか
    
    // バックグランドカラー
    auto background = LayerColor::create(Color4B::BLUE,
                                         winSize.width,
                                         winSize.height);
    //バックグランドカラー追加 第2引数は表示順
    this->addChild(background, 0);
    
    // UserDefault 読込　LOG表示
    auto userDefault =UserDefault::getInstance();
    int row = userDefault->getIntegerForKey("row");
    
    // row + 行目との結合
    auto *rowstring = String::createWithFormat("%i行目",row);
    //auto *rowstring = String::createWithFormat("行目");
    // キャスト変換
    string _rowstring = rowstring->getCString();
    // ラベル生成
    auto label01 = Label::createWithSystemFont(_rowstring, "arial", 140);
    // ラベルの色:ホワイト
    label01->setColor(Color3B::WHITE);
    //画面の中央に表示
    label01->setPosition(Point(winSize.width/2, winSize.height/2 - 150));
    // Layerにラベルを追加
    this->addChild(label01);
    
    //_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
    
    // タイトルを設置
    auto lbl_title = Label::createWithSystemFont("Second", "arial", 100);
    lbl_title->setPosition(Point(origin.x + winSize.width/2,
                                     origin.y + winSize.height
                                     -lbl_title->getContentSize().height));
    this->addChild(lbl_title,1);
    
    //戻るボタンを設置
    auto backButton = MenuItemImage::create("CloseNormalBack.png",  //表示
                                            "CloseSelected.png",  //タップ時の画像
                                            CC_CALLBACK_1(SecondScene::pushBack, this));
    
    backButton->setPosition(Point(winSize.width /2 ,winSize.height/2 + 100));
    
    //create menu, it's an autorelease object
    auto menu = Menu::create(backButton, NULL);
    
    menu->setPosition(Point::ZERO);
    
    this->addChild(menu, 1);
    
    return true;
}

// pushBackボタン
void SecondScene::pushBack(Ref *pSender)
{
    // 効果音を鳴らす
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("onepoint26.mp3");

    // 遷移先の画面のインスタンス
    Scene *pScene = Overview::createScene();

    // 0.5秒かけてフェードアウトしながら次の画面に遷移します
    //    引数１:フィードの時間
    //    引数２：移動先のシーン
    //    引数３：フィードの色（オプション）
    TransitionFade* transition = TransitionFade::create(0.5f, pScene);

    //遷移実行  遷移時のアニメーション　http://study-cocos2d-x.info/scenelayer/55/
    Director::getInstance()->replaceScene(transition);
    
}
