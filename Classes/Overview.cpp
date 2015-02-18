//
//  Overview.cpp
//  TableView01
//
//  Created by MAEDAHAJIME on 2015/02/18.
//
//

#include "Overview.h"
#include "SecondScene.h"
//音をならすためにinclude
#include "SimpleAudioEngine.h"

/// 行数格納用のキー
const char* ROW_KEY = "row";

Scene* Overview::createScene()
{
    auto scene = Scene::create();
    auto layer = Overview::create();
    // sceneにlayerを読み込み表示する
    scene->addChild(layer);
    
    return scene;
}

// on "init" you need to initialize your instance
bool Overview::init()
{
    //初期化
    if ( !Layer::init() ) return false;
    
    //画面サイズサイズを取得
    window_size = Director::getInstance()->getWinSize();
    
    // バックグランドカラー
    auto background = LayerColor::create(Color4B::WHITE,
                                         window_size.width,
                                         window_size.height);
    
    // バックグランドカラー 第2引数は表示順
    this->addChild(background, 0);
    
    // テーブル一覧ラベルを生成
    auto label1 = Label::createWithSystemFont("テーブル一覧", "Arial", 60);
    
    label1->setColor(Color3B::BLACK);
    
    // ラベルの設置
    label1->setPosition(Vec2(window_size.width / 2 ,window_size.height - 80));
    
    // ラベルタイトルを呼び込み追加
    this->addChild(label1,1);
    
    
    // テーブルのヘッダー空間
    TableView* tableView = TableView::create(this,Size(window_size.width,window_size.height*9/10));
    // テーブル全体表示
    //TableView* tableView = TableView::create(this, window_size);
    
    //展開方向
    tableView->setDirection(TableView::Direction::VERTICAL);
    //表示順序上からしたへ
    tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    
    //追加
    tableView->setDelegate(this);
    addChild(tableView);
    // tableViewに呼び込む
    tableView->reloadData();
    
    return true;
}

// セルの大きさを設定する
Size Overview::cellSizeForTable(TableView *table){
    return Size(window_size.width, 100);
}

// 1セルに表示させるValueをセット
TableViewCell* Overview::tableCellAtIndex(TableView *table, ssize_t idx){
    
    // 行番号
    std::string id = StringUtils::format("%zd", idx);
    // 行テキスト
    std::string text = StringUtils::format("行目");
    // セル
    //auto *cell = table->dequeueCell();
    TableViewCell *cell = table->dequeueCell();
    
    cell = new TableViewCell();
    // autoreleaseを呼び出す
    cell->autorelease();
    
    // セルの背景は交互に色を変更する
    auto background_color = Color3B::GREEN;
    if (idx%2) {
        background_color = Color3B::BLUE;
    }
    
    // Background
    Sprite* bg = Sprite::create();
    bg->setAnchorPoint(Point(0, 0));
    bg->setTextureRect(Rect(0, 0, window_size.width, 90));
    bg->setColor(background_color);
    bg->setTag(100);
    // Backgroundを呼び出し表示
    cell->addChild(bg);
    
    // ボーダーライン
    Sprite* line = Sprite::create();
    line->setAnchorPoint(Point(0, 0));
    line->setTextureRect(Rect(0, 0, window_size.width, 1));
    line->setColor(Color3B::WHITE);
    cell->addChild(line);
    
    // 画像
    Sprite* imge_1 = Sprite::create("imge80.png");
    imge_1->setAnchorPoint(Point(0, 0));
    imge_1->setPosition(Point(10, +5));
    cell->addChild(imge_1);
    
    // IDテキスト部分
    auto *label_1 = LabelTTF::create(id.c_str(), "Arial", 80);
    label_1->setAnchorPoint(Point(0, 0));
    label_1->setPosition(Point(110, -4));
    label_1->setColor(Color3B::WHITE);
    cell->addChild(label_1);
    
    // テキスト部分
    auto *label_2 = LabelTTF::create(text.c_str(), "Arial", 80);
    label_2->setAnchorPoint(Point(0, 0));
    label_2->setPosition(Point(210, -4));
    label_2->setColor(Color3B::WHITE);
    cell->addChild(label_2);
    
    return cell;
}

// セル数
ssize_t Overview::numberOfCellsInTableView(TableView *table){
    return 60;
}

// セルがタッチされた時のcallback
void Overview::tableCellTouched(TableView* table, TableViewCell* cell){
    
    log("%ziのセルがタッチされました", cell->getIdx());
    // cell 行番号
    float row = cell->getIdx();
    
    // 行番号保存
    UserDefault::getInstance()->setIntegerForKey(ROW_KEY, row);

    // 効果音を鳴らす
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("onepoint26.mp3");
    
    
    // 遷移先の画面のインスタンス
    auto *pScene = SecondScene::createScene();
    
    // 0.5秒かけてフェードアウトしながら次の画面に遷移します
    //    引数１:フィードの時間
    //    引数２：移動先のシーン
    //    引数３：フィードの色（オプション）
    TransitionFade* transition = TransitionFade::create(0.5f, pScene);
    
    // 遷移実行  遷移時のアニメーション　http://study-cocos2d-x.info/scenelayer/55/
    // 直前のsceneはもう使わないから捨ててしまう方法。基本はこれになります。
    Director::getInstance()->replaceScene(transition);
}